#include "solidbar.h"
#include "lib/tircolor.h"
#define TrigoHeight 17 /*顶部三角形的高度*/
#define TrigoWidth  25 /*顶部三角形的宽度*/
SolidBar::SolidBar(QObject *parent) : QObject(parent)
{
    mHeight = 440;
    mWidth  = 100;
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
}

void SolidBar::registerField(){
    SatData* nSatData = SatData::initance();//注册观察字段获取数据类
    QList<QString> nList;
    nList.append("MaxTemp");
    nList.append("MinTemp");
    nList.append("InfraredMode");
    nList.append("OrangeTemp");
    nList.append("RedTemp");
    nList.append("CenterTemp");
    nList.append("TempUnit");
    nSatData->attach(this,nList);
}

QRectF SolidBar::boundingRect() const{
    return QRectF(0,0,mWidth,mHeight);

}

void SolidBar::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing,true);//启用反走样
    SatData* nSatData = SatData::initance();//获取数据类
    float nMaxTemp = nSatData->getMaxTemp();//获取最大温度
    float nMinTemp = nSatData->getMinTemp();//获取最小温度
    SatData::InfraredEnum nInfrared = nSatData->getInfraredMode();//获取红外模式
    float nOrangeTemp = nSatData->getOrangeTemp();//获取橙色温度
    float nRedTemp = nSatData->getRedTemp();//获取红色温度
    float nCenterTemp = nSatData->getCenterTemp();//获取中心点温度


    if(!nSatData->getTempUnit()){
        nMaxTemp = nMaxTemp*1.8 + 32;
        nMinTemp = nMinTemp*1.8 + 32;
        nOrangeTemp = nOrangeTemp*1.8 + 32;
        nRedTemp = nRedTemp*1.8 + 32;
        nCenterTemp = nCenterTemp*1.8 + 32;
    }


    int nRBarWidth;//参考杆宽度
    int nRBarHeight;//参考杆高度
    int x,y;
    QPen nPen;
    QFont nFont;
    QPixmap nBgPixmap;//温度显示的背景图
    QString nPixStr = QString("%1back.png").arg(IMG_DIR);
    nBgPixmap.load(nPixStr);//温度显示背景图加载
    QPointF nPoints[3];//用来存储三角形三个点的坐标
    nPoints[0] = QPointF(mWidth - TrigoWidth - 1 , TrigoHeight);//三角形的左下角
    nPoints[1] = QPointF(mWidth , TrigoHeight);//三角形的右下角
    nPoints[2] = QPointF(mWidth - TrigoWidth/2 - 1 , 0);//三角形的顶点
    //绘制三角形
    nPen.setColor(QColor(0,187,18));
    painter->setPen(nPen);//笔的颜色为绿色
    painter->setBrush(QColor(0,187,18));//笔刷的颜色为绿色
    painter->drawPolygon(nPoints, 3);//绘制三角形
    nRBarWidth = 15;//参考杆宽度
    nRBarHeight = mHeight-nBgPixmap.height()-TrigoHeight;//计算参考杆高度
    int nRBarX1 = mWidth-(TrigoWidth-nRBarWidth)/2-nRBarWidth;//参考杆左上角x坐标
    float nRBarY  = TrigoHeight + 2;//参考杆左上角y坐标
    int nRBarX2 = nRBarX1 + nRBarWidth;//参考杆右上角的x坐标
    float nSpace = nRBarHeight*1.0/256;//256种颜色的间隔
    //绘制伪彩条
    nPen.setWidth(nSpace+1);//设置笔的宽度----加1后变成向上取整
    int i;
    for(i = 255; i >= 0; i--){//从伪彩条的顶部开始绘制,所以从伪彩色表的尾部开始取颜色
        int nColor;
        if(nInfrared == SatData::GREY){//白热模式
            nColor = GREY[i];
        }else if(nInfrared == SatData::GREYINV){//黑热模式
            nColor = GREYINV[i];
        }else if(nInfrared == SatData::IRON){
            nColor = IRON[i];
        }else if(nInfrared == SatData::IRONINV){
            nColor = IRONINV[i];
        }else if(nInfrared == SatData::RAINBOW){
            nColor = RAINBOW[i];
        }else if(nInfrared == SatData::FEATHER){
            nColor = FEATHER[i];
        }else{
            nColor = GREY[i];
        }
        nPen.setColor(QColor(nColor));
        painter->setPen(nPen);
        painter->drawLine(nRBarX1,nRBarY,nRBarX2,nRBarY);//绘制颜色
        nRBarY += nSpace;
    }
    //计算温度实杆参数
    int nLBarX2 = nRBarX1 - 1;//温度条右上角的x坐标
    int nLBarX1 = nLBarX2-nRBarWidth-1;//温度条左上角的x坐标
    int nLBarY  = TrigoHeight + 1 + nRBarHeight;//温度条底部y坐标
    int nLBarH;//温度条的实际高度
    if(nCenterTemp > nMaxTemp){
        nLBarH = nRBarHeight;//当前温度值大于最高指标时,温度条高度为伪彩条高度
    }else if(nCenterTemp < nMinTemp){
        nLBarH = 0;
    }else{
        nLBarH = nRBarHeight*((nCenterTemp-nMinTemp)*1.0/(nMaxTemp-nMinTemp));//温度条的高度(当前值/最大值*伪彩条的高度)
    }
    float index,nRedIndex = 0,nOrangeIndex = 0;
    QLinearGradient nLinear = QLinearGradient(nLBarX1,TrigoHeight+2,nLBarX1,nLBarY);//温度条的渐变
    nLinear.setColorAt(0,QColor(139,0,0,255));//设置顶端的渐变颜色-深红色
    nLinear.setColorAt(1,QColor(255,255,102,255));//设置低端的渐变颜色-浅黄色
    if(nRedTemp >= nMaxTemp){
        nRedIndex = 0;
    }
    if(nOrangeTemp >= nMaxTemp){
        nOrangeIndex = 0;
    }
    if(nOrangeTemp <= nMinTemp){
        nOrangeIndex = 1;
    }
    if(nRedTemp <= nMinTemp){
        nRedIndex = 1;
    }
    if((nRedTemp < nMaxTemp) && (nRedTemp > nMinTemp)){
        index = 1-((nRedTemp-nMinTemp)*1.0/(nMaxTemp-nMinTemp));
        if(index < 0){index = 0;}
        if(index > 1){index = 1;}
        nRedIndex = index;
    }
    if((nOrangeTemp < nMaxTemp) && (nOrangeTemp > nMinTemp)){
        index = 1-((nOrangeTemp-nMinTemp)*1.0/(nMaxTemp-nMinTemp));
        if(index < 0){index = 0;}
        if(index > 1){index = 1;}
        nOrangeIndex = index;
    }
    nLinear.setColorAt(nOrangeIndex,QColor(255,165,0,255));//设置中端的渐变颜色-橙色
    nLinear.setColorAt(nRedIndex,QColor(255,69,0,255));//设置高端的渐变颜色-红色
    //绘制温度实杆
    painter->setPen(Qt::NoPen);//不要笔
    painter->setBrush(nLinear);
    painter->drawRect(nLBarX1,nLBarY-nLBarH-1,nLBarX2-nLBarX1,nLBarH);//绘制温度条
    //绘制温度刻度
    nFont.setPointSize(18);//设置字体大小
    painter->setFont(nFont);
    painter->setPen(QColor(0,187,18));//笔的颜色为绿
    int nScaleWidth = nRBarWidth/2+3;//设置刻度的宽度为彩条的一半(向下取整),修正3个像素,大刻度为小刻度的2倍
    for(int i = 1;i <= 9; i++){//将伪彩条划分为10部分,绘制9条刻度线(底部和顶部的线不绘制)
        float value = (nMaxTemp-nMinTemp)*(i*0.1)+nMinTemp;//将最大值划分,分别为:10%,20%...
        if(i == 3 || i == 5 || i == 8){//在30%,50%,80%的位置绘制大刻度
            x = nRBarX1-nScaleWidth*2;//刻度线的左端的x坐标(伪彩条的左上角x坐标-大刻度宽度)
            y = mHeight-nBgPixmap.height()-nRBarHeight*i*1.0/10.0;//20180208-15:31
            painter->drawLine(x,y,nRBarX1-2,y);//绘制刻度线
            painter->drawText(0,y-10,60,20,Qt::AlignCenter,QString("%1").arg(QString::number(value, 'f', 1)));//大刻度绘制数值
        }else{//小刻度绘制(除了刻度宽度和不用绘制数值,其他与大刻度一样)
            x = nRBarX1-nScaleWidth;
            y = mHeight-nBgPixmap.height()-nRBarHeight*i*1.0/10.0;//20180208-15:31
            painter->drawLine(x,y,nRBarX1-2,y);//绘制刻度线
        }
    }

    x = mWidth - nBgPixmap.width();//背景图的x坐标
    y = mHeight - nBgPixmap.height();//背景图的y坐标
    painter->drawPixmap(x,y,nBgPixmap);
    //绘制温度数值
    nFont.setPointSize(18);//设置温度字体大小------
    nFont.setBold(true);//加粗字体
    painter->setFont(nFont);
    painter->setPen(QColor(0,187,18));//设置温度数值颜色为绿色℃
    x = mWidth - nBgPixmap.width();//背景图的x坐标
    y = mHeight - nBgPixmap.height();//背景图的y坐标
    if(nSatData->getTempUnit()){
        painter->drawText(x,y,nBgPixmap.width(),nBgPixmap.height(),
                          Qt::AlignCenter,tr("%1°C").arg(QString::number(nCenterTemp, 'f', 1)));//绘制当前温度数值
    }else{
        painter->drawText(x,y,nBgPixmap.width(),nBgPixmap.height(),
                          Qt::AlignCenter,tr("%1°F").arg(QString::number(nCenterTemp, 'f', 1)));//绘制当前温度数值
    }

}

void SolidBar::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}


int SolidBar::width(){
    return mWidth;
}

int SolidBar::height(){
    return mHeight;
}

void SolidBar::doUpdateSlot(QString /*nUpStr*/){
    update();
}














































BadPointCalItem::BadPointCalItem(QObject *parent) : QObject(parent)
{
    mHeight = 150;
    mWidth  = 150;
    mPosX = 320;
    mPosY = 240;
    mTextPosition = LOWER_RIGHT;//初始文本位置：右下角
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    setFlag(QGraphicsItem::ItemIsFocusable);
    //注册观察字段
    mSatData = SatData::initance();//获取数据类
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

void BadPointCalItem::registerField(){
    QList<QString> nList;
    nList.append("CalBadPointAD");
    nList.append("CalBadPointState");
    mSatData->attach(this,nList);
}


BadPointCalItem::~BadPointCalItem(){
}
QRectF BadPointCalItem::boundingRect() const{//返回可绘制的范围
    return QRectF(0,0,mWidth,mHeight);
}
void BadPointCalItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing,true);//启用反走样
    QPen nPen;
    nPen.setWidth(2);//画笔宽度
    nPen.setColor(QColor(255,255,255));//画笔颜色
    painter->setPen(nPen);
    int nCenterX = mWidth/2;
    int nCenterY = mHeight/2;
    painter->drawPoint(nCenterX,nCenterY);//绘制中心点
    int nLineLength = 50;//线的长度
    int nInterval = 15;//线距离中心点的距离
    nPen.setWidth(6);//画笔宽度
    painter->setPen(nPen);
    //左边的线
    int nLineX = nCenterX - nInterval - nLineLength;
    int nLineY = nCenterY;
    painter->drawLine(nLineX,nLineY,nLineX+nLineLength,nLineY);
    //右边的线
    nLineX = nCenterX + nInterval;
    nLineY = nCenterY;
    painter->drawLine(nLineX,nLineY,nLineX+nLineLength,nLineY);
    //上边的线
    nLineX = nCenterX;
    nLineY = nCenterY - nInterval - nLineLength;
    painter->drawLine(nLineX,nLineY,nLineX,nLineY+nLineLength);
    //下边的线
    nLineX = nCenterX;
    nLineY = nCenterY + nInterval;
    painter->drawLine(nLineX,nLineY,nLineX,nLineY+nLineLength);
    QFont nFont;
    nFont.setPixelSize(15);//字体大小
    painter->setFont(nFont);
    nPen.setWidth(1);//画笔宽度
    painter->setPen(nPen);
    QString nStr = QString("%1\n%2\n(%3,%4)")
            .arg(mSatData->getCalBadPointState() ? "Yes" : "No")
            .arg(mSatData->getCalBadPointAD(),4,16,QLatin1Char('0'))
            .arg(mPosX).arg(mPosY);//绘制的文本内容
    int nTextWidth = 70;
    int nTextHeight = 70;
    if(mTextPosition == UPPER_RIGHT){
        painter->drawText(nCenterX + nInterval/2,nCenterY - nInterval/2 - nTextHeight,nTextWidth,nTextHeight,Qt::AlignLeft,nStr);
    }else if(mTextPosition == LOWER_LEFT){
        painter->drawText(nCenterX - nInterval/2 -nTextWidth,nCenterY + nInterval/2,nTextWidth,nTextHeight,Qt::AlignRight,nStr);
    }else if(mTextPosition == UPPER_LEFT){
        painter->drawText(nCenterX - nInterval/2 -nTextHeight,nCenterY - nInterval/2 - nTextWidth,nTextWidth,nTextHeight,Qt::AlignRight,nStr);
    }else{
        painter->drawText(nCenterX + nInterval/2,nCenterY + nInterval/2,nTextWidth,nTextHeight,Qt::AlignLeft,nStr);
    }
}
void BadPointCalItem::setItemPos(int x, int y){//设置项的坐标，传入的坐标是中心点的位置
    mPosX = x;
    mPosY = y;
    textPosition();//改变文本显示的方位
    emit operationSignal(BadPoint_SetPos,QString("X=%1;Y=%2").arg(mPosX).arg(mPosY));
    this->setPos(mPosX - mWidth/2,mPosY - mHeight/2);
    //emit operationSignal(BadPoint_Query,NULL);
}
void BadPointCalItem::keyPressEvent(QKeyEvent *ke){
    switch (ke->key()) {
        case KEY_19://上移
            {
                mPosY--;
                if(mPosY < 0){
                    mPosY = 0;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_20://下移
            {
                mPosY++;
                if(mPosY > SCREEN_HEIGHT - 1){
                    mPosY = SCREEN_HEIGHT - 1;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_21://左移
            {
                mPosX--;
                if(mPosX < 0){
                    mPosX = 0;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_22://右移
            {
                mPosX++;
                if(mPosX > SCREEN_WIDTH - 1){
                    mPosX = SCREEN_WIDTH - 1;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_18://校坏点操作
            {
                emit operationSignal(BadPoint_Cal,NULL);
            }
            break;
        case KEY_25://25号键来退出校坏点模式
            {
                emit operationSignal(Save_KTable,NULL);
                emit operationSignal(Set_Window_Normal,NULL);
                this->clearFocus();
            }
            break;
        default://其他按键不拦截
            QGraphicsItem::keyPressEvent(ke);
            break;
    }
}
void BadPointCalItem::focusInEvent(QFocusEvent *event){//得到焦点事件
    update();
    this->setZValue(10);
    QGraphicsItem::focusInEvent(event);
}
void BadPointCalItem::focusOutEvent(QFocusEvent *event){
    update();
    this->setZValue(0);
    QGraphicsItem::focusOutEvent(event);
}
void BadPointCalItem::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}
int BadPointCalItem::width(){
    return mWidth;
}
int BadPointCalItem::height(){
    return mHeight;
}
void BadPointCalItem::textPosition(){//改变文本内容显示方位（原则：需要改变时才改变，不需要变时则不变，避免不必要的变化）
    if(mPosX < mWidth/2){//当X坐标过小时，那么文本方向在右边
        if(mPosY < mHeight/2){//如果Y坐标过小，文本方向为右下
            mTextPosition = LOWER_RIGHT;
        }else if(mPosY > SCREEN_HEIGHT - mHeight/2){//Y坐标过大时，文本方向为右上
            mTextPosition = UPPER_RIGHT;
        }else if(mTextPosition == UPPER_LEFT || mTextPosition == LOWER_LEFT){//当Y坐标适中，则如果原本是左边的，需要设为右下
            mTextPosition = LOWER_RIGHT;
        }
    }else if(mPosX > SCREEN_WIDTH - mWidth/2){//原理同上
        if(mPosY < mHeight/2){
            mTextPosition = LOWER_LEFT;
        }else if(mPosY > SCREEN_HEIGHT - mHeight/2){
            mTextPosition = UPPER_LEFT;
        }else if(mTextPosition == UPPER_RIGHT || mTextPosition == LOWER_RIGHT){
            mTextPosition = LOWER_LEFT;
        }
    }else{//如果X坐标适中，原理同上
        if(mPosY < mHeight/2 && (mTextPosition == UPPER_LEFT || mTextPosition == UPPER_RIGHT)){
            mTextPosition = LOWER_RIGHT;
        }else if(mPosY > SCREEN_HEIGHT - mHeight/2 && (mTextPosition == LOWER_LEFT || mTextPosition == LOWER_RIGHT)){
            mTextPosition = UPPER_RIGHT;
        }
    }
    update();
}


void BadPointCalItem::doUpdateSlot(QString /*nUpStr*/){
    update();
}














































CollectDataItem::CollectDataItem(int nID, QObject *parent) : QObject(parent)
{
    mID = nID;//采集数据的区域框的编号
    mHeight = 70;//图片的高度，不包括文本显示
    mWidth = 70;//图片的宽度，不包括文本显示
    mTextHeight = 80;//底部文本显示高度
    mPosX = 320;//图片中心点的X坐标
    mPosY = 240;//图片中心点的Y坐标
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    setFlag(QGraphicsItem::ItemIsFocusable);//设置了该项可以拥有焦点
    //注册观察字段
    mSatData = SatData::initance();//获取数据类
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}


CollectDataItem::~CollectDataItem(){//析构函数
    //mSatData->unattach(this);
}


void CollectDataItem::registerField(){
    QList<QString> nList;
    nList.append("Sensor");
    nList.append("Det");
    if(mID == 1){
        nList.append("CollectDataItemAD1");
    }else{
        nList.append("CollectDataItemAD2");
    }
    mSatData->attach(this,nList);
}

QRectF CollectDataItem::boundingRect() const{//项的区域，是可绘制的区域范围
    return QRectF(0,0,mWidth,mHeight+mTextHeight);//加上底部文本显示的高度
}

void CollectDataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);//启用反走样
    QPixmap nBgPixmap;//温度显示的背景图
    QString nStr;
    if(this->hasFocus()){//根据是否拥有焦点来选择加载不同的图片
        nStr = QString("%1%2").arg(IMG_DIR).arg("mid2-2px.png");
    }else{
        nStr = QString("%1%2").arg(IMG_DIR).arg("mid2.png");
    }
    nBgPixmap.load(nStr);//温度显示背景图加载
    nBgPixmap = nBgPixmap.scaled(mWidth,mHeight);//放大图片
    painter->drawPixmap(0,0,nBgPixmap);
    if(mID == 1){
        nStr = QString("AD1:%1\nT:%2\nDet:%3")
                .arg(mSatData->getCollectDataItemAD1(),4,16,QLatin1Char('0'))
                .arg(mSatData->getSensor())
                .arg(mSatData->getDet(),4,16,QLatin1Char('0'));
    }else{
        nStr = QString("AD2:%1\nT:%2\nDet:%3")
                .arg(mSatData->getCollectDataItemAD2(),4,16,QLatin1Char('0'))
                .arg(mSatData->getSensor())
                .arg(mSatData->getDet(),4,16,QLatin1Char('0'));
    }
    QFont nFont;
    nFont.setPixelSize(15);//字体大小
    painter->setFont(nFont);
    QPen nPen;
    nPen.setColor(QColor(255,255,255));//画笔颜色
    painter->setPen(nPen);
    painter->drawText(0,mHeight,mWidth,mTextHeight,Qt::AlignLeft,nStr);
}

void CollectDataItem::setItemPos(int x, int y){//设置该项的位置，这个位置是指图片中心点所在的位置
    mPosX = x;
    mPosY = y;
    if(mID == 1){
        emit operationSignal(Collect1_SetPos,QString("X=%1;Y=%2").arg(mPosX).arg(mPosY));
    }else{
        emit operationSignal(Collect2_SetPos,QString("X=%1;Y=%2").arg(mPosX).arg(mPosY));
    }
    this->setPos(mPosX - mWidth/2,mPosY - mHeight/2);
}
void CollectDataItem::keyPressEvent(QKeyEvent *ke){
    switch (ke->key()) {
        case KEY_19://19号键上移
            {
                mPosY--;
                if(mPosY < 0){
                    mPosY = 0;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_20://20号键下移
            {
                mPosY++;
                if(mPosY > SCREEN_HEIGHT - 1){
                    mPosY = SCREEN_HEIGHT - 1;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_21://21号键左移
            {
                mPosX--;
                if(mPosX < 0){
                    mPosX = 0;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        case KEY_22://22号键右移
            {
                mPosX++;
                if(mPosX > SCREEN_WIDTH - 1){
                    mPosX = SCREEN_WIDTH - 1;
                }
                setItemPos(mPosX,mPosY);
            }
            break;
        default://其他按键不拦截
            QGraphicsItem::keyPressEvent(ke);
            break;
    }
}
void CollectDataItem::focusInEvent(QFocusEvent *event){//得到焦点事件
    update();
    this->setZValue(10);
    QGraphicsItem::focusInEvent(event);
}
void CollectDataItem::focusOutEvent(QFocusEvent *event){
    update();
    this->setZValue(0);
    QGraphicsItem::focusOutEvent(event);
}
void CollectDataItem::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}
int CollectDataItem::width(){
    return mWidth;
}
int CollectDataItem::height(){
    return mHeight;
}
void CollectDataItem::doUpdateSlot(QString /*nUpStr*/){
    update();
}






SchemaItem::SchemaItem(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
    mWidth = 35;
    mHeight = 35;
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
}

SchemaItem::SchemaItem(int nWidth, int nHeight, QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
    mWidth = nWidth;
    mHeight = nHeight;
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
}

void SchemaItem::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}

void SchemaItem::registerField(){
    mSatData->attach(this,"SchemaIndex");
}

void SchemaItem::doUpdateSlot(QString nUpStr){
    if(nUpStr == "SchemaIndex"){
        update();
    }
}

int SchemaItem::width(){
    return mWidth;
}

int SchemaItem::height(){
    return mHeight;
}

void SchemaItem::setWidth(int nWidth){
    mWidth = nWidth;
    update();
}

void SchemaItem::setHeight(int nHeight){
    mHeight = nHeight;
    update();
}

QRectF SchemaItem::boundingRect() const{
    return QRectF(0,0,mWidth,mHeight);
}

void SchemaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHint(QPainter::Antialiasing);//启用反走样
    QString nStr = mSatData->getCurrentSchema()->imageNormal();
    if(!nStr.isEmpty() && QFile::exists(nStr)){
        QPixmap nPixmap;//温度显示的背景图
        nPixmap.load(nStr);//温度显示背景图加载
        nPixmap = nPixmap.scaled(mWidth,mHeight);//放大图片
        painter->drawPixmap(0,0,nPixmap);
    }
}






















SatPhotoItem::SatPhotoItem(QObject *parent) : QObject(parent){
    mWidth = 35;
    mHeight = 35;
    mTextShowSign = false;
}

SatPhotoItem::SatPhotoItem(int nWidth, int nHeight, QObject *parent) : QObject(parent){
    mWidth = nWidth;
    mHeight = nHeight;
    mTextShowSign = false;
}

int SatPhotoItem::getWidth(){
    return mWidth;
}

int SatPhotoItem::getHeight(){
    return mHeight;
}

void SatPhotoItem::setWidth(int nWidth){
    if(mWidth != nWidth){
        mWidth = nWidth;
        update();
    }
}

void SatPhotoItem::setHeight(int nHeight){
    if(mHeight != nHeight){
        mHeight = nHeight;
        update();
    }
}

int SatPhotoItem::getPhotoWidth(){
    return mPhotoWidth;
}

int SatPhotoItem::getPhotoHeight(){
    return mPhotoHeight;
}

void SatPhotoItem::setPhotoWidth(int nPhotoWidth){
    if(mPhotoWidth != nPhotoWidth){
        mPhotoWidth = nPhotoWidth;
        update();
    }
}

void SatPhotoItem::setPhotoHeight(int nPhotoHeight){
    if(mPhotoHeight != nPhotoHeight){
        mPhotoHeight = nPhotoHeight;
        update();
    }
}

bool SatPhotoItem::isTextShowSign(){
    return mTextShowSign;
}

void SatPhotoItem::setTextShowSign(bool nTextShowSign){
    if(mTextShowSign != nTextShowSign){
        mTextShowSign = nTextShowSign;
        update();
    }
}

QString SatPhotoItem::getTextString(){
    return mTextString;
}

void SatPhotoItem::setTextString(QString nTextString){
    if(mTextString != nTextString){
        mTextString = nTextString;
        update();
    }
}

QString SatPhotoItem::getPhotoFilename(){
    return mPhotoFilename;
}

void SatPhotoItem::setPhotoFilename(QString nPhotoFilename){
    if(mPhotoFilename != nPhotoFilename){
        mPhotoFilename = nPhotoFilename;
        update();
    }
}

QRectF SatPhotoItem::boundingRect() const{
    return QRectF(0,0,mWidth,mHeight);
}

void SatPhotoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHint(QPainter::Antialiasing);//启用反走样
    if(!mPhotoFilename.isEmpty() && QFile::exists(mPhotoFilename)){
        QPixmap nPixmap;
        nPixmap.load(mPhotoFilename);
        nPixmap = nPixmap.scaled(mPhotoWidth,mPhotoHeight);
        painter->drawPixmap((mWidth-mPhotoWidth)/2,0,nPixmap);
    }
    if(!mTextString.isEmpty() && mTextShowSign){
        painter->drawText(0,mPhotoHeight,mWidth,mHeight-mPhotoHeight,Qt::AlignCenter,mTextString);
    }
}




















SatPoleItem::SatPoleItem(PoleType nPoleType, QObject *parent) : QObject(parent){
    mPoleType = nPoleType;
    mWidth = 35;
    mHeight = 35;
    mPosX = -100;
    mPosY = -100;
}
int SatPoleItem::getWidth(){
    return mWidth;
}

int SatPoleItem::getHeight(){
    return mHeight;
}

void SatPoleItem::setWidth(int nWidth){
    if(mWidth != nWidth){
        mWidth = nWidth;
        update();
    }
}

void SatPoleItem::setHeight(int nHeight){
    if(mHeight != nHeight){
        mHeight = nHeight;
        update();
    }
}

void SatPoleItem::setItemPos(int x,int y){
    mPosX = x - mWidth/2;
    mPosY = y - mHeight/2;
    this->setPos(mPosX,mPosY);
}

QRectF SatPoleItem::boundingRect() const{
    return QRectF(0,0,mWidth,mHeight);
}

void SatPoleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/){
    painter->setRenderHint(QPainter::Antialiasing);//启用反走样
    if(mPoleType == MaxPole){
        QPen nPen;
        nPen.setWidth(2);//画笔宽度
        nPen.setColor(QColor(255,0,0));//画笔颜色
        painter->setPen(nPen);
        painter->drawRect(0,0,mWidth,mHeight);
    }else{
        QPen nPen;
        nPen.setWidth(2);//画笔宽度
        nPen.setColor(QColor(52,133,251));//画笔颜色
        painter->setPen(nPen);
        painter->drawRect(0,0,mWidth,mHeight);
    }
}
