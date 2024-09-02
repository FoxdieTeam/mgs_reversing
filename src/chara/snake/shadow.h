#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"

GV_ACT *NewShadow_800602CC(CONTROL *control, OBJECT *parent, SVECTOR indices);
GV_ACT *NewShadow2_80060384(CONTROL *control, OBJECT *parent, SVECTOR indices, int **enabled);

#endif // _SHADOW_H_
