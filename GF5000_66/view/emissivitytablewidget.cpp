#include "emissivitytablewidget.h"

//辐射率表窗口的小窗口
SatEmissivityTableSmallWidget::SatEmissivityTableSmallWidget(QWidget *parent) : QWidget(parent){
    this->setFixedSize(640,60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //上移按钮
    SatPhotoButton *nMoveUpButton = new SatPhotoButton(this);
    nMoveUpButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("moveup_normal.png"));
    nMoveUpButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("moveup_focus.png"));
    nMoveUpButton->setTextStr(tr("MoveUp"));
    nMoveUpButton->setTextShowSign(false);
    nMoveUpButton->installEventFilter(this);
    nLayout->addWidget(nMoveUpButton);
    nSignalMapper->setMapping(nMoveUpButton,"MoveUp");
    connect(nMoveUpButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nMoveUpButton);
    //下移
    SatPhotoButton *nMoveDownButton = new SatPhotoButton(this);
    nMoveDownButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("movedown_normal.png"));
    nMoveDownButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("movedown_focus.png"));
    nMoveDownButton->setTextStr(tr("MoveDown"));
    nMoveDownButton->setTextShowSign(false);
    nMoveDownButton->installEventFilter(this);
    nLayout->addWidget(nMoveDownButton);
    nSignalMapper->setMapping(nMoveDownButton,"MoveDown");
    connect(nMoveDownButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nMoveDownButton);
    //左移
    SatPhotoButton *nLeftShiftButton = new SatPhotoButton(this);
    nLeftShiftButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("leftshift_normal.png"));
    nLeftShiftButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("leftshift_focus.png"));
    nLeftShiftButton->setTextStr(tr("LeftShift"));
    nLeftShiftButton->setTextShowSign(false);
    nLeftShiftButton->installEventFilter(this);
    nLayout->addWidget(nLeftShiftButton);
    nSignalMapper->setMapping(nLeftShiftButton,"LeftShift");
    connect(nLeftShiftButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLeftShiftButton);
    //右移
    SatPhotoButton *nRightShiftButton = new SatPhotoButton(this);
    nRightShiftButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("rightshift_normal.png"));
    nRightShiftButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("rightshift_focus.png"));
    nRightShiftButton->setTextStr(tr("RightShift"));
    nRightShiftButton->setTextShowSign(false);
    nRightShiftButton->installEventFilter(this);
    nLayout->addWidget(nRightShiftButton);
    nSignalMapper->setMapping(nRightShiftButton,"RightShift");
    connect(nRightShiftButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRightShiftButton);
    //隐藏
    SatPhotoButton *nHideButton = new SatPhotoButton(this);
    nHideButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_normal.png"));
    nHideButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_focus.png"));
    nHideButton->setTextStr(tr("Hide"));
    nHideButton->setTextShowSign(false);
    nHideButton->installEventFilter(this);
    nLayout->addWidget(nHideButton);
    nSignalMapper->setMapping(nHideButton,"Hide");
    connect(nHideButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nHideButton);
    //退出
    SatPhotoButton *nQuitButton = new SatPhotoButton(this);
    nQuitButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_normal.png"));
    nQuitButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_focus.png"));
    nQuitButton->setTextStr(tr("Quit"));
    nQuitButton->setTextShowSign(false);
    nQuitButton->installEventFilter(this);
    nLayout->addWidget(nQuitButton);
    nSignalMapper->setMapping(nQuitButton,"Quit");
    connect(nQuitButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nQuitButton);
    //配置
    nLayout->addStretch();
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->setMargin(0);
    nLayout->setSpacing(10);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatEmissivityTableSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatEmissivityTableSmallWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_26:
                focusPrevious();
                break;
            case KEY_27:
                focusNext();
                break;
            case KEY_16:
                mList.at(mIndex)->click();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatEmissivityTableSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatEmissivityTableSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatEmissivityTableSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatEmissivityTableSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "MoveUp"){
        mIndex = 0;
    }else if(nOpeStr == "MoveDown"){
        mIndex = 1;
    }else if(nOpeStr == "LeftShift"){
        mIndex = 2;
    }else if(nOpeStr == "RightShift"){
        mIndex = 3;
    }else if(nOpeStr == "Hide"){
        this->hide();
        return;
    }else if(nOpeStr == "Quit"){
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}







SatEmissivityTablePage::SatEmissivityTablePage(QWidget *parent) : QTableWidget(parent){
    this->setColumnCount(5);//5列
    this->setRowCount(16);//16行
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    this->verticalHeader()->setVisible(false);//设置行表头隐藏
    //表头
    QStringList nHeader;
    nHeader << tr("Name") << tr("Type") << tr("Min") << tr("Max") << tr("Default");
    this->setHorizontalHeaderLabels(nHeader);
    //表头字体加粗
    QFont nFont = this->horizontalHeader()->font();
    nFont.setBold(true);
    this->horizontalHeader()->setFont(nFont);
    //
    QString nStringList[16][5] = {{tr("Asphaltum"),tr("Nonmetal"),"0.85","0.85","0.85"},
                                  {tr("Brick"),tr("Nonmetal"),"0.75","0.75","0.75"},
                                  {tr("Calcimine"),tr("Nonmetal"),"0.90","0.90","0.90"},
                                  {tr("Ceramics(vase type)"),tr("Nonmetal"),"0.90","0.90","0.90"},
                                  {tr("Copper Wire"),tr("Metal"),"0.87","0.88","0.87"},
                                  {tr("Diode"),tr("Nonmetal"),"0.89","0.90","0.89"},
                                  {tr("Fire resistance brick"),tr("Nonmetal"),"0.75","0.75","0.75"},
                                  {tr("Graphite(lamp black)"),tr("Nonmetal"),"0.95","0.95","0.95"},
                                  {tr("Glass"),tr("Nonmetal"),"0.91","0.92","0.91"},
                                  {tr("Glass(surface)"),tr("Nonmetal"),"0.94","0.94","0.94"},
                                  {tr("Liquid Steel"),tr("Metal"),"0.28","0.28","0.28"},
                                  {tr("Mercury"),tr("Metal"),"0.09","0.12","0.11"},
                                  {tr("Sheet metal"),tr("Metal"),"0.88","0.90","0.89"},
                                  {tr("Stainless Stell 310(25Cr,20Ni)"),tr("Metal"),"0.90","0.97","0.94"},
                                  {tr("Steel(oxidizing at 600c\\260c)"),tr("Metal"),"0.79","0.79","0.79"},
                                  {tr("Ransistor(plastics sealed)"),tr("Nonmetal"),"0.30","0.40","0.35"}
                                 };
    for(int nRow = 0; nRow <16; nRow++){
        for(int nColum = 0; nColum < 5; nColum++){
            QTableWidgetItem *nItem = new QTableWidgetItem;
            nItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            nItem->setText(nStringList[nRow][nColum]);
            this->setItem(nRow,nColum,nItem);
        }
    }
    this->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);

#if 0
      //设置表头字体加粗
      QFont font = this->horizontalHeader()->font();
      font.setBold(true);
      table_widget->horizontalHeader()->setFont(font);

      table_widget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
      table_widget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
      table_widget->verticalHeader()->setDefaultSectionSize(10); //设置行高
      table_widget->setFrameShape(QFrame::NoFrame); //设置无边框
      table_widget->setShowGrid(false); //设置不显示格子线
      table_widget->verticalHeader()->setVisible(false); //设置垂直头不可见
      table_widget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都能够）
      table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
      table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
      table_widget->horizontalHeader()->resizeSection(0,150); //设置表头第一列的宽度为150
      table_widget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
      table_widget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
      table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

      //设置水平、垂直滚动栏样式
      table_widget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
      table_widget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
#endif
}

void SatEmissivityTablePage::moveUpSlot(){
    QScrollBar *nVerBar = this->verticalScrollBar();
    nVerBar->setSliderPosition(nVerBar->value() - 10);
}

void SatEmissivityTablePage::moveDownSlot(){
    QScrollBar *nVerBar = this->verticalScrollBar();
    nVerBar->setSliderPosition(nVerBar->value() + 10);
}

void SatEmissivityTablePage::leftShiftSlot(){
    QScrollBar *nHorBar = this->horizontalScrollBar();
    nHorBar->setSliderPosition(nHorBar->value() - 10);
}

void SatEmissivityTablePage::rightShiftSlot(){
    QScrollBar *nHorBar = this->horizontalScrollBar();
    nHorBar->setSliderPosition(nHorBar->value() + 10);
}









EmissivityTableWidget::EmissivityTableWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Emissivity Table"));
    mSatTitleBar->installEventFilter(this);


    mSmallWidget = new SatEmissivityTableSmallWidget(this);
    mSmallWidget->hide();
    mRightWidget = new SatEmissivityTablePage(this);
    mRightWidget->installEventFilter(this);

    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar,0,Qt::AlignTop);
    nVLayout->addWidget(mRightWidget);
    nVLayout->addWidget(mSmallWidget,0,Qt::AlignBottom);
    nVLayout->setContentsMargins(0,0,0,0);
    nVLayout->setSpacing(0);//设置内边框
    nVLayout->setStretchFactor(mRightWidget,10);
    this->setLayout(nVLayout);
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));
}

void EmissivityTableWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                mSatTitleBar->setTitle(tr("Emissivity Table"));
            }
            break;
        default:
            break;
    }
}


void EmissivityTableWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void EmissivityTableWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
}

bool EmissivityTableWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
#if 0
        if(nKey->isAutoRepeat()){
            return ture;
        }
#endif
        switch(nKey->key()){
            case KEY_16:
                {
                    mSmallWidget->show();
                }
                break;
            case KEY_26:
                focusPrevious();
                break;
            case KEY_27:
                focusNext();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}



void EmissivityTableWidget::goBackSlot(){
    mSmallWidget->hide();
    this->hide();
}

void EmissivityTableWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == "MoveUp"){
        mRightWidget->moveUpSlot();
    }else if(nOpeStr == "MoveDown"){
        mRightWidget->moveDownSlot();
    }else if(nOpeStr == "LeftShift"){
        mRightWidget->leftShiftSlot();
    }else if(nOpeStr == "RightShift"){
        mRightWidget->rightShiftSlot();
    }else if(nOpeStr == "Quit"){
        mSmallWidget->hide();
        this->hide();
    }else{
    }
}

void EmissivityTableWidget::focusPrevious(){
    mRightWidget->moveUpSlot();
}

void EmissivityTableWidget::focusNext(){
    mRightWidget->moveDownSlot();
}

