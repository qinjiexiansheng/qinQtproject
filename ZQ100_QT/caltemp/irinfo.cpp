/** 
 *
 *  Added by huo. 2012-11-09
 *      - 修改calDiffAD(): 修改传感器温度补偿关系式
 */

#include "irinfo.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

IrInfo::IrInfo(){
	lenUnit=tmpUnit=0;//长度单位为米，温度单位为度
    	irTempInfo.tmp0=irTempInfo.tmp4=irTempInfo.tmp7=25;
    	irTempInfo.TabMaxAD = 65535;
    	irTempInfo.TabMinAD = 0;
    	irTempInfo.TabBegAD = 1000;
    	irTempInfo.TabNum   = 2;
    	irTempInfo.TabBaseTmp = 30;
    	irTempInfo.temp_ad_tab[0] = 0;
    	irTempInfo.temp_ad_tab[1] = 65535;
    	irTempInfo.temp_wtab[0]     = 0;
    	irTempInfo.temp_wtab[1]     = 1000;
}

bool	IrInfo::setFocus(TempInfoTAB TempInfo){
    	float   tmp0, tmp4, tmp7;
    	tmp0 = irTempInfo.tmp0;
    	tmp4 = irTempInfo.tmp4;
    	tmp7 = irTempInfo.tmp7;
    	memcpy(&irTempInfo,&TempInfo, sizeof(struct TempInfoTAB));
    	irTempInfo.tmp0 = tmp0;
    	irTempInfo.tmp4 = tmp4;
    	irTempInfo.tmp7 = tmp7;
    	return(caldeltaAD());
}

TempInfoTAB	IrInfo::getFocus(){   
    	TempInfoTAB i;
    	memcpy(&i,&irTempInfo, sizeof(struct TempInfoTAB));
    	return i;
}

bool	IrInfo::setTemp0(float tmp){
    	irTempInfo.tmp0 = tmp;
    	return(caldeltaAD());
}

bool	IrInfo::setTemp4(float tmp){
    	irTempInfo.tmp4 = tmp;
    	return(caldeltaAD());
}

bool	IrInfo::setTemp7(float tmp){
    	irTempInfo.tmp7 = tmp;
    	return(caldeltaAD());
}

float	IrInfo::readDeltaAD(){
    	return(deltaAD);
}

bool IrInfo::caldeltaAD(){

        unsigned short tempADL=0, tempADH=1;
        int tempL=0, tempH=1;
        if((irTempInfo.tmp4 < irTempInfo.temp_wtab[0]) || (irTempInfo.tmp4 > irTempInfo.temp_wtab[irTempInfo.TabNum-1])){
                tempL   = 30;
                tempADL = 0x8000 ;
                tempH   = irTempInfo.temp_wtab[0];
                tempADH = irTempInfo.temp_ad_tab[0];
                deltaAD = (float)(((tempADH - tempADL) * (irTempInfo.tmp4 - tempL)) / (float)(tempH - tempL)) + tempADL - 32768;
                //printf("tempH:%d tempADH:%d tmp4:%f\n",tempH, tempADH, irTempInfo.tmp4 );
                //printf("==========guobinzi deltaAD:%f\n ", deltaAD );
        }
        for(int i=0; (i < irTempInfo.TabNum)&&(i < 64); ){
                tempL   = irTempInfo.temp_wtab[i];
                tempADL = irTempInfo.temp_ad_tab[i];

                i++;

                tempH   = irTempInfo.temp_wtab[i];
                tempADH = irTempInfo.temp_ad_tab[i];

                if((irTempInfo.tmp4 >= tempL) && (irTempInfo.tmp4 <= tempH))
                        break;
        }
        deltaAD = (float)(((tempADH - tempADL) * (irTempInfo.tmp4 - tempL)) / (float)(tempH - tempL)) + tempADL - 32768;
        //printf("======[%s, %d] tmp4:%.02f ADL:%d ADH:%d tempL:%d tempH:%d deltaAD:%f\n", __FILE__, __LINE__, 
        //irTempInfo.tmp4, tempADL, tempADH, tempL, tempH, deltaAD);
        return 1;
}


extern float revise_temp_table[];

IrTempStru  IrInfo::calSiteTmp(unsigned short AD){
	
	IrTempStru      OutTmp;
	//printf("___IrInfo::calSiteTmp_OutTmp.stru:____%s  OutTmp.temp: %8f   OutTmp.AD: %u   OutTmp.AD2: %u\n",OutTmp.stru, OutTmp.temp, OutTmp.AD, OutTmp.AD2);
	unsigned short  tempADL=0, tempADH=1;
	int             tempL=0, tempH=1;
        float           _diffTempL=0, _diffTempH=1;
	OutTmp.AD = AD;

//		printf("irTempInfo.TabMaxAD  is: %d, irTempInfo.TabBegAD is: %d\n",irTempInfo.TabMaxAD, irTempInfo.TabBegAD);
	if(irTempInfo.TabBegAD > AD){
		//printf("TabBegAD > AD_____irTempInfo.TabBegAD  is: %d, AD is: %d\n",irTempInfo.TabBegAD, AD);

		tempL     = irTempInfo.temp_wtab[0];
		_diffTempL   = revise_temp_table[0];
		tempADL = irTempInfo.temp_ad_tab[0];
		tempH     = irTempInfo.temp_wtab[1];
		_diffTempH   = revise_temp_table[1];
		tempADH = irTempInfo.temp_ad_tab[1];

                strcpy(OutTmp.stru, "OK");

                goto CALCTEMP;
	}else if(irTempInfo.TabMaxAD < AD){
//		printf("irTempInfo.TabMaxAD  is: %d, AD is: %d\n",irTempInfo.TabMaxAD, AD);
		tempL     = irTempInfo.temp_wtab[irTempInfo.TabNum-2];
		_diffTempL   = revise_temp_table[irTempInfo.TabNum-2];
		tempADL = irTempInfo.temp_ad_tab[irTempInfo.TabNum-2];

		tempH     = irTempInfo.temp_wtab[irTempInfo.TabNum-1];
		_diffTempH   = revise_temp_table[irTempInfo.TabNum-1];
		tempADH = irTempInfo.temp_ad_tab[irTempInfo.TabNum-1];

                strcpy(OutTmp.stru, "OK");

                goto CALCTEMP;
	}else    
		strcpy(OutTmp.stru, "OK");
	for(int i=0;(i < irTempInfo.TabNum)&&(i<64);){
          	//printf ("[%s, %d] %s:+++++++++++iiiiiiiiiiiiiiiiiiiii", __FILE__, __LINE__, __PRETTY_FUNCTION__);
		tempL     = irTempInfo.temp_wtab[i];
		_diffTempL   = revise_temp_table[i];
		tempADL = irTempInfo.temp_ad_tab[i];
	//	printf("_______tempL:%d  _diffTempL: %d tempADL %8f\n",tempL, _diffTempL, tempADL);
		i++;

		tempH     = irTempInfo.temp_wtab[i];
		_diffTempH   = revise_temp_table[i];
		tempADH = irTempInfo.temp_ad_tab[i];
	//	printf("_______tempH:%d  _diffTempH: %d tempADH %8f\n",tempH, _diffTempH, tempADH);
	//	printf("AD:%d  tempADL: %d tempADH %8f\n",AD,tempADL,tempADH);

		if((AD >= tempADL) && (AD <= tempADH)){
			break;
		}
	}

CALCTEMP:
	OutTmp.temp = (float)(((tempH - tempL) * (AD - tempADL)) / (float)(tempADH - tempADL)) + tempL;
        OutTmp.temp = ((OutTmp.temp - _diffTempL)/(_diffTempH - _diffTempL))*(tempH - tempL) + tempL;

	return(OutTmp);
}

IrTempStru  IrInfo::calSiteAD(float tmp)
{
        IrTempStru     OutAD;
        unsigned short tempADL=0, tempADH=1;
        int            tempL=0, tempH=1;
        float          ftempAD;
        float           _diffTempL=0, _diffTempH=1;

        OutAD.temp = tmp;
        if(irTempInfo.temp_wtab[0] > tmp)
        {
               //printf ("[%s, %d] %s:+++++++++++++++ irTempInfo.temp:%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, irTempInfo.temp_wtab[0]);
               //printf ("[%s, %d] %s:++++++++++++++ tmp:%d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, tmp);
                strcpy(OutAD.stru, "<<<");
                return (OutAD);
        }
        else if(irTempInfo.temp_wtab[irTempInfo.TabNum-1] < tmp)
        {
                strcpy(OutAD.stru, ">>>");
                return (OutAD);
        }
        else    strcpy(OutAD.stru, "OK");

        for(int i=0;(i < irTempInfo.TabNum)&&(i<64);)
        {
        _diffTempL   = revise_temp_table[i];
                tempL     = irTempInfo.temp_wtab[i];
                tempADL = irTempInfo.temp_ad_tab[i];

                i++;

        _diffTempH   = revise_temp_table[i];
                tempH     = irTempInfo.temp_wtab[i];
                tempADH = irTempInfo.temp_ad_tab[i];
                if((tmp >= tempL) && (tmp <= tempH))
                        break;
        }

        float _diffTemp;
        _diffTemp = ((tmp - tempL) / (float)(tempH - tempL)) * (_diffTempH - _diffTempL) + _diffTempL;
        ftempAD = (float)(((tempADH - tempADL) * (_diffTemp - tempL)) / (float)(tempH - tempL)) + tempADL;
        OutAD.AD = (unsigned short) ftempAD;
        return(OutAD);
}

/************************************************************/
// @revise_temp_table[] extern全部变量的获取
// @irTempInfo 数据的获取
/************************************************************///peng_20171219
short IrInfo::calDiffAD(){
       float _temp=0.0;
       float _temp_sensor = irTempInfo.tmp4;

       int _filter = 0;//add by peng_20171218
       if( (0==_filter)||(2==_filter) ) {
               _temp = _temp_sensor + revise_temp_table[30];
       } else {
               _temp = _temp_sensor + 0.0008*_temp_sensor*_temp_sensor - 0.0028*_temp_sensor+0.6155+revise_temp_table[30];
       }
        //printf ("[%s, %d] %s:+++++++++++ sensor=%f\n,_temp:%f", __FILE__, __LINE__, __PRETTY_FUNCTION__,  _temp_sensor,_temp);
        //printf ("[%s, %d] %s:+++++++++++ sensor=%f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,  _temp_sensor);

        unsigned short tempADL=0, tempADH=1;
        int tempL=0, tempH=1;

        if( _temp < irTempInfo.temp_wtab[0] ) {
                tempL   = irTempInfo.temp_wtab[0];
                tempADL = irTempInfo.temp_ad_tab[0];

                tempH   = irTempInfo.temp_wtab[1];
                tempADH = irTempInfo.temp_ad_tab[1];
                goto CALDELTAAD;
        } else if( _temp > irTempInfo.temp_wtab[irTempInfo.TabNum-1] ) {
                tempL   = irTempInfo.temp_wtab[irTempInfo.TabNum-2];
                tempADL = irTempInfo.temp_ad_tab[irTempInfo.TabNum-2];

                tempH   = irTempInfo.temp_wtab[irTempInfo.TabNum-1];
                tempADH = irTempInfo.temp_ad_tab[irTempInfo.TabNum-1];
                goto CALDELTAAD;
        }

        for(int i=0; (i < irTempInfo.TabNum)&&(i < 64); ){
                tempL   = irTempInfo.temp_wtab[i];
                tempADL = irTempInfo.temp_ad_tab[i];

                i++;

                tempH   = irTempInfo.temp_wtab[i];
                tempADH = irTempInfo.temp_ad_tab[i];

                if((_temp >= tempL) && (_temp <= tempH))
                        break;
        }

CALDELTAAD:
        deltaAD = (float)(((tempADH - tempADL) * (_temp - tempL)) / (float)(tempH - tempL)) + tempADL - irTempInfo.temp_ad_tab[6];;
        return deltaAD;
}
