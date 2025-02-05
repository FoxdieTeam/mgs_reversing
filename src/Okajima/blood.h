#ifndef _BLOOD_H_
#define _BLOOD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

void *NewBlood(MATRIX *, int count);

void AN_Blood_Mist(SVECTOR *pos, SVECTOR *speed);

#endif // _BLOOD_H_
