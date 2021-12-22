

#include "idaTypes.h"

extern int  dword_800A3DB4;

int mts_8008BB60(int arg0)
{
    int ret;

    ret = dword_800A3DB4;
    dword_800A3DB4 = arg0;
    return ret;
}
