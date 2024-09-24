#ifndef _AMISSILE_H_
#define _AMISSILE_H_

#include <sys/types.h>
#include <libgte.h>
#include "libgv/libgv.h"

// Anti-Air Missile (Stinger)

GV_ACT *NewAMissile(MATRIX *world, int side);

#endif // _AMISSILE_H_
