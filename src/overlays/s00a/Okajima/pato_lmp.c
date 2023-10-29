#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/object.h"
#include "Game/camera.h"

typedef struct _PatoLmpSub // It's probably OBJECT + 24 rots
{
    OBJECT field_0;
    char   field_24[0xC0];
} PatoLmpSub;

typedef struct _PatoLmpSub2 // It's probably MATRIX[2]
{
    MATRIX field_0;
    char   field_20[0x20];
} PatoLmpSub2;

typedef struct _PatoLmpPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} PatoLmpPrims;

typedef struct _PatoLmpWork
{
    GV_ACT         actor;
    PatoLmpPrims  *field_20;
    PatoLmpSub     field_24[4];
    PatoLmpSub     field_3B4[4];
    PatoLmpSub     field_744[4];
    PatoLmpSub     field_AD4[4];
    PatoLmpSub2    field_E64[4];
    char           field_F64[0x40];
    SVECTOR        field_FA4[4];
    SVECTOR        field_FC4[4];
    SVECTOR        field_FE4[4];
    int            field_1004;
    DG_PRIM       *field_1008;
    char           field_100C[0x100];
    int            field_110C[4];
    char           field_111C[0x800];
    int            field_191C;
    int            field_1920;
    int            field_1924;
    SVECTOR        field_1928;
    SVECTOR        field_1930;
    int            field_1938;
    int            field_193C;
    int            field_1940;
    int            field_1944;
    int            field_1948;
    unsigned short field_194C;
    short          field_194E;
    int            field_1950;
    int            field_1954;
    int            field_1958;
    int            field_195C;
    int            field_1960;
    int            field_1964;
} PatoLmpWork;

extern const char aPatoLmpC[]; // = "pato_lmp.c"
extern const char s00a_aClose_800E0AF4[];
extern const char s00a_aOpen_800E0AEC[];
extern const char s00a_aSeoff_800E0B04[];
extern const char s00a_aSeon_800E0AFC[];
extern const char s00a_dword_800E0ADC[];
extern const char s00a_dword_800E0AE4[];

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern int              GV_Clock_800AB920;

#define EXEC_LEVEL 4

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D5E30.s")
int s00a_pato_lmp_800D5E30(int field_194C, int count, short *hashes);

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
void s00a_pato_lmp_800D5FC4(PatoLmpWork *work);

void s00a_pato_lmp_800D617C(PatoLmpWork *work, int field_191C, short vx, short vy, short vz)
{
    work->field_1920 = field_191C;
    work->field_1930.vx = vx;
    work->field_1930.vy = vy;
    work->field_1930.vz = vz;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6194.s")
void s00a_pato_lmp_800D6194(PatoLmpWork *, int arg2, int arg3, int arg4);
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6550.s")
void s00a_pato_lmp_800D6550(PatoLmpWork *work);
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_pato_lmp_800D6600.s")
void s00a_pato_lmp_800D6600(PatoLmpWork *work);

void s00a_pato_lmp_800D6678(PatoLmpWork *work)
{
    SVECTOR svec;
    short   hashes[6];
    int     i;
    int     sp30;

    int field_1940;
    int field_1940_2;

    char *ot;

    PatoLmpSub *field_3B4_iter;
    PatoLmpSub *field_AD4_iter;
    PatoLmpSub *field_744_iter;
    SVECTOR    *field_FA4_iter;
    SVECTOR    *field_FE4_iter;

    short zero;

    zero = 0;
    GM_CurrentMap_800AB9B0 = work->field_1948;

    hashes[0] = GV_StrCode_80016CCC(s00a_dword_800E0ADC);
    hashes[1] = GV_StrCode_80016CCC(s00a_dword_800E0AE4);
    hashes[2] = GV_StrCode_80016CCC(s00a_aOpen_800E0AEC);
    hashes[3] = GV_StrCode_80016CCC(s00a_aClose_800E0AF4);
    hashes[4] = GV_StrCode_80016CCC(s00a_aSeon_800E0AFC);
    hashes[5] = GV_StrCode_80016CCC(s00a_aSeoff_800E0B04);

    switch (s00a_pato_lmp_800D5E30(work->field_194C, 6, hashes))
    {
    case 0:
    case 2:
        work->field_1950 = 1;
        s00a_pato_lmp_800D6550(work);
        work->field_1940 = 0;
        work->field_195C = 1;
        break;

    case 1:
    case 3:
        work->field_1950 = 0;
        s00a_pato_lmp_800D6600(work);
        break;

    case 4:
        work->field_195C = 1;
        break;

    case 5:
        work->field_195C = 0;
        break;
    }

    if (work->field_1958 == 0)
    {
        work->field_1958 = 1;

        for (i = 0; i < work->field_1004; i++)
        {
            DG_SetPos2_8001BC8C(&work->field_FA4[i], &work->field_FC4[i]);
            GM_ActObject2_80034B88(&work->field_3B4[i].field_0);
            GM_ActObject2_80034B88(&work->field_24[i].field_0);
            DG_GetLightMatrix_8001A3C4(&work->field_FA4[i], &work->field_E64[i].field_0);
        }
    }

    if (work->field_1950 != 0 || work->field_193C != 0)
    {
        work->field_1940++;
        sp30 = 65536;

        if (work->field_1950 == 1)
        {
            field_FA4_iter = work->field_FA4;
            field_FE4_iter = work->field_FE4;
            field_3B4_iter = work->field_3B4;
            field_744_iter = work->field_744;
            field_AD4_iter = work->field_AD4;

            work->field_193C = work->field_1950;

            for (i = 0; i < work->field_1004;
                 i++, field_FA4_iter++, field_FE4_iter++, field_3B4_iter++, field_744_iter++, field_AD4_iter++)
            {
                field_FE4_iter->vy += 128;
                DG_SetPos2_8001BC8C(field_FA4_iter, field_FE4_iter);
                GM_ActObject2_80034B88(&field_744_iter->field_0);

                svec = *field_FE4_iter;
                svec.vy += 2048;

                DG_SetPos2_8001BC8C(field_FA4_iter, &svec);
                GM_ActObject2_80034B88(&field_AD4_iter->field_0);
                GM_ActObject2_80034B88(&field_3B4_iter->field_0);

                if (work->field_1954 == 1)
                {
                    sp30 = 0;
                }
                else
                {
                    work->field_110C[i] = GV_DistanceVec3_80016E84(field_FA4_iter, &gUnkCameraStruct2_800B7868.eye);
                    if (work->field_110C[i] < sp30)
                    {
                        sp30 = work->field_110C[i];
                    }
                }
            }
        }
        else
        {
            sp30 = 0;
        }

        field_1940 = work->field_1940;
        field_1940 %= 32;
        if (mts_get_tick_count_8008BBB0() - work->field_1960 >= 64)
        {
            work->field_1960 = mts_get_tick_count_8008BBB0();
            if (work->field_1950 == 1)
            {
                if (work->field_195C == work->field_1950)
                {
                    GM_SeSet2_80032968(0, 127, work->field_1964);
                }
            }
        }

        field_1940_2 = field_1940 + 16;
        if (field_1940_2 >= 32)
        {
            field_1940_2 = field_1940 - 16;
        }
        for (i = 0; i < work->field_1004; i++)
        {
            s00a_pato_lmp_800D6194(work, i, field_1940, 0);
            s00a_pato_lmp_800D6194(work, i, field_1940_2, 1);
        }

        if (work->field_193C == 1 && sp30 < 16384)
        {
            ot = DG_ChanlOTag(0);
            addPrim(ot, &work->field_20->tile[GV_Clock_800AB920]);
            addPrim(ot, &work->field_20->tpage[GV_Clock_800AB920]);
            s00a_pato_lmp_800D5FC4(work);
            if (work->field_1924 == work->field_1920)
            {
                work->field_1924 = zero;
                work->field_1928 = work->field_1930;
                switch (work->field_1938)
                {
                case 0:
                    sp30 = 16384 - sp30;
                    s00a_pato_lmp_800D617C(work, work->field_191C, sp30 / 128, sp30 / 512, 0);
                    break;

                case 1:
                    s00a_pato_lmp_800D617C(work, work->field_191C, 0, 0, 0);
                    break;
                }
                work->field_1938++;

                if (work->field_1938 >= 2)
                {
                    work->field_1938 = 0;
                }
                if (work->field_1938 == 1 && work->field_1950 == 0)
                {
                    work->field_193C = 0;
                }
            }
        }
    }
}

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

GV_ACT *s00a_pato_lmp_800D7A2C(int arg0, int arg1)
{
    PatoLmpWork *work;

    work = (PatoLmpWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PatoLmpWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_pato_lmp_800D6678,
                                  (TActorFunction)s00a_pato_lmp_800D6C44, aPatoLmpC);

        if (s00a_pato_lmp_800D6E28(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
