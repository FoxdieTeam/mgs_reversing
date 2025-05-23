#include "uji.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

typedef struct _UjiWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  f24[256];
    SVECTOR  f824[64];
    SVECTOR  fA24[64];
    char     pad[0x100];
    int      fD24;
    SVECTOR  fD28[4];
    SVECTOR  fD48[4];
    int      fD68[4];
    int      fD78;
    int      fD7C;
    char     pad2[0x8];
    int      fD88;
    int      fD8C;
    int      map;
    char     pad3[0x8];
} UjiWork;

RECT uji_rect = {100, 100, 200, 200};

const char aUji[] = "uji";
const char aUjiC[] = "uji.c";

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int UjiGetSvecs_800C39E8(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, svec);

        svec++;
        count++;
    }

    return count;
}

int UjiGetInts_800C3A3C(char *opt, int *out)
{
    int   count;
    int  *out2;
    char *result;

    count = 0;
    out2 = out;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        *out2++ = GCL_StrToInt(result);
        count++;
    }

    return count;
}

void UjiShadePacks_800C3A94(POLY_FT4 *packs, int n_packs, DG_TEX *tex, SVECTOR *color)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, color->vx, color->vy, color->vz);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;

        packs->clut = tex->clut;
        packs->tpage |= 0x60;

        packs++;
    }
}

void UjiDie_800C3B38(UjiWork *work)
{
    GM_FreePrim(work->prim);
}

void UjiAct_800C3B74(UjiWork *work)
{
    SVECTOR  sp10[4];
    SVECTOR  sp30[4];
    SVECTOR  sp50;
    SVECTOR  sp58;
    SVECTOR  sp60;
    int      modulo;
    int      x, y, z;
    SVECTOR *vec1;
    SVECTOR *vec2;
    SVECTOR *vec3;
    SVECTOR *vec4;
    SVECTOR *vec5;
    int     *vec6;

    GM_CurrentMap = work->map;

    work->fD88++;

    if (work->fD24 == 0)
    {
        modulo = 4;
    }
    else
    {
        modulo = 2;
    }

    sp58.vx = 0;
    sp58.vy = 0;

    vec1 = work->f24;
    vec2 = work->f824;
    vec3 = work->fA24;
    vec4 = work->fD28;
    vec5 = work->fD48;
    vec6 = work->fD68;

    for (y = 0; y < work->fD78; y++, vec4++, vec5++, vec6++)
    {
        for (x = 0; x < work->fD7C; x++, vec1 += 4, vec2++, vec3++)
        {
            z = (rsin((work->fD88 + vec2->vx) * 64) >> 10) + 14;

            sp10[0].vx = -5;
            sp10[0].vy = 0;
            sp10[0].vz = z;

            sp10[1].vx = 5;
            sp10[1].vy = 0;
            sp10[1].vz = z;

            sp10[2].vx = -5;
            sp10[2].vy = 0;
            sp10[2].vz = -z;

            sp10[3].vx = 5;
            sp10[3].vy = 0;
            sp10[3].vz = -z;

            switch (GV_RandU(4))
            {
            case 0:
                vec3->vy += GV_RandU(4096) % (modulo * 8);
                break;

            case 1:
                vec3->vy -= GV_RandU(4096) % (modulo * 8);
                break;

            case 2:
            case 3:
                break;
            }

            if (GV_RandU(16) == 0)
            {
                sp50.vx = 0;
                sp50.vy = 0;
                sp50.vz = modulo;

                DG_SetPos2(&DG_ZeroVector, vec3);
                DG_PutVector(&sp50, &sp60, 1);

                DG_SetPos2(vec2, vec5);
                DG_PutVector(&sp60, &sp60, 1);

                if (*vec6 < GV_DiffVec3(&sp60, vec4))
                {
                    vec3->vy += 2048;
                }
                else
                {
                    DG_SetPos2(&DG_ZeroVector, vec3);
                    DG_PutVector(&sp50, &sp60, 1);

                    DG_SetPos2(vec2, vec5);
                    DG_PutVector(&sp60, vec2, 1);
                }
            }

            DG_SetPos2(&DG_ZeroVector, vec3);
            DG_PutVector(sp10, sp30, 4);

            DG_SetPos2(vec2, vec5);
            DG_PutVector(sp30, vec1, 4);
        }
    }
}

int UjiCheckMessages_800C3EEC(UjiWork *work)
{
    char *opt;

    opt = GCL_GetOption('m');
    if (opt != 0)
    {
        work->fD24 = GCL_StrToInt(opt);

        if (work->fD24 >= 2)
        {
            work->fD24 = 0;
        }
    }
    else
    {
        work->fD24 = 0;
    }

    opt = GCL_GetOption('c');
    if (opt != 0)
    {
        work->fD78 = UjiGetSvecs_800C39E8(opt, work->fD28);
    }
    else
    {
        work->fD78 = 1;
    }

    opt = GCL_GetOption('r');
    if (opt != 0)
    {
        UjiGetInts_800C3A3C(opt, work->fD68);
    }

    opt = GCL_GetOption('v');
    if (opt != 0)
    {
        UjiGetSvecs_800C39E8(opt, work->fD48);
    }

    opt = GCL_GetOption('n');
    if (opt != 0)
    {
        work->fD7C = GCL_StrToInt(opt);

        if (work->fD7C <= 0)
        {
            work->fD7C = 1;
        }
    }
    else
    {
        work->fD7C = 1;
    }

    GM_GetMap(work->map);

    return 0;
}

int UjiGetResources_800C3FC8(UjiWork *work, int map)
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    SVECTOR  sp30[4];
    SVECTOR  sp50[4];
    SVECTOR  color;
    int      count;
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      x, y;
    int      index;

    work->map = map;
    GM_CurrentMap = map;

    UjiCheckMessages_800C3EEC(work);

    sp30[0].vx = -5;
    sp30[0].vy = 0;
    sp30[0].vz = 10;

    sp30[1].vx = 5;
    sp30[1].vy = 0;
    sp30[1].vz = 10;

    sp30[2].vx = -5;
    sp30[2].vy = 0;
    sp30[2].vz = -10;

    sp30[3].vx = 5;
    sp30[3].vy = 0;
    sp30[3].vz = -10;

    sp28.vx = 0;
    sp28.vz = 0;

    count = work->fD78 * work->fD7C;

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, count, 0, work->f24, &uji_rect);
    work->prim = prim;
    if (!prim)
    {
        return -1;
    }

    prim->field_2E_k500 = 500;
    prim->field_2E_k500 /= 5;

    tex = DG_GetTexture(GV_StrCode(aUji));
    if (!tex)
    {
        return -1;
    }

    color.vx = 64;
    color.vy = 64;
    color.vz = 50;

    UjiShadePacks_800C3A94(&prim->packs[0]->poly_ft4, count, tex, &color);
    UjiShadePacks_800C3A94(&prim->packs[1]->poly_ft4, count, tex, &color);

    for (y = 0; y < work->fD78; y++)
    {
        index = y * work->fD7C;

        for (x = 0; x < work->fD7C; x++, index++)
        {
            sp18.vx = 0;
            sp18.vy = 0;
            sp18.vz = GV_RandS(4096) % work->fD68[y];

            sp28.vy = GV_RandS(4096);

            DG_SetPos2(&DG_ZeroVector, &sp28);
            DG_PutVector(&sp18, &sp20, 1);

            DG_SetPos2(&work->fD28[y], &work->fD48[y]);
            DG_PutVector(&sp20, &work->f824[index], 1);

            work->fA24[index].vx = 0;
            work->fA24[index].vy = GV_RandS(4096);
            work->fA24[index].vz = 0;

            DG_SetPos2(&DG_ZeroVector, &work->fA24[index]);
            DG_PutVector(sp30, sp50, 4);

            DG_SetPos2(&work->f824[index], &work->fD48[y]);
            DG_PutVector(sp50, &work->f24[index * 4], 4);
        }
    }

    work->fD88 = 0;
    return 0;
}

void *NewUji_800C42F8(int name, int where, int argc, char **argv)
{
    UjiWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(UjiWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, UjiAct_800C3B74, UjiDie_800C3B38, aUjiC);

        if (UjiGetResources_800C3FC8(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
