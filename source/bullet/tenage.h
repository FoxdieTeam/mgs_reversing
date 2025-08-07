#ifndef __MGS_BULLET_TENAGE_H__
#define __MGS_BULLET_TENAGE_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// 手投げ弾 (en: hand grenade)

void *NewTenage(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model);
void *NewTenage2(SVECTOR *pos, SVECTOR *step, int fuse_time);
void *NewTenage3(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model, int do_sound, int player_side);

#endif // __MGS_BULLET_TENAGE_H__
