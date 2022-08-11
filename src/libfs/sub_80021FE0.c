#include <SYS/TYPES.H>
#include "psyq.h"

extern int dword_8009D4DC;

void sub_80021FE0(void)
{
    CdReadyCallback(0);
    CdSyncCallback(0);
    CdFlush();
    CdControl('\t', 0, 0);
    dword_8009D4DC = 0;
}
