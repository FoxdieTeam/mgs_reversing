#include "blast.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/target.h"
#include "Anime/animeconv/anime.h"
#include "unknown.h"
#include "map/map.h"

extern int            claymore_map_800AB9DC;
extern TBombFunction3 GM_lpfnBombExplosion_800AB3F0;
extern short          GM_uBombHoming_800AB3E4;
extern SVECTOR        DG_ZeroVector_800AB39C;

extern const char aBlastC[];

Blast_Data blast_data_8009F4B8 = {0x100, 5, 0x3E8, 0x7D0, 2};
Blast_Data blast_data_8009F4CC = {0x100, 5, 0x3E8, 0x7D0, 6};
Blast_Data blast_data_8009F4E0 = {0x100, 5, 0x3E8, 0x7D0, 5};
Blast_Data blast_data_8009F4F4 = {0x100, 5, 0x3E8, 0x7D0, 4};
Blast_Data blast_data_8009F508 = {0x100, 5, 0x3E8, 0x7D0, 3};
Blast_Data blast_data_8009F51C = {0x100, 5, 0x3E8, 0x7D0, -1};
Blast_Data blast_data_8009F530 = {0x400, 5, 0x3E8, 0x7D0, 10};
Blast_Data blast_data_8009F544 = {0, 0, 1, 1, -1};

SVECTOR svector_8009F558[2] = {{100, 0, 0, 0}, {2000, 2000, 4000, 4000}};

ANIMATION stru_8009F568 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BAC};
ANIMATION stru_8009F584 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BEC};
ANIMATION stru_8009F5A0 = {-21358, 4, 4, 16, 1, 2000, 1, 500, 500, 128, NULL, (void *)0x80012C2C};
ANIMATION stru_8009F5BC = {-21358, 4, 4, 16, 1, 2000, 1, 200, 200, 128, NULL, (void *)0x80012C6C};
ANIMATION stru_8009F5D8 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012CAC};

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
    DG_PRIM *pPrim;

    if (blast->field_38 < 2)
    {
        sub_8007913C();
    }

    pPrim = blast->field_2C_prim;
    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }
}

void blast_8006DDEC(Blast_Data *pBlastData, Actor_Blast *pBlast, int targetSidePicker)
{
    TARGET *pTarget = &pBlast->field_3C_target;
    SVECTOR vec;

    vec.vx = vec.vy = vec.vz = pBlastData->field_8_z;

    if ( targetSidePicker )
    {
        GM_SetTarget_8002DC74(pTarget, 4, 0, &vec);
    }
    else
    {
        GM_SetTarget_8002DC74(pTarget, 4, 2, &vec);
    }

    GM_Target_8002DCCC(pTarget, 7, 2, pBlastData->field_0 >> 1, pBlastData->field_4, svector_8009F558);

    pTarget->field_44 = pBlastData->field_10;

    GM_Target_SetVector_8002D500(&pBlast->field_3C_target, &pBlast->field_24_vec);
    sub_8002D7DC(pTarget);

    vec.vx = vec.vy = vec.vz = pBlastData->field_C;
    svector_8009F558[0].vx = 50;

    if ( targetSidePicker )
    {
        GM_SetTarget_8002DC74(pTarget, 4, 0, &vec);
    }
    else
    {
        GM_SetTarget_8002DC74(pTarget, 4, 2, &vec);
    }

    GM_Target_8002DCCC(pTarget, 7, 2, pBlastData->field_0 >> 1, 3, svector_8009F558);

    pTarget->field_44 = pBlastData->field_10;

    GM_Target_SetVector_8002D500(&pBlast->field_3C_target, &pBlast->field_24_vec);
    sub_8002D7DC(pTarget);

    if ( GM_lpfnBombExplosion_800AB3F0 && GM_lpfnBombExplosion_800AB3F0(&pBlast->field_3C_target, GM_uBombHoming_800AB3E4) )
    {
        ++pBlast->field_38;
    }
    else
    {
        GM_SeSet_80032858(&pBlast->field_24_vec, 41);
    }
}

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

Actor_Blast * NewBlast_8006DFDC(MATRIX *pMtx, Blast_Data *pBlastData)
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
            return NULL;
        }

        GM_SetNoise(255, 32, &pActor->field_24_vec);

        sub_800790E8();
    }

    return pActor;
}

Actor_Blast * NewBlast2_8006E0F0(MATRIX *pMtx, Blast_Data *pBlastData, int doSound, int whichSidePicker)
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
            return NULL;
        }

        if (doSound)
        {
            GM_SetNoise(255, 32, &pActor->field_24_vec);
        }

        sub_800790E8();
    }
    return pActor;
}

void AN_Blast_Single_8006E224(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F568;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Blast_8006E2A8(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;

    pre.s_anim = 0;

    anm = &stru_8009F5A0;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Blast_Minimini_8006E32C(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;

    pre.s_anim = 0;

    anm = &stru_8009F5BC;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8006E3B0(SVECTOR *pVec)
{
    PRESCRIPT  prescript;
    PRESCRIPT *prescript_ptr;
    MATRIX    *m;
    int        map;
    int        randu;
    ANIMATION *anm;

    prescript.pos = *pVec;
    prescript.pos.vx += GV_RandS_800170BC(128);
    prescript.pos.vy += GV_RandS_800170BC(128);
    prescript.pos.vz += GV_RandS_800170BC(128);

    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.speed.vy += GV_RandS_800170BC(64);

    prescript.s_anim = 0;

    randu = GV_RandU_80017090(4);
    if (randu == 0)
    {
        anm = &stru_8009F568;
    }
    else
    {
        anm = &stru_8009F584;
    }

    prescript_ptr = &prescript;
    map = 0;
    m = NULL;
    // Silly code just to get the compiler to emit
    // an unnecessary move and get a match...
    if (randu == 0)
    {
        m = NULL;
        anm->field_14_pre_script = prescript_ptr;
    }
    else
    {
        anm->field_14_pre_script = prescript_ptr;
    }

    prescript.scr_num = 0;
    NewAnime_8005FBC8(m, map, anm);
}

void sub_8006E4A4(SVECTOR *pPosition)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pPosition;
    pre.pos.vy += 600;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 200;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.pos.vy += 400;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 150;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.pos.vy += 200;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 100;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 50;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 3;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void sub_8006E6CC(SVECTOR *pPosition, SVECTOR *pOffset)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pPosition;
    pre.pos.vx += pOffset->vx;
    pre.pos.vy += pOffset->vy;
    pre.pos.vz += pOffset->vz;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += pOffset->vx / 3;
    pre.speed.vy += pOffset->vy / 3;
    pre.speed.vz += pOffset->vz / 3;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.pos.vx += (pOffset->vx * 3) >> 2;
    pre.pos.vy += (pOffset->vy * 3) >> 2;
    pre.pos.vz += (pOffset->vz * 3) >> 2;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += ((pOffset->vx / 3) * 3) >> 2;
    pre.speed.vy += ((pOffset->vy / 3) * 3) >> 2;
    pre.speed.vz += ((pOffset->vz / 3) * 3) >> 2;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.pos.vx += pOffset->vx >> 1;
    pre.pos.vy += pOffset->vy >> 1;
    pre.pos.vz += pOffset->vz >> 1;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += (pOffset->vx / 3) >> 1;
    pre.speed.vy += (pOffset->vy / 3) >> 1;
    pre.speed.vz += (pOffset->vz / 3) >> 1;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pPosition;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += (pOffset->vx / 3) >> 2;
    pre.speed.vy += (pOffset->vy / 3) >> 2;
    pre.speed.vz += (pOffset->vz / 3) >> 2;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 3;
    NewAnime_8005FBC8( NULL, 0, anm );
}
