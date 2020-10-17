#ifndef SATDEFINE_H
#define SATDEFINE_H

#include <QObject>

#define UP      Qt::Key_Up
#define DOWN    Qt::Key_Down
#define LEFT    Qt::Key_Left
#define RIGHT   Qt::Key_Right
#define ENTER   Qt::Key_Return
#define ESC     Qt::Key_Escape

#define TAB_WIDE 120
#define TAB_HIGH 240

/*==========================
    PC目录结构
    +Root(/home/sat/Sat/Root/)
        +GF5000
            +cof  //档位参数，K值表，标定表
            +img  //图片资源
            +qss  //样式表
            +log  //日志
            +root //模拟根目录
        +sdcard   //模拟SD卡目录
 *==========================*/
#define COF_DIR            "/home/sat/Sat/Root/GF5000/cof/"
#define TEMP_AD_TABLE      "tmpad%1.txt"
#define TEMP_AD_TABLE_NEW  "tmpad-new%1.txt"

#endif // SATDEFINE_H
