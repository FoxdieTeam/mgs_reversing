#include "ninja.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "equip/equip.h"
#include "sound/g_sound.h"

#include "takabe/spark2.h"      // for NewSpark2_800CA714

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[17];
    MOTION_SEGMENT m_segs2[17];
    SVECTOR        rots[32];
    MATRIX         light[2];
    GV_ACT        *shadow; // unused, a guess based on otacom.c
    GV_ACT        *kogaku;
    int            bound_where;
    SVECTOR        field_7E4;
    int            unused2;
    unsigned int   mode;
    int            unused3;
    int            timer;
    int            field_7FC[2];
    int            procs[4];
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void AN_Unknown_800CCA40(SVECTOR *pos);

void OpenCinemaScreen(int, int);
void CloseCinemaScreen(void);

int  s03b_boxall_800C93AC(int arg0);
void s03b_boxall_800C9404(void);
int  s03b_boxall_800C95EC(void);

static void SendMessage(int address, int message1, int message2)
{
    GV_MSG msg;

    msg.address = address;
    msg.message_len = 2;
    msg.message[0] = message1;
    msg.message[1] = message2;
    GV_SendMessage(&msg);
}

static void Update(Work *work, int timer)
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
    OBJECT  *body;

    int len;

    control = &work->control;
    body = &work->body;

    switch (work->mode)
    {
    case 0:
        if (timer == 0)
        {
            args1.argc = 1;
            args1.argv = argv1;
            argv1[0] = 0;
            GCL_ExecProc(work->procs[1], &args1);

            GV_SubVec3(&work->control.mov, &GM_PlayerPosition, &svec3);
            GM_PlayerControl->turn.vy = GV_VecDir2(&svec3);

            GM_GameStatus |= STATE_PADRELEASE | STATE_JAMMING;

            work->kogaku = NewKogaku2(control, body, 0);
        }
        if (timer == 32)
        {
            GM_SeSet(&work->field_7E4, SE_PSG1_SHOT);
            GM_SetSound(0x01ffff0b, SD_ASYNC);
            svec1 = DG_ZeroVector;
            svec1.vx = 1024;
            svec1.vy = -1024;
            svec2 = work->field_7E4;
            svec2.vy = 1500;
            DG_SetPos2(&svec2, &svec1);
            ReadRotMatrix(&rot);
            NewSpark2_800CA714(&rot);
            svec2.vx -= 250;
            AN_Unknown_800CCA40(&svec2);
        }
        if (timer == 96)
        {
            SendMessage(work->bound_where, GV_StrCode("入る") /* HASH_ENTER */, GV_StrCode("ninja"));
        }

        GV_SubVec3(&work->field_7E4, &GM_PlayerPosition, &svec1);
        svec1.vy = 0;

        len = GV_VecLen3(&svec1);

        if (timer == 128)
        {
            GM_SetSound(0x01000003, SD_ASYNC);
            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_PlayerControl->turn.vy = GV_VecDir2(&svec1);
            GCL_ExecProc(work->procs[2], NULL);
        }
        if (timer > 128 && len < 1500)
        {
            GV_SubVec3(&work->control.mov, &GM_PlayerPosition, &svec3);
            GM_PlayerControl->turn.vy = GV_VecDir2(&svec3);
            OpenCinemaScreen(0, 30000);
            GM_GameStatus |= STATE_PADRELEASE;
            s03b_boxall_800C93AC(work->field_7FC[0]);
            args1.argc = 1;
            args1.argv = argv1;
            argv1[0] = 1;
            GCL_ExecProc(work->procs[1], &args1);
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
            GV_DestroyActor(work->kogaku);
            GM_SeSetMode(&control->mov, SE_NINJA_STEALTH, GM_SEMODE_BOMB);
        }
        if (timer == 36)
        {
            work->kogaku = NewKogaku2(control, body, 0);
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
            GV_DestroyActor(work->kogaku);
        }
        if (timer < 40)
        {
            if (timer & 1)
            {
                DG_InvisibleObjs(body->objs);
            }
            else
            {
                DG_VisibleObjs(body->objs);
            }
        }
        if (timer == 16)
        {
            if (work->body.action != 1)
            {
                GM_ConfigObjectAction(&work->body, 1, 0, 4);
            }
        }
        if (timer == 32)
        {
            GM_SeSetMode(&control->mov, 196, GM_SEMODE_BOMB);
            GM_SetSound(0x01ffff0b, SD_ASYNC);
        }
        if (timer == 38)
        {
            work->kogaku = NewKogaku2(control, body, 0);
            GM_SeSetMode(&control->mov, SE_NINJA_STEALTH, GM_SEMODE_BOMB);
        }
        if (timer == 55)
        {
            DG_InvisibleObjs(body->objs);
        }
        if (body->is_end)
        {
            GV_DestroyOtherActor(work->kogaku);
            work->timer = 0;
            work->mode++;
        }
        break;
    case 4:
        s03b_boxall_800C9404();
        if (timer == 0)
        {
            DG_InvisibleObjs(body->objs);
            s03b_boxall_800C93AC(work->field_7FC[1]);
        }
        if (s03b_boxall_800C95EC())
        {
            work->timer = 0;
            work->mode++;
            CloseCinemaScreen();
            GM_GameStatus &= ~STATE_JAMMING;
            GCL_ExecProc(work->procs[2], NULL);
            GCL_ExecProc(work->procs[0], NULL);
            args2.argc = 1;
            args2.argv = argv2;
            argv2[0] = 1;
            GCL_ExecProc(work->procs[3], &args2);
            GM_SetSound(0x01000001, SD_ASYNC);
            GV_DestroyActor(&work->actor);
        }
        break;
    case 5:
        if (timer == 16)
        {
            GM_GameStatus &= ~(STATE_JAMMING | STATE_PADRELEASE);
        }
        break;
    }
}

static void Act(Work *work)
{
    CONTROL *control;
    OBJECT  *body;
    int      timer;

    body = &work->body;
    GM_ActMotion(body);

    control = &work->control;
    GM_ActControl(control);

    GM_ActObject(body);
    DG_GetLightMatrix(&control->mov, work->light);

    work->control.height = work->body.height;

    timer = work->timer;
    work->timer++;
    Update(work, timer);
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);

    if (work->shadow)
    {
        GV_DestroyOtherActor(work->shadow);
    }
}

static void InitSounds(Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('v'))
    {
        return;
    }

    i = 0;
    out = work->field_7FC;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 2)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

static void InitProc(Work *work)
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
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    int      model;
    int      motion;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    GM_ConfigControlHazard(control, 1000, -1, -1);

    GCL_GetOption('m');
    model = GCL_StrToInt(GCL_GetParamResult());

    GCL_GetOption('o');
    motion = GCL_StrToInt(GCL_GetParamResult());

    body = &work->body;
    GM_InitObject(body, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, motion & 0xFFFF, work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    GCL_GetOption('b');
    work->bound_where = GCL_StrToInt(GCL_GetParamResult());

    InitSounds(work);
    InitProc(work);

    GCL_GetOption('a');
    GCL_StrToSV(GCL_GetParamResult(), &work->field_7E4);

    work->unused3 = 0;
    work->timer = 0;
    work->shadow = NULL;

    return 0;
}

void *NewPrisonNinja(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "ninja.c");
    if (GetResources(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }
    return (void *)work;
}
