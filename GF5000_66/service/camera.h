#ifndef CAMERA_H
#define CAMERA_H
#include <QObject>
#include "model/satdata.h"
#include "lib/client.h"
#include "uitls/fileope.h"

#include <QImageIOHandler>
#include <QImage>

/*======================================
  类名 ： Camera
  与图像相关的操作
  ======================================*/
class Camera : public QObject
{
public:
    Camera(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void photograph();//拍照
    void videoStart();//开启录像
    void videoStop();//停止录像
    void imageFreeze();//图像冻结
    void imageThaw();//图像解冻
private:
    SatData *mSatData;

};
#endif // CAMERA_H
