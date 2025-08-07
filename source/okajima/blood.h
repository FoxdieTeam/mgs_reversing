#ifndef __MGS_OKAJIMA_BLOOD_H__
#define __MGS_OKAJIMA_BLOOD_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

void *NewBlood(MATRIX *, int count);

void AN_Blood_Mist(SVECTOR *pos, SVECTOR *speed);

#endif // __MGS_OKAJIMA_BLOOD_H__
