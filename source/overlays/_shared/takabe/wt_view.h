#ifndef _WT_VIEW_H_
#define _WT_VIEW_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewWaterView(int name, int where, int argc, char **argv);
void *NewWaterView2(int name, int where, SVECTOR *bounds, CVECTOR *color);

#endif // _WT_VIEW_H_
