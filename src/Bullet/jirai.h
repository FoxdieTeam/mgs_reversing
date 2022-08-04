#ifndef _JIRAI_H_
#define _JIRAI_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "util/idaTypes.h"
#include "libgv/actor.h"
#include "Game/object.h"
#include "Game/GM_Control.h"
#include "target.h"

typedef struct Actor_Jirai
{
  Actor field_0_actor;
  GM_Control field_20_ctrl;
  OBJECT field_9C_obj;
  MATRIX field_C0_mtx;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  GM_Target *field_100_pTarget;
  SVECTOR field_104;
  short field_10C;
  short field_10E;
  int field_110;
  int field_114;
  int field_118;
  int field_11C;
  int field_120;
  int field_124;
  int field_128;
  int field_12C;
  int field_130;
  long field_134_gcl_arg;
  int field_138_gcl;
  int field_13C_idx;
  int field_140;
  SVECTOR field_144;
  int field_14C;
  int field_150;
} Actor_Jirai;

typedef struct Jirai_unknown
{
  int field_0_ypos; // might be a short
  Actor_Jirai *field_4_pActor;
  GM_Control *field_8_pCtrl;
  GM_Target *field_C_pTarget;
} Jirai_unknown;

#endif // _JIRAI_H_
