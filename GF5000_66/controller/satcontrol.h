#ifndef SATCONTROL_H
#define SATCONTROL_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "model/satdata.h"
#include "service/camera.h"
#include "service/datarefresh.h"
#include "service/gearadjust.h"
#include "service/imagedenoise.h"
#include "service/infraredmode.h"
#include "service/otherbus.h"
#include "service/parameteradjust.h"
#include "uitls/operationfield.h"
#include "schema/basicschema.h"
#include "schema/correctschema.h"
#include "schema/denoiseschema.h"
#include "schema/displayschema.h"
#include "schema/imagefreeschema.h"
#include "schema/infraredschema.h"
#include "schema/gearschema.h"
#include <QDebug>
#include <QThread>

#include <QTranslator>

class SatControl : public QObject
{
    Q_OBJECT
public:
    static SatControl* initance();//获取该对象指针
    void setTranslator(QTranslator *nTranslator);
    void changeLanguage(QString nLanguage);
public slots:
    void doService(int nOpeStr,QString nParStr);
    void init();
private slots:
    void doDataUpdate();//数据更新（定时操作）
    void doAutoManual();//打档操作（定时操作）
    void doAutoSavePhoto();//保存图片操作（定时操作
private:
    SatControl(QObject *parent = 0);
    static SatControl* _SatControl;
    SatData* mSatData;
    QTimer* mDUTimer;//更新数据定时器
    QTimer* mAMTimer;//自动打档定时器
    QTimer *mASTimer;//自动保存图片定时器
    //业务对象
    Camera *mCameraOpe;
    TempADOperation *mTempADOpe;
    KFileOperation *mKFileOpe;
    DataOperation *mDataOpe;
    GearMode *mGearOpe;
    DenoiseMode *mDenoiseOpe;
    InfraredMode *mInfraredOpe;
    OtherBus *mOtherOpe;
    AdjustParam *mAdjustOpe;


    QTranslator *mTranslator;

};

#endif // SATCONTROL_H
