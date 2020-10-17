#ifndef MACRODEFINE_H
#define MACRODEFINE_H

#include <QObject>

//按键长按的触发时间
#define KEY_LONG_TIME 2000
//控制刷新数据的间隔
#define UPDATA_TIME   400
//自动打档时间
#define AUTOSAVE_TIME 30000


#define KEY_16 Qt::Key_P
#define KEY_18 Qt::Key_F
#define KEY_19 Qt::Key_W
#define KEY_20 Qt::Key_S
#define KEY_21 Qt::Key_A
#define KEY_22 Qt::Key_D
#define KEY_23 Qt::Key_G
#define KEY_24 Qt::Key_H
#define KEY_25 Qt::Key_R
#define KEY_26 Qt::Key_K
#define KEY_27 Qt::Key_L
//按键扫描间隔
#define KEYSCAN_TIME  150
//报警项闪烁间隔
#define ALARM_FLASH_TIME  1000
//电量项闪烁间隔
#define BAT_FLASH_TIME 1000
//
#define Tips_Hide_Time 1000


//电量分段数值
#define BATTERY_FOUR_MIN  75
#define BATTERY_THREE_MIN 50
#define BATTERY_TWO_MIN   25
#define BATTERY_ONE_MIN   10
#define BATTERY_ZERO_MIN  0

#define BATTERY_SHOTDOWN  3


//电量分段对应的图标索引
#define BATTERY_FOUR  0
#define BATTERY_THREE 1
#define BATTERY_TWO   2
#define BATTERY_ONE   3
#define BATTERY_ZERO  4


#define MAX_FID    2792
#define MIN_FID    931
#define MAX_GSK    3351
#define MIN_GSK    1
#define MAX_GAIN   2
#define MIN_GAIN   0
#define MAX_INT    100000
#define MIN_INT    0

#define DEFAULT_FID 2200
#define DEFAULT_GSK 1700
#define DEFAULT_GAIN 2
#define DEFAULT_INT  380
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
#ifdef _SAT_XNJ_
#define ROOT_DIR           "/home/sat/Sat/Root/GF5000/root/"
#define COF_DIR            "/home/sat/Sat/Root/GF5000/cof/"
#define IMG_DIR            "/home/sat/Sat/Root/GF5000/img/"
#define QSS_DIR            "/home/sat/Sat/Root/GF5000/qss/"
#define LOG_DIR            "/home/sat/Sat/Root/GF5000/log/"
#define SD_DIR             "/home/sat/Sat/Root/sdcard/GF5000/cof/"
#define TEMP_AD_TABLE      "tmpad%1.txt"
#define TEMP_AD_TABLE_NEW  "tmpad-new%1.txt"
#define ARG_FILE           "arg%1.txt"
#define DATA_FILE          "test%1.txt"
#define DATA_FILE_TWO      "stest%1.txt"
#define K_FILE             "k%1.dat"
#define K_FILE_DEFAULT     "k.dat"
#define TEMP_AD_TABLE_OTH  "tmpad.txt"
#define LOG_FILE           "log%1.txt"

#define PICTURE_DIR        "/home/sat/Sat/Root/GF5000/pictures/"
#define VIDEO_DIR          "/home/sat/Sat/Root/GF5000/videos/"
#define VIDEO_PICTURE      "/home/sat/Sat/Root/GF5000/img/video_focus.png"
#define PHOTO_PICTURE      "/home/sat/Sat/Root/GF5000/img/photo_focus.png"
#define QM_DIR             "/home/sat/Sat/Root/GF5000/cof/"
#endif
/*==========================
    ARM目录结构(暂定)
    +root(/root/)//根目录
        +Qt4.5.3/GF5000/res(/root/Qt4.5.3/GF5000/res/)
            +cof  //档位参数，K值表，标定表
            +img  //图片资源
            +qss  //样式表
            +log  //日志
        +sdcard   //SD卡目录
 *==========================*/
#ifdef _SAT_ARM_
#define ROOT_DIR           "/root/"
#define COF_DIR            "/root/Qt4.5.3/GF5000/res/cof/"
#define IMG_DIR            "/root/Qt4.5.3/GF5000/res/img/"
#define QSS_DIR            "/root/Qt4.5.3/GF5000/res/qss/"
#define LOG_DIR            "/root/Qt4.5.3/GF5000/res/log/"
#define SD_DIR             "/root/sdcard/GF5000/cof/"
#define TEMP_AD_TABLE      "tmpad%1.txt"
#define TEMP_AD_TABLE_NEW  "tmpad-new%1.txt"
#define ARG_FILE           "arg%1.txt"
#define DATA_FILE          "test%1.txt"
#define DATA_FILE_TWO      "stest%1.txt"
#define K_FILE             "k%1.dat"
#define K_FILE_DEFAULT     "k.dat"
#define TEMP_AD_TABLE_OTH  "tmpad.txt"
#define LOG_FILE           "log%1.txt"

#define PICTURE_DIR        "/root/sdcard/pics/"
#define VIDEO_DIR          "/root/sdcard/video/"
#define VIDEO_PICTURE      "/root/Qt4.5.3/GF5000/res/img/video_focus.png"
#define PHOTO_PICTURE      "/root/Qt4.5.3/GF5000/res/img/photo_focus.png"


#define QM_DIR             "/root/Qt4.5.3/GF5000/res/cof/"
#define VERSION            "/root/Version"
#endif


#define ARROW_PNG    "arrowr.png"
#define TICK_PNG     "hook.png"
#define OFF_PNG      "off.png"
#define ON_PNG       "on.png"

#define App_Param    "app.ini"



//自动打档最小时间
#define AUTO_SHUTTER_TIME 30
#define AUTO_SHUTTER_MIN_TIME  10
//当前年份
#define CURRENT_YEAR    2018
//最大年数
#define YEAR_MAX_COUNT 30
//月数
#define MONTH_MAX_COUNT 12
//天数
#define DAY_MAX_COUNT 31
//屏幕大小
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//探头大小
#define PIXEL_WIDTH   368
#define PIXEL_HEIGHT  288
//温度AD表默认个数
#define TEMP_AD_TABLE_TABNUM 20
#define TEMP_AD_TABLE_TABBASETMP 30

//报警温度
#define ALARM_TEMP 500
#define RED_TEMP 600
#define ORANGE_TEMP 500


#define DET_REFERENCE_ONE 8608
#define INT_REFERENCE_ONE 320
#define B_CONSTANT_ONE    (-8)
#define A_FORMULA_ONE     0.0001
#define B_FORMULA_ONE     1.2901
#define C_FORMULA_ONE     10018

#define DET_REFERENCE_TWO 8600
#define INT_REFERENCE_TWO 60
#define B_CONSTANT_TWO    (0)
#define A_FORMULA_TWO     0.0001
#define B_FORMULA_TWO     1.1882
#define C_FORMULA_TWO     9947.5



#define Emiss_Min  0.01
#define Emiss_Max  1.00
#define Dis_Min    0.5
#define Dis_Max    1000
#define EnvTemp_Min  (-40.0)
#define EnvTemp_Max  125.0
#define RefTemp_Min  (-40.0)
#define RefTemp_Max  125.0
#define RelHum_Min   0.01
#define RelHum_Max   1.00
#define CorTemp_Min  (-40.0)
#define CorTemp_Max  125.0


#define ShutDownTime   3


//备份文件列表
#ifdef _SAT_ARM_
#if 0
//需要打包的文件记录，根据里面记录的文件进行复制打包
#define BackupListFile     "/root/sdcard/backup.file"
//打包目录，需要打包的文件将复制到该目录下，解压的文件也是存放在该目录下
#define BackupDataDir      "/root/Qt4.5.3/GF5000/res/backup/data/"
//备份存放点
#define BackupDir          "/root/Qt4.5.3/GF5000/res/backup/"
//打包中间文件
#define BackupTgzFile      "backup.tgz"
//打包并且加密后的文件
#define BackupGpgFile      "backup.tgz.gpg"
//临时打包脚本
#define BackupScript       "backup.sh"
//压缩包的文件信息，用于将判断文件移动到哪里
#define BackupInfoDat      "backup.dat"
//秘钥文件
#define KeyFile            "gpg_key"
//更新脚本
#define UpdateScript       "/root/Qt4.5.3/GF5000/res/backup/update.sh"
#define BackupInfoFile     "backup.file"
#define EXE_FILE           "/root/Qt4.5.3/GF5000/GF5000"
#define TEMP_SH            "temp.sh"
#endif

#define Package_File_List        "/root/Qt4.5.3/GF5000/res/workspace/backup.file"
#define Package_File_List_Name   "backup.file"
#define Workspace                "/root/Qt4.5.3/GF5000/res/workspace/"
#define Package                  "/root/Qt4.5.3/GF5000/res/workspace/package/"
#define Package_Name             "backup.tgz"
#define Package_Gpg_Name         "backup.tgz.gpg"
#define Key_File                 "gpg_key"
#define Update_Script            "/root/Qt4.5.3/GF5000/res/workspace/update.sh"
#define Package_Script           "package.sh"
#define GF5000_Exe               "/root/Qt4.5.3/GF5000/GF5000"
#define Package_Old_Name         "backup-old.tgz.gpg"
#define Tmp_Script               "/root/Qt4.5.3/GF5000/res/workspace/tmp.sh"


#endif


//===============pc端----end====================
#ifdef _SAT_XNJ_
/*  Package_File_List            备份文件列表
 *  Package_File_List_Name
 *  Workspace                    工作空间
 *  Package                      打包目录
 *  Package_Name                 包名字
 *  Package_Gpg_Name             加密包
 *  Package_Script               打包脚本
 *  Key_File                     秘钥文件
 *  Update_Script                更新脚本
 *  GF5000_Exe                   执行文件
 *  Tmp_Script                   临时脚本
 */
#define Package_File_List        "/home/sat/Sat/Root/GF5000/workspace/backup.file"
#define Package_File_List_Name   "backup.file"
#define Workspace                "/home/sat/Sat/Root/GF5000/workspace/"
#define Package                  "/home/sat/Sat/Root/GF5000/workspace/package/"
#define Package_Name             "backup.tgz"
#define Package_Gpg_Name         "backup.tgz.gpg"
#define Key_File                 "gpg_key"
#define Update_Script            "/home/sat/Sat/Root/GF5000/workspace/update.sh"
#define Package_Script           "package.sh"
#define GF5000_Exe               "/home/sat/Sat/Root/GF5000"
#define Package_Old_Name         "backup-old.tgz.gpg"
#define Tmp_Script               "/home/sat/Sat/Root/GF5000/workspace/tmp.sh"

#if 0
//需要打包的文件记录，根据里面记录的文件进行复制打包
#define BackupListFile     "/home/sat/Sat/Root/GF5000/backup/backup.file"
//打包目录，需要打包的文件将复制到该目录下，解压的文件也是存放在该目录下
#define BackupDataDir      "/home/sat/Sat/Root/GF5000/backup/data/"
//备份存放点
#define BackupDir          "/home/sat/Sat/Root/GF5000/backup/"
//打包中间文件
#define BackupTgzFile      "backup.tgz"
//打包并且加密后的文件
#define BackupGpgFile      "backup.tgz.gpg"
//临时打包脚本
#define BackupScript       "backup.sh"
//压缩包的文件信息，用于将判断文件移动到哪里
#define BackupInfoDat      "backup.dat"

#define KeyFile            "gpg_key"  //秘钥文件
//更新脚本
#define UpdateScript       "/home/sat/Sat/Root/GF5000/backup/update.sh"
#define BackupInfoFile     "backup.file"
#define EXE_FILE           "/root/Qt4.5.3/GF5000/GF5000"
#define TEMP_SH            "temp.sh"
#endif
#endif


#define EXIT_CODE_REBOOT 123456789

#define App_Version        "V1.0.0"

#define Max_Interval       10










#endif // MACRODEFINE_H
