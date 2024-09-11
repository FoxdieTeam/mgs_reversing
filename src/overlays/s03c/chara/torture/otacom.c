#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/sna_hzd.h"
#include "chara/snake/shadow.h"
#include "Equip/kogaku2.h"
#include "SD/g_sound.h"

typedef struct OtacomWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    MOTION_SEGMENT oar1[17];
    MOTION_SEGMENT oar2[17];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    GV_ACT        *shadow;
    GV_ACT        *kogaku;
    int            bound_where;
    SnaAutoMove    field_7E4;
    int            field_804;
    int            mode;
    int            timer;
    int            field_810[3];
    int            procs[3];
} OtacomWork;

#define EXEC_LEVEL 5

int s03c_dword_800C33D8 = 0;

extern SVECTOR  DG_ZeroVector_800AB39C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern CONTROL *GM_PlayerControl_800AB9F4;

void s03b_boxall_800C9404(void);
int  s03b_boxall_800C93AC(int arg0);
int  s03b_boxall_800C95EC(void);

GV_ACT *NewJohnny2_800CE368();

void OtacomSendMessage_800CB3E0(int address, int message)
{
    GV_MSG msg;

    msg.address = address;
    msg.message[0] = message;
    msg.message[1] = GV_StrCode("otacom");
    msg.message_len = 2;
    GV_SendMessage(&msg);
}

void OtacomSendLampOnOffToGomon_800CB420(int on)
{
    GV_MSG msg;

    msg.address = GV_StrCode("dr_gomon");

    msg.message[0] = GV_StrCode("on");
    if (on)
    {
        msg.message[1] = GV_StrCode("dr_lamp_on");
    }
    else
    {
        msg.message[1] = GV_StrCode("dr_lamp_off");
    }

    msg.message_len = 2;

    GV_SendMessage(&msg);
}

void Otacom_800CB494(OtacomWork *work, int timer)
{
    SVECTOR svec1;
    SVECTOR indices;
    SVECTOR svec2;
    SVECTOR svec3;
    SVECTOR svec4;

    CONTROL *control;
    OBJECT  *object;

    control = &work->control;
    object = &work->object;

    switch (work->mode)
    {
    case 0:
        if (timer == 0)
        {
            work->kogaku = NewKogaku2_800615FC(control, object, 0);

            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction(&work->object, 1, 0, 0);
            }

            OtacomSendMessage_800CB3E0(work->bound_where, GV_StrCode("入る")); // 入る = enter (HASH_ENTER)
            OtacomSendLampOnOffToGomon_800CB420(1);
        }

        if (timer == 64)
        {
            OtacomSendMessage_800CB3E0(work->bound_where, GV_StrCode("出る")); // 出る = leave (HASH_LEAVE)
            OtacomSendLampOnOffToGomon_800CB420(0);

            if (work->object.action_flag != 0)
            {
                GM_ConfigObjectAction(&work->object, 0, 0, 4);
            }

            work->timer = 0;
            work->mode++;
        }
        break;

    case 1:
        work->field_7E4.field_0_ivec.vx = HZD_GetAddress_8005C6C4(
            work->control.map->hzd, &work->control.mov, work->field_7E4.field_0_ivec.vx);
        sna_unk_helper2_helper_8006070C(&work->field_7E4, &work->control);

        if (sna_act_unk_helper2_helper3_80060684(&work->field_7E4, &work->control.mov) < 250)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction(&work->object, 1, 0, 4);
            }

            work->control.turn.vy = -1024;
            s03b_boxall_800C93AC(work->field_810[0]);

            work->timer = 0;
            work->mode++;
        }
        break;

    case 2:
        s03b_boxall_800C9404();

        if (s03b_boxall_800C95EC() != 0)
        {
            GV_SubVec3(&work->control.mov, &GM_PlayerPosition_800ABA10, &svec4);
            GM_PlayerControl_800AB9F4->turn.vy = GV_VecDir2(&svec4);

            GCL_ExecProc(work->procs[1], NULL);

            GM_GameStatus_800AB3CC |= STATE_PADRELEASE;

            work->timer = 0;
            work->mode++;
        }
        break;

    case 3:
        if (timer == 16)
        {
            if (work->kogaku)
            {
                GV_DestroyOtherActor(work->kogaku);
            }
            work->kogaku = NULL;

            GM_SeSetMode_800329C4(&work->control.mov, SE_NINJA_STEALTH, GM_SEMODE_BOMB);
            GM_ConfigControlAttribute(control, 1);

            indices.vx = 0;
            indices.vy = 6;
            indices.vz = 12;
            indices.pad = 15;
            work->shadow = NewShadow_800602CC(control, object, indices);
        }

        if (timer == 64)
        {
            GCL_ExecProc(work->procs[2], NULL);

            GM_GameStatus_800AB3CC &= ~STATE_PADRELEASE;

            work->timer = 0;
            work->mode++;
        }
        break;

    case 4:
        svec2 = work->control.mov;
        svec2.vy = 0;

        svec3 = GM_PlayerPosition_800ABA10;
        svec3.vy = 0;

        GV_SubVec3(&svec2, &svec3, &svec1);

        if (GV_VecLen3(&svec1) < 1500)
        {
            GV_SubVec3(&work->control.mov, &GM_PlayerPosition_800ABA10, &svec1);
            GM_PlayerControl_800AB9F4->turn.vy = GV_VecDir2(&svec1);

            GCL_ExecProc(work->procs[2], NULL);
            GCL_ExecProc(work->procs[0], NULL);

            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void Otacom_800CB838(OtacomWork *work, int timer)
{
    SVECTOR  indices;
    CONTROL *control;
    OBJECT  *object;

    control = &work->control;
    object = &work->object;

    switch (work->mode)
    {
    case 0:
        s03b_boxall_800C9404();
        if (timer == 0)
        {
            GM_ConfigControlAttribute(control, 1);

            indices.vx = 0;
            indices.vy = 6;
            indices.vz = 12;
            indices.pad = 15;
            work->shadow = NewShadow_800602CC(control, object, indices);

            GCL_ExecProc(work->procs[1], NULL);

            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction(object, 1, 0, 0);
            }

            s03b_boxall_800C93AC(work->field_810[1]);

            NewJohnny2_800CE368();
        }

        GM_GameStatus_800AB3CC |= STATE_PADRELEASE | STATE_RADIO_OFF;

        if (s03b_boxall_800C95EC())
        {
            GM_GameStatus_800AB3CC &= ~STATE_PADRELEASE;

            if (work->object.action_flag != 0)
            {
                GM_ConfigObjectAction(&work->object, 0, 0, 4);
            }

            work->timer = 0;
            work->mode++;
        }
        break;

    case 1:
        s03b_boxall_800C9404();

        if (timer == 32)
        {
            GCL_ExecProc(work->procs[2], NULL);
            s03b_boxall_800C93AC(work->field_810[2]);
        }

        if (timer == 96)
        {
            if (work->shadow)
            {
                GV_DestroyOtherActor(work->shadow);
            }
            work->shadow = NULL;

            work->kogaku = NewKogaku2_800615FC(control, object, 0);

            GM_ConfigControlAttribute(control, 0);
            GM_SeSetMode_800329C4(&control->mov, SE_NINJA_STEALTH, GM_SEMODE_BOMB);
        }

        work->field_7E4.field_0_ivec.vx = HZD_GetAddress_8005C6C4(
            work->control.map->hzd, &work->control.mov, work->field_7E4.field_0_ivec.vx);

        sna_unk_helper2_helper_8006070C(&work->field_7E4, &work->control);

        if (sna_act_unk_helper2_helper3_80060684(&work->field_7E4, &work->control.mov) < 250)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction(&work->object, 1, 0, 4);
            }

            work->timer = 0;
            work->mode++;
        }
        break;

    case 2:
        if (timer == 0)
        {
            DG_InvisibleObjs(work->object.objs);
            OtacomSendMessage_800CB3E0(work->bound_where, GV_StrCode("入る")); // 入る = enter (HASH_ENTER)
            OtacomSendLampOnOffToGomon_800CB420(1);
        }

        if (timer == 64)
        {
            OtacomSendMessage_800CB3E0(work->bound_where, GV_StrCode("出る")); // 出る = leave (HASH_LEAVE)
            OtacomSendLampOnOffToGomon_800CB420(0);
        }

        if (timer == 128)
        {
            s03c_dword_800C33D8 = 1;

            GCL_ExecProc(work->procs[0], NULL);
            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void Otacom_800CBB20(OtacomWork *work)
{
    int      footstepsFrame;
    CONTROL *control;

    if (work->object.action_flag == 0)
    {
        footstepsFrame = work->motion.field_04_info1.field_2_footstepsFrame;
        control = &work->control;
        if (footstepsFrame == 0)
        {
            GM_SeSetMode_800329C4(&control->mov, 0xA0, GM_SEMODE_BOMB);
        }
        if (footstepsFrame == 0xC)
        {
            GM_SeSetMode_800329C4(&control->mov, 0xA1, GM_SEMODE_BOMB);
        }
    }
}

void OtacomAct_800CBB8C(OtacomWork *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      timer;

    object = &work->object;
    GM_ActMotion(object);

    control = &work->control;
    GM_ActControl(control);

    GM_ActObject(object);
    DG_GetLightMatrix(&control->mov, work->light);

    work->control.height = work->object.field_18;

    timer = work->timer++;
    switch (work->field_804)
    {
    case 0:
        Otacom_800CB494(work, timer);
        break;
    case 1:
        Otacom_800CB838(work, timer);
        break;
    }

    Otacom_800CBB20(work);
    sna_act_helper2_helper2_80033054(GV_StrCode("オタコン"), &work->adjust[6]); // オタコン = Otacon
}

void OtacomDie_800CBC50(OtacomWork *work)
{
    if (work->shadow)
    {
        GV_DestroyOtherActor(work->shadow);
    }

    if (work->kogaku)
    {
        GV_DestroyActorQuick(work->kogaku);
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);

    GM_GameStatus_800AB3CC &= ~STATE_RADIO_OFF;
}

void Otacom_800CBCC4(OtacomWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('v'))
    {
        return;
    }

    i = 0;
    out = work->field_810;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 3)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

void Otacom_800CBD3C(OtacomWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('r'))
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 3)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
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
    if (GM_InitControl(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, 1000, -1, -1);

    if (GCL_GetOption('m'))
    {
        model = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        model = GV_StrCode("otacom");
    }

    if (GCL_GetOption('o'))
    {
        motion = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        motion = GV_StrCode("ota_03c");
    }

    GM_InitObject(&work->object, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint(&work->object);
    GM_ConfigMotionControl_80034F08(&work->object, &work->motion, motion & 0xFFFF, work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight(&work->object, work->light);
    GM_ConfigObjectAction(&work->object, 0, 0, 0);

    if (GCL_GetOption('b'))
    {
        work->bound_where = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->bound_where = -1;
    }

    Otacom_800CBCC4(work);
    Otacom_800CBD3C(work);

    sub_80060548(&work->field_7E4, work->control.map->hzd, &work->control.mov);

    if (GCL_GetOption('a'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &svec);
    }
    else
    {
        svec = DG_ZeroVector_800AB39C;
    }

    sna_act_unk_helper2_helper2_800605DC(&work->field_7E4, work->control.map->hzd, &svec);

    work->timer = 0;

    if (GCL_GetOption('c'))
    {
        work->field_804 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_804 = 0;
    }

    if (work->field_804)
    {
        GM_GameStatus_800AB3CC |= STATE_PADRELEASE | STATE_RADIO_OFF;
    }

    work->shadow = 0;
    s03c_dword_800C33D8 = 0;
    GM_ConfigMotionAdjust_80035008(&work->object, work->adjust);

    return 0;
}

GV_ACT *NewOtacom_800CC030(int arg0, int arg1)
{
    OtacomWork *work;

    work = (OtacomWork *)GV_NewActor(EXEC_LEVEL, sizeof(OtacomWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)OtacomAct_800CBB8C,
                     (TActorFunction)OtacomDie_800CBC50, "otacom.c");
    if (OtacomGetResources_800CBDB4(work, arg0, arg1) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }
    return &work->actor;
}
