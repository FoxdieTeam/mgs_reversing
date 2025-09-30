#ifndef __MGS_CHARA_SHADOW_H__
#define __MGS_CHARA_SHADOW_H__

#include "game/game.h"

void *NewShadow(CONTROL *control, OBJECT *parent, SVECTOR indices);
void *NewShadow2(CONTROL *control, OBJECT *parent, SVECTOR indices, int **enabled);

#endif // __MGS_CHARA_SHADOW_H__
