#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "game/game.h"

void *NewShadow_800602CC(CONTROL *control, OBJECT *parent, SVECTOR indices);
void *NewShadow2_80060384(CONTROL *control, OBJECT *parent, SVECTOR indices, int **enabled);

#endif // _SHADOW_H_
