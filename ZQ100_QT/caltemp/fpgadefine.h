#ifndef FPGADEFINE_H
#define FPGADEFINE_H

#define IMAGE_SIZE    384*288*4
#define K_IMAGE_SIZE    384*288*2
#define FPGA_CMD_READ_LINE 0
#define FPGA_SDRAM_BASE       0x3100000 //  0x1000000// 0x3100000  //2310_0000 IR
#define IMAGE_LINE_SIZE      2048     // 1024
#define K_IMAGE_LINE_SIZE      1024     // 1024
#define FPGA_IMAGE_LINE_SIZE 1024         // 1024
#define FPGA_SDRAM_K_BASE    0x3200000  //320_0000
#define FPGA_IMAGE_MODE_ADDR 0x43c30000
#define POINT_SUM            384*288
#define FPGA_IMAGE_IR_ADJUST  3
#define CONST_FRACTION  0x4000          // 2^14 power
#define FPGA_CTL_REG0 0
#define FPGA_CTL_REG1 1
#define FPGA_CTL_REG2 2
#define FPGA_CTL_REG3 3
#define FRAME_NUM    64 // 64
#define FPGA_VSK    4
#define FPGA_FID    5
#define FPGA_GAIN   6

#define IRPRO0_BASE_ADDR    0
#define IRPRO0_PARAM_OFFSET(x)   (IRPRO0_BASE_ADDR+(x))

#define MEM_IR_DEV    "/dev/fpga3"
#define MEM_BRAM_DEV  "/dev/membram"
#define IRPRO0_DEVMEN  "/dev/memirpsot"
#define OSDCTRL0_DEVMEN  "/dev/memOsdCtl"

#define PIONT_SET_ADDRESS  0x3e0
#define PIONT_GET_ADDRESS  0x300

#define LINE_SET_ADDRESS   0x3dc
#define LINE_GET_ADDRESS    0x0

#define AREA_SET_ADDRESS    0x398
#define AREA_GET_ADDRESS    0x314
#define READ_FLAG 930


struct _areaval
{
    unsigned short maxAD;
    unsigned short minAD;
    unsigned short maxX;
    unsigned short maxY;
    unsigned short minX;
    unsigned short minY;
    unsigned short averAD;
    unsigned short reserved[2];
};
typedef struct _areaval AreaVal;

#endif // FPGADEFINE_H
