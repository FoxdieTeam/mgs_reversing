#ifndef _TENAGE_H_
#define _TENAGE_H_

#include <sys/types.h>
#include <libgte.h>
#include "libgv/libgv.h"

// the projectile for all types of grenades

GV_ACT *NewTenage(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model);
GV_ACT *NewTenage2(SVECTOR *pos, SVECTOR *step, int fuse_time);
GV_ACT *NewTenage3(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model, int do_sound, int player_side);

#endif // _TENAGE_H_
