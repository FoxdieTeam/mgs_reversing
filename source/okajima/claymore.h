#ifndef __MGS_OKAJIMA_CLAYMORE_H__
#define __MGS_OKAJIMA_CLAYMORE_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewClaymore(SVECTOR *noise_position, SVECTOR *new_field_2C, int pCnt, int param_4);

#endif // __MGS_OKAJIMA_CLAYMORE_H__
