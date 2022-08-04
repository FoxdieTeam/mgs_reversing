#ifndef _BODY_ARM_H_
#define _BODY_ARM_H_

#include "libgv/actor.h"
#include "Game/game.h"
#include "Game/GM_Control.h"

typedef struct Actor_bodyarm
{
  Actor field_0;
  OBJECT *field_20;
} Actor_bodyarm;

Actor* bodyarm_init_80060940(GM_Control *pCtrl, OBJECT *pObj);

#endif // _BODY_ARM_H_
