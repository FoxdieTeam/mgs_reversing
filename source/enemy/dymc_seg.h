#ifndef __MGS_ENEMY_DYMC_SEG_H__
#define __MGS_ENEMY_DYMC_SEG_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewDynamicSegment(int where, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag, void **arg6);

#endif // __MGS_ENEMY_DYMC_SEG_H__
