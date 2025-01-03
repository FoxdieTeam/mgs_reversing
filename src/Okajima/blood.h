#ifndef _BLOOD_H_
#define _BLOOD_H_

#include "common.h"
#include "libgv/libgv.h"

GV_ACT *NewBlood(MATRIX *, int count);

void AN_Blood_Mist(SVECTOR *pos, SVECTOR *speed);

#endif // _BLOOD_H_
