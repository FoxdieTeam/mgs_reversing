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
  Actor field_0_scope;
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
  int field_74_alloc_0x100;
  int field_78_0x80mOff;
  int field_7C_pPrims[2];
  short field_84;
  short field_86;
  int field_88_alloc;
  int field_8C;
  int field_90_pPrims;
  int field_94;
  int field_98;
  int field_9C_flags;
} Actor_scope;

#endif // _SCOPE_H_
