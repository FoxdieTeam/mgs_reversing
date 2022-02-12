

#include "idaTypes.h"

extern int  dword_800A3DB0;

void mts_lock_sio_8008BA64(void)
{
    dword_800A3DB0 = 0;
}
