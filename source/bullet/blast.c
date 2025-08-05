#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "game/map.h"
#include "sd/g_sound.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_AFTER

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    SVECTOR  pos;
    DG_PRIM *prim;
    int      unused1;
    int      unused2;
    int      time;
    TARGET   target;
} Work;

/*---------------------------------------------------------------------------*/

BLAST_DATA blast_data_8009F4B8[8] = {
    { 0x100, 5, 0x3E8, 0x7D0,  2 },
    { 0x100, 5, 0x3E8, 0x7D0,  6 },
    { 0x100, 5, 0x3E8, 0x7D0,  5 },
    { 0x100, 5, 0x3E8, 0x7D0,  4 },
    { 0x100, 5, 0x3E8, 0x7D0,  3 },
    { 0x100, 5, 0x3E8, 0x7D0, -1 },
    { 0x400, 5, 0x3E8, 0x7D0, 10 },
    {     0, 0,     1,     1, -1 }
};

/*---------------------------------------------------------------------------*/

STATIC SVECTOR svector_8009F558[2] = {
#ifndef VR_EXE
    {100, 0, 0, 0},
#else
    {50, 0, 0, 0},
#endif
    {2000, 2000, 4000, 4000}
};

static void Act(Work *work)
{
    int time;

    GM_CurrentMap = work->map;

    time = ++work->time;

    if (time == 1)
    {
        AN_Blast_Single(&work->pos);
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

static void Die(Work *blast)
{
    if (blast->time < 2)
    {
        sub_8007913C();
    }

    GM_FreePrim(blast->prim);
}

/*---------------------------------------------------------------------------*/

static void InitBlastTarget(BLAST_DATA *blast_data, Work *work, int side)
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

    if ( GM_lpfnBombExplosion && GM_lpfnBombExplosion(&work->target, GM_uBombHoming) )
    {
        ++work->time;
    }
    else
    {
        GM_SeSet(&work->pos, SE_EXPLOSION);
    }
}

static int GetResources(BLAST_DATA *blast_data, Work *work, MATRIX *world, int side)
{
    work->time = 0;
    work->map = GM_CurrentMap;
    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];
    InitBlastTarget(blast_data, work, side);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBlast(MATRIX *world, BLAST_DATA *blast_data)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blast.c");
        GM_ClaymoreMap = GM_CurrentMap;

        if (GetResources(blast_data, work, world, 1) < 0)
        {

            GV_DestroyActor(&work->actor);
            return NULL;
        }

        GM_SetNoise(255, 32, &work->pos);

        sub_800790E8();
    }

    return (void *)work;
}

void *NewBlast2(MATRIX *world, BLAST_DATA *blast_data, int doSound, int side)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blast.c");
        GM_ClaymoreMap = GM_CurrentMap;
        if (GetResources(blast_data, work, world, side) < 0)
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
    return (void *)work;
}

/*---------------------------------------------------------------------------*/

STATIC const unsigned char blast_anim_data_single[64] = {
   0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
   0x04,0xb0,0x04,0xb0, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
   0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x64,0x00,0x64,0x08, 0xf8,0xf8,0xf8,0x02,
   0x00,0x01,0x0a,0x00, 0x50,0x00,0x50,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};
STATIC const unsigned char blast_anim_data_random[64] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x04,0x01,0xff,0x0a,
    0x04,0xb0,0x04,0xb0, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x0c,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x08, 0x01,0xff,0x0a,0x00, 0x64,0x00,0x64,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x50,0x00,0x50,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};
STATIC const unsigned char blast_anim_data_mini[64] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
    0x02,0x58,0x02,0x58, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x32,0x00,0x32,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x28,0x00,0x28,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};
STATIC const unsigned char blast_anim_data_minimini[64] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
    0x00,0xc8,0x00,0xc8, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x14,0x00,0x14,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x14,0x00,0x14,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};
STATIC const unsigned char blast_anim_data_high[290] = {
    0x01,0x17,0x04,0x00, 0x0b,0x00,0x4b,0x00, 0x90,0x00,0xd9,0x01, 0x00,0x02,0x00,0x01,
    0x0c,0x00,0x02,0x01, 0xff,0x0a,0x04,0xb0, 0x04,0xb0,0x02,0x00, 0x01,0x0d,0x0c,0x00,
    0x06,0x01,0xff,0x0a, 0x00,0xc8,0x00,0xc8, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x07,0x01,
    0xff,0x0a,0x00,0x64, 0x00,0x64,0x08,0xf8, 0xf8,0xf8,0x02,0x00, 0x01,0x0a,0x00,0x50,
    0x00,0x50,0x08,0xf8, 0xf8,0xf8,0x02,0x00, 0x01,0x0d,0x0f,0x01, 0x00,0x02,0x00,0x01,
    0x01,0x00,0x02,0x00, 0x01,0x0c,0x00,0x02, 0x01,0xff,0x0a,0x03, 0xe8,0x03,0xe8,0x02,
    0x00,0x01,0x0d,0x0c, 0x00,0x06,0x01,0xff, 0x0a,0x00,0xb4,0x00, 0xb4,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x64,0x00,0x64,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x50,0x00,0x50,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f,
    0x0c,0x00,0x02,0x01, 0x00,0x02,0x00,0x01, 0x0d,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00,
    0x02,0x01,0xff,0x0a, 0x03,0x20,0x03,0x20, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01,
    0xff,0x0a,0x00,0xa0, 0x00,0xa0,0x02,0x00, 0x01,0x0d,0x0c,0x00, 0x07,0x01,0xff,0x0a,
    0x00,0x64,0x00,0x64, 0x08,0xf8,0xf8,0xf8, 0x02,0x00,0x01,0x0a, 0x00,0x50,0x00,0x50,
    0x08,0xf8,0xf8,0xf8, 0x02,0x00,0x01,0x0d, 0x0f,0x0c,0x00,0x03, 0x01,0x00,0x02,0x00,
    0x01,0x0d,0x01,0x00, 0x02,0x00,0x01,0x0c, 0x00,0x02,0x01,0xff, 0x0a,0x02,0x58,0x02,
    0x58,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x06, 0x01,0xff,0x0a,0x00, 0x8c,0x00,0x8c,0x02,
    0x00,0x01,0x0d,0x0c, 0x00,0x07,0x01,0xff, 0x0a,0x00,0x64,0x00, 0x64,0x08,0xf8,0xf8,
    0xf8,0x02,0x00,0x01, 0x0a,0x00,0x50,0x00, 0x50,0x08,0xf8,0xf8, 0xf8,0x02,0x00,0x01,
    0x0d,0x0f
};

STATIC ANIMATION blast_anim_single   = { PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)blast_anim_data_single };
STATIC ANIMATION blast_anim_random   = { PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)blast_anim_data_random };
STATIC ANIMATION blast_anim_mini     = { PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1,  500,  500, 128, NULL, (void *)blast_anim_data_mini };
STATIC ANIMATION blast_anim_minimini = { PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1,  200,  200, 128, NULL, (void *)blast_anim_data_minimini };
STATIC ANIMATION blast_anim_high     = { PCX_BOMB1_FL, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)blast_anim_data_high };

void AN_Blast_Single(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &blast_anim_single;
    anm->pre_script = &pre;

    NewAnime( NULL, 0, anm );
}

void AN_Blast_Mini(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;

    pre.s_anim = 0;

    anm = &blast_anim_mini;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );
}

void AN_Blast_Minimini(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;

    pre.s_anim = 0;

    anm = &blast_anim_minimini;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );
}

void AN_Blast_Rand(SVECTOR *pos)
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

    prescript.speed = DG_ZeroVector;
    prescript.speed.vy += GV_RandS(64);

    prescript.s_anim = 0;

    randu = GV_RandU(4);
    if (randu == 0)
    {
        anm = &blast_anim_single;
    }
    else
    {
        anm = &blast_anim_random;
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
    NewAnime(m, map, anm);
}

void AN_Blast_high(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.pos.vy += 600;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 200;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 400;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 150;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 200;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 100;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 50;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 3;
    NewAnime( NULL, 0, anm );
}

void AN_Blast_high2(SVECTOR *pos, SVECTOR *offset)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.pos.vx += offset->vx;
    pre.pos.vy += offset->vy;
    pre.pos.vz += offset->vz;
    pre.speed = DG_ZeroVector;
    pre.speed.vx += offset->vx / 3;
    pre.speed.vy += offset->vy / 3;
    pre.speed.vz += offset->vz / 3;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vx += (offset->vx * 3) >> 2;
    pre.pos.vy += (offset->vy * 3) >> 2;
    pre.pos.vz += (offset->vz * 3) >> 2;
    pre.speed = DG_ZeroVector;
    pre.speed.vx += ((offset->vx / 3) * 3) >> 2;
    pre.speed.vy += ((offset->vy / 3) * 3) >> 2;
    pre.speed.vz += ((offset->vz / 3) * 3) >> 2;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vx += offset->vx >> 1;
    pre.pos.vy += offset->vy >> 1;
    pre.pos.vz += offset->vz >> 1;
    pre.speed = DG_ZeroVector;
    pre.speed.vx += (offset->vx / 3) >> 1;
    pre.speed.vy += (offset->vy / 3) >> 1;
    pre.speed.vz += (offset->vz / 3) >> 1;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.speed.vx += (offset->vx / 3) >> 2;
    pre.speed.vy += (offset->vy / 3) >> 2;
    pre.speed.vz += (offset->vz / 3) >> 2;
    pre.s_anim = 0;

    anm = &blast_anim_high;
    anm->pre_script = &pre;

    pre.scr_num = 3;
    NewAnime( NULL, 0, anm );
}
