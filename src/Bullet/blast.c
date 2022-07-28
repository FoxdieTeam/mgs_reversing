#include "blast.h"
#include "libdg.h"
#include "game.h"

extern const char aBlastC[];
extern int claymore_map_800AB9DC;

void AN_Blast_Single_8006E224(SVECTOR *pVec);
void sub_8007913C();

void blast_act_8006DD18(Actor_Blast *pActor)
{
    int new_38; // $s0

    GM_CurrentMap_800AB9B0 = pActor->field_20_map_bits;
 
    new_38 = pActor->field_38 + 1;
    pActor->field_38 = new_38;
    
    if ( new_38 == 1  )
    {
        AN_Blast_Single_8006E224(&pActor->field_24_vec);
    }
     
    if ( new_38 == 2 )
    {
        sub_8007913C();
    }
      
    if ( new_38 >= 30 )
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
}

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
void blast_8006DDEC(Blast_Data *pBlastData, Actor_Blast *pBlast, int targetSidePicker);

int blast_init_8006DF8C(Blast_Data *pBlastData, Actor_Blast *pBlast, MATRIX *pMtx, int targetSidePicker)
{
    pBlast->field_38 = 0;
    pBlast->field_20_map_bits = GM_CurrentMap_800AB9B0;
    pBlast->field_24_vec.vx = pMtx->t[0];
    pBlast->field_24_vec.vy = pMtx->t[1];
    pBlast->field_24_vec.vz = pMtx->t[2];
    blast_8006DDEC(pBlastData, pBlast, targetSidePicker);
    return 0;
}

void blast_act_8006DD18(Actor_Blast* pActor);

void sub_800790E8();

Actor* NewBlast_8006DFDC(MATRIX *pMtx, Blast_Data *pBlastData)
{
    Actor_Blast *pActor = (Actor_Blast *)GV_NewActor_800150E4(6, sizeof(Actor_Blast));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)blast_act_8006DD18, (TActorFunction)blast_kill_8006DD90, aBlastC);
        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;

        if ( blast_init_8006DF8C(pBlastData, pActor, pMtx, 1) < 0 )
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
        if ( blast_init_8006DF8C(pBlastData, pActor, pMtx, whichSidePicker) < 0 )
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
