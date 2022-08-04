#ifndef _TENAGE_H_
#define _TENAGE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/actor.h"
#include "Game/GM_Control.h"
#include "Game/object.h"

typedef struct Actor_tenage
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
  int field_100_homing_arg2;
  int field_104_count;
  SVECTOR field_108;
  int field_110;
  int field_114_homing_arg3;
  int field_118_do_sound;
  int field_11C;
  int field_120_ctrl_idx;
} Actor_tenage;


#endif // _TENAGE_H_
