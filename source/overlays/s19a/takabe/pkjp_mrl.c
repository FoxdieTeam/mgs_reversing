#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/meryl_jeep.h"

/* Meryl (or Otacon) sitting in the parked jeep (created by pjeep.c) */


typedef void (*ACTION)(MerylJeepWork *, int);

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

/* pjeep.c */
extern int PkJeep_800E0E18;
extern int PkJeep_800E0E1C;
extern int PkJeep_Flags;

void sna_act_helper2_helper2_80033054(int face, SVECTOR *rot);

/* position in the jeep */
SVECTOR pkjp_mrl_offset = {345, 915, -440};

static void ActionMain(MerylJeepWork *work);

static inline void SetMode(MerylJeepWork *work, ACTION action)
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

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
    control->mov = pkjp_mrl_offset;

    GM_ActControl(control);
    GM_ActObject(body);

    objs = work->body.objs;
    CompMatrix(work->root_mat, &objs->world, &objs->world);

    control->mov.vx = objs->world.t[0];
    control->mov.vy = objs->world.t[1];
    control->mov.vz = objs->world.t[2];

    DG_GetLightMatrix(&control->mov, work->light);
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
        GM_InitObject(body, GV_StrCode("meryl"), BODY_FLAG, GV_StrCode("mel_19a"));
        work->face = GV_StrCode("メリル");
        work->voice1 = 0x82;
        work->voice2 = 0x83;
        work->voice3 = 0x84;
        work->voice4 = 0x82;
    }
    else
    {
        GM_InitObject(body, GV_StrCode("otacom"), BODY_FLAG, GV_StrCode("mel_19a"));
        work->face = GV_StrCode("メリル");
        work->voice1 = 0x85;
        work->voice2 = 0x86;
        work->voice3 = 0x87;
        work->voice4 = 0x85;
    }

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("mel_19a"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 14, 28, 0);
    GM_ActMotion(&work->body);
    GM_ConfigMotionAdjust(body, work->adjust);

    work->target = GM_AllocTarget();
    control->r_sphere = -2;
    return 0;
}


void PkJeepMerylDie(MerylJeepWork *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

void *NewPkJeepMeryl(CONTROL *root_ctrl, MATRIX *root_mat, int which)
{
    MerylJeepWork *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(MerylJeepWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, PkJeepMerylDie, "pkjp_mrl.c");

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
static void StateDuck1(MerylJeepWork *work, int time);
static void StateDuck2(MerylJeepWork *work, int time);
static void StateDuck3(MerylJeepWork *work, int time);
static void StateShout1(MerylJeepWork *work, int time);
static void StateShout2(MerylJeepWork *work, int time);
static void StateShout3(MerylJeepWork *work, int time);
static void StateDamage(MerylJeepWork *work, int time);
static void StateShoot1(MerylJeepWork *work, int time);
static void StateShoot2(MerylJeepWork *work, int time);

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
        SetMode(work, StateShoot1);
        return 1;
    }

    if (flags & 0x2000)
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

static void StateShoot1(MerylJeepWork *work, int time)
{
    SVECTOR pos;

    if (time == 0)
    {
        work->action_id = 14;
        GM_ConfigObjectAction(&work->body, 14, 0, 4);
    }

    if (time == 1)
    {
        pos.vx = work->body.objs->objs[4].world.t[0];
        pos.vy = work->body.objs->objs[4].world.t[1];
        pos.vz = work->body.objs->objs[4].world.t[2];
        GM_SeSet(&pos, 0xB2);
    }

    if ((time & 3) == 2)
    {
        PkJeep_800E0E1C = 255;
    }

    if (work->body.is_end)
    {
        if (work->flags & 0x10000)
        {
            SetMode(work, StateShoot2);
        }
        else
        {
            work->time = 0;
        }
    }
}

static void StateShoot2(MerylJeepWork *work, int time)
{
    SVECTOR pos;

    if (time == 0)
    {
        work->action_id = 14;
        GM_ConfigObjectAction(&work->body, 14, 0, 4);
    }

    if (time == 1)
    {
        pos.vx = work->body.objs->objs[4].world.t[0];
        pos.vy = work->body.objs->objs[4].world.t[1];
        pos.vz = work->body.objs->objs[4].world.t[2];
        GM_SeSet(&pos, 0xB1);
    }

    if ((time & 3) == 2)
    {
        PkJeep_800E0E1C = 255;
    }

    if (work->body.is_end)
    {
        PkJeep_800E0E18 = 1;
        SetMode(work, StateIdle);
    }
}

static void StateLook(MerylJeepWork *work, int time)
{
    SVECTOR diff;
    int     dir;

    if (time == 0)
    {
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);

    dir = -ratan2(diff.vz, diff.vx) - work->control.rot.vy;
    dir &= 0xFFF;
    if (dir & 0x800)
    {
        dir -= 0x1000;
    }

    if (dir < -0x400)
    {
        dir = -0x400;
    }

    if (dir > 0x400)
    {
        dir = 0x400;
    }

    work->head_rot = dir;

    if (!(work->flags & 0x2000))
    {
        SetMode(work, StateIdle);
        work->head_rot = 0;
    }
}

static void StateDuck1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }

    if (CheckFlags(work) == 0 && work->body.is_end)
    {
        SetMode(work, StateDuck2);
    }
}

static void StateDuck2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }

    if (CheckFlags(work) == 0 && !(work->flags & 0x20000))
    {
        SetMode(work, StateDuck3);
    }
}

static void StateDuck3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }

    if (CheckFlags(work) == 0 && work->body.is_end)
    {
        SetMode(work, StateIdle);
    }
}

static void StateShout1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }

    if (CheckFlags(work) == 0 && work->body.is_end)
    {
        SetMode(work, StateShout2);
    }
}

static void StateShout2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }

    if (CheckFlags(work) == 0 && !(work->flags & 0x20000))
    {
        SetMode(work, StateShout3);
    }
}

static void StateShout3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }

    if (CheckFlags(work) == 0 && work->body.is_end)
    {
        SetMode(work, StateIdle);
    }
}

static void StateDamage(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 13;
        GM_ConfigObjectAction(&work->body, 13, 0, 4);
        GM_SeSet(&work->control.mov, work->voice1);
    }

    if (work->body.is_end)
    {
        SetMode(work, StateIdle);
    }
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
        action = StateShoot1;
        work->action = action;
        work->action_id = 14;
        GM_ConfigObjectAction(&work->body, 14, 0, 0);
    }

    action(work, time);
}

static void ActionMain(MerylJeepWork *work)
{
    work->flags = PkJeep_Flags;
    PkJeep_Flags &= ~0xFFFF;
    ActionMain2(work);
}
