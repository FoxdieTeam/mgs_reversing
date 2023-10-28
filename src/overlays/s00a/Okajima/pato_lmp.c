#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/object.h"

typedef struct _PatoLmpSub
{
    OBJECT field_0;
    char   field_24[0xC0];
} PatoLmpSub;

typedef struct _PatoLmpWork
{
    GV_ACT     actor;
    void      *field_20;
    PatoLmpSub field_24[4];
    PatoLmpSub field_3B4[4];
    PatoLmpSub field_744[4];
    PatoLmpSub field_AD4[4];
    char       field_E64[0x1A0];
    int        field_1004;
    DG_PRIM   *field_1008;
    char       field_100C[0x95C];
} PatoLmpWork;

extern const char aPatoLmpC[]; // = "pato_lmp.c"

#define EXEC_LEVEL 4

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D5E30.s")

int s00a_pato_lmp_800D5EC8(int unused, SVECTOR *svecs)
{
    int            count;
    unsigned char *param;

    count = 0;
    for (count = 0; (param = GCL_Get_Param_Result_80020AA4()); svecs++, count++)
    {
        GCL_StrToSV_80020A14(param, svecs);
    }
    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D5F1C.s")

void s00a_pato_lmp_800D5F38(POLY_FT4 *polys, int count, DG_TEX *tex)
{
    int offx, width;
    int offy, height;

    while (--count >= 0)
    {
        setPolyFT4(polys);
        setSemiTrans(polys, 1);

        offx = tex->field_8_offx;
        width = tex->field_A_width;
        offy = tex->field_9_offy;
        height = tex->field_B_height;

        setUVWH(polys, offx, offy, width, height);

        polys->tpage = tex->field_4_tPage;
        polys->clut = tex->field_6_clut;
        polys->tpage |= 0x60;

        polys->r0 = 0;
        polys->g0 = 0;
        polys->b0 = 0;

        polys++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D5FC4.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D617C.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6194.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6550.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6600.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6678.s")
int s00a_pato_lmp_800D6678(PatoLmpWork *work);

void s00a_pato_lmp_800D6C44(PatoLmpWork *work)
{
    DG_PRIM *prim;
    void    *allocated;
    int      i;

    prim = work->field_1008;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    for (i = 0; i < work->field_1004; i++)
    {
        GM_FreeObject_80034BF8(&work->field_24[i].field_0);
        GM_FreeObject_80034BF8(&work->field_3B4[i].field_0);
        GM_FreeObject_80034BF8(&work->field_744[i].field_0);
        GM_FreeObject_80034BF8(&work->field_AD4[i].field_0);
    }
    allocated = work->field_20;
    if (allocated)
    {
        GV_DelayedFree_80016254(allocated);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6D24.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6D40.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6E28.s")
int s00a_pato_lmp_800D6E28(PatoLmpWork *work, int, int);

GV_ACT * s00a_pato_lmp_800D7A2C(int arg0, int arg1)
{
    PatoLmpWork *work;

    work = (PatoLmpWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PatoLmpWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_pato_lmp_800D6678, (TActorFunction)s00a_pato_lmp_800D6C44, aPatoLmpC);

        if (s00a_pato_lmp_800D6E28(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
