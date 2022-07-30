#ifndef _MINE_H_
#define _MINE_H_

#include "game.h"
#include "actor.h"
#include "GM_Control.h"

typedef struct Actor_Mine
{
  Actor field_0_actor;
  GM_Control *field_20_pCtrl;
  OBJECT *field_24_pObj;
  OBJECT field_28_obj;
  int field_4C_unit;
  int *field_50_pFlags;
  int field_54_counter;
} Actor_Mine;

STATIC_ASSERT_SIZE(Actor_Mine, 0x58);

#endif // _MINE_H