#ifndef CALACTMP_H
#define CALACTMP_H

#include "fpga_global.h"
#include "irinfo.h"


class CalacTemp
{
public:
        static      IrInfo s_irInfo;
        CalacTemp();
        IrTempStru  irAD2Temp(unsigned short AD);
        IrTempStru  irTemp2AD(float temp);
        void setLen( int len = 7 );

        bool setTempSetup( TempSetup InTempSetup);
        TempSetup   getTempSetup();



        short addAD_filter0;
        short addAD_filter2;
private:
        TempSetup   m_irTempSetup;    
        float       m_ti;

        float       temp_ti_cal();

        float unit_out_long(float lon);
        float unit_out_temp(float tmp);
        float unit_out_mdf(float tmp);
        float unit_in_long(float lon);
        float unit_in_temp(float tmp);
        float unit_in_mdf(float tmp);

        float invReviseTemp4Dist( float dist, const float temp );
        float reviseTemp4Dist( const float dist, const float temp );
        float callNewDistCalib(const float dist, const float temp);
        float invCallNewDistCalib(float dist, const float temp);
        int m_lenNum;
        int m_len;
};
#endif
