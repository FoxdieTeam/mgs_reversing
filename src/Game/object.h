#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Game/game.h"

void GM_InitObjectNoRots(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
void GM_InitObject(OBJECT *obj, int model, int flag, int motion);
void GM_ActMotion(OBJECT *obj);
void GM_ActObject(OBJECT *obj);
void GM_ActObject2(OBJECT *obj);
void GM_FreeObject(OBJECT *obj);
void GM_ConfigObjectFlags(OBJECT *obj, int flags);
void GM_ConfigObjectLight(OBJECT *obj, MATRIX *light);
void GM_ConfigObjectStep(OBJECT *obj, SVECTOR *step);
void GM_ConfigObjectRoot(OBJECT *obj, OBJECT *parent_obj, int num_parent);
void GM_ConfigObjectJoint(OBJECT *obj);
void GM_ConfigObjectSlide(OBJECT *obj);
void GM_ConfigObjectAction(OBJECT *obj, int action_flag, int motion, int interp);
void GM_ConfigObjectOverride(OBJECT *obj, int a1, int motion, int interp, int a4);
int  GM_ConfigObjectMotion(OBJECT *obj, int action_flag, int motion);
int  GM_ConfigObjectModel(OBJECT_NO_ROTS *obj, int model);

#endif // _OBJECT_H_
