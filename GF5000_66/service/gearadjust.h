#ifndef SENMODEL_H
#define SENMODEL_H

#include <QObject>
#include "service/datarefresh.h"
#include "service/otherbus.h"
#include "service/parameteradjust.h"

class GearMode : public QObject
{
public:
    GearMode(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
        mTempADOpe = new TempADOperation(this);
        mKFileOpe = new KFileOperation(this);
        mDataOpe = new DataOperation(this);
        mAdjustOpe = new AdjustParam(this);
        mOtherOpe = new OtherBus(this);
    }
    void gearOne();
    void gearTwo();
private:
    void msDelay(int nMs);
    SatData *mSatData;
    TempADOperation *mTempADOpe;
    KFileOperation *mKFileOpe;
    DataOperation *mDataOpe;
    AdjustParam *mAdjustOpe;
    OtherBus *mOtherOpe;
};

#endif // SENMODEL_H
