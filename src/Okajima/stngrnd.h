#ifndef _STNGRND_H_
#define _STNGRND_H_

#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct Actor_StunGrenade
{
  GV_ACT field_0;
  RECT field_20;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  int field_48;
  int field_4C;
  int field_50;
  int field_54;
  int field_58;
  int field_5C;
  DG_OBJS *field_60_pObjs;
  int field_64;
  int field_68;
  int field_6C;
  int field_70;
  int field_74;
  int field_78;
  int field_7C;
  int field_80_array[8];
  SVECTOR field_A0_vecs[8];
  SVECTOR field_E0;
  int field_E8_alive_counter;
  int field_EC;
  int field_F0_map;
  int field_F4;
} Actor_StunGrenade;


void stngrnd_free_80074844(int param_1, int param_2);

#endif // _STNGRND_H_
