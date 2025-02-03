#ifndef _TENAGE_H_
#define _TENAGE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// the projectile for all types of grenades

void *NewTenage(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model);
void *NewTenage2(SVECTOR *pos, SVECTOR *step, int fuse_time);
void *NewTenage3(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model, int do_sound, int player_side);

#endif // _TENAGE_H_
