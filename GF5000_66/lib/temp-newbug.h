#ifndef TEMP_H
#define TEMP_H

struct TempResult
{
	char mStr[6];
	float   mTemp;
	unsigned short mAd;
};

class Temp
{
public:
	//===========构造函数---Begin===============
	Temp(int nGear,const char *nFilename);
	//===========构造函数---End=================
	//===========算温---Begin===================
	TempResult adToTemp(int nAd);
	TempResult adToTemp(int nAd,float nSensor);
	//===========算温---End=====================
	//===========设置档位信息---Begin============
	void setGearInfo(int nGear,const char *nFilename);
    void setGear(int nGear);
    void setGearFilename(const char *nFilename);
	//===========设置档位信息---End==============
	//===========设置挡片补偿---Begin============
	void setSensor(float nSensor);//设置挡片温度
	//===========设置挡片补偿---End==============
	//===========设置单位---Begin================
	void setLengthUnit(bool nLengthUnit);//设置长度单位，true为米，false为英尺
	void setTempUnit(bool nTempUnit);//设置温度单位，true为摄氏，false为华氏
	//===========设置单位---End==================
	//===========设置修正参数---Begin=============
	bool setDistance(float nDistance);//设置距离
	bool setEmiss(float nEmiss);//设置辐射率
	bool setEnvTemp(float nEnvTemp);//设置环境温度
	bool setRelHum(float nRelHum);//设置相对湿度
	bool setRefTemp(float nRefTemp);//设置反射温度
	bool setCorTemp(float nCorTemp);//设置修正温度
};

#endif
