#include "blood_bl.h"

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
    SVECTOR  pos;
    SVECTOR  verts[4];
    SVECTOR  dir;
    int      scale;
    int      target;
    int      time;
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

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void Act(Work *work)
{
    SVECTOR verts[4];
    int     size;

    if (work->time < work->target)
    {
        work->time++;

        size = (work->scale * work->time) / work->target;

        verts[0].vx = size;
        verts[0].vy = 0;
        verts[0].vz = size;

        verts[1].vx = -size;
        verts[1].vy = 0;
        verts[1].vz = size;

        verts[2].vx = size;
        verts[2].vy = 0;
        verts[2].vz = -size;

        verts[3].vx = -size;
        verts[3].vy = 0;
        verts[3].vz = -size;

        DG_SetPos2(&work->pos, &work->dir);
        DG_PutVector(verts, work->verts, 4);
    }
}

static int GetResources(Work *work, int map)
{
    SVECTOR   color;
    char     *opt;
    int       raise;
    int       abr;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *pack0;
    POLY_FT4 *pack1;

    work->time = 0;

    raise = 0;

    opt = GCL_GetOption('r');
    if (opt != NULL)
    {
        raise = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        GetSvecs(opt, &work->pos);
    }

    opt = GCL_GetOption('d');
    if (opt != NULL)
    {
        GetSvecs(opt, &work->dir);
    }

    opt = GCL_GetOption('s');
    if (opt != NULL)
    {
        work->scale = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('t');
    if (opt != NULL)
    {
        work->target = GCL_StrToInt(opt);
    }
    else
    {
        work->target = 1;
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

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = raise;

    tex = DG_GetTexture(GV_StrCode("ketchap_grey"));
    if (tex == NULL)
    {
        return -1;
    }

    pack0 = prim->packs[0];
    pack1 = prim->packs[1];

    setPolyFT4(pack0);
    setSemiTrans(pack0, 1);

    setPolyFT4(pack1);
    setSemiTrans(pack1, 1);

    DG_SetPacketTexture4(pack0, tex);
    DG_SetPacketTexture4(pack1, tex);

    setRGB0(pack0, color.vx, color.vy, color.vz);
    setRGB0(pack1, color.vx, color.vy, color.vz);

    pack0->tpage |= abr << 5;
    pack1->tpage |= abr << 5;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBloodBl(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blood_bl.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
