#include "blink_tx.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  pos[8];
    char     pad[0x4];
} Work;

/*---------------------------------------------------------------------------*/

static RECT blink_tx_rect = {1000, 1000, 2000, 2000};

static void InitPacks(POLY_FT4 *packs, int n_packs, DG_TEX *tex, int shade)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, shade, shade, shade);
        DG_SetPacketTexture4(packs, tex);
        packs++;
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetSvecs(char *opt, SVECTOR *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(param, out);

        out++;
        count++;
    }

    return count;
}

static int GetResources(Work *work, int map, int n_prims)
{
    DG_PRIM *prim;
    char    *opt;
    int      texid;
    DG_TEX  *tex;

    GM_CurrentMap = map;

    prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, n_prims, work->pos, &blink_tx_rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = 500;
    prim->raise *= 2;

    opt = GCL_GetOption('t');
    if (opt != NULL)
    {
        texid = GCL_StrToInt(opt);
    }
    else
    {
        texid = GV_StrCode("sfex0236");
    }

    tex = DG_GetTexture(texid);
    if (tex == NULL)
    {
        return -1;
    }

    if (GCL_GetOption('n'))
    {
        InitPacks(prim->packs[0], n_prims, tex, 36);
        InitPacks(prim->packs[1], n_prims, tex, 36);
    }
    else
    {
        InitPacks(prim->packs[0], n_prims, tex, 30);
        InitPacks(prim->packs[1], n_prims, tex, 36);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBlinkTexture(int name, int where, int argc, char **argv)
{
    Work    *work;
    char    *opt;
    int     n_prims;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, NULL, Die, "blink_tx.c");

        opt = GCL_GetOption('p');
        n_prims = GetSvecs(opt, work->pos);

        if (GetResources(work, where, n_prims) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
