#include "claymore.h"

extern SVECTOR stru_8009F630[4];

void claymore_800731CC(SVECTOR *param_1)
{
    DG_PutVector_8001BE48(stru_8009F630, param_1, 4); // 4 = sizeof?
}

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper2_800731F8.s") // 184 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_helper_800732B0.s")     // 180 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_helper_80073364.s")     // 300 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_80073490.s")  // 272 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_helper_800735A0.s")  // 272 bytes
#pragma INCLUDE_ASM("asm/Okajima/claymore_act_800736B0.s")            // 580 bytes

void claymore_kill_800738F4(Actor_Claymore *claymore)
{
    DG_OBJS *objs;

    if (objs = (DG_OBJS *)claymore->field_84_pPrim)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }
}

extern SVECTOR stru_8009F660;

void claymore_loader_80073930(Actor_Claymore *pActor)
{
    SVECTOR vec;

    GM_Target *pTarget = &pActor->field_3C_target;
    GM_SetTarget_8002DC74(&pActor->field_3C_target, 4, 0, &stru_8009F660);
    vec.vx = pActor->field_34.vx / 32;
    vec.vy = pActor->field_34.vy / 32;
    vec.vz = pActor->field_34.vz / 32;
    GM_Target_8002DCCC(pTarget, 0, 2, 256, 0, &vec);
    pTarget->field_44 = 5;
}

#pragma INCLUDE_ASM("asm/Okajima/claymore_loader_800739EC.s") // 416 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewClaymore_80073B8C.s")     // 548 bytes
