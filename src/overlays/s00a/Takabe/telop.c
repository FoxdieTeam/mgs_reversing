#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _TelopSub
{
    char pad[0x70];
    int  f70;
    int  f74;
    int  f78;
    char pad2[0x8];
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

extern const char aTelopC[]; // = "telop.c";

#define EXEC_LEVEL 3

#pragma INCLUDE_ASM("asm/overlays/s00a/telop_800DD550.s")
int telop_800DD550(TelopSub *, int, int, DG_TEX *, DG_TEX *);

#pragma INCLUDE_ASM("asm/overlays/s00a/telop_800DD730.s")
void telop_800DD730(char *ot, TelopSub *sub);

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

        if (sub->f70 == 4)
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

int telop_800DDA18(TelopWork2 *work, int unused, int unused2)
{
    TelopSub *sub;
    int       count;
    int       arg1;
    int       arg2;
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
        arg1 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        arg2 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

        sub->f74 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()) * 2;
        sub->f78 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()) - 16;

        tex = DG_GetTexture_8001D830(GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()));
        telop_800DD550(sub, arg1, arg2, tex, tex);
    }

    return 0;
}

GV_ACT * telop_800DDB34(int arg0, int arg1)
{
    TelopWork2 *work;

    work = (TelopWork2 *)GV_NewActor_800150E4(3, 0x28);
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)telop_800DD92C, (TActorFunction)telop_800DD9E8, aTelopC);

        if (telop_800DDA18(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void telop_800DDBC8(TelopWork *work)
{
    TelopSub *sub;

    sub = work->sub;
    telop_800DD730(DG_ChanlOTag(1), sub);

    if (sub->f70 == 4)
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

GV_ACT * telop_800DDC60(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    TelopWork *work;
    TelopSub  *sub;
    DG_TEX    *tex1;
    DG_TEX    *tex2;

    work = (TelopWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(TelopWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)telop_800DDBC8, (TActorFunction)telop_800DDC30, aTelopC);

        work->sub = GV_Malloc_8001620C(sizeof(TelopSub));
        sub = work->sub;
        if (sub == NULL)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        sub->f74 = arg2 * 2;
        sub->f78 = arg3 - 16;

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

        telop_800DD550(sub, arg0, arg1, tex1, tex2);
    }

    return &work->actor;
}

GV_ACT * telop_800DDD7C(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    return telop_800DDC60(arg0, arg1, arg2, arg3, arg4, arg4);
}
