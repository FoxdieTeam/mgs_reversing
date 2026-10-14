#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/camera.h"
#include "sound/g_sound.h"

/* Snake standing in the parked jeep (created by pjeep.c), shooting with the jeep's gun */

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;           // 0x20
    MATRIX        *root_mat;            // 0x24
    CONTROL        control;             // 0x28
    OBJECT         body;                // 0xA4
    MOTION_CONTROL m_ctrl;              // 0x188
    MOTION_SEGMENT m_segs1[17];         // 0x1D8
    MOTION_SEGMENT m_segs2[17];         // 0x43C
    SVECTOR        rots[16];            // 0x6A0
    SVECTOR        adjust[16];          // 0x720
    MATRIX         light[2];            // 0x7A0
    SVECTOR        rot;                 // 0x7E0
    OBJECT         weapon;              // 0x7E8
    char           pad_8CC[0x8];
    SVECTOR        gun_rot;             // 0x8D4
    char           pad_8DC[0x8];
    MATRIX         gun_world;           // 0x8E4
    int            field_904;           // 0x904
    int            aim_dir;             // 0x908
    int            field_90C;           // 0x90C
    TARGET        *target;              // 0x910
    char           pad_914[0x4];
    void          *action;              // 0x918
    char           pad_91C[0x4];
    int            time;                // 0x920
    char           pad_924[0x4];
    int            motion;              // 0x928
    int            pad_flags;           // 0x92C
    char           pad_930[0xC];
    int            vitality;            // 0x93C
    int            damaged;             // 0x940
    int            blink;               // 0x944
    int            hide;                // 0x948
    char           pad_94C[0x4];
    int            dead;                // 0x950
    char           pad_954[0x4];
} Work;

typedef void (*ACTION)(Work *, int);

#define EXEC_LEVEL GV_ACTOR_AFTER

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

extern void *NewPadVibration(unsigned char *table, int dir);
extern void *NewBlood(MATRIX *world, int count);
#include "okajima/bullet.h"
extern void *AN_PkFlash(MATRIX *world);

extern void Voicesys_800CE310(void);
extern void Voicesys_800CE5F8(int, int);
extern void Voicesys_800CE734(void);

VECTOR  pkjp_sne_scale = {2048, 2048, 2048};
int     pkjp_sne_address = -1;
SVECTOR pkjp_sne_target_size = {150, 750, 150};

short   pkjp_sne_actions[8] = {0, 1, 2, 3, 4, 5, 6};

u_char  pkjp_sne_vib_damage1[4] = {0x7F, 0x04, 0x00, 0x00};
u_char  pkjp_sne_vib_damage2[8] = {0xE1, 0x01, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00};
u_char  pkjp_sne_vib_dead1[4] = {0x7F, 0x01, 0x00, 0x00};
u_char  pkjp_sne_vib_dead2[4] = {0x9B, 0x03, 0x00, 0x00};

SVECTOR pkjp_sne_blood_pos = {0, 0, 100};
SVECTOR pkjp_sne_blood_rot = {-1024, 0, 0};

SVECTOR pkjp_sne_bullet_pos = {0, 286, 574};
SVECTOR pkjp_sne_bullet_rot = {3072, 0, 0};

SVECTOR pkjp_sne_gun_pos = {0, 1435, -925};
SVECTOR pkjp_sne_gun_ofs = {180, -932, -340};
int     pkjp_sne_counter = 0;

static void StateNormal(Work *work, int time);
static void StateDamage(Work *work, int time);
static void StateDead(Work *work, int time);
static void StateDead2(Work *work, int time);
void s19a_800DB510(Work *work);

static inline void SetMotion(Work *work, int motion)
{
    if (work->motion != motion)
    {
        work->motion = motion;
        GM_ConfigObjectAction(&work->body, pkjp_sne_actions[motion], 0, 4);
        work->rot = DG_ZeroVector;
    }
}

static void Act(Work *work)
{
    SVECTOR  rot;
    SVECTOR  pos;
    OBJECT  *body;
    CONTROL *control;
    TARGET  *target;
    int      vitality;

    body = &work->body;

    rot = work->control.rot;
    work->control.rot = DG_ZeroVector;
    control = &work->control;
    GM_ActMotion(body);
    work->control.rot = rot;

    work->rot.vx += work->control.step.vx;
    work->rot.vz += work->control.step.vz;
    work->rot.vy = work->body.height - 503;

    GM_ActControl(control);
    GM_ActObject(body);
    ScaleMatrix(&work->body.objs->world, &pkjp_sne_scale);
    DG_GetLightMatrix(&control->mov, work->light);

    s19a_800DB510(work);

    GM_PlayerPosition = work->control.mov;

    pos = work->control.mov;
    pos.vy = 0;
    GM_PlayerAddress = pkjp_sne_address = HZD_GetAddress(work->control.map->hzd, &pos, pkjp_sne_address);

    GM_SnakeCamera.position.vx = work->body.objs->objs[6].world.t[0];
    GM_SnakeCamera.position.vy = work->body.objs->objs[6].world.t[1];
    GM_SnakeCamera.position.vz = work->body.objs->objs[6].world.t[2];

    if (GM_GameOverTimer == 0)
    {
        if (GM_PlayerStatus & PLAYER_INVINCIBLE)
        {
            work->target->vital = work->vitality;
        }

        target = work->target;
        vitality = target->vital;
        vitality += GM_Vitality - work->vitality;
        if (vitality > GM_VitalityMax)
        {
            vitality = GM_VitalityMax;
        }

        target->vital = vitality;
        GM_Vitality = work->vitality = (short)vitality;

        if ((short)vitality <= 0)
        {
            if (GM_Item == IT_Ration && GM_Items[IT_Ration] != 0)
            {
                if (--GM_Items[IT_Ration] == 0)
                {
                    GM_Item = IT_None;
                }

                GM_Vitality = work->vitality = work->target->vital = (GM_GameLevel <= GM_LEVEL_EASY) ? 384 : 256;

                if (GM_GameLevel < GM_LEVEL_EASY)
                {
                    GM_Vitality = work->vitality = work->target->vital = GM_VitalityMax;
                }

                GM_SeSet2(0, 63, SE_RECOVER_LIFE);
                GM_RationUseCount++;
            }
            else
            {
                GM_Vitality = 0;
                GM_GameOver();
                GM_GameOverTimer = -1;
                work->dead = 1;
                GM_SeSet(NULL, 0x1A);
                work->control.skip_flag |= CTRL_SKIP_TRAP;
                GM_GameStatus |= STATE_PADRELEASE;
            }
        }
    }

    GM_MoveTarget(work->target, &work->control.mov);

    if (work->blink == 0)
    {
        work->target->class = TARGET_SEEK | TARGET_POWER;
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
    }
    else
    {
        work->target->class = TARGET_AVAIL;

        if (work->blink & 2)
        {
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
        }
        else
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        }

        work->blink--;
    }

    if (work->hide)
    {
        work->body.objs->flag |= DG_FLAG_INVISIBLE;
    }
}

void PkJeepSnakeInitTarget(Work *work)
{
    TARGET *target;
    int     vitality;

    target = work->target;
    vitality = GM_Vitality;

    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, PLAYER_SIDE, &pkjp_sne_target_size);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, vitality, 0, &DG_ZeroVector);
    target->map = work->root_ctrl->map->index;
}

static int GetResources(Work *work, int name)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, work->root_ctrl->map->index) < 0)
    {
        return -1;
    }

    control->mov = work->root_ctrl->mov;
    control->rot = work->root_ctrl->rot;

    GM_ConfigControlInterp(control, 4);
    GM_ConfigControlHazard(control, 750, 450, 450);
    GM_ConfigControlAttribute(control, RADAR_VISIBLE);
    GM_ConfigControlTrapCheck(control);

    GM_PlayerStatus = 0;

    body = &work->body;
    GM_InitObject(body, GV_StrCode("snake"), BODY_FLAG, GV_StrCode("sne_19b"));
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("sne_19b"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    work->target = GM_AllocTarget();
    PkJeepSnakeInitTarget(work);

    control->r_sphere = -2;

    GM_PlayerBody = body;
    GM_PlayerControl = control;

    work->vitality = GM_Vitality;
    return 0;
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_PlayerControl = NULL;
    GM_PlayerBody = NULL;
}

void *NewPkJeepSnake(CONTROL *root_ctrl, MATRIX *root_mat)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "pkjp_sne.c");

        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;

        if (GetResources(work, GV_StrCode("スネーク")) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

static void PutBlood(Work *work, int obj, int count)
{
    MATRIX world;

    DG_SetPos(&work->body.objs->objs[obj].world);
    DG_MovePos(&pkjp_sne_blood_pos);
    DG_RotatePos(&pkjp_sne_blood_rot);
    ReadRotMatrix(&world);
    NewBlood(&world, count);
}

static int CheckDamage(Work *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->force = DG_ZeroVector;

        work->action = StateDamage;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;

        target->damage = 0;
        target->damaged = 0;

        NewPadVibration(pkjp_sne_vib_damage1, 1);
        NewPadVibration(pkjp_sne_vib_damage2, 2);
        return 1;
    }

    return 0;
}

static int CheckDamage2(Work *work)
{
    if (CheckDamage(work))
    {
        work->target->class = TARGET_AVAIL;
        work->blink = 4;
        work->aim_dir += GV_RandS(512);
        return 1;
    }

    return 0;
}

static void Shoot(Work *work)
{
    MATRIX  world;
    SVECTOR pos;
    long    flag;

    RotMatrix(&pkjp_sne_bullet_rot, &world);
    MulMatrix0(&work->gun_world, &world, &world);
    DG_SetPos(&work->gun_world);
    RotTrans(&pkjp_sne_bullet_pos, (VECTOR *)world.t, &flag);
    NewBullet(&world, 1, 1, 0);

    pos.vx = world.t[0];
    pos.vy = world.t[1];
    pos.vz = world.t[2];
    GM_SeSet(&pos, 0x2E);
    AN_PkFlash(&world);
}

static void StateNormal(Work *work, int time)
{
    int flags;

    flags = work->pad_flags;

    if (CheckDamage2(work))
    {
        return;
    }

    if (flags & 1)
    {
        Shoot(work);
    }

    if (time == 0)
    {
        SetMotion(work, 0);
    }

    if (flags & 2)
    {
        SetMotion(work, 2);
    }
    else if (flags & 4)
    {
        SetMotion(work, 3);
    }
    else
    {
        SetMotion(work, 0);
    }
}

static void StateDamage(Work *work, int time)
{
    work->blink = 4;

    if (time == 0)
    {
        work->damaged = 1;
        SetMotion(work, 1);
        PutBlood(work, 5, 0);

        if (GM_Vitality > 0)
        {
            GM_SeSet(&work->control.mov, 0x88);
        }
    }

    if (work->body.is_end)
    {
        if (work->dead == 0)
        {
            work->action = StateNormal;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            SetMotion(work, 0);
            work->damaged = 0;
            work->blink = 45;
        }
        else
        {
            work->action = StateDead;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}

static void StateDead(Work *work, int time)
{
    if (time == 0)
    {
        SetMotion(work, 4);
        Voicesys_800CE310();
        Voicesys_800CE5F8(12, 1);
        Voicesys_800CE734();
    }

    if (time == 61)
    {
        NewPadVibration(pkjp_sne_vib_dead1, 1);
        NewPadVibration(pkjp_sne_vib_dead2, 2);
        GM_SeSetMode(&work->control.mov, 0x33, GM_SEMODE_BOMB);
    }

    if (work->body.is_end)
    {
        GM_GameOverTimer = 1;
        work->action = StateDead2;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

static void StateDead2(Work *work, int time)
{
    if (time == 0)
    {
        SetMotion(work, 5);
    }
}

static void ActionMain(Work *work)
{
    ACTION action;
    int    time;

    work->target->class = TARGET_AVAIL;

    time = work->time;
    action = work->action;
    work->time = time + 1;

    if (action == NULL)
    {
        action = StateNormal;
        work->action = action;
        SetMotion(work, 0);
    }

    action(work, time);

    if (GM_PlayerStatus & PLAYER_INVINCIBLE)
    {
        work->target->class = TARGET_AVAIL;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800DAE40.s")
void s19a_800DAE40(Work *work); /* pad input, aiming */

void s19a_800DB510(Work *work)
{
    s19a_800DAE40(work);
    ActionMain(work);
}
