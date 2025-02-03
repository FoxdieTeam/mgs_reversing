#include "ir_cens.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "overlays/s00a/Enemy/enemy.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _IrCensWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  f30[16];
    SVECTOR  fB0;
    SVECTOR  fB8;
    SVECTOR  fC0;
    SVECTOR  fC8;
    SVECTOR  fD0;
    int      fD8;
    int      fDC;
    int      fE0;
    int      fE4;
    int      fE8;
    int      fEC;
    int      fF0;
    int      fF4;
    int      fF8;
    int      fFC;
    int      f100;
    int      f104;
    int      f108;
    int      proc;
    int      f110;
    int      f114;
} IrCensWork;

extern int     GM_CurrentMap;
extern int     GM_AlertMode;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern OBJECT *GM_PlayerBody_800ABA20;

unsigned short s02c_dword_800C3714[] = {HASH_KILL, 0xDCFC, 0xE102};
const SVECTOR  s02c_dword_800E3900 = {0, 512, 1024, 0};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void IrCens_800D97E8(POLY_GT4 *poly, DG_TEX *tex, int arg2)
{
    int i;
    int x, y, w, h;

    for (i = 0; i < 8; i++)
    {
        setPolyGT4(poly);
        setSemiTrans(poly, 1);

        x = tex->off_x;
        w = tex->w + 1;
        poly->u0 = poly->u2 = x + (w * i) / 8;
        poly->u1 = poly->u3 = x + (w * (i + 1)) / 8 - 1;

        y = tex->off_y;
        h = tex->h + 1;
        poly->v0 = poly->v1 = y + (h * arg2) / 64;
        poly->v2 = poly->v3 = y + (h * (arg2 + 1)) / 64 - 1;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;

        poly++;
    }
}

void IrCens_800D98DC(POLY_GT4 *poly, DG_TEX *tex, int x)
{
    int v;
    int i;

    v = tex->off_y + (tex->h * x) / 64;
    for (i = 0; i < 8; i++)
    {
        poly->v0 = poly->v1 = poly->v2 = poly->v3 = v;
        poly++;
    }
}

void IrCens_800D9934(IrCensWork *work, int shade)
{
    int       color;
    POLY_GT4 *poly0;
    POLY_GT4 *poly1;
    int       i;

    poly0 = &work->prim->packs[0]->poly_gt4;
    poly1 = &work->prim->packs[1]->poly_gt4;

    color = (LLOAD(&poly0->r0) & 0xFF000000) | (shade << 16) | (shade << 8) | shade;

    for (i = 8; i > 0; i--)
    {
        LSTORE(color, &poly0->r0);
        LSTORE(color, &poly0->r1);
        LSTORE(color, &poly0->r2);
        LSTORE(color, &poly0->r3);
        poly0++;

        LSTORE(color, &poly1->r0);
        LSTORE(color, &poly1->r1);
        LSTORE(color, &poly1->r2);
        LSTORE(color, &poly1->r3);
        poly1++;
    }
}

void IrCens_800D99A4(IrCensWork *work, SVECTOR *arg1)
{
    SVECTOR  *svec;
    int       x, y, z;
    VECTOR   *vec;
    int       i;
    int       len;
    POLY_GT4 *poly0;
    POLY_GT4 *poly1;
    int       color;

    svec = work->f30;

    x = arg1->vx;
    y = arg1->vy;
    z = arg1->vz;

    vec = (VECTOR *)SCRPAD_ADDR;
    vec->vx = x - svec->vx;
    vec->vy = y - svec->vy;
    vec->vz = z - svec->vz;

    vec++;
    svec++;

    for (i = 8; i > 0; i--)
    {
        vec->vx = x - svec->vx;
        vec->vy = y - svec->vy;
        vec->vz = z - svec->vz;
        vec++;

        svec += 2;
    }

    vec = (VECTOR *)SCRPAD_ADDR;
    for (i = 9; i > 0; i--)
    {
        Square0(vec, vec);
        len = SquareRoot0(vec->vx + vec->vy + vec->vz);
        if (len > 2048)
        {
            len = 2048;
        }

        len = 128 - len / 16;
        vec->pad = len;
        vec++;
    }

    poly0 = &work->prim->packs[0]->poly_gt4;
    poly1 = &work->prim->packs[1]->poly_gt4;

    vec = (VECTOR *)SCRPAD_ADDR;
    for (i = 8; i > 0; i--)
    {
        color = (LLOAD(&poly0->r0) & 0xFF000000) | vec[0].pad;
        LSTORE(color, &poly0->r0);
        LSTORE(color, &poly0->r2);
        LSTORE(color, &poly1->r0);
        LSTORE(color, &poly1->r2);

        color = (LLOAD(&poly0->r0) & 0xFF000000) | vec[1].pad;
        LSTORE(color, &poly0->r1);
        LSTORE(color, &poly0->r3);
        LSTORE(color, &poly1->r1);
        LSTORE(color, &poly1->r3);

        poly0++;
        poly1++;

        vec++;
    }
}

void IrCens_800D9B5C(char *rgb0, char *rgb1, int inc)
{
    unsigned int color;
    int          r, g, b;

    color = LLOAD(rgb0);

    r = color & 0xFF;
    g = ((color >> 8) & 0xFF);
    b = ((color >> 16) & 0xFF);

    r += inc;
    r = MIN(0x80, r);

    g += inc;
    g = MIN(0x80, g);

    b += inc;
    b = MIN(0x80, b);

    color = (color & 0xFF000000) | r | (g << 8) | (b << 16);
    LSTORE(color, rgb1);
    LSTORE(color, rgb0);
}

void IrCens_800D9BE4(IrCensWork *work, int inc)
{
    POLY_GT4 *poly0;
    POLY_GT4 *poly1;
    int       i;

    poly0 = &work->prim->packs[0]->poly_gt4;
    poly1 = &work->prim->packs[1]->poly_gt4;

    for (i = 8; i > 0; i--)
    {
        IrCens_800D9B5C(&poly0->r0, &poly1->r0, inc);
        IrCens_800D9B5C(&poly0->r1, &poly1->r1, inc);
        IrCens_800D9B5C(&poly0->r2, &poly1->r2, inc);
        IrCens_800D9B5C(&poly0->r3, &poly1->r3, inc);
        poly0++;
        poly1++;
    }
}

void IrCens_800D9C7C(IrCensWork *work, SVECTOR *in, int arg2)
{
    SVECTOR *scratch;
    SVECTOR *out;
    int      i;
    int      scale;

    scratch = (SVECTOR *)SCRPAD_ADDR;
    out = work->f30;

    scratch[0] = work->fC8;
    scratch[1] = *in;

    for (i = 8; i > 0; i--)
    {
        *out++ = scratch[1];

        arg2 -= work->fDC;
        if (arg2 > 0)
        {
            scratch[1].vx += scratch[0].vx;
            scratch[1].vy += scratch[0].vy;
            scratch[1].vz += scratch[0].vz;
            *out++ = scratch[1];
        }
        else
        {
            scale = arg2 + work->fDC;
            scratch[1].vx += (scratch[0].vx * scale) / work->fDC;
            scratch[1].vy += (scratch[0].vy * scale) / work->fDC;
            scratch[1].vz += (scratch[0].vz * scale) / work->fDC;
            *out++ = scratch[1];

            while (--i != 0)
            {
                *out++ = scratch[1];
                *out++ = scratch[1];
            }

            break;
        }
    }
}

void IrCensAct_800D9EF8(IrCensWork *work)
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    SVECTOR  sp30;
    SVECTOR  sp38;
    SVECTOR  sp40;
    SVECTOR *vec;
    int      scale;
    int      len;

    GM_CurrentMap = work->map;

    switch (THING_Msg_CheckMessage(work->name, 3, s02c_dword_800C3714))
    {
    case 0:
        GV_DestroyActor(&work->actor);
        return;

    case 1:
        work->f104 = 1;
        break;

    case 2:
        work->f104 = 0;
        break;
    }

    work->fE0++;
    work->fE0 &= 0x7F;

    if (++work->fE8 == work->fE4)
    {
        work->fE8 = 0;
        work->fEC ^= 0x1;
    }

    switch (work->fF4)
    {
    case 0:
        break;

    case 1:
        if (++work->fF8 >= work->fFC)
        {
            work->fF8 = 0;
            work->fF4 = 2;
        }
        else
        {
            work->fF0 = 1;
        }
        break;

    case 2:
        if (++work->fF8 >= work->f100)
        {
            work->fF8 = 0;
            work->fF4 = 1;
        }
        else
        {
            work->fF0 = 0;
        }
        break;
    }

    vec = &work->fD0;

    if (work->fEC == 0)
    {
        scale = work->fE8;
    }
    else
    {
        scale = work->fE4 - work->fE8;
    }

    sp30.vx = (vec->vx * scale) / work->fE4;
    sp30.vy = (vec->vy * scale) / work->fE4;
    sp30.vz = (vec->vz * scale) / work->fE4;

    GV_AddVec3(&work->fB0, &sp30, &sp20);
    GV_AddVec3(&work->fB8, &sp30, &sp28);

    if (work->fF0 != 0 && GM_CurrentItemId != ITEM_STEALTH)
    {
        if (GM_Target_8002E1B8(&sp20, &sp28, work->map, &sp18, ENEMY_SIDE))
        {
            ENE_SetTopCommAL_800CEAE8(0xFF);
            ENE_SetGopointLast_800CEB00();

            if (GM_AlertMode != 3)
            {
                s00a_command_800CEC40(&GM_PlayerPosition_800ABA10, 128);
            }

            GV_SubVec3(&sp18, &sp20, &sp18);
            len = GV_VecLen3(&sp18);

            if (work->f114 > 0)
            {
                if (work->proc != 0)
                {
                    GCL_ExecProc(work->proc, NULL);
                }

                work->f114--;
            }
        }
        else
        {
            len = GV_VecLen3(&sp28);
            work->f114 = work->f110;
        }
    }
    else
    {
        len = GV_VecLen3(&sp28);
        work->f114 = work->f110;
    }

    IrCens_800D9C7C(work, &sp20, len);

    if (GM_CurrentItemId == ITEM_CIGS && work->fF0 != 0)
    {
        sp40 = s02c_dword_800E3900;

        DG_SetPos(&GM_PlayerBody_800ABA20->objs->objs[6].world);
        DG_PutVector(&sp40, &sp38, 1);

        IrCens_800D99A4(work, &sp38);
    }
    else if ((GM_GameStatus & STATE_THERMG) && work->fF0 != 0)
    {
        IrCens_800D9934(work, 128);
    }
    else
    {
        IrCens_800D9934(work, 0);
    }

    if (work->f104 != 0)
    {
        work->f108 += 2;
        if (work->f108 > 128)
        {
            work->f108 = 128;
        }
    }
    else
    {
        work->f108 -= 2;
        if (work->f108 < 0)
        {
            work->f108 = 0;
        }
    }

    if (work->f108 != 0)
    {
        IrCens_800D9BE4(work, work->f108);
    }

    IrCens_800D98DC(&work->prim->packs[0]->poly_gt4, work->tex, work->fE0 / 2);
    IrCens_800D98DC(&work->prim->packs[1]->poly_gt4, work->tex, work->fE0 / 2);
}

void IrCensDie_800DA3DC(IrCensWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int IrCensGetResources_800DA418(IrCensWork *work, int name, int map)
{
    char    *opt;
    SVECTOR *vec;
    int      i;
    DG_PRIM *prim;
    DG_TEX  *tex;

    GM_CurrentMap = map;

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        vec = work->f30;
        for (i = 0; i < 2; i++)
        {
            GCL_StrToSV(opt, vec);
            opt = GCL_GetParamResult();
            vec++;
        }
    }

    work->fB0 = work->f30[0];
    work->fB8 = work->f30[1];

    GV_SubVec3(&work->f30[1], &work->f30[0], &work->fC0);

    work->fC8.vx = work->fC0.vx / 8;
    work->fC8.vy = work->fC0.vy / 8;
    work->fC8.vz = work->fC0.vz / 8;

    work->proc = THING_Gcl_GetInt('e');

    THING_Gcl_GetSVector('m', &work->fD0);

    work->fE4 = THING_Gcl_GetIntDefault('s', 60);
    work->fE8 = 0;

    opt = GCL_GetOption('b');
    if (opt != NULL)
    {
        work->fFC = GCL_StrToInt(GCL_GetParamResult());
        work->f100 = GCL_StrToInt(GCL_GetParamResult());
        work->fF4 = 1;
    }

    prim = DG_GetPrim(DG_PRIM_LINE_GT2, 8, 0, work->f30, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("lsight"));
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    IrCens_800D97E8(&work->prim->packs[0]->poly_gt4, tex, 0);
    IrCens_800D97E8(&work->prim->packs[1]->poly_gt4, tex, 0);

    IrCens_800D9C7C(work, &work->fB0, 8000);

    work->fD8 = GV_VecLen3(&work->fC0);
    work->fDC = GV_VecLen3(&work->fC8);

    work->fF0 = 1;
    work->f114 = 1;
    work->f110 = 1;

    return 0;
}

void *NewIrCens_800DA66C(int name, int where, int argc, char **argv)
{
    IrCensWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(IrCensWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, IrCensAct_800D9EF8, IrCensDie_800DA3DC, "ir_cens.c");

        if (IrCensGetResources_800DA418(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
        work->fE0 = GV_RandU(128);
    }

    return (void *)work;
}
