#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct _PatoLmpWork
{
    GV_ACT actor;
    char   pad[0x1948];
} PatoLmpWork;

extern const char aPatoLmpC[]; // = "pato_lmp.c"

#define EXEC_LEVEL 4

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D5E30.s")

int s00a_pato_lmp_800D5EC8(int unused, SVECTOR *svecs)
{
    int count;
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

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6C44.s")
int s00a_pato_lmp_800D6C44(PatoLmpWork *work);

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
