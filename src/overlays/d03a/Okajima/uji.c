#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _UjiWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    char     pad[0xD00];
    int      fD24;
    SVECTOR  fD28[4];
    SVECTOR  fD48[4];
    int      fD68[4];
    int      fD78;
    int      fD7C;
    char     pad3[0x10];
    int      fD90;
    char     pad4[0x8];
} UjiWork;

extern const char aUjiC[]; // = "uji.c"

#define EXEC_LEVEL 4

int d03a_uji_800C39E8(int opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(result, svec);

        svec++;
        count++;
    }

    return count;
}

int d03a_uji_800C3A3C(int opt, int *out)
{
    int   count;
    int  *out2;
    char *result;

    count = 0;
    out2 = out;

    while ((result = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *out2++ = GCL_StrToInt_800209E8(result);
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

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;

        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->field_4_tPage;

        packs->clut = tex->field_6_clut;
        packs->tpage |= 0x60;

        packs++;
    }
}

void UjiDie_800C3B38(UjiWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

#pragma INCLUDE_ASM("asm/overlays/d03a/UjiAct_800C3B74.s")
void UjiAct_800C3B74(UjiWork *work);

int Uji_800C3EEC(UjiWork *work)
{
    int opt;

    opt = GCL_GetOption_80020968('m');
    if (opt != 0)
    {
        work->fD24 = GCL_StrToInt_800209E8((char *)opt);

        if (work->fD24 >= 2)
        {
            work->fD24 = 0;
        }
    }
    else
    {
        work->fD24 = 0;
    }

    opt = GCL_GetOption_80020968('c');
    if (opt != 0)
    {
        work->fD78 = d03a_uji_800C39E8(opt, work->fD28);
    }
    else
    {
        work->fD78 = 1;
    }

    opt = GCL_GetOption_80020968('r');
    if (opt != 0)
    {
        d03a_uji_800C3A3C(opt, work->fD68);
    }

    opt = GCL_GetOption_80020968('v');
    if (opt != 0)
    {
        d03a_uji_800C39E8(opt, work->fD48);
    }

    opt = GCL_GetOption_80020968('n');
    if (opt != 0)
    {
        work->fD7C = GCL_StrToInt_800209E8((char *)opt);

        if (work->fD7C <= 0)
        {
            work->fD7C = 1;
        }
    }
    else
    {
        work->fD7C = 1;
    }

    Map_FromId_800314C0(work->fD90);

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/d03a/UjiGetResources_800C3FC8.s")
int UjiGetResources_800C3FC8(UjiWork *work, int);

GV_ACT * NewUji_800C42F8(int arg0, int arg1)
{
    UjiWork *work;

    work = (UjiWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(UjiWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)UjiAct_800C3B74, (TActorFunction)UjiDie_800C3B38, aUjiC);

        if (UjiGetResources_800C3FC8(work, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
