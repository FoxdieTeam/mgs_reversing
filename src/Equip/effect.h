#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "libdg/libdg.h"
#include "Game/object.h"

void EQ_ChangeTexture(const char *itemName1, const char *itemName2);
void EQ_InvisibleHead(OBJECT *object, short *n_packs, short *raise);
void EQ_VisibleHead(OBJECT *object, short *n_packs, short *raise);

#ifdef VR_EXE
void EQ_InvisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
void EQ_VisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
#endif

void EQ_InvisibleUnit2(DG_OBJS *objs, unsigned int color, int arg2);
int  EQ_VisibleUnit2(short *, char *);

#endif // _EFFECT_H_
