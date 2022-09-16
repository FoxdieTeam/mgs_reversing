#include "Game/object.h"
#include "Game/target.h"
#include "amissile.h"

// stinger missile?

#pragma INCLUDE_ASM("asm/Bullet/amissile_loader_helper_8006D1F4.s") // 172 bytes
#pragma INCLUDE_ASM("asm/Bullet/amissile_act_helper_8006D2A0.s")    // 220 bytes
#pragma INCLUDE_ASM("asm/Bullet/amissile_act_helper_8006D37C.s")    // 644 bytes

int amissile_act_helper_8006D600(void)
{
    return 0;
}

#pragma INCLUDE_ASM("asm/Bullet/amissile_act_8006D608.s")    // 916 bytes

extern int        dword_8009F490;
extern GM_Target *target_800BDF00;

void amissile_kill_8006D99C(Actor_amissile *pActor)
{
    DG_OBJS *pPrim;

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    pPrim = (DG_OBJS *)pActor->field_134_prim;

    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }

    if (target_800BDF00)
    {
        target_800BDF00 = 0;
    }

    dword_8009F490 = 0;
}


#pragma INCLUDE_ASM("asm/Bullet/amissile_loader_8006DA0C.s") // 580 bytes

extern SVECTOR DG_ZeroVector_800AB39C;

extern const char aRmissileC[]; // = "amissile.c"

Actor_amissile * NewAMissile_8006DC50(int arg0, void *arg1)
{
    Actor_amissile *pActor = (Actor_amissile *)GV_NewActor_800150E4(6, sizeof(Actor_amissile));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&amissile_act_8006D608,
                                  (TActorFunction)&amissile_kill_8006D99C, aRmissileC);

        if (amissile_loader_8006DA0C(pActor, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        pActor->field_124 = 30;
        pActor->field_120 = 0;
        pActor->field_128 = 0;
        pActor->field_12C_svector = DG_ZeroVector_800AB39C;
    }

    return pActor;
}
