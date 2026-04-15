#include "game/game.h"

#define EXEC_LEVEL  5

#define PRIM_COUNT  8

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  offset[PRIM_COUNT];
    SVECTOR  verts[PRIM_COUNT * 4];
    SVECTOR  speed[PRIM_COUNT];
    int      time;
} Work;

static void InitVerts(SVECTOR *offsets, SVECTOR *verts, SVECTOR *speeds, int count)
{
    SVECTOR pos[4];
    MATRIX  rot;
    SVECTOR ang;

    pos[0].vx = -105;
    pos[0].vy = 0;
    pos[0].vz = 145;
    pos[1].vx = 105;
    pos[1].vy = 0;
    pos[1].vz = 145;
    pos[2].vx = -105;
    pos[2].vy = 0;
    pos[2].vz = -145;
    pos[3].vx = 105;
    pos[3].vy = 0;
    pos[3].vz = -145;

    rot.t[1] = 0;

    while (--count >= 0)
    {
        ang.vx = GV_RandS(128);
        ang.vy = GV_RandS(256);
        ang.vz = GV_RandS(128);

        rot.t[0] = GV_RandS(128);
        rot.t[2] = GV_RandS(128);
        RotMatrixYXZ(&ang, &rot);
        DG_SetPos(&rot);
        DG_PutVector(pos, verts, 4);

        offsets->vy = GV_RandS(32) + 90;
        offsets->vy = GV_RandS(64) + 150;
        offsets->vx = GV_RandS(32);
        offsets->vz = GV_RandU(32) + 32;

        speeds->vx = GV_RandS(8);
        speeds->vy = GV_RandU(8);
        speeds->vz = 0;

        verts += 4;
        offsets++;
        speeds++;
    }
}

static void UpdateVerts(SVECTOR *offsets, SVECTOR *verts, SVECTOR *speeds, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = offsets->vx;
        y = offsets->vy;
        z = offsets->vz;

        if (x > 0)
        {
            speeds->vx -= 2;
        }
        else
        {
            speeds->vx += 2;
        }

        if (z > 0)
        {
            speeds->vz -= 2;
        }
        else
        {
            speeds->vz += 2;
        }

        offsets->vx += speeds->vx;
        offsets->vz += speeds->vz;

        if (y > 0)
        {
            x *= 2;
            z *= 2;
            offsets->vy -= 12;
        }
        else if (++offsets->vy > 0)
        {
            offsets->vy = -24;
            speeds->vx = GV_RandS(8);
            speeds->vz = GV_RandS(8);
        }

        verts[0].vx += x;
        verts[0].vy += y;
        verts[0].vz += z;

        verts[1].vx += x;
        verts[1].vy += y;
        verts[1].vz += z;

        verts[2].vx += x;
        verts[2].vy += y;
        verts[2].vz += z;

        verts[3].vx += x;
        verts[3].vy += y;
        verts[3].vz += z;

        verts += 4;
        offsets++;
        speeds++;
    }
}

static void InitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setPolyFT4(packs1);
        DG_SetPacketTexture4(packs0, tex);
        DG_SetPacketTexture4(packs1, tex);
        packs0++;
        packs1++;
    }
}

static void ShadePacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);
        packs0++;
        packs1++;
    }
}

static void Act(Work *work)
{
    short time;
    short shade;

    GM_SetCurrentMap(work->map);

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    UpdateVerts(work->offset, work->verts, work->speed, PRIM_COUNT);

    shade = time * 4 + 50;
    if (shade > 128)
    {
        shade = 128;
    }

    ShadePacks(work->prim->packs[0], work->prim->packs[1], PRIM_COUNT, shade);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap;

    InitVerts(work->offset, work->verts, work->speed, PRIM_COUNT);

    prim = work->prim = GM_MakePrim(DG_PRIM_POLY_FT4, PRIM_COUNT, work->verts, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos(world);
    DG_PutPrim(&prim->world);

    tex = DG_GetTexture(GV_StrCode("paper"));
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], prim->packs[1], PRIM_COUNT, tex);

    work->time = 64;
    return 0;
}

void *NewPaperFall(MATRIX *world)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "pfall.c");

        if (GetResources(work, world) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
