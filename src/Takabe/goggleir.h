#ifndef _GOGGLEIR_H
#define _GOGGLEIR_H

#include "libgv/actor.h"
#include "Game/game.h"
#include "Game/GM_Control.h"

typedef struct Actor_GoggleIr
{
  Actor field_0_actor;
  OBJECT field_20_obj;
  GM_Control *field_44_pCtrl;
  OBJECT *field_48_pParent;
  int field_4C_head_hidden;
  int field_50;
  Actor *field_54_pScn_mask;
  Actor *field_58_actor_unknown;
  int field_5C;
  int field_60;
  Actor *field_64_pGglmng;
  short field_68_savedNPacks;
  short field_6A_saved_raise;
} Actor_GoggleIr;

STATIC_ASSERT_SIZE(Actor_GoggleIr, 0x6C);

#endif // _GOGGLEIR_H
