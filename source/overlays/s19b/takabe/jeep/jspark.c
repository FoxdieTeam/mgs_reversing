#include <rand.h>

#include "game/game.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
    char     pad4[0x1C];
    MATRIX   world;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL 5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  speeds[8];
    SVECTOR  vertices[32];
    SVECTOR  pos;
    int      count;
    MATRIX   world;
} Work;

static int random_index1 = -1;
static int random_index2 = 0;

static u_short SECTION(".bss") random_table[64];

static void InitRand(void)
{
    int      rnd;
    u_short *table;
    int      i;

    if (random_index1 != -1)
    {
        rnd = rand();

        random_index1 = (random_index1 + 1) & 0x3F;
        random_table[random_index1] = rnd;
    }
    else
    {
        random_index1 = 0;
        random_index2 = 0;

        table = random_table;
        for (i = 64; i > 0; i--)
        {
            *table++ = rand();
        }
    }
}

static inline int NextRand(void)
{
    u_short *table;

    table = random_table;

    random_index2++;
    random_index2 &= 0x3F;
    return table[random_index2];
}

static void InitVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    MATRIX  mat;
    MATRIX  old;
    SVECTOR rot;
    SVECTOR pos;
    SVECTOR vert;
    int     rot_x;
    int     x, y, z;
    int     rx, ry, rz;

    gte_ReadRotMatrix(&old);

    pos = DG_ZeroVector;
    rot.vz = 0;

    while (--count >= 0)
    {
        rot.vy = NextRand() & 0xFFF;
        rot_x = rot.vx = NextRand() & 0x1FF;

        RotMatrixYXZ_gte(&rot, &mat);
        pos.vy = -16384 / (rot_x + 64);
        ApplyMatrixSV(&mat, &pos, &vert);

        *speeds = vert;

        x = vert.vx;
        y = vert.vy;
        z = vert.vz;

        verts[0].vx = x;
        verts[0].vy = y;
        verts[0].vz = z;

        verts[3].vx = x * 4;
        verts[3].vy = y * 4;
        verts[3].vz = z * 4;

        rx = (NextRand() & 0x7F) - 64;
        ry = (NextRand() & 0x7F) - 64;
        rz = (NextRand() & 0x7F) - 64;

        x = x * 4 - x;
        y = y * 4 - y;
        z = z * 4 - z;

        verts[1].vx = x + rx;
        verts[1].vy = y + ry;
        verts[1].vz = z + rz;

        verts[2].vx = x - rx;
        verts[2].vy = y - ry;
        verts[2].vz = z - rz;

        speeds++;
        verts += 4;
    }

    gte_SetRotMatrix(&old);
    gte_SetTransMatrix(&old);
}

static void UpdateVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = speeds->vx;
        y = speeds->vy;
        z = speeds->vz;

        verts[0].vx += x;
        verts[0].vy += y;
        verts[0].vz += z;

        verts[3].vx += x;
        verts[3].vy += y;
        verts[3].vz += z;

        verts[1].vx += x;
        verts[1].vy += y;
        verts[1].vz += z;

        verts[2].vx += x;
        verts[2].vy += y;
        verts[2].vz += z;

        speeds->vx = x - (x / 8);
        speeds->vy = y - (y / 8);
        speeds->vz = z - (z / 8);

        verts += 4;
        speeds++;
    }
}

static void InitPacks(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    POLY_FT4 *spad;

    spad = (POLY_FT4 *)getScratchAddr(0);
    setPolyFT4(spad);
    setSemiTrans(spad, 1);
    DG_SetPacketTexture4(spad, tex);

    while (--n_packs >= 0)
    {
        LCOPY2(&spad->tag, &packs->tag, &spad->r0, &packs->r0);
        LCOPY(&spad->u0, &packs->u0);
        LCOPY(&spad->u1, &packs->u1);
        LCOPY(&spad->u2, &packs->u2);
        LCOPY(&spad->u3, &packs->u3);
        packs++;
    }
}

static void ShadePacks(POLY_FT4 *packs, int n_packs, int shade)
{
    int color;

    color = MAKE_RGB(shade, shade, shade);
    while (--n_packs >= 0)
    {
        LSTORE((LLOAD(&packs->r0) & RGBA_A_MASK) | color, &packs->r0);
        packs++;
    }
}

static void Act(Work *work)
{
    int      unused[2];
    int      val1, val2;
    DG_PRIM *prim;
    int      bright;

    GM_CurrentMap = work->map;

    work->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->world.t[2] += Takabe_JeepSystem.pos.vz;

    DG_SetPos(&work->world);
    DG_PutPrim(&work->prim->world);

    val1 = work->count--;
    val2 = work->count;

    if (work->count <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    UpdateVerts(work->speeds, work->vertices, 8);

    prim = work->prim;
    ShadePacks(prim->packs[0], 8, val2 * 16);
    ShadePacks(prim->packs[1], 8, val2 * 16);

    bright = (val1 - 9) * 512;
    if (bright > 0)
    {
        DG_SetTmpLight(&work->pos, bright >> 1, 500);
    }
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

    InitRand();
    InitVerts(work->speeds, work->vertices, 8);

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 8, work->vertices, NULL);
    if (prim != NULL)
    {
        work->world = *world;

        DG_SetPos(world);
        DG_PutPrim(&prim->world);

        work->pos.vx = world->t[0];
        work->pos.vy = world->t[1];
        work->pos.vz = world->t[2];

        tex = DG_GetTexture(GV_StrCode("spark_fl"));
        if (tex == NULL)
        {
            return -1;
        }

        InitPacks(prim->packs[0], 8, tex);
        InitPacks(prim->packs[1], 8, tex);

        work->count = 12;
        return 0;
    }

    return -1;
}

void *NewJeepSpark(MATRIX *world, int count)
{
    Work *work;
    int   i;

    work = NULL;

    for (i = 0; i <= count; i++)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

        if (work != NULL)
        {
            GV_SetNamedActor(work, Act, Die, "jspark.c");

            SetSpadStack(SPAD_STACK_ADDR);

            if (GetResources(work, world) < 0)
            {
                ResetSpadStack();
                GV_DestroyActor(work);
                return NULL;
            }

            ResetSpadStack();
        }
    }

    return work;
}
