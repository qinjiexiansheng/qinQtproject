#include "calactmp.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <QDebug>

#define TempDistNum 34  

static int TempTab[107]={2,3,3,3,4,4,5,7,10,15,
                         25,34,41,48,56,61,67,74,81,89,
                         98 ,108,118,128,140,152,166,181,198,215,
                         234,254,275,299,324,353,381,413,447,484,
                         518,554,592,633,676,722,770,822,876,
                         933,994,1057,1125,1196,1271,1350,1434,1522,1614,
                         1722,1814,1922,2036,2155,2280,2411,2549,2700,2845,
                         3004,3170,3345,3528,3719,3919,4122,4337,4560,4791,
                         5031,5280,5537,5802,6076,6359,6649,6947,7253,7567,
                         7887,8214,8547,8885,9229,9577,9928,10282,10639,10996,
                         11353,11709,12062,12411,12756,13093,13422,
                        } ;

IrInfo CalacTemp::s_irInfo; 

CalacTemp::CalacTemp()
{   
    m_irTempSetup.Emiss = 1;
    m_irTempSetup.RelHum = 0;
    m_irTempSetup.Dist = 1;
    m_irTempSetup.Tamb = 25;
    m_irTempSetup.mdf = 0;
    m_irTempSetup.Trefl = 25;
    m_ti=temp_ti_cal();
    m_lenNum = 0;
    m_len = 7;
    addAD_filter0 = 0;
    addAD_filter2 = 0;
}

float CalacTemp::temp_ti_cal()
{
    float  ti,water;
    if(m_irTempSetup.Tamb<-39)
        water=2;
    else if(m_irTempSetup.Tamb>66)
        water=13422;
    else
        water=TempTab[(int)(m_irTempSetup.Tamb+39)];

    water = (water*m_irTempSetup.RelHum+11106)*m_irTempSetup.Dist/1000000000;
    if(water<0.165)
        ti=exp(-0.598*sqrt(water));
    else
        ti=0.784*pow(0.165/water,0.122);
    return(ti);
}

float CalacTemp::unit_out_long(float lon)
{
  if(s_irInfo.lenUnit)    //1 foot 英尺=12 inches 英寸=0.3048 metre 米
      //return(0.3048*lon);
      return(lon/0.3048); //Modified by will. 2013-06-27
  else
      return(lon);
}
//*********************************************
float CalacTemp::unit_out_temp(float tmp)
{
    if(s_irInfo.tmpUnit)    //?aê???±êó?é?ê???±êμ?1??μ?aF=1.8?át+32
          return(tmp*1.8 +32);
    else
          return(tmp);
}
//*********************************************
float CalacTemp::unit_out_mdf(float tmp)
{
    if(s_irInfo.tmpUnit)
          return(tmp*1.8);
    else
          return(tmp);
}
//*********************************************
float CalacTemp::unit_in_long(float lon)
{
  if(s_irInfo.lenUnit)    //1 foot ó￠3?=12 inches ó￠′?=0.3048 metre ?×
      //return(lon/0.3048);
      return(lon*0.3048);//Modified by will. 2013-06-27
  else
      return(lon);
}
//*********************************************
float CalacTemp::unit_in_temp(float tmp)
{
    if( s_irInfo.tmpUnit )    //?aê???±êó?é?ê???±êμ?1??μ?aF=1.8?át+32
            return((tmp-32)/1.8);
    else
          return(tmp);
}
//*********************************************
float CalacTemp::unit_in_mdf(float tmp)
{
    if(s_irInfo.tmpUnit)
            return(tmp/1.8);
    else
          return(tmp);
}

void CalacTemp::setLen( int len )
{
    m_len = len;
    if( len == 7 ) {
        m_lenNum = 0;
    } else if( len == 3 ) {
        m_lenNum = 2;
    } else if( len == 6 ) {
        m_lenNum = 4;
    } else if( len == 5 ) {
        m_lenNum = 6;
    } else {
        m_lenNum = 0;
    }
}

/**
 *
 * @param       dist    传入的距离
 * @param       temp    需要修正的温度
 * @return      修正后的温度值
 * @author      Tomson
 */
extern float **g_DistReviseTable;
extern int g_DistReviseTable_M;
extern int g_DistReviseTable_N;

const float func_param[TempDistNum][8] = 
{
    {0.0893, -0.1978, 0.054,  -1.0,  0.1250, -1.2, 0.4,  -0.0667},
    {0.0329,  9.81,   0.074,  8.9,   0.0725,  9.2,  0.2343,  9.9},
    {0.0042,  19.81,  0.004,  20.0,  0.0425,  19.6, 0.0457,   20},
    {-0.0671, 30,     -0.006, 30.0,  -0.025, 30.3,  -0.1543, 30.0},
    {-0.117,  40.05,  -0.008, 40.1,  -0.0475, 40.5,  -0.2429, 40.1},
    {-0.1582, 50.02,  -0.028, 50.5,  -0.0575, 50.6, -0.2971,  50.1},
    {-0.1808, 60.12,  -0.054, 60.9,  -0.0875, 60.8, -0.4057,  60.1},
    {-0.1741, 70.16,  -0.072, 71.0,  -0.1525, 71.4, -0.4771, 70.1},
    {-0.2390, 80.22,  -0.052, 80.8,  -0.14,   81.3, -0.6457, 80.2},
    {-0.2416, 90.22,  -0.02,  90.2,  -0.165,  91.5, -0.5857, 90.2},
    {-0.2984, 100.42,  -0.096,101.5, -0.21,   102.0, -0.6714, 100.2},
    {-0.3489, 120.42,  -0.13, 121.8, -0.1525, 121.5, -0.8514, 120.2},
    {-0.4129, 140.46,  -0.116, 141.8, -0.2325, 142.1, -1.2486, 140.4},


    {-0.4067,  160.67, -0.186,  162.7, -0.2325,  162.2, -1.3029,  160.4},
    {-0.6574,  180.74, -0.23,   183.4, -0.3650,  183.4, -1.38,  180.4},
    {-0.7069,  200.76, -0.336,  204.9, -0.3725,  203.6, -1.4314,  200.7},
    {-0.9269,  251.25, -0.336,  255.8, -0.485,  254.9, -1.6857,  250.9},
    {-0.9378,  301.22, -0.472,  306.9, -0.51,   304.9, -1.8629,  301.0},

    {-1.3028,  351.76, -0.472,  356.9, -0.5125,  355.3, -2.22,  351.2},
    {-1.4063,  401.17, -0.538,  407.9, -0.6875,  406.1, -2.1429,  400.8},
    {-1.7238,  501.11, -0.69,   510.2, -0.9975,  510.6, -3.1857,  501.5},
    {-2.0879,  601.47, -0.814,  611.9, -1.21,   612.5, -4.2171,  601.9},
    {-9.4,     817.2, -1.9429,  813.8, -6.85,  833.7, -19.914,  811.8},

    {-12.45,  1020.3, -2.5714, 1019.6, -6.4000,  1030.9,  -27.657, 1019.7},
    {-12.55,  1223.2, -3.0143, 1221.4, -8.0000,  1241.5,  -23.257, 1213.0},
    {-14.85,  1431.1, -4.3429, 1429.4, -7.5500,  1438.0,  -30.486, 1422.4},
    {-17.05,  1624.7, -4.1714,  1629,  -9.3000,  1647.5,  -32.314, 1621.0},
    {-19.5,   1826.7, -5.4,  1837.5,   -10.2000, 1851.8,  -35.486, 1821.3},
    {-21.9,  2028.7, -6.1429,  2041.9, -11.1000, 2055.9,  -38.686, 2020.9},
    {-24.0,  2231.0, -6.9143,  2246.7, -11.7000, 2258.8,  -41.371, 2219.7},
    {-0.4806, 140.58,  -0.128, 141.8, -0.3450, 143.5, -1.0886, 140.2},
    {-0.5349,  160.72, -0.112,  161.8, -0.3725, 163.6, -1.3000,  160.4},
    {-6.4000,  511.70, -2.3143, 516.8, -3.55,  518.7, -9.2286,  506.1},
    {-8.2000,  614.70, -2.1571, 615.6, -2.60,  613.4, -13.1140, 606.0},
};
const float tempStd[TempDistNum] = 
{
    1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 250, 300, 350, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 140, 160, 500, 600,
};
float temp4Dist[TempDistNum];

float CalacTemp::callNewDistCalib(float dist, const float temp) 
{
    if( m_len == 5 ) {
        if( dist > 10 ) {
            dist = 10;
        }
    } else {
        if( dist > 30 ) {
            dist = 30;
        }
    }
    for( int i=0; i<TempDistNum-4; i++ ) {
        temp4Dist[i] = func_param[i][m_lenNum]*dist + func_param[i][m_lenNum+1];
    }
    int _filter = 0;
    if( 1==_filter ) {
        temp4Dist[12] = func_param[30][m_lenNum]*dist + func_param[30][m_lenNum+1];
        temp4Dist[13] = func_param[31][m_lenNum]*dist + func_param[31][m_lenNum+1];
    } else if( 2==_filter ) {
        temp4Dist[20] = func_param[32][m_lenNum]*dist + func_param[32][m_lenNum+1];
        temp4Dist[21] = func_param[33][m_lenNum]*dist + func_param[33][m_lenNum+1];
    }

    int i = 0;
    for( int j=0; j<TempDistNum-5; j++ ) {
        if( (temp >= temp4Dist[j]) && (temp <= temp4Dist[j+1]) ) {
            i = j;
            break;
        }else{
            i = -1;
        }
    }

    if(i == -1 ) {
        return temp;
    }

    float _temp = (temp - temp4Dist[i])/(temp4Dist[i+1] - temp4Dist[i])*(tempStd[i+1]-tempStd[i]) + tempStd[i];
    return _temp;
}

float CalacTemp::invCallNewDistCalib(float dist, const float temp)
{
        //Added by huo 2016-10-13
        if( m_len == 5 ) {
                if( dist > 10 ) {
                        dist = 10;
                }
        } else {
                if( dist > 30 ) {
                        dist = 30;
                }
        }
        if( temp < 15 ) {
                return temp;
        }

        int i = 0;
        for( int j=0; j<TempDistNum-5; j++ ) {
                if( (temp >= tempStd[j]) && (temp <= tempStd[j+1]) ) {
                        i = j;
                        break;
                } else {
                        i = -1;
                }
        }

        if(i == -1 ) {
                return temp;
        }

        temp4Dist[i] = func_param[i][m_lenNum]*dist + func_param[i][m_lenNum+1];
        temp4Dist[i+1] = func_param[i+1][m_lenNum]*dist + func_param[i+1][m_lenNum+1];

        int _filter = 0;
        if( 1==_filter ) {  //Added by huo 2017-06-26
                temp4Dist[12] = func_param[30][m_lenNum]*dist + func_param[30][m_lenNum+1];
                temp4Dist[13] = func_param[31][m_lenNum]*dist + func_param[31][m_lenNum+1];
        } else if( 2==_filter ) {
                temp4Dist[20] = func_param[32][m_lenNum]*dist + func_param[32][m_lenNum+1];
                temp4Dist[21] = func_param[33][m_lenNum]*dist + func_param[33][m_lenNum+1];
        }

        float _temp = (temp - tempStd[i])/(tempStd[i+1] - tempStd[i])*(temp4Dist[i+1]-temp4Dist[i]) + temp4Dist[i];
        //printf ("[%s, %d] %s: out temp:%f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, _temp );
        return _temp;
}

IrTempStru  CalacTemp::irAD2Temp(unsigned short AD)
{
    IrTempStru     OutTmp;
    unsigned short tempAD_mid;
    short tempAD_mid_tmp;
    float          tempOut;

    short diffAD_filter2 = 0;
    int _filter = 0;//第一档测温add by peng_20171218
    tempAD_mid_tmp = AD;

    if(0 == _filter) {//第一档测温
        tempAD_mid_tmp += 0;//addAD_filter0 测温规律的AD补偿(D300、HM460一般电路部门提供)
    }
    if(2 == _filter) {//第三档测温
        tempAD_mid_tmp += addAD_filter2;

    }

    tempAD_mid = tempAD_mid_tmp;
    //printf("Input__[FILE:%s LINE:%d]___OutTmp.stru: %s  OutTmp.temp: %8f   OutTmp.AD: %u   OutTmp.AD2: %u\n\n", __FILE__, __LINE__, OutTmp.stru, OutTmp.temp, OutTmp.AD, OutTmp.AD2);
    OutTmp = s_irInfo.calSiteTmp(tempAD_mid);
    //printf("Output__[FILE:%s LINE:%d]___OutTmp.stru: %s  OutTmp.temp: %8f   OutTmp.AD: %u   OutTmp.AD2: %u\n\n", __FILE__, __LINE__, OutTmp.stru, OutTmp.temp, OutTmp.AD, OutTmp.AD2);
    OutTmp.AD = AD;
    if(strcmp(OutTmp.stru,"OK") == 0){
        //printf("Pow Function__[FILE:%s LINE:%d___Run the pow function of caculate temp.\n\n",__FILE__,__LINE__);
        tempOut=(pow(OutTmp.temp+273.15,4)-(1-m_ti)*pow(m_irTempSetup.Tamb+273.15,4)-(1-m_irTempSetup.Emiss)*m_ti*pow(m_irTempSetup.Trefl+273.15,4))/(m_irTempSetup.Emiss*m_ti);
        if(tempOut<0){
            strcpy(OutTmp.stru,"Err");
            //printf("1111\n");
            return(OutTmp);
        }else{
            tempOut=pow(tempOut,0.25)-273.15;
            if(tempOut<-60){
                strcpy(OutTmp.stru,"Min");
                //printf("222\n");
                return(OutTmp);
            }else if(tempOut>4000){
                strcpy(OutTmp.stru,"Max");
                //printf("3333\n");
                return(OutTmp);
            }
        }
    }
    tempOut = CalacTemp::reviseTemp4Dist(m_irTempSetup.Dist, tempOut);
    tempOut += m_irTempSetup.mdf;
    OutTmp.temp = unit_out_temp(tempOut);
    return(OutTmp);
}

IrTempStru  CalacTemp::irTemp2AD(float temp)
{
    IrTempStru     OutAD;
    //unsigned short tempAD_mid;
    float             tmp;

    tmp   = unit_in_temp(temp);
    tmp = CalacTemp::invReviseTemp4Dist(m_irTempSetup.Dist, tmp);  //Added by huo   2012-04-20
    if(tmp<-60)
    {
        strcpy(OutAD.stru,"Min");
        OutAD.temp = temp;
        return(OutAD);
    }
    else if(tmp>4000)
    {
        strcpy(OutAD.stru,"Max");
        OutAD.temp = temp;
        return(OutAD);
    }
    tmp   = tmp +273.15 - m_irTempSetup.mdf;
    tmp   = pow(tmp,4)*m_ti*m_irTempSetup.Emiss+(1-m_irTempSetup.Emiss)*m_ti*pow(m_irTempSetup.Trefl+273.15,4)+(1-m_ti)*pow(m_irTempSetup.Tamb+273.15,4);
    tmp   = pow(tmp,0.25) - 273.15;

    OutAD  = s_irInfo.calSiteAD(tmp);
    OutAD.temp = temp;
    if(strcmp(OutAD.stru,"OK") == 0) {
        short AD_tmp = OutAD.AD;//Added by huo 2011-11-16
//        qDebug()<<s_irInfo.calDiffAD();
//        AD_tmp -= s_irInfo.calDiffAD();//Added by huo 2011-11-16
        int _filter =  0;
        if(0 == _filter) { //Added by huo 2017-05-09
            AD_tmp -= addAD_filter0;
        }
        if(2 == _filter) {
            AD_tmp -= addAD_filter2;
        }
        OutAD.AD = AD_tmp; //Added by huo 2011-11-16
        //OutAD.AD -= s_irInfo.calDiffAD();//Commented by huo 2011-11-16
        //printf ("[%s, %d] %s: temp:%.2f 0x%X\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, tmp, OutAD.AD);
    }
    return(OutAD);
}


float CalacTemp::invReviseTemp4Dist( float dist, const float temp )
{
        //Added by huo 2016-10-13
        if( m_len == 5 ) {
                if( dist > 10 ) {
                        dist = 10;
                }
        } else {
                if( dist > 30 ) {
                        dist = 30;
                }
        }
        //End added
        //printf ("[%s, %d] %s+++++++: dist:%f,in temp:%f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,dist, temp );
       if( temp > 15 ) {
               int _filter = 0;
               float _distMin = 1, _distMax = 13;
               if( 7 == m_len ) {
                       _distMin = 1;
                       _distMax = 10;
               } else if( 6 == m_len ) {
                       _distMin = 3;
                       _distMax = 10;
               } else if( 5 == m_len ) {
                       _distMin = 0.5;
                       _distMax = 3;
               } else if( 3 == m_len ) {
                       _distMin = 5;
                       _distMax = 15;
               }
               if( dist <= _distMin ) {
                       return temp;
               } else if( dist > _distMax || _filter ) {
                       return invCallNewDistCalib(dist, temp);
               }

       }

        if( dist < 0 || g_DistReviseTable_M == 0 || g_DistReviseTable_N == 0 )
                return temp;

        float _low=0, _high=1;
        // 找到适合的距离
        int i=0;
        while( i < (g_DistReviseTable_N-1) ) {
                _low = g_DistReviseTable[0][i];
                i++;
                _high = g_DistReviseTable[0][i];

                if( dist >= _low && dist <= _high )
                        break;
        }

        // 计算当前距离下的温度值
        float _temp[g_DistReviseTable_M];
        float k = (dist - g_DistReviseTable[0][i-1])/(g_DistReviseTable[0][i] - g_DistReviseTable[0][i-1]);
        for( int j=1; j<g_DistReviseTable_M; j++ ) {
                _temp[j] = (g_DistReviseTable[j][i] - g_DistReviseTable[j][i-1])*k + g_DistReviseTable[j][i-1];
                //printf ("==========[%s, %d] %s: i-1:%f i:%f, t:%f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__,
                                //g_DistReviseTable[j][i-1], g_DistReviseTable[j][i], _temp[j]);
        }
// 计算温度
        if( temp < g_DistReviseTable[1][0] ) {
                _low = g_DistReviseTable[1][0];
                _high = g_DistReviseTable[2][0];
                i = 2;
                //printf("==========[%s, %d] i:%d low:%f,high:%f\n", __FILE__, __LINE__,i,_low,_high);
        } else if( temp > g_DistReviseTable[g_DistReviseTable_M-1][0]){
                return invCallNewDistCalib(dist, temp);  //Added by huo 2013-01-15
                _low = g_DistReviseTable[g_DistReviseTable_M-2][0];
                _high = g_DistReviseTable[g_DistReviseTable_M-1][0];
                i = g_DistReviseTable_M-1;
        } else {

                // 计算温度
                i=1;
                while( i < (g_DistReviseTable_M-1) ) {
                        _low = g_DistReviseTable[i][0];
                        i++;
                        _high = g_DistReviseTable[i][0];
                        if( temp >= _low && temp <= _high )
                                break;
                }
        }
        //printf ("[%s, %d] %s: temp:%f i:%d i-1:%f i:%f low:%f high:%f\n",__FILE__,__LINE__,__PRETTY_FUNCTION__
        //                ,temp, i ,_low, _high, g_DistReviseTable[i-1][0], g_DistReviseTable[i][0]);
        k = ( temp - _low )/(_high - _low );
        float _t;

        //printf("==========[%s, %d] i:%d low:%f,high:%f,k:%f\n", __FILE__, __LINE__,i,_low,_high,k);
        _t = ( _temp[i] - _temp[i-1] ) * k + _temp[i-1];
        //printf ("[%s, %d] %s++++++++++out temp:%f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, _t );

        return _t;
}

float CalacTemp::reviseTemp4Dist( float dist, const float temp )
{
    if( m_len == 5 ) {
        if( dist > 10 ) {
            dist = 10;
        }
    }else{
        if( dist > 30 ) {
            dist = 30;
        }
    }
    if( temp > 15 ) {
        int _filter = 0;
        float _distMin = 1, _distMax = 10;
        if( 7 == m_len ) {
            _distMin = 1;
            _distMax = 10;
        } else if( 6 == m_len ) {
            if(2==_filter) {
                _distMin = 5;
                _distMax = 8;
            } else {
                _distMin = 10;
                _distMax = 18;
            }
        } else if( 5 == m_len ) {
            _distMin = 0.5;
            _distMax = 3;
        } else if( 3 == m_len ) {
            if( 2==_filter ) {
                _distMin = 7;
                _distMax = 12;
            } else {
                _distMin = 15;
                _distMax = 30;
            }
        }
        if( dist <= _distMin ) {
            return temp;
        } else if( dist > _distMax || _filter ) {
            return callNewDistCalib(dist, temp);
        }
    }

    if( dist < 0 || g_DistReviseTable_M == 0 || g_DistReviseTable_N == 0 )
        return temp;

    float _low=0, _high=1;
    // 找到适合的距离
    int i=0;
    while( i < (g_DistReviseTable_N-1) ) {
        _low = g_DistReviseTable[0][i];
        i++;
        _high = g_DistReviseTable[0][i];

        if( dist >= _low && dist <= _high )
            break;
    }

    // 计算当前距离下的温度值
    float _temp[g_DistReviseTable_M];
    float k = (dist - g_DistReviseTable[0][i-1])/(g_DistReviseTable[0][i] - g_DistReviseTable[0][i-1]);
    for( int j=1; j<g_DistReviseTable_M; j++ ) {
        _temp[j] = (g_DistReviseTable[j][i] - g_DistReviseTable[j][i-1])*k + g_DistReviseTable[j][i-1];
    }
    if( temp < _temp[1] ) {
        _low = _temp[1];
        _high = _temp[2];
        i = 2;
    } else if( temp > _temp[g_DistReviseTable_M-1]){
        return callNewDistCalib(dist, temp); //距离修正
        _low = _temp[g_DistReviseTable_M-2];
        _high = _temp[g_DistReviseTable_M-1];
        i = g_DistReviseTable_M-1;
    } else {
        i=1;
        while( i < (g_DistReviseTable_M-1) ) {
            _low = _temp[i];
            i++;
            _high = _temp[i];
            if( temp >= _low && temp <= _high )
                break;
        }
    }
    k = ( temp - _low )/(_high - _low );
    float _t;

    _t = ( g_DistReviseTable[i][0] - g_DistReviseTable[i-1][0] ) * k + g_DistReviseTable[i-1][0];

    return _t;
}

TempSetup   CalacTemp::getTempSetup()
{
    TempSetup OutTempSetup;
    OutTempSetup.Emiss  = m_irTempSetup.Emiss;
    OutTempSetup.RelHum = m_irTempSetup.RelHum;
    OutTempSetup.Dist   = unit_out_long(m_irTempSetup.Dist);
    OutTempSetup.Tamb   = unit_out_temp(m_irTempSetup.Tamb);
    OutTempSetup.Trefl   = unit_out_temp(m_irTempSetup.Trefl);
    OutTempSetup.mdf    = unit_out_mdf(m_irTempSetup.mdf);
    return(OutTempSetup);
}

bool CalacTemp::setTempSetup( TempSetup InTempSetup)
{
    if((InTempSetup.Emiss < 0.009) || (InTempSetup.Emiss > 1.001) )      return(0);
    if((InTempSetup.RelHum < 0.009) || (InTempSetup.RelHum > 1.001) )    return(0);
    if((unit_in_long(InTempSetup.Dist) < 0) || (unit_in_long(InTempSetup.Dist) > 100000) )           return(0);
    if((unit_in_temp(InTempSetup.Tamb) < -40.001) || (unit_in_temp(InTempSetup.Tamb) > 125.001) )    return(0);
    if((unit_in_mdf(InTempSetup.mdf) < -100.001) || (unit_in_mdf(InTempSetup.mdf) > 100.001) )       return(0);
    if((unit_in_temp(InTempSetup.Trefl) < -80.001) || (unit_in_temp(InTempSetup.Trefl) > 3000.001) )    return(0);

    //if( InTempSetup.Emiss != m_irTempSetup.Emiss ||InTempSetup.RelHum != m_irTempSetup.RelHum
    //|| InTempSetup.Dist != m_irTempSetup.Dist || InTempSetup.Tamb != m_irTempSetup.Tamb || InTempSetup.mdf != m_irTempSetup.mdf || InTempSetup.Trefl != m_irTempSetup.Trefl )
    if( InTempSetup.Emiss != m_irTempSetup.Emiss ||InTempSetup.RelHum != m_irTempSetup.RelHum
            || unit_in_long(InTempSetup.Dist) != m_irTempSetup.Dist || unit_in_temp(InTempSetup.Tamb) != m_irTempSetup.Tamb || unit_in_temp(InTempSetup.mdf) != m_irTempSetup.mdf || unit_in_temp(InTempSetup.Trefl) != m_irTempSetup.Trefl )
    {
        //printf("======= set tempsetup\n");

        m_irTempSetup.Emiss  = InTempSetup.Emiss;
        m_irTempSetup.RelHum = InTempSetup.RelHum;
        m_irTempSetup.Dist   = unit_in_long(InTempSetup.Dist);
        m_irTempSetup.Tamb   = unit_in_temp(InTempSetup.Tamb);


        //qDebug()<<"<<<"<<InTempSetup.Tamb;

        m_irTempSetup.Trefl   = unit_in_temp(InTempSetup.Trefl);
        m_irTempSetup.mdf       = unit_in_mdf(InTempSetup.mdf);
        m_ti=temp_ti_cal();
        //printf("============= 357 m_ti=%f\n", m_ti);

        //printf ("[%s, %d] m_ti:%f,Tamb:%1f, Emiss:%2f,Trefl:%1f,Dist:%f,RelHum:%f,mdf:%f\n", __FILE__, __LINE__, m_ti, m_irTempSetup.Tamb,m_irTempSetup.Emiss,m_irTempSetup.Trefl,m_irTempSetup.Dist,m_irTempSetup.RelHum,m_irTempSetup.mdf );
        //printf ("[%s, %d] m_ti:%f,Tamb:%1f, Emiss:%2f,Trefl:%1f,Dist:%f,RelHum:%f,mdf:%f\n", __FILE__, __LINE__, m_ti, unit_in_temp(InTempSetup.Tamb),InTempSetup.Emiss,unit_in_temp(InTempSetup.Trefl), unit_in_long(InTempSetup.Dist),InTempSetup.RelHum,unit_in_mdf(InTempSetup.mdf));
        return(1);
    }
    return true;
}

