#ifndef _BANDANA_H_
#define _BANDANA_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct BandanaWork
{
    GV_ACT  actor;
    OBJECT *field_20_pParent;
    int     field_24;
    int     field_28;
} BandanaWork;

void   bandana_act_80061DA0(BandanaWork *work);
GV_ACT * NewBandana_80061E40(CONTROL *pCtrl, OBJECT *pParent, int unused);

#endif // _BANDANA_H_
