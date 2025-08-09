#ifndef __MGS_ENEMY_ASIATO2_H__
#define __MGS_ENEMY_ASIATO2_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"  // for CONTROL, OBJECT

void *NewAsiato2_800DD238(MATRIX *world, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void *s01a_blink_tx_800DD60C(CONTROL *control, OBJECT *object, int arg2, int *arg3);

#endif // __MGS_ENEMY_ASIATO2_H__
