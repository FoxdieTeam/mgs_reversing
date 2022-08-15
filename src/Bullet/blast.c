#include "blast.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/target.h"
#include "Anime/animeconv/anime.h"
#include "unknown.h"

extern const char aBlastC[];
extern int        claymore_map_800AB9DC;

extern int (*GM_lpfnBombExplosion_800AB3F0)(GM_Target *, int);
extern short GM_uBombHoming_800AB3E4;

extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR stru_8009F558[2];

extern Anim_Data stru_8009F568;
extern Anim_Data stru_8009F5A0;
extern Anim_Data stru_8009F5BC;

void blast_act_8006DD18(Actor_Blast *pActor)
{
    int new_38; // $s0

    GM_CurrentMap_800AB9B0 = pActor->field_20_map_bits;

    new_38 = pActor->field_38 + 1;
    pActor->field_38 = new_38;

    if (new_38 == 1)
    {
        AN_Blast_Single_8006E224(&pActor->field_24_vec);
    }

    if (new_38 == 2)
    {
        sub_8007913C();
    }

    if (new_38 >= 30)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
}

void blast_kill_8006DD90(Actor_Blast *blast)
{
    DG_OBJS *objs;

    if (blast->field_38 < 2)
    {
        sub_8007913C();
    }

    objs = (DG_OBJS *)blast->field_2C;
    if (objs)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }
}

#pragma INCLUDE_ASM("asm/Bullet/blast_8006DDEC.s") // 416 bytes
// void blast_8006DDEC(Blast_Data *pBlastData, Actor_Blast *pBlast, int targetSidePicker);
/*
void blast_8006DDEC(Blast_Data *pBlastData, Actor_Blast *pBlast, int targetSidePicker)
{
    GM_Target *pTarget; // $s1
    short whichSide; // $a2
    short v8; // $v1
    int v10; // $v0
    SVECTOR *pVec; // $a0
    SVECTOR vec; // [sp+18h] [-8h] BYREF

    pTarget = &pBlast->field_3C_target;
    vec.vz = pBlastData->field_8_z;
    vec.vy = vec.vz;
    vec.vx = vec.vz;

    if ( targetSidePicker )
    {
        whichSide = 0;
    }
    else
    {
        whichSide = 2;
    }

    GM_SetTarget_8002DC74(&pBlast->field_3C_target, 4, whichSide, &vec);
    GM_Target_8002DCCC(pTarget, 7, 2, pBlastData->field_0 >> 1, pBlastData->field_4, stru_8009F558);
    pTarget->field_44 = pBlastData->field_10;
    GM_Target_SetVector_8002D500(&pBlast->field_3C_target, &pBlast->field_24_vec);
    sub_8002D7DC(pTarget);


    v8 = pBlastData->field_C;
    stru_8009F558[0].vx = 50;
    vec.vz = v8;
    vec.vy = v8;
    vec.vx = v8;

    if ( targetSidePicker )
    {
        whichSide = 0;
    }
    else
    {
        whichSide = 2;
    }

    GM_SetTarget_8002DC74(pTarget, 4, whichSide, &vec);
    GM_Target_8002DCCC(pTarget, 7, 2, pBlastData->field_0 >> 1, 3, stru_8009F558);
    pTarget->field_44 = pBlastData->field_10;
    GM_Target_SetVector_8002D500(&pBlast->field_3C_target, &pBlast->field_24_vec);
    sub_8002D7DC(pTarget);

    if ( GM_lpfnBombExplosion_800AB3F0 )
    {
        v10 = GM_lpfnBombExplosion_800AB3F0(&pBlast->field_3C_target, GM_uBombHoming_800AB3E4);
        pVec = &pBlast->field_24_vec;
        if ( v10 )
        {
            ++pBlast->field_38;
            return;
        }
    }
    else
    {
        pVec = &pBlast->field_24_vec;
    }

    GM_SeSet_80032858(pVec, 41);
}
*/

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

Actor *NewBlast_8006DFDC(MATRIX *pMtx, Blast_Data *pBlastData)
{
    Actor_Blast *pActor = (Actor_Blast *)GV_NewActor_800150E4(6, sizeof(Actor_Blast));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)blast_act_8006DD18,
                                  (TActorFunction)blast_kill_8006DD90, aBlastC);
        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;

        if (blast_init_8006DF8C(pBlastData, pActor, pMtx, 1) < 0)
        {

            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        GM_SetNoise(255, 32, &pActor->field_24_vec);

        sub_800790E8();
    }

    return &pActor->field_0_actor;
}

Actor_Blast *NewBlast2_8006E0F0(MATRIX *pMtx, Blast_Data *pBlastData, int doSound, int whichSidePicker)
{
    Actor_Blast *pActor = (Actor_Blast *)GV_NewActor_800150E4(6, sizeof(Actor_Blast));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)blast_act_8006DD18,
                                  (TActorFunction)blast_kill_8006DD90, aBlastC);
        claymore_map_800AB9DC = GM_CurrentMap_800AB9B0;
        if (blast_init_8006DF8C(pBlastData, pActor, pMtx, whichSidePicker) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        if (doSound)
        {
            GM_SetNoise(255, 32, &pActor->field_24_vec);
        }

        sub_800790E8();
    }
    return pActor;
}

void AN_Blast_Single_8006E224(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = 0;
    data.field_10_anim_idx = 0;
    stru_8009F568.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F568);
}

void sub_8006E2A8(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = 0;
    stru_8009F5A0.field_14 = &data;
    data.field_10_anim_idx = 0;
    anime_init_8005FBC8(0, 0, &stru_8009F5A0);
}

void AN_Blast_Minimini_8006E32C(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = 0;
    stru_8009F5BC.field_14 = &data;
    data.field_10_anim_idx = 0;
    anime_init_8005FBC8(0, 0, &stru_8009F5BC);
}
