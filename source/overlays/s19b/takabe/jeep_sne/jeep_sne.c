#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/camera.h"
#include "sound/g_sound.h"

/* Snake standing in the jeep (created by jeep.c), shooting with the jeep's gun.
   Same actor as s19a pkjp_sne.c, plus the gun object, the camera follow and
   the scripted aim flags of Takabe_JeepSystem. */

typedef struct _JEEP_SYSTEM
{
    char     pad_00[0x4];
    CONTROL *control;               // 0x04
    char     pad_08[0x4C - 0x8];
    int      flags;                 // 0x4C
    int      field_50;              // 0x50
    char     pad_54[0x5C - 0x54];
    int      has_homing_target;     // 0x5C
    OBJECT  *snake_body;            // 0x60
    char     pad_64[0x78 - 0x64];
    int      field_78;              // 0x78
    char     pad_7C[0x128 - 0x7C];
    SVECTOR  camera_pos;            // 0x128
} JEEP_SYSTEM;

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
    SVECTOR        world_rot;           // 0x8CC: gun_rot + the jeep's rotation
    SVECTOR        gun_rot;             // 0x8D4
    char           pad_8DC[0x8];
    MATRIX         gun_world;           // 0x8E4
    int            shoot_wait;          // 0x904
    int            aim_dir;             // 0x908
    int            aim_pitch;           // 0x90C
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
    SVECTOR        pos;                 // 0x958
} Work;

typedef void (*ACTION)(Work *, int);

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL GV_ACTOR_AFTER

#define SNAKE_NAME 0x21CA // GV_StrCode("スネーク")

#define MOTION_DATA GV_StrCode("sne_19b")
#define BODY_DATA   GV_StrCode("snake")
#define WEAPON_DATA GV_StrCode("jeep_gun")

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )
#define WEAPON_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

extern void *NewPadVibration(unsigned char *table, int dir);
extern void *NewBlood(MATRIX *world, int count);
extern void *NewJeepBlood(MATRIX *, int, DG_OBJ *);
extern void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2);
extern void *AN_FamasFlash(MATRIX *world);
extern void s19b_jblood_800C8070(MATRIX *world);

extern void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
extern void Voicesys_800CE310(void);
extern void Voicesys_800CE5F8(int, int);
extern void Voicesys_800CE734(void);
extern void GM_CheckShukanReverse(unsigned short *pInput);
extern void GM_CheckShukanReverseAnalog(unsigned char *pInput);

VECTOR  jeep_sne_scale = {2048, 2048, 2048};
SVECTOR jeep_sne_target_size = {150, 750, 150};

short   jeep_sne_actions[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

u_char  jeep_sne_vib_damage1[4] = {0x7F, 0x04, 0x00, 0x00};
u_char  jeep_sne_vib_damage2[8] = {0xE1, 0x01, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00};
u_char  jeep_sne_vib_dead1[4] = {0x7F, 0x01, 0x00, 0x00};
u_char  jeep_sne_vib_dead2[4] = {0x9B, 0x03, 0x00, 0x00};

SVECTOR jeep_sne_blood_pos = {0, 0, 100};
SVECTOR jeep_sne_blood_rot = {-1024, 0, 0};

SVECTOR jeep_sne_bullet_pos = {0, 286, 574};
SVECTOR jeep_sne_bullet_rot = {3072, 0, 0};

SVECTOR jeep_sne_gun_pos = {0, 1435, -925};
SVECTOR jeep_sne_gun_ofs = {180, -932, -340};
int     jeep_sne_counter = 0;

static void StateNormal(Work *work, int time);
static void StateDamage(Work *work, int time);
void StateHit(Work *work, int time);
static void StateDead(Work *work, int time);
static void StateDead2(Work *work, int time);
static void PadAndAction(Work *work);

static inline void SetMotion(Work *work, int motion)
{
    if (work->motion != motion)
    {
        work->motion = motion;
        GM_ConfigObjectAction(&work->body, jeep_sne_actions[motion], 0, 4);
        work->rot = DG_ZeroVector;
    }
}

static void Act(Work *work)
{
    SVECTOR  rot;
    SVECTOR  diff;
    SVECTOR *cam;
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
    ScaleMatrix(&work->body.objs->world, &jeep_sne_scale);
    DG_GetLightMatrix(&control->mov, work->light);

    PadAndAction(work);

    sna_act_helper2_helper2_80033054(SNAKE_NAME, &work->adjust[6]);

    GM_PlayerPosition = work->control.mov;

    cam = &Takabe_JeepSystem.camera_pos;
    cam->vx = work->body.objs->objs[6].world.t[0];
    cam->vy = work->body.objs->objs[6].world.t[1];
    cam->vz = work->body.objs->objs[6].world.t[2];

    GV_SubVec3(&Takabe_JeepSystem.control->mov, &work->pos, &diff);
    work->pos = Takabe_JeepSystem.control->mov;
    GV_AddVec3(cam, &diff, cam);

    GM_SnakeCamera.position = *cam;
    GM_SnakeCamera.target = GM_SnakeCamera.position;

    if (GM_GameOverTimer == 0)
    {
        if (GM_GameStatus & (STATE_PADRELEASE | STATE_PAUSE_ONLY))
        {
            work->target->vital = GM_Vitality;
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
            else if (!(GM_GameStatus & STATE_PADDEMO))
            {
                GM_Vitality = 0;
                GM_GameOver();
                GM_GameOverTimer = -1;
                work->dead = 1;
                GM_SeSet(NULL, 0x1A);
                GM_GameStatus |= STATE_PADRELEASE;
            }
            else
            {
                GM_Vitality = 1;
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

        if ((work->blink & 3) == 1)
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
    else if (GM_GameStatus & STATE_PADDEMO)
    {
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
    }
}

void JeepSnakeInitTarget(Work *work)
{
    TARGET *target;
    int     vitality;

    target = work->target;
    vitality = GM_Vitality;

    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, PLAYER_SIDE, &jeep_sne_target_size);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, vitality, 0, &DG_ZeroVector);
    target->map = work->root_ctrl->map->index;
}

static int GetResources(Work *work, int name)
{
    CONTROL *control;
    OBJECT  *body;
    OBJECT  *weapon;

    control = &work->control;
    if (GM_InitControl(control, name, work->root_ctrl->map->index) < 0)
    {
        return -1;
    }

    work->control.mov = work->root_ctrl->mov;
    work->control.rot = work->root_ctrl->rot;

    GM_ConfigControlInterp(control, 4);
    GM_ConfigControlHazard(control, 750, 450, 450);
    GM_ConfigControlAttribute(control, RADAR_VISIBLE);

    GM_PlayerStatus = 0;

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject(body, BODY_DATA, BODY_FLAG, MOTION_DATA);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots);

    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ConfigMotionAdjust(body, work->adjust);

    GM_InitObject(weapon, WEAPON_DATA, WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);

    work->target = GM_AllocTarget();

    JeepSnakeInitTarget(work);

    control->r_sphere = -2;

    GM_PlayerBody = body;
    GM_PlayerControl = control;

    work->vitality = GM_Vitality;

    Takabe_JeepSystem.snake_body = body;
    work->pos = Takabe_JeepSystem.control->mov;
    return 0;
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->weapon);
    GM_FreeObject(&work->body);
    GM_PlayerControl = NULL;
    GM_PlayerBody = NULL;
}

void *NewJeepSnake(CONTROL *root_ctrl, MATRIX *root_mat)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "jeep_sne.c");

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
    MATRIX  world;
    DG_OBJ *dobj;

    dobj = &work->body.objs->objs[obj];
    DG_SetPos(&dobj->world);
    DG_MovePos(&jeep_sne_blood_pos);
    DG_RotatePos(&jeep_sne_blood_rot);
    ReadRotMatrix(&world);
    if (Takabe_JeepSystem.field_78 == 0)
    {
        NewBlood(&world, count);
    }
    else
    {
        NewJeepBlood(&world, count, dobj);
    }
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

        NewPadVibration(jeep_sne_vib_damage1, 1);
        NewPadVibration(jeep_sne_vib_damage2, 2);
        return 1;
    }

    return 0;
}

/* NON_MATCHING: same behaviour, but gcc lays the shared `return 0` block out
   after the end of the function instead of between the two tests */
#if 0
static int CheckDamage2(Work *work)
{
    if (CheckDamage(work))
    {
        work->target->class = TARGET_AVAIL;
        work->blink = 4;
        work->aim_dir += GV_RandS(512);
        return 1;
    }

    if (work->blink != 0 || !(work->pad_flags & 8))
    {
        return 0;
    }

    work->action = StateHit;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;

    NewPadVibration(jeep_sne_vib_damage1, 1);
    NewPadVibration(jeep_sne_vib_damage2, 2);
    work->aim_dir += GV_RandS(256);
    return 1;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jlamp2_800D519C.s")
int s19b_jlamp2_800D519C(Work *work); // CheckDamage2

void Shoot(Work *work)
{
    MATRIX  world;
    SVECTOR pos;
    long    flag;

    RotMatrix(&jeep_sne_bullet_rot, &world);
    MulMatrix0(&work->gun_world, &world, &world);
    DG_SetPos(&work->gun_world);
    RotTrans(&jeep_sne_bullet_pos, (VECTOR *)world.t, &flag);
    NewJeepBullet(&world, 1, 1, 0);

    pos.vx = world.t[0];
    pos.vy = world.t[1];
    pos.vz = world.t[2];
    if (Takabe_JeepSystem.field_78 == 0)
    {
        GM_SeSet(&pos, 0x2E);
        AN_FamasFlash(&world);
    }
    else
    {
        GM_SeSet(&pos, 0x2E);
        s19b_jblood_800C8070(&world);
    }
}

static void StateNormal(Work *work, int time)
{
    int flags;

    flags = work->pad_flags;

    if (s19b_jlamp2_800D519C(work))
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
        Takabe_JeepSystem.flags |= 1;

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

void StateHit(Work *work, int time)
{
    if (CheckDamage(work))
    {
        work->target->class = TARGET_AVAIL;
        work->blink = 4;
        work->aim_dir += GV_RandS(512);
        return;
    }

    if (time == 0)
    {
        SetMotion(work, 8);
        GM_SeSet(&work->control.mov, 0x88);
    }

    if (time >= 21)
    {
        work->action = StateNormal;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        SetMotion(work, 0);
    }
}

static void StateDead(Work *work, int time)
{
    if (time == 0)
    {
        SetMotion(work, 4);
        Voicesys_800CE310();
        Voicesys_800CE5F8(15, 1);
        Voicesys_800CE734();
    }

    if (time == 61)
    {
        NewPadVibration(jeep_sne_vib_dead1, 1);
        NewPadVibration(jeep_sne_vib_dead2, 2);
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

    if (GM_GameStatus & STATE_PADDEMO)
    {
        work->target->class = TARGET_AVAIL;
    }
}

/* pad input: aims and shoots the jeep's gun */
static void Input(Work *work)
{
    SVECTOR  gun_pos;
    MATRIX   rotm;
    SVECTOR  vec;
    SVECTOR  ofs;
    MATRIX   world;
    SVECTOR  rot;
    SVECTOR  sv;
    VECTOR   sq;
    int      status;
    int      dy;
    int      yaw;
    int      pitch;
    int      dx;
    int      first;
    int      limit;
    int      flags;
    DG_OBJS *objs;
    MATRIX  *mtx;
    int      ang;
    int      ang2;
    int      rel;

    dx = 0;
    dy = 0;
    work->pad_flags = 0;

    if (work->dead == 0)
    {
        status = GV_PadData[0].status;

        if (GV_PadData[0].analog == 2)
        {
            dy = GV_PadData[0].left_dy;
            dx = GV_PadData[0].left_dx;

            if (dx >= 128)
            {
                dx -= 192;
                if (dx < 0)
                {
                    dx = 0;
                }
            }
            else
            {
                dx -= 64;
                if (dx > 0)
                {
                    dx = 0;
                }
            }

            if (dy >= 128)
            {
                dy -= 192;
                if (dy < 0)
                {
                    dy = 0;
                }
            }
            else
            {
                dy -= 64;
                if (dy > 0)
                {
                    dy = 0;
                }
            }

            dx *= 2;
            dy *= 2;
        }

        if (dx == 0 && dy == 0)
        {
            if (status & PAD_LEFT)
            {
                dx = -128;
            }

            if (status & PAD_RIGHT)
            {
                dx = 127;
            }

            if (status & PAD_UP)
            {
                dy = -128;
            }

            if (status & PAD_DOWN)
            {
                dy = 127;
            }
        }

        if (GM_PlayerStatus & PLAYER_WATCH)
        {
            GM_CheckShukanReverse((unsigned short *)&status);
            dy += 128;
            GM_CheckShukanReverseAnalog((unsigned char *)&dy);
            dy -= 128;
        }
    }
    else
    {
        status = 0;
        dy = 0;
    }

    first = GM_Camera.first_person;
    if (first == 0)
    {
        if (jeep_sne_counter > 0)
        {
            jeep_sne_counter--;
        }

        limit = 18;
    }
    else
    {
        if (jeep_sne_counter < 15)
        {
            jeep_sne_counter++;
        }

        limit = 13;
    }

    if (jeep_sne_counter < limit)
    {
        work->hide = 0;
    }
    else
    {
        work->hide = 1;
    }

    if (Takabe_JeepSystem.flags & 0xFFFF0000)
    {
        if (Takabe_JeepSystem.flags & 0x10000)
        {
            work->gun_rot.vy = 0;
        }
        else if (Takabe_JeepSystem.flags & 0x20000)
        {
            work->gun_rot.vy = 0x800;
            work->aim_dir = 0x800;
        }
        else if (Takabe_JeepSystem.flags & 0x40000)
        {
            rel = work->gun_rot.vy;
            rel = (rel - 0x400) & 0xFFF;
            if (rel >= 0x65 && rel < 0x800)
            {
                dx = -128;
                status |= PAD_LEFT;
            }
            else if (rel >= 0x800 && rel < 0xFA0)
            {
                dx = 128;
                status |= PAD_RIGHT;
            }

            status |= PAD_SQUARE;
        }
    }

    gun_pos = jeep_sne_gun_pos;
    work->world_rot.vy = (work->gun_rot.vy + work->root_ctrl->rot.vy) & 0xFFF;
    DG_SetPos2(&gun_pos, &work->gun_rot);
    RotMatrixZYX(&work->gun_rot, &rotm);
    rotm.t[0] = gun_pos.vx;
    rotm.t[1] = gun_pos.vy;
    rotm.t[2] = gun_pos.vz;
    CompMatrix(work->root_mat, &rotm, &work->gun_world);
    GM_ActObject2(&work->weapon);
    work->weapon.objs->world = work->gun_world;

    flags = status;
    if (work->damaged && !work->dead)
    {
        flags &= 0xFFFF0FFF;
        dx = 0;
        dy = 0;

        if (GM_Camera.first_person)
        {
            flags |= 0x10;
        }
        else
        {
            flags &= ~0x10;
        }
    }

    work->aim_dir -= dx / 4;

    if (dx < 0)
    {
        work->pad_flags |= 2;
    }
    else if (dx > 0)
    {
        work->pad_flags |= 4;
    }

    work->gun_rot.vy = GV_NearExp4P(work->gun_rot.vy, work->aim_dir);

    if (first == 1)
    {
        work->aim_pitch = GV_NearExp4P(work->aim_pitch, (dy * 300) / 128);
    }
    else
    {
        work->aim_pitch = GV_NearExp4P(work->aim_pitch, 0);
    }

    if (work->shoot_wait)
    {
        work->shoot_wait--;
    }

    if ((status & PAD_SQUARE) && work->shoot_wait == 0)
    {
        work->shoot_wait = 3;
        work->pad_flags |= 1;
    }

    if (flags & 0x10)
    {
        GM_Camera.first_person = 1;
        GM_PlayerStatus |= PLAYER_WATCH;
    }
    else
    {
        GM_Camera.first_person = 0;
        GM_PlayerStatus &= ~PLAYER_WATCH;
    }

    ofs = jeep_sne_gun_pos;

    if (first == 0)
    {
        GM_PlayerControl->rot = work->world_rot;
        GM_SnakeCamera.rotate2.vy = work->world_rot.vy;
    }
    else
    {
        GM_PlayerControl->rot.vy = work->world_rot.vy;

        mtx = &GM_PlayerBody->objs->objs[6].world;
        sv.vx = mtx->m[0][2];
        sv.vy = 0;
        sv.vz = mtx->m[2][2];
        ang = mtx->m[1][2];
        GM_SnakeCamera.rotate2.vx = work->aim_pitch - ratan2(ang, GV_VecLen3(&sv));
        GM_SnakeCamera.rotate2.vy = work->world_rot.vy;
    }

    rot = GM_PlayerControl->rot;
    rot.vy -= work->root_ctrl->rot.vy;
    DG_SetPos2(&DG_ZeroVector, &rot);
    GV_AddVec3(&jeep_sne_gun_ofs, &work->rot, &vec);
    DG_RotVector(&vec, &vec, 1);
    GV_AddVec3(&vec, &ofs, &vec);
    DG_SetPos2(&vec, &rot);
    ReadRotMatrix(&world);
    CompMatrix(work->root_mat, &world, &GM_PlayerBody->objs->world);

    GM_PlayerControl->mov.vx = work->body.objs->world.t[0];
    GM_PlayerControl->mov.vy = work->body.objs->world.t[1];
    GM_PlayerControl->mov.vz = work->body.objs->world.t[2];

    GM_GetHomingTarget2(&work->weapon.objs->world, work->world_rot.vy, &yaw, &pitch, GM_CurrentMap, 6000, 128);

    objs = GM_PlayerBody->objs;
    sq.vx = objs->world.m[0][2];
    sq.vy = 0;
    sq.vz = objs->world.m[2][2];
    Square0(&sq, &sq);
    ang2 = -ratan2(objs->world.m[1][2], SquareRoot0(sq.vx + sq.vz));

    if (yaw == -1)
    {
        work->gun_rot.vx = GV_NearExp4(work->gun_rot.vx, 0);
        Takabe_JeepSystem.has_homing_target = 0;
    }
    else
    {
        work->gun_rot.vx = GV_NearExp4(work->gun_rot.vx, pitch - ang2);
        Takabe_JeepSystem.has_homing_target = 1;
    }

    if (Takabe_JeepSystem.flags & 2)
    {
        work->pad_flags |= 8;
    }
}


static void PadAndAction(Work *work)
{
    Input(work);
    Takabe_JeepSystem.flags &= 0xFFFF0000;
    ActionMain(work);
}
