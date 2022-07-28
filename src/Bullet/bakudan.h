#ifndef _BAKUDAN_H_
#define _BAKUDAN_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game.h"
#include "actor.h"
#include "GM_Control.h"

typedef struct Actor_bakudan
{
  Actor field_0;
  GM_Control field_20_ctrl;
  OBJECT field_9C_kmd;
  MATRIX field_C0_light_mtx;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  MATRIX *field_100_pMtx;
  SVECTOR *field_104;
  int field_108;
  int field_10C;
  unsigned short *field_110_padObj;
  int field_114;
  int field_118;
} Actor_bakudan;


#endif // _BAKUDAN_H_

