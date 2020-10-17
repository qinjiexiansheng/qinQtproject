#ifndef FPGA_GLOBAL_H
#define FPGA_GLOBAL_H

struct  TempSetup
{
        float Emiss;            // 辐射    0.01 ~ 1
        float Dist;             // 距离      1 ~ 10km
        float Tamb;             // 环境 -45 ~ 125
        float Trefl;            //反射温度
        float RelHum;           // 湿度  0.01 ~ 1
        float mdf;              // 修正温度  -100 ~ 100
};

struct TempInfoTAB
{
        float               tmp0,tmp4,tmp7;                  
        unsigned short int  TabMaxAD,TabMinAD,TabBegAD;
        unsigned short int  TabNum,TabBaseTmp;
        unsigned short int  temp_ad_tab[64] ;                
        int                 temp_wtab[64]    ;               
};
extern unsigned short revise_ad_tab[64];
struct IrTempStru
{
        char stru[6];
        float   temp;
        unsigned short AD;
        unsigned short AD2;
};
#endif
