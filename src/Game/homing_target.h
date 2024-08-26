#ifndef _HOMING_TARGET_H_
#define _HOMING_TARGET_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "Game/control.h"

#ifndef VR_EXE

#define HOMING_TARGET_ARRAY_LENGTH 8

#else

#define HOMING_TARGET_ARRAY_LENGTH 64

#endif

typedef struct HOMING
{
    MATRIX     *field_0;       // ptr
    CONTROL *field_4;       // ptr
    int         flag;       // alive
    int         field_C_bUsed; // auto_aimable
} HOMING;

void HomingTarget_2_80032EAC(MATRIX *pMtx, int vecY, int *pRetY, int *pRetX, int mapBit, int max_dist, int min_angle);
void HomingTarget_Clear_All_80032C68();
void HomingTarget_Free_80032CFC(HOMING *pTarget);
HOMING *HomingTarget_Alloc_80032C8C(MATRIX *a1, CONTROL *a2);

#endif // _HOMING_TARGET_H_
