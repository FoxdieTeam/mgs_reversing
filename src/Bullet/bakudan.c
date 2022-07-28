#include "bakudan.h"

extern const char aBakudanC[];

#pragma INCLUDE_ASM("asm/Bullet/bakudan_act_8006A218.s")
#pragma INCLUDE_ASM("asm/Bullet/bakudan_kill_8006A4A4.s")
#pragma INCLUDE_ASM("asm/Bullet/bakudan_8006A510.s")
#pragma INCLUDE_ASM("asm/Bullet/bakudan_8006A54C.s")

void bakudan_act_8006A218(Actor_bakudan* pActor);
void bakudan_kill_8006A4A4(Actor_bakudan* pActor);
int bakudan_8006A54C(Actor_bakudan *pActor, MATRIX *pMatrix, SVECTOR *pVec, int a4, GM_Target *pTarget);

extern int used_counter_8009F42C;

Actor* NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, GM_Target *pTarget)
{
    Actor_bakudan *pActor; // $s0

    if ( used_counter_8009F42C == 16 )
    {
        return 0;
    }

    pActor = (Actor_bakudan *)GV_NewActor_800150E4(6, sizeof(Actor_bakudan));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)bakudan_act_8006A218, (TActorFunction)bakudan_kill_8006A4A4, aBakudanC);
        if ( bakudan_8006A54C(pActor, pMtx, pVec, a3, pTarget) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return 0;
        }
        pActor->field_10C = 0;
        pActor->field_108 = 0;
    }
    return &pActor->field_0;
}