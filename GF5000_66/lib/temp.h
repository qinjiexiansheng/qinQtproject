#ifndef TEMP_H
#define TEMP_H

struct IrTempStru
{
        char stru[6];
        float   temp;
        unsigned short AD;
        unsigned short AD2;
};

class TEMP
{
public:
	 TEMP();
	~TEMP();
    IrTempStru AdToTemp(int);
    void updateFile();
    void setSensor(float nSensor);
    void setGear(int nGear);
    void setDistance(float nDistance);

    void setEmiss(float nEmiss);
    void setEnvTemp(float nEnvTemp);
    void setRelHum(float nRelHum);
    void setRefTemp(float nRefTemp);
    void setCorTemp(float nCorTemp);



private:

};

#endif
