#ifndef _HOMING_TARGET_H_
#define _HOMING_TARGET_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "GM_Control.h"

typedef struct Homing_Target
{
  MATRIX* field_0; // ptr
  GM_Control* field_4; // ptr
  int field_8; // alive
  int field_C_bUsed; // auto_aimable 
} Homing_Target;

#endif // _HOMING_TARGET_H_
