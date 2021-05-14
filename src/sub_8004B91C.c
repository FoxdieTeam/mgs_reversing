#include "mts_new.h"

extern const char   aCloseInfo[];

extern void         GV_FreeMemory_80015FD0(int*, int);

void sub_8004B91C(int arg0)
{
    mts_printf_8008BBA0(aCloseInfo);
    if (arg0 != 0)
    {
        GV_FreeMemory_80015FD0(0, arg0);
    }
}
