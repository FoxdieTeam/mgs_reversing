#ifndef _HOMING_TARGET_H_
#define _HOMING_TARGET_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "Game/control.h"

#ifdef VR_EXE
#define HOMING_TARGET_ARRAY_LENGTH 64
#else
#define HOMING_TARGET_ARRAY_LENGTH 8
#endif

typedef struct HOMING
{
    MATRIX     *matrix;
    CONTROL    *control;
    int         flag;           // alive
    int         auto_aimable;
} HOMING;

void GM_ResetHomingTargets(void);
HOMING *GM_AllocHomingTarget(MATRIX *matrix, CONTROL *control);
void GM_FreeHomingTarget(HOMING *homing);
void GM_HomingTarget1(MATRIX *matrix, int vecY, int *pRetY, int *pRetX, int mapBit);
void GM_HomingTarget2(MATRIX *matrix, int vecY, int *pRetY, int *pRetX, int mapBit, int max_dist, int min_angle);

#endif // _HOMING_TARGET_H_
