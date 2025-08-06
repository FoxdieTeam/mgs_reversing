#include "chafgrnd.h"

#include <stddef.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "bullet/blast.h"
#include "game/game.h"
#include "sd/g_sound.h"
#include "strcode.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern int              dword_800BDF98;
extern int              dword_800BDF9C;
extern int              okajima_CHAF_LIFE;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL5

#define CHAFF_LIFETIME  300

typedef struct _ChaffGrdWork
{
    GV_ACT   actor;
    int      field_20_map;
    int      field_24;
    int      field_28;
    SVECTOR  field_2c;
    SVECTOR  field_34[2][64];
    SVECTOR  field_434[2][64];
    SVECTOR  field_834[64];
    DG_PRIM *field_a34;
    int      field_a38;
    int      field_a3c;
    char     field_a40[64];
    MATRIX   field_a80;
} ChaffGrdWork;

/*---------------------------------------------------------------------------*/

STATIC void chafgrnd_InitParticleSize(TILE *tile)
{
    TILE        *pIter = tile;
    int          i;
    unsigned int rand_width, rand_height;

    for (i = 64; i > 0; i--)
    {
        setTile(pIter);
        rand_width = GV_RandU(2) + 1;
        rand_height = GV_RandU(2) + 1;
        setWH(pIter, rand_width, rand_height);
        pIter++;
    }
}

STATIC void chafgrnd_InitParticleColor(TILE *tile)
{
    int i;

    for (i = 0x40; i > 0; i--)
    {
        tile->r0 = -1;
        tile->g0 = -1;
        tile->b0 = 0;
        tile++;
    }
}

STATIC void chafgrnd_CalcParticlePosition(SVECTOR *va, SVECTOR *vb, SVECTOR *vout)
{
    SVECTOR vec;
    int temp_s0;
    short temp_v0;
    int temp_v1;

    GV_SubVec3(vb, va, &vec);
    vout->vy = ratan2(vec.vx, vec.vz) & 0xfff;

    temp_s0 = vec.vy;
    vec.vy = 0;

    temp_v1 = ratan2(GV_VecLen3(&vec), temp_s0) & 0xfff;

    temp_v0 = temp_v1 - 0x400;
    vout->vx = temp_v0;

    if (temp_v0 < 0)
    {
        vout->vx = temp_v1 + 0xc00;
    }

    vout->vz = 0;
}

STATIC void chafgrnd_Act(ChaffGrdWork* work)
{
    SVECTOR unused;
    SVECTOR sp18;

    int sp20;
    int i;
    int ang;
    int temp_v0_2;

    SVECTOR *var_s4;
    SVECTOR *var_s5;
    SVECTOR *var_s7;

    SVECTOR *pVec;
    SVECTOR *pVec2;

    if (GM_CheckMessage(&work->actor, GV_StrCode("effect"), HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    if (GM_GameStatus & STATE_DEMO)
    {
        GV_DestroyActor(&work->actor);
    }

    GM_GameStatus |= STATE_CHAFF;
    GM_SetCurrentMap(GM_PlayerMap);

    work->field_a34->group_id = GM_PlayerMap;

    if (dword_800BDF98 == TRUE)
    {
        dword_800BDF98 = FALSE;

        work->field_a38 = 64;

        for (i = 0; i < 64; i++)
        {
            work->field_a40[i] = 0;
        }
    }

    if (--okajima_CHAF_LIFE < 0)
    {
        GM_GameStatus &= ~STATE_CHAFF;
        GV_DestroyActor(&work->actor);
        return;
    }

    if ((mts_get_tick_count() - dword_800BDF9C) > 48)
    {
        dword_800BDF9C = mts_get_tick_count();
        GM_SeSet2(0, 63, SE_CHAFF_PARTICLE);
    }

    var_s7 = work->field_834;

    if (work->field_a3c == 1)
    {
        return;
    }

    unused.vz = 0;

    temp_v0_2 = okajima_CHAF_LIFE % 2;
    var_s5 = work->field_34[temp_v0_2];
    var_s4 = work->field_434[temp_v0_2];

    DG_PointCheck(var_s4, 64);

    sp20 = 0;

    if ((okajima_CHAF_LIFE < work->field_28) || (work->field_24 == 1))
    {
        work->field_24 = 1;

        chafgrnd_CalcParticlePosition(&gUnkCameraStruct2_800B7868.eye, &gUnkCameraStruct2_800B7868.center, &sp18);

        pVec = (SVECTOR *)getScratchAddr(0);
        pVec->vx = 0;
        pVec->vy = 0;
        pVec->vz = 2000;

        DG_SetPos2(&gUnkCameraStruct2_800B7868.eye, &sp18);
        DG_PutVector(pVec, pVec, 1);

        sp20 = 1;
        work->field_a34->root = &work->field_a80;
    }

    if (okajima_CHAF_LIFE == work->field_a38)
    {
        work->field_a38 = okajima_CHAF_LIFE - 1;
        work->field_a40[okajima_CHAF_LIFE - 1] = 1;
    }

    for (i = 0; i < 64; i++, var_s5++, var_s4++, var_s7++)
    {
        if (work->field_a40[i])
        {
            *var_s7 = gUnkCameraStruct2_800B7868.eye;
            continue;
        }

        if (sp20)
        {
            if ((var_s4->pad != 1) || (GV_RandU(64) == 0))
            {
                pVec2 = (SVECTOR *)getScratchAddr(0);
                var_s4->vx = pVec2->vx + GV_RandS(4096);
                var_s4->vy = pVec2->vy + GV_RandS(4096);
                var_s4->vz = pVec2->vz + GV_RandS(4096);
            }

            ang = GV_Time + (i * 16);

            if (i > 32)
            {
                var_s4->vx -= rsin(ang * 64) / 128;
                var_s4->vy -= 15;
                var_s4->vz -= rcos(ang * 64) / 128;
            }
            else
            {
                var_s4->vx += rsin(ang * 64) / 128;
                var_s4->vy -= 15;
                var_s4->vz -= rcos(ang * 64) / 128;
            }
        }
        else
        {
            var_s5->vx = (var_s5->vx * 7) >> 3;
            var_s5->vy -= 5;
            var_s5->vz = (var_s5->vz * 7) >> 3;

            var_s4->vx += var_s5->vx;
            var_s4->vy += var_s5->vy;
            var_s4->vz += var_s5->vz;
        }

        *var_s7 = *var_s4;
    }

    chafgrnd_InitParticleColor(&work->field_a34->packs[GV_Clock]->tiles);
}

STATIC int chafgrnd_GetResources(ChaffGrdWork *work, MATRIX *world)
{
    SVECTOR vec1;
    SVECTOR vec2;
    DG_PRIM *prim;
    int i;
    int j;

    okajima_CHAF_LIFE = CHAFF_LIFETIME;
    dword_800BDF9C = mts_get_tick_count();

    work->field_a38 = 64;
    work->field_24 = 0;
    work->field_28 = okajima_CHAF_LIFE - 60;

    work->field_20_map = GM_CurrentMap;

    work->field_2c.vx = world->t[0];
    work->field_2c.vy = world->t[1];
    work->field_2c.vz = world->t[2];

    work->field_20_map = GM_CurrentMap;

    vec1.vx = 0;
    vec1.vy = 0;
    vec2.vz = 0;

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_TILE, 64, 0, work->field_834, NULL);
    work->field_a34 = prim;

    if (!prim)
    {
        return -1;
    }

    chafgrnd_InitParticleSize(&prim->packs[0]->tiles);
    chafgrnd_InitParticleSize(&prim->packs[1]->tiles);

    work->field_a80 = DG_ZeroMatrix;

    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 2; j++)
        {
            vec1.vz = GV_RandU(1024) + 100;
            vec2.vx = -GV_RandU(512) - 256;
            vec2.vy = GV_RandU(4096);

            DG_SetPos2(&DG_ZeroVector, &vec2);
            DG_PutVector(&vec1, &work->field_34[j][i], 1);

            work->field_434[j][i] = work->field_2c;
        }

        work->field_a40[i] = 0;
    }

    return 0;
}

STATIC void chafgrnd_Die(ChaffGrdWork *work)
{
    GM_GameStatus &= ~STATE_CHAFF;

    GM_FreePrim(work->field_a34);
}

/*---------------------------------------------------------------------------*/

void *NewChaffGrd(MATRIX *world)
{
    SVECTOR vec;
    ChaffGrdWork *work;

    vec.vx = world->t[0];
    vec.vy = world->t[1];
    vec.vz = world->t[2];

    GM_SetCurrentMap(GM_CurrentMap);
    AN_Blast_Minimini(&vec);

    if (GM_GameStatus & STATE_CHAFF)
    {
        okajima_CHAF_LIFE = CHAFF_LIFETIME;
        dword_800BDF98 = TRUE;
        GM_SeSetMode(&vec, SE_CHAFF_EXPLODE, GM_SEMODE_BOMB);
        GM_SetNoise(100, 32, &vec);
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(ChaffGrdWork));

    if (work)
    {
        dword_800BDF98 = FALSE;
        GV_SetNamedActor(&work->actor, &chafgrnd_Act, &chafgrnd_Die, "chafgrnd.c");

        work->field_a3c = 0;
        if (chafgrnd_GetResources(work, world) < 0)
        {
            work->field_a3c = 1;
        }

        GM_SeSetMode(&work->field_2c, SE_CHAFF_EXPLODE, GM_SEMODE_BOMB);
        GM_SetNoise(100, 32, &work->field_2c);
    }

    return (void *)work;
}
