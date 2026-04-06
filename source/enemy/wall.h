#ifndef __MGS_ENEMY_WALL_H__
#define __MGS_ENEMY_WALL_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewWall(SVECTOR *pos, SVECTOR *dir);
void *NewWallGcl(int name, int where, int argc, char **argv);

#endif // __MGS_ENEMY_WALL_H__
