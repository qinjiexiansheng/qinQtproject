#ifndef LGLOBAL_H
#define LGLOBAL_H

#include "globalheader.h"
#include "caltemp/tfpga.h"

class TMainPage;
class GlobalParam
{
public:
    //背景显示状态
    enum Background{Hide, Show};
    //显示方向
    enum Orientation{HORIZONTAL, VERTICAL};
    //标题栏的样式
    enum TitleBarStyle{SINGLE_BUTTON, DOUBLE_BUTTON, SWITCH_BUTTON};
    //标题栏的信号返回类型的按键id
    enum ButtonType{NONE_BUTTON, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_SWITCH};
    //提供给SlideWidget使用，根据其类型在accept关闭窗口时设置相应的全局变量
    enum ValueType{DEFAULT, VALUE, TIME, TIMEZONE, SCREENSAVER, POWEROFF, TVOUTMODE, USBMODE, MULTIFUNCKEY};

    GlobalParam();

    static void setParentWidget(TMainPage *);
    static TMainPage * getParentWidget();

    static void setFPGA( TFPGA *_fpga);
    static TFPGA *getFPGA();

    static void setImageMode(int index);
    static int getImageMode();

    static void setPaletteMode(int index);
    static int getPaletteMode();

    static void setAdjustMode(int index);
    static int getAdjustMode();

    static void setCurrentIndex(int index);
    static int getCurrentIndex();

    static int getCurrentWifiState();

    static void loadDefault();

    static void setBackground(GlobalParam::Background);
    static GlobalParam::Background getBackground();

    static void setTempRangeLevel(int);
    static int getTempRangeLevel();

    static void setLowerLimit(int);
    static int getLowerLimit();

    static void setUpperLimit(int);
    static int getUpperLimit();

    static void setParamSettingValue(float);
    static float getParamSettingValue();

    static void setcompSwitchState(bool);
    static bool getcompSwitchState();

    static void addSpotCount();
    static uint getSpotCount();

    static void addAreaCount();
    static uint getAreaCount();

    static void setTimeZoneTemp(QString);
    static QString getTimeZoneTemp();

    static void setScreenSaver(QString);
    static QString getScreenSaver();

    static void setPowerOff(QString);
    static QString getPowerOff();

    static void setLengthUnit(int);
    static int getLengthUnit();

    static void setTempUnit(int);
    static int getTempUnit();

    static void setLens(int);
    static int getLens();

    static void setTVOutMode(QString);
    static QString getTVOutMode();

    static void setLEDState(bool);
    static bool getLEDState();

    static void setLaserState(bool);
    static bool getLaserState();

    static void setUSBMode(QString);
    static QString getUSBMode();

    static void setMultifuncKey(QString);
    static QString getMultifuncKey();

private:
    //父窗口指针
    static TMainPage *g_parentWidget;

    //设置参数时的临时值
    static float g_paramSettingValue;

    //全局参数设置
    static GlobalParam::Background g_background;
    static int g_lens;

    //设置温度档位时的参数
    static int g_tempRangeLevel;
    static int g_lowerLimit;
    static int g_upperLimit;

    //开启测温分析的控件数量
    static uint g_spotCount;
    static uint g_areaCount;
    static bool g_lineSwitch;

    //比较温度界面的开关状态
    static bool g_compSwitchState;

    //关于时间设置
    static QString g_timezoneTemp;

    //关于单位设置
    static int g_lengthUnit;
    static int g_tempUnit;

    //关于电源管理
    static QString g_screenSaver;
    static QString g_powerOff;

    //关于控制窗口
    static QString g_tvoutMode;
    static bool g_ledState;
    static bool g_laserState;
    static QString g_usbMode;
    static QString g_multifuncKey;

    //TFPGA 单例
    static TFPGA *g_fpga;

    //Image Mode
    static int g_imageMode;
    static int g_paletteMode;
    static int g_adjustMode;

    //暂存滑动窗口中的Index值
    static int g_index;

    //保存当前的wifi状态
    static  bool g_wifiState;
};

#endif // LGLOBAL_H
