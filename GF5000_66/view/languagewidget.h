#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QScrollBar>
#include <QScrollArea>
#include "view/smallwidget.h"

//语言列表窗口
class SatLanguageListWidget : public QWidget
{
    Q_OBJECT
public:
    SatLanguageListWidget(QWidget *parent = 0);
    QString getLanguage();//获取当前索引的语言
signals:
    void focusTransferSignal();//焦点转移信号，由父窗口决定焦点转移到哪个窗口
protected:
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);//焦点进入事件
    void paintEvent(QPaintEvent *event);//绘制事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件
    bool eventFilter(QObject *nObject, QEvent *event);//事件过滤
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//索引校准
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};

//语言操作面板
class SatLanguagePage : public QWidget
{
    Q_OBJECT
public:
    SatLanguagePage(QWidget *parent = 0);
signals:
    void goBackSignal();//退出信号，由父窗口执行关闭窗口操作
    void focusTransferSignal();//焦点转移信号，至于转移到哪个窗口，由父窗口决定
    void loadLanguageSignal();//加载语言信号，该窗口中加载按键被点击，由父窗口执行具体操作
protected:
    void showEvent(QShowEvent *event);
    void focusInEvent(QFocusEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
    void handleContent(const QString &nStr);
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};

//语言列表的滑动区域
class SatLanguageScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    SatLanguageScrollArea(QWidget *parent = 0);
signals:
public slots:
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    void calcRoll();//调整区域的显示项，让拥有焦点的项一直显示
private:
    bool mIsStartMove;
    QPoint mOldPoint;
    bool mIsContinueMove;

};

//语言设置窗口
class LanguageWidget : public QWidget
{
    Q_OBJECT
public:
    LanguageWidget(QWidget *parent = 0);
signals:
public slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void goBackSlot();
    void loadLanguageSlot();
protected:
    void keyReleaseEvent(QKeyEvent *event);
private:
    SatLanguageScrollArea *mLeftWidget;
    SatLanguagePage *mRightWidget;
    SatTitleBar *mSatTitleBar;

};

#endif // LANGUAGEWIDGET_H
