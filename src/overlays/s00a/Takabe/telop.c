#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Takabe/thing.h"

typedef struct _TelopPrims
{
    DR_TPAGE tpage1;
    SPRT     sprt1;
    DR_TPAGE tpage2;
    SPRT     sprt2;
} TelopPrims;

typedef struct _TelopSub
{
    TelopPrims prims[2];
    int        state;
    int        timer;
    int        reload;
    int        visible;
    int        shade;
} TelopSub;

typedef struct _TelopWork
{
    GV_ACT    actor;
    TelopSub *sub;
} TelopWork;

typedef struct _TelopWork2
{
    GV_ACT    actor;
    TelopSub *sub;
    int       count;
} TelopWork2;

extern int GV_Clock_800AB920;
extern int GV_PassageTime_800AB924;
extern int GV_PauseLevel_800AB928;

#define EXEC_LEVEL 3

void telop_800DD550(TelopSub *sub, int x, int y, DG_TEX *arg3, DG_TEX *arg4)
{
    SPRT *sprt;
    int   tpage;

    sprt = &sub->prims[0].sprt1;
    SetSprt(sprt);
    SetSemiTrans(sprt, 1);
    setRGB0(sprt, 0, 0, 0);
    sprt->x0 = x;
    sprt->y0 = y;
    sprt->u0 = arg4->off_x;
    sprt->v0 = arg4->off_y;
    sprt->w = arg4->w + 1;
    sprt->h = arg4->h + 1;
    sprt->clut = arg4->clut;

    sub->prims[0].sprt2 = sub->prims[0].sprt1;

    sprt = &sub->prims[0].sprt2;
    sprt->u0 = arg3->off_x;
    sprt->v0 = arg3->off_y;
    sprt->w = arg3->w + 1;
    sprt->h = arg3->h + 1;
    sprt->clut = arg3->clut;

    tpage = arg3->tpage & ~0x60;
    SetDrawTPage(&sub->prims[0].tpage2, 0, 1, tpage | 0x20);

    tpage = arg4->tpage & ~0x60;
    SetDrawTPage(&sub->prims[0].tpage1, 0, 1, tpage | 0x40);

    MargePrim(&sub->prims[0].tpage1, &sub->prims[0].sprt1);
    MargePrim(&sub->prims[0].tpage2, &sub->prims[0].sprt2);
    MargePrim(&sub->prims[0].tpage1, &sub->prims[0].tpage2);

    sub->prims[1] = sub->prims[0];

    sub->state = 0;
    sub->shade = 0;
    sub->visible = 0;
}

void telop_800DD730(char *ot, TelopSub *sub)
{
    int         shade;
    TelopPrims *prims;

    shade = 0;

    if (GV_PauseLevel_800AB928 == 0)
    {
        switch (sub->state)
        {
        case 0:
            sub->timer -= GV_PassageTime_800AB924;
            if (sub->timer <= 0)
            {
                shade = 0;
                sub->timer = 16;
                sub->shade = 0;
                sub->visible = 1;
                sub->state++;
            }
            break;

        case 1:
            sub->timer--;

            shade = sub->shade;
            shade = MIN(shade + 8, 128);
            sub->shade = shade;
            shade = shade | (shade << 8) | (shade << 16);

            if (sub->timer <= 0)
            {
                sub->timer = sub->reload * 2;
                sub->state++;
            }
            break;

        case 2:
            shade = 0x808080;
            sub->timer -= GV_PassageTime_800AB924;

            if (sub->timer <= 0)
            {
                sub->timer = 16;
                sub->shade = 128;
                sub->state++;
            }
            break;

        case 3:
            sub->timer--;

            shade = sub->shade;
            shade = MAX(shade - 8, 0);
            sub->shade = shade;
            shade = shade | (shade << 8) | (shade << 16);

            if (sub->timer <= 0)
            {
                sub->visible = 0;
                sub->state++;
            }
            break;

        case 4:
            break;
        }
    }
    else
    {
        shade = sub->shade;
        shade = shade | (shade << 8) | (shade << 16);
    }

    if (sub->visible != 0)
    {
        prims = &sub->prims[GV_Clock_800AB920];
        shade |= LLOAD(&prims->sprt1.r0) & 0xFF000000;
        LSTORE(shade, &prims->sprt1.r0);
        LSTORE(shade, &prims->sprt2.r0);
        addPrim(ot, &prims->tpage1);
    }
}

void TelopSetAct_800DD92C(TelopWork2 *work)
{
    TelopSub *sub;
    char     *ot;
    int       found;
    int       count;

    sub = work->sub;
    ot = DG_ChanlOTag(1);

    found = 0;
    for (count = work->count; count > 0; count--, sub++)
    {
        telop_800DD730(ot, sub);

        if (sub->state == 4)
        {
            found++;
        }
    }

    if (found == work->count)
    {
        GV_DestroyActor(&work->actor);
    }
}

void TelopSetDie_800DD9E8(TelopWork2 *work)
{
    if (work->sub)
    {
        GV_DelayedFree(work->sub);
    }
}

int TelopGetResources_800DDA18(TelopWork2 *work, int unused, int unused2)
{
    TelopSub *sub;
    int       count;
    int       x, y;
    DG_TEX   *tex;

    work->count = THING_Gcl_GetIntDefault('n', 1);
    sub = GV_Malloc(sizeof(TelopSub) * work->count);
    work->sub = sub;
    if (!sub || !GCL_GetOption('d'))
    {
        return -1;
    }

    for (count = work->count; count > 0; count--, sub++)
    {
        x = GCL_StrToInt(GCL_GetParamResult());
        y = GCL_StrToInt(GCL_GetParamResult());

        sub->timer = GCL_StrToInt(GCL_GetParamResult()) * 2;
        sub->reload = GCL_StrToInt(GCL_GetParamResult()) - 16;

        tex = DG_GetTexture(GCL_StrToInt(GCL_GetParamResult()));
        telop_800DD550(sub, x, y, tex, tex);
    }

    return 0;
}

GV_ACT * NewTelopSet_800DDB34(int name, int where, int argc, char **argv)
{
    TelopWork2 *work;

    work = (TelopWork2 *)GV_NewActor(3, sizeof(TelopWork2));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)TelopSetAct_800DD92C, (TActorFunction)TelopSetDie_800DD9E8, "telop.c");

        if (TelopGetResources_800DDA18(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void Telop2Act_800DDBC8(TelopWork *work)
{
    TelopSub *sub;

    sub = work->sub;
    telop_800DD730(DG_ChanlOTag(1), sub);

    if (sub->state == 4)
    {
        GV_DestroyActor(&work->actor);
    }
}

void telop_800DDC30(TelopWork *work)
{
    if (work->sub)
    {
        GV_DelayedFree(work->sub);
    }
}

GV_ACT * NewTelop2_800DDC60(int x, int y, int timer, int reload, int arg4, int arg5)
{
    TelopWork *work;
    TelopSub  *sub;
    DG_TEX    *tex1;
    DG_TEX    *tex2;

    work = (TelopWork *)GV_NewActor(EXEC_LEVEL, sizeof(TelopWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)Telop2Act_800DDBC8, (TActorFunction)telop_800DDC30, "telop.c");

        work->sub = GV_Malloc(sizeof(TelopSub));
        sub = work->sub;
        if (sub == NULL)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        sub->timer = timer * 2;
        sub->reload = reload - 16;

        if ((arg4 & 0xFFFF0000) == 0)
        {
            tex1 = DG_GetTexture(arg4);
            tex2 = DG_GetTexture(arg5);
        }
        else
        {
            tex1 = (DG_TEX *)arg4;
            tex2 = (DG_TEX *)arg5;
        }

        telop_800DD550(sub, x, y, tex1, tex2);
    }

    return &work->actor;
}

GV_ACT * NewTelop_800DDD7C(int x, int y, int timer, int reload, int tex)
{
    return NewTelop2_800DDC60(x, y, timer, reload, tex, tex);
}
