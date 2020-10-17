#ifndef INFRAREDMODE_H
#define INFRAREDMODE_H

#include <QObject>
#include "model/satdata.h"
#include "lib/client.h"
class InfraredMode : public QObject
{
public:
    InfraredMode(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void iron();
    void ironInv();
    void grey();
    void greyInv();
    void feather();
    void rainBow();
private:
    SatData *mSatData;
};

#endif // INFRAREDMODE_H
