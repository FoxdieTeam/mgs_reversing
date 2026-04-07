#ifndef __MGS_ENEMY_ASIATO2_H__
#define __MGS_ENEMY_ASIATO2_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"  // for CONTROL, OBJECT

// void *NewAsiatoChar2(MATRIX *world, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void *NewAsiato2(CONTROL *control, OBJECT *object, int arg2, int *arg3);

#endif // __MGS_ENEMY_ASIATO2_H__
