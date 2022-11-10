#ifndef _RFSIGHT_H_
#define _RFSIGHT_H_

#include "libgv/libgv.h"
#include "Thing/sight.h"

// PSG1 first person HUD

typedef Actor_Sight * (*rfsight_pfn_t)(int, int, short *, short, short *);

typedef struct _Actor_Rfsight
{
    Actor         field_0_actor;
    DVECTOR      *field_20;
    int           field_24;
    int           field_28;
    rfsight_pfn_t field_2c_pfn;
} Actor_Rfsight;

STATIC_ASSERT_SIZE(Actor_Rfsight, 0x30);

void rfsight_act_helper_80069478(int a1, GV_PAD *pPad, DVECTOR *pAxis, int dir, short sens, short max);

void rfsight_act_800696CC(Actor_Rfsight *pActor);
void rfsight_kill_80069850(Actor_Rfsight *pActor);

int  rfsight_init_helper_8006985C(Actor_Rfsight *pActor);

Actor_Rfsight * NewRifleSight_8006989C(void);
Actor_Rfsight * NewRifleSightFast_80069920(void);

#endif // _RFSIGHT_H_
