#ifndef _GGMNG_H_
#define _GGMNG_H_

#include "libgv/libgv.h"

// Goggle Manager?
// used by all items and weapons that can go first person in order to transition into their first person modes?

typedef struct Actor_gglmng
{
    GV_ACT  field_0_actor;
    int    field_20_type;
    int    field_24;
    GV_ACT *field_28_pGglsight;
} Actor_gglmng;

GV_ACT *gglmng_init_800779B8(int type);

#endif // _GGMNG_H_
