#ifndef _GGLSIGHT_H
#define _GGLSIGHT_H

#include "actor.h"
#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

typedef struct Actor_gglsight
{
  Actor field_0_actor;
  int field_20_type;
  int field_24;
  int field_28_rgb;

  // TODO: Field types might be correct here
  short field_2C_4Array[4];
  int field_34;
  int field_38;
  int field_3C;
  // end likely wrongness

  TILE_1 field_40_tile1[2][24];
  LINE_F2 field_280_linef2[6];
  POLY_F4 field_2E0_polyF4[6];
  DR_TPAGE field_370_dr_tpage[2];
  int field_380;
} Actor_gglsight;


#endif // _GGLSIGHT_H
