#ifndef _CHAFGRND_H_
#define _CHAFGRND_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _ChafgrndWork
{
    GV_ACT   actor;
    int      field_20_map;
    int      field_24;
    int      field_28;
    SVECTOR  field_2c;
    SVECTOR  field_34[2][64];
    SVECTOR  field_434[2][64];
    SVECTOR  field_834[64];
    DG_PRIM *field_a34;
    int      field_a38;
    int      field_a3c;
    char     field_a40[64];
    MATRIX   field_a80;
} ChafgrndWork;

STATIC_ASSERT_SIZE(ChafgrndWork, 0xaa0);

void chafgrnd_act_80076B28(ChafgrndWork *work);
void chafgrnd_kill_8007721C(ChafgrndWork *work);

int chafgrnd_loader_80077014(ChafgrndWork *work, MATRIX *pWorld);

GV_ACT *NewChafgrnd_80077264(MATRIX *pWorld);

#endif // _CHAFGRND_H_
