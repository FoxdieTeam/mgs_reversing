#include "blink_tx.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _BlinkTxWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  pos[8];
    char     pad[0x4];
} BlinkTxWork;

extern int GM_CurrentMap;

RECT blink_tx_rect = {1000, 1000, 2000, 2000};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void BlinkTxShadePacks_800DEA9C(POLY_FT4 *packs, int n_packs, DG_TEX *tex, int shade)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, shade, shade, shade);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs++;
    }
}

void BlinkTxDie_800DEB24(BlinkTxWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int BlinkTxGetSvecs_800DEB60(char *opt, SVECTOR *out)
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

int BlinkTxGetResources_800DEBB4(BlinkTxWork *work, int map, int n_prims)
{
    DG_PRIM *prim;
    char    *opt;
    int      texid;
    DG_TEX  *tex;

    GM_CurrentMap = map;

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, n_prims, 0, work->pos, &blink_tx_rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 500;
    prim->field_2E_k500 *= 2;

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
        BlinkTxShadePacks_800DEA9C(&prim->packs[0]->poly_ft4, n_prims, tex, 36);
        BlinkTxShadePacks_800DEA9C(&prim->packs[1]->poly_ft4, n_prims, tex, 36);
    }
    else
    {
        BlinkTxShadePacks_800DEA9C(&prim->packs[0]->poly_ft4, n_prims, tex, 30);
        BlinkTxShadePacks_800DEA9C(&prim->packs[1]->poly_ft4, n_prims, tex, 36);
    }

    return 0;
}

GV_ACT *NewBlinkTx_800DECD8(int name, int where, int argc, char **argv)
{
    BlinkTxWork *work;
    char        *opt;
    int          n_prims;

    work = (BlinkTxWork *)GV_NewActor(EXEC_LEVEL, sizeof(BlinkTxWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, NULL, (GV_ACTFUNC)BlinkTxDie_800DEB24, "blink_tx.c");

        opt = GCL_GetOption('p');
        n_prims = BlinkTxGetSvecs_800DEB60(opt, work->pos);

        if (BlinkTxGetResources_800DEBB4(work, where, n_prims) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
