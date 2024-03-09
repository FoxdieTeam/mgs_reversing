#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"

typedef struct ValcanWork
{
    GV_ACT   actor;
    int      field_20;
    CONTROL  field_24;
    OBJECT   field_A0;
    OBJECT   field_184;
    char     pad_268[0x3BC];
    MATRIX   field_624[2];
    TARGET  *field_664;
    TARGET  *field_668;
    char     pad_66C[0x3C];
    int      field_6A8;
    char     pad_6AC[8];
    int      field_6B4;
    char     pad_6B8[4];
    int      field_6BC;
    char     pad_6C0[0x34];
    DG_PRIM *field_6F4;
    char     pad_6F8[0xDC];
    int      field_7D4;
    char     pad_7D8[0x44];
    int      field_81C;
    char     pad_820[0xB0];
    int      field_8D0;
    int      field_8D4;
    int      field_8D8;
    char     pad_8DC[0x24];
    int      field_900;
    char     pad_904[8];
    int      field_90C;
    SVECTOR  field_910;
    int      field_918;
    int      field_91C;
    char     pad_920[8];
    HZD_SEG  field_928;
    char     pad_938[0x1C];
} ValcanWork;

#define EXEC_LEVEL 4

extern char s15c_dword_800E2E5C[];

extern SVECTOR s15c_dword_800C35F0;
extern SVECTOR s15c_dword_800C35F8;
extern int     s15c_dword_800E346C;
extern SVECTOR s15c_dword_800E3474;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Time_800AB330;
extern SVECTOR GM_PlayerPosition_800ABA10;

void    AN_Breath_800C3AA8(MATRIX *matrix);
GV_ACT *NewFadeIo_800C4224(int name, int where);

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D8D20.s")
int s15c_valcan_800D8D20(CONTROL *, SVECTOR *);

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D8D5C.s")
void s15c_valcan_800D8D5C(ValcanWork *work, int);

void ValcanDequeueDynamicSegment_800D8DA0(ValcanWork *work)
{
    HZD_DequeueDynamicSegment2_8006FE44(Map_FromId_800314C0(work->field_20)->field_8_hzd, &work->field_928);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D8DD8.s")
void s15c_valcan_800D8DD8(ValcanWork *work);

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D8E88.s")

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D8ECC.s")
void s15c_valcan_800D8ECC(ValcanWork *work);

// Identical to item_init_prim_buffer_800336A4
void Valcan_800D9028(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1

    setPolyFT4(prims);
    setSemiTrans(prims, 1);

    t_u0 = tex->field_8_offx;
    t_u1 = t_u0 + tex->field_A_width;

    t_v0 = tex->field_9_offy;
    t_v2 = t_v0 + tex->field_B_height;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->field_4_tPage;
    prims->clut = tex->field_6_clut;
}

void Valcan_800D9B5C(ValcanWork *);

void ValcanAct_800D9088(ValcanWork *work)
{
    CONTROL *control;

    if (GM_SnakeCurrentHealth <= 0)
    {
        GCL_ExecProc_8001FF2C(work->field_8D4, NULL);
    }
    if (!(GV_Time_800AB330 & 3))
    {
        AN_Breath_800C3AA8(&work->field_A0.objs->objs[6].world);
    }
    if (work->field_7D4 != 2)
    {
        control = &work->field_24;
        GM_CurrentMap_800AB9B0 = work->field_20;
        Valcan_800D9B5C(work);
        s15c_valcan_800D8ECC(work);
        if (work->field_81C == 0)
        {
            GM_ActControl_80025A7C(control);
            GM_ActObject2_80034B88(&work->field_A0);
            GM_Target_SetVector_8002D500(work->field_664, &control->field_0_mov);
            GM_Target_SetVector_8002D500(work->field_668, &control->field_0_mov);
            sub_8002DA14(work->field_668);
            if (GM_CurrentItemId == ITEM_THERM_G)
            {
                DG_AmbientObjs(work->field_A0.objs);
            }
            else
            {
                DG_UnAmbientObjs(work->field_A0.objs);
            }
            DG_GetLightMatrix2_8001A5D8(&control->field_0_mov, work->field_624);
        }
    }
    s15c_dword_800E3474 = work->field_24.field_0_mov;
    if (work->field_81C == 1)
    {
        work->field_81C = 2;
    }
    if (work->field_81C == 2)
    {
        work->field_81C = 3;
        work->field_8D8 = 30;
        NewFadeIo_800C4224(0, 20);
    }
    if (work->field_81C == 3)
    {
        if (work->field_8D8-- < 0)
        {
            s15c_dword_800E346C = work->field_81C;
            GV_DestroyActor_800151C8(&work->actor);
        }
    }
    ValcanDequeueDynamicSegment_800D8DA0(work);
    s15c_valcan_800D8DD8(work);
    if (GV_DiffDirAbs_8001706C(work->field_24.field_8_rot.vy,
                               s15c_valcan_800D8D20(&work->field_24, &GM_PlayerPosition_800ABA10)) < 1024)
    {
        s15c_valcan_800D8D5C(work, 223);
    }
    else
    {
        s15c_valcan_800D8D5C(work, 219);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D92A8.s")

void ValcanDie_800D96E8(ValcanWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->field_24);
    GM_FreeObject_80034BF8(&work->field_A0);
    GM_FreeObject_80034BF8(&work->field_184);
    prim = work->field_6F4;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    GM_FreeTarget_8002D4B0(work->field_664);
    GM_FreeTarget_8002D4B0(work->field_668);
    GCL_ExecProc_8001FF2C(work->field_8D0, NULL);
    ValcanDequeueDynamicSegment_800D8DA0(work);
}

int ValcanGetResources2_800D9774(ValcanWork *work)
{
    TARGET *target, *target2;

    target = GM_AllocTarget_8002D400();
    work->field_664 = target;

    if (target != NULL)
    {
        GM_SetTarget_8002DC74(target, 0x15, 2, &s15c_dword_800C35F0);
        GM_Target_8002DCCC(target, 1, -1, work->field_6A8, 0xFF, &DG_ZeroVector_800AB39C);
        work->field_900 = work->field_6A8;

        target2 = GM_AllocTarget_8002D400();
        work->field_668 = target2;

        if (target2 != NULL)
        {
            GM_SetTarget_8002DC74(target2, 8, 0, &s15c_dword_800C35F8);
            target2->field_3C = 1;
            return 0;
        }
    }

    return -1;
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_valcan_800D9830.s")
int s15c_valcan_800D9830(ValcanWork *work, int, int);

GV_ACT *NewValcan_800D9864(int arg0, int arg1)
{
    ValcanWork *work;

    work = (ValcanWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ValcanWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ValcanAct_800D9088, (TActorFunction)ValcanDie_800D96E8,
                                  s15c_dword_800E2E5C);
        if (s15c_valcan_800D9830(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        if (ValcanGetResources2_800D9774(work) < 0)
        {
            return NULL;
        }
    }

    return &work->actor;
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D990C.s")
void s15c_crow_800D990C(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D99F0.s")
void s15c_crow_800D99F0(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9AB8.s")
void s15c_crow_800D9AB8(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9B3C.s")

void s15c_crow_800DD03C(ValcanWork *work);

void Valcan_800D9B5C(ValcanWork *work)
{
    SVECTOR unused;

    s15c_crow_800DD03C(work);
    switch (work->field_90C)
    {
    case 0:
        work->field_90C = 1;
        break;

    case 1:
        work->field_90C = 2;
        s15c_crow_800D99F0(work);

    case 2:
        s15c_crow_800D990C(work);
        break;
    }

    s15c_crow_800D9AB8(work);

    unused.vx = 0;
    unused.vy = -730;
    unused.vz = -150;

    work->field_184.objs->root = &work->field_A0.objs->objs[4].world;
    GM_ActObject2_80034B88(&work->field_184);

    if (GM_CurrentItemId == ITEM_THERM_G)
    {
        DG_AmbientObjs(work->field_184.objs);
    }
    else
    {
        DG_UnAmbientObjs(work->field_184.objs);
    }

    DG_GetLightMatrix2_8001A5D8(&work->field_24.field_0_mov, work->field_624);

    switch (work->field_91C)
    {
    case 1:
        work->field_6B4 = 0;
        work->field_91C = 2;
        work->field_918 = 0;
        GM_Sound_800329C4(&work->field_910, 180, 1);

    case 2:
        work->field_918 += 1;
        work->field_6B4 += 20;
        if (work->field_918 >= 16)
        {
            work->field_91C = 3;
            work->field_918 = 0;
        }
        break;
    case 3:
        if (mts_get_tick_count_8008BBB0() - work->field_6BC >= 4)
        {
            work->field_6BC = mts_get_tick_count_8008BBB0();
            GM_Sound_800329C4(&work->field_910, 179, 1);
        }
        break;

    default:
        work->field_6B4 -= 6;
        if (work->field_6B4 < 0)
        {
            work->field_6B4 = 0;
        }
        else if (mts_get_tick_count_8008BBB0() - work->field_6BC > work->field_918 + 4)
        {
            work->field_918 += 6;
            work->field_6BC = mts_get_tick_count_8008BBB0();
        }
        break;
    }
    work->field_184.rots[1].vy += work->field_6B4;
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9D90.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9DC0.s")

// Identical to Eventmouse_800C9288
void Valcan_800D9EBC(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;

    GV_SubVec3_80016D40(to, from, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3_80016D80(&diff), y) & 0xFFF) - 1024;
    out->vz = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9F3C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800D9F8C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA044.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA140.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA1AC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA21C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA2A8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA558.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA8E4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA990.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DACCC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DAE38.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DAE7C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DAFCC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB200.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB2E4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB470.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB500.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB868.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB9F0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DBCB4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DBF74.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC06C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC124.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC290.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC2EC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC318.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC7A0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DCC84.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DCE60.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DCF8C.s")

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DD03C.s")
void s15c_crow_800DD03C(ValcanWork *work);

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DD578.s")
