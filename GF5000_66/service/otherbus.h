#ifndef OTHERBUS_H
#define OTHERBUS_H
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "model/satdata.h"
#include "uitls/fileope.h"
#include "lib/client.h"

class OtherBus : public QObject
{
public:
    OtherBus(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void tableToSD();
    void SDToTable();
    void loadModelData();
    void saveModelData();
    void openLaser();
    void stopLaser();

    void obtainReleaseDate();
private:
    SatData *mSatData;
};

#endif // OTHERBUS_H
