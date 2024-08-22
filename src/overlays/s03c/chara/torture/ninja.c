#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Equip/kogaku2.h"

typedef struct NinjaWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    MOTION_SEGMENT     oar1[17];
    MOTION_SEGMENT     oar2[17];
    SVECTOR        rots[32];
    MATRIX         light[2];
    GV_ACT        *unused_shadow; // a guess based on otacom.c
    GV_ACT        *kogaku;
    int            bound_where;
    SVECTOR        field_7E4;
    int            unused2;
    unsigned int   mode;
    int            unused3;
    int            timer;
    int            field_7FC[2];
    int            procs[4];
} NinjaWork;

#define EXEC_LEVEL 5

extern SVECTOR  GM_PlayerPosition_800ABA10;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  DG_ZeroVector_800AB39C;

GV_ACT *NewSpark2_800CA714(MATRIX *world);
void    AN_Unknown_800CCA40(SVECTOR *pos);
void    s03b_boxall_800C969C(int, int);
void    s03b_boxall_800C96E8(void);
int     s03b_boxall_800C93AC(int arg0);
void    s03b_boxall_800C9404(void);
int     s03b_boxall_800C95EC(void);

void NinjaSendMessage_800CC0BC(int address, int message1, int message2)
{
    GV_MSG msg;

    msg.address = address;
    msg.message_len = 2;
    msg.message[0] = message1;
    msg.message[1] = message2;
    GV_SendMessage_80016504(&msg);
}

void Ninja_800CC0F0(NinjaWork *work, int timer)
{
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    MATRIX  rot;

    GCL_ARGS args1;
    GCL_ARGS args2;
    long     argv1[1];
    long     argv2[1];

    CONTROL *control;
    OBJECT  *object;

    int len;

    control = &work->control;
    object = &work->object;

    switch (work->mode)
    {
    case 0:
        if (timer == 0)
        {
            args1.argc = 1;
            args1.argv = argv1;
            argv1[0] = 0;
            GCL_ExecProc_8001FF2C(work->procs[1], &args1);

            GV_SubVec3_80016D40(&work->control.mov, &GM_PlayerPosition_800ABA10, &svec3);
            GM_PlayerControl_800AB9F4->turn.vy = GV_VecDir2_80016EF8(&svec3);

            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29 | GAME_FLAG_BIT_24;

            work->kogaku = NewKogaku2_800615FC(control, object, 0);
        }
        if (timer == 32)
        {
            GM_SeSet_80032858(&work->field_7E4, 27);
            GM_Sound_80032C48(0x01ffff0b, 0);
            svec1 = DG_ZeroVector_800AB39C;
            svec1.vx = 1024;
            svec1.vy = -1024;
            svec2 = work->field_7E4;
            svec2.vy = 1500;
            DG_SetPos2_8001BC8C(&svec2, &svec1);
            ReadRotMatrix(&rot);
            NewSpark2_800CA714(&rot);
            svec2.vx -= 250;
            AN_Unknown_800CCA40(&svec2);
        }
        if (timer == 96)
        {
            NinjaSendMessage_800CC0BC(work->bound_where, GV_StrCode_80016CCC("入る"),
                                      GV_StrCode_80016CCC("ninja")); // 入る = enter (HASH_ENTER)
        }

        GV_SubVec3_80016D40(&work->field_7E4, &GM_PlayerPosition_800ABA10, &svec1);
        svec1.vy = 0;

        len = GV_VecLen3_80016D80(&svec1);

        if (timer == 128)
        {
            GM_Sound_80032C48(0x01000003, 0);
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
            GM_PlayerControl_800AB9F4->turn.vy = GV_VecDir2_80016EF8(&svec1);
            GCL_ExecProc_8001FF2C(work->procs[2], NULL);
        }
        if (timer > 128 && len < 1500)
        {
            GV_SubVec3_80016D40(&work->control.mov, &GM_PlayerPosition_800ABA10, &svec3);
            GM_PlayerControl_800AB9F4->turn.vy = GV_VecDir2_80016EF8(&svec3);
            s03b_boxall_800C969C(0, 30000);
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
            s03b_boxall_800C93AC(work->field_7FC[0]);
            args1.argc = 1;
            args1.argv = argv1;
            argv1[0] = 1;
            GCL_ExecProc_8001FF2C(work->procs[1], &args1);
            work->timer = 0;
            work->mode++;
        }
        break;
    case 1:
        s03b_boxall_800C9404();
        if (s03b_boxall_800C95EC())
        {
            work->timer = 0;
            work->mode++;
        }
        break;
    case 2:
        if (timer == 32)
        {
            GV_DestroyActor_800151C8(work->kogaku);
            GM_Sound_800329C4(&control->mov, 0x4E, 1);
        }
        if (timer == 36)
        {
            work->kogaku = NewKogaku2_800615FC(control, object, 0);
        }
        if (timer == 64)
        {
            work->timer = 0;
            work->mode++;
        }
        break;
    case 3:
        if (timer == 0)
        {
            GV_DestroyActor_800151C8(work->kogaku);
        }
        if (timer < 40)
        {
            if (timer & 1)
            {
                DG_InvisibleObjs(object->objs);
            }
            else
            {
                DG_VisibleObjs(object->objs);
            }
        }
        if (timer == 16)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction_80034CD4(&work->object, 1, 0, 4);
            }
        }
        if (timer == 32)
        {
            GM_Sound_800329C4(&control->mov, 0xC4, 1);
            GM_Sound_80032C48(0x01ffff0b, 0);
        }
        if (timer == 38)
        {
            work->kogaku = NewKogaku2_800615FC(control, object, 0);
            GM_Sound_800329C4(&control->mov, 0x4E, 1);
        }
        if (timer == 55)
        {
            DG_InvisibleObjs(object->objs);
        }
        if (object->is_end)
        {
            GV_DestroyOtherActor_800151D8(work->kogaku);
            work->timer = 0;
            work->mode++;
        }
        break;
    case 4:
        s03b_boxall_800C9404();
        if (timer == 0)
        {
            DG_InvisibleObjs(object->objs);
            s03b_boxall_800C93AC(work->field_7FC[1]);
        }
        if (s03b_boxall_800C95EC())
        {
            work->timer = 0;
            work->mode++;
            s03b_boxall_800C96E8();
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_24;
            GCL_ExecProc_8001FF2C(work->procs[2], NULL);
            GCL_ExecProc_8001FF2C(work->procs[0], NULL);
            args2.argc = 1;
            args2.argv = argv2;
            argv2[0] = 1;
            GCL_ExecProc_8001FF2C(work->procs[3], &args2);
            GM_Sound_80032C48(0x01000001, 0);
            GV_DestroyActor_800151C8(&work->actor);
        }
        break;
    case 5:
        if (timer == 16)
        {
            GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_24 | GAME_FLAG_BIT_29);
        }
        break;
    }
}

void NinjaAct_800CC68C(NinjaWork *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      timer;

    object = &work->object;
    GM_ActMotion_80034A7C(object);

    control = &work->control;
    GM_ActControl_80025A7C(control);

    GM_ActObject_80034AF4(object);
    DG_GetLightMatrix_8001A3C4(&control->mov, work->light);

    work->control.height = work->object.field_18;

    timer = work->timer;
    work->timer++;
    Ninja_800CC0F0(work, timer);
}

void NinjaDie_800CC704(NinjaWork *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);

    if (work->unused_shadow)
    {
        GV_DestroyOtherActor_800151D8(work->unused_shadow);
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
    out = work->procs;
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

    GM_ConfigControlString_800261C0(control, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));

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
    GM_ConfigObjectLight_80034C44(object, work->light);
    GM_ConfigObjectAction_80034CD4(object, 0, 0, 0);

    GCL_GetOption_80020968('b');
    work->bound_where = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

    Ninja_800CC74C(work);
    Ninja_800CC7C4(work);

    GCL_GetOption_80020968('a');
    GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->field_7E4);

    work->unused3 = 0;
    work->timer = 0;
    work->unused_shadow = NULL;

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
