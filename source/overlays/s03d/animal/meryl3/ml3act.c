#include "meryl3.h"
#include "anime/animconv/anime.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

/*---------------------------------------------------------------------------*/

#define ACTINTERP   4

#define STANDSTILL  0
#define WALK        1
#define GUNSHOOT    2
#define SITUP       3
#define DAMAGE      4
#define RUN         5
#define RELOAD      6
#define UNUSED      7

static short act_table[8] =
{
    0, 1, 0, 4, 3, 2, 5, 0
};

static SVECTOR bullet_pos = {5, -500, 80};
static SVECTOR blood_pos = {0, 0, 100};
static SVECTOR blood_rot = {-1024, 0, 0};

static void ActWalk(Work *work, int time);
static void ActRun(Work *work, int time);
static void ActReload(Work *work, int time);
static void ActAim(Work *work, int time);
static void ActShoot(Work *work, int time);
static void ActDamage(Work *work, int time);

/*---------------------------------------------------------------------------*/

static inline void SetAction( Work *work, int n_action, int interp )
{
    work->n_action = n_action;
    GM_ConfigObjectAction( &( work->body ), act_table[ n_action ], 0, interp );
}

static inline void UnsetMode( Work *work )
{
    GM_ConfigObjectOverride( &( work->body ), act_table[ 0 ], 0, 4, 0 );
    work->action2 = 0;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

/*---------------------------------------------------------------------------*/

static int CheckPad(Work *work)
{
    if (work->pad.press & PAD_L2)
    {
        SetMode(work, ActAim);
        return 1;
    }

    if (work->pad.press & PAD_L1)
    {
        SetMode(work, ActRun);
        return 1;
    }

    if (work->pad.press & PAD_R1)
    {
        SetMode(work, ActReload);
        return 1;
    }

    return 0;
}

static int CheckTarget(Work *work)
{
    TARGET *trg;

    trg = work->target;
    if (trg->damaged & TARGET_POWER)
    {
        switch (trg->a_mode)
        {
        case 1:
            trg->force = DG_ZeroVector;
            SetMode(work, ActDamage);
            break;
        case 2:
            trg->force = DG_ZeroVector;
            SetMode(work, ActDamage);
            break;
        }

        trg->damage = 0;
        trg->damaged = 0;
        return 1;
    }

    return 0;
}

static void AdjustTarget(Work *work)
{
    int pitch;

    pitch = work->trg_pitch;
    work->adjust[2].vx = pitch;
    work->adjust[6].vx = pitch;

    if (pitch < 0)
    {
        work->adjust[7].vx = pitch * 3;
    }
    else
    {
        work->adjust[7].vx = pitch * 3 / 2;
    }
}

static void FamasShoot(Work *work)
{
    MATRIX  mat;
    SVECTOR rot;
    MATRIX *world;

    world = &work->body.objs->objs[4].world;

    DG_SetPos(world);
    DG_MovePos(&bullet_pos);

    rot = DG_ZeroVector;
    rot.vx = 1024;
    DG_RotatePos(&rot);

    ReadRotMatrix(&mat);
    NewBulletEx(BULLET_RECOILSPARK, &mat, PLAYER_SIDE, 1, 0, 10, 65, 10000, 750);
    GM_SeSetMode(&work->control.mov, SE_GUNCAM_SHOT, GM_SEMODE_BOMB);
    AN_BulletSmoke(world, 0);
    AN_FamasFlash(&mat);
}

static void ActIdle(Work *work, int time)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;

    if (time == 0)
    {
        SetAction(work, STANDSTILL, ACTINTERP);
    }

    if (CheckTarget(work))
    {
        return;
    }

    if (CheckPad(work))
    {
        return;
    }

    if (work->pad.dir >= 0)
    {
        SetMode(work, ActWalk);
    }

    work->control.step = DG_ZeroVector;
    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void ActWalk(Work *work, int time)
{
    CONTROL *control;
    int      dir, dis;

    control = &work->control;
    dir = work->pad.dir;

    if (time == 0)
    {
        SetAction(work, WALK, ACTINTERP);
    }

    if (CheckTarget(work))
    {
        return;
    }
    if (CheckPad(work))
    {
        return;
    }

    if (dir < 0)
    {
        SetMode(work, ActIdle);
        UnsetMode(work);
        return;
    }

    control->turn.vy = dir;
    dis = (time < 10) ? time * 4 : 40;
    control->step.vx = dis * rsin(dir) / 4096;
    control->step.vz = dis * rcos(dir) / 4096;
    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void ActRun(Work *work, int time)
{
    CONTROL *control;

    control = &work->control;

    work->control.step.vx = 0;
    work->control.step.vz = 0;

    if (time == 0)
    {
        SetAction(work, RUN, ACTINTERP);
    }

    if (CheckTarget(work))
    {
        return;
    }

    if (!(work->pad.press & PAD_L1))
    {
        if (!CheckPad(work))
        {
            SetMode(work, ActIdle);
        }
        return;
    }

    control->turn.vy = work->trg_yaw;
    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void ActReload(Work *work, int time)
{
    CONTROL *control;

    control = &work->control;

    if (time == 0)
    {
        SetAction(work, GUNSHOOT, ACTINTERP);
    }

    if (time < 30 && (time % 8) == 0)
    {
        GM_SeSetMode(&work->control.mov, SE_KARASHT, GM_SEMODE_BOMB);
    }

    if (time == 30)
    {
        SetAction(work, RELOAD, ACTINTERP);
        NewAnime_8005DDE0(&work->body.objs->objs[4].world);
    }

    if (time == 46)
    {
        GM_SeSetMode(&work->control.mov, SE_RELOAD, GM_SEMODE_BOMB);
    }

    if (time >= 31 && work->body.is_end)
    {
        SetMode(work, ActIdle);
        GM_SeSetMode(&work->control.mov, SE_READY_WEAPON, GM_SEMODE_BOMB);
        return;
    }

    control->turn.vy = work->trg_yaw;
    control->step = DG_ZeroVector;
    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void ActAim(Work *work, int time)
{
    int press;

    press = work->pad.press;

    work->control.step.vx = 0;
    work->control.step.vz = 0;

    if (CheckTarget(work))
    {
        return;
    }

    if (time == 0)
    {
        SetAction(work, GUNSHOOT, ACTINTERP);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    AdjustTarget(work);

    if (!(press & PAD_L2))
    {
        SetMode(work, ActIdle);
        return;
    }

    work->control.turn.vy = work->trg_yaw;
    work->control.step = DG_ZeroVector;

    if (press & PAD_R2)
    {
        SetMode(work, ActShoot);
        return;
    }

    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void ActShoot(Work *work, int time)
{
    if (CheckTarget(work))
    {
        return;
    }

    if (time == 0)
    {
        SetAction(work, GUNSHOOT, 0);
        FamasShoot(work);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    AdjustTarget(work);

    work->control.turn.vy = work->trg_yaw;
    work->control.step = DG_ZeroVector;

    SetMode(work, ActAim);
    work->target->class |= (TARGET_SEEK | TARGET_POWER);
}

static void PutBlood(Work *work, int unit, int count)
{
    MATRIX m;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&blood_pos);
    DG_RotatePos(&blood_rot);

    ReadRotMatrix(&m);
    NewBlood(&m, count);

    work->control.step = DG_ZeroVector;
}

static void ActDamage(Work *work, int time)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;

    if (time == 0)
    {
        SetAction(work, DAMAGE, ACTINTERP);
        GM_SeSet(&work->control.mov, 187);
        PutBlood(work, 5, 0);
    }

    if (work->body.is_end)
    {
        SetMode(work, ActIdle);
    }
}

static void DoAction(Work *work)
{
    CONTROL *control;
    OBJECT  *body;
    int      time;
    void   (*action)(struct _Work *, int);

    control = &work->control;
    body = &work->body;

    work->target->class = TARGET_AVAIL;

    time = work->time++;
    action = work->action;
    if (action == NULL)
    {
        action = ActIdle;
        work->action = action;
    }

    action(work, time);

    control->height = body->height;
    control->r_sphere = -1;

    if (work->height < 0 && control->grounded)
    {
        work->height = 0;
    }

    work->height -= 16;
    control->step.vy = work->height;
}

static void CheckPlayer(Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &vec);
    vec.vy = 0;

    work->player_dir = GV_VecDir2(&vec);
    work->player_dis = GV_VecLen3(&vec);
}

void Meryl3Act(Work *work)
{
    CheckPlayer(work);
    Meryl3Think(work);
    DoAction(work);
}
