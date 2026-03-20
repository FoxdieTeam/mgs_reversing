#ifndef __MGS_GAME_HOMING_H__
#define __MGS_GAME_HOMING_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/control.h"

#ifdef VR_EXE
#define NUM_HOMING_TARGETS 64
#else
#define NUM_HOMING_TARGETS 8
#endif

typedef struct HOMING
{
    MATRIX  *world;
    CONTROL *control;
    int      flag;
    int      used;
} HOMING;

void    GM_ResetHomingTargets(void);
HOMING *GM_AllocHomingTarget(MATRIX *world, CONTROL *control);
void    GM_FreeHomingTarget(HOMING *hom);
void    GM_GetHomingTarget(MATRIX *world, int ang, int *yaw, int *pitch, int map);
void    GM_GetHomingTarget2(MATRIX *world, int ang, int *yaw, int *pitch, int map, int max_dist, int max_ang);

#endif // __MGS_GAME_HOMING_H__
