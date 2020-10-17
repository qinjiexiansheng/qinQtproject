#ifndef TABLE_H
#define TABLE_H

#include "fpga_global.h"

class TTable
{
public:
	static bool readTable(const char *filename, struct TempInfoTAB* adtempInfo);
	static bool readReviseTable(const char *filename, unsigned short *revise_ad);
	static bool readReviseTempTable(const char *filename, float *revise_temp);
	static float **readReviseTemp4Dist(const char *filename, int *m, int *n);
};

#endif
