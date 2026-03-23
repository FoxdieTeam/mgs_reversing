#ifndef __MGS_OKAJIMA_SPLASH2_H__
#define __MGS_OKAJIMA_SPLASH2_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewSplash2_800DB424( MATRIX *matrix, int noripple, int r, int g, int b );
void NewSplash2_800DB4E0(int angy, SVECTOR *pos, int noripple);
void NewSplash2_800DB5E4(SVECTOR *ang, SVECTOR *pos);
void NewSplash2_800DB6F0(int angy, SVECTOR *pos, int noripple);

#endif // __MGS_OKAJIMA_SPLASH2_H__
