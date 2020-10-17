#ifndef GLOBALDEFINES_H
#define GLOBALDEFINES_H

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#define MAXSPOTNUM  8
#define MAXAREANUM  5

#ifdef PC
    #define MAIN_TEXT_COLOR          QString("QLabel{font-weight: bold; color: rgb(0, 0, 0)}")
    #define MAIN_BACKGROUND_COLOR    QString("QWidget#obj {background-color: rgb(255, 0, 255);}")
#else
    #define MAIN_TEXT_COLOR          QString("QLabel{font-weight: bold; color: rgb(255, 255, 255)}")
    #define MAIN_BACKGROUND_COLOR    QString("QWidget#obj {background-color: rgb(254, 254, 254);}")
#endif
#define MAINPAGE_STYLESHEET \
{\
    QString("%1 %2")\
    .arg(MAIN_BACKGROUND_COLOR)\
    .arg(MAIN_TEXT_COLOR)\
}

#define BACKGROUND_COLOR         QString("background-color: rgb(0, 155, 155)")
#define CHILDPAGE_STYLESHEET     QString("%1").arg(BACKGROUND_COLOR)

//Qt LIB
#include <QApplication>
#include <QBitmap>
#include <QButtonGroup>
#include <QComboBox>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QDirModel>
#include <QEvent>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QFocusEvent>
#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QHash>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QImage>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QModelIndex>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QPen>
#include <QPixmap>
#include <QProcess>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QSocketNotifier>
#include <QStyledItemDelegate>
#include <QTabBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QTimeZone>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QWidget>


//C++ LIB
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>



#endif // GLOBALDEFINES_H
