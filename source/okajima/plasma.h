#ifndef __MGS_OKAJIMA_PLASMA_H__
#define __MGS_OKAJIMA_PLASMA_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"  // for OBJECT

void *NewPlasma_800CD110(int name, int where);
void *NewPlasma_800CD1A4(OBJECT *parent, int arg1, int arg2, int arg3, int arg4, int arg5);
void *NewPlasma_800CD268(SVECTOR *arg0, SVECTOR *arg1, int arg2);
void *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, int arg3);

#endif // __MGS_OKAJIMA_PLASMA_H__
