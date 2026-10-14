#include <stdlib.h>
#include <memory.h>
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

/* Blood splatters on the walls/floors around a position (demo effect) */

#define N_BLOODS 5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;                   // 0x20
    DG_PRIM *prims[N_BLOODS];       // 0x24
    SVECTOR  verts[N_BLOODS * 4];   // 0x38
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

void BloodHazard_Act(Work *work);
void BloodHazard_Die(Work *work);

/* NON_MATCHING: the code of this draft is identical to the original, only the
 * stack frame differs: the original frame is 8 bytes bigger (0x44..0x4f unused,
 * after the three spill slots at 0x38..0x40). Verified with the native cc1 in
 * gdb: if the pseudo holding the high part of width * 0x55555556 (width / 3 in
 * the loop) goes "on stack" when reload spills $hi, the output is exactly the
 * original (reload redirects the mult output into its reload register, so the
 * 8-aligned spill slot stays unreferenced). That happens if regclass gives the
 * pseudo alternate class NO_REGS (it then is local-allocated to $hi and not
 * retried), or if retry_global_alloc fails for it or for one of the floor
 * normal / sqrt mult results. With this source the pseudo's GR cost (48) is
 * below its memory cost (56), so it gets GR as alternate class; a C construct
 * that changes this without changing the code has not been found.
 * (Act/Die are not static: a static function following an INCLUDE_ASM
 * function would be merged into it by include_asm_fixup.py) */
#if 0
void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx);

void *NewBloodHazard(MATRIX *world, int width, int height, int size, int dist)
{
    Work    *work;
    DG_TEX  *tex;
    HZD_SEG *seg;
    HZD_FLR *flr;
    SVECTOR  eye;
    SVECTOR  dir;
    SVECTOR  ang;
    SVECTOR  pos;
    int      half_w, half_h;
    int      s;
    int      i;

    tex = NULL;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, BloodHazard_Act, BloodHazard_Die, "bloodhzd.c");

    work->map = GM_CurrentMap;
    sub_8007EF34(&eye, &dir, world);

    half_w = width >> 1;
    half_h = height >> 1;

    for (i = 0; i < N_BLOODS; i++)
    {
        ang.vx = rand() % width;
        ang.vy = rand() % height;

        work->prims[i] = GM_MakePrim(DG_PRIM_POLY_FT4, 1, &work->verts[i * 4], NULL);

        if (ang.vx / (width / 3) == 1 && ang.vy / (height / 3) == 1)
        {
            tex = DG_GetTexture(GV_StrCode("chi_01"));
        }
        else if (ang.vx / half_w == 0 && ang.vy / half_h == 0)
        {
            tex = DG_GetTexture(GV_StrCode("chi_02"));
        }
        else if (ang.vx / half_w == 1 && ang.vy / half_h == 0)
        {
            tex = DG_GetTexture(GV_StrCode("chi_03"));
        }
        else if (ang.vx / half_w == 0 && ang.vy / half_h == 1)
        {
            tex = DG_GetTexture(GV_StrCode("chi_04"));
        }
        else if (ang.vx / half_w == 1 && ang.vy / half_h == 1)
        {
            tex = DG_GetTexture(GV_StrCode("chi_05"));
        }

#define PACK0   (((POLY_FT4 *)work->prims[i]->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)work->prims[i]->packs[0]) + 1)

        {
            int x, y, w, h;
            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(PACK0, x, y, w, h);
            PACK0->tpage = tex->tpage;
            PACK0->clut = tex->clut;
        }
        {
            int x, y, w, h;
            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(PACK1, x, y, w, h);
            PACK1->tpage = tex->tpage;
            PACK1->clut = tex->clut;
        }

        PACK0->tpage |= 0x40;
        PACK1->tpage |= 0x40;

        setPolyFT4(PACK0);
        setPolyFT4(PACK1);
        setRGB0(PACK0, 0, 255, 255);
        setRGB0(PACK1, 0, 255, 255);
        setSemiTrans(PACK0, 1);
        setSemiTrans(PACK1, 1);

#undef PACK0
#undef PACK1

        ang.vx = dir.vx + (ang.vx - half_w);
        ang.vy = dir.vy + (ang.vy - half_h);
        ang.vz = dir.vz;

        memset(&pos, 0, sizeof(SVECTOR));
        pos.vz = dist;
        DG_SetPos2(&DG_ZeroVector, &ang);
        DG_PutVector(&pos, &pos, 1);

        pos.vx += eye.vx;
        pos.vy += eye.vy;
        pos.vz += eye.vz;

        if (HZD_OnlineHazardCheck(GM_GetMap(work->map)->hzd, &eye, &pos, 15, 0))
        {
            if ((int)HZD_GetOnlineHazard() < 0)
            {
                seg = HZD_GetOnlineHazard();
                pos.vx = -((seg->p1.z - seg->p2.z) * -seg->p1.h);
                pos.vy = 0;
                pos.vz = (seg->p1.x - seg->p2.x) * -seg->p1.h;
            }
            else
            {
                flr = HZD_GetOnlineHazard();
                pos.vx = (flr->p2.y - flr->p3.y) * (flr->p1.z - flr->p2.z) - (flr->p2.z - flr->p3.z) * (flr->p1.y - flr->p2.y);
                pos.vy = (flr->p2.z - flr->p3.z) * (flr->p1.x - flr->p2.x) - (flr->p2.x - flr->p3.x) * (flr->p1.z - flr->p2.z);
                pos.vz = (flr->p2.x - flr->p3.x) * (flr->p1.y - flr->p2.y) - (flr->p2.y - flr->p3.y) * (flr->p1.x - flr->p2.x);
            }

            ang.vx = -ratan2(pos.vy, SquareRoot0(pos.vx * pos.vx + pos.vz * pos.vz));
            ang.vy = ratan2(pos.vx, pos.vz);
            ang.vz = 0;

            s = size >> 1;
            work->verts[i * 4 + 0].vx = -s;
            work->verts[i * 4 + 0].vy = -s;
            work->verts[i * 4 + 1].vx = -s;
            work->verts[i * 4 + 1].vy = s;
            work->verts[i * 4 + 2].vx = s;
            work->verts[i * 4 + 2].vy = -s;
            work->verts[i * 4 + 3].vx = s;
            work->verts[i * 4 + 3].vy = s;

            HZD_GetOnlinePoint(&pos);
            DG_SetPos2(&pos, &ang);
            DG_PutVector(&work->verts[i * 4], &work->verts[i * 4], 4);
        }
    }

    return (void *)work;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800D6A4C.s")

void BloodHazard_Act(Work *work)
{
    GM_CurrentMap = work->map;
}

void BloodHazard_Die(Work *work)
{
    int i;

    for (i = 0; i < N_BLOODS; i++)
    {
        GM_FreePrim(work->prims[i]);
    }
}
