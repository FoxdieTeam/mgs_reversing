#ifndef _D_BLOOD_H
#define _D_BLOOD_H

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"


typedef struct _DBloodWork
{
    GV_ACT actor;
    int    f20;
    int    f24_state;
    int    f28;
    char   f2C_placeholder[0xC];
    int    f38_current_map;
} DBloodWork;

GV_ACT *NewKetchap_80072B60(CONTROL *pControl, OBJECT *pParent, int numParent);

#endif // _D_BLOOD_H
