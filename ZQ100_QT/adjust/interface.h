#ifndef INTERFACE_H
#define INTERFACE_H

#include <QString>

class FloatPair
{
public:
    FloatPair(QString nKey,float nValue = 0){
        mKey = nKey;
        mValue = nValue;
    }
    QString getKey(){
        return mKey;
    }
    float getValue(){
        return mValue;
    }
    void setKey(QString nKey){
        mKey = nKey;
    }
    void setValue(float nValue){
        mValue = nValue;
    }
private:
    QString mKey;
    float mValue;
};


class IntPair
{
public:
    IntPair(QString nKey,int nValue = 0){
        mKey = nKey;
        mValue = nValue;
    }
    QString getKey(){
        return mKey;
    }
    int getValue(){
        return mValue;
    }
    void setKey(QString nKey){
        mKey = nKey;
    }
    void setValue(int nValue){
        mValue = nValue;
    }
private:
    QString mKey;
    int mValue;
};

#endif // INTERFACE_H
