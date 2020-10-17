#ifndef TFPGA_H
#define TFPGA_H

#include <QPoint>
#include "fpga_global.h"
#include "calactmp.h"
#include "table.h"
#include "fpgaInterface.h"

struct _area
{
    unsigned short xlt;
    unsigned short ylt;
    //unsigned char ylt;
    unsigned short xrb;
    unsigned short yrb;
    //unsigned char yrb;
};
typedef struct _area AreaRect;

typedef struct
{
    IrTempStru _max;
    IrTempStru _min;
    IrTempStru _averg;
} AreaTemp;

class TFPGA : public fpgaInterface
{
public:
    TFPGA();

    void init();
    void initTempSetup();
    void setTempSetup(TempSetup);
    TempSetup getTempSetup();

    int getSpotTemp(const int id, QPoint point, IrTempStru &ir, const int mod);
    int getLineTemp(QPoint point, IrTempStru &ir);
    int getAreaTemp(const int id, AreaRect &area,
                           AreaVal &areaVal, AreaTemp &area_temp);

    IrTempStru AdToTemp(int AD);
    IrTempStru TempToAd(float temp);


private:
    //测温计算用到的全局参数
    TempSetup m_allTempSetup;
    //测温计算工具
    CalacTemp  m_calcTemp;
};

#endif // TFPGA_H
