#ifndef _GASMASK_H_
#define _GASMASK_H_

#include "actor.h"
#include "game.h"
#include "GM_Control.h"

struct Actor_gasmask
{
  Actor field_0_actor;
  OBJECT field_20_obj;
  GM_Control *field_44_pCtrl;
  OBJECT *field_48_pParent;
  int field_4C_unit;
  int field_50_count;
  Actor *field_54_gmsight;
  short field_58_maybe_pad; // not sure if padding
  short field_5A_head_saved_packs;
  short field_5C_head_saved_raise;
  short field_5E_maybe_pad; // padding
};

Actor* gasmask_init_80060C14(GM_Control *pCtrl, OBJECT *pParent, int unit);

#endif // _GASMASK_H_
