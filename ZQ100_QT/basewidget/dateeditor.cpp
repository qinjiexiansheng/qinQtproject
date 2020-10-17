#include "dateeditor.h"
#include "basewidget/slidearea.h"

/**
 * @name    DateEditor(QWidget *parent, int H_Spacing, int V_Spacing) : QDialog(parent)
 * @details DateEditor类提供一个设置当前日期的界面
 * @param   parent  父窗口指针
 * @param   H_Spacing   水平间隙
 * @param   V_Spacing   垂直间隙

 * @date    2018-11-21
**/
DateEditor::DateEditor(QWidget *parent, int H_Spacing, int V_Spacing) : QDialog(parent)
{
    m_hSpacing = H_Spacing;
    m_vSpacing = V_Spacing;

    initView();
}

/**
 * @name    void initView()
 * @details 初始化日记编辑器的界面

 * @date    2018-11-21
**/
void DateEditor::initView()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    m_title = new QLabel("Date Setting");
    m_LButton = new QPushButton("Cancel");
    m_RButton = new QPushButton("Ok");

    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFrameStyle(QFrame::StyledPanel);

    m_title->setFocusPolicy(Qt::NoFocus);
    m_LButton->setFocusPolicy(Qt::NoFocus);
    m_RButton->setFocusPolicy(Qt::NoFocus);

    //新建两个滑动窗口
    m_monthArea = new SlideArea(this, m_hSpacing, m_vSpacing);
    m_dayArea = new SlideArea(this, m_hSpacing, m_vSpacing);
    m_yearArea = new SlideArea(this, m_hSpacing, m_vSpacing);

    //滑动窗口之间的间隔
    m_dot = new QLabel("-");
    m_dot->setAlignment(Qt::AlignCenter);
    m_dot->setScaledContents(true);
    m_dot->adjustSize();
    m_dot->setFixedSize(m_dot->size());
    m_dot->setFocusPolicy(Qt::NoFocus);

    m_dot2 = new QLabel("-");
    m_dot2->setAlignment(Qt::AlignCenter);
    m_dot2->setScaledContents(true);
    m_dot2->adjustSize();
    m_dot2->setFixedSize(m_dot2->size());
    m_dot2->setFocusPolicy(Qt::NoFocus);

    m_title->setFixedHeight(m_vSpacing);
    m_LButton->setFixedHeight(m_vSpacing);
    m_RButton->setFixedHeight(m_vSpacing);

    installData();

    connect(m_monthArea, SIGNAL(valueChangedSig()), this, SLOT(adjustDay()));
    connect(m_yearArea, SIGNAL(valueChangedSig()), this, SLOT(adjustDay()));

    connect(m_LButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(m_RButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

/**
 * @name    void installData()
 * @details 给月分、天数和年份滑动窗口装载相关显示数据

 * @date    2018-11-21
**/
void DateEditor::installData()
{
    QStringList list;
    list<<"Jan."<<"Feb."<<"Mar."<<"Apr."<<"May."<<"Jun."
       <<"Jul."<<"Aug."<<"Sep."<<"Oct."<<"Nov."<<"Dec.";
    m_monthArea->addItems(&list);
    list.clear();
    for(int i=1; i<=31; i++)
        list<<QString::number(i);
    m_dayArea->addItems(&list);
    list.clear();
    int begin = QDate::currentDate().year() - 50;
    int end = QDate::currentDate().year() + 50;
    for(int i=begin; i<=end; i++)
        list<<QString::number(i);
    m_yearArea->addItems(&list);

    m_monthArea->setCurrentIndex(QDate::currentDate().month()-1);
    m_dayArea->setCurrentText(QDate::currentDate().day());
    m_yearArea->setCurrentText(QDate::currentDate().year());

    adjustDay();

    adjustLayout();
}

/**
 * @name    void adjustDay()
 * @details 当月份或年份变更时，调整天数滑动窗口的显示

 * @date    2018-11-21
**/
void DateEditor::adjustDay()
{
//    if(!(qobject_cast<SlideArea *>(sender()) == m_yearArea && (m_monthArea->getCurrentIndex()+1) == 2))
//        return;
    int month = m_monthArea->getCurrentIndex()+1;
    int year = m_yearArea->getCurrentText().toInt();

    int day = getDaysInMonth(year, month);

    m_dayArea->setShowItemNum(day);
}

/**
 * @name    int getDaysInMonth(int year,int month)
 * @details 计算某月的天数
 * @param   year    年份
 * @param   month   月份

 * @date    2018-11-21
**/
int DateEditor::getDaysInMonth(int year,int month)
{
    int d;
    int day[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if (2==month)
    {
        d=(((0==year%4)&&(0!=year%100)||(0==year%400))?29:28);
    }
    else
    {
        d=day[month-1];

    }
    return d;
}

/**
 * @name    void adjustLayout()
 * @details 调整窗口的布局

 * @date    2018-11-21
**/
void DateEditor::adjustLayout()
{
    //两个滑动窗口都无数据时直接退出
    if(m_monthArea->isEmpty() && m_dayArea->isEmpty())
        return;

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->setMargin(0);
    viewLayout->setSpacing(0);
    viewLayout->addWidget(m_monthArea);
    viewLayout->addWidget(m_dot);
    viewLayout->addWidget(m_dayArea);
    viewLayout->addWidget(m_dot2);
    viewLayout->addWidget(m_yearArea);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setMargin(0);
    btnLayout->setSpacing(0);
    btnLayout->addWidget(m_LButton);
    btnLayout->addWidget(m_RButton);

    delete this->layout();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_title);
    mainLayout->addLayout(viewLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);

    setFixedSize(mainLayout->sizeHint());

    show();
}

/**
 * @name    void accept()
 * @details 窗口accept前，设置系统的日期时间

 * @date    2018-11-21
**/
void DateEditor::accept()
{
    int y = m_yearArea->getCurrentText().toInt();
    int m = m_monthArea->getCurrentIndex()+1;
    int d = m_dayArea->getCurrentText().toInt();
    QString date = QDate(y, m, d).toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh:mm:ss");
#ifdef PC
    QString cmd = QString("date -s \"%1 %2\"")
            .arg(date).arg(time);
#else
    QString cmd = QString("/mnt/sd/busybox date -s \"%1 %2\"")
            .arg(date).arg(time);
#endif


    QProcess *pro = new QProcess(this);
    pro->execute(cmd);

#ifdef PC
        pro->execute("hwclock -w");
#else
        pro->execute("/mnt/sd/busybox hwclock -w");
#endif
    QDialog::accept();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义回车和Esc键的功能
 * @param   e  按键事件

 * @date    2018-11-21
**/
void DateEditor::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        reject();
    else if(e->key() == Qt::Key_Return)
        accept();
    else
        e->accept();
}
