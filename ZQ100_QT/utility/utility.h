#ifndef UTILITY_H
#define UTILITY_H

#include "caltemp/color_tables.h"
#include <stdlib.h>
#include <string.h>

class Utility
{
public:
    Utility();

    static void HSL2RGB(unsigned char hh, unsigned char ss, unsigned char LL,unsigned char &rr, unsigned char &gg,
                 unsigned char &bb);
    static rgb_item * HSL2RGB_(const rgb_item *hsl_color_t, unsigned int size);
};

#endif // UTILITY_H
