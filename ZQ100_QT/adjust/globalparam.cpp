#include "globalparam.h"
#include <QTime>
#include <QDate>
#include <QTimeZone>
#include <QDebug>

//设置初始化变量
QWidget* GlobalParam::g_parentWidget= NULL;
float GlobalParam::g_paramSettingValue = 0.00;

//Analysis
uint GlobalParam::g_spotCount = 1;
uint GlobalParam::g_areaCount = 0;
bool GlobalParam::g_lineSwitch = false;

//Analysis Setting
float GlobalParam::g_emissivity = 1.00;
float GlobalParam::g_distance = 1.0;
float GlobalParam::g_ambiTemp = 25.0;
float GlobalParam::g_reflTemp = 25.0;
float GlobalParam::g_humidity = 50;
float GlobalParam::g_offset = 0.0;
GlobalParam::Background GlobalParam::g_background = GlobalParam::Background::Hide;
int GlobalParam::g_tempRangeLevel = 0;
int GlobalParam::g_lowerLimit = -20;
int GlobalParam::g_upperLimit = 150;
bool GlobalParam::g_compSwitchState = false;

//System Setting
QString GlobalParam::g_timezoneTemp = QString(QTimeZone::systemTimeZoneId());
int GlobalParam::g_lengthUnit = 0;
int GlobalParam::g_tempUnit = 0;
QString GlobalParam::g_screenSaver = "Off";
QString GlobalParam::g_powerOff = "Off";

/**
 * @name    GlobalParam()
 * @details 构造函数
 * @author  lee
 * @date    2018-11-15
**/
GlobalParam::GlobalParam()
{

}

/**
 * @name    void loadDefault()
 * @details 恢复初始设置
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::loadDefault()
{
    g_emissivity = 1.00;
    g_distance = 1.0;
    g_ambiTemp = 25.0;
    g_reflTemp = 25.0;
    g_humidity = 50;
    g_offset = 0.0;
    g_background = GlobalParam::Background::Hide;
    g_tempRangeLevel = 0;
    g_lowerLimit = -20;
    g_upperLimit = 150;

    g_spotCount = 1;
    g_areaCount = 0;
    g_lineSwitch = false;

    g_compSwitchState = false;

    //...
}

/**
 * @name    void setEmissivity(float val)
 * @details 设置辐射率
 * @param   val 辐射值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setEmissivity(float val)
{
    g_emissivity = val;
}

/**
 * @name    float getEmissivity()
 * @details 读取辐射率
 * @return  当前辐射率
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getEmissivity()
{
    return g_emissivity;
}

/**
 * @name    void setDistance(float val)
 * @details 设置距离
 * @param   val 距离值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setDistance(float val)
{
    g_distance = val;
}

/**
 * @name    float getDistance()
 * @details 读取距离
 * @return  当前距离
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getDistance()
{
    return g_distance;
}

/**
 * @name    void setAmbiTemp(float val)
 * @details 设置环境温度
 * @param   val 环境温度值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setAmbiTemp(float val)
{
    g_ambiTemp = val;
}

/**
 * @name    float getAmbiTemp()
 * @details 读取环境温度
 * @return  当前环境温度
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getAmbiTemp()
{
    return g_ambiTemp;
}

/**
 * @name    void setReflTemp(float val)
 * @details 设置反射温度
 * @param   val 反射温度值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setReflTemp(float val)
{
    g_reflTemp = val;
}

/**
 * @name    float getReflTemp()
 * @details 读取反射温度
 * @return  当前反射温度
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getReflTemp()
{
    return g_reflTemp;
}

/**
 * @name    void setHumidity(float val)
 * @details 设置湿度
 * @param   val 湿度值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setHumidity(float val)
{
    g_humidity = val;
}

/**
 * @name    float getHumidity()
 * @details 读取湿度
 * @return  当前湿度
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getHumidity()
{
    return g_humidity;
}

/**
 * @name    void setOffset(float val)
 * @details 设置修正参数
 * @param   val 修正值
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setOffset(float val)
{
    g_offset = val;
}

/**
 * @name    float getOffset()
 * @details 获取修正参数
 * @return  当前修正值
 * @author  lee
 * @date    2018-11-15
**/
float GlobalParam::getOffset()
{
    return g_offset;
}

/**
 * @name    void setBackground(GlobalParam::Background val)
 * @details 设置背景显示方式
 * @param   val 背景显示方式值
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
 * @date    2018-11-15
**/
int GlobalParam::getUpperLimit()
{
    return g_upperLimit;
}

/**
 * @name    void setParentWidget(QWidget *widget)
 * @details 设置父窗口的指针
 * @param   widget 父窗口的指针
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParam::setParentWidget(QWidget *widget)
{
    g_parentWidget = widget;
}

/**
 * @name    QWidget *getParentWidget()
 * @details 获取父窗口的指针
 * @return  父窗口的指针
 * @author  lee
 * @date    2018-11-15
**/
QWidget *GlobalParam::getParentWidget()
{
    return g_parentWidget;
}

/**
 * @name    void setParamSettingValue(float val)
 * @details 当使用滑动窗口的修改参数时，临时保存滑动窗口的数值
 * @param   val 修改的参数值
 * @author  lee
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
 * @author  lee
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
 * @author  lee
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
 * @author  lee
 * @date    2018-11-15
**/
bool GlobalParam::getcompSwitchState()
{
    return g_compSwitchState;
}

/**
 * @name    void addSpotCount()
 * @details 添加一个测温的Spot
 * @author  lee
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
 * @author  lee
 * @date    2018-11-15
**/
uint GlobalParam::getSpotCount()
{
    return g_spotCount;
}

void GlobalParam::setTimeZoneTemp(QString timezone)
{
    g_timezoneTemp = timezone;
}

QString GlobalParam::getTimeZoneTemp()
{
    return g_timezoneTemp;
}

void GlobalParam::setLengthUnit(int lengthunit)
{
    g_lengthUnit = lengthunit;
}

int GlobalParam::getLengthUnit()
{
    return g_lengthUnit;
}

void GlobalParam::setTempUnit(int tempUnit)
{
    g_tempUnit = tempUnit;
}

int GlobalParam::getTempUnit()
{
    return g_tempUnit;
}

void GlobalParam::setScreenSaver(QString screenSaver)
{
    g_screenSaver = screenSaver;
}

QString GlobalParam::getScreenSaver()
{
    return g_screenSaver;
}

void GlobalParam::setPowerOff(QString poweroff)
{
    g_powerOff = poweroff;
}

QString GlobalParam::getPowerOff()
{
    return g_powerOff;
}

