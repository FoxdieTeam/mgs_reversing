#include "mgstype.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"
#include "game/vibrate.h"
#include "../jeep_system.h"
#include "takabe/meryl_jeep.h"

extern SVECTOR s19b_dword_800C39E0;

/* the Meryl (or Otacon) sitting in the jeep; same actor as pkjp_mrl.c of s19a */

typedef void (*ACTION)(MerylJeepWork *, int);

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

static inline void SetMode(MerylJeepWork *work, ACTION action)
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void sna_act_helper2_helper2_80033054(int face, SVECTOR *rot);

static void ActionMain(MerylJeepWork *work);

static void Act(MerylJeepWork *work)
{
    CONTROL *control;
    OBJECT  *body;
    DG_OBJS *objs;

    control = &work->control;

    ActionMain(work);

    body = &work->body;
    GM_ActMotion(body);

    sna_act_helper2_helper2_80033054(work->face, &work->adjust[6]);
    work->adjust[6].vy = GV_NearSpeed(work->adjust[6].vy, work->head_rot, 200);

    control->turn = DG_ZeroVector;
    control->rot = control->turn;
    control->mov = s19b_dword_800C39E0;

    GM_ActControl(control);
    GM_ActObject(body);

    objs = work->body.objs;
    CompMatrix(work->root_mat, &objs->world, &objs->world);

    control->mov.vx = objs->world.t[0];
    control->mov.vy = objs->world.t[1];
    control->mov.vz = objs->world.t[2];

    DG_GetLightMatrix(&control->mov, work->light);

    Takabe_MerylHeadPos.vx = work->body.objs->objs[6].world.t[0];
    Takabe_MerylHeadPos.vy = work->body.objs->objs[6].world.t[1];
    Takabe_MerylHeadPos.vz = work->body.objs->objs[6].world.t[2];

    GM_MoveTarget(work->target, &control->mov);
}

static int GetResources(MerylJeepWork *work, int name, int which)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, GM_CurrentMap) < 0)
    {
        return -1;
    }

    control->mov = work->root_ctrl->mov;
    control->rot = work->root_ctrl->rot;
    GM_ConfigControlInterp(control, 4);

    body = &work->body;
    if (which == 0)
    {
        GM_InitObject(body, GV_StrCode("meryl"), BODY_FLAG, GV_StrCode("mel_19b"));
        work->face = GV_StrCode("メリル");
        work->voice1 = 0x82;
        work->voice2 = 0x83;
        work->voice3 = 0x84;
        work->voice4 = 0x82;
    }
    else
    {
        GM_InitObject(body, GV_StrCode("otacom"), BODY_FLAG, GV_StrCode("mel_19b"));
        work->face = GV_StrCode("オタコン");
        work->voice1 = 0x85;
        work->voice2 = 0x86;
        work->voice3 = 0x87;
        work->voice4 = 0x85;
    }

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("mel_19b"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ActMotion(&work->body);
    GM_ConfigMotionAdjust(body, work->adjust);

    work->target = GM_AllocTarget();
    Takabe_JeepSystem.meryl_body = body;
    control->r_sphere = -2;
    return 0;
}

void s19b_jeep_mrl_800D4098(MerylJeepWork *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

void *s19b_jeep_mrl_800D40D4(CONTROL *root_ctrl, MATRIX *root_mat, int which)
{
    MerylJeepWork *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(MerylJeepWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, s19b_jeep_mrl_800D4098, "jeep_mrl.c");

        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;

        if (GetResources(work, GV_StrCode("meryl"), which) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}

static void StateIdle(MerylJeepWork *work, int time);
static void StateLook(MerylJeepWork *work, int time);
static void StateCrouch(MerylJeepWork *work, int time);
static void StateDuck1(MerylJeepWork *work, int time);
static void StateDuck2(MerylJeepWork *work, int time);
static void StateDuck3(MerylJeepWork *work, int time);
static void StateShout1(MerylJeepWork *work, int time);
static void StateShout2(MerylJeepWork *work, int time);
static void StateShout3(MerylJeepWork *work, int time);
static void StateDamage(MerylJeepWork *work, int time);

static int CheckFlags(MerylJeepWork *work)
{
    int flags = work->flags;

    if (flags & 0x2)
    {
        SetMode(work, StateDamage);
        return 1;
    }

    if (flags & 0x1)
    {
        SetMode(work, StateIdle);
        return 1;
    }

    if (flags & 0x20)
    {
        SetMode(work, StateDuck1);
        return 1;
    }

    if (flags & 0x200)
    {
        SetMode(work, StateShout1);
        return 1;
    }

    if (flags & 0x1000)
    {
        SetMode(work, StateCrouch);
        return 1;
    }

    if ((flags & 0x10000) == 0)
    {
        SetMode(work, StateLook);
        return 1;
    }

    return 0;
}

static void StateIdle(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    CheckFlags(work);
}

static void StateLook(MerylJeepWork *work, int time)
{
    SVECTOR diff;
    int     angle;

    if (time == 0)
    {
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    if ((Takabe_JeepSystem.flags & 1) && GV_RandU(0x100) < 0x14)
    {
        GM_SeSet(&work->control.mov, work->voice3);
    }

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);

    angle = (GM_PlayerControl->rot.vy - work->control.rot.vy) - work->root_ctrl->rot.vy;
    angle &= 0xFFF;
    if (angle & 0x800)
    {
        angle -= 0x1000;
    }
    if (angle < -0x400)
    {
        angle = -0x400;
    }
    if (angle > 0x400)
    {
        angle = 0x400;
    }
    work->head_rot = angle;

    if (work->flags & 0x10000)
    {
        work->head_rot = 0;
        if (CheckFlags(work) == 0)
        {
            SetMode(work, StateIdle);
        }
    }
}

static void StateCrouch(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }

    if (work->flags & 0x10000)
    {
        SetMode(work, StateIdle);
    }
}

static void StateDuck1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetMode(work, StateDuck2);
}

static void StateDuck2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }

    if (CheckFlags(work) != 0) return;
    if (work->flags & 0x20000) return;
    SetMode(work, StateDuck3);
}

static void StateDuck3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetMode(work, StateIdle);
}

static void StateShout1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetMode(work, StateShout2);
}

static void StateShout2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }

    if (CheckFlags(work) != 0) return;
    if (work->flags & 0x20000) return;
    SetMode(work, StateShout3);
}

static void StateShout3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetMode(work, StateIdle);
}

static void StateDamage(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 13;
        GM_ConfigObjectAction(&work->body, 13, 0, 4);
        GM_SeSet(&work->control.mov, work->voice1);
    }

    if (work->body.is_end == 0) return;
    SetMode(work, StateIdle);
}

static void ActionMain2(MerylJeepWork *work)
{
    ACTION action;
    int    time;

    time = work->time;
    action = work->action;
    work->time = time + 1;

    if (action == NULL)
    {
        action = StateIdle;
        work->action = action;
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    action(work, time);
}

static void ActionMain(MerylJeepWork *work)
{
    work->flags = Takabe_JeepSystem.flags_50;
    Takabe_JeepSystem.flags_50 &= ~0xFFFF;
    ActionMain2(work);
}
