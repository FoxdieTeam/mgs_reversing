#include "blast.h"

#include <stddef.h> // for NULL
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "Game/map.h"
#include "Game/target.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern int            GM_ClaymoreMap_800AB9DC;
extern TBombFunction3 GM_lpfnBombExplosion_800AB3F0;
extern short          GM_uBombHoming_800AB3E4;
extern SVECTOR        DG_ZeroVector_800AB39C;

Blast_Data blast_data_8009F4B8[8] = {
    {0x100, 5, 0x3E8, 0x7D0, 2},
    {0x100, 5, 0x3E8, 0x7D0, 6},
    {0x100, 5, 0x3E8, 0x7D0, 5},
    {0x100, 5, 0x3E8, 0x7D0, 4},
    {0x100, 5, 0x3E8, 0x7D0, 3},
    {0x100, 5, 0x3E8, 0x7D0, -1},
    {0x400, 5, 0x3E8, 0x7D0, 10},
    {0, 0, 1, 1, -1}
};

SVECTOR svector_8009F558[2] = {
#ifndef VR_EXE
    {100, 0, 0, 0},
#else
    {50, 0, 0, 0},
#endif
    {2000, 2000, 4000, 4000}
};

void BlastAct_8006DD18(BlastWork *work)
{
    int time;

    GM_CurrentMap_800AB9B0 = work->map;

    time = ++work->time;

    if (time == 1)
    {
        AN_Blast_Single_8006E224(&work->pos);
    }

    if (time == 2)
    {
        sub_8007913C();
    }

    if (time >= 30)
    {
        GV_DestroyActor(&work->actor);
    }
}

void BlastDie_8006DD90(BlastWork *blast)
{
    DG_PRIM *prim;

    if (blast->time < 2)
    {
        sub_8007913C();
    }

    prim = blast->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void blast_8006DDEC(Blast_Data *blast_data, BlastWork *work, int side)
{
    TARGET *target = &work->target;
    SVECTOR size;

    size.vx = size.vy = size.vz = blast_data->field_8_z;

    if ( side )
    {
        GM_SetTarget(target, 4, NO_SIDE, &size);
    }
    else
    {
        GM_SetTarget(target, 4, ENEMY_SIDE, &size);
    }

    GM_Target_8002DCCC(target, 7, 2, blast_data->field_0 >> 1, blast_data->field_4, svector_8009F558);

    target->field_44 = blast_data->field_10;

    GM_MoveTarget(&work->target, &work->pos);
    GM_PowerTarget(target);

    size.vx = size.vy = size.vz = blast_data->field_C;
    svector_8009F558[0].vx = 50;

    if ( side )
    {
        GM_SetTarget(target, 4, NO_SIDE, &size);
    }
    else
    {
        GM_SetTarget(target, 4, ENEMY_SIDE, &size);
    }

    GM_Target_8002DCCC(target, 7, 2, blast_data->field_0 >> 1, 3, svector_8009F558);

    target->field_44 = blast_data->field_10;

    GM_MoveTarget(&work->target, &work->pos);
    GM_PowerTarget(target);

    if ( GM_lpfnBombExplosion_800AB3F0 && GM_lpfnBombExplosion_800AB3F0(&work->target, GM_uBombHoming_800AB3E4) )
    {
        ++work->time;
    }
    else
    {
        GM_SeSet_80032858(&work->pos, SE_EXPLOSION);
    }
}

int BlastGetResources_8006DF8C(Blast_Data *blast_data, BlastWork *work, MATRIX *world, int side)
{
    work->time = 0;
    work->map = GM_CurrentMap_800AB9B0;
    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];
    blast_8006DDEC(blast_data, work, side);
    return 0;
}

GV_ACT *NewBlast_8006DFDC(MATRIX *world, Blast_Data *blast_data)
{
    BlastWork *work = (BlastWork *)GV_NewActor(6, sizeof(BlastWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BlastAct_8006DD18,
                         (TActorFunction)BlastDie_8006DD90, "blast.c");
        GM_ClaymoreMap_800AB9DC = GM_CurrentMap_800AB9B0;

        if (BlastGetResources_8006DF8C(blast_data, work, world, 1) < 0)
        {

            GV_DestroyActor(&work->actor);
            return NULL;
        }

        GM_SetNoise(255, 32, &work->pos);

        sub_800790E8();
    }

    return &work->actor;
}

GV_ACT *NewBlast2_8006E0F0(MATRIX *world, Blast_Data *blast_data, int doSound, int side)
{
    BlastWork *work = (BlastWork *)GV_NewActor(6, sizeof(BlastWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BlastAct_8006DD18,
                         (TActorFunction)BlastDie_8006DD90, "blast.c");
        GM_ClaymoreMap_800AB9DC = GM_CurrentMap_800AB9B0;
        if (BlastGetResources_8006DF8C(blast_data, work, world, side) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        if (doSound)
        {
            GM_SetNoise(255, 32, &work->pos);
        }

        sub_800790E8();
    }
    return &work->actor;
}

const unsigned char animation_data_80012BAC[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char animation_data_80012BEC[64] = {
    0u,   59u,  1u,   0u, 5u,  1u, 0u,   2u, 0u,  1u, 12u, 0u,  4u,   1u,   255u, 10u,  4u,  176u, 4u,   176u, 2u,   0u,
    1u,   13u,  12u,  0u, 12u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   8u,   1u,   255u, 10u, 0u,   100u, 0u,   100u, 8u,
    248u, 248u, 248u, 2u, 0u,  1u, 10u,  0u, 80u, 0u, 80u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u};

const unsigned char animation_data_80012C2C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  2u,  88u, 2u,  88u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,  50u, 0u,  50u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 40u, 0u, 40u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,  13u, 15u};

const unsigned char animation_data_80012C6C[64] = {
    0u,   59u,  1u,   0u, 5u, 1u, 0u,   2u, 0u,  1u, 12u, 0u,  2u,   1u,   255u, 10u,  0u,  200u, 0u,  200u, 2u,  0u,
    1u,   13u,  12u,  0u, 6u, 1u, 255u, 2u, 0u,  1u, 13u, 12u, 0u,   7u,   1u,   255u, 10u, 0u,   20u, 0u,   20u, 8u,
    248u, 248u, 248u, 2u, 0u, 1u, 10u,  0u, 20u, 0u, 20u, 8u,  248u, 248u, 248u, 2u,   0u,  1u,   13u, 15u};

const unsigned char animation_data_80012CAC[290] = {
    1u,   23u,  4u,   0u,   11u,  0u,   75u,  0u,   144u, 0u,   217u, 1u,   0u,   2u,   0u,  1u,   12u,  0u,   2u,
    1u,   255u, 10u,  4u,   176u, 4u,   176u, 2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,  255u, 10u,  0u,   200u,
    0u,   200u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,  100u, 8u,   248u, 248u,
    248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,  1u,   13u,  15u,  1u,
    0u,   2u,   0u,   1u,   1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u, 3u,   232u, 3u,   232u,
    2u,   0u,   1u,   13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   180u, 0u,   180u, 2u,  0u,   1u,   13u,  12u,
    0u,   7u,   1u,   255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,  1u,   10u,  0u,   80u,
    0u,   80u,  8u,   248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   2u,   1u,  0u,   2u,   0u,   1u,
    13u,  1u,   0u,   2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  3u,   32u,  3u,  32u,  2u,   0u,   1u,
    13u,  12u,  0u,   6u,   1u,   255u, 10u,  0u,   160u, 0u,   160u, 2u,   0u,   1u,   13u, 12u,  0u,   7u,   1u,
    255u, 10u,  0u,   100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,  80u,  0u,   80u,  8u,
    248u, 248u, 248u, 2u,   0u,   1u,   13u,  15u,  12u,  0u,   3u,   1u,   0u,   2u,   0u,  1u,   13u,  1u,   0u,
    2u,   0u,   1u,   12u,  0u,   2u,   1u,   255u, 10u,  2u,   88u,  2u,   88u,  2u,   0u,  1u,   13u,  12u,  0u,
    6u,   1u,   255u, 10u,  0u,   140u, 0u,   140u, 2u,   0u,   1u,   13u,  12u,  0u,   7u,  1u,   255u, 10u,  0u,
    100u, 0u,   100u, 8u,   248u, 248u, 248u, 2u,   0u,   1u,   10u,  0u,   80u,  0u,   80u, 8u,   248u, 248u, 248u,
    2u,   0u,   1u,   13u,  15u};

ANIMATION stru_8009F568 = {PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)animation_data_80012BAC};
ANIMATION stru_8009F584 = {PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)animation_data_80012BEC};
ANIMATION stru_8009F5A0 = {PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 500, 500, 128, NULL, (void *)animation_data_80012C2C};
ANIMATION stru_8009F5BC = {PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 200, 200, 128, NULL, (void *)animation_data_80012C6C};
ANIMATION stru_8009F5D8 = {PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)animation_data_80012CAC};

void AN_Blast_Single_8006E224(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F568;
    anm->pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Blast_Mini_8006E2A8(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;

    pre.s_anim = 0;

    anm = &stru_8009F5A0;
    anm->pre_script = &pre;

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
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Blast_Rand_8006E3B0(SVECTOR *pos)
{
    PRESCRIPT  prescript;
    PRESCRIPT *prescript_ptr;
    MATRIX    *m;
    int        map;
    int        randu;
    ANIMATION *anm;

    prescript.pos = *pos;
    prescript.pos.vx += GV_RandS(128);
    prescript.pos.vy += GV_RandS(128);
    prescript.pos.vz += GV_RandS(128);

    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.speed.vy += GV_RandS(64);

    prescript.s_anim = 0;

    randu = GV_RandU(4);
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
        anm->pre_script = prescript_ptr;
    }
    else
    {
        anm->pre_script = prescript_ptr;
    }

    prescript.scr_num = 0;
    NewAnime_8005FBC8(m, map, anm);
}

void AN_Blast_high_8006E4A4(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.pos.vy += 600;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 200;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 400;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 150;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 200;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 100;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vy += 50;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 3;
    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Blast_high2_8006E6CC(SVECTOR *pos, SVECTOR *offset)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.pos.vx += offset->vx;
    pre.pos.vy += offset->vy;
    pre.pos.vz += offset->vz;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += offset->vx / 3;
    pre.speed.vy += offset->vy / 3;
    pre.speed.vz += offset->vz / 3;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vx += (offset->vx * 3) >> 2;
    pre.pos.vy += (offset->vy * 3) >> 2;
    pre.pos.vz += (offset->vz * 3) >> 2;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += ((offset->vx / 3) * 3) >> 2;
    pre.speed.vy += ((offset->vy / 3) * 3) >> 2;
    pre.speed.vz += ((offset->vz / 3) * 3) >> 2;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 1;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vx += offset->vx >> 1;
    pre.pos.vy += offset->vy >> 1;
    pre.pos.vz += offset->vz >> 1;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += (offset->vx / 3) >> 1;
    pre.speed.vy += (offset->vy / 3) >> 1;
    pre.speed.vz += (offset->vz / 3) >> 1;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime_8005FBC8( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.speed.vx += (offset->vx / 3) >> 2;
    pre.speed.vy += (offset->vy / 3) >> 2;
    pre.speed.vz += (offset->vz / 3) >> 2;
    pre.s_anim = 0;

    anm = &stru_8009F5D8;
    anm->pre_script = &pre;

    pre.scr_num = 3;
    NewAnime_8005FBC8( NULL, 0, anm );
}
