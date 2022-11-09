#ifndef _RFSIGHT_H_
#define _RFSIGHT_H_

//#include <SYS/TYPES.H>
//#include <LIBGTE.H>
//#include <LIBGPU.H>

#include "libgv/libgv.h"

// PSG1 first person HUD

typedef struct _Actor_Rfsight
{
    Actor field_0_actor;
    char  field_20_pad[0xc];
    void *field_2c_pfn;
} Actor_Rfsight;

STATIC_ASSERT_SIZE(Actor_Rfsight, 0x30);

void rfsight_act_800696CC(Actor_Rfsight *pActor);
void rfsight_kill_80069850(Actor_Rfsight *pActor);
int  rfsight_init_helper_8006985C(Actor_Rfsight *pActor);

Actor_Rfsight * NewRifleSight_8006989C(void);
Actor_Rfsight * NewRifleSightFast_80069920(void);

#endif // _RFSIGHT_H_
