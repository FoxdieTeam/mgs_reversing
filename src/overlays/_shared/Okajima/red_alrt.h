#ifndef _RED_ALRT_H_
#define _RED_ALRT_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewRedAlert_800C4DF0(int name, int where, int argc, char **argv);
void *NewRedAlert2_800C4E84(int name, int length, SVECTOR *color1, SVECTOR *color2, int arg4, int arg5);
void RedAlert_800C4F48(void);

#endif // _RED_ALRT_H_
