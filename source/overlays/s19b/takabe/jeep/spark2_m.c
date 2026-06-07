#include "game/game.h"

typedef struct _JEEP_SYSTEM_S
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
} JEEP_SYSTEM_S;

extern JEEP_SYSTEM_S Takabe_JeepSystem;

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    MATRIX   world;
    SVECTOR  speeds[16];
    SVECTOR  verts[32];
    char     unused[0x28];
    int      time;
} Work;

static void InitVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    MATRIX  mat;
    SVECTOR rot;
    SVECTOR pos;
    int     x, y, z;

    pos = DG_ZeroVector;

    rot.vz = 0;

    while (--count >= 0)
    {
        rot.vx = GV_RandS(256);
        rot.vy = GV_RandS(256);

        RotMatrixYXZ_gte(&rot, &mat);
        DG_SetPos(&mat);

        pos.vz = GV_RandU(256) + 64;
        DG_RotVector(&pos, speeds, 1);

        x = speeds->vx / 2;
        y = speeds->vy / 2;
        z = speeds->vz / 2;

        verts[0].vx = x;
        verts[0].vy = y;
        verts[0].vz = z;

        verts[1].vx = x / 4;
        verts[1].vy = y / 4;
        verts[1].vz = z / 4;

        verts += 2;
        speeds++;
    }
}

static void UpdateVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = speeds->vx;
        y = speeds->vy;
        z = speeds->vz;

        verts[1] = verts[0];

        verts->vx += x;
        verts->vy += y - 16;
        verts->vz += z;

        speeds->vx = x - x / 4;
        speeds->vy = y - y / 4;
        speeds->vz = z - z / 4;

        verts += 2;
        speeds++;
    }
}

static void InitPacks(LINE_F2 *packs, int n_packs, int bright)
{
    while (--n_packs >= 0)
    {
        setLineF2(packs);
        packs++;
    }
}

static void ShadePacks(LINE_F2 *packs, int n_packs, int bright)
{
    int color;

    color = bright | (bright / 2) << 8 | (bright / 2) << 16;
    while (--n_packs >= 0)
    {
        LSTORE((LLOAD(&packs->r0) & 0xFF000000) | color, &packs->r0);
        packs++;
    }
}

static void Act(Work *work)
{
    int      time;
    DG_PRIM *prim;
    int      shade;

    GM_CurrentMap = work->map;

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    UpdateVerts(work->speeds, work->verts, 16);

    prim = work->prim;

    shade = (time * 16) + 50;
    if (shade > 255)
    {
        shade = 255;
    }

    ShadePacks(prim->packs[GV_Clock], 16, shade);

    work->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->world.t[2] += Takabe_JeepSystem.pos.vz;

    DG_SetPos(&work->world);
    DG_PutPrim(work->prim);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world)
{
    DG_PRIM *prim;

    work->map = GM_CurrentMap;

    InitVerts(work->speeds, work->verts, 16);

    prim = GM_MakePrim(DG_PRIM_LINE_F2, 16, work->verts, NULL);
    work->prim = prim;
    if (prim != NULL)
    {
        DG_SetPos(world);
        DG_PutPrim(prim);
        work->world = *world;

        InitPacks(prim->packs[0], 16, 0);
        InitPacks(prim->packs[1], 16, 0);
        ShadePacks(prim->packs[GV_Clock], 16, 255);

        work->time = 16;
        return 0;
    }

    return -1;
}

void *NewSpark2M(MATRIX *world)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "spark2_m.c");

        SetSpadStack(SPAD_STACK_ADDR);

        if (GetResources(work, world) < 0)
        {
            ResetSpadStack();

            GV_DestroyActor(&work->actor);
            return NULL;
        }

        ResetSpadStack();
    }
    return (void *)work;
}

void s19b_fadeio_800DA784(void)
{
    GV_ZeroMemory(&Takabe_JeepSystem, 0x16C);
}
