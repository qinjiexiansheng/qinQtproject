#ifndef LITTLEWIDGET_H
#define LITTLEWIDGET_H
#include <QPushButton>
#include "interface.h"
#include <QLineEdit>
#include <QStyle>
#include <QPainter>
#include <QFont>
#include <QFile>
#include "macrodefine.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QScrollBar>
#include <QScrollArea>
#include <QKeyEvent>
#include <QWidget>
/*===============================================================================
  @classname     xx
  @describe      xx
  @author        Helin
  @date          2018-06-08
  ===============================================================================*/
class SatButton : public QPushButton , public HighLight
{
    Q_OBJECT
    Q_PROPERTY(bool highLight READ isHighLight WRITE setHighLight)
    Q_PROPERTY(bool pixelSize READ getPixelSize WRITE setPixelSize)
    Q_PROPERTY(QString arrowPath READ getArrowPath WRITE setArrowPath)
    Q_PROPERTY(QColor fontColor READ getFontColor WRITE setFontColor)
    Q_PROPERTY(bool onState READ isOnState WRITE setOnState)
    Q_PROPERTY(QString onPath READ getOnPath WRITE setOnPath)
    Q_PROPERTY(QString offPath READ getOffPath WRITE setOffPath)
public:
    enum ButtonType{
        NormalButton,//正常按钮（跟QPushButton一样，只是多了高亮）
        TextLeftButton,//文本左对齐按钮（与正常按钮用样式左对齐差不多，但左边的留空跟下面的一致）
        ArrowButton,//箭头按钮
        PictureSwitchButton,//图片开关按钮
        TextSwitchButton,//文本开关按钮
        TextArrowButton,//文本箭头按钮
        RadioTickButton//单选打钩按钮,mArrowPath存储图标勾的路径
    };
    SatButton(QWidget *parent = 0);
    SatButton(ButtonType nType,QWidget *parent = 0);
    SatButton(const QString &nText,QWidget *parent = 0);
    SatButton(const QString &nText,ButtonType nType,QWidget *parent = 0);
    void setHighLight(bool nHighLight);
    bool isHighLight();
    void setPixelSize(int nPixelSize);
    int getPixelSize();
    void setText(const QString &nText);
    QString getText();
    void setArrowPath(QString nArrowPath);
    QString getArrowPath();
    void setFontColor(const QColor &nFontColor);
    QColor getFontColor();
    void setOnState(bool nOnState);
    bool isOnState();
    void setOnPath(QString nOnPath);
    QString getOnPath();
    void setOffPath(QString nOffPath);
    QString getOffPath();
    void setSelect(bool nIsSelect);
    bool getSelect();
    ButtonType getType();
public slots:

protected:
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
    bool event(QEvent *event);
private slots:
    void switchOnState();
private:
    void initWidget();
    ButtonType mType;
    bool mHighLight;//高亮
    int mPixelSize;
    QColor mFontColor;
    QString mText;
    QString mArrowPath;
    bool mOnState;//当前开关状态
    QString mOnPath;
    QString mOffPath;
    bool mIsSelect;
};



/*===============================================================================
  @classname     xx
  @describe      xx
  @author        Helin
  @date          2018-06-08
  ===============================================================================*/
class SatLineEdit : public QLineEdit , public HighLight
{
    Q_OBJECT
    Q_PROPERTY(bool highLight READ isHighLight WRITE setHighLight DESIGNABLE true)
public:
    SatLineEdit(QWidget *parent = 0);
    void setHighLight(bool nHighLight);
    bool isHighLight();
protected:
    void focusInEvent(QFocusEvent *event);
private:
    bool mHighLight;
};

class SatPhotoButton;
class SatTitleBar : public QWidget
{
    Q_OBJECT
public:
    SatTitleBar(QWidget *parent = 0);
    SatTitleBar(QString nTitle,QWidget *parent = 0);
    void setTitle(QString nTitle);
    QString getTitle();
signals:
    void returnButtonClick();
private:
    void initWidget();
    QString mTitle;
    SatPhotoButton *mReturnButton;
    QLabel *mTitleLabel;
};



class SatScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    SatScrollArea(QWidget *parent = 0);
    void calcRoll();
signals:
public slots:
protected:
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
    bool event(QEvent *event);
private:

private:
    bool mIsStartMove;
    QPoint mOldPoint;
    bool mIsContinueMove;
};



//图片按钮
class SatPhotoButton : public QPushButton
{
    Q_OBJECT
public:
    SatPhotoButton(QWidget *parent = 0);
    QString getTextStr();
    void setTextStr(QString nTextStr);
    bool isTextShowSign();
    void setTextShowSign(bool nTextShowSign);
    QString getNormalPhotoStr();
    void setNormalPhotoStr(QString nNormalPhotoStr);
    QString getFocusPhotoStr();
    void setFocusPhotoStr(QString nFocusPhotoStr);

    bool isTwoState();
    void setTwoState(bool nTwoState);

    QString getTwoNormalPhotoStr();
    void setTwoNormalPhotoStr(QString nTwoNormalPhotoStr);
    QString getTwoFocusPhotoStr();
    void setTwoFocusPhotoStr(QString nTwoFocusPhotoStr);


protected:
    void paintEvent(QPaintEvent *event);
private:

    bool mTwoState;

    bool mTextShowSign;
    QString mTextStr;
    QString mNormalPhotoStr;
    QString mFocusPhotoStr;

    QString mTwoNormalPhotoStr;
    QString mTwoFocusPhotoStr;

};

//高亮图片按钮
class SatPhotoHighLightButton : public QPushButton , public HighLight
{
    Q_OBJECT
public:
    SatPhotoHighLightButton(QWidget *parent = 0);
    void setHighLight(bool nHighLight);
    bool isHighLight();
    void setTextShowSign(bool nTextShowSign);
    bool isTextShowSign();
    void setTextString(QString nTextString);
    QString getTextString();
    void setFocusFilename(QString nFocusFilename);
    QString getFocusFilename();
    void setNormalFilename(QString nNormalFilename);
    QString getNormalFilename();
    void setHighLightFilename(QString nHighLightFilename);
    QString getHighLightFilename();
protected:
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    bool mHighLight;
    bool mTextShowSign;
    QString mTextString;
    QString mFocusFilename;
    QString mNormalFilename;
    QString mHighLightFilename;
};



#endif // LITTLEWIDGET_H
