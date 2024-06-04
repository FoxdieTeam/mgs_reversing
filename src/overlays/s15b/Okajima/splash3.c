#include "libdg/libdg.h"
#include "libgv/libgv.h"

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

extern int GV_Clock_800AB920;
extern int GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

void Splash3InitVecs_800C7D24(MATRIX *world, SVECTOR *vec1, SVECTOR *vec2, int n_vecs, int n_matrices)
{
    SVECTOR vec[4];
    int     i, j;
    int     ang;
    int     x, y, z;
    int     xoff, zoff;

    for (i = 0; i < n_matrices; i++)
    {
        DG_SetPos_8001BC44(world);

        for (j = n_vecs - 1; j >= 0; j--)
        {
            ang = GV_RandU_80017090(4096);
            x = rcos(ang);
            z = rsin(ang);

            y = GV_RandU_80017090(128) + 128;
            x /= y;
            z /= y;

            xoff = GV_RandS_800170BC(1024);
            zoff = GV_RandS_800170BC(1024);

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

            DG_RotVector_8001BE98(vec, vec1, 1);
            DG_PutVector_8001BE48(vec, vec2, 4);

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

    GM_CurrentMap_800AB9B0 = work->map;

    g = --work->time;
    if (work->time <= 0)
    {
        Splash3ShadePacks_800C7EF0(&work->prim->packs[0]->poly_ft4, 32, 0);
        Splash3ShadePacks_800C7EF0(&work->prim->packs[1]->poly_ft4, 32, 0);
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    g *= 10;

    packs = &work->prim->packs[GV_Clock_800AB920]->poly_ft4;
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
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

static inline void Splash3InitPack(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    setPolyFT4(pack);
    setSemiTrans(pack, 1);

    x = tex->field_8_offx;
    w = tex->field_A_width;
    y = tex->field_9_offy;
    h = tex->field_B_height;
    setUVWH(pack, x, y, w, h);

    pack->tpage = tex->field_4_tPage;
    pack->clut = tex->field_6_clut;
    pack->tpage |= 0x20;

    setRGB0(pack, 255, 255, 255);
}

#define Splash3Init                                                      \
do                                                                       \
{                                                                        \
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
        rot.vx = GV_RandS_800170BC(128) + 500;                           \
        rot.vy = dir + GV_RandS_800170BC(256);                           \
        RotMatrixYXZ_gte(&rot, world);                                   \
                                                                         \
        world->t[0] = pos->vx + GV_RandS_800170BC(1024);                 \
        world->t[1] = pos->vy;                                           \
        world->t[2] = pos->vz + GV_RandS_800170BC(1024);                 \
                                                                         \
        scale.vx = scale.vy = scale.vz = GV_RandS_800170BC(2048) + 4096; \
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

    work->map = GM_CurrentMap_800AB9B0;

    prim = DG_GetPrim(0x12, 32, 0, work->pos, &s15b_800C3398);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    texid = GV_StrCode_80016CCC("awa_3");
    tex = DG_GetTexture_8001D830(texid);
    if (tex == NULL)
    {
        return -1;
    }

    Splash3Init; // Not sure why this is needed
}

GV_ACT * NewSplash3_800C83D0(int dir, SVECTOR *pos)
{
    Splash3Work *work;

    work = (Splash3Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Splash3Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Splash3Act_800C7F1C, (TActorFunction)Splash3Die_800C80D0, "splash3.c");

        if (Splash3GetResources_800C810C(work, dir, pos) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
