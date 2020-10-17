#ifndef FILEOPE_H
#define FILEOPE_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHash>

//#include "uitls/exifparam.h"



class FileOpe
{
public:
    //文件复制，传入的路径是全路径
    static bool copyFile(const QString &nOriginalPath ,const QString &nTargetPath, bool nCover = true);
    //目录复制，传入的路径时全路径
    static bool copyDir(const QString &nOriginalPath ,const QString &nTargetPath, bool nCover = true);
    //编号文件，传入路径，文件名（test%1.txt）
    static QString numberFile(QString nDirStr,QString nFileStr);

    static bool writeInfoToPhoto(const char *nPhotoFileName);

};







#endif // FILEOPE_H
