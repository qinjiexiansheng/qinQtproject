#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QThread>
#include "uitls/interface.h"
#include "uitls/operationfield.h"
#include "view/solidbar.h"
#include "uitls/macrodefine.h"
#include "view/tabpage.h"
#include "view/tabdialog.h"
#include "view/softkeyboard.h"
#include "controller/satcontrol.h"
#include "view/modifyadtablewidget.h"
#include "controller/keyscan.h"
#include "view/userwidget.h"

#include "view/systemwidget.h"
#include "view/picturebrowingwidget.h"

#include <QTranslator>

class MainWindow : public QMainWindow , public DataObserver
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);//构造方法
    void doUpdate(QString nUpStr);//观察者注册的字段变化时被调用的方法
    void registerField();//注册监听字段


public slots:
    void keyToEvent(int nKey,bool nPress,bool nRepeat);//按键转发
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
    void doUpdateSignal(QString nUpStr);//监听字段更新
protected:
    void keyPressEvent(QKeyEvent *ke);//按键按下事件
    void keyReleaseEvent(QKeyEvent *ke);//按键释放事件
    void changeEvent(QEvent *event);
private slots:
    void doUpdateSlot(QString nUpStr);//监听字段变化处理槽
    void alarmFlashSlot();//报警图标闪烁槽
    void batFlashSlot();//低电量闪烁槽
    void keyLongPress();//按键长按槽（27号按键）
    void tipsHideSlot();
    void powerOffSlot();
private:
    void operationSelf(int nOpeStr);//业务操作自身过滤
    //void nextSchema();//下一模式
    void initWindow();//初始化窗口
    void showVideo();
    void showPole();
    //void showPoleTemp();
    void showPlus();//显示+模式指示项
    void showLow();//低灵敏度指示项
    void showWarning();//报警项
    void showBattery();//电量项
    void showText();//取景框的信息文本项
    void showCenterItem();
    void showCorrectItem();
    int  mapBattery(float nBattery);//电量到图片索引的映射方法
private:
    SatData* mSatData;
    bool mPowerSignal;
    QTimer *mKeyTimer16;
    QGraphicsPixmapItem *mPlusItem;//plus模式指示项
    QGraphicsPixmapItem *mLowItem;//低灵敏度指示项
    QGraphicsPixmapItem *mWarningItem;//警报指示项
    QGraphicsPixmapItem *mBatteryItem[6];//电量指示项
    QGraphicsPixmapItem *mAreaCenterItem;//中心显示框
    QGraphicsPixmapItem *mSpotCenterItem;//中心显示点
    QGraphicsTextItem *mTextItem;//中心文本项
    SolidBar* mSolidBar;//伪彩条
    BadPointCalItem *mBadPointCalItem;
    CollectDataItem  *mCollectData1Item;
    CollectDataItem  *mCollectData2Item;
    QTimer* mAlarmFlashTimer;//报警闪烁频率定时器
    QTimer* mBatFlashTimer;//低电量闪烁频率定时器
    QTimer* mKeyTimer;//按键长按计时器（27号按键）

    QTimer* mTipsTimer;


    TabDialog* mTabWidget;//标定窗口


    QGraphicsTextItem *mDisTextItem;
    QGraphicsTextItem *mEmissTextItem;
    QGraphicsTextItem *mEnvTmpTextItem;
    QGraphicsTextItem *mRelHumTextItem;

    SchemaItem *mSchemaItem;//模式显示图标
    SatPhotoItem *mVideoItem;//正在录像显示图标

    QGraphicsTextItem *mTipsItem;//文本提示项



    SatMainSmallWidget *mMainSmallWidget;//左侧小窗口


    SatPoleItem *mMaxPoleItem;//最大点
    SatPoleItem *mMinPoleItem;//最小点
    QGraphicsTextItem *mMaxTempItem;//最大温度数值显示项
    QGraphicsTextItem *mMinTempItem;//最小温度数值显示项


    ShutDownWidget *mShutDownWidget;//关机显示面板

};

#endif // MAINWINDOW_H











