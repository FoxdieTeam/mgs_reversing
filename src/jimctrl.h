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
} Actor_sub_80038004;

#endif // JIMCTRL_H
