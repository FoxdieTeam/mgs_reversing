#ifndef __MGS_ENEMY_DYMC_SEG_H__
#define __MGS_ENEMY_DYMC_SEG_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewDynamicSegment(int where, SVECTOR *min, SVECTOR *max, int minh, int maxh, int flag, int **enable);

#endif // __MGS_ENEMY_DYMC_SEG_H__
