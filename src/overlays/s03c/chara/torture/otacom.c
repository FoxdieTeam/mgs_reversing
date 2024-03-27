#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/sna_hzd.h"

typedef struct OtacomWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    OAR_RECORD     oar1[17];
    OAR_RECORD     oar2[17];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    GV_ACT        *field_7D8;
    GV_ACT        *field_7DC;
    int            field_7E0;
    SnaAutoMove    field_7E4;
    int            field_804;
    int            field_808;
    int            field_80C;
    int            field_810[3];
    int            field_81C[3];
} OtacomWork;

#define EXEC_LEVEL 5

const char s03c_aOtacom_800D7A90[] = "otacom";
const char s03c_aDrgomon_800D7A98[] = "dr_gomon";
const char s03c_aOn_800D7AA4[] = "on";
const char s03c_aDrlampon_800D7AA8[] = "dr_lamp_on";
const char s03c_aDrlampoff_800D7AB4[] = "dr_lamp_off";
const char s03c_dword_800D7AC0[] = {0xc6, 0xfe, 0xa4, 0xeb};
const char s03c_dword_800D7AC4[] = {0x0, 0x0, 0x0, 0x0};
const char s03c_dword_800D7AC8[] = {0xbd, 0xd0, 0xa4, 0xeb};
const char s03c_dword_800D7ACC[] = {0x0, 0x0, 0x0, 0x0};
const int  s03c_dword_800D7AD0 = 0x800CB4EC;
const int  s03c_dword_800D7AD4 = 0x800CB59C;
const int  s03c_dword_800D7AD8 = 0x800CB624;
const int  s03c_dword_800D7ADC = 0x800CB69C;
const int  s03c_dword_800D7AE0 = 0x800CB75C;

int s03c_dword_800C33D8 = 0;

extern SVECTOR DG_ZeroVector_800AB39C;

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_otacom_800CB494.s")
void s03c_otacom_800CB494(OtacomWork *work, int);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_otacom_800CB838.s")
void s03c_otacom_800CB838(OtacomWork *work, int);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_otacom_800CBB20.s")
void s03c_otacom_800CBB20(OtacomWork *work);

void OtacomAct_800CBB8C(OtacomWork *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      field_80C;

    object = &work->object;
    GM_ActMotion_80034A7C(object);

    control = &work->control;
    GM_ActControl_80025A7C(control);

    GM_ActObject_80034AF4(object);
    DG_GetLightMatrix_8001A3C4(&control->field_0_mov, work->light);

    work->control.field_32_height = work->object.field_18;

    field_80C = work->field_80C++;
    switch (work->field_804)
    {
    case 0:
        s03c_otacom_800CB494(work, field_80C);
        break;
    case 1:
        s03c_otacom_800CB838(work, field_80C);
        break;
    }

    s03c_otacom_800CBB20(work);
    sna_act_helper2_helper2_80033054(GV_StrCode_80016CCC("オタコン"), &work->adjust[6]); // オタコン = Otacon
}

void OtacomDie_800CBC50(OtacomWork *work)
{
    if (work->field_7D8)
    {
        GV_DestroyOtherActor_800151D8(work->field_7D8);
    }

    if (work->field_7DC)
    {
        GV_DestroyActorQuick_80015164(work->field_7DC);
    }

    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);

    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_14;
}

void Otacom_800CBCC4(OtacomWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('v'))
    {
        return;
    }

    i = 0;
    out = work->field_810;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 3)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

void Otacom_800CBD3C(OtacomWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('r'))
    {
        return;
    }

    i = 0;
    out = work->field_81C;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 3)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

int OtacomGetResources_800CBDB4(OtacomWork *work, int arg1, int arg2)
{
    SVECTOR  svec;
    CONTROL *control;
    int      model;
    int      motion;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(control, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(control, 1000, -1, -1);

    if (GCL_GetOption_80020968('m'))
    {
        model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        model = GV_StrCode_80016CCC(s03c_aOtacom_800D7A90);
    }

    if (GCL_GetOption_80020968('o'))
    {
        motion = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        motion = GV_StrCode_80016CCC("ota_03c");
    }

    GM_InitObject_80034A18(&work->object, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint_80034CB4(&work->object);
    GM_ConfigMotionControl_80034F08(&work->object, &work->motion, motion & 0xFFFF, work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight_80034C44(&work->object, work->light);
    GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 0);

    if (GCL_GetOption_80020968('b'))
    {
        work->field_7E0 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_7E0 = -1;
    }

    Otacom_800CBCC4(work);
    Otacom_800CBD3C(work);

    sub_80060548(&work->field_7E4, work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov);

    if (GCL_GetOption_80020968('a'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &svec);
    }
    else
    {
        svec = DG_ZeroVector_800AB39C;
    }

    sna_act_unk_helper2_helper2_800605DC(&work->field_7E4, work->control.field_2C_map->field_8_hzd, &svec);

    work->field_80C = 0;

    if (GCL_GetOption_80020968('c'))
    {
        work->field_804 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_804 = 0;
    }

    if (work->field_804)
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29 | GAME_FLAG_BIT_14;
    }

    work->field_7D8 = 0;
    s03c_dword_800C33D8 = 0;
    GM_ConfigMotionAdjust_80035008(&work->object, work->adjust);

    return 0;
}

GV_ACT *NewOtacom_800CC030(int arg0, int arg1)
{
    OtacomWork *work;

    work = (OtacomWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(OtacomWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)OtacomAct_800CBB8C, (TActorFunction)OtacomDie_800CBC50,
                              "otacom.c");
    if (OtacomGetResources_800CBDB4(work, arg0, arg1) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }
    return &work->actor;
}
