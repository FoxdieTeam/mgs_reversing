#ifndef _CHAFGRND_H_
#define _CHAFGRND_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Actor_Chafgrnd
{
    Actor    field_0_actor;
    char     field_20_pad[0xc];
    SVECTOR  field_2c;
    char     pad[0xa00];
    DG_OBJS *field_a34;
    char     pad2[0x4];
    int      field_a3c;
    char     pad3[0x60];
} Actor_Chafgrnd;

STATIC_ASSERT_SIZE(Actor_Chafgrnd, 0xaa0);

void chafgrnd_act_80076B28(Actor_Chafgrnd *pActor);
void chafgrnd_kill_8007721C(Actor_Chafgrnd *pActor);

int chafgrnd_loader_80077014(Actor_Chafgrnd *pActor, MATRIX *pWorld);

Actor_Chafgrnd * NewChaffGrd_80077264(MATRIX *pWorld);

#endif // _CHAFGRND_H_
