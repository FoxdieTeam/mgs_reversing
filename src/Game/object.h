#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Game/game.h"

void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
void GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
void GM_ConfigObjectAction_80034CD4(OBJECT *obj, int action_flag, int motion, int interp);
void GM_ConfigObjectLight_80034C44(OBJECT *obj, MATRIX *light);
void GM_FreeObject_80034BF8(OBJECT *obj);
void GM_ActObject2_80034B88(OBJECT *obj);

#endif // _OBJECT_H_
