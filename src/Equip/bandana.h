#ifndef _BANDANA_H_
#define _BANDANA_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/GM_Control.h"

typedef struct Actor_bandana
{
    Actor   field_0_actor;
    OBJECT *field_20_pParent;
    int     field_24;
    int     field_28;
} Actor_bandana;

Actor *NewBandana_80061E40(GM_Control *pCtrl, OBJECT *pParent);

#endif // _BANDANA_H_
