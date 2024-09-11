#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "libdg/libdg.h"

void EQ_ChangeTexture_80060CE4(const char *itemName1, const char *itemName2);
void EQ_InvisibleHead_80060D5C(OBJECT *object, short *n_packs, short *raise);
void EQ_VisibleHead_80060DF0(OBJECT *object, short *n_packs, short *raise);
int  EQ_VisibleUnit2_80060F20(short *, char *);
void EQ_InvisibleUnit2_80060E68(DG_OBJS *objs, unsigned int color, int arg2);

#endif // _EFFECT_H_
