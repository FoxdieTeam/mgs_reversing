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
    CONTROL        control;
    OBJECT         field_A0;
    OBJECT         field_184;
    MOTION_CONTROL field_268;
    MOTION_SEGMENT field_2B8;
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
    int            field_68C;
    int            field_690;
    int            field_694;
    int            field_698;
    int            field_69C;
    int            field_6A0;
    int            field_6A4;
    int            field_6A8;
    int            field_6AC;
    int            field_6B0;
    int            field_6B4;
    int            field_6B8;
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
    int            field_744[4];
    short          field_754;
    short          field_756;
    int            field_758;
    char           pad75C[12];
    int            field_768;
    int            field_76C;
    int            field_770;
    int            field_774;
    int            field_778;
    int            field_77C;
    int            field_780;
    int            field_784;
    int            field_788;
    int            field_78C;
    int            field_790;
    int            field_794;
    int            field_798;
    char           pad79C[4];
    short          field_7A0;
    short          field_7A2;
    SVECTOR        field_7A4;
    SVECTOR        field_7AC;
    int            field_7B4;
    char           pad7B8[0x1C];
    int            field_7D4;
    int            field_7D8;
    char           field_7DC[32][2]; // could be smaller
    int            field_81C;
    int            field_820;
    int            field_824;
    int            field_828;
    int            field_82C;
    int            field_830;
    int            field_834;
    int            field_838;
    int            field_83C;
    int            field_840;
    char           pad844[0x34];
    SVECTOR        field_878;
    char           pad880[0x50];
    int            field_8D0;
    int            field_8D4;
    int            field_8D8;
    int            field_8DC;
    int            field_8E0;
    int            field_8E4;
    int            field_8E8;
    int            field_8EC;
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
    int            field_924;
    HZD_SEG        field_928;
    int            field_938;
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
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

extern SVECTOR          DG_ZeroVector_800AB39C;
extern int              GV_Time_800AB330;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern int              amissile_alive_8009F490;
extern SVECTOR          svector_8009F478;
extern SVECTOR          svector_8009F494;
extern int              dword_8009F46C[];
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              GM_AlertMode_800ABA00;

void    AN_Breath_800C3AA8(MATRIX *matrix);
void    AN_Unknown_800CA1EC(MATRIX *world, int index);
GV_ACT *NewFadeIo_800C4224(int name, int where);

int Valcan_800D8D20(CONTROL *control, SVECTOR *svec1)
{
    SVECTOR svec2;

    GV_SubVec3_80016D40(svec1, &control->mov, &svec2);
    return ratan2(svec2.vx, svec2.vz) & 0xFFF;
}

void ValcanQueueDynamicSegment_800D8D5C(ValcanWork *work, int flag)
{
    HZD_QueueDynamicSegment2_8006FDDC(Map_FromId_800314C0(work->field_20)->hzd, &work->field_928, flag);
}

void ValcanDequeueDynamicSegment_800D8DA0(ValcanWork *work)
{
    HZD_DequeueDynamicSegment2_8006FE44(Map_FromId_800314C0(work->field_20)->hzd, &work->field_928);
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

    DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
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

    t_u0 = tex->off_x;
    t_u1 = t_u0 + tex->w;

    t_v0 = tex->off_y;
    t_v2 = t_v0 + tex->h;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->tpage;
    prims->clut = tex->clut;
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
        control = &work->control;
        GM_CurrentMap_800AB9B0 = work->field_20;
        Valcan_800D9B5C(work);
        s15c_valcan_800D8ECC(work);
        if (work->field_81C == 0)
        {
            GM_ActControl_80025A7C(control);
            GM_ActObject2_80034B88(&work->field_A0);
            GM_MoveTarget_8002D500(work->field_664, &control->mov);
            GM_MoveTarget_8002D500(work->field_668, &control->mov);
            GM_PushTarget_8002DA14(work->field_668);
            if (GM_CurrentItemId == ITEM_THERM_G)
            {
                DG_AmbientObjs(work->field_A0.objs);
            }
            else
            {
                DG_UnAmbientObjs(work->field_A0.objs);
            }
            DG_GetLightMatrix2_8001A5D8(&control->mov, work->field_624);
        }
    }
    s15c_dword_800E3474 = work->control.mov;
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
    if (GV_DiffDirAbs_8001706C(work->control.rot.vy,
                               Valcan_800D8D20(&work->control, &GM_PlayerPosition_800ABA10)) < 1024)
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

    control = &work->control;
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

        work->control.mov.vx = work->field_6F8[work->field_738][work->field_73A][0];
        work->control.mov.vy = 0;
        work->control.mov.vz = work->field_6F8[work->field_738][work->field_73A][1];

        option = (unsigned char *)GCL_GetOption_80020968('q');
        if (option)
        {
            ValcanGetInts_800D8E88(option, args);
        }

        work->field_73C = args[0];
        work->field_73E = args[1];

        work->field_6C4 = work->control.mov;
        work->field_6CC = work->control.rot;

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

        Valcan_800D9028(&prim->packs[0]->poly_ft4, tex);
        Valcan_800D9028(&prim->packs[1]->poly_ft4, tex);

        setRGB0(&prim->packs[0]->poly_ft4, 150, 150, 150);
        setRGB0(&prim->packs[1]->poly_ft4, 150, 150, 150);

        work->field_878 = GM_PlayerPosition_800ABA10;

        NewFadeIo_800C4224(1, 20);
    }

    ValcanQueueDynamicSegment_800D8D5C(work, 0xDF);
    return 0;
}

void ValcanDie_800D96E8(ValcanWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->control);
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

    control = &work->control;
    control->height = work->field_A0.field_18;
    control->field_36 = GV_NearExp2_80026384(control->field_36, 450);

    if (work->field_66C < 0 && control->field_57 != 0)
    {
        work->field_66C = 0;
    }
    work->field_66C -= 16;

    control->step.vy = work->field_66C;
}

void Valcan_800DD578(ValcanWork *work);

void Valcan_800D9B3C(ValcanWork *work)
{
    Valcan_800DD578(work);
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

    DG_GetLightMatrix2_8001A5D8(&work->control.mov, work->field_624);

    switch (work->field_91C)
    {
    case 1:
        work->field_6B4 = 0;
        work->field_91C = 2;
        work->field_918 = 0;
        GM_Sound_800329C4(&work->field_910, 180, 1);

    case 2:
        work->field_918++;
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
    RADAR_CONE *cone;

    work->control.radar_cone.dir = work->control.rot.vy + work->field_5A4[6].vy;

    cone = &work->control.radar_cone;
    cone->len = work->field_944;
    cone->ang = work->field_948;
    cone->_pad = 0;
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
    if (dword_8009F46C[0] == 1)
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
        if (work->control.mov.vx >= work->field_6F8[sp0[0]][0][0] + sp0[4])
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
        if (work->control.mov.vz >= work->field_6F8[0][sp0[1]][1] + sp0[5])
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

    Valcan_800D9EBC(&work->control.mov, &GM_PlayerPosition_800ABA10, &svec);
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &svec);
    ReadRotMatrix(&rotmat);
    NewBulletEx_80076708(2048, &rotmat, 2, 0, 0, 30, 90, 30000, 100);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DA2A8.s")

int Valcan_800DA558(ValcanWork *work, int arg1)
{
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    int     diffdir;
    int     var_s0;
    int     flag;

    svec1.vx = work->field_A0.objs->objs[4].world.t[0];
    svec1.vy = work->field_A0.objs->objs[4].world.t[1];
    svec1.vz = work->field_A0.objs->objs[4].world.t[2];

    Valcan_800D9EBC(&svec1, &work->field_51C, &svec2);
    diffdir =
        GV_DiffDirAbs_8001706C(svec2.vy, work->control.rot.vy + work->field_5A4[1].vy + work->field_5A4[6].vy);
    if (arg1 != 0)
    {
        svec3.vx = -800;
        svec3.vy = 0;
        svec3.vz = 0;
        DG_SetPos2_8001BC8C(&svec1, &svec2);
        DG_PutVector_8001BE48(&svec3, &svec1, 1);
    }

    flag = 0;
    var_s0 = 0;
    if (dword_8009F46C[0] == 1 || amissile_alive_8009F490 == 1)
    {
        if (sub_80028454(work->control.map->hzd, &svec1, &work->field_51C, 12, 2) == 0)
        {
            if (sub_80028454(work->control.map->hzd, &svec1, &GM_PlayerPosition_800ABA10, 12, 2) == 0)
            {
                var_s0 = Valcan_800D9DC0(work, 1);
                if (var_s0 < work->field_68C)
                {
                    work->field_51C = GM_PlayerPosition_800ABA10;
                    flag = 1;
                }
            }
            if (work->field_93C != 0 && amissile_alive_8009F490 == 1)
            {
                work->field_838 = amissile_alive_8009F490;
                return 1;
            }
        }
        else if (sub_80028454(work->control.map->hzd, &svec1, &GM_PlayerPosition_800ABA10, 12, 2) ==
                 0)
        {
            var_s0 = Valcan_800D9DC0(work, 1);
            flag = 1;
            work->field_51C = GM_PlayerPosition_800ABA10;
        }
        else
        {
            work->field_788 = 0;
            return 0;
        }
    }
    else if (sub_80028454(work->control.map->hzd, &svec1, &GM_PlayerPosition_800ABA10, 12, 2) != 0)
    {
        work->field_788 = 0;
        return 0;
    }
    else
    {
        var_s0 = Valcan_800D9DC0(work, 1);
        flag = 1;
    }

    if (!flag)
    {
        if (diffdir > 512)
        {
            return work->field_68C < 3500;
        }

        work->field_7A4 = svec2;

        if (dword_8009F46C[0] == 1 && work->field_950 < 0)
        {
            work->field_82C = dword_8009F46C[0];
        }
        else if (amissile_alive_8009F490 == 1)
        {
            work->field_838 = 1;
        }
        else
        {
            work->field_93C = 0;
        }
        return 1;
    }
    else if (var_s0 < 3000)
    {
        if (diffdir < 256)
        {
            if (!(GM_PlayerStatus_800ABA50 & (PLAYER_INVULNERABLE | PLAYER_UNK100 | PLAYER_UNK80)))
            {
                GM_SeSet2_80032968(0, 0x7F, 0x25);
                Valcan_800DA21C(work);
            }
        }
        return 1;
    }
    else if (diffdir > 512)
    {
        if (work->field_68C < 4000 || work->field_924 > 0)
        {
            return 1;
        }

        return 0;
    }
    else
    {
        work->field_7A4 = svec2;
        work->field_93C = 0;
    }
    return 1;
}

void Valcan_800DA8E4(ValcanWork *work)
{
    SVECTOR  svecs[2];
    CONTROL *control;

    control = &work->control;

    svecs[0].vx = GV_RandU_80017090(512);
    svecs[0].vy = GV_RandU_80017090(512) + 256;
    svecs[0].vz = 500;
    svecs[1].vx = GV_RandU_80017090(256);
    svecs[1].vy = GV_RandU_80017090(256);
    svecs[1].vz = 200;

    DG_SetPos2_8001BC8C(&control->mov, &control->rot);
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
        work->control.mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx < work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 1:
        Valcan_800DA044(work);
        work->control.mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx > work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 2:
        Valcan_800DA044(work);
        work->control.mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
        if (work->field_6C4.vz < work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    case 3:
        Valcan_800DA044(work);
        work->control.mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
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

int Valcan_800DB2E4(ValcanWork *work)
{
    short diffs[2];
    int   flag;
    Valcan_800DA044(work);

    if (work->field_7DC[work->field_6A0][0] == work->field_7A0 &&
        work->field_7DC[work->field_6A0][1] == work->field_7A2)
    {
        if (++work->field_6A0 >= 21)
        {
            work->field_6A0 = 0;
        }
    }

    diffs[0] = work->field_7DC[work->field_6A0][0] - work->field_7A0;
    diffs[1] = work->field_7DC[work->field_6A0][1] - work->field_7A2;

    flag = 0;

    if (diffs[0] > 0)
    {
        if (work->field_740 >= 2 && work->field_740 <= 3)
        {
            flag = Valcan_800DA1AC(work->field_740, 1);
        }
        else if (work->field_740 == 0)
        {
            flag = 1;
        }
    }
    else if (diffs[0] < 0)
    {
        if (work->field_740 < 2 || work->field_740 > 3)
        {
            if (work->field_740 == 1)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 0);
        }
    }
    else if (diffs[1] > 0)
    {
        if (work->field_740 < 0 || work->field_740 > 1)
        {
            if (work->field_740 == 2)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 3);
        }
    }
    else if (diffs[1] < 0)
    {
        if (work->field_740 >= 0 && work->field_740 <= 1)
        {
            flag = Valcan_800DA1AC(work->field_740, 2);
        }
        else if (work->field_740 == 3)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        Valcan_800D9F3C(work, 16);
    }

    return flag;
}

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
        return Valcan_800DB2E4(work);
    default:
        return 0;
    }
}

void Valcan_800DB500(ValcanWork *work)
{
    work->field_738 = work->field_73C;
    work->field_73A = work->field_73E;

    // We love switches!!!
    switch (work->field_770)
    {
    case 3:
    case 0:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73E = 1;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    case 1:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 0;
                if (--work->field_73E < 0)
                {
                    work->field_73E = 1;
                }
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 3;
                if (--work->field_73E < 0)
                {
                    work->field_73C = 2;
                    work->field_73E = 0;
                }
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73C--;
                work->field_73E = 0;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 1;
                }
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73C--;
                work->field_73E = 3;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 2;
                }
            }
            break;
        }
        break;
    case 2:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_768 = 3;

                work->field_73C = 0;
                work->field_73E = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_768 = 1;
                work->field_73C = 1;
                work->field_73E = 0;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    }
}

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

    work->control.mov.vx = work->field_7AC.vx;
    work->control.mov.vz = work->field_7AC.vz;

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

    work->control.turn.vy = vy;
    work->control.turn.vx = 0;
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

void Valcan_800DC124(ValcanWork *work)
{
    if (work->field_94C >= 30 && Valcan_800DA558(work, 1) && (work->field_940 >= 0x1E || work->field_68C < 0x1F41))
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 0;
        work->field_7B4 = work->control.turn.vy;
        work->field_778 = work->field_684;
        work->field_77C = work->field_688;

        if (work->field_6C0 > 150)
        {
            work->field_6C0 = 0;
            work->field_940 = 0;
            GM_SeSet2_80032968(0, 0x3F, 0x53);
            AN_Unknown_800CA1EC(&work->field_A0.objs->objs[6].world, 0);
            if (work->field_8E4++ >= 2)
            {
                work->field_8E4 = 0;
                switch (work->field_770)
                {
                case 1:
                    GM_Sound_800329C4(&work->field_910, 0x80, 1);
                    break;
                case 2:
                    GM_Sound_800329C4(&work->field_910, 0x81, 1);
                    break;
                case 3:
                    GM_Sound_800329C4(&work->field_910, 0x89, 1);
                    break;
                }
            }
        }

        work->field_684 = 1;
        work->field_688 = 12;
    }
}

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

#define ABS(x) (((x) >= 0) ? (x) : -(x))

static inline int Valcan_800DCC84_helper(int a)
{
    return (a & 0xFFF) + 0x1000;
}

void Valcan_800DCC84(ValcanWork *work)
{
    int temp_a0;
    int temp_v0;

    if (work->field_794 == 1)
    {
        work->control.radar_atr |= RADAR_UNK4;
        Valcan_800DBF74(work);
    }
    else if (work->field_698 == 0)
    {
        work->field_698 = GV_RandU_80017090(4) + 26;
    }

    if (work->field_698 > 0)
    {
        work->field_698--;
        work->control.turn.vy += GV_RandS_800170BC(8);
        if (work->field_794 == 1)
        {
            work->field_698 = 0;
        }
    }
    if (work->field_940 > 120)
    {
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_744[work->field_768]);
        }
        else
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_7B4);
        }

        if (ABS(temp_a0 - temp_v0) < 256 || work->field_940 > 600)
        {
            work->field_940 = 0;
            work->field_6C0 = 0;
            work->field_698 = 1;
        }
    }
    if (work->field_698 == 1)
    {
        work->control.radar_atr &= ~RADAR_UNK4;
        Valcan_800D9F3C(work, 16);
        work->field_788 = 0;
        work->field_6B0 = 0;
        work->field_684 = work->field_778;
        work->field_688 = work->field_77C;
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            work->control.turn.vy = work->field_744[work->field_768];
            if (work->field_770 == 2)
            {
                work->field_774 = work->field_770;
            }
        }
        else
        {
            work->control.turn.vy = work->field_7B4;
        }
        work->field_6A4 = 0;
    }
}

void Valcan_800DCE60(ValcanWork *work)
{
    if (work->field_698 == 0)
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 35;
        GM_SeSet2_80032968(0, 0x3F, 0x8A);
        if (GV_RandU_80017090(2) == 0)
        {
            work->field_688 = 27;
        }
        else
        {
            work->field_688 = 29;
        }
    }
    if (work->field_698 > 0)
    {
        work->field_698--;
        if (work->field_698 >= 16 && !(work->field_698 & 1))
        {
            Valcan_800DC06C(work, GV_RandU_80017090(8), 2);
        }
        if (work->field_698 == 1)
        {
            work->field_684 = work->field_780;
            work->field_688 = work->field_784;
            Valcan_800D9F3C(work, 16);
            work->field_6B0 = 0;
            work->field_6A4 = 0;
            work->field_788 = 0;
            if (work->field_770 >= 2 && work->field_770 <= 3)
            {
                work->control.turn.vy = work->field_744[work->field_768];
                if (work->field_770 == 2)
                {
                    work->field_774 = 2;
                }
            }
        }
    }
}

void Valcan_800DCF8C(ValcanWork *work)
{
    work->field_798 = work->field_794;
    work->field_794 = Valcan_800DA558(work, 0);
    switch (work->field_684)
    {
    case 0:
        work->field_8F0 = 0;
        s15c_crow_800DC7A0(work);
        Valcan_800DA140(work);
        break;
    case 1:
        work->field_8F0 = 1;
        Valcan_800DCC84(work);
        break;
    case 3:
        work->field_8F0 = 0;
        Valcan_800DCE60(work);
        break;
    }
    s15c_crow_800DC318(work);
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DD03C.s")
void s15c_crow_800DD03C(ValcanWork *work);

void Valcan_800DD578(ValcanWork *work)
{
    work->field_69C = 0;
    work->field_6A0 = 0;
    work->field_690 = 0;
    work->field_698 = 0;
    work->field_6A4 = 0;
    work->field_694 = 0;
    work->field_6B8 = 0;
    work->field_6B0 = 0;
    work->field_670 = 9;
    GM_ConfigMotionAdjust_80035008(&work->field_A0, work->field_5A4);
    Valcan_800D9F3C(work, 16);
    Valcan_800DC2EC(work, 0);
    work->field_758 = 0;
    work->field_744[0] = 3072;
    work->field_744[1] = 1024;
    work->field_744[2] = 2048;
    work->field_744[3] = 0;
    Valcan_800DB868(work);
    work->field_768 = work->field_740;
    work->control.rot.vx = 0;
    work->control.rot.vy = work->field_744[work->field_740];
    work->control.rot.vz = 0;
    work->control.turn.vx = 0;
    work->control.turn.vy = work->field_744[work->field_740];
    work->control.turn.vz = 0;
    work->field_76C = 2800;
    work->field_774 = 0;
    work->field_778 = 0;
    work->field_77C = 0;
    work->field_770 = 0;
    work->field_788 = 0;
    work->field_78C = 0;
    work->field_790 = 0;
    work->field_794 = 0;
    work->field_798 = 0;
    work->field_81C = 0;
    work->field_828 = 0;
    work->field_830 = 0;
    work->field_834 = 0;
    work->field_83C = 0;
    work->field_840 = 0;
    work->field_8F0 = 0;
    work->field_90C = 0;
    work->field_918 = 0;
    work->field_91C = 0;
    work->field_920 = 0;
    work->field_924 = -1;
    work->field_6B4 = 0;
    work->field_6BC = 0;
    work->field_6C0 = 1000;
    work->field_93C = 0;
    work->field_940 = 0;
    work->field_8DC = 0;
    work->field_8E4 = 0;
    work->field_8E8 = 0;
    work->field_8E0 = GV_RandU_80017090(16) + 40;
    work->field_8EC = mts_get_tick_count_8008BBB0();
    work->field_6BC = mts_get_tick_count_8008BBB0();
    work->field_94C = 0;
    work->field_7DC[0][0] = 0;
    work->field_7DC[0][1] = 3;
    work->field_7DC[1][0] = 1;
    work->field_7DC[1][1] = 1;
    work->field_7DC[2][0] = 2;
    work->field_7DC[2][1] = 2;
    work->field_7DC[3][0] = 3;
    work->field_7DC[3][1] = 3;
    work->field_7DC[4][0] = 1;
    work->field_7DC[4][1] = 1;
    work->field_7DC[5][0] = 0;
    work->field_7DC[5][1] = 0;
    work->field_7DC[6][0] = 2;
    work->field_7DC[6][1] = 2;
    work->field_7DC[7][0] = 3;
    work->field_7DC[7][1] = 0;
    work->field_7DC[8][0] = 2;
    work->field_7DC[8][1] = 2;
    work->field_7DC[9][0] = 3;
    work->field_7DC[9][1] = 3;
    work->field_7DC[10][0] = 1;
    work->field_7DC[10][1] = 1;
    work->field_7DC[11][0] = 2;
    work->field_7DC[11][1] = 0;
    work->field_7DC[12][0] = 0;
    work->field_7DC[12][1] = 3;
    work->field_7DC[13][0] = 3;
    work->field_7DC[13][1] = 0;
    work->field_7DC[14][0] = 0;
    work->field_7DC[14][1] = 1;
    work->field_7DC[15][0] = 2;
    work->field_7DC[15][1] = 2;
    work->field_7DC[16][0] = 1;
    work->field_7DC[16][1] = 1;
    work->field_7DC[17][0] = 0;
    work->field_7DC[17][1] = 3;
    work->field_7DC[18][0] = 3;
    work->field_7DC[18][1] = 2;
    work->field_7DC[19][0] = 1;
    work->field_7DC[19][1] = 3;
    work->field_7DC[20][0] = 3;
    work->field_7DC[20][1] = 0;
    work->field_684 = 0;
    work->field_688 = 0;
    work->field_944 = 15000;
    work->field_948 = 1024;
    Valcan_800D9D90(work);
    GM_AlertMode_800ABA00 = 4;
}
