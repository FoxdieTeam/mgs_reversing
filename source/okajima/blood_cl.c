#include "blood_cl.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[64];
    int      map;
} Work;

/*---------------------------------------------------------------------------*/

static int GetSvecs(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

static void GetInts(char *opt, int *out)
{
    char *res;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        *out = GCL_StrToInt(res);
        out++;
    }
}

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void Act(Work *work)
{
    /* do nothing */
}

static int GetResources(Work *work, int map)
{
    SVECTOR   pos[16];
    SVECTOR   dir[16];
    int       size[16];
    SVECTOR   local[4];
    SVECTOR   color;
    int       raise;
    int       n_prims;
    char     *opt;
    int       abr;
    int       i;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *packs0;
    POLY_FT4 *packs1;

    raise = 0;

    n_prims = 0;
    opt = GCL_GetOption('r');
    if (opt != NULL)
    {
        raise = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        n_prims = GetSvecs(opt, pos);

        opt = GCL_GetOption('d');
        if (opt != NULL)
        {
            GetSvecs(opt, dir);
        }

        opt = GCL_GetOption('s');
        if (opt != NULL)
        {
            GetInts(opt, size);
        }
    }

    opt = GCL_GetOption('u');
    if (opt != NULL)
    {
        abr = GCL_StrToInt(opt);
        abr &= 0x3;
    }
    else
    {
        abr = 0;
    }

    opt = GCL_GetOption('c');
    if (opt != NULL)
    {
        GetSvecs(opt, &color);
    }

    work->map = map;
    GM_SetCurrentMap(map);

    for (i = 0; i < n_prims; i++)
    {
        local[0].vx = size[i];
        local[0].vy = 0;
        local[0].vz = size[i];

        local[1].vx = -size[i];
        local[1].vy = 0;
        local[1].vz = size[i];

        local[2].vx = size[i];
        local[2].vy = 0;
        local[2].vz = -size[i];

        local[3].vx = -size[i];
        local[3].vy = 0;
        local[3].vz = -size[i];

        DG_SetPos2(&pos[i], &dir[i]);
        DG_PutVector(local, &work->vecs[i * 4], 4);
    }

    prim = GM_MakePrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, n_prims, work->vecs, NULL);
    work->prim = prim;
    if (work->prim == NULL)
    {
        return -1;
    }

    prim->raise = raise;

    tex = DG_GetTexture(GV_StrCode("ketchap_grey"));
    if (tex == NULL)
    {
        return -1;
    }

    packs0 = (POLY_FT4 *)prim->packs[0];
    packs1 = (POLY_FT4 *)prim->packs[1];

    while (--n_prims >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        DG_SetPacketTexture4(packs0, tex);
        DG_SetPacketTexture4(packs1, tex);

        setRGB0(packs0, color.vx, color.vy, color.vz);
        setRGB0(packs1, color.vx, color.vy, color.vz);

        packs0->tpage |= abr << 5;
        packs1->tpage |= abr << 5;

        packs0++;
        packs1++;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBloodCl(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blood_cl.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
