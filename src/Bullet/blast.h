#ifndef _BLAST_H_
#define _BLAST_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "actor.h"
#include "target.h"

typedef struct Target_Data
{
  SVECTOR field_0;
  SVECTOR field_8_size;
  int field_10;
  int field_14;
  int field_18;
  unsigned int field_1C;
} Target_Data;

typedef struct Actor_Blast
{
  Actor field_0_actor;
  int field_20_map_bits;
  SVECTOR field_24_vec;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  GM_Target field_3C_target;
} Actor_Blast;

#endif // _BLAST_H_
