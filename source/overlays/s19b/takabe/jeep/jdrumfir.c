#include "strcode.h"
#include "game/game.h"
#include "takabe/prim.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x18];
    SVECTOR  field_38;
    int      field_40;
    char     pad4[0x1C];
    OBJECT  *body;
    char     pad5[0x18];
    int      field_7C;
    MATRIX   world;
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           // 0x20
    DG_PRIM *prim;          // 0x24
    DG_TEX  *tex;           // 0x28
    MATRIX   world;         // 0x2C
    MATRIX  *root;          // 0x4C
    int      flag;          // 0x50
    int      time;          // 0x54
    int      count;         // 0x58
    int      interval;      // 0x5C
    int      index;         // 0x60
    SVECTOR  vertices[16];  // 0x64
    SVECTOR  params[16];    // 0xE4: vx = life, vy = fade, vz = anim frame
} Work;

void s19b_jdrumfir_800CA4A0(Work *work);
void s19b_jdrumfir_800CA564(Work *work, int);

void s19b_jdrumfir_800CA13C(Work *work)
{
    GM_CurrentMap = work->map;

    work->prim->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->prim->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->prim->world.t[2] += Takabe_JeepSystem.pos.vz;

    if (work->prim->world.t[2] > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->flag & 1)
    {
        work->world = *work->root;
    }

    if (work->time > 0)
    {
        s19b_jdrumfir_800CA564(work, 1);
    }
    else
    {
        s19b_jdrumfir_800CA564(work, 1);

        if (work->count == 0)
        {
            GV_DestroyActor(work);
            return;
        }

        work->count--;
    }

    work->time--;
}

void s19b_jdrumfir_800CA280(Work *work)
{
    GM_FreePrim(work->prim);
}

int s19b_jdrumfir_800CA2BC(Work *work, MATRIX *world, int arg2, int arg3)
{
    work->root = world;
    work->map = GM_CurrentMap;
    work->world = *world;

    work->flag = arg2;
    work->time = arg3;

    s19b_jdrumfir_800CA4A0(work);
    work->count = 40;
    return 0;
}

void *NewJeepDrumFire(MATRIX *world, int arg1, int arg2)
{
    Work* work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jdrumfir_800CA13C, s19b_jdrumfir_800CA280, "jdrumfir.c");

        if (s19b_jdrumfir_800CA2BC(work, world, arg1, arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

void s19b_jdrumfir_800CA3E8(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int x, y, w, h;

    while (--n_packs != -1)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;
        packs->u0 = packs->u2 = x;
        packs->u1 = packs->u3 = x + (w + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h;
        packs->v0 = packs->v1 = y;
        packs->v2 = packs->v3 = y + (h + 1) / 4 - 1;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= (3 << 5);

        setRGB0(packs, 0, 0, 0);
        packs++;
    }
}

void s19b_jdrumfir_800CA4A0(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = work->tex = DG_GetTexture(PCX_FIRE2);
    prim = work->prim = Takabe_MakeIndividualRect3DPrim(16, work->vertices);

    s19b_jdrumfir_800CA3E8(prim->packs[0], tex, 16);
    s19b_jdrumfir_800CA3E8(prim->packs[1], tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->raise = 500;
}

void s19b_jdrumfir_800CA564(Work *work, int spawn)
{
    SVECTOR  *param;
    SVECTOR  *vert;
    POLY_FT4 *packs;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    if (spawn != 0)
    {
        if (work->interval < 0)
        {
            param = &work->params[work->index];
            param->vx = work->count;
            param->vy = 255;
            param->vz = GV_RandU(16);

            vert = &work->vertices[work->index];
            vert->vx = work->world.t[0] + GV_RandS(256) / 2;
            vert->vz = work->world.t[2] + GV_RandS(256) / 2;

            vert->pad = work->count * 20 - 200;
            if (vert->pad < 200)
            {
                vert->pad = 200;
            }

            vert->vy = work->world.t[1] + vert->pad;

            work->interval = 12;
            work->index = (work->index + 1) & 15;
        }
        else
        {
            work->interval--;
        }
    }

    param = work->params;
    vert = work->vertices;
    packs = work->prim->packs[GV_Clock];

    for (i = 16; i > 0; i--)
    {
        if (param->vx != 0)
        {
            xs = param->vz & 3;
            ys = param->vz / 4;

            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 4;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 4 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++param->vz >= 16)
            {
                param->vz = 0;
            }

            shade = param->vx * 16;
            if (shade > 255)
            {
                shade = 255;
            }

            if (param->vy > 0)
            {
                shade -= param->vy;
                if (shade < 0)
                {
                    shade = 0;
                }

                param->vy /= 2;
            }

            setRGB0(packs, shade, shade, shade);

            vert->pad -= 10;
            if (vert->pad < 200)
            {
                vert->pad = 200;
            }

            if (vert->pad != 200)
            {
                vert->vy -= 10;
            }

            param->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        param++;
        packs++;
    }
}
