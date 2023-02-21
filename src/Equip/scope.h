#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/GM_Control.h"
#include "map/map.h"

typedef struct Actor_scope
{
  GV_ACT field_0_scope;
  GM_Control *field_20_ctrl;
  OBJECT *field_24_pParent;
  OBJECT field_28_obj;
  short field_4C_saved_packs;
  short field_4E_saved_raise;
  map_record *field_50_pMap;
  GV_PAD *field_54_pOldPad;
  int field_58;
  short field_5C;
  short field_5E;
  short field_60;
  short field_62;
  short field_64;
  short field_66;
  short field_68;
  short field_6A;
  short field_6C;
  short field_6E;
  short field_70;
  short field_72;
  LINE_F2 *field_74_lineF2s[2];
  LINE_F4 *field_7C_lineF4s[2];
  short field_84[2];
  LINE_F3 *field_88_lineF3s[2];
  LINE_F3 *field_90_lineF3s[2];
  int field_98;
  int field_9C_flags;
} Actor_scope;

#endif // _SCOPE_H_
