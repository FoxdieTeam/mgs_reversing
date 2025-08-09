#ifndef __MGS_TAKABE_WT_VIEW_H__
#define __MGS_TAKABE_WT_VIEW_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewWaterView(int name, int where, int argc, char **argv);
void *NewWaterView2(int name, int where, SVECTOR *bounds, CVECTOR *color);

#endif // __MGS_TAKABE_WT_VIEW_H__
