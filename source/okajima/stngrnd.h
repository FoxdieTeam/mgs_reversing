#ifndef __MGS_OKAJIMA_STNGRND_H__
#define __MGS_OKAJIMA_STNGRND_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewStanBlast( MATRIX *world );
void AN_Stn_G_Sonic( SVECTOR *pos );
void AN_Stn_G_Center( SVECTOR *pos );

#endif // __MGS_OKAJIMA_STNGRND_H__
