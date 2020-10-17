#ifndef SATDATA_H
#define SATDATA_H

#include <QObject>
#include <QStandardItemModel>
#include "interface.h"

class satData : public QObject
{
    Q_OBJECT
public:
    explicit satData(QObject *parent = 0);

    QString getTmpAdFile();
    QString getTmpAdNewFile();
    satData *initance();

    enum GearEnum{GEARONE,GEARTWO};


    //temp ad table operation ======begin======
    QString findAdKeyForValue(int nValue);
    QString findTempKeyForValue(float nValue);
    QString findDiffKeyForValue(float nValue);
    int findAdValueForKey(QString nKey);
    float findTempValueForKey(QString nKey);
    float findDiffValueForKey(QString nKey);
    void appendAdList(IntPair *nAdPair);
    void appendAdList(QString nKey,int nValue = 0);
    void appendTempList(FloatPair *nTempPair);
    void appendTempList(QString nKey,float nValue = 0);
    void appendDiffList(FloatPair *nDiffPair);
    void appendDiffList(QString nKey,float nValue = 0);
    void modifyAdList(QString nKey,int nValue = 0);
    void modifyTempList(QString nKey,float nValue = 0);
    void modifyDiffList(QString nKey,float nValue = 0);
    QList<FloatPair *> *getTempList();
    QList<FloatPair *> *getDiffList();
    QList<IntPair *> *getAdList();
    void clearAdList();
    void clearTempList();
    void clearDiffList();
    int getTabNum();
    float getTabBaseTemp();
    int getTabBegAD();
    int getTabMaxAD();
    int getTabMinAD();
    float getDiff30();
    void setTabNum(int nTabNum);
    void setTabBaseTemp(float nTabBaseTemp);
    void setTabBegAD(int nTabBegAD);
    void setTabMaxAD(int nTabMaxAD);
    void setTabMinAD(int nTabMinAD);
    void setDiff30(float nDiff30);
    //temp ad table operation ======end======

signals:

public slots:

private:
    int mTabNum;//个数，主要是为了保存文本读出的数据，以下几个同理
    int mTabBegAD;
    int mTabMaxAD;
    int mTabMinAD;
    float mDiff30;
    float mMaxTemp;//最大温度
    float mMinTemp;//最小温度
    float mCenterTemp;//中心点温度

    QList<FloatPair*> mTempList;//温度AD表中的temp项
    QList<FloatPair*> mDiffList;//温度AD表中的diff项
    QList<IntPair*> mAdList;//温度AD表中的AD项
    QString mTmpAdFile;//当前标定表文件
    QString mTmpAdNewFile;//当前标定表临时文件
};

#endif // SATDATA_H
