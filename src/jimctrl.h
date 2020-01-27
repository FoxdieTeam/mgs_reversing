#ifndef JIMCTRL_H
#define JIMCTRL_H

#define array_800B9340_SIZE 6

#include "actor.h"

typedef struct
{
  short field_0;
  char field_2;
  char field_3;
} array_800B9340_child;

typedef struct
{
    Actor base;
    BYTE pad0[24];
    int field_38;
    BYTE pad1[8];
    int field_44;
} Actor_sub_80038004; //todo rename to Actor_jimctrl

void jimctrl_init_helper_clear_80037FB8(void);
void jimctrl_kill_helper_clear_80038004(Actor_sub_80038004 *pJimCtrl);
void jimctrl_kill_8003853C(Actor_sub_80038004 *pJimCtrl);
void sub_80037FE0(int index, WORD value);

#endif // JIMCTRL_H
