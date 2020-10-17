#include "fpgaInterface.h"
#include <QObject>
#include <QDebug>
#include "color_tables.h"
#include "yuv2rgbconverter.h"
#include "utility/utility.h"
#include <QElapsedTimer>

fpgaInterface::fpgaInterface()
{

    fd_3 = open(MEM_IR_DEV, O_RDWR);
    if (fd_3 < 0)
    {
        qDebug("can't open /dev/fpga3\n");
    }

    fd_4 = open(MEM_BRAM_DEV, O_RDWR);
    if (fd_4 < 0)
    {
        qDebug("can't open /dev/membram\n");
    }

    irpro0_fd = open(IRPRO0_DEVMEN, O_RDWR);
    if (irpro0_fd < 0)
    {
        qDebug("can't open /dev/memirpost\n");
    }

    osdctrl0_fd = open(OSDCTRL0_DEVMEN, O_RDWR);
    {
        if (osdctrl0_fd < 0)
        {
            qDebug("can't open /dev/memOsdCtl\n");
        }
    }
}

fpgaInterface::~fpgaInterface()
{

}
int fpgaInterface::writeData(const int m_fd, const unsigned int addr, const void *data, const int size )
{
    if( m_fd < 0 || data == NULL ){
        //qDebug(" m_fd < 0 || data == NULL  \n");
        return -1;
    }

    int ret;
    lseek( m_fd, addr, SEEK_SET );
    ret = write( m_fd, data, size );
    if( ret < 0 )
        //qDebug("write fpga failed");
        return ret;
}

int fpgaInterface::readData(const int m_fd , const unsigned int addr, void * const data, const int size )
{
    if( m_fd < 0 || data == 0 || size == 0 ){
        //qDebug(" m_fd < 0 || data == NULL  \n");
        return -1;
    }
    int ret;
    lseek(m_fd, addr, SEEK_SET);
    ret=read(m_fd, data, size);
    if( ret < 0 )
        //qDebug("read data failed");
        return ret;
}

int fpgaInterface::fpgaGskFidSet(unsigned char vsk, unsigned char fid)
{
    unsigned int temp =0;

    temp |=fid;
    temp = temp<<8;
    temp |=vsk;
    temp = temp<<8;
    temp |=(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    return writeData(fd_3, 0, &temp, 4 );
}

int fpgaInterface::fpgaGskSet(unsigned char vsk)
{
    unsigned int temp =0;
    unsigned char fid = 0;

    readData(fd_3, 2, &fid, 1 );

    temp |=fid;
    temp = temp<<8;
    temp |=vsk;
    temp = temp<<8;
    temp |=(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    return writeData(fd_3, 0, &temp, 4 );
}
int fpgaInterface::fpgaFidSet(unsigned char fid)
{
    unsigned int temp =0;
    unsigned char vsk = 0;


    readData(fd_3, 1, &vsk, 1 );

    temp |=fid;
    temp = temp<<8;
    temp |=vsk;
    temp = temp<<8;
    temp |=(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    //qDebug("fpgaVskSet temp = 0x%x",temp);

    return writeData(fd_3, 0, &temp, 4 );
}

int fpgaInterface::fpgaGainSet(unsigned char gain)
{
    int temp = 0;
    unsigned int temp1 ;

    temp |=(1<<24);
    temp |= gain;

    readData(fd_3, 0, &temp1, 4);
    temp1 &= 0xffffff00;
    temp1 |= temp;

    writeData(fd_3, 0, &temp1, 4 );
    temp1 &=~(1<<24);
    return writeData(fd_3, 0, &temp1, 4 );
}
int fpgaInterface::fpgaDLYSet(unsigned char dly)
{

}

int fpgaInterface::fpgaLevelSet(unsigned short level)
{
    unsigned short temp = 0;
    temp = (level&0xff)<<8;
    temp |= level;
    return writeData(irpro0_fd, IRPRO0_PARAM_OFFSET(6), &temp, sizeof(unsigned short ));
}
int fpgaInterface::fpgaSpanSet(unsigned short span)
{
    unsigned short temp = 0;
    temp = (span&0xff)<<8;
    temp |= span;
    return writeData(irpro0_fd, IRPRO0_PARAM_OFFSET(4), &temp, sizeof(unsigned char ));
}

int fpgaInterface::fpgaLevelGet(unsigned short *level)
{
    unsigned char level_H, level_L;
    readData(irpro0_fd, IRPRO0_PARAM_OFFSET(0), &level_L, sizeof(unsigned char));
    readData(irpro0_fd, IRPRO0_PARAM_OFFSET(1), &level_H, sizeof(unsigned char));
    *level = (short)(((level_H<<8)|level_L));
//        qDebug("level = %X", *level);

    return 0;
}

int fpgaInterface::fpgaSpanGet(unsigned short *span)
{
    unsigned char span_H, span_L;
    readData(irpro0_fd, IRPRO0_PARAM_OFFSET(2), &span_L, sizeof(unsigned char));
    readData(irpro0_fd, IRPRO0_PARAM_OFFSET(3), &span_H, sizeof(unsigned char));
    *span = (short)(((span_H<<8)|span_L));
//        qDebug("span = %X", *span);
    return 0;
}

char fpgaInterface::fpga_imageMode_set( const int index )
{
    //        if( index > GRAYINV_T ) {
    //                //qDebug("The color index is too large.\n");
    //                return -1;
    //        }

    //       const rgb_item *_color_t = color_tables[index];
    //
    unsigned char mode;
    switch (index) {
    case 1:
        //CCD
        mode = 0x45;
        break;
    case 2:
        //Merge
        mode = 0x47;
        break;
    case 3:
        //MergePlut
        mode = 0x44;
        break;
    case 4:
        //Image Only
        mode = 0x43;
        break;
    default:
        //IR
        mode = 0x46;
        break;
    }
    qWarning("set image mode %X", mode);
    return writeData(osdctrl0_fd, 0, &mode, sizeof(unsigned char ));
}

char fpgaInterface::fpga_colorTable_set( const int index )
{
    int ret = 0;
    if( index > GRAYINV_T ) {
        //qDebug("The color index is too large.\n");
        return -1;
    }

    QElapsedTimer mstimer;
    mstimer.start();
    const rgb_item *_color_t = color_tables[index];
    {
//    unsigned int size = sizeof(color_iron_table)/sizeof(color_iron_table[0]);
//    rgb_item *getColor;

//    getColor = Utility::HSL2RGB_(_color_t, size);
////    for(int i = 0; i < size; i++)
////    {
////        qWarning("%d %d %d -> %d %d %d",
////                 _color_t[i].r, _color_t[i].g,_color_t[i].b,
////                 getColor[i].r, getColor[i].g,getColor[i].b);
////    }
//    qint64 time=mstimer.nsecsElapsed();
//    qWarning("HSL2RGB_ time: %luns", time);
    }
    if(writeData(fd_4, FPGA_COLOR_TABLE_ADDR, (unsigned char *)_color_t, 256*4) < 0)
    {
        ret = -1;
        goto RETURN_LABEL;
    };

RETURN_LABEL:
//    free(getColor);
    return ret;
}

char fpgaInterface::fpga_adjustMode_set(const int index)
{
    unsigned char mode;
    switch (index) {
    case 1:
        //Auto
        mode = 0x65;
        break;
    default:
        //Manual
        mode = 0x05;
        break;
    }
    qWarning("set adjus Mode %X", mode);

    return writeData(irpro0_fd, IRPRO0_PARAM_OFFSET(8), &mode, sizeof(unsigned char ));
}

int fpgaInterface::fpgaPointPositionSet(char id, int x, int y)
{
    int temp = 0;
    unsigned int addr =0;

    if(id > 8){
        //qDebug("fpgaPointPositioSet err id");
    }

    addr = PIONT_SET_ADDRESS + id*4;
    //qDebug("fpgaPointPositioSet addr = %d",addr);

    temp |= y;
    temp  = temp <<9;
    temp |= x;
    //qDebug("fpgaPointPositioSet temp = 0x%x",temp);
    temp |= 1<<18;

    return writeData(fd_4, addr, &temp, 4);
}
int fpgaInterface::fpgaPointAdGet(char id, unsigned short *pointAd)
{
    unsigned int addr =0;
    char flag = 0;

    //qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

        if(flag)
            break;
    }

//    qDebug("READ_FLAG flag = %d", flag);

    addr = PIONT_GET_ADDRESS + id*2;

    return readData(fd_4, addr, pointAd, 2);
}
int fpgaInterface::fpgaAllPointAdGet(unsigned short *dotAd)
{
    unsigned int addr =0;
    unsigned int temp = 0;
    char flag = 0;

    //qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

        if(flag)
            break;
    }
    //qDebug("READ_FLAG flag = %d", flag);


    return readData(fd_4, PIONT_GET_ADDRESS, dotAd, 16);
}
int fpgaInterface::fpgaLinePositionSet(int y)
{
    unsigned int temp = 0;

    temp |= y;
    temp |= 1<<9;

    return writeData(fd_4, LINE_SET_ADDRESS, &temp, 4);
}
int fpgaInterface::fpgaLineAdGet(unsigned short *lineAd)
{
    char flag = 0;

    //qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

        if(flag)
            break;
    }
    //qDebug("READ_FLAG flag = %d", flag);


    return readData(fd_4, LINE_GET_ADDRESS, lineAd, 4+0x2fc);

}

int fpgaInterface::fpgaAreaPositionSet(char id, int x1, int x2, int y1, int y2)
{
    unsigned int temp[2]={0};

    unsigned int addr;

    addr = AREA_SET_ADDRESS + id*8;

//    qDebug("fpgaAreaPositionSet addr31 = 0x%x",addr);


    temp[0] |=x2;
    temp[0] = temp[0] <<16;
    temp[0] |= x1;
//    qDebug("fpgaAreaPositionSet temp0 = 0x%x",temp[0]);

    temp[1] |= y2;
    temp[1]  = temp[1] <<16;
    temp[1] |= y1;
//    temp[1] |= 1<<18;
//    qDebug("fpgaAreaPositionSet temp1 = 0x%x",temp[1]);

    return writeData(fd_4, addr, &temp[0], 8);

}

char fpgaInterface::fpgaAllAreaValGet( char id, AreaVal *a)
{
    unsigned short _area[8];
    unsigned int addr = 0;
    char flag = 0;
    int offset  = 0;

    //qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

        if(flag)
            break;
    }

    //qDebug("READ_FLAG flag = %d", flag);


    addr = AREA_GET_ADDRESS + id*16;
    if(id % 2 == 0 && id != 0)
        addr -= 0x04;

    readData(fd_4, addr, _area, sizeof(short)*8);

//    qDebug("0x%08X: 0x%04X%04X", addr, _area[1],_area[0]);
//    qDebug("0x%08X: 0x%04X%04X", addr+0x4, _area[3],_area[2]);
//    qDebug("0x%08X: 0x%04X%04X", addr+0x8, _area[5],_area[4]);
//    qDebug("0x%08X: 0x%04X%04X", addr+0xc, _area[7],_area[6]);

    if(id % 2 == 0)
        offset = 1;
    else
        offset = 0;

    a->maxAD  = _area[0+offset];
    a->maxX   = _area[1+offset];
    a->maxY   = _area[2+offset];

    a->minAD  = _area[3+offset];
    a->minX   = _area[4+offset];
    a->minY   = _area[5+offset];

    a->averAD = _area[6+offset];

    return 0;
}

