#ifndef __MGS_ENEMY_GRNAD_E_H__
#define __MGS_ENEMY_GRNAD_E_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"  // for CONTROL, OBJECT

void *NewGrenadeEnemy_800D203C(CONTROL *control, OBJECT *parent, int num_parent, int *arg3, int unused, SVECTOR *arg6, int type);
void NewGrenadeEnemy_800D2138(CONTROL *control, OBJECT *parent, int num_parent, int *arg3, SVECTOR *arg4, int arg5);
void NewGrenadeEnemy_800D2168(CONTROL *control, OBJECT *parent, int num_parent, int *arg3, SVECTOR *arg4, int arg5);

#endif // __MGS_ENEMY_GRNAD_E_H__
