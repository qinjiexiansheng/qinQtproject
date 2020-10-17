#ifndef INITFPGA_H
#define INITFPGA_H
#include "globalclass.h"


class initFpga
{
public:
    initFpga();
    ~initFpga();
private:
    unsigned char getVsk;
    unsigned char getFid;
    unsigned char getGain;
    fpgaInterface *_FpgaInterface;
    Standardparamsetting *_Standardparamsetting;
    TabDialog* _tabDialog;

};

#endif // INITFPGA_H
