#ifndef FPGAINTERFACE_H
#define FPGAINTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include "fpgadefine.h"

class fpgaInterface
{
public:
    fpgaInterface();
    ~fpgaInterface();
    int writeData(const int m_fd, const unsigned int addr, const void *data, const int size );
    int readData(const int m_fd , const unsigned int addr, void * const data, const int size );
    int fpgaGskFidSet(unsigned char vsk, unsigned char fid);
    int fpgaGskSet(unsigned char vsk);
    int fpgaFidSet(unsigned char fid);
    int fpgaGainSet(unsigned char gain);
    int fpgaDLYSet(unsigned char dly);
    int fpgaLevelSet(unsigned char level);
    int fpgaSpanSet(unsigned char span);
    char fpga_colorTable_set( const int index );

    // irPost
    int fpagVideoLevelGet(unsigned short *videolevel);
    int fpgaVideoSpanGet(unsigned short *videoSpan);
    int fpgaHeadSpanGet(unsigned short *headSpan);
    int fpgaHeadLevelGet(unsigned short *headLevel);
    int fpgaRdLsSlt(unsigned char videoCtrol);


    //dot
    int fpgaPointPositionSet(char id, int x, int y);
    int fpgaPointAdGet(char id, unsigned short *pointAd);
    int fpgaAllPointAdGet(unsigned short *dotAd);

    //line
    int fpgaLinePositionSet(int y);
    int fpgaLineAdGet(unsigned short *lineAd);

    //area
    int fpgaAreaPositionSet(char id, int x1, int x2, int y1, int y2);
    char fpgaAllAreaValGet( char id, AreaValt *a);



 private:
    int fd_1;
    int fd_2;
    int fd_3;
    int fd_4;
};

#endif // FPGAINTERFACE_H
