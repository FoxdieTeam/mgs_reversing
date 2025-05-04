#ifndef _STNGRND_H_
#define _STNGRND_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewStanBlast( MATRIX *world );
void AN_Stn_G_Sonic( SVECTOR *pos );
void AN_Stn_G_Center( SVECTOR *pos );

#endif // _STNGRND_H_
