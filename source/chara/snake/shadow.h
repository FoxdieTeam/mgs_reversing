#ifndef __MGS_CHARA_SHADOW_H__
#define __MGS_CHARA_SHADOW_H__

#include "game/game.h"

void *NewHumanShadow(CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units);
void *NewHumanShadow2(CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units, int **enabled);

#endif // __MGS_CHARA_SHADOW_H__
