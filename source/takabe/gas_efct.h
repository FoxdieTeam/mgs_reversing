#ifndef __MGS_TAKABE_GAS_EFCT_H__
#define __MGS_TAKABE_GAS_EFCT_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewGasEffectSet(int name, int where, int argc, char **argv);
void *NewGasEffect(SVECTOR *arg0, int arg1, int arg2);

#endif // __MGS_TAKABE_GAS_EFCT_H__
