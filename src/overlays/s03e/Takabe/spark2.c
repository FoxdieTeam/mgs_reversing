#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "SD/g_sound.h"

typedef struct _Spark2Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    MATRIX   world;
    SVECTOR  vecs[32];
    SVECTOR  vecs2[64];
    SVECTOR  light_pos;
    char     pad3[0x40];
    SVECTOR  pos;
    int      time;
} Spark2Work;

typedef struct _Spark2Prim
{
    DR_TPAGE tpage;
    CVECTOR  color;
    short    x0, y0;
    short    x1, y1;
} Spark2Prim;

extern MATRIX  DG_ZeroMatrix;
extern SVECTOR DG_ZeroVector;
extern int     GV_Clock_800AB920;
extern int     GM_CurrentMap_800AB9B0;

const SVECTOR spark2_light_pos = {0, 0, 500, 0};

#define EXEC_LEVEL 5

void s03e_spark2_800CA0E8(int count)
{
    MATRIX  *rot;
    SVECTOR *rotvec;
    SVECTOR *in;
    SVECTOR *out;

    rot = (MATRIX *)0x1F800000;
    rotvec = (SVECTOR *)0x1F800028;
    in = (SVECTOR *)0x1F800020;
    out = (SVECTOR *)0x1F800030;

    *in = DG_ZeroVector;
    rotvec->vz = 0;

    while (--count >= 0)
    {
        rotvec->vx = GV_RandS(512);
        rotvec->vy = GV_RandS(512);

        RotMatrixYXZ_gte(rotvec, rot);
        DG_SetPos(rot);

        in->vz = GV_RandU(256) + 64;
        DG_RotVector(in, out, 1);

        out++;
    }
}

void s03e_spark2_800CA1CC(SVECTOR *vec1, SVECTOR *vec2, MATRIX *world, int count)
{
    SVECTOR *scratch;
    int      x, y, z;

    scratch = (SVECTOR *)getScratchAddr(12);

    DG_SetPos(world);
    DG_RotVector(scratch, scratch, count);

    while (--count >= 0)
    {
        x = scratch->vx;
        y = scratch->vy;
        z = scratch->vz;

        vec1->vx = x;
        vec1->vy = y;
        vec1->vz = z;

        vec2[0].vx = x;
        vec2[0].vy = y;
        vec2[0].vz = z;

        vec2[1].vx = x / 4;
        vec2[1].vy = y / 4;
        vec2[1].vz = z / 4;

        vec2 += 2;
        vec1++;
        scratch++;
    }
}

void s03e_spark2_800CA2D4(SVECTOR *vec1, SVECTOR *vec2, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = vec1->vx;
        y = vec1->vy;
        z = vec1->vz;

        vec2[1] = vec2[0];

        vec2->vx += x;
        vec2->vy += y;
        vec2->vz += z;

        vec1->vx = x - x / 4;
        vec1->vy = y - y / 4 - 3;
        vec1->vz = z - z / 4;

        vec2 += 2;
        vec1++;
    }
}

void s03e_spark2_800CA3A8(Spark2Prim *packs, int n_packs)
{
    while (--n_packs >= 0)
    {
        packs->tpage.tag = 0x04000000;
        packs->tpage.code[0] = _get_mode(0, 1, getTPage(0, 1, 0, 0));
        LSTORE(0x428080FF, &packs->color);
        packs++;
    }
}

void s03e_spark2_800CA3F0(Spark2Prim *packs, int n_packs, int brightness)
{
    while (--n_packs >= 0)
    {
        packs->color.r = brightness;
        packs->color.g = brightness / 2;
        packs->color.b = brightness / 2;
        packs++;
    }
}

void s03e_spark2_800CA428(Spark2Work *work)
{
    DG_PRIM *prim;
    int      time;
    int      old_time;
    int      brightness;

    GM_CurrentMap_800AB9B0 = work->map;

    if (work->time == 32)
    {
        GM_SeSet_80032858(&work->pos, SE_SPARKS);
    }

    old_time = work->time;
    time = --work->time;

    if (work->time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s03e_spark2_800CA2D4(work->vecs, work->vecs2, 32);

    prim = work->prim;

    brightness = (time * 16) + 50;
    if (brightness > 255)
    {
        brightness = 255;
    }

    s03e_spark2_800CA3F0((Spark2Prim *)prim->packs[GV_Clock_800AB920], 32, brightness);

    brightness = (old_time - 29) * 512;
    if (brightness > 0)
    {
        DG_SetTmpLight(&work->light_pos, brightness, 1000);
    }

    work->world.t[1] -= 16;

    DG_SetPos(&work->world);
    DG_PutPrim(&prim->world);
}

void s03e_spark2_800CA520(Spark2Work *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int s03e_spark2_800CA55C(Spark2Work *work, MATRIX *world)
{
    SVECTOR  light_pos;
    DG_PRIM *prim;

    work->map = GM_CurrentMap_800AB9B0;

    s03e_spark2_800CA0E8(32);
    s03e_spark2_800CA1CC(work->vecs, work->vecs2, world, 32);

    DG_SetFreePrimParam(20, 2, 12, 4);

    prim = DG_GetPrim(DG_PRIM_FREE, 32, 0, work->vecs2, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos(world);
    DG_PutPrim(&prim->world);

    light_pos = spark2_light_pos;
    DG_PutVector(&light_pos, &work->light_pos, 1);

    s03e_spark2_800CA3A8((Spark2Prim *)prim->packs[0], 32);
    s03e_spark2_800CA3A8((Spark2Prim *)prim->packs[1], 32);

    work->world = DG_ZeroMatrix;
    work->world.t[0] = world->t[0];
    work->world.t[1] = world->t[1];
    work->world.t[2] = world->t[2];

    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];

    work->time = 32;

    return 0;
}

GV_ACT *NewSpark2_800CA714(MATRIX *world)
{
    Spark2Work *work;

    work = (Spark2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Spark2Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)s03e_spark2_800CA428,
                         (TActorFunction)s03e_spark2_800CA520, "spark2.c");

        if (s03e_spark2_800CA55C(work, world) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
