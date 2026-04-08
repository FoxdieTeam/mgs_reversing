#ifndef __MGS_ENEMY_GRNAD_E_H__
#define __MGS_ENEMY_GRNAD_E_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"  // for CONTROL, OBJECT

void *NewGrenadeEnemy(CONTROL *control, OBJECT *parent, int num_parent, u_long *flags, SVECTOR *pos, int side);
void *NewGrenadeEnemy2(CONTROL *control, OBJECT *parent, int num_parent, u_long *flags, SVECTOR *pos, int side);

#endif // __MGS_ENEMY_GRNAD_E_H__
