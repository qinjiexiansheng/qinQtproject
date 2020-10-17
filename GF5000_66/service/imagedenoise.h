#ifndef IMAGEDENOISE_H
#define IMAGEDENOISE_H
#include <QObject>
#include "model/satdata.h"
#include "lib/client.h"
class DenoiseMode : public QObject
{
public:
    DenoiseMode(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void denoiseNot();
    void denoiseOne();
private:
    SatData *mSatData;
};

#endif // IMAGEDENOISE_H
