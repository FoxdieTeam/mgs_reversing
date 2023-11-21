#ifndef _STNGRND_H_
#define _STNGRND_H_

#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct StunGrenadeWork
{
  GV_ACT field_0;
  RECT field_20[8];
  DG_PRIM *field_60_pPrims[8];
  int field_80_array[8];
  SVECTOR field_A0_vecs[8];
  SVECTOR field_E0;
  int field_E8_alive_counter;
  int field_EC;
  int field_F0_map;
  int field_F4;
} StunGrenadeWork;

void AN_Stn_G_Sonic_80074CA4(SVECTOR *pos);
void AN_Stn_G_Center_80074D28(SVECTOR *pos);

GV_ACT *NewStanBlast_80074B5C( MATRIX *pMtx );

#endif // _STNGRND_H_
