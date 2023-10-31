#ifndef _BODY_ARM_H_
#define _BODY_ARM_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct Actor_bodyarm
{
    GV_ACT  field_0;
    OBJECT *field_20;
} Actor_bodyarm;

GV_ACT * NewBodyarm_80060940(CONTROL *pCtrl, OBJECT *pObj, int unused);

#endif // _BODY_ARM_H_
