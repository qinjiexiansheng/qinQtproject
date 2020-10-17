#ifndef VIDEODECODE_H
#define VIDEODECODE_H

#if 1
extern "C"{
//    #include "lib/include/libavcodec/avcodec.h"
  //  #include "lib/include/libavformat/avformat.h"
   // #include "lib/include/libavutil/avutil.h"
  //  #include "lib/include/libavutil/mem.h"
  //  #include "lib/include/libavutil/fifo.h"
  //  #include "lib/include/libswscale/swscale.h"
  //  #include <stdint.h>
  //  #include "lib/include/libavutil/eval.h"
  //  #include "lib/include/libavutil/parseutils.h"
  //  #include "lib/include/libavutil/opt.h"
  //  #include "lib/include/libavfilter/avfilter.h"
}
#include <QObject>
#include <QImage>
#include <QThread>
#include <QDebug>
#include <QList>
#include <QTimer>
typedef unsigned char   uint8_t;

class VideoDecode : public QObject
{
    Q_OBJECT
public:
    VideoDecode(QObject *parent = 0);//构造函数
    QString getVideoFilename();//获取视频文件名
    void setVideoFilename(QString nVideoFilename);//设置视频文件名
    void videoPlay();//视频播放
    void videoStop();//视频停止
    void videoPause();//视频暂停
signals:
    void displayImage(QImage nImage);//显示图片
    //发送解码线程的信号，如解码视频结束、视频解码错误
    void videoDecodeSignal(QString nVideoString);
public slots:
    void decode();
private:
    void init();//初始化
    void freeSpace();//释放空间
private:
    QString mVideoFilename;//视频文件名
    AVFormatContext *mAVFormatContext;//格式内容
    AVCodecContext *mAVCodecContext;//解码内容
    AVCodec *mAVCodec;//解码器
    AVPacket *mAVPacket;//包
    AVFrame *mAVFrame;//画面
    AVFrame *mAVFrameRGB;//画面
    int mVideoStream;
    struct SwsContext *mSwsContext;
    uint8_t *mOutBuffer;
    QTimer *mTimer;//定时器，决定解码间隔
    bool mIsReady;
    int mTargetWidth;
    int mTargetHeight;
    int mTest;
};

#endif


#endif // VIDEODECODE_H
