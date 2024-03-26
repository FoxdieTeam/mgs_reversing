#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct NinjaWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    OAR_RECORD     oar1[17];
    OAR_RECORD     oar2[17];
    SVECTOR        rots[32];
    MATRIX         field_798[2];
    GV_ACT        *field_7D8;
    char           pad7DC[4];
    int            field_7E0;
    SVECTOR        field_7E4;
    char           pad7EC[8];
    int            field_7F4;
    int            field_7F8;
    int            field_7FC[2];
    int            field_804[4];
} NinjaWork;

#define EXEC_LEVEL 5

void NinjaSendMessage_800CC0BC(unsigned short address, unsigned short message1, unsigned short message2)
{
    GV_MSG msg;

    msg.address = address;
    msg.message_len = 2;
    msg.message[0] = message1;
    msg.message[1] = message2;
    GV_SendMessage_80016504(&msg);
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_ninja_800CC0F0.s")
int s03c_ninja_800CC0F0(NinjaWork *, int);

void NinjaAct_800CC68C(NinjaWork *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      field_7F8;

    object = &work->object;
    GM_ActMotion_80034A7C(object);

    control = &work->control;
    GM_ActControl_80025A7C(control);

    GM_ActObject_80034AF4(object);
    DG_GetLightMatrix_8001A3C4(&control->field_0_mov, work->field_798);

    work->control.field_32_height = work->object.field_18;

    field_7F8 = work->field_7F8;
    work->field_7F8++;
    s03c_ninja_800CC0F0(work, field_7F8);
}

void NinjaDie_800CC704(NinjaWork *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);

    if (work->field_7D8)
    {
        GV_DestroyOtherActor_800151D8(work->field_7D8);
    }
}

void Ninja_800CC74C(NinjaWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('v'))
    {
        return;
    }

    i = 0;
    out = work->field_7FC;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 2)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

void Ninja_800CC7C4(NinjaWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('r'))
    {
        return;
    }

    i = 0;
    out = work->field_804;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

int NinjaGetResources_800CC83C(NinjaWork *work, int scriptData, int scriptBinds)
{
    CONTROL *control;
    OBJECT  *object;
    int      model;
    int      motion;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, scriptData, scriptBinds) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(control, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));

    GM_ConfigControlHazard_8002622C(control, 1000, -1, -1);

    GCL_GetOption_80020968('m');
    model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

    GCL_GetOption_80020968('o');
    motion = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

    object = &work->object;
    GM_InitObject_80034A18(object, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint_80034CB4(object);
    GM_ConfigMotionControl_80034F08(object, &work->motion, motion & 0xFFFF, work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight_80034C44(object, work->field_798);
    GM_ConfigObjectAction_80034CD4(object, 0, 0, 0);

    GCL_GetOption_80020968('b');
    work->field_7E0 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

    Ninja_800CC74C(work);
    Ninja_800CC7C4(work);

    GCL_GetOption_80020968('a');
    GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->field_7E4);

    work->field_7F4 = 0;
    work->field_7F8 = 0;
    work->field_7D8 = NULL;

    return 0;
}

GV_ACT *NewNinja_800CC9B4(int scriptData, int scriptBinds)
{
    NinjaWork *work;

    work = (NinjaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(NinjaWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)NinjaAct_800CC68C, (TActorFunction)NinjaDie_800CC704,
                              "ninja.c");
    if (NinjaGetResources_800CC83C(work, scriptData, scriptBinds) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }
    return &work->actor;
}
