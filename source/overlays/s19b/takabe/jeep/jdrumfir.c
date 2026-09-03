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

#define EXEC_LEVEL GV_ACTOR_USER

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX   world;
    MATRIX  *root;
    int      field_50;
    int      field_54;
    int      field_58;
    int      field_5C;
    int      field_60;
    SVECTOR  vertices[16];
    SVECTOR  speeds[16];
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

    if (work->field_50 & 1)
    {
        work->world = *work->root;
    }

    if (work->field_54 > 0)
    {
        s19b_jdrumfir_800CA564(work, 1);
    }
    else
    {
        s19b_jdrumfir_800CA564(work, 1);

        if (work->field_58 == 0)
        {
            GV_DestroyActor(work);
            return;
        }

        work->field_58--;
    }

    work->field_54--;
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

    work->field_50 = arg2;
    work->field_54 = arg3;

    s19b_jdrumfir_800CA4A0(work);
    work->field_58 = 40;
    return 0;
}

void *NewJeepDrumFire(MATRIX *world, int arg1, int arg2)
{
    Work* work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
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

void s19b_jdrumfir_800CA564(Work *work, int arg1)
{
    POLY_FT4 *pack;
    SVECTOR  *vtx;
    SVECTOR  *spd;
    int       i;
    int       col;
    int       row;
    int       x, y, w, h;
    int       bright;
    int       flash;

    if (arg1 != 0)
    {
        if (work->field_5C < 0)
        {
            spd = &work->speeds[work->field_60];
            spd->vx = work->field_58;
            spd->vy = 255;
            spd->vz = GV_RandU(16);

            vtx = &work->vertices[work->field_60];
            vtx->vx = work->world.t[0] + GV_RandS(256) / 2;
            vtx->vz = work->world.t[2] + GV_RandS(256) / 2;
            vtx->pad = work->field_58 * 20 - 200;
            if (vtx->pad < 200)
            {
                vtx->pad = 200;
            }
            vtx->vy = work->world.t[1] + vtx->pad;

            work->field_5C = 12;
            work->field_60 = (work->field_60 + 1) & 0xF;
        }
        else
        {
            work->field_5C--;
        }
    }

    spd  = work->speeds;
    vtx  = work->vertices;
    pack = work->prim->packs[GV_Clock];

    for (i = 16; i > 0; vtx++, spd++, pack++, i--)
    {
        if (spd->vx != 0)
        {
            col = spd->vz & 3;
            row = spd->vz / 4;

            x = work->tex->off_x;
            w = work->tex->w;
            pack->u0 = pack->u2 = x + (w + 1) * col / 4;
            pack->u1 = pack->u3 = x + (w + 1) * (col + 1) / 4 - 1;

            y = work->tex->off_y;
            h = work->tex->h;
            pack->v0 = pack->v1 = y + (h + 1) * row / 4;
            pack->v2 = pack->v3 = y + (h + 1) * (row + 1) / 4 - 1;

            spd->vz++;
            if (spd->vz >= 16)
            {
                spd->vz = 0;
            }

            bright = spd->vx * 16;
            if (bright >= 256)
            {
                bright = 255;
            }
            flash = spd->vy;
            if (flash > 0)
            {
                bright -= flash;
                if (bright < 0)
                {
                    bright = 0;
                }
                spd->vy = flash / 2;
            }
            pack->r0 = bright;
            pack->g0 = bright;
            pack->b0 = bright;

            vtx->pad -= 10;
            if (vtx->pad < 200)
            {
                vtx->pad = 200;
            }
            if (vtx->pad != 200)
            {
                vtx->vy -= 10;
            }
            spd->vx--;
        }
        else
        {
            vtx->pad = 0;
            pack->r0 = 0;
            pack->g0 = 0;
            pack->b0 = 0;
        }
    }
}
