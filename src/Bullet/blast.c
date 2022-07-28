#include "blast.h"
#include "libdg.h"
#include "game.h"

#pragma INCLUDE_ASM("asm/Bullet/blast_act_8006DD18.s")

extern const char aBlastC[];

extern int claymore_map_800AB9DC;

extern void sub_8007913C(void);

void blast_kill_8006DD90(int param_1)
{
    DG_OBJS *iVar1;

    if (*(int *)(param_1 + 0x38) < 2)
    {
        sub_8007913C();
    }
    iVar1 = *(DG_OBJS **)(param_1 + 0x2c);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
}

#pragma INCLUDE_ASM("asm/Bullet/blast_8006DDEC.s")
#pragma INCLUDE_ASM("asm/Bullet/blast_8006DF8C.s")


int blast_8006DF8C(Blast_Data *pBlastData, Actor_Blast *pBlast, MATRIX *pMtx, int targetSidePicker);

void blast_act_8006DD18(Actor_Blast* pActor);

void sub_800790E8();

Actor* NewBlast_8006DFDC(MATRIX *pMtx, Blast_Data *pBlastData)
{
    Actor_Blast *pActor = (Actor_Blast *)GV_NewActor_800150E4(6, sizeof(Actor_Blast));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)blast_act_8006DD18, (TActorFunction)blast_kill_8006DD90, aBlastC);
        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;

        if ( blast_8006DF8C(pBlastData, pActor, pMtx, 1) < 0 )
        {

            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        GM_SetNoise(255, 32, &pActor->field_24_vec);

        sub_800790E8();
    }

    return &pActor->field_0_actor;
}

Actor_Blast* NewBlast2_8006E0F0(MATRIX *pMtx, Blast_Data *pBlastData, int doSound, int whichSidePicker)
{
    Actor_Blast *pActor = (Actor_Blast *)GV_NewActor_800150E4(6, sizeof(Actor_Blast));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)blast_act_8006DD18, (TActorFunction)blast_kill_8006DD90, aBlastC);
        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;
        if ( blast_8006DF8C(pBlastData, pActor, pMtx, whichSidePicker) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        if ( doSound )
        {
            GM_SetNoise(255, 32, &pActor->field_24_vec);
        }

        sub_800790E8();
    }
    return pActor;
}

#pragma INCLUDE_ASM("asm/AN_Blast_Single_8006E224.s")
#pragma INCLUDE_ASM("asm/sub_8006E2A8.s")
#pragma INCLUDE_ASM("asm/AN_Blast_Minimini_8006E32C.s")
