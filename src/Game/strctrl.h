#ifndef _STRCTRL_H_
#define _STRCTRL_H_

#include "libgv/libgv.h"

// TODO: might be bigger if the jimctrl actually uses this
typedef struct Actor_strctrl
{
  Actor field_0_actor;
  short field_20_state;
  short field_22_sub_state;
  short field_24;
  short field_26_flags;
  int field_28;
  int field_2C_map;
  int field_30_voxStream;
  int *field_34_pStreamData;
  int field_38_proc;
  int field_3C;
} Actor_strctrl;


#endif // _STRCTRL_H_
