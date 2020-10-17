#include "area.h"

#define AREA_DEFWIDTH   50
#define AREA_DEFSIZE    QSize(AREA_DEFWIDTH, AREA_DEFWIDTH)
#define LONGPRESSDURATION   250

/**
 * @name    Area(QWidget *parent, int id)
 * @details Area构造函数。实现区域测温的显示和功能
 * @param   parent  父窗口指针
 * @param   id  标示id
 * @date    2018-12-21
**/
Area::Area(QWidget *parent, int id) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::StrongFocus);
    resize(AREA_DEFSIZE);

    m_id = id;
    isPressed = false;
    singleStep = 1;
    singleStepTemp = singleStep;

    isLeftPressDown = false;
    dir = NONE;
    setMouseTracking(true);
    initProperty();

    propertyWnd = new AreaPropertyWnd(this);

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    updateTempTimer = new QTimer(this);
    connect(updateTempTimer, SIGNAL(timeout()), this, SLOT(updateTempSlot()));

    m_label = new QLabel(parent);
    m_label->setStyleSheet("color: white; background-color: black");
    m_label->setFont(QFont(font().family(), 10));
    m_label->setScaledContents(true);
    m_label->setWindowFlags(Qt::FramelessWindowHint);
    m_label->setAttribute(Qt::WA_DeleteOnClose,true);
    m_label->setAttribute(Qt::WA_TranslucentBackground, true);
    m_label->lower();

    m_maxCursor = new QLabel(parent);
    m_minCursor = new QLabel(parent);
    //    m_avgCursor = new QLabel;

    QImage *img = new QImage;
    float scale = 0.5;

    if(img->load(":/pics/D300/area_max.png")) //加载图像
    {
        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    m_maxCursor->setPixmap(QPixmap::fromImage(*img));
    m_maxCursor->lower();
    m_maxCursor->setFixedSize(img->size());
    m_maxCursor->setMask(QBitmap(QPixmap::fromImage(*img).mask()));

    if(img->load(":/pics/D300/area_min.png")) //加载图像
    {
        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    m_minCursor->setPixmap(QPixmap::fromImage(*img));
    m_minCursor->setFixedSize(img->size());
    m_minCursor->setMask(QBitmap(QPixmap::fromImage(*img).mask()));

    //    if(img->load(":/pics/D300/area_avera.png")) //加载图像
    //    {
    //        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    //    }
    //    m_avgCursor->setPixmap(QPixmap::fromImage(*img));
    //    m_avgCursor->resize(img->width(), img->height());

    m_maxCursor->move(QPoint(geometry().topLeft().x()-m_maxCursor->width()/2,
                             geometry().topLeft().y()-m_maxCursor->height()/2));
    m_minCursor->move(QPoint(geometry().bottomRight().x()-m_minCursor->width()/2,
                             geometry().bottomRight().y()-m_minCursor->height()/2));

    lower();

    //目前右五个区域测温工具，以下为各区域初始位置
    const QPoint AreaPosBuf[MAXAREANUM] = {
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
        QPoint((SCREEN_WIDTH-width())/2, (SCREEN_HEIGHT-height())/2),
    };

    move(AreaPosBuf[m_id]);
}

/**
 * @name    void Area::move(int x, int y)
 * @details 重写move函数，移动式限制x，y的范围，并刷新温度
 * @param   x   横坐标
 * @param   y   纵坐标
 * @author  lee
 * @date    2018-12-21
**/
void Area::move(int x, int y)
{
    x = (x < 0 ? 0 : x);
    x = (x > SCREEN_WIDTH-width() ? SCREEN_WIDTH-width() : x);
    y = (y < 0 ? 0 : y);
    y = (y > SCREEN_HEIGHT-height() ? SCREEN_HEIGHT-height() : y);

    QWidget::move(x, y);
    updateTempSlot();
}

/**
 * @name    inline void move(QPoint point)
 * @details 重写move(QPoint point)，调用move(int x, int y)
 * @param   point   坐标点
 * @author  lee
 * @date    2018-12-21
**/
inline void Area::move(QPoint point)
{
    move(point.x(), point.y());
}

/**
 * @name    void show()
 * @details 重写show函数，调用setDisplay
 * @author  lee
 * @date    2018-12-20
**/
void Area::show()
{
    setDisplay(1);
}

/**
 * @name    void hide()
 * @details 重写hide函数，调用setDisplay
 * @author  lee
 * @date    2018-12-20
**/
void Area::hide()
{
    setDisplay(0);
}

/**
 * @name    void close()
 * @details 重写close函数，关闭Area，也关闭温度显示label
 * @author  lee
 * @date    2018-12-20
**/
void Area::close()
{
    m_label->close();
    QWidget::close();
}

/**
 * @name    inline void setGeometry(int x, int y, int w, int h)
 * @details 重写setGeometry(int x, int y, int w, int h)函数，调用setGeometry(const QRect &rect)
 * @param   x   横坐标
 * @param   y   纵坐标
 * @param   w   宽度
 * @param   h   高度
 * @author  lee
 * @date    2018-12-20
**/
inline void Area::setGeometry(int x, int y, int w, int h)
{
    setGeometry(QRect(x, y, w, h));
}

/**
 * @name    void setGeometry(const QRect &rect)
 * @details 重写setGeometry(const QRect &rect)，限制Area的起始座位和宽度、高度,并刷新温度
 * @param   rect   矩形 区域
 * @author  lee
 * @date    2018-12-20
**/
void Area::setGeometry(const QRect &rect)
{
    QRect rectTemp = rect;
    rectTemp.setX(rect.x() < 0 ? 0 : rect.x());
    rectTemp.setY(rect.y() < 0 ? 0 : rect.y());
    rectTemp.setWidth(rectTemp.x() + rectTemp.width() > SCREEN_WIDTH ? SCREEN_WIDTH-rectTemp.x() : rectTemp.width());
    rectTemp.setHeight(rectTemp.y() + rectTemp.height() > SCREEN_HEIGHT ? SCREEN_HEIGHT-rectTemp.y() : rectTemp.height());

    QWidget::setGeometry(rectTemp);
    updateTempSlot();
}

/**
 * @name    int id()
 * @details 返回Area的标示id
 * @return  Area的标示id
 * @author  lee
 * @date    2018-12-20
**/
int Area::id()
{
    return m_id;
}

/**
 * @name    AreaTemp Area::getTemp()
 * @details 返回Area的温度
 * @return  Area的温度
 * @author  lee
 * @date    2018-12-20
**/
AreaTemp Area::getTemp()
{
    return m_areaTemp;
}

/**
 * @name    void initProperty()
 * @details 初始化Area的属性值
 * @author  lee
 * @date    2018-12-20
**/
void Area::initProperty()
{
    m_property.displayMode = 1;
    m_property.maxShowMode = 1;
    m_property.minShowMode = 1;
    m_property.avgShowMode = 1;
    m_property_temp = m_property;
}

/**
 * @name    void _setProperty(AreaProperty property)
 * @details 设置Area的属性值
 * @param   property 待设置属性
 * @author  lee
 * @date    2018-12-20
**/
void Area::_setProperty(AreaProperty property)
{
    setDisplay(property.displayMode);
    setMaxShow(property.maxShowMode);
    setMinShow(property.minShowMode);
    setAvgShow(property.avgShowMode);
    m_property = property;
}

//int Area::getDisplay()
//{
//    return m_property.displayMode;
//}

//int Area::getMaxShow()
//{
//    return m_property.maxShowMode;
//}

//int Area::getMinShow()
//{
//    return m_property.minShowMode;
//}

//int Area::getAvgShow()
//{
//    return m_property.avgShowMode;
//}

/**
 * @name    AreaProperty _getProperty()
 * @details 获取Area的属性值
 * @return   返回Area的属性
 * @author  lee
 * @date    2018-12-20
**/
AreaProperty Area::_getProperty()
{
    return m_property;
}

/**
 * @name    void setDisplay(int displayMode)
 * @details 根据displayMode的值，激活Area，温度显示label和更新温度定时器
 * @param  displayMode 0:off 1:on
 * @date    2018-12-20
**/
void Area::setDisplay(int displayMode)
{
    switch (displayMode) {
    case 0://hide
    {
        if(!m_label->isHidden())
            m_label->hide();
//        if(!m_maxCursor->isHidden())
//            m_maxCursor->hide();
//        if(!m_minCursor->isHidden())
//            m_minCursor->hide();
        QWidget::hide();
        updateTempTimer->stop();
        break;
    }
    case 1://show
    {
        setFocus();
        if(m_label->isHidden())
            m_label->show();
//        if(m_maxCursor->isHidden())
//            m_maxCursor->show();
//        if(m_minCursor->isHidden())
//            m_minCursor->show();
        QWidget::show();
        updateTempTimer->start(1000);
        m_property_temp = m_property;
        break;
    }
    default:
        break;
    }
    m_property.displayMode = displayMode;
}

/**
 * @name    void setMaxShow(int maxShow)
 * @details 根据maxShow的值，设置是否显示温度最大值
 * @param  maxShow 0:off 1:on
 * @date    2018-12-20
**/
void Area::setMaxShow(int maxShow)
{
    switch (maxShow) {
    case 0://Off
        qWarning("Max Off!");
        break;
    case 1://On
        qWarning("Max On!");
        break;
    default:
        break;
    }
    m_property.maxShowMode = maxShow;
}

/**
 * @name    void setMinShow(int minShow)
 * @details 根据minShow的值，设置是否显示温度最小值
 * @param  minShow 0:off 1:on
 * @date    2018-12-21
**/
void Area::setMinShow(int minShow)
{
    switch (minShow) {
    case 0://Off
        qWarning("Min Off!");
        break;
    case 1://On
        qWarning("Min On!");
        break;
    default:
        break;
    }
    m_property.minShowMode = minShow;
}

/**
 * @name    void setAvgShow(int avgShow)
 * @details 根据avgShow的值，设置是否显示温度平均值
 * @param  avgShow 0:off 1:on
 * @date    2018-12-21
**/
void Area::setAvgShow(int avgShow)
{
    switch (avgShow) {
    case 0://Off
        qWarning("Avg Off!");
        break;
    case 1://On
        qWarning("Avg On!");
        break;
    default:
        break;
    }
    m_property.avgShowMode = avgShow;
}

/**
 * @name    void rollbackProperty()
 * @details 撤销属性更改，恢复更改前的状态

 * @date    2018-12-20
**/
void Area::rollbackProperty()
{
    m_property = m_property_temp;
    _setProperty(m_property);
}

/**
 * @name    void commitProperty()
 * @details 确认更改属性

 * @date    2018-12-20
**/
void Area::commitProperty()
{
    m_property_temp = m_property;
}

/**
 * @name    void updateText()
 * @details 更新显示Label
 * @date    2018-12-21
**/
void Area::updateText()
{
    QString text = QString("Area %1").arg(m_id);
#ifdef SHOWTEMP
    float total = abs(m_maxTemp) + abs(m_minTemp)+ abs(m_avgTemp);
    QString maxTempText = QString("\nMax:")
            + (!total ? QString(">>>>>") : (QString::number(m_maxTemp, 'f', 1)));
    QString minTempText = QString("\nMin:")
            + (!total ? QString(">>>>>") : (QString::number(m_minTemp, 'f', 1)));
    QString avgTempText = QString("\nAvg:")
            + (!total ? QString(">>>>>") : (QString::number(m_avgTemp, 'f', 1)));
#else
    unsigned short total = 1;
    QString maxTempText = QString("\nMax:")
            + (!total ? QString(">>>>>") : (QString::number(m_areaTemp._max.AD, 16)));
    QString minTempText = QString("\nMin:")
            + (!total ? QString(">>>>>") : (QString::number(m_areaTemp._min.AD, 16)));
    QString avgTempText = QString("\nAvg:")
            + (!total ? QString(">>>>>") : (QString::number(m_areaTemp._averg.AD, 16)));
#endif

    if(m_property.maxShowMode == 1)
        text += maxTempText;
    if(m_property.minShowMode == 1)
        text += minTempText;
    if(m_property.avgShowMode == 1)
        text += avgTempText;

    m_label->setText(text);
    m_label->adjustSize();

    QPoint defPos = QPoint(SCREEN_WIDTH-m_label->width()-20,
                           (SCREEN_HEIGHT-m_label->height())/2);
    if(m_label->pos() != defPos)
        m_label->move(defPos);
}

/**
 * @name    void updateCursor()
 * @details 更新最大值最小的坐标图标
 * @date    2018-12-21
**/
void Area::updateCursor()
{
#ifdef PC
    qsrand(QTime(m_id,m_id,m_id).secsTo(QTime::currentTime()));
    unsigned int max_xOffset = qrand()%width();
    unsigned int max_yOffset = qrand()%height();
    unsigned int min_xOffset = qrand()%width();
    unsigned int min_yOffset = qrand()%height();

    QPoint startPoint = QPoint(geometry().topLeft().x()-m_minCursor->width()/2,
                               geometry().topLeft().y()-m_minCursor->height()/2);
    QPoint maxPoint, minPoint;

    maxPoint.setX(startPoint.x()+max_xOffset);
    maxPoint.setY(startPoint.y()+max_yOffset);

    minPoint.setX(startPoint.x()+min_xOffset);
    minPoint.setY(startPoint.y()+min_yOffset);

    //        qDebug()<<maxPoint<<", "<<minPoint;

    m_maxCursor->move(maxPoint);
    m_minCursor->move(minPoint);
    {
#else
    if(!(m_areaVal.maxX > geometry().topLeft().x()+width()+m_minCursor->width()/2 ||
         m_areaVal.minX > geometry().topLeft().x()+width()+m_minCursor->width()/2 ||
         m_areaVal.maxY > geometry().topLeft().y()+height()+m_minCursor->height()/2 ||
         m_areaVal.minY > geometry().topLeft().y()+height()+m_minCursor->height()/2))
    {

        m_maxCursor->move(m_areaVal.maxX, m_areaVal.maxY);
        m_minCursor->move(m_areaVal.minX, m_areaVal.minY);
#endif
        if(m_maxCursor->isHidden() && !isHidden())
        {
            m_maxCursor->show();
            m_minCursor->show();
        }
    }
}

/**
 * @name    void paintEvent(QPaintEvent *event)
 * @details 绘图事件。显示Area的名称，并根据是否获得焦点显示不同的效果
 * @param   event   绘图事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(0, 0, geometry().width()-1, geometry().height()-1);

    if(hasFocus())
    {
        painter.setPen(Qt::green);
        painter.drawRect(0+2, 0+2, geometry().width()-1-4, geometry().height()-1-4);
    }

    painter.setPen(Qt::white);

    painter.drawText(rect().topLeft()+QPoint(1, 15), QString("A%1").arg(m_id));
}

/**
 * @name    void mouseMoveEvent(QMouseEvent *event)
 * @details 鼠标移动事件。实现该Area在鼠标拖动状态下跟随移动,并判断是否处于修改大小状态
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //        //        raise();
        //        setFocus();
        isLeftPressDown = true;
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        event->accept();
    }
    //    if(event->button() == Qt::RightButton)
    //    {
    //        close();
    //    }
}

/**
 * @name    void mouseReleaseEvent(QMouseEvent *event)
 * @details 鼠标释放事件, 释放时取消修改大小状态
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    QWidget::mouseReleaseEvent(event);
}

/**
 * @name    void mouseMoveEvent(QMouseEvent *event)
 * @details 鼠标移动事件, 处理Area的移动和大小变化
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {
        this->region(gloPoint);
    }
    else {
        if(dir != NONE) {
            QRect rMove(pos().x(), pos().y(), width(), height());

            switch(dir) {
            case LEFT:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                break;
            case RIGHT:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                break;
            case UP:
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case DOWN:
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            case LEFTTOP:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case RIGHTTOP:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case LEFTBOTTOM:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            default:
                break;
            }
            if( !(rMove.width() < 0 || rMove.height() < 0
                  || (abs(rMove.topLeft().x() - rMove.bottomRight().x()) < 5*PADDING)
                  || (abs(rMove.topLeft().y() - rMove.bottomRight().y()) < 5*PADDING)))
                setGeometry(rMove);
        } else {
            QPoint position = event->globalPos()-dragPosition;
            move(position);
            event->accept();
        }
        update();
    }
}

/**
 * @name    void mouseDoubleClickEvent(QMouseEvent *event)
 * @details 鼠标双击事件。双击Area唤出属性窗口
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::mouseDoubleClickEvent(QMouseEvent *event)
{
    //    QMessageBox::information(this, QString("Area"), QString("I am Area %1!").arg(m_id), QMessageBox::Ok);
    propertyWnd->exec();
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 按下按键事件。方向键移动Area位置，回车键唤出属性窗口。长按时启动长按定时器，修改移动步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::keyPressEvent(QKeyEvent *event)
{
    if(!isPressed )
    {
        isPressed = true;
        longPressTimer->start(LONGPRESSDURATION);
        singleStepTemp = singleStep;
    }

    QPoint position(pos());

    if(event->key() == Qt::Key_Escape)
        event->ignore();
    if(event->key() == Qt::Key_Return)
        mouseDoubleClickEvent(0);
    {
        if(event->key() == Qt::Key_Left)
        {
            position.setX(position.x()-singleStep);
        }
        else if(event->key() == Qt::Key_Right)
        {
            position.setX(position.x()+singleStep);
        }
        if(event->key() == Qt::Key_Up)
        {
            position.setY(position.y()-singleStep);
        }
        else if(event->key() == Qt::Key_Down)
        {
            position.setY(position.y()+singleStep);
        }
        move(position);
    }
}

/**
 * @name    void keyReleaseEvent(QKeyEvent *event)
 * @details 释放按键事件。停止长按定时器，并重置步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Area::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat() && isPressed)
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    QWidget::keyReleaseEvent(event);
}

/**
 * @name    void longPressSlot()
 * @details 长按处理槽，改变移动的步进值
 * @date    2018-12-21
**/
void Area::longPressSlot()
{
    if(!hasFocus())
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    else
    {
        if(isPressed)
        {
            singleStep += 1;
        }
    }
}

/**
 * @name    void region(const QPoint &cursorGlobalPoint)
 * @details 重写region，判断拉伸大小的位置
 * @date    2018-12-21
**/
void Area::region(const QPoint &cursorGlobalPoint)
{
    //获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

/**
 * @name    void focusInEvent(QFocusEvent *event)
 * @details 获得焦点事件,显示温度label
 * @param   event   焦点事件指针
 * @date    2018-12-20
**/
void Area::focusInEvent(QFocusEvent *event)
{
    m_label->show();
    QWidget::focusInEvent(event);
}

/**
 * @name    void focusOutEvent(QFocusEvent *event)
 * @details 失去焦点事件,隐藏温度label
 * @param   event   焦点事件指针
 * @date    2018-12-20
**/
void Area::focusOutEvent(QFocusEvent *event)
{
    m_label->hide();
    QWidget::focusOutEvent(event);
}

/**
 * @name    void updateTempSlot()
 * @details 刷新温度槽，从底层读取温度数据并刷新显示
 * @date    2018-12-21
**/
void Area::updateTempSlot()
{
    m_areaRect.xlt = pos().x();
    m_areaRect.ylt = pos().y();
    m_areaRect.xrb = pos().x()+rect().width();
    m_areaRect.yrb = pos().y()+rect().height();

//    qDebug()<<m_areaRect.xlt<<", "<<m_areaRect.ylt<<", "<<m_areaRect.xrb<<", "<<m_areaRect.yrb;

    if( GlobalParam::getFPGA()->getAreaTemp(m_id, m_areaRect, m_areaVal, m_areaTemp) < 0 )
    {
        qWarning("read area temp failed");
        qsrand(QTime(m_id,m_id,m_id).secsTo(QTime::currentTime()));
        m_maxTemp = qrand()%100+qrand()%10*0.1;
        m_minTemp = qrand()%100+qrand()%10*0.1;
        if(m_maxTemp < m_minTemp)
        {
            float temp = m_maxTemp;
            m_maxTemp = m_minTemp;
            m_minTemp = temp;
        }
        m_avgTemp = (m_maxTemp+m_minTemp)/2.0;
    }
    else
    {
        m_maxTemp = m_areaTemp._max.temp;
        m_minTemp = m_areaTemp._min.temp;
        m_avgTemp = m_areaTemp._averg.temp;
//        updateCursor();
    }
   updateText();
}
