#include "FileOpe.h"

//=======================================================
bool FileOpe::copyFile(const QString &nOriginalPath, const QString &nTargetPath, bool nCover){
    if(nOriginalPath == nTargetPath){
        return true;
    }
    if(!QFile::exists(nOriginalPath)){
        return false;
    }
    if(QFile::exists(nTargetPath)){
        if(!nCover){
            return false;
        }
        QFile::remove(nTargetPath);
    }
    QFile::copy(nOriginalPath,nTargetPath);
    return true;
}

bool FileOpe::copyDir(const QString &nOriginalPath, const QString &nTargetPath, bool nCover){

    QDir nOriginalDir(nOriginalPath);
    QDir nTargeDir(nTargetPath);
    if(!nTargeDir.exists()){
        if(!nTargeDir.mkpath(nTargeDir.absolutePath())){
            qDebug("[D]Lin >> %s",nTargeDir.absolutePath().toStdString().c_str());
            return false;
        }
    }
    if(!nOriginalDir.exists()){
        return false;
    }
    QFileInfoList nFileInfoList = nOriginalDir.entryInfoList();
    foreach(QFileInfo nFileInfo, nFileInfoList){
        if(nFileInfo.fileName() == "." || nFileInfo.fileName() == ".."){
            continue;
        }
        if(nFileInfo.isDir()){
            if(!copyDir(nOriginalPath,nTargetPath,nCover)){
                return false;
            }
        }else{
            if(nCover && nTargeDir.exists(nFileInfo.fileName())){
                nTargeDir.remove(nFileInfo.fileName());
            }
            if(!QFile::copy(nFileInfo.filePath(),nTargeDir.filePath(nFileInfo.fileName()))){
                return false;
            }
        }

    }
    return true;
}





QString FileOpe::numberFile(QString nDirStr, QString nFileStr){
//    QDir nDir(nDirStr);
//    if(!nDir.exists()){
//        if(!nDir.mkdir(nDir.absolutePath())){
//            return NULL;
//        }
//    }
//    QFileInfoList nFileInfoList = nOriginalDir.entryInfoList();
//    foreach(QFileInfo nFileInfo, nFileInfoList){
//        if(nFileInfo.fileName() == "." || nFileInfo.fileName() == ".."){
//            continue;
//        }
//        if(nFileInfo.isDir()){
//            if(!copyDir(nOriginalPath,nTargetPath,nCover)){
//                return false;
//            }
//        }else{
//            if(nCover && nTargeDir.exists(nFileInfo.fileName())){
//                nTargeDir.remove(nFileInfo.fileName());
//            }
//            if(!QFile::copy(nFileInfo.filePath(),nTargeDir.filePath(nFileInfo.fileName()))){
//                return false;
//            }
//        }
//    }
    nFileStr = nFileStr.arg(1);
    return nDirStr+nFileStr;

}


bool FileOpe::writeInfoToPhoto(const char *nPhotoFileName){
    int i;
    ExifFileInfo    *ExifInfo;
    ExifInfo = ( ExifFileInfo* ) malloc ( sizeof(ExifFileInfo));
    memset(ExifInfo, 0x00, sizeof(ExifFileInfo));
    makeExifParam(ExifInfo);
    //printf("\nMake:%s  Modle:%s  CopyRight:%s  UserComments:%s \n",ExifInfo->Make,ExifInfo->Model,ExifInfo->CopyRight,ExifInfo->UserComments);
    char *ExifBuf;
    UINT  ExifLen;
    UINT  bufSize;
    bufSize = EXIF_FILE_SIZE;
    ExifBuf = (char *)malloc(bufSize);
    memset(ExifBuf, 0x20, bufSize);
    printf("ExifBuf has obtain %d byte\n",bufSize);
    makeExifFile ( ExifBuf, &ExifLen, ExifInfo);
    makeNewSatJpgFromBuf( "/home/sat/Sat/Temp/ExifMake/ExifMake/makeExif_5/in.jpg", "/home/sat/Sat/Temp/ExifMake/ExifMake/makeExif_5/out.jpg",ExifBuf, ExifLen);//修改下源和目的路径即可
    free(ExifInfo);
    return true;
}
