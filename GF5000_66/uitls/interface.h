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




/*
 * =====================================================================================
 *
 *      Classname:  DataObserver
 *
 *    Description:  数据观察者接口,如果要观察数据的变化,则可以继承该接口,再在对应的数据类里注册,
 *                  当数据发生变化时,doUpdate()函数会被调用
 *
 *        Created:  2018年4月8日
 *
 * =====================================================================================
 */
class DataObserver
{
public:
    DataObserver(){}
    virtual void doUpdate(QString nStr)=0;
};



//抽象模式接口
class AbstractSchema
{
public:
    AbstractSchema(){}
    virtual QString name()=0;//模式名字，也用于显示在图片下面
    virtual int doLeftShort()=0;
    virtual int doLeftLong()=0;
    virtual int doRightShort()=0;
    virtual int doRightLong()=0;
    virtual int doRightRelease()=0;
    virtual int entryMode()=0;
    virtual int leaveMode()=0;
    virtual QString imageNormal()=0;
    virtual QString imageFocus()=0;
    virtual QString imageLight()=0;
};



class HighLight
{
public:
    //HighLight(){}
    virtual void setHighLight(bool nHighLight)=0;
    virtual bool isHighLight()=0;
};




#endif // INTERFACE_H
