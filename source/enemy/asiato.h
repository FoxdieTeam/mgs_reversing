#ifndef __MGS_ENEMY_ASIATO_H__
#define __MGS_ENEMY_ASIATO_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libhzd/libhzd.h"      // for HZD_HDL

// void *NewAsiatoChar(MATRIX *world, int arg1, int arg2, int arg3, int arg4);

void AsiatoPos(int idx, SVECTOR *out);
int NextAsiato(HZD_HDL *hdl, int idx, SVECTOR *svec2);
void CleanAsiato(void);
int NearAsiato(void);
int SearchNearAsiato( HZD_HDL *hzd, SVECTOR *mov, int facedir, int vision_unk, int length );
int AsiatoCheck( HZD_HDL *hzd, SVECTOR *pos );

void *NewAsiato(int name, int where, int argc, char **argv);
void *NewAsiatoKun(int name, int where, int argc, char **argv);

#endif // __MGS_ENEMY_ASIATO_H__
