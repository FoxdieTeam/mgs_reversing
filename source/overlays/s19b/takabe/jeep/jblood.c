#include "game/game.h"

#define EXEC_LEVEL 5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  speeds[16];
    SVECTOR  vertices[64];
    int      time;
    MATRIX   world;
    MATRIX  *root;
} Work;

RECT s19b_dword_800C348C = {50, 50, 100, 100};

extern SVECTOR Takabe_JeepSystem[];

void s19b_jblood_800C8448(SVECTOR *pos, SVECTOR *speed, MATRIX *world);

static void InitVerts(Work *work, MATRIX *arg1, int count, int mode)
{
    SVECTOR  sp10[4];
    SVECTOR  diff;
    int      amount;
    SVECTOR *speed;
    SVECTOR *vert;
    int      div;
    int      ang;
    int      x, y, z;
    int      sx, sy, sz;

    speed = work->speeds;
    vert = work->vertices;

    DG_SetPos(arg1);

    switch (mode)
    {
    case 1:
        amount = 4;
        div = 4;
        break;
    case 2:
        amount = count >> 1;
        div = 1;
        break;
    default:
        amount = 4;
        div = 4;
        break;
    }

    while (--count >= 0)
    {
        ang = GV_RandU(4096);
        x = rcos(ang) >> 2;
        z = rsin(ang) >> 2;

        y = GV_RandU(128) + 32;
        x /= y;
        z /= y;

        if (count <= amount)
        {
            y = -y / div;
            x /= div;
            z /= div;
        }

        sp10[0].vx = x;
        sp10[0].vy = y;
        sp10[0].vz = z;

        sp10[3].vx = x * 8;
        sp10[3].vy = y * 8;
        sp10[3].vz = z * 8;

        sx = GV_RandS(64);
        sy = GV_RandS(64);
        sz = GV_RandS(64);

        sp10[1].vx = x + sx;
        sp10[1].vy = y + sy;
        sp10[1].vz = z + sz;

        sp10[2].vx = x - sx;
        sp10[2].vy = y - sy;
        sp10[2].vz = z - sz;

        DG_RotVector(sp10, speed, 1);
        DG_PutVector(sp10, vert, 4);

        if (count >= 15)
        {
            speed->vx /= 4;
            speed->vy /= 4;
            speed->vz /= 4;

            if (work->root)
            {
                diff.vx = vert->vx - work->root->t[0];
                diff.vy = vert->vy - work->root->t[1];
                diff.vz = vert->vz - work->root->t[2];
                s19b_jblood_800C8448(&diff, speed, work->root);
            }
            else
            {
                s19b_jblood_800C8448(vert, speed, NULL);
            }
        }

        speed++;
        vert += 4;
    }
}

static void UpdateVerts(SVECTOR *speed, SVECTOR *vert, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = speed->vx;
        y = speed->vy;
        z = speed->vz;

        vert[0].vx += x;
        vert[0].vy += y;
        vert[0].vz += z;

        vert[3].vx += x;
        vert[3].vy += y;
        vert[3].vz += z;

        vert[1].vx += x;
        vert[1].vy += y;
        vert[1].vz += z;

        vert[2].vx += x;
        vert[2].vy += y;
        vert[2].vz += z;

        speed->vx = x;
        speed->vy = y - 11;
        speed->vz = z;

        vert += 4;
        speed++;
    }
}

static void InitPacks(POLY_FT4 *pack, int n_packs, DG_TEX *tex, int count)
{
    int i;

    for (i = n_packs - 1; i >= 0; i--, pack++)
    {
        setPolyFT4(pack);
        setSemiTrans(pack, 1);
        DG_SetPacketTexture4(pack, tex);

        if (count == 2)
        {
            pack->tpage |= 0x60;
        }
        else
        {
            pack->tpage |= 0x60;
        }
    }
}

static void ShadePacks(POLY_FT4 *pack, int n_packs, int shade)
{
    int i;

    for (i = n_packs - 1; i >= 0; i--)
    {
        setRGB0(pack, shade, shade, shade);
        pack++;
    }
}

static void Act(Work *work)
{
    int      time;
    DG_PRIM *prim;

    GM_CurrentMap = work->map;

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    UpdateVerts(work->speeds, work->vertices, 16);

    prim = work->prim;
    ShadePacks(prim->packs[0], 16, time * 16);
    ShadePacks(prim->packs[1], 16, time * 16);

    work->world.t[0] += Takabe_JeepSystem[3].vx;
    work->world.t[1] += Takabe_JeepSystem[3].vy;
    work->world.t[2] += Takabe_JeepSystem[3].vz;

    DG_SetPos(&work->world);
    DG_PutPrim(&work->prim->world);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, MATRIX *root, int count)
{
    DG_PRIM *prim;
    DG_TEX *tex;

    work->root = root;
    work->map = GM_CurrentMap;

    InitVerts(work, world, 16, count);

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 16, work->vertices, &s19b_dword_800C348C);
    if (!prim)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("blood_1"));
    if (!tex)
    {
        return -1;
    }

    InitPacks(prim->packs[0], 16, tex, count);
    InitPacks(prim->packs[1], 16, tex, count);

    work->time = 16;
    work->world = DG_ZeroMatrix;
    return 0;
}

void *NewJeepBlood(MATRIX *world, int count, MATRIX *root)
{
    SVECTOR rand;
    SVECTOR rot;
    SVECTOR pos;
    Work   *work;
    int     ang;
    short   scale;
    int     i;

    work = NULL;

    if (count == 0)
    {
        DG_SetPos(world);

        ang = GV_RandU(4096);
        rand.vx = rcos(ang) / 4;
        rand.vz = rsin(ang) / 4;

        scale = GV_RandU(128) + 32;
        rand.vx = rand.vx / scale;
        rand.vy = scale;
        rand.vz = rand.vz / scale;

        DG_RotVector(&rand, &rot, 1);
        DG_PutVector(&rand, &pos, 1);

        rot.vx /= 4;
        rot.vy /= 4;
        rot.vz /= 4;

        if (root)
        {
            pos.vx -= root->t[0];
            pos.vy -= root->t[1];
            pos.vz -= root->t[2];
        }

        s19b_jblood_800C8448(&pos, &rot, root);
    }
    else
    {
        for (i = 0; i < count; i++)
        {
            work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
            if (work)
            {
                GV_SetNamedActor(work, Act, Die, "jblood.c");

                if (GetResources(work, world, root, count) < 0)
                {
                    GV_DestroyActor(work);
                    return NULL;
                }
            }
        }
    }

    return work;
}
