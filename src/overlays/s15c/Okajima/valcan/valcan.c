#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Okajima/bullet.h"
#include "Okajima/blood.h"

typedef struct ValcanWork
{
    GV_ACT         actor;
    int            field_20;
    CONTROL        field_24;
    OBJECT         field_A0;
    OBJECT         field_184;
    MOTION_CONTROL field_268;
    OAR_RECORD     field_2B8;
    char           pad2DC[0x240];
    SVECTOR        field_51C;
    SVECTOR        field_524;
    char           pad52C[0x78];
    SVECTOR        field_5A4[0x10];
    MATRIX         field_624[2];
    TARGET        *field_664;
    TARGET        *field_668;
    int            field_66C;
    int            field_670;
    char           pad674[0x10];
    int            field_684;
    int            field_688;
    char           pad68C[4];
    int            field_690;
    char           pad694[0x14];
    int            field_6A8;
    char           pad6AC[8];
    int            field_6B4;
    char           pad6B8[4];
    int            field_6BC;
    int            field_6C0;
    SVECTOR        field_6C4;
    SVECTOR        field_6CC;
    SVECTOR        field_6D4;
    char           pad6DC[0x18];
    DG_PRIM       *field_6F4;
    short          field_6F8[4][4][2];
    short          field_738;
    short          field_73A;
    short          field_73C;
    short          field_73E;
    int            field_740;
    char           pad744[0x10];
    short          field_754;
    short          field_756;
    int            field_758;
    char           pad75C[0x10];
    int            field_76C;
    int            field_770;
    int            field_774;
    char           pad778[0x1C];
    int            field_794;
    int            field_798;
    char           pad79C[4];
    short          field_7A0;
    short          field_7A2;
    char           pad7A4[8];
    unsigned short field_7AC;
    char           pad7AE[2];
    unsigned short field_7B0;
    char           pad7B2[0x22];
    int            field_7D4;
    char           pad7D8[0x44];
    int            field_81C;
    int            field_820;
    int            field_824;
    int            field_828;
    int            field_82C;
    int            field_830;
    int            field_834;
    int            field_838;
    int            field_83C;
    char           pad840[0x38];
    SVECTOR        field_878;
    char           pad880[0x50];
    int            field_8D0;
    int            field_8D4;
    int            field_8D8;
    char           pad8DC[0x14];
    int            field_8F0;
    MENU_BAR_CONF  field_8F4;
    int            field_900;
    int            field_904;
    char           pad908[4];
    int            field_90C;
    SVECTOR        field_910;
    int            field_918;
    int            field_91C;
    int            field_920;
    char           pad924[4];
    HZD_SEG        field_928;
    char           pad938[0xC];
    unsigned short field_944;
    char           pad946[2];
    unsigned short field_948;
    char           pad94A[0xA];
} ValcanWork;

#define EXEC_LEVEL 4

SVECTOR s15c_dword_800C3608 = {0, 0, 100};
SVECTOR s15c_dword_800C3610 = {64512, 0, 0};

int     SECTION("overlay.bss") s15c_dword_800E346C;
int     SECTION("overlay.bss") s15c_dword_800E3470;
SVECTOR SECTION("overlay.bss") s15c_dword_800E3474;
char    SECTION("overlay.bss") s15c_dword_800E347C[8]; // could be smaller, it only has to be 6 bytes large
int     SECTION("overlay.bss") s15c_dword_800E3484;
int     SECTION("overlay.bss") s15c_dword_800E3488;

extern char s15c_dword_800E2E5C[];
extern char s15c_aBarrel_800E2E4C[];
extern char s15c_aShadow_800E2E54[];
extern char s15c_aVala_800E2E44[];
extern char s15c_aValwep_800E2E3C[];
extern char s15c_aRaven_800E2E68[];

extern SVECTOR s15c_dword_800C35F0;
extern SVECTOR s15c_dword_800C35F8;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_Time_800AB330;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern int     dword_8009F46C;
extern int     amissile_alive_8009F490;
extern SVECTOR svector_8009F478;
extern SVECTOR svector_8009F494;

void    AN_Breath_800C3AA8(MATRIX *matrix);
GV_ACT *NewFadeIo_800C4224(int name, int where);

int Valcan_800D8D20(CONTROL *control, SVECTOR *svec1)
{
    SVECTOR svec2;

    GV_SubVec3_80016D40(svec1, &control->field_0_mov, &svec2);
    return ratan2(svec2.vx, svec2.vz) & 0xFFF;
}

void ValcanQueueDynamicSegment_800D8D5C(ValcanWork *work, int flag)
{
    HZD_QueueDynamicSegment2_8006FDDC(Map_FromId_800314C0(work->field_20)->field_8_hzd, &work->field_928, flag);
}

void ValcanDequeueDynamicSegment_800D8DA0(ValcanWork *work)
{
    HZD_DequeueDynamicSegment2_8006FE44(Map_FromId_800314C0(work->field_20)->field_8_hzd, &work->field_928);
}

void Valcan_800D8DD8(ValcanWork *work)
{
    SVECTOR svec1, svec2;

    svec1.vx = -500;
    svec1.vy = 0;
    svec1.vz = -1000;

    svec2.vx = 500;
    svec2.vy = 0;
    svec2.vz = -1000;

    DG_SetPos2_8001BC8C(&work->field_24.field_0_mov, &work->field_24.field_8_rot);
    DG_PutVector_8001BE48(&svec1, &svec1, 2);

    work->field_928.p1.y = 500;
    work->field_928.p1.h = 1500;
    work->field_928.p2.y = 500;
    work->field_928.p2.h = 1500;

    work->field_928.p1.x = svec1.vx;
    work->field_928.p2.x = svec2.vx;
    work->field_928.p1.z = svec1.vz;
    work->field_928.p2.z = svec2.vz;

    HZD_SetDynamicSegment_8006FEE4(&work->field_928, &work->field_928);
}

// Identical to BloodClGetInts_800C9A00
void ValcanGetInts_800D8E88(unsigned char *opt, int *out)
{
    char *res;

    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *out = GCL_StrToInt_800209E8(res);
        out++;
    }
}

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
    Valcan_800D8DD8(work);
    if (GV_DiffDirAbs_8001706C(work->field_24.field_8_rot.vy,
                               Valcan_800D8D20(&work->field_24, &GM_PlayerPosition_800ABA10)) < 1024)
    {
        ValcanQueueDynamicSegment_800D8D5C(work, 223);
    }
    else
    {
        ValcanQueueDynamicSegment_800D8D5C(work, 219);
    }
}

void Valcan_800D9B3C(ValcanWork *work);

int ValcanGetResources_800D92A8(ValcanWork *work, int name, int where)
{
    int            args[15];
    CONTROL       *control;
    DG_PRIM       *prim;
    DG_TEX        *tex;
    OBJECT        *object1, *object2;
    unsigned char *option;
    int            i, j;
    int            k500;

    work->field_20 = where;
    GM_CurrentMap_800AB9B0 = where;

    option = (unsigned char *)GCL_GetOption_80020968('s');
    if (option)
    {
        work->field_7D4 = GCL_StrToInt_800209E8(option);
    }
    else
    {
        work->field_7D4 = 1;
    }

    control = &work->field_24;
    if (work->field_7D4 != 2)
    {
        k500 = 500;
        if (GM_InitLoader_8002599C(control, name, where) < 0)
        {
            return -1;
        }

        GM_ConfigControlAttribute_8002623C(control, 5);
        GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
        GM_ConfigControlInterp_80026244(control, 4);

        option = (unsigned char *)GCL_GetOption_80020968('h');
        if (option)
        {
            work->field_6A8 = GCL_StrToInt_800209E8(option);
            work->field_6A8 = work->field_6A8 / 8 * 8;
        }
        else
        {
            work->field_6A8 = 1024;
        }

        for (j = 0; j < 4; j++)
        {
            for (i = 0; i < 4; i++)
            {
                work->field_6F8[i][j][0] = i * 7000 - 10500;
                work->field_6F8[i][j][1] = j * 6000 - 7500;
            }
        }

        option = (unsigned char *)GCL_GetOption_80020968('p');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_738 = args[0];
        work->field_73A = args[1];

        work->field_24.field_0_mov.vx = work->field_6F8[work->field_738][work->field_73A][0];
        work->field_24.field_0_mov.vy = 0;
        work->field_24.field_0_mov.vz = work->field_6F8[work->field_738][work->field_73A][1];

        option = (unsigned char *)GCL_GetOption_80020968('q');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_73C = args[0];
        work->field_73E = args[1];

        work->field_6C4 = work->field_24.field_0_mov;
        work->field_6CC = work->field_24.field_8_rot;

        option = (unsigned char *)GCL_GetOption_80020968('n');
        if (option)
        {
            work->field_8D0 = GCL_StrToInt_800209E8(option);
        }

        option = (unsigned char *)GCL_GetOption_80020968('i');
        if (option)
        {
            work->field_8D4 = GCL_StrToInt_800209E8(option);
        }

        object1 = &work->field_A0;
        GM_InitObject_80034A18(object1, GV_StrCode_80016CCC(s15c_aValwep_800E2E3C), 0x22D,
                               GV_StrCode_80016CCC(s15c_aVala_800E2E44));
        GM_ConfigObjectJoint_80034CB4(object1);
        GM_ConfigMotionControl_80034F08(object1, &work->field_268, GV_StrCode_80016CCC(s15c_aVala_800E2E44),
                                        &work->field_2B8, NULL, control, &work->field_524);
        GM_ConfigObjectLight_80034C44(object1, work->field_624);

        object2 = &work->field_184;
        GM_InitObject_80034A18(object2, GV_StrCode_80016CCC(s15c_aBarrel_800E2E4C), 0x22D, 0);
        GM_ConfigObjectLight_80034C44(object2, work->field_624);
        GM_ConfigObjectJoint_80034CB4(object2);

        Valcan_800D9B3C(work);
        s15c_valcan_800D8ECC(work);

        work->field_6F4 = prim = DG_GetPrim(0x12, 1, 0, &work->field_6D4, NULL);
        if (work->field_6F4 == NULL)
        {
            return -1;
        }

        prim->field_2E_k500 = k500;

        tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(s15c_aShadow_800E2E54));
        if (tex == NULL)
        {
            return -1;
        }

        Valcan_800D9028(&prim->field_40_pBuffers[0]->poly_ft4, tex);
        Valcan_800D9028(&prim->field_40_pBuffers[1]->poly_ft4, tex);

        setRGB0(&prim->field_40_pBuffers[0]->poly_ft4, 150, 150, 150);
        setRGB0(&prim->field_40_pBuffers[1]->poly_ft4, 150, 150, 150);

        work->field_878 = GM_PlayerPosition_800ABA10;

        NewFadeIo_800C4224(1, 20);
    }

    ValcanQueueDynamicSegment_800D8D5C(work, 0xDF);
    return 0;
}

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

int ValcanGetResources_800D9830(ValcanWork *work, int name, int where)
{
    s15c_dword_800E346C = 0;
    if (ValcanGetResources_800D92A8(work, name, where) < 0)
    {
        return -1;
    }
    return 0;
}

GV_ACT *NewValcan_800D9864(int name, int where)
{
    ValcanWork *work;

    work = (ValcanWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(ValcanWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)ValcanAct_800D9088, (TActorFunction)ValcanDie_800D96E8,
                                  s15c_dword_800E2E5C);
        if (ValcanGetResources_800D9830(work, name, where) < 0)
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

void Valcan_800D990C(ValcanWork *work)
{
    int rest;
    int now;

    now = (work->field_900 << 10) / work->field_6A8 / 8 * 8;
    if (now < 0)
    {
        now = 0;
        work->field_664->field_26_hp = 0;
        work->field_900 = 0;
    }

    rest = work->field_904;
    if (rest < now)
    {
        rest = now;
    }
    if (now < rest)
    {
        work->field_904 -= 8;
    }

    if (rest < 8 || now < 8)
    {
        rest = 8;
        now = 8;
    }

    menu_DrawBar2_80038DE0(28, rest, now, 1024, &work->field_8F4);
}

void Valcan_800D99F0(ValcanWork *work)
{
    MENU_BAR_CONF *bar;

    work->field_904 = (work->field_900 << 10) / work->field_6A8 / 8 * 8;
    memcpy(s15c_dword_800E347C, s15c_aRaven_800E2E68, 6); // 6 == strlen("RAVEN") + 1
    work->field_8F4.field_0_text = s15c_dword_800E347C;

    bar = &work->field_8F4;
    bar->field_4_rgb_left[0] = 16;
    bar->field_4_rgb_left[1] = 111;
    bar->field_4_rgb_left[2] = 159;
    bar->field_7_rgb_right[0] = 31;
    bar->field_7_rgb_right[1] = 223;
    bar->field_7_rgb_right[2] = 127;
}

void Valcan_800D9AB8(ValcanWork *work)
{
    CONTROL *control;

    control = &work->field_24;
    control->field_32_height = work->field_A0.field_18;
    control->field_36 = GV_NearExp2_80026384(control->field_36, 450);

    if (work->field_66C < 0 && control->field_57 != 0)
    {
        work->field_66C = 0;
    }
    work->field_66C -= 16;

    control->field_44_step.vy = work->field_66C;
}

void s15c_crow_800DD578(ValcanWork *work);

void Valcan_800D9B3C(ValcanWork *work)
{
    s15c_crow_800DD578(work);
}

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
        Valcan_800D99F0(work);

    case 2:
        Valcan_800D990C(work);
        break;
    }

    Valcan_800D9AB8(work);

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

void Valcan_800D9D90(ValcanWork *work)
{
    SVECTOR *svec;

    work->field_24.field_3C.vx = work->field_24.field_8_rot.vy + work->field_5A4[6].vy;

    svec = &work->field_24.field_3C;
    svec->vy = work->field_944;
    svec->vz = work->field_948;
    svec->pad = 0;
}

int Valcan_800D9DC0(ValcanWork *work, int param_2)
{
    SVECTOR svec1, pos;
    int     vx, vy, vz;

    svec1.vx = work->field_A0.objs->objs[4].world.t[0];
    svec1.vy = work->field_A0.objs->objs[4].world.t[1];
    svec1.vz = work->field_A0.objs->objs[4].world.t[2];

    if (param_2)
    {
        pos = GM_PlayerPosition_800ABA10;
    }
    else
    {
        pos = work->field_51C;
    }

    vx = (svec1.vx - pos.vx) >> 4;
    vy = (svec1.vy - pos.vy) >> 4;
    vz = (svec1.vz - pos.vz) >> 4;
    return SquareRoot0(vx * vx + vy * vy + vz * vz) * 16;
}

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

void Valcan_800D9F3C(ValcanWork *work, int count)
{
    SVECTOR *out;
    int      i;

    out = work->field_5A4;
    work->field_690 = 0;
    for (i = 0; i < count; i++, out++)
    {
        *out = DG_ZeroVector_800AB39C;
    }
}

void Valcan_800D9F8C(ValcanWork *work)
{
    if (dword_8009F46C == 1)
    {
        work->field_51C = svector_8009F478;
        return;
    }
    work->field_82C = 0;
    if (amissile_alive_8009F490 == 1)
    {
        work->field_51C = svector_8009F494;
        return;
    }
    work->field_838 = 0;
    work->field_51C = GM_PlayerPosition_800ABA10;
}

void Valcan_800DA044(ValcanWork *work)
{
    // FIXME: why does this function do everything on stack?
    // FIXME: is there a better for loop match (without those strange break/continues)?
    short sp0[6];

    sp0[4] = (work->field_6F8[1][0][0] - work->field_6F8[0][0][0]) / 2;
    sp0[5] = (work->field_6F8[0][1][1] - work->field_6F8[0][0][1]) / 2;

    sp0[0] = 0;
    for (;;)
    {
        if (work->field_24.field_0_mov.vx >= work->field_6F8[sp0[0]][0][0] + sp0[4])
        {
            if (++sp0[0] < 4)
            {
                continue;
            }
        }
        break;
    }

    sp0[1] = 0;
    for (;;)
    {
        if (work->field_24.field_0_mov.vz >= work->field_6F8[0][sp0[1]][1] + sp0[5])
        {
            if (++sp0[1] < 4)
            {
                continue;
            }
        }
        break;
    }

    work->field_7A0 = sp0[0];
    work->field_7A2 = sp0[1];
}

void Valcan_800DA140(ValcanWork *work)
{
    if (work->field_690 >= 48)
    {
        if (work->field_690 < 144)
        {
            work->field_5A4[6].vy -= 8;
        }
        else if (work->field_690 < 192)
        {
            work->field_5A4[6].vy += 8;
        }
    }
    else
    {
        work->field_5A4[6].vy += 8;
    }

    if (++work->field_690 >= 192)
    {
        work->field_690 = 0;
    }
}

int Valcan_800DA1AC(int arg0, int arg1)
{
    if (arg0 < 2)
    {
        arg0 = 1 - arg0;
    }

    arg0 = 1 - arg0 % 2 * 2;
    arg1 = 1 - (arg1 - (arg1 / 2 * 2)) * 2;

    return (arg0 * arg1 + 1) / 2 + 2;
}

void Valcan_800DA21C(ValcanWork *work) // it possibly returns a BulletWork*
{
    MATRIX  rotmat;
    SVECTOR svec;

    Valcan_800D9EBC(&work->field_24.field_0_mov, &GM_PlayerPosition_800ABA10, &svec);
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &svec);
    ReadRotMatrix(&rotmat);
    NewBulletEx_80076708(2048, &rotmat, 2, 0, 0, 30, 90, 30000, 100);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA2A8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA558.s")
int s15c_crow_800DA558(ValcanWork *work, int);

void Valcan_800DA8E4(ValcanWork *work)
{
    SVECTOR  svecs[2];
    CONTROL *control;

    control = &work->field_24;

    svecs[0].vx = GV_RandU_80017090(512);
    svecs[0].vy = GV_RandU_80017090(512) + 256;
    svecs[0].vz = 500;
    svecs[1].vx = GV_RandU_80017090(256);
    svecs[1].vy = GV_RandU_80017090(256);
    svecs[1].vz = 200;

    DG_SetPos2_8001BC8C(&control->field_0_mov, &control->field_8_rot);
    DG_PutVector_8001BE48(svecs, svecs, 2);

    DG_SetTmpLight_8001A114(svecs, 500, 1000);
    DG_SetTmpLight_8001A114(svecs, 500, 500);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA990.s")

void Valcan_800DACCC(ValcanWork *work)
{
    if (work->field_758 != 0)
    {
        return;
    }

    switch (work->field_740)
    {
    case 0:
        Valcan_800DA044(work);
        work->field_24.field_0_mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx < work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 1:
        Valcan_800DA044(work);
        work->field_24.field_0_mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx > work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 2:
        Valcan_800DA044(work);
        work->field_24.field_0_mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
        if (work->field_6C4.vz < work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    case 3:
        Valcan_800DA044(work);
        work->field_24.field_0_mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
        if (work->field_6C4.vz > work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    }
}

int Valcan_800DAE38()
{
    return GV_RandU_80017090(4096) % 3 + 1;
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DAE7C.s")
int s15c_crow_800DAE7C(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DAFCC.s")
int s15c_crow_800DAFCC(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB200.s")
int s15c_crow_800DB200(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB2E4.s")
int s15c_crow_800DB2E4(ValcanWork *work);

int Valcan_800DB470(ValcanWork *work)
{
    switch (work->field_770)
    {
    case 0:
        return s15c_crow_800DAE7C(work);
    case 1:
        return s15c_crow_800DAFCC(work);
    case 2:
        return s15c_crow_800DB200(work);
    case 3:
        return s15c_crow_800DB2E4(work);
    default:
        return 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB500.s")

void Valcan_800DB868(ValcanWork *work)
{
    int diff1, diff2;

    if (work->field_770 == 2)
    {
        work->field_76C = 0;
    }
    else if (work->field_770 == 3 || (work->field_770 == 1 && work->field_774 != 0))
    {
        work->field_76C = 500;
    }
    else if ((work->field_770 == 0 && work->field_774 == 2) || (work->field_770 == 1 && work->field_774 == 0))
    {
        work->field_76C = 0;
    }
    else
    {
        work->field_76C = 2800;
    }

    diff1 = work->field_73C - work->field_738;
    diff2 = work->field_73E - work->field_73A;
    if (diff1 < 0)
    {
        work->field_740 = 0;
        work->field_754 = work->field_6F8[work->field_73C][work->field_73E][0] + work->field_76C;
    }
    else if (diff1 > 0)
    {
        work->field_740 = 1;
        work->field_754 = work->field_6F8[work->field_73C][work->field_73E][0] - work->field_76C;
    }
    else if (diff2 < 0)
    {
        work->field_740 = 2;
        work->field_756 = work->field_6F8[work->field_73C][work->field_73E][1] + work->field_76C;
    }
    else if (diff2 > 0)
    {
        work->field_740 = 3;
        work->field_756 = work->field_6F8[work->field_73C][work->field_73E][1] - work->field_76C;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DB9F0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DBCB4.s")

void Valcan_800DBF74(ValcanWork *work)
{
    int sqrt;
    int vx, vy;
    int diff1, diff2;
    int tan1, tan2;

    work->field_24.field_0_mov.vx = work->field_7AC;
    work->field_24.field_0_mov.vz = work->field_7B0;

    Valcan_800D9F3C(work, 16);

    diff1 = work->field_51C.vx - work->field_6C4.vx;
    diff2 = work->field_51C.vz - work->field_6C4.vz;
    tan1 = ratan2(diff1, diff2);

    vy = (tan1 + GV_RandS_800170BC(64)) & 0xFFF;

    sqrt = SquareRoot0(diff2 * diff2 + diff1 * diff1);
    diff1 = work->field_51C.vy - work->field_6C4.vy;
    tan2 = ratan2(sqrt, diff1);

    vx = (GV_RandS_800170BC(8) + tan2 - 1008) & 0xFFF;

    work->field_5A4[4].vx = vx - 32;
    work->field_5A4[7].vx = vx - 64;
    work->field_5A4[6].vx = vx - 32;
    work->field_5A4[9].vx = -512;

    work->field_24.field_4C_turn.vy = vy;
    work->field_24.field_4C_turn.vx = 0;
}

void Valcan_800DC06C(ValcanWork *work, int index, int blood_count)
{
    MATRIX mat;

    DG_SetPos_8001BC44(&work->field_A0.objs->objs[index].world);
    DG_MovePos_8001BD20(&s15c_dword_800C3608);

    s15c_dword_800C3610.vx += GV_RandS_800170BC(128);
    s15c_dword_800C3610.vy += GV_RandS_800170BC(128);
    s15c_dword_800C3610.vz += GV_RandS_800170BC(512);
    DG_RotatePos_8001BD64(&s15c_dword_800C3610);

    ReadRotMatrix(&mat);
    NewBlood_80072728(&mat, blood_count);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC124.s")

void Valcan_800DC290(ValcanWork *work, int arg1, int arg2)
{
    if (work->field_670 != arg1)
    {
        work->field_920 = 0;
        work->field_670 = arg1;
        GM_ConfigObjectAction_80034CD4(&work->field_A0, arg1, 0, 4);
    }
    else if (work->field_A0.is_end == 1)
    {
        work->field_688 = arg2;
    }
}

void Valcan_800DC2EC(ValcanWork *work, int action)
{
    work->field_670 = action;
    GM_ConfigObjectAction_80034CD4(&work->field_A0, action, 0, 4);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC318.s")
void s15c_crow_800DC318(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DC7A0.s")
void s15c_crow_800DC7A0(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DCC84.s")
void s15c_crow_800DCC84(ValcanWork *work);
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DCE60.s")
void s15c_crow_800DCE60(ValcanWork *work);

void Valcan_800DCF8C(ValcanWork *work)
{
    work->field_798 = work->field_794;
    work->field_794 = s15c_crow_800DA558(work, 0);
    switch (work->field_684)
    {
    case 0:
        work->field_8F0 = 0;
        s15c_crow_800DC7A0(work);
        Valcan_800DA140(work);
        break;
    case 1:
        work->field_8F0 = 1;
        s15c_crow_800DCC84(work);
        break;
    case 3:
        work->field_8F0 = 0;
        s15c_crow_800DCE60(work);
        break;
    }
    s15c_crow_800DC318(work);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DD03C.s")
void s15c_crow_800DD03C(ValcanWork *work);

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DD578.s")
void s15c_crow_800DD578(ValcanWork *work);
