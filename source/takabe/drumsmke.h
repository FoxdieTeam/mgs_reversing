#ifndef __MGS_TAKABE_DRUMSMKE_H__
#define __MGS_TAKABE_DRUMSMKE_H__

#include <sys/types.h>
#include <libgte.h>

void *NewDrumSmoke(MATRIX *world, int flag, int time);
void *NewDrumSmoke2(MATRIX *world, SVECTOR *offset, int flag, int time);

#endif // __MGS_TAKABE_DRUMSMKE_H__
