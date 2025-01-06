#ifndef _CLAYMORE_H_
#define _CLAYMORE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"

GV_ACT *NewClaymore(SVECTOR *noise_position, SVECTOR *new_field_2C, int pCnt, int param_4);

#endif // _CLAYMORE_H_
