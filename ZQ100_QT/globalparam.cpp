#include "globalparam.h"
#include "tmainpage.h"

//设置初始化变量
TMainPage* GlobalParam::g_parentWidget= NULL;
float GlobalParam::g_paramSettingValue = 0.00;

//Analysis
uint GlobalParam::g_spotCount = 0;
uint GlobalParam::g_areaCount = 0;
bool GlobalParam::g_lineSwitch = false;

//Analysis Setting
GlobalParam::Background GlobalParam::g_background = GlobalParam::Background::Hide;
int GlobalParam::g_tempRangeLevel = 0;
int GlobalParam::g_lowerLimit = -20;
int GlobalParam::g_upperLimit = 150;
bool GlobalParam::g_compSwitchState = false;
int GlobalParam::g_lens = 24;

//System Setting
QString GlobalParam::g_timezoneTemp = QString(QTimeZone::systemTimeZoneId());
int GlobalParam::g_lengthUnit = 0;
int GlobalParam::g_tempUnit = 0;
QString GlobalParam::g_screenSaver = "Off";
QString GlobalParam::g_powerOff = "Off";

//Control
QString GlobalParam::g_tvoutMode = "PAL";
bool GlobalParam::g_ledState = false;
bool GlobalParam::g_laserState = false;
QString GlobalParam::g_usbMode = "UDisk";
QString GlobalParam::g_multifuncKey = "Shutter";

TFPGA *GlobalParam::g_fpga = NULL;

//Image Mode
int GlobalParam::g_imageMode = 0;
int GlobalParam::g_paletteMode = 0;
int GlobalParam::g_adjustMode = 1;

int GlobalParam::g_index = 0;

/**
 * @name    GlobalParam()
 * @details 构造函数

 * @date    2018-11-15
**/
GlobalParam::GlobalParam()
{

}

/**
 * @name    void setParentWidget(QWidget *widget)
 * @details 设置父窗口的指针
 * @param   widget 父窗口的指针

 * @date    2018-11-15
**/
void GlobalParam::setParentWidget(TMainPage *widget)
{
    g_parentWidget = widget;
}

/**
 * @name    QWidget *getParentWidget()
 * @details 获取父窗口的指针
 * @return  父窗口的指针

 * @date    2018-11-15
**/
TMainPage *GlobalParam::getParentWidget()
{
    return g_parentWidget;
}

/**
 * @name    void loadDefault()
 * @details 恢复初始设置

 * @date    2018-11-15
**/
void GlobalParam::loadDefault()
{
    getFPGA()->initTempSetup();

    g_background = GlobalParam::Background::Hide;
    g_tempRangeLevel = 0;
    g_lowerLimit = -20;
    g_upperLimit = 150;

    g_spotCount = 0;
    g_areaCount = 0;
    g_lineSwitch = false;

    g_compSwitchState = false;

    //...
}

/**
 * @name    void setFPGA( TFPGA *_fpga)
 * @details 设置TFPGA对象
 * @param   _fpga TFPGA对象指针

 * @date    2018-12-18
**/
void GlobalParam::setFPGA( TFPGA *_fpga)
{
    g_fpga = _fpga;
}

/**
 * @name    void getFPGA()
 * @details 获取TFPGA对象
 * @return  TFPGA对象指针

 * @date    2018-12-18
**/
TFPGA *GlobalParam::getFPGA()
{
    if( g_fpga == NULL )
    {
        g_fpga= new TFPGA();
    }
    return g_fpga;
}

/**
 * @name    void setImageMode(int index)
 * @details 设置图像显示模式
 * @param   index   待设置图像模式的id

 * @date    2018-12-18
**/
void GlobalParam::setImageMode(int index)
{
    g_imageMode = index;
}

/**
 * @name    void getImageMode()
 * @details 获取图像显示模式
 * @return  当前图像模式的id

 * @date    2018-12-18
**/
int GlobalParam::getImageMode()
{
    return g_imageMode;
}

/**
 * @name    void setPaletteMode(int index)
 * @details 设置调色板
 * @param   index   待设置色板的id

 * @date    2018-12-18
**/
void GlobalParam::setPaletteMode(int index)
{
    g_paletteMode = index;
}

/**
 * @name    void getPaletteMode()
 * @details 获取调色板id
 * @return  当前调色板的id

 * @date    2018-12-18
**/
int GlobalParam::getPaletteMode()
{
    return g_paletteMode;
}

/**
 * @name    void setAdjustMode(int index)
 * @details 设置LEVEL/SPAN调节方式
 * @param   index   待设置色板的index
 * @author  lee
 * @date    2018-12-24
**/
void GlobalParam::setAdjustMode(int index)
{
    g_adjustMode = index;
}

/**
 * @name    int getAdjustMode()
 * @details 获取LEVEL/SPAN调节方式
 * @return  LEVEL/SPAN调节方式  0:Manual 1:Auto
 * @author  lee
 * @date    2018-12-24
**/
int GlobalParam::getAdjustMode()
{
    return g_adjustMode;
}

/**
 * @name    void setCurrentIndex(int index)
 * @details 用于设置QString类型的SlideWidget在Accept当前的Index值
 * @param   index   SlideWidget当前的Index值

 * @date    2018-12-18
**/
void GlobalParam::setCurrentIndex(int index)
{
    g_index = index;
}

/**
 * @name    void getCurrentIndex()
 * @details 用于获取QString类型的SlideWidget暂存的Index值
 * @return  暂存的Index值

 * @date    2018-12-18
**/
int GlobalParam::getCurrentIndex()
{
    return g_index;
}

/**
 * @name    void getCurrentWifiState()
 * @details 读取wifi状态,后续完善
 * @return  wifi状态 0:热点未启用 1:热点已开启

 * @date    2018-12-18
**/
int GlobalParam::getCurrentWifiState()
{
    int wifiState = -1;
    //cmd....判断wifi状态
//    connect(pro, SIGNAL(readyReadStandardOutput()),this,
//            SLOT(readFromStdOut()));
//    pro->execute("iwconfig");
//    readFromStdOut{QProcess::readAllStandardOutput()}
//    return wifiState;
    return 1;
}

/**
 * @name    void setBackground(GlobalParam::Background val)
 * @details 设置背景显示方式
 * @param   val 背景显示方式值

 * @date    2018-11-15
**/
void GlobalParam::setBackground(GlobalParam::Background val)
{
    g_background = val;
}

/**
 * @name    GlobalParam::Background getBackground()
 * @details 获取背景显示方式
 * @return  背景显示方式

 * @date    2018-11-15
**/
GlobalParam::Background GlobalParam::getBackground()
{
    return g_background;
}

/**
 * @name    void setTempRangeLevel(int val)
 * @details 设置温度档位
 * @param   val 温度档位

 * @date    2018-11-15
**/
void GlobalParam::setTempRangeLevel(int val)
{
    g_tempRangeLevel = val;
}

/**
 * @name    int getTempRangeLevel()
 * @details 获取温度档位
 * @return  温度档位

 * @date    2018-11-15
**/
int GlobalParam::getTempRangeLevel()
{
    return g_tempRangeLevel;
}

/**
 * @name    void setLowerLimit(int val)
 * @details 设置温度档位中的下限
 * @param   val 温度下限值

 * @date    2018-11-15
**/
void GlobalParam::setLowerLimit(int val)
{
    g_lowerLimit = val;
}

/**
 * @name    int getLowerLimit()
 * @details 获取温度档位中的下限
 * @return  温度档位中的下限

 * @date    2018-11-15
**/
int GlobalParam::getLowerLimit()
{
    return g_lowerLimit;
}

/**
 * @name    void setUpperLimit(int val)
 * @details 设置温度档位中的上限
 * @param   val 温度上限值

 * @date    2018-11-15
**/
void GlobalParam::setUpperLimit(int val)
{
    g_upperLimit = val;
}

/**
 * @name    int getUpperLimit()
 * @details 获取温度档位中的上限
 * @return  温度档位中的上限

 * @date    2018-11-15
**/
int GlobalParam::getUpperLimit()
{
    return g_upperLimit;
}

/**
 * @name    void setParamSettingValue(float val)
 * @details 当使用滑动窗口的修改参数时，临时保存滑动窗口的数值
 * @param   val 修改的参数值

 * @date    2018-11-15
**/
void GlobalParam::setParamSettingValue(float val)
{
    g_paramSettingValue = val;
}

/**
 * @name    float getParamSettingValue()
 * @details 获取滑动窗口的临时数值
 * @return  滑动窗口的临时数值

 * @date    2018-11-15
**/
float GlobalParam::getParamSettingValue()
{
    return g_paramSettingValue;
}

/**
 * @name    void setcompSwitchState(bool val)
 * @details 设置比较温度界面的开关状态
 * @param   val 开关状态

 * @date    2018-11-15
**/
void GlobalParam::setcompSwitchState(bool val)
{
    g_compSwitchState = val;
}

/**
 * @name    bool getcompSwitchState()
 * @details 获取比较温度界面的开关状态
 * @return  比较温度界面的开关状态

 * @date    2018-11-15
**/
bool GlobalParam::getcompSwitchState()
{
    return g_compSwitchState;
}

/**
 * @name    void addSpotCount()
 * @details 添加一个测温的Spot

 * @date    2018-11-15
**/
void GlobalParam::addSpotCount()
{
    g_spotCount++;
}

/**
 * @name    uint getSpotCount()
 * @details 获取当前的spot数量
 * @return  当前的spot数量

 * @date    2018-11-15
**/
uint GlobalParam::getSpotCount()
{
    return g_spotCount;
}

/**
 * @name    void addAreaCount()
 * @details 添加一个Area测温工具

 * @date    2018-11-15
**/
void GlobalParam::addAreaCount()
{
    g_areaCount++;
}

/**
 * @name    uint getAreaCount()
 * @details 获取当前使用的Area测温工具数量
 * @return  当前使用的Area测温工具数量

 * @date    2018-11-15
**/
uint GlobalParam::getAreaCount()
{
    return g_areaCount;
}

/**
 * @name    void setTimeZoneTemp(QString timezone)
 * @details 设置当前时区
 * @param   timezone    时区名称

 * @date    2018-11-15
**/
void GlobalParam::setTimeZoneTemp(QString timezone)
{
    g_timezoneTemp = timezone;
}

/**
 * @name    void getTimeZoneTemp()
 * @details 获取当前时区
 * @return  时区名称

 * @date    2018-11-15
**/
QString GlobalParam::getTimeZoneTemp()
{
    return g_timezoneTemp;
}

/**
 * @name    void setLengthUnit(int lengthunit)
 * @details 设置长度单位
 * @param   lengthunit  0:meter 1:foot

 * @date    2018-12-18
**/
void GlobalParam::setLengthUnit(int lengthunit)
{
    g_lengthUnit = lengthunit;
}

/**
 * @name    int getLengthUnit()
 * @details 获取当前长度单位
 * @return  0:meter 1:foot

 * @date    2018-12-18
**/
int GlobalParam::getLengthUnit()
{
    return g_lengthUnit;
}

/**
 * @name    void setTempUnit(int tempUnit)
 * @details 设置温度单位
 * @param   tempUnit  0:摄氏度 1:华氏度

 * @date    2018-12-18
**/
void GlobalParam::setTempUnit(int tempUnit)
{
    g_tempUnit = tempUnit;
}

/**
 * @name    int getTempUnit()
 * @details 获取当前温度单位
 * @return  0:摄氏度 1:华氏度

 * @date    2018-12-18
**/
int GlobalParam::getTempUnit()
{
    return g_tempUnit;
}

/**
 * @name    void setScreenSaver(QString screenSaver)
 * @details 设置屏保时间
 * @param   screenSaver 屏保时间

 * @date    2018-12-18
**/
void GlobalParam::setScreenSaver(QString screenSaver)
{
    g_screenSaver = screenSaver;
}

/**
 * @name    QString getScreenSaver()
 * @details 获取当前屏保时间
 * @return  当前屏保时间

 * @date    2018-12-18
**/
QString GlobalParam::getScreenSaver()
{
    return g_screenSaver;
}

/**
 * @name    void setPowerOff(QString poweroff)
 * @details 设置定时关机时间
 * @param  poweroff    定时关机时间

 * @date    2018-12-18
**/
void GlobalParam::setPowerOff(QString poweroff)
{
    g_powerOff = poweroff;
}

/**
 * @name    QString getScreenSaver()
 * @details 获取定时关机时间
 * @return  定时关机时间

 * @date    2018-12-18
**/
QString GlobalParam::getPowerOff()
{
    return g_powerOff;
}

/**
 * @name    void setLens(int lens)
 * @details 设置Lens
 * @param  lens

 * @date    2018-12-18
**/
void GlobalParam::setLens(int lens)
{
    g_lens = lens;
}

/**
 * @name    int getLens()
 * @details 获取Lens
 * @param   Lens

 * @date    2018-12-18
**/
int GlobalParam::getLens()
{
    return g_lens;
}

/**
 * @name    void setTVOutMode(QString str)
 * @details 设置视频输出模式
 * @param   str 视频输出模式

 * @date    2018-12-18
**/
void GlobalParam::setTVOutMode(QString str)
{
    g_tvoutMode = str;
}

/**
 * @name    QString getTVOutMode()
 * @details 获取视频输出模式
 * @return  当前视频输出模式

 * @date    2018-12-18
**/
QString GlobalParam::getTVOutMode()
{
    return g_tvoutMode;
}

/**
 * @name    void setLEDState(bool state)
 * @details 设置LED开关
 * @param   state false: off true: on

 * @date    2018-12-18
**/
void GlobalParam::setLEDState(bool state)
{
    g_ledState = state;
}

/**
 * @name    bool getLEDState()
 * @details 获取LED开启状态
 * @return  当前LED开启状态, false: off true: on

 * @date    2018-12-18
**/
bool GlobalParam::getLEDState()
{
    return g_ledState;
}

/**
 * @name    void setLaserState(bool state)
 * @details 设置激光开关
 * @param   state false: off true: on

 * @date    2018-12-18
**/
void GlobalParam::setLaserState(bool state)
{
    g_laserState = state;
}

/**
 * @name    bool getLaserState()
 * @details 获取激光开启状态
 * @return  当前激光开启状态, false: off true: on

 * @date    2018-12-18
**/
bool GlobalParam::getLaserState()
{
    return g_laserState;
}

/**
 * @name    void setUSBMode(QString str)
 * @details 设置连接USB方式
 * @param   str 连接USB方式

 * @date    2018-12-20
**/
void GlobalParam::setUSBMode(QString str)
{
    g_usbMode = str;
}

/**
 * @name    QString getUSBMode()
 * @details 获取连接USB方式
 * @return  USB连接的方式

 * @date    2018-12-20
**/
QString GlobalParam::getUSBMode()
{
    return g_usbMode;
}

/**
 * @name    void setMultifuncKey(QString str)
 * @details 设置多功能键
 * @param   str 多功能键

 * @date    2018-12-20
**/
void GlobalParam::setMultifuncKey(QString str)
{
    g_multifuncKey = str;
}

/**
 * @name    QString getMultifuncKey()
 * @details 获取多功能键
 * @return  多功能键

 * @date    2018-12-20
**/
QString GlobalParam::getMultifuncKey()
{
    return g_multifuncKey;
}



