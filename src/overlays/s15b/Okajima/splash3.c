#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Splash3Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  off[32];
    SVECTOR  pos[128];
    int      time;
    MATRIX   world[4];
} Splash3Work;

RECT s15b_800C3398 = {100, 100, 200, 200};

extern int GV_Clock;
extern int GM_CurrentMap;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void Splash3InitVecs_800C7D24(MATRIX *world, SVECTOR *vec1, SVECTOR *vec2, int n_vecs, int n_matrices)
{
    SVECTOR vec[4];
    int     i, j;
    int     ang;
    int     x, y, z;
    int     xoff, zoff;

    for (i = 0; i < n_matrices; i++)
    {
        DG_SetPos(world);

        for (j = n_vecs - 1; j >= 0; j--)
        {
            ang = GV_RandU(4096);
            x = rcos(ang);
            z = rsin(ang);

            y = GV_RandU(128) + 128;
            x /= y;
            z /= y;

            xoff = GV_RandS(1024);
            zoff = GV_RandS(1024);

            vec[0].vy = y;
            vec[1].vy = y * 2;
            vec[2].vy = y * 2;
            vec[3].vy = y * 4;

            vec[0].vx = x;
            vec[0].vz = z;
            vec[1].vx = x + xoff;
            vec[1].vz = z + zoff;
            vec[2].vx = x - xoff;
            vec[2].vz = z - zoff;
            vec[3].vx = x * 4;
            vec[3].vz = z * 4;

            DG_RotVector(vec, vec1, 1);
            DG_PutVector(vec, vec2, 4);

            vec1++;
            vec2 += 4;
        }

        world++;
    }
}

void Splash3ShadePacks_800C7EF0(POLY_FT4 *packs, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}

void Splash3Act_800C7F1C(Splash3Work *work)
{
    int       r, g, b;
    POLY_FT4 *packs;
    int       i;
    SVECTOR  *off;
    SVECTOR  *vec;
    int       x, y, z;

    GM_CurrentMap = work->map;

    g = --work->time;
    if (work->time <= 0)
    {
        Splash3ShadePacks_800C7EF0(&work->prim->packs[0]->poly_ft4, 32, 0);
        Splash3ShadePacks_800C7EF0(&work->prim->packs[1]->poly_ft4, 32, 0);
        GV_DestroyActor(&work->actor);
        return;
    }

    g *= 10;

    packs = &work->prim->packs[GV_Clock]->poly_ft4;
    off = work->off;
    vec = work->pos;

    r = g / 2;
    b = (g * 3) / 4;

    for (i = 31; i >= 0; i--)
    {
        x = off->vx;
        y = off->vy;
        z = off->vz;

        vec->vx += x;
        vec->vy += y;
        vec->vz += z;
        vec++;

        vec->vx += x;
        vec->vy += y;
        vec->vz += z;
        vec++;

        vec->vx += x;
        vec->vy += y;
        vec->vz += z;
        vec++;

        vec->vx += x;
        vec->vy += y;
        vec->vz += z;
        vec++;

        off->vy -= 7;
        off++;

        setRGB0(packs, r, g, b);
        packs++;
    }
}

void Splash3Die_800C80D0(Splash3Work *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

static inline void Splash3InitPack(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    setPolyFT4(pack);
    setSemiTrans(pack, 1);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(pack, x, y, w, h);

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
    pack->tpage |= 0x20;

    setRGB0(pack, 255, 255, 255);
}

#define Splash3Init()                                                    \
do {                                                                     \
    SVECTOR   rot;                                                       \
    VECTOR    scale;                                                     \
    POLY_FT4 *packs0;                                                    \
    POLY_FT4 *packs1;                                                    \
    MATRIX   *world;                                                     \
    int       i, j;                                                      \
                                                                         \
    packs0 = (POLY_FT4 *)prim->packs[0];                     \
    packs1 = (POLY_FT4 *)prim->packs[1];                     \
                                                                         \
    rot.vz = 0;                                                          \
                                                                         \
    world = work->world;                                                 \
                                                                         \
    for (i = 0; i < 4; i++, world++)                                     \
    {                                                                    \
        rot.vx = GV_RandS(128) + 500;                           \
        rot.vy = dir + GV_RandS(256);                           \
        RotMatrixYXZ_gte(&rot, world);                                   \
                                                                         \
        world->t[0] = pos->vx + GV_RandS(1024);                 \
        world->t[1] = pos->vy;                                           \
        world->t[2] = pos->vz + GV_RandS(1024);                 \
                                                                         \
        scale.vx = scale.vy = scale.vz = GV_RandS(2048) + 4096; \
                                                                         \
        ScaleMatrix(world, &scale);                                      \
                                                                         \
        for (j = 7; j >= 0; j--)                                         \
        {                                                                \
            Splash3InitPack(packs0, tex);                                \
            Splash3InitPack(packs1, tex);                                \
                                                                         \
            packs0++;                                                    \
            packs1++;                                                    \
        }                                                                \
    }                                                                    \
                                                                         \
    Splash3InitVecs_800C7D24(work->world, work->off, work->pos, 8, 4);   \
                                                                         \
    work->time = 25;                                                     \
    return 0;                                                            \
} while (0)

int Splash3GetResources_800C810C(Splash3Work *work, int dir, SVECTOR *pos)
{
    DG_PRIM  *prim;
    int       texid;
    DG_TEX   *tex;

    work->map = GM_CurrentMap;

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 32, 0, work->pos, &s15b_800C3398);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    texid = GV_StrCode("awa_3");
    tex = DG_GetTexture(texid);
    if (tex == NULL)
    {
        return -1;
    }

    Splash3Init(); // Not sure why this is needed
}

void *NewSplash3_800C83D0(int dir, SVECTOR *pos)
{
    Splash3Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Splash3Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Splash3Act_800C7F1C, Splash3Die_800C80D0, "splash3.c");

        if (Splash3GetResources_800C810C(work, dir, pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
