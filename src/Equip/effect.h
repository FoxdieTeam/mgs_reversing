#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "libdg/libdg.h"

void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);
int  EQ_VisibleUnit_80060F20(short *, char *);
void EQ_InvisibleUnit_80060E68(DG_OBJS *pObjs, unsigned int color, int arg2);
void EQ_ChangeTexture_80060CE4(const char *itemName1, const char *itemName2);

#endif // _EFFECT_H_