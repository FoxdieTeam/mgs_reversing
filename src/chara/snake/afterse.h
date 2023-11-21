#ifndef _AFTERSE_H_
#define _AFTERSE_H_

#include "libgv/libgv.h"

typedef struct AfterseWork
{
  GV_ACT field_0;
  short field_20_noise;
  short field_22_count_down;
} AfterseWork;

void afterse_act_800603EC(AfterseWork* work);
AfterseWork * afterse_init_800604C0(short noise, short count_down);

#endif // _AFTERSE_H_
