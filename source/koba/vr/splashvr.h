#ifndef __MGS_KOBA_VR_SPLASHVR_H__
#define __MGS_KOBA_VR_SPLASHVR_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewSplashVr(MATRIX *pos, SVECTOR *size, short n_prims, int arg3, u_short tex_id, int radius);

#endif // __MGS_KOBA_VR_SPLASHVR_H__
