#include "fpgaInterface.h"
#include <QObject>
#include "color_tables.h"
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
}
int fpgaInterface::writeData(const int m_fd, const unsigned int addr, const void *data, const int size )
{
        if( m_fd < 0 || data == NULL ){
        qDebug(" m_fd < 0 || data == NULL  \n");
        return -1;
        }

        int ret;
        lseek( m_fd, addr, SEEK_SET );
        ret = write( m_fd, data, size );
        if( ret < 0 )
                qDebug("write fpga failed");
        return ret;
}

int fpgaInterface::readData(const int m_fd , const unsigned int addr, void * const data, const int size )
{
        if( m_fd < 0 || data == 0 || size == 0 ){
        qDebug(" m_fd < 0 || data == NULL  \n");
        return -1;
        }
        int ret;
        lseek(m_fd, addr, SEEK_SET);
        ret=read(m_fd, data, size);
        if( ret < 0 )
                qDebug("read data failed");
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
    qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    qDebug("fpgaVskSet temp = 0x%x",temp);

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
    qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    qDebug("fpgaVskSet temp = 0x%x",temp);

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
    qDebug("fpgaVskSet temp = 0x%x",temp);

    writeData(fd_3, 0, &temp, 4 );

    temp &=~(1<<25);
    qDebug("fpgaVskSet temp = 0x%x",temp);

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
int fpgaInterface::fpgaLevelSet(unsigned char level)
{

}
int fpgaInterface::fpgaSpanSet(unsigned char span)
{

}

char fpgaInterface::fpga_colorTable_set( const int index )
{
        if( index > GRAYINV_T ) {
                qDebug("The color index is too large.\n");
                return -1;
        }

       const rgb_item *_color_t = color_tables[index];
       return writeData(fd_3, FPGA_COLOR_TABLE_ADDR, (unsigned char *)_color_t, 256*4);
}

int fpgaInterface::fpgaPointPositionSet(char id, int x, int y)
{
    int temp = 0;
    unsigned int addr =0;

    if(id > 8){
        qDebug("fpgaPointPositioSet err id");
    }

    addr = PIONT_SET_ADDRESS + id*4;
    qDebug("fpgaPointPositioSet addr = %d",addr);

    temp |= y;
    temp  = temp <<9;
    temp |= x;
    qDebug("fpgaPointPositioSet temp = 0x%x",temp);
    temp |= 1<<18;

    return writeData(fd_4, addr, &temp, 4);
}
int fpgaInterface::fpgaPointAdGet(char id, unsigned short *pointAd)
{
    unsigned int addr =0;
    char flag = 0;

    qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

            if(flag)
                break;
    }

    qDebug("READ_FLAG flag = %d", flag);

    addr = PIONT_GET_ADDRESS + id*2;

    return readData(fd_4, addr, pointAd, 2);
}
int fpgaInterface::fpgaAllPointAdGet(unsigned short *dotAd)
{
    unsigned int addr =0;
    unsigned int temp = 0;
    char flag = 0;

    qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

            if(flag)
                break;
    }
    qDebug("READ_FLAG flag = %d", flag);


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

    qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

            if(flag)
                break;
    }
    qDebug("READ_FLAG flag = %d", flag);


    return readData(fd_4, LINE_GET_ADDRESS, lineAd, 768);

}

int fpgaInterface::fpgaAreaPositionSet(char id, int x1, int x2, int y1, int y2)
{
    unsigned int temp[2]={0};

    unsigned int addr = 0;

    addr = AREA_SET_ADDRESS + id*8;

    qDebug("fpgaAreaPositionSet addr31 = 0x%x",addr);


    temp[0] |=x2;
    temp[0] = temp[0] <<9;
    temp[0] |= x1;
    qDebug("fpgaAreaPositionSet temp0 = 0x%x",temp[0]);

    temp[1] |= y2;
    temp[1]  = temp[1] <<9;
    temp[1] |= y1;
    temp[1] |= 1<<18;
    qDebug("fpgaAreaPositionSet temp1 = 0x%x",temp[1]);

    return writeData(fd_4, addr, &temp[0], 8);

}
char fpgaInterface::fpgaAllAreaValGet( char id, AreaValt *a)
{
    unsigned short _area[7];
    unsigned int addr = 0;
    char flag = 0;

    qDebug("while(flag);");
    while (1) {
        flag = readData(fd_4, READ_FLAG, &flag, 1);

            if(flag)
                break;
    }

    qDebug("READ_FLAG flag = %d", flag);


    addr = AREA_GET_ADDRESS + id*16;

    readData(fd_4, addr, _area, sizeof(short)*7);

    a->maxAD  = _area[0];
    a->maxX   = _area[1];
    a->maxY   = _area[2];

    a->minAD  = _area[3];
    a->minX   = _area[4];
    a->minY   = _area[5];

    a->averAD = _area[6];

    return 0;
}

