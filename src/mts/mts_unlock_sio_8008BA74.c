

#include "idaTypes.h"

extern int  dword_800A3DB0;

int mts_unlock_sio_8008BA74(void)
{
    dword_800A3DB0 = 1;
    return 1;
}
