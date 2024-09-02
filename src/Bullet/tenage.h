#ifndef _TENAGE_H_
#define _TENAGE_H_

#include "libgv/libgv.h"

// the projectile for all types of grenades

GV_ACT *NewTenage_8006A010(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model);
GV_ACT *NewTenage2_8006A100(SVECTOR *pos, SVECTOR *step, int fuse_time);
GV_ACT *NewTenage3_8006A128(SVECTOR *pos, SVECTOR *step, int fuse_time, int type, int model, int do_sound, int player_side);

#endif // _TENAGE_H_
