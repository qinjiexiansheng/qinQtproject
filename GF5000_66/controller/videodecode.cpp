#include "videodecode.h"

//构造函数
VideoDecode::VideoDecode(QObject *parent) : QObject(parent){
    av_register_all();//注册
    mAVFormatContext = NULL;//格式内容
    mAVCodecContext = NULL;//解码内容
    mAVCodec = NULL;//解码器
    mAVPacket = NULL;//包
    mAVFrame = NULL;//画面
    mAVFrameRGB = NULL;//画面
    mOutBuffer = NULL;
    mIsReady = false;
    mTimer = new QTimer();
    mTimer->setInterval(1);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(decode()));
}

QString VideoDecode::getVideoFilename(){
    return mVideoFilename;
}

void VideoDecode::setVideoFilename(QString nVideoFilename){
    mVideoFilename = nVideoFilename;
    mIsReady = false;
    mTest = 0;
    if(!mVideoFilename.isEmpty()){
        init();
    }else{
        emit videoDecodeSignal("FileNameEmpty");//文件名空
    }
}

void VideoDecode::videoPlay(){
    if(mVideoFilename.isEmpty()){
        qDebug("[D]Lin >> Just Debug!");
    }else{
        mTimer->start();
    }

}

void VideoDecode::videoStop(){
    mTimer->stop();
}

void VideoDecode::videoPause(){
    mTimer->stop();
}

void VideoDecode::decode(){
    if(av_read_frame(mAVFormatContext,mAVPacket) < 0){//视频读取完
        mTimer->stop();//停止计时器
        emit videoDecodeSignal("VideoDecodeFinish");//文件解码结束
        return;
    }
    if(mAVPacket->stream_index == mVideoStream){//对于视频帧
        qDebug("[D]Lin >> ============%d===",mTest);
        int nGotPicture;//标记
        int nDecodeRet = avcodec_decode_video2(mAVCodecContext,mAVFrame,&nGotPicture,mAVPacket);//解码
        if(nDecodeRet < 0){
            //解码错误
            mTimer->stop();//停止计时器
            qDebug("[E]Lin >> Decode error!");
            emit videoDecodeSignal("Error");//解码错误
            return;
        }
        if(nGotPicture){
            //格式转换
            sws_scale(mSwsContext,(uint8_t const * const *)mAVFrame->data,
                mAVFrame->linesize,0,mAVCodecContext->height,
                mAVFrameRGB->data,mAVFrameRGB->linesize);
            QImage nImage((uchar *)mAVFrameRGB->data[0],mTargetWidth,
                mTargetHeight,QImage::Format_RGB888);
            emit displayImage(nImage);//发送图片，显示图片
        }
    }
    av_free_packet(mAVPacket);
    qDebug("[D]Lin >> =============%d",mTest);
    mTest++;
}


void VideoDecode::init(){
    freeSpace();//释放空间
    mAVFormatContext = avformat_alloc_context();
    int nErrorNum = avformat_open_input(&mAVFormatContext,mVideoFilename.toStdString().c_str(),NULL,NULL);
    if(nErrorNum < 0){//打开失败
        qDebug("[E]Lin >> AVFormat open the file fail!%d",nErrorNum);
        emit videoDecodeSignal("OpenFileError");
        return;
    }
    if(avformat_find_stream_info(mAVFormatContext,NULL) < 0){
        qDebug("[E]Lin >> Could't find stream infomation!");
        emit videoDecodeSignal("Error");
        return;
    }
    mVideoStream = -1;
    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    for(int i=0; i<mAVFormatContext->nb_streams; i++){
        if(mAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){//流的类型是视频
            mVideoStream = i;
        }
    }
    if(mVideoStream == -1){//没有找到视频流
        qDebug("[E]Lin >> Could't find a video stream!");
        emit videoDecodeSignal("Error");
        return;
    }
    //查找解码器
    mAVCodecContext = mAVFormatContext->streams[mVideoStream]->codec;

    mAVFormatContext->streams[mVideoStream]->r_frame_rate;


    mAVCodec = avcodec_find_decoder(mAVCodecContext->codec_id);
    if(mAVCodec == NULL){
        qDebug("[E]Lin >> The Codec not find!");
        emit videoDecodeSignal("Error");
        return;
    }
    //打开解码器
    if(avcodec_open2(mAVCodecContext,mAVCodec,NULL) < 0){
        qDebug("[E]Lin >> Open the codec fail!");
        emit videoDecodeSignal("Error");
        return;
    }
    //申请AVFrame，单个帧
    mAVFrame = av_frame_alloc();//原始画面
    mAVFrameRGB = av_frame_alloc();//目标画面
    //格式转换上下文
    //sws_getContext()形参参数：
    //源图像宽，源图像高，源图像的像素格式
    //目标图像宽，目标图像高，目标图像的像素格式
    //使用的拉伸算法，源和目的的SwsFilter（涉及到色度/亮度过滤）,参数（可能稍微改变算法的结果）
#if 1
    mTargetWidth = mAVCodecContext->width;
    mTargetHeight = mAVCodecContext->height;
#else
    mTargetWidth = 640*0.8;
    mTargetHeight = 480*0.8;
#endif
    mSwsContext = sws_getContext(mAVCodecContext->width,mAVCodecContext->height,mAVCodecContext->pix_fmt,
                                 mTargetWidth,mTargetHeight,AV_PIX_FMT_RGB24,
                                 SWS_BICUBIC,NULL,NULL,NULL);
    //目标图片大小
    int nNumBytes = avpicture_get_size(AV_PIX_FMT_RGB24,mTargetWidth,mTargetHeight);
    //申请空间
    mOutBuffer = (uint8_t *)av_malloc(nNumBytes*sizeof(uint8_t));
    //填充
    avpicture_fill((AVPicture *)mAVFrameRGB,mOutBuffer,AV_PIX_FMT_RGB24,mTargetWidth,mTargetHeight);
    int nSize = mTargetWidth * mTargetHeight;
    //包申请
    mAVPacket = (AVPacket *)malloc(sizeof(AVPacket));
    av_new_packet(mAVPacket,nSize);
    qDebug("[D]Lin >> ===============The File Infomation=============");
    av_dump_format(mAVFormatContext,0,mVideoFilename.toStdString().c_str(),0);//输出视频信息
    qDebug("[D]Lin >> ===============================================");
    mIsReady = true;
#if 0
    while(1){
        if(av_read_frame(mAVFormatContext,mAVPacket) < 0){
            break;//视频读取完
        }
        if(mAVPacket->stream_index == nVideoStream){
            int nGotPicture;
            int nDecodeRet = avcodec_decode_video2(mAVCodecContext,mAVFrame,&nGotPicture,mAVPacket);
            if(nDecodeRet < 0){
                //解码错误
                qDebug("[E]Lin >> Decode error!");
                return;
            }
            if(nGotPicture){
                sws_scale(mSwsContext,(uint8_t const * const *)mAVFrame->data,
                          mAVFrame->linesize,0,mAVCodecContext->height,
                          mAVFrameRGB->data,mAVFrameRGB->linesize);
                QImage nImage((uchar *)mAVFrameRGB->data[0],mAVCodecContext->width,
                        mAVCodecContext->height,QImage::Format_RGB16);
            }
        }
        av_free_packet(mAVPacket);
    }
    av_free(mOutBuffer);
    av_free(mAVFrameRGB);
    avcodec_close(mAVCodecContext);
    avformat_close_input(&mAVFormatContext);
#endif
}

//释放空间
void VideoDecode::freeSpace(){
    if(mOutBuffer != NULL){
        av_free(mOutBuffer);
        mOutBuffer = NULL;
    }
    if(mAVFrameRGB != NULL){
        av_free(mAVFrameRGB);
        mAVFrameRGB = NULL;
    }
    if(mAVPacket != NULL){
        av_free_packet(mAVPacket);
        mAVPacket = NULL;
    }
    if(mAVFrame != NULL){
        av_free(mAVFrame);
        mAVFrame = NULL;
    }
    if(mAVCodecContext != NULL){
        avcodec_close(mAVCodecContext);
        mAVCodecContext = NULL;
    }
    if(mAVFormatContext != NULL){
        avformat_close_input(&mAVFormatContext);
        mAVFormatContext = NULL;
    }
}

