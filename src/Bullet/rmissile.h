#ifndef _RMISSILE_H_
#define _RMISSILE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "Game/camera.h"
#include "Game/game.h"
#include "Game/target.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

// nikita missile

GV_ACT *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

#endif // _RMISSILE_H_
