#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "chara/snake/sna_init.h"

typedef struct RevolverWork
{
    GV_ACT         actor;
    CONTROL        field_20;
    OBJECT         field_9C;
    MOTION_CONTROL field_180;
    OAR_RECORD     field_1D0;
    char           pad_1F4[0x264];
    OAR_RECORD     field_458;
    char           pad_47C[0x264];
    SVECTOR        field_6E0;
    char           pad_6E8[0x80];
    SVECTOR        field_768;
    char           pad_770[0x30];
    SVECTOR        field_7A0;
    char           pad_7A8[0x48];
    MATRIX         field_7F0_light[2];
    ShadowWork    *field_830;
    int            field_834;
    SVECTOR        field_838;
    char           pad_840[0x78];
    SVECTOR       *field_8B8;
    int            field_8BC;
    SVECTOR        field_8C0;
    int            field_8C8;
    char           pad_8CC[0x74];
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    char           pad_950[8];
    int            field_958;
    int            field_95C;
    int            field_960;
    int            field_964;
    char           pad_968[0x3C];
    SVECTOR        field_9A4;
    SVECTOR        field_9AC;
    short          field_9B4;
    short          field_9B6;
} RevolverWork;

#define EXEC_LEVEL 5

extern char s03b_aRevolverc_800D302C[];
extern char s03b_dword_800D300C[];
extern char s03b_aRevbd_800D3018[];
extern char s03b_aRevvct_800D3020[];
extern char s03b_aEnd_800D2F24[];
extern char s03b_aChprogcam_800D2F68[];
extern char s03b_dword_800D2FB8[];

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GV_PadMask_800AB374;

GV_ACT *NewFadeIo_800C4224(int name, int where);

// Those functions are not actually in boxall, info
// those are some helper functions (not sure if part of revolver.c)
int  s03b_boxall_800C9328();
void s03b_info_800CA868();
int  s03b_boxall_800C95EC();
int  s03b_boxall_800C95FC();
void s03b_boxall_800C96E8();

void RevolverSendMessage_800C7170(int hash, short *message)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message_len = 2;
    msg.message[0] = message[1];
    msg.message[1] = message[2];

    GV_SendMessage_80016504(&msg);
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C71B0.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C71E8.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C72A4.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C7384.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C742C.s")
void s03b_revolver_800C742C(RevolverWork *work, int arg1, int arg2, int arg3);

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C7574.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C7958.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C7D04.s")

void Revolver_800C7E2C(RevolverWork *work, int arg1)
{
    work->field_20.field_0_mov = *work->field_8B8;
    if (work->field_948 & 0x200)
    {
        s03b_revolver_800C742C(work, arg1, -1, 0x80);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C7E88.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C81EC.s")
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C826C.s")

void Revolver_800C8488(RevolverWork *work, int mode)
{
    short message[3];
    int   field_9B4;

    if (mode == 0)
    {
        NewFadeIo_800C4224(0, 28);
        s03b_boxall_800C9328();
        s03b_boxall_800C96E8();
    }

    if (mode == 32)
    {
        message[1] = GV_StrCode_80016CCC(s03b_aEnd_800D2F24);
        message[2] = 0;
        RevolverSendMessage_800C7170(GV_StrCode_80016CCC(s03b_aChprogcam_800D2F68), message);

        message[1] = 4;
        message[2] = 0;
        RevolverSendMessage_800C7170(GV_StrCode_80016CCC(s03b_dword_800D2FB8), message);

        message[1] = 0x491D;
        message[2] = work->field_9B6;
        RevolverSendMessage_800C7170(work->field_20.field_30_scriptData, message);

        work->field_948 &= ~0x100;

        message[1] = 0x71F1;
        message[2] = 0;
        RevolverSendMessage_800C7170(0x62FE, message);

        work->field_20.field_0_mov = work->field_9A4;
        work->field_20.field_4C_turn = work->field_9AC;

        field_9B4 = work->field_9B4;
        if (work->field_9C.action_flag != field_9B4)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, work->field_9B4, 0, 4);
        }

        GM_GameStatus_800AB3CC = (GM_GameStatus_800AB3CC & ~GAME_FLAG_BIT_29) | GAME_FLAG_BIT_28;
        GV_PadMask_800AB374 = ~0x800;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C8600.s")
void s03b_revolver_800C8600(RevolverWork *);

int Revolver_800C8710(RevolverWork *work, int arg1)
{
    if (arg1 == 0 && work->field_9C.action_flag != 12)
    {
        GM_ConfigObjectAction_80034CD4(&work->field_9C, 12, 0, 4);
    }
    if (work->field_9C.is_end)
    {
        work->field_20.field_4C_turn.vy += 2048;
        work->field_20.field_8_rot.vy = work->field_20.field_4C_turn.vy;
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 0, 0, 0);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C8794(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_20.field_4C_turn.vy = 0;
        if (work->field_9C.action_flag != 8)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 8, 0, 4);
        }
    }

    GV_NearExp4V_800266D4(&work->field_20.field_0_mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 24)
    {
        GM_SeSet_80032858(&work->field_20.field_0_mov, 179);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C884C(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_20.field_4C_turn.vy = 0;
        if (work->field_9C.action_flag != 9)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 9, 0, 4);
        }
    }

    GV_NearExp4V_800266D4(&work->field_20.field_0_mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 10 || arg1 == 44)
    {
        GM_SeSet_80032858(&work->field_20.field_0_mov, 180);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C8910(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_20.field_4C_turn.vy = 0;
        if (work->field_9C.action_flag != 10)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 10, 0, 4);
        }
    }

    GV_NearExp4V_800266D4(&work->field_20.field_0_mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 32)
    {
        GM_SeSet_80032858(&work->field_20.field_0_mov, 180);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C89C8.s")
void s03b_revolver_800C89C8(RevolverWork *);

void Revolver_800C8B5C(RevolverWork *work)
{
    SVECTOR svec2, svec1;

    work->field_948 &= ~0x7;
    if (work->field_9C.is_end)
    {
        work->field_948 |= 4;
    }

    if ((work->field_948 & 0x10) && s03b_boxall_800C95EC())
    {
        work->field_948 = (work->field_948 | 0x2) & ~0x10;
    }

    if (s03b_boxall_800C95FC())
    {
        GM_ConfigMotionAdjust_80035008(&work->field_9C, &work->field_768);
        work->field_948 |= 0x10;
    }

    sna_act_helper2_helper2_80033054(GV_StrCode_80016CCC(s03b_dword_800D300C), &work->field_7A0);

    if (work->field_948 & 0x20)
    {
        svec1 = work->field_20.field_0_mov;
        svec1.vy = 0;
        GV_SubVec3_80016D40(work->field_8B8, &svec1, &svec2);
        work->field_20.field_4C_turn.vy = GV_VecDir2_80016EF8(&svec2);
        if (GV_VecLen3_80016D80(&svec2) < 0x80)
        {
            work->field_948 = (work->field_948 | 1) & ~0x20;
            if (work->field_9C.action_flag != 0)
            {
                GM_ConfigObjectAction_80034CD4(&work->field_9C, 0, 0, 4);
            }
        }
    }
}

void Revolver_800C8CA8(RevolverWork *work)
{
    s03b_info_800CA868();
    s03b_revolver_800C89C8(work);
    Revolver_800C8B5C(work);
    s03b_revolver_800C8600(work);
}

void RevolverAct_800C8CE4(RevolverWork *work)
{
    GM_ActMotion_80034A7C(&work->field_9C);
    GM_ActControl_80025A7C(&work->field_20);
    GM_ActObject_80034AF4(&work->field_9C);

    DG_GetLightMatrix_8001A3C4(&work->field_20.field_0_mov, work->field_7F0_light);

    work->field_20.field_32_height = work->field_9C.field_18;

    Revolver_800C8CA8(work);

    if (work->field_8C0.vy < 0 && work->field_20.field_57 != 0)
    {
        work->field_8C0.vy = 0;
    }
    work->field_8C0.vy -= 32;

    work->field_20.field_44_step.vy += work->field_8C0.vy;
}

void RevolverDie_800C8D8C(RevolverWork *work)
{
    GV_DestroyOtherActor_800151D8(&work->field_830->field_0_actor);
    GM_FreeControl_800260CC(&work->field_20);
    GM_FreeObject_80034BF8(&work->field_9C);
    s03b_boxall_800C9328();
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C8DD0.s")
int s03b_revolver_800C8DD0(HZD_PAT *route, int *, SVECTOR *);

int Revolver_800C8E34(RevolverWork *work)
{
    HZD_PAT *routes;
    int      route_idx;
    int      opt;

    opt = GCL_GetOption_80020968('r');
    route_idx = 0;
    if (opt)
    {
        route_idx = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    routes = work->field_20.field_2C_map->field_8_hzd->f00_header->routes;
    routes += route_idx; // Why?

    if (s03b_revolver_800C8DD0(routes, &work->field_834, &work->field_838) < 0)
    {
        return -1;
    }

    work->field_8B8 = &work->field_838;
    work->field_8BC = 0;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C8EC0.s")
void s03b_revolver_800C8EC0(RevolverWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_revolver_800C8F4C.s")
void s03b_revolver_800C8F4C(RevolverWork *work);

void Revolver_800C8FC4(RevolverWork *work)
{
    work->field_964 = 0;
    work->field_95C = 0;
    work->field_960 = 0;
}

int RevolverGetResources_800C8FD4(RevolverWork *work, int arg1, int arg2)
{
    SVECTOR  indices;
    OBJECT  *object;
    short    motion;
    CONTROL *control;

    if (GCL_GetOption_80020968('o'))
    {
        motion = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        motion = GV_StrCode_80016CCC(s03b_aRevbd_800D3018);
    }

    if (GCL_GetOption_80020968('m'))
    {
        GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        GV_StrCode_80016CCC(s03b_aRevvct_800D3020);
    }

    control = &work->field_20;

    if (GM_InitLoader_8002599C(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(control, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(control, control->field_0_mov.vy, -1, -1);
    control->field_59 = 2;
    GM_ConfigControlAttribute_8002623C(control, 1);

    object = &work->field_9C;

    GM_InitObject_80034A18(object, GV_StrCode_80016CCC(s03b_aRevvct_800D3020), BODY_FLAG2, motion);
    GM_ConfigObjectJoint_80034CB4(object);
    GM_ConfigMotionControl_80034F08(object, &work->field_180, motion, &work->field_1D0, &work->field_458, control,
                                    &work->field_6E0);
    GM_ConfigObjectLight_80034C44(object, work->field_7F0_light);
    GM_ConfigObjectAction_80034CD4(object, 0, 0, 0);

    if (Revolver_800C8E34(work) < 0)
    {
        return -1;
    }

    s03b_revolver_800C8EC0(work);
    s03b_revolver_800C8F4C(work);
    Revolver_800C8FC4(work);

    work->field_8C0 = DG_ZeroVector_800AB39C;
    work->field_944 = 0;
    work->field_948 = 0;
    work->field_94C = 0;
    work->field_958 = -1;

    if (GCL_GetOption_80020968('e') != 0)
    {
        work->field_8C8 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_8C8 = -1;
    }

    if (GCL_GetOption_80020968('c') != 0)
    {
        work->field_940 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_940 = 0;
    }

    if (GCL_GetOption_80020968('f') && GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4()))
    {
        work->field_948 |= 0x400;
    }

    indices.vx = 0;
    indices.vy = 7;
    indices.vz = 13;
    indices.pad = 16;

    work->field_830 = shadow_init_800602CC(control, object, indices);
    if (work->field_830 == NULL)
    {
        return -1;
    }

    return 0;
}

GV_ACT *NewRevolver_800C929C(int arg0, int arg1)
{
    RevolverWork *work;

    work = (RevolverWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(RevolverWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RevolverAct_800C8CE4, (TActorFunction)RevolverDie_800C8D8C,
                              s03b_aRevolverc_800D302C);
    if (RevolverGetResources_800C8FD4(work, arg0, arg1) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }

    return &work->actor;
}
