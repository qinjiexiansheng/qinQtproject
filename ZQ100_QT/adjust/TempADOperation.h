#ifndef TEMPADOPERATION_H
#define TEMPADOPERATION_H

#include <QObject>

class TempADOperation : public QObject
{
public:
//    TempADOperation(QObject *parent = 0) : QObject(parent){
//        mSatData = SatData::initance();
//    }

    void loadADTable();
    void saveADTable();
    void updateADTable();
    void countTempAD();
    void takeEffectADTable();
private:
 //   SatData *mSatData;
};

#endif // TEMPADOPERATION_H
