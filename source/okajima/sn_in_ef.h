#ifndef __MGS_OKAJIMA_SN_IN_EF_H__
#define __MGS_OKAJIMA_SN_IN_EF_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// VR: particle ring around Snake while he appears, ends when *done becomes 1
void *NewSnakeInEffect( MATRIX *world, int size, int *done, int map, SVECTOR *color );

#endif // __MGS_OKAJIMA_SN_IN_EF_H__
