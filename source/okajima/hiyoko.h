#ifndef __MGS_OKAJIMA_HIYOKO_H__
#define __MGS_OKAJIMA_HIYOKO_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewHiyokoGcl(int name, int where, int argc, char **argv);
void *NewHiyoko(MATRIX *world, int arg1);

#endif // __MGS_OKAJIMA_HIYOKO_H__
