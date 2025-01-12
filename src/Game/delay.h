#ifndef _DELAY_H_
#define _DELAY_H_

#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

GV_ACT *GM_DelayedExecCommand(int proc, GCL_ARGS *args, int time);

#endif // _DELAY_H_
