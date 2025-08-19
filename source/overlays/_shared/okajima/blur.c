#include "blur.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

typedef struct _BlurSub
{
    POLY_FT4 *poly;
    char      pad[0xC];
} BlurSub;

typedef struct _BlurWork
{
    GV_ACT  actor;
    int     f20;
    BlurSub f24[2];
    char    pad2[0x10];
    int     f54;
    int     f58;
    int     f5C;
    int     f60;
    int     f64;
    int     f68;
    int     f6C;
    int     f70;
    int     f74;
    char    pad3[0x8];
} BlurWork;

TILE   SECTION("overlay.bss") d01a_dword_800D1428[2];
DR_STP SECTION("overlay.bss") d01a_dword_800D1448[2];
int    SECTION("overlay.bss") d01a_dword_800D1460;
int    SECTION("overlay.bss") d01a_dword_800D1464;
DR_STP SECTION("overlay.bss") d01a_dword_800D1468[2];

void d01a_blur_800CCB28(void)
{
    unsigned int *ot;
    TILE         *tile;
    DR_STP       *stp;
    DR_STP       *stp2;

    ot = (unsigned int *)DG_Chanl(0)->ot[GV_Clock];

    tile = &d01a_dword_800D1428[GV_Clock];
    SetTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, -160, -112);
    setWH(tile, 320, 224);
    DG_SetBackGroundTile(tile);
    addPrim(&ot[0xFF], tile);

    stp = &d01a_dword_800D1448[GV_Clock];
    SetDrawStp(stp, 1);
    addPrim(&ot[0xFF], stp);

    ot = (unsigned int *)DG_Chanl(1)->ot[GV_Clock];

    stp2 = &d01a_dword_800D1468[GV_Clock];
    SetDrawStp(stp2, 1);
    addPrim(ot, stp2);
}

void d01a_blur_800CCCC8(POLY_FT4 *packs, BlurWork *work, int arg3, int abr, int arg5, int arg6)
{
    int var_s2;
    int xoff, yoff;
    int i, j, k;
    int c111, c189, c221;
    int f64, f6C, f70, f74;
    int c159_2, c111_2;

    char pad1[24];
    int  rnd1[3];
    char pad2[24];
    int  rnd2[3];
    char pad3[16];

    POLY_FT4 *packs_copy;
    POLY_FT4 *packs1;
    POLY_FT4 *packs2;
    POLY_FT4 *packs3;
    POLY_FT4 *packs4;

    packs_copy = packs;
    packs1 = packs++;
    packs2 = packs++;
    packs3 = packs++;
    packs4 = packs++;

    xoff = 0;
    yoff = 0;

    rnd1[0] = GV_RandS(2);
    rnd1[1] = GV_RandS(2);
    rnd1[2] = GV_RandS(2);
    rnd2[0] = GV_RandS(2);
    rnd2[1] = GV_RandS(2);
    rnd2[2] = c189 = GV_RandS(2);

    switch (arg6)
    {
    case 1:
        if (work->f58 != 0)
        {
            work->f70 = (rsin(work->f5C * 41) + rsin(work->f5C * 30)) / 2048;
            work->f74 = (rsin(work->f5C * 53) + rsin(work->f5C * 81)) / 2048;
        }
        else
        {
            work->f70 = 0;
            work->f74 = 0;
        }
        xoff = 0;
        yoff = 0;
        break;

    case 2:
        xoff = 8;
        yoff = 8;
        work->f70 = 0;
        work->f74 = 0;
        break;

    case 3:
        xoff = -8;
        yoff = -8;
        work->f70 = 0;
        work->f74 = 0;
        break;
    }

    packs1->x0 = work->f64 + xoff;
    packs1->y0 = work->f68 + yoff;
    packs1->x1 = work->f70 + (rnd1[0] + 160);
    packs1->y1 = work->f68 + yoff;
    packs1->x2 = work->f64 + xoff;
    packs1->y2 = work->f74 + (rnd2[0] + 112);
    packs1->x3 = work->f70 + (rnd1[1] + 160);
    packs1->y3 = work->f74 + (rnd2[1] + 112);

    packs2->x0 = packs1->x1;
    packs2->y0 = packs1->y1;
    packs2->x1 = -xoff + 320 - work->f64;
    packs2->y1 = (work->f68 + yoff);
    packs2->x2 = packs1->x3;
    packs2->y2 = packs1->y3;
    packs2->x3 = -xoff + 320 - work->f64;
    packs2->y3 = work->f74 + (rnd2[2] + 112);

    packs3->x0 = packs1->x2;
    packs3->y0 = packs1->y2;
    packs3->x1 = packs1->x3;
    packs3->y1 = packs1->y3;
    packs3->x2 = work->f64 + xoff;
    packs3->y2 = -yoff + 224 - work->f6C;
    packs3->x3 = work->f70 + (rnd1[2] + 160);
    packs3->y3 = -yoff + 224 - work->f6C;

    packs4->x0 = packs1->x3;
    packs4->y0 = packs1->y3;
    packs4->x1 = packs2->x3;
    packs4->y1 = packs2->y3;
    packs4->x2 = packs3->x3;
    packs4->y2 = packs3->y3;
    c159_2 = 159;
    asm(""); // FIXME
    packs4->x3 = -xoff + 320 - work->f64;
    packs4->y3 = -yoff + 224 - work->f6C;

    packs1->u0 = packs1->u2 = work->f64 + 2;
    c111_2 = 111;
    asm(""); // FIXME
    packs1->v0 = packs1->v1 = work->f68 + 2;

    f70 = c159_2 - work->f70;
    f74 = c111_2 - work->f74;
    packs1->u1 = packs1->u3 = f70;
    packs1->v2 = packs1->v3 = f74;

    packs2->u0 = packs2->u2 = 32 - work->f70;
    packs2->v0 = packs2->v1 = work->f68 + 2;

    f64 = 189 - work->f64;
    c111 = c111_2 - work->f74;
    packs2->u1 = packs2->u3 = f64;
    packs2->v2 = packs2->v3 = c111;

    packs3->u0 = packs3->u2 = work->f64 + 2;
    packs3->v0 = packs3->v1 = 112 - work->f74;

    c159_2 = c159_2 - work->f70;
    f6C = 221 - work->f6C;
    packs3->u1 = packs3->u3 = c159_2;
    packs3->v2 = packs3->v3 = f6C;

    packs4->u0 = packs4->u2 = 32 - work->f70;
    packs4->v0 = packs4->v1 = 112 - work->f74;

    c189 = 189 - work->f64;
    c221 = 221 - work->f6C;
    packs4->u1 = packs4->u3 = c189;
    packs4->v2 = packs4->v3 = c221;

    packs = packs_copy;
    for (i = 0; i < 2; i++)
    {
        for (j = 0, var_s2 = 0; j < 2; j++)
        {
            for (k = 0; k < 1; k++)
            {
                int new_var = var_s2 & (~0x3F);
                setPolyFT4(packs);
                packs->tpage = GetTPage(2, arg5, (((1 - abr) * 5) << 6) + new_var, 0);
                setSemiTrans(packs, 1);
                setRGB0(packs, 128, 128, 128);

                packs++;
            }

            var_s2 += 0xA0;
        }
    }
}

void BlurAct_800CD274(BlurWork *work)
{
    char     *ot;
    POLY_FT4 *prim;
    int       var_t0;
    int       var_t1;
    int       i;

    if (work->f20 != -1 && GM_CheckMessage(&work->actor, work->f20, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    work->f5C++;

    d01a_blur_800CCB28();

    if (work->f60 > 0)
    {
        work->f60--;
        return;
    }

    ot = DG_ChanlOTag(1);
    prim = work->f24[GV_Clock].poly;

    var_t0 = 1;
    var_t1 = 0;

    switch (work->f54)
    {
    case 0:
        break;

    case 1:
        var_t0 = 2;
        break;

    case 2:
        var_t0 = 3;
        break;

    case 3:
        var_t1 = 3;
        break;
    }

    d01a_blur_800CCCC8(prim, work, 0, GV_Clock, var_t1, var_t0);

    for (i = 0; i < 4; i++)
    {
        addPrim(ot, prim);
        prim++;
    }
}

void BlurDie_800CD3E8(BlurWork *work)
{
    if (work->f24[0].poly != NULL)
    {
        GV_DelayedFree(work->f24[0].poly);
    }
}

int BlurGetResources_800CD418(BlurWork *work, int arg1, int arg2, int arg3)
{
    POLY_FT4 *polys;
    polys = GV_Malloc(sizeof(POLY_FT4) * 8);
    if (polys == NULL)
    {
        return -1;
    }

    work->f24[0].poly = &polys[0];
    work->f24[1].poly = &polys[4];
    work->f54 = arg3;

    switch (arg3)
    {
    case 0:
        break;

    case 1:
        arg3 = 0;
        break;

    case 2:
        arg3 = 0;
        break;
    }

    d01a_blur_800CCCC8(work->f24[0].poly, work, 1, 0, arg3, 1);
    d01a_blur_800CCCC8(work->f24[1].poly, work, 1, 1, arg3, 1);

    work->f5C = GV_RandU(4096);
    work->f60 = 4;
    work->f58 = arg1;

    if (arg2 != 0)
    {
        work->f64 = 0;
        work->f68 = 0;
        work->f6C = 0;
    }
    else
    {
        work->f68 = 24;
        work->f64 = 0;
        work->f6C = 40;
    }

    return 0;
}

#define EXEC_LEVEL GV_ACTOR_AFTER2

void *NewBlur_800CD530(int name, int where, int argc, char **argv)
{
    BlurWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(BlurWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BlurAct_800CD274, BlurDie_800CD3E8, "blur.c");

        if (BlurGetResources_800CD418(work, name, where, argc) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f20 = -1;
    }

    return (void *)work;
}

void *NewBlur_800CD5D8(int arg0)
{
    BlurWork *work;
    char     *opt;
    int       var_s2;
    int       var_s3;
    int       var_s4;

    var_s4 = 0;
    var_s3 = 0;
    var_s2 = 0;

    work = GV_NewActor(EXEC_LEVEL, sizeof(BlurWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BlurAct_800CD274, BlurDie_800CD3E8, "blur.c");

        opt = GCL_GetOption('d');
        if (opt != NULL)
        {
            var_s4 = GCL_StrToInt(opt);
            var_s3 = GCL_StrToInt(opt);
            var_s2 = GCL_StrToInt(opt);
        }

        if (BlurGetResources_800CD418(work, var_s4, var_s3, var_s2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->f20 = arg0;
    }

    return (void *)work;
}
