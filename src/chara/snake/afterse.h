#ifndef _AFTERSE_H_
#define _AFTERSE_H_

#include "libgv/libgv.h"

typedef struct Actor_afterse
{
  Actor field_0;
  short field_20_noise;
  short field_22_count_down;
} Actor_afterse;

void afterse_act_800603EC(Actor_afterse* pActor);
Actor_afterse * afterse_init_800604C0(short noise, short count_down);

#endif // _AFTERSE_H_
