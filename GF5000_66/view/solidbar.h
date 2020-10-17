#ifndef SOLIDBAR_H
#define SOLIDBAR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <QLinearGradient>
#include <QDebug>
#include <QPushButton>
#include <QTextCodec>
#include <QKeyEvent>
#include "uitls/interface.h"
#include "uitls/operationfield.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include "uitls/macrodefine.h"

/*======================================

  温度参考杆 ： SolidBar

 ======================================*/
class SolidBar : public QObject , public QGraphicsItem , public DataObserver
{
    Q_OBJECT
public:
    SolidBar(QObject *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void doUpdate(QString nStr);
    int width();
    int height();//获取组件高度
    void registerField();
signals:
    void doUpdateSignal(QString nUpStr);
private slots:
    void doUpdateSlot(QString);
private:
    int mWidth;
    int mHeight;
};






class BadPointCalItem : public QObject , public QGraphicsItem , public DataObserver
{
    Q_OBJECT
public:
    enum TextPositionEnum{UPPER_LEFT,LOWER_LEFT,UPPER_RIGHT,LOWER_RIGHT};//文本位置
    BadPointCalItem(QObject *parent = 0);
    ~BadPointCalItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void doUpdate(QString nStr);
    void setItemPos(int x, int y);
    int width();
    int height();
    void registerField();
protected:
    void keyPressEvent(QKeyEvent *ke);//按键按下事件
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
signals:
    void doUpdateSignal(QString nUpStr);
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void doUpdateSlot(QString);
private:
    void textPosition();
    int mWidth;
    int mHeight;
    int mPosX;
    int mPosY;
    TextPositionEnum mTextPosition;
    SatData *mSatData;
};



















class CollectDataItem : public QObject , public QGraphicsItem , public DataObserver
{
    Q_OBJECT
public:
    CollectDataItem(int nID, QObject *parent = 0);
    ~CollectDataItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void doUpdate(QString nStr);
    void setItemPos(int x, int y);
    int width();
    int height();
    void registerField();
protected:
    void keyPressEvent(QKeyEvent *ke);//按键按下事件
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
signals:
    void doUpdateSignal(QString nUpStr);
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void doUpdateSlot(QString nUpStr);
private:
    int mWidth;
    int mHeight;
    int mTextHeight;
    int mPosX;
    int mPosY;
    int mID;
    SatData *mSatData;
};




class SchemaItem :  public QObject , public QGraphicsItem , public DataObserver
{
    Q_OBJECT
public:
    SchemaItem(QObject *parent = 0);
    SchemaItem(int nWidth,int nHeight,QObject *parent = 0);
    void doUpdate(QString nStr);
    void registerField();
    int width();
    int height();
    void setWidth(int nWidth);
    void setHeight(int nHeight);
signals:
    void doUpdateSignal(QString nUpStr);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void doUpdateSlot(QString nUpStr);
private:
    int mWidth;
    int mHeight;
    SatData *mSatData;
};


class SatPhotoItem : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    SatPhotoItem(QObject *parent = 0);
    SatPhotoItem(int nWidth,int nHeight,QObject *parent = 0);
    int getWidth();
    int getHeight();
    void setWidth(int nWidth);
    void setHeight(int nHeight);
    int getPhotoWidth();
    int getPhotoHeight();
    void setPhotoWidth(int nPhotoWidth);
    void setPhotoHeight(int nPhotoHeight);
    bool isTextShowSign();
    void setTextShowSign(bool nTextShowSign);
    QString getTextString();
    void setTextString(QString nTextString);
    QString getPhotoFilename();
    void setPhotoFilename(QString nPhotoFilename);
signals:
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
private:
    bool mTextShowSign;
    int mWidth;
    int mHeight;
    int mPhotoWidth;
    int mPhotoHeight;
    QString mTextString;
    QString mPhotoFilename;
};





class SatPoleItem : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    enum PoleType{
        MaxPole,
        MinPole
    };
    SatPoleItem(PoleType nPoleType,QObject *parent = 0);
    int getWidth();
    int getHeight();
    void setWidth(int nWidth);
    void setHeight(int nHeight);
    void setItemPos(int x,int y);
signals:
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
private:
    int mWidth;
    int mHeight;
    int mPosX;
    int mPosY;
    PoleType mPoleType;
};








#endif // SOLIDBAR_H
