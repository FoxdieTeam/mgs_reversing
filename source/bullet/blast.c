#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

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
    { 0x100, 5, 0x3E8, 0x7D0, WP_Grenade },
    { 0x100, 5, 0x3E8, 0x7D0, WP_C4 },
    { 0x100, 5, 0x3E8, 0x7D0, WP_Claymore },
    { 0x100, 5, 0x3E8, 0x7D0, WP_Stinger },
    { 0x100, 5, 0x3E8, 0x7D0, WP_Nikita },
    { 0x100, 5, 0x3E8, 0x7D0, WP_None },
    { 0x400, 5, 0x3E8, 0x7D0, WP_Max },
    {     0, 0,     1,     1, WP_None }
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

    GM_SetPowerTarget(target, POWER_CONST | POWER_EXPLODE, 2, blast_data->field_0 >> 1, blast_data->field_4, svector_8009F558);

    target->weapon = blast_data->weapon;

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

    GM_SetPowerTarget(target, POWER_CONST | POWER_EXPLODE, 2, blast_data->field_0 >> 1, 3, svector_8009F558);

    target->weapon = blast_data->weapon;

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

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
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

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
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

static const char anm_blast_single_form_script[] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
    0x04,0xb0,0x04,0xb0, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x64,0x00,0x64,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x50,0x00,0x50,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

ANIMATION anm_blast_single_form = {
    PCX_BOMB1_FL,               // tex
    4,                          // texdev_x
    4,                          // texdev_y
    16,                         // n_anime
    1,                          // n_verts
    2000,                       // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (void *)anm_blast_single_form_script // script
};

static const char anm_blast_random_form_script[] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x04,0x01,0xff,0x0a,
    0x04,0xb0,0x04,0xb0, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x0c,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x08, 0x01,0xff,0x0a,0x00, 0x64,0x00,0x64,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x50,0x00,0x50,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

ANIMATION anm_blast_random_form = {
    PCX_BOMB1_FL,               // tex
    4,                          // texdev_x
    4,                          // texdev_y
    16,                         // n_anime
    1,                          // n_verts
    2000,                       // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (void *)anm_blast_random_form_script // script
};

static const char anm_blast_mini_form_script[] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
    0x02,0x58,0x02,0x58, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x32,0x00,0x32,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x28,0x00,0x28,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

ANIMATION anm_blast_mini_form = {
    PCX_BOMB1_FL,               // tex
    4,                          // texdev_x
    4,                          // texdev_y
    16,                         // n_anime
    1,                          // n_verts
    2000,                       // raise
    1,                          // amb
    500,                        // size_w
    500,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (void *)anm_blast_mini_form_script // script
};

static const char anm_blast_minimini_form_script[] = {
    0x00,0x3b,0x01,0x00, 0x05,0x01,0x00,0x02, 0x00,0x01,0x0c,0x00, 0x02,0x01,0xff,0x0a,
    0x00,0xc8,0x00,0xc8, 0x02,0x00,0x01,0x0d, 0x0c,0x00,0x06,0x01, 0xff,0x02,0x00,0x01,
    0x0d,0x0c,0x00,0x07, 0x01,0xff,0x0a,0x00, 0x14,0x00,0x14,0x08, 0xf8,0xf8,0xf8,0x02,
    0x00,0x01,0x0a,0x00, 0x14,0x00,0x14,0x08, 0xf8,0xf8,0xf8,0x02, 0x00,0x01,0x0d,0x0f
};

ANIMATION anm_blast_minimini_form = {
    PCX_BOMB1_FL,               // tex
    4,                          // texdev_x
    4,                          // texdev_y
    16,                         // n_anime
    1,                          // n_verts
    2000,                       // raise
    1,                          // amb
    200,                        // size_w
    200,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (void *)anm_blast_minimini_form_script // script
};

static const char anm_blast_high_form_script[] = {
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

ANIMATION anm_blast_high_form = {
    PCX_BOMB1_FL,               // tex
    4,                          // texdev_x
    4,                          // texdev_y
    16,                         // n_anime
    1,                          // n_verts
    2000,                       // raise
    1,                          // amb
    1000,                       // size_w
    1000,                       // size_h
    128,                        // v
    NULL,                       // pre_script
    (void *)anm_blast_high_form_script // script
};

/*---------------------------------------------------------------------------*/

void AN_Blast_Single(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &anm_blast_single_form;
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

    anm = &anm_blast_mini_form;
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

    anm = &anm_blast_minimini_form;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );
}

void AN_Blast_Rand(SVECTOR *pos)
{
    PRESCRIPT  pre;
    PRESCRIPT *pre_ptr;
    MATRIX    *m;
    int        map;
    int        randu;
    ANIMATION *anm;

    pre.pos = *pos;
    pre.pos.vx += GV_RandS(128);
    pre.pos.vy += GV_RandS(128);
    pre.pos.vz += GV_RandS(128);

    pre.speed = DG_ZeroVector;
    pre.speed.vy += GV_RandS(64);

    pre.s_anim = 0;

    randu = GV_RandU(4);
    if (randu == 0)
    {
        anm = &anm_blast_single_form;
    }
    else
    {
        anm = &anm_blast_random_form;
    }

    pre_ptr = &pre;
    map = 0;
    m = NULL;
    // Silly code just to get the compiler to emit
    // an unnecessary move and get a match...
    if (randu == 0)
    {
        m = NULL;
        anm->pre_script = pre_ptr;
    }
    else
    {
        anm->pre_script = pre_ptr;
    }

    pre.scr_num = 0;
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

    anm = &anm_blast_high_form;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 400;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 150;
    pre.s_anim = 0;

    anm = &anm_blast_high_form;
    anm->pre_script = &pre;

    pre.scr_num = 1;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.pos.vy += 200;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 100;
    pre.s_anim = 0;

    anm = &anm_blast_high_form;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.speed.vy += 50;
    pre.s_anim = 0;

    anm = &anm_blast_high_form;
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

    anm = &anm_blast_high_form;
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

    anm = &anm_blast_high_form;
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

    anm = &anm_blast_high_form;
    anm->pre_script = &pre;

    pre.scr_num = 2;
    NewAnime( NULL, 0, anm );

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.speed.vx += (offset->vx / 3) >> 2;
    pre.speed.vy += (offset->vy / 3) >> 2;
    pre.speed.vz += (offset->vz / 3) >> 2;
    pre.s_anim = 0;

    anm = &anm_blast_high_form;
    anm->pre_script = &pre;

    pre.scr_num = 3;
    NewAnime( NULL, 0, anm );
}
