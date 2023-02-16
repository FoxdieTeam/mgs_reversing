#ifndef _D_BLOOD_H
#define _D_BLOOD_H

#include "libgv/libgv.h"

typedef struct _Actor_DBlood
{
    GV_ACT field_0_actor;
    int    f20;
    int    f24_state;
    int    f28;
    char   f2C_placeholder[12];
    int    f38_current_map;
} Actor_DBlood;

STATIC_ASSERT_SIZE(Actor_DBlood, 0x3c);

void d_blood_act_80072A0C(Actor_DBlood *pActor);
void d_blood_kill_null_800729AC(Actor_DBlood *pActor);

int d_blood_loader_helper_80072B24(Actor_DBlood *pActor);
int d_blood_loader_80072B38(Actor_DBlood *pActor);

Actor_DBlood * NewKetchap_80072B60(void);

#endif // _D_BLOOD_H
