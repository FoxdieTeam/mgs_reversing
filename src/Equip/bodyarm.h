#ifndef _BODY_ARM_H_
#define _BODY_ARM_H_

#include "actor.h"
#include "game.h"
#include "GM_Control.h"

typedef struct Actor_bodyarm
{
  Actor field_0;
  OBJECT *field_20;
} Actor_bodyarm;

Actor* bodyarm_init_80060940(GM_Control *pCtrl, OBJECT *pObj);

#endif // _BODY_ARM_H_
