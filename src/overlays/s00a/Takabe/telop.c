#include "common.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

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

int THING_Gcl_GetIntDefault(char param, int def);

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
    sprt->u0 = arg4->field_8_offx;
    sprt->v0 = arg4->field_9_offy;
    sprt->w = arg4->field_A_width + 1;
    sprt->h = arg4->field_B_height + 1;
    sprt->clut = arg4->field_6_clut;

    sub->prims[0].sprt2 = sub->prims[0].sprt1;

    sprt = &sub->prims[0].sprt2;
    sprt->u0 = arg3->field_8_offx;
    sprt->v0 = arg3->field_9_offy;
    sprt->w = arg3->field_A_width + 1;
    sprt->h = arg3->field_B_height + 1;
    sprt->clut = arg3->field_6_clut;

    tpage = arg3->field_4_tPage & ~0x60;
    SetDrawTPage(&sub->prims[0].tpage2, 0, 1, tpage | 0x20);

    tpage = arg4->field_4_tPage & ~0x60;
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
            shade = __min(shade + 8, 128);
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
            shade = __max(shade - 8, 0);
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

void telop_800DD92C(TelopWork2 *work)
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
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void telop_800DD9E8(TelopWork2 *work)
{
    if (work->sub)
    {
        GV_DelayedFree_80016254(work->sub);
    }
}

int TelopGetResources_800DDA18(TelopWork2 *work, int unused, int unused2)
{
    TelopSub *sub;
    int       count;
    int       x, y;
    DG_TEX   *tex;

    work->count = THING_Gcl_GetIntDefault('n', 1);
    sub = GV_Malloc_8001620C(sizeof(TelopSub) * work->count);
    work->sub = sub;
    if (!sub || !GCL_GetOption_80020968('d'))
    {
        return -1;
    }

    for (count = work->count; count > 0; count--, sub++)
    {
        x = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        y = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

        sub->timer = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()) * 2;
        sub->reload = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()) - 16;

        tex = DG_GetTexture_8001D830(GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()));
        telop_800DD550(sub, x, y, tex, tex);
    }

    return 0;
}

GV_ACT * NewTelopSet_800DDB34(int arg0, int arg1)
{
    TelopWork2 *work;

    work = (TelopWork2 *)GV_NewActor_800150E4(3, sizeof(TelopWork2));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)telop_800DD92C, (TActorFunction)telop_800DD9E8, "telop.c");

        if (TelopGetResources_800DDA18(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
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
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void telop_800DDC30(TelopWork *work)
{
    if (work->sub)
    {
        GV_DelayedFree_80016254(work->sub);
    }
}

GV_ACT * NewTelop2_800DDC60(int x, int y, int timer, int reload, int arg4, int arg5)
{
    TelopWork *work;
    TelopSub  *sub;
    DG_TEX    *tex1;
    DG_TEX    *tex2;

    work = (TelopWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(TelopWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Telop2Act_800DDBC8, (TActorFunction)telop_800DDC30, "telop.c");

        work->sub = GV_Malloc_8001620C(sizeof(TelopSub));
        sub = work->sub;
        if (sub == NULL)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        sub->timer = timer * 2;
        sub->reload = reload - 16;

        if ((arg4 & 0xFFFF0000) == 0)
        {
            tex1 = DG_GetTexture_8001D830(arg4);
            tex2 = DG_GetTexture_8001D830(arg5);
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
