#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "actor.h"
#include "game.h"
#include "GM_Control.h"

typedef struct Actor_Shadow
{
  Actor field_0_actor;
  GM_Control *field_20_ctrl;
  OBJECT *field_24_pObj;
  OBJECT field_28_obj;
  MATRIX field_4C_mtx;
  short field_6C;
  short field_6E;
  int field_70;
  short field_74;
  short field_76;
  short field_78;
  short field_7A;
  int field_7C;
  int field_80;
  int field_84;
  int field_88;
  int field_8C;
  int field_90_bEnable;
  int field_94_a4;
  int field_98_a5;
} Actor_Shadow;


#endif // _SHADOW_H_
