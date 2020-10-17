#ifndef SATCONTROL_H
#define SATCONTROL_H

#include <QObject>
#include "TempADOperation.h"

class SatControl : public QObject
{
    Q_OBJECT
public:
    explicit SatControl(QObject *parent = 0);
    static SatControl* initance();//获取该对象指针

public slots:
    void doService(int nOpeStr,QString nParStr);

private:
    static SatControl* _SatControl;

    //业务对象
    Camera *mCameraOpe;
    TempADOperation *mTempADOpe;


};

#endif // SATCONTROL_H
