#include "rmissile.h"

#include "Game/object.h"

// nikita missile

#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_helper4_8006B800.s")       // 136 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_8006B888.s")                      // 156 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_8006B924.s")                      // 140 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006B9B0.s")    // 192 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006BA70.s")    // 160 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006BB10.s")    // 532 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BD24.s")           // 300 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BE50.s")           // 64 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BE90.s")           // 92 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BEEC.s")           // 232 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BFD4.s")           // 208 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006C0A4.s")    // 112 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006C114.s")           // 616 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006C37C.s")           // 584 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_8006C5C4.s")                  // 1404 bytes

extern int   dword_8009F46C;
extern int   dword_8009F470;
extern short Nik_Blast_8009F484;

void rmissile_kill_8006CB40(Actor_rmissile *pActor)
{
    DG_OBJS *objs;
    
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    if (pActor->field_174)
    {
        GV_DelayedFree_80016254(pActor->field_174);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }
    
    dword_8009F470 = 0;
    Nik_Blast_8009F484 = 0;

    objs = pActor->field_2D8_objs;
    
    if (objs)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }

    if (!pActor->field_117)
    {
        rmissile_8006B924(pActor);
    }
}

#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_helper3_8006CBD8.s")       // 120 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_helper2_8006CC50.s")       // 204 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_helper_helper_8006CD1C.s") // 312 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_helper_8006CE54.s")        // 240 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_loader_8006CF44.s")               // 480 bytes

extern int dword_8009F480;

extern const char rRmissileC[]; // = "rmissile.c";

Actor_rmissile * NewRMissile_8006D124(MATRIX *pMtx, int whichSide)
{
    Actor_rmissile *actor;

    actor = (Actor_rmissile *)GV_NewActor_800150E4(6, sizeof(Actor_rmissile));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)&rmissile_act_8006C5C4,
                                  (TActorFunction)&rmissile_kill_8006CB40, rRmissileC);

        if (rmissile_loader_8006CF44(actor, pMtx, whichSide) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        actor->field_111 = 30;
        actor->field_112 = 0;
        actor->field_113 = 0;
        actor->field_117 = 0;
        actor->field_114 = 0;
        actor->field_115 = 0;
        actor->field_116 = 0;
        dword_8009F480 = 0;
        actor->field_118 = 0;
        actor->field_11A = 0;
        actor->field_11C = 0;
        actor->field_168 = 0;
        Nik_Blast_8009F484 = 0;
    }

    return actor;
}
