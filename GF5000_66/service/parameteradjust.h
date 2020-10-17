#ifndef PARAMETERADJUST_H
#define PARAMETERADJUST_H
#include <QObject>
#include "model/satdata.h"
#include "lib/client.h"
class AdjustParam : public QObject
{
public:
    AdjustParam(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void adjustFID();
    void adjustGSK();
    void adjustGAIN();
    void adjustINT();
    void adjustAutoInt();
private:
    int autoInt();
private:
    SatData *mSatData;
};

#endif // PARAMETERADJUST_H
