#ifndef __MGS_TAKABE_WINDCRCL_H__
#define __MGS_TAKABE_WINDCRCL_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewWindCircle( MATRIX *world, int arg1 );
void *NewWindCircle2( MATRIX *world, int arg1, int arg2, int arg3, int time );

#endif // __MGS_TAKABE_WINDCRCL_H__
