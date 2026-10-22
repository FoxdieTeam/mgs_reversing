#ifndef __MGS_OKAJIMA_LENS_FL2_H__
#define __MGS_OKAJIMA_LENS_FL2_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// VR: lens flare drifting from pos by speed each frame, lasts time frames
void *NewLensFlare2( SVECTOR *pos, SVECTOR *speed, int time );

#endif // __MGS_OKAJIMA_LENS_FL2_H__
