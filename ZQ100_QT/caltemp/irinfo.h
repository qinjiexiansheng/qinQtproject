#ifndef IRINFO_H
#define IRINFO_H

#include "fpga_global.h"

class IrInfo  
{
public:
        IrInfo();

        char        lenUnit,tmpUnit; 
        bool        setTemp0(float tmp); 
        bool        setTemp4(float tmp); 
        bool        setTemp7(float tmp); 

        bool        setFocus(TempInfoTAB TempInfo);
        TempInfoTAB getFocus();

	float       readDeltaAD();
        IrTempStru  calSiteTmp(unsigned short AD);
        IrTempStru  calSiteAD(float tmp);
        short calDiffAD();

        TempInfoTAB irTempInfo;
private:
        float       deltaAD;
        bool        caldeltaAD();
};
#endif
