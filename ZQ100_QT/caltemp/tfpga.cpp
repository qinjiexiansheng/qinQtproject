#include "tfpga.h"
#include <unistd.h>

#include <QDebug>
#include <QTime>

/**
 * @name    TFPGA()
 * @details TFPGA提供底层的对接函数
 * @author  lee
 * @date    2018-12-21
**/
TFPGA::TFPGA()
{
}

/**
 * @name    void init()
 * @details 初始化fpga配置
 * @author  lee
 * @date    2018-12-21
**/
void TFPGA::init()
{
    //初始化全局变量
    initTempSetup();
    //设置Caltemp类的计算参数
    setTempSetup(m_allTempSetup);

    //默认启用IR+QT的Image Mode
    fpga_imageMode_set(0);
    //默认启用Iron的调色表
    fpga_colorTable_set(0);
    //开启自动levelspan，测试用
    fpga_adjustMode_set(1);
}

/**
 * @name    void initTempSetup()
 * @details 初始化fpga配置
 * @author  lee
 * @date    2018-12-21
**/
void TFPGA::initTempSetup()
{ 
    m_allTempSetup.Emiss = 1;
    m_allTempSetup.RelHum = 0;
    m_allTempSetup.Dist = 1;
    m_allTempSetup.Tamb = 25;
    m_allTempSetup.mdf = 0;
    m_allTempSetup.Trefl = 25;
}

/**
 * @name   void setTempSetup(TempSetup setup)
 * @details 为测温计算工具安装参数
 * @author  lee
 * @date    2018-12-21
**/
void TFPGA::setTempSetup(TempSetup setup)
{
    m_calcTemp.setTempSetup(setup);
    m_allTempSetup = setup;
}

/**
 * @name   TempSetup getTempSetup()
 * @details 获取测温计算工具使用的参数
 * @return  测温计算工具使用的参数
 * @author  lee
 * @date    2018-12-21
**/
TempSetup TFPGA::getTempSetup()
{
    return m_allTempSetup;
}

/**
 * @name   int getSpotTemp(const int id, QPoint point, IrTempStru &ir, const int mod)
 * @details 获取点测温的温度
 * @param   id  测温点id
 * @param   point   测温点坐标
 * @param   ir  保存返回的温度数据
 * @param   mod 测温模式 0:Manual 1:max 2:min
 * @return  成功返回0， 失败返回-1
 * @author  lee
 * @date    2018-12-21
**/
int TFPGA::getSpotTemp(const int id, QPoint point, IrTempStru &ir, const int mod)
{
    unsigned short _ad;
    if(fpgaPointPositionSet(id, point.x(), point.y()) > 0)
    {
        if(fpgaPointAdGet(id, &_ad)< 0)
        {
            qDebug()<<"fpgaPointAdGet failed";
            return -1;
        }
    }
    else
    {
        qDebug()<<"fpgaPointPositionSet failed";
        return -1;
    }
    ir = AdToTemp(_ad);

//    qWarning("spot get ad : 0x%X", _ad);
//    qWarning("spot get temp : %f", ir.temp);

    return 0;
}

/**
 * @name   int getLineTemp(QPoint point, IrTempStru &ir)
 * @details 获取线测温的温度
 * @param   point   测温线的坐标
 * @param   ir  保存返回的温度数据
 * @return  成功返回0， 失败返回-1
 * @author  lee
 * @date    2018-12-21
**/
int TFPGA::getLineTemp(QPoint point, IrTempStru &ir)
{
    unsigned short _ad[384];
    if(fpgaLinePositionSet(point.y()) > 0)
    {
        if(fpgaLineAdGet(_ad)< 0)
        {
            qDebug()<<"fpgaLineAdGet failed";
            return -1;
        }
    }
    else
    {
        qDebug()<<"fpgaLinePositionSet failed";
        return -1;
    }
    unsigned int total = 0;
    for(int i=0; i<384; i++)
    {
        total += _ad[i];
    }
    total /= 384;

    ir = AdToTemp(total);

    qWarning("line get ad : 0x%X", _ad);
    qWarning("line get temp : %f", ir.temp);

    return 0;
}

/**
 * @name   int getAreaTemp(const int id, AreaRect &area,
                       AreaVal &areaVal, AreaTemp &area_temp)
 * @details 获取区域测温的温度
 * @param   id  测温区域id
 * @param   area 测温区域
 * @param   areaVal 保存测温区域的返回底层数据
 * @param   area_temp  保存返回的温度数据
 * @return  成功返回0， 失败返回-1
 * @author  lee
 * @date    2018-12-21
**/
int TFPGA::getAreaTemp(const int id, AreaRect &area,
                       AreaVal &areaVal, AreaTemp &area_temp)
{

    if(fpgaAreaPositionSet(id, area.xlt, area.xrb, area.ylt, area.yrb) > 0)
    {
        if(fpgaAllAreaValGet(id, &areaVal)< 0)
        {
            qDebug()<<"fpgaAllAreaValGet failed";
            return -1;
        }
    }
    else
    {
        qDebug()<<"fpgaAreaPositionSet failed";
        return -1;
    }

    area_temp._max = AdToTemp( areaVal.maxAD );
    area_temp._min = AdToTemp( areaVal.minAD );
    area_temp._averg = AdToTemp( areaVal.averAD );

//    qWarning("id:%d, max:%x, min:%x, avg:%x", id, areaVal.maxAD, areaVal.minAD, areaVal.averAD);
//    qWarning("id:%d, max:%x, min:%x, avg:%x", id, area_temp._max.temp, area_temp._min.temp, area_temp._averg.temp);

    return 0;
}

//unsigned short revise_ad_table[64]={0};
float revise_temp_table[64] = {0};
//float g_t1_1=0, g_t2_1=0, g_t1_2=0, g_t2_2=0;

/**
 * @name   IrTempStru AdToTemp(int AD)
 * @details AD值转温度
 * @return  返回转换后的温度值
 * @author  lee
 * @date    2018-12-21
**/
IrTempStru TFPGA::AdToTemp(int AD){
    char filename[100]={'\0'};
#ifdef PC
    sprintf(filename, "/home/osrc/lee/ZQ100_QT/caltemp/table-analysis.txt");
#else
    sprintf(filename, "/mnt/sd/table-analysis.txt");
#endif

    if( access( filename, 0) != 0){
        //        printf("[%s, %d] %s is no exist\n", __FILE__, __LINE__, filename);r
    }
    //printf ("[%s, %d] %s: Temp-AD: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, filename);
    TempInfoTAB  ATempInfo;
    TTable::readTable(filename, &ATempInfo);
    TTable::readReviseTempTable(filename, revise_temp_table);

    for(int i=0; i<ATempInfo.TabNum; i++) {
        if( revise_temp_table[i] == 0 ) {
            revise_temp_table[i] = ATempInfo.temp_wtab[i];
            //printf("i: %d ___________irTempInfo.TabNum: %d\n", i, ATempInfo.temp_wtab[i]);
        }
    }
#if 0
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabMaxAD);
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabMinAD);
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabBegAD);
#endif

    m_calcTemp.s_irInfo.setFocus(ATempInfo);

    IrTempStru ctemp = m_calcTemp.irAD2Temp(AD);
    return ctemp;
}

IrTempStru TFPGA::TempToAd(float temp)
{
    char filename[100]={'\0'};
#ifdef PC
    sprintf(filename, "/home/osrc/lee/ZQ100_QT/caltemp/table-analysis.txt");
#else
    sprintf(filename, "/mnt/sd/table-analysis.txt");
#endif

    if( access( filename, 0) != 0){
        //        printf("[%s, %d] %s is no exist\n", __FILE__, __LINE__, filename);r
    }
    //printf ("[%s, %d] %s: Temp-AD: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, filename);
    TempInfoTAB  ATempInfo;
    TTable::readTable(filename, &ATempInfo);
    TTable::readReviseTempTable(filename, revise_temp_table);

    for(int i=0; i<ATempInfo.TabNum; i++) {
        if( revise_temp_table[i] == 0 ) {
            revise_temp_table[i] = ATempInfo.temp_wtab[i];
            //printf("i: %d ___________irTempInfo.TabNum: %d\n", i, ATempInfo.temp_wtab[i]);
        }
    }
#if 0
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabMaxAD);
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabMinAD);
    printf(" irTempInfo.TabMaxAD: %d_____\n",ATempInfo.TabBegAD);
#endif

    m_calcTemp.s_irInfo.setFocus(ATempInfo);

    IrTempStru cad = m_calcTemp.irTemp2AD(temp);

    return cad;
}

