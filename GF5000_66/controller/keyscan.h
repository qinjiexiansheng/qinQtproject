#ifndef KEYSCAN_H
#define KEYSCAN_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QString>
#include "uitls/macrodefine.h"


class SatKey
{
public:
    SatKey(QString nDevFile,int nKey,bool nState = false){
        mDevFile = nDevFile;
        mKey = nKey;
        mState = nState;
    }

    QString getDevFile(){
        return mDevFile;
    }
    bool getState(){
        return mState;
    }
    void setState(bool nState){
        mState = nState;
    }

    int getKey(){
        return mKey;
    }
private:
    QString mDevFile;
    bool mState;
    int mKey;
};


class KeyScan : public QObject
{
    Q_OBJECT
public:
    KeyScan(QObject *parent = 0);
signals:
    void keyChangeSignal(int nKey, bool nPress , bool nRepeat);
public slots:
    void init();
private slots:
    void startScan();
private:
    int getGpio(QString nDevFile);
    void setGpio(QString nDevFile,int nLevel);
    void setGpioDir(QString nDevFile,int nDir);
    QTimer *mScanTimer;
    QList<SatKey *> mKeyList;
};

#endif // KEYSCAN_H
