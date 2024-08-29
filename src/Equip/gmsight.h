#ifndef _GMSIGHT_H
#define _GMSIGHT_H

// gas mask first person

#include "libgv/libgv.h"

typedef struct _GasmaskSightWork
{
    GV_ACT actor;
    int   field_20;
} GasmaskSightWork;

void gmsight_act_800635BC(GasmaskSightWork *work);
void gmsight_kill_80063644(GasmaskSightWork *work);
int  gmsight_loader_80063650(GasmaskSightWork *work, int unused, int unused2);

#endif // _GMSIGHT_H
