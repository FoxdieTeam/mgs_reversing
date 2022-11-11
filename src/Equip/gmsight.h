#ifndef _GMSIGHT_H
#define _GMSIGHT_H

// gas mask first person

#include "libgv/libgv.h"

typedef struct _Actor_gmsight
{
    Actor field_0_actor;
    int   field_20;
} Actor_gmsight;

void gmsight_act_800635BC(Actor_gmsight *pActor);
void gmsight_kill_80063644(Actor_gmsight *pActor);
int  gmsight_loader_80063650(Actor_gmsight *pActor, int unused, int unused2);

#endif // _GMSIGHT_H
