#include "mgstype.h"
#include "strcode.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"
#include "takabe/fadeio.h"
#include "linkvar.h"
#include "mgrex.h"

/* Metal Gear REX: main actor functions (the original file name is unknown) */

extern int s17a_dword_800E5E58;
extern GM_SnakeCameraWork GM_SnakeCamera;

void s17a_800DA9DC(MGREX_WORK *work);
void s17a_800DEBB4(MGREX_WORK *work, int action, int arg2);
void s17a_800DECE4(MGREX_WORK *work);
void s17a_800E44C0(MGREX_WORK *work);
void s17a_800E37D4(MGREX_WORK *work, HZD_SEG *segs);
void s17a_800E3B00(MGREX_WORK *work, HZD_SEG *segs);
void s17a_800E32B4(MGREX_WORK *work);
void s17a_800E3C7C(MGREX_WORK *work);
void s17a_800E3BA8(MGREX_WORK *work, int arg1);
void s17a_800DF3E8(MGREX_WORK *work);
void s17a_800DD910(MGREX_WORK *work);
void s17a_800E0328(MGREX_WORK *work);
void s17a_800DFAE8(MGREX_WORK *work);
void s17a_800DFF74(MGREX_WORK *work);
void s17a_800DF720(MGREX_WORK *work);

void MgRex_800DB210(MGREX_WORK *work);
void MgRex_800DB268(MGREX_WORK *work);
void MgRex_800DB478(MGREX_WORK *work);
void MgRex_800DB63C(MGREX_WORK *work);
void MgRex_800DB728(MGREX_WORK *work);
void MgRex_800DB854(MGREX_WORK *work);
void MgRex_800DB85C(MGREX_WORK *work);
void MgRex_800DBC24(MGREX_WORK *work);

void *NewMgSmoke1Offset(MATRIX *world, SVECTOR *offset, int flag, int time);
void *NewMgSmoke2(MATRIX *world, SVECTOR *offset, SVECTOR *dir, int time);
void *NewSpark2L(MATRIX *world);

/* the area REX is allowed to move in (corners of its body) */
SVECTOR mgrex_bounds[6] = {
    { 6000, 0, 6000}, {-6000, 0, 6000}, {-5000, 0, 0},
    {0, 0, -5000}, {-2000, 0, -5000}, {2000, 0, -5000}
};

SVECTOR mgrex_radar_target_size = {1500, 1500, 1500};
SVECTOR mgrex_pit_target_size = {400, 600, 400};
SVECTOR mgrex_radar_offset = {750, 70, 2932};
SVECTOR mgrex_radar_smoke_offset = {750, 70, 3432};
SVECTOR mgrex_pit_smoke_offset = {0, -500, 1000};
int     mgrex_step_se_timer = 0;
SVECTOR mgrex_leg_smoke_offset = {0, -2990, 500};
SVECTOR mgrex_leg_smoke_dir = {0, -600, 300};
SVECTOR mgrex_spark_offset = {0, -2459, 907};

void MgRex_Act(MGREX_WORK *work)
{
    SVECTOR  pos;
    GV_MSG   msg;
    SVECTOR *vec;
    DG_OBJ  *obj;
    int      rot_y;
    int      dist;
    int      min_x, min_z;
    int      max_x, max_z;
    int      i;

    work->frame++;
    work->body_rots[0].vy = work->f176C;
    memset(&work->body_control.step, 0, sizeof(SVECTOR));

    GM_ActMotion(&work->objWaist);
    GM_ActMotion(&work->leg_l);
    GM_ActMotion(&work->leg_r);

    work->leg_r_rots[0] = DG_ZeroVector;
    work->leg_l_rots[0] = work->leg_r_rots[0];

    work->control.step.vy = 0;
    work->control.step.vx = work->body_control.step.vx * 10;
    work->control.step.vz = work->body_control.step.vz * 10;
    work->control.mov.vy = work->objWaist.height * 10;

    GM_ActControl(&work->control);
    GM_ActObject(&work->objWaist);

    DG_GetLightMatrix(&work->control.mov, work->light);
    DG_GetLightMatrix2(&work->control.mov, work->pit_light);

    if (!(GM_GameStatus & STATE_THERMG))
    {
        work->pit_light[0].t[0] = work->light[0].t[0];
        work->pit_light[0].t[1] = work->light[0].t[1];
        work->pit_light[0].t[2] = work->light[0].t[2];
    }

    work->body_rots[7].vx = 0;
    work->body_rots[7].vy = 0;
    work->body_rots[7].vz = 0;
    work->body_rots[8] = work->svectRailGunJointAngle;

    if (work->mode >= 3)
    {
        work->body_rots[3].vx = 170;
        work->body_rots[3].vy = 0;
        work->body_rots[3].vz = 0;
    }

    work->f1A3C = ratan2(work->objWaist.objs->objs[4].world.m[0][2], work->objWaist.objs->objs[4].world.m[2][2]) & 0xFFF;

    switch (work->mode)
    {
    case 0:
        MgRex_800DB63C(work);
        break;

    case 1:
        s17a_800DA9DC(work);
        break;

    case 2:
        MgRex_800DB268(work);
        break;

    case 3:
        MgRex_800DB210(work);
        break;

    case 4:
        MgRex_800DB478(work);
        break;

    case 5:
        MgRex_800DB728(work);
        break;

    case 6:
        MgRex_800DB854(work);
        break;

    case 7:
        break;
    }

    s17a_800DECE4(work);
    s17a_800E44C0(work);
    MgRex_800DBC24(work);

    work->f390 = 0;

    if (work->f1AC4 == work->f1AC0)
    {
        work->f1AC8 = 10;
    }
    else if (--work->f1AC8 < 0)
    {
        work->f1AC0 = GV_NearSpeed(work->f1AC0, work->f1AC4, 64);
    }

    obj = &work->leg_l.objs->objs[8];
    pos.vx = obj->world.t[0];
    pos.vy = obj->world.t[1];
    pos.vz = obj->world.t[2];
    GM_MoveTarget(work->target3, &pos);
    GM_PushTarget(work->target3);

    obj = &work->leg_r.objs->objs[8];
    pos.vx = obj->world.t[0];
    pos.vy = obj->world.t[1];
    pos.vz = obj->world.t[2];
    GM_MoveTarget(work->target4, &pos);
    GM_PushTarget(work->target4);

    MgRex_800DB85C(work);
    s17a_800E37D4(work, work->segs);
    s17a_800E3B00(work, work->segs2);
    s17a_800E32B4(work);

    dist = SquareRoot0((GM_SnakeCamera.position.vx - work->control.mov.vx) * (GM_SnakeCamera.position.vx - work->control.mov.vx) +
                       (GM_SnakeCamera.position.vz - work->control.mov.vz) * (GM_SnakeCamera.position.vz - work->control.mov.vz));

    if (work->f1AD0 == 0)
    {
        if (dist < 10000 || GM_SnakeCamera.position.vz < work->control.mov.vz || s17a_dword_800E5E30 != 0)
        {
            msg.address = 0xC356;
            msg._len = 2;
            msg.message[0] = 1;
            msg.message[1] = 0xDD2;
            GV_SendMessage(&msg);
            work->f1AD0 = 1;
        }
    }
    else if (dist > 12000 && work->control.mov.vz + 2000 < GM_SnakeCamera.position.vz && s17a_dword_800E5E30 == 0)
    {
        msg.address = 0xC356;
        msg._len = 2;
        msg.message[0] = 1;
        msg.message[1] = HASH_LEAVE;
        GV_SendMessage(&msg);
        work->f1AD0 = 0;
    }

    if (s17a_dword_800E5E30 != 0)
    {
        s17a_dword_800E5E30--;
    }

    rot_y = work->body_rots[0].vy;
    work->f176C = rot_y;
    RotMatrixY(rot_y, &work->objWaist.objs->world);

    vec = (SVECTOR *)getScratchAddr(0);
    work->body_rots[0].vy = 0;
    DG_SetPos(&work->objWaist.objs->world);

    DG_PutVector(mgrex_bounds, vec, 6);

    min_x = min_z = 32000;
    for (i = 6; i > 0; i--)
    {
        min_x = MIN(min_x, vec->vx);
        min_z = MIN(min_z, vec->vz);
        vec++;
    }

    vec = (SVECTOR *)getScratchAddr(0);
    max_x = max_z = -32000;
    for (i = 6; i > 0; i--)
    {
        max_x = MAX(max_x, vec->vx);
        max_z = MAX(max_z, vec->vz);
        vec++;
    }

    if (min_x < -13000)
    {
        work->control.mov.vx += -13000 - min_x;
    }

    if (min_z < -25000)
    {
        work->control.mov.vz += -25000 - min_z;
    }

    if (max_x > 13000)
    {
        work->control.mov.vx += 13000 - max_x;
    }

    if (max_z > 25000)
    {
        work->control.mov.vz += 25000 - max_z;
    }
}

void MgRex_Die(MGREX_WORK *work)
{
    int i;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->objWaist);
    GM_FreeObject(&work->leg_l);
    GM_FreeObject(&work->leg_r);
    GM_FreeControl(&work->control2);
    GM_FreeObject((OBJECT *)&work->objCockpit);
    GM_FreeObject((OBJECT *)&work->pit_u);
    GM_FreeObject(&work->objCockpit2);
    GM_FreeObject((OBJECT *)&work->radar);
    GM_FreeObject((OBJECT *)&work->hatch_l);
    GM_FreeObject((OBJECT *)&work->hatch_r);

    work->objWaist.objs->objs[3].model->ty = work->f1A9C;

    GM_FreeTarget(work->target3);
    GM_FreeTarget(work->target4);

    if (work->segs)
    {
        for (i = 0; i < 45; i++)
        {
            HZD_DequeueDynamicSegment(work->control.map->hzd, &work->segs[i]);
        }

        GV_Free(work->segs);
        work->segs = NULL;
    }

    mgrex_saved = *work;
}

void s17a_800DA9DC(MGREX_WORK *work)
{
    SVECTOR pos;

    if (--work->timers[0] < 0) work->timers[0] = 0;
    if (--work->timers[1] < 0) work->timers[1] = 0;
    if (--work->timers[2] < 0) work->timers[2] = 0;
    if (--work->timers[3] < 0) work->timers[3] = 0;
    if (--work->timers[4] < 0) work->timers[4] = 0;
    if (--work->timers[5] < 0) work->timers[5] = 0;
    if (--work->timers[6] < 0) work->timers[6] = 0;
    if (--work->timers[7] < 0) work->timers[7] = 0;

    s17a_800E3C7C(work);

    switch (work->f1980)
    {
    case 0:
        work->f6FC = 1;
        s17a_800DD910(work);
        break;

    case 1:
        if (work->f1988 == 0 || GM_GameLevel <= 0)
        {
            work->f6FC = 1;
            s17a_800DD910(work);
            break;
        }

        s17a_800DF3E8(work);

        switch (work->f6FC)
        {
        case 2:
            s17a_800DD910(work);
            break;

        case 3:
            s17a_800E0328(work);
            break;

        case 4:
            s17a_800DFAE8(work);
            break;

        case 5:
            s17a_800DFF74(work);
            break;

        case 6:
            s17a_800DF720(work);
            break;

        case 7:
            break;

        default:
            work->f6FC = 2;
            break;
        }
        break;

    case 2:
        s17a_800DF3E8(work);

        switch (work->f6FC)
        {
        case 2:
            s17a_800DD910(work);
            break;

        case 3:
            s17a_800E0328(work);
            break;

        case 4:
            s17a_800DFAE8(work);
            break;

        case 5:
            s17a_800DFF74(work);
            break;

        case 6:
            s17a_800DF720(work);
            break;

        case 7:
            break;

        default:
            work->f6FC = 2;
            break;
        }
        break;
    }

    if (work->f720 == 0 && work->f5BC > 0 && work->target_a == NULL)
    {
        work->target_a = GM_AllocTarget();
        GM_SetTarget(work->target_a, TARGET_POWER | TARGET_SEEK | TARGET_TOUCH, ENEMY_SIDE, &mgrex_radar_target_size);
        GM_SetPowerTarget(work->target_a, POWER_DECREASE, -1, work->f5BC, 0, &DG_ZeroVector);
        GM_InitControl(&work->ctrl_a, work->name, work->where);
        GM_ConfigControlAttribute(&work->ctrl_a, 1);
    }

    if (work->f720 == 0 && work->f5BC <= 0 && work->target_a == NULL && work->f5C4 > 0 && work->target_b == NULL)
    {
        work->target_b = GM_AllocTarget();
        GM_SetTarget(work->target_b, TARGET_POWER | TARGET_SEEK | TARGET_TOUCH, ENEMY_SIDE, &mgrex_pit_target_size);
        GM_SetPowerTarget(work->target_b, POWER_DECREASE, -1, work->f5C4, 0, &DG_ZeroVector);
        GM_InitControl(&work->ctrl_b, work->name, work->where);
        GM_ConfigControlAttribute(&work->ctrl_b, 1);
    }

    if (work->target_a)
    {
        DG_SetPos(&work->objWaist.objs->objs[6].world);
        DG_PutVector(&mgrex_radar_offset, &pos, 1);
        GM_MoveTarget(work->target_a, &pos);
        work->ctrl_a.mov = pos;

        if (work->target_a->damaged)
        {
            work->target_a->damaged = 0;
            work->timers[5] = work->f5C0;
            s17a_800E3BA8(work, 2);
            work->player_pos = GM_PlayerControl->mov;
            GM_SeSetPan(&pos, 176, 63);
            work->f1968 = 60;
            NewMgSmoke1Offset(&work->objWaist.objs->objs[6].world, &mgrex_radar_smoke_offset, 1, 90);

        }

        work->f1AC4 = work->f5BC = work->target_a->vital;
        if (work->f1AC4 < 0)
        {
            work->f1AC4 = 0;
        }

        if (work->f5BC <= 0)
        {
            GM_FreeControl(&work->ctrl_a);
            GM_FreeTarget(work->target_a);
            work->target_a = NULL;

            GM_FreeObject((OBJECT *)&work->radar);
            GM_InitObjectNoRots(&work->radar, GV_StrCode("radar_f2"), 0x15D, 0);
            GM_ConfigObjectLight((OBJECT *)&work->radar, work->light);
            GM_ConfigObjectRoot((OBJECT *)&work->radar, &work->objWaist, 6);

            if (work->target_c)
            {
                GM_FreeControl(&work->ctrl_c);
                GM_FreeTarget(work->target_c);
                work->target_c = NULL;
            }

            work->f720 = 2;
        }
        else
        {
            if (work->f1968)
            {
                work->target_a->class = TARGET_AVAIL;
                work->f1968--;
            }
            else
            {
                work->target_a->class = TARGET_POWER | TARGET_SEEK;
            }
        }
    }

    if (work->target_b)
    {
        pos.vx = work->objCockpit2.objs->objs[1].world.t[0];
        pos.vy = work->objCockpit2.objs->objs[1].world.t[1];
        pos.vz = work->objCockpit2.objs->objs[1].world.t[2];
        GM_MoveTarget(work->target_b, &pos);
        work->ctrl_b.mov = pos;

        if (work->target_b->damaged)
        {
            work->target_b->damaged = 0;
            work->timers[6] = work->f5C8;
            s17a_800E3BA8(work, 2);
            work->player_pos = GM_PlayerControl->mov;
            GM_SeSetMode(&pos, 190, GM_SEMODE_BOMB);
            GM_SeSetMode(&pos, 130, GM_SEMODE_BOMB);
            work->f1968 = 60;
            NewMgSmoke1Offset(&work->objCockpit2.objs->objs[1].world, &mgrex_pit_smoke_offset, 1, 90);

        }

        work->f1AC4 = work->f5C4 = work->target_b->vital;
        if (work->f1AC4 < 0)
        {
            work->f1AC4 = 0;
        }

        if (work->f5C4 <= 0)
        {
            GM_FreeControl(&work->ctrl_b);
            GM_FreeTarget(work->target_b);
            work->target_b = NULL;

            if (work->target_c)
            {
                GM_FreeControl(&work->ctrl_c);
                GM_FreeTarget(work->target_c);
                work->target_c = NULL;
            }

            work->f720 = 1;
        }
        else
        {
            if (work->f1968)
            {
                work->target_b->class = TARGET_AVAIL;
                work->f1968--;
            }
            else
            {
                work->target_b->class = TARGET_POWER | TARGET_SEEK;
            }
        }
    }

    MENU_DrawBar2(28, (work->f1AC0 * 1500) / work->f1ABC, (work->f1AC4 * 1500) / work->f1ABC, 1500, &work->life_bar);

    if (work->f720 == 1 || work->f720 == 2)
    {
        work->f724 = 0;
        work->f1AA8 = 0;
        work->mode++;
        GM_ConfigControlAttribute(&work->control2, 1);
        THING_Msg_SendMessage(0x3B49, HASH_STOP);
        NewFadeInOut(FADEIO_MODE_TOWHITE, 30);
    }
}

void MgRex_800DB210(MGREX_WORK *work)
{
    if (work->frame < 5)
    {
        work->player_pos = GM_PlayerPosition;
    }

    s17a_800DA9DC(work);
}

void MgRex_800DB268(MGREX_WORK *work)
{
    work->f724 = -1;

    if (work->f1960)
    {
        s17a_800DEBB4(work, 2, 0);
    }

    work->f198C.vx = GV_NearExp8(work->f198C.vx, GV_RandS(128));
    work->f198C.vy = GV_NearExp8(work->f198C.vy, GV_RandS(128));

    MENU_DrawBar2(28, (work->f1AC0 * 1500) / work->f1ABC, (work->f1AC4 * 1500) / work->f1ABC, 1500, &work->life_bar);

    GM_GameStatus |= STATE_JAMMING;

    if (++work->f1AA8 > 32)
    {
        if (GM_GameOverTimer != 0)
        {
            s17a_800DEBB4(work, 0, 0);
            return;
        }

        THING_Msg_SendMessage(0x62FE, 0x71F1);
        THING_Msg_SendMessage(0x7169, HASH_KILL);

        work->f720 = 0;
        mgrex_saved = *work;
        GV_DestroyActor(work);

        GM_GameStatus &= ~STATE_JAMMING;
        GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
        GCL_ExecProc(work->f1764, NULL);
    }
}

void MgRex_800DB478(MGREX_WORK *work)
{
    work->f724 = -1;

    if (work->f1960)
    {
        s17a_800DEBB4(work, 11, 0);
    }

    MENU_DrawBar2(28, (work->f1AC0 * 1500) / work->f1ABC, (work->f1AC4 * 1500) / work->f1ABC, 1500, &work->life_bar);

    if (++work->f1AA8 >= 40)
    {
        if (GM_GameOverTimer != 0)
        {
            s17a_800DEBB4(work, 0, 0);
            return;
        }

        THING_Msg_SendMessage(0x62FE, 0x71F1);
        THING_Msg_SendMessage(0x7169, HASH_KILL);

        work->f720 = 0;
        mgrex_saved = *work;
        GV_DestroyActor(work);

        GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
        GCL_ExecProc(work->f1768, NULL);
    }
}

void MgRex_800DB63C(MGREX_WORK *work)
{
    SVECTOR pos;

    if (work->frame > 300)
    {
        work->player_pos = GM_PlayerPosition;
        work->mode = 1;
    }

    if (work->frame == 180)
    {
        s17a_800DEBB4(work, 0, 0);
    }
    else if (work->frame == 270)
    {
        pos.vx = work->objWaist.objs->objs[3].world.t[0];
        pos.vy = work->objWaist.objs->objs[3].world.t[1];
        pos.vz = work->objWaist.objs->objs[3].world.t[2];
        GM_SeSetPan(&pos, 177, 63);
    }

    if (work->frame == 120)
    {
        GM_SeSetMode(&work->control.mov, 179, GM_SEMODE_BOMB);
    }
}

void MgRex_800DB728(MGREX_WORK *work)
{
    SVECTOR  pos;
    GV_MSG  *msg;
    int      n_msgs;

    if (work->target_b == NULL)
    {
        work->target_b = GM_AllocTarget();
        pos.vx = 400;
        pos.vy = 600;
        pos.vz = 400;
        GM_SetTarget(work->target_b, TARGET_POWER | TARGET_SEEK | TARGET_TOUCH, ENEMY_SIDE, &pos);
        GM_SetPowerTarget(work->target_b, POWER_DECREASE, -1, work->f5C4, 0, &DG_ZeroVector);
    }

    pos.vx = work->objCockpit2.objs->objs[1].world.t[0];
    pos.vy = work->objCockpit2.objs->objs[1].world.t[1];
    pos.vz = work->objCockpit2.objs->objs[1].world.t[2];
    GM_MoveTarget(work->target_b, &pos);

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; msg++, n_msgs--)
    {
        if (msg->message[0] == HASH_KILL)
        {
            GM_FreeTarget(work->target_b);
            GV_DestroyActor(work);
            return;
        }
    }
}

void MgRex_800DB854(MGREX_WORK *work)
{
}

void MgRex_800DB85C(MGREX_WORK *work)
{
    SVECTOR  pos;
    SVECTOR  pos2;
    DG_OBJ  *foot;
    DG_OBJ  *obj;
    int      flags;
    int      play;
    int      se;

    flags = work->f1ACC;
    foot = &work->leg_l.objs->objs[8];

    if (flags & 1)
    {
        if (foot->world.t[1] >= 751)
        {
            work->f1ACC = flags & ~1;
        }
    }
    else if (foot->world.t[1] < 751)
    {
        work->f1ACC = flags | 1;

        pos.vx = foot->world.t[0];
        pos.vy = foot->world.t[1];
        pos.vz = foot->world.t[2];

        GM_SeSetMode(&pos, (work->f1950 == 7 || work->f1950 == 9) ? 192 : 184, GM_SEMODE_BOMB);

        pos.vy = -32000;
        GM_SetNoise(255, 16, &pos);
    }

    foot = &work->leg_r.objs->objs[8];

    if (flags & 2)
    {
        if (foot->world.t[1] >= 751)
        {
            work->f1ACC &= ~2;
        }
    }
    else if (foot->world.t[1] < 751)
    {
        work->f1ACC |= 2;

        pos2.vx = foot->world.t[0];
        pos2.vy = foot->world.t[1];
        pos2.vz = foot->world.t[2];

        if (work->f1950 == 8 || work->f1950 == 9)
        {
            se = 192;
        }
        else
        {
            se = 184;
        }

        GM_SeSetMode(&pos2, se, GM_SEMODE_BOMB);

        pos2.vy = -32000;
        GM_SetNoise(255, 16, &pos2);
    }

    obj = NULL;
    play = 0;

    if (work->leg_l.action2 == 45)
    {
        if (work->leg_l.m_ctrl->info2.frame == 0)
        {
            play = 1;
            obj = &work->leg_l.objs->objs[12];
        }

        if (work->leg_l.m_ctrl->info2.frame == 5)
        {
            play = 1;
            obj = &work->leg_l.objs->objs[10];
        }
    }

    if (work->leg_r.action2 == 46)
    {
        if (work->leg_r.m_ctrl->info2.frame == 0)
        {
            play = 1;
            obj = &work->leg_r.objs->objs[12];
        }

        if (work->leg_r.m_ctrl->info2.frame == 5)
        {
            play = 1;
            obj = &work->leg_r.objs->objs[10];
        }
    }

    if (play)
    {
        pos.vx = obj->world.t[0];
        pos.vy = obj->world.t[1];
        pos.vz = obj->world.t[2];
        GM_SeSetMode(&pos, 198, GM_SEMODE_BOMB);
    }

    if (work->mode < 3 && (work->f1ACC & 4) && work->f1980 != 2)
    {
        work->f1ACC &= ~4;

        mgrex_step_se_timer += GV_PassageTime;
        if (mgrex_step_se_timer >= 6)
        {
            pos.vx = work->objWaist.objs->objs[6].world.t[0];
            pos.vy = work->objWaist.objs->objs[6].world.t[1];
            pos.vz = work->objWaist.objs->objs[6].world.t[2];
            mgrex_step_se_timer = 0;
            GM_SeSetMode(&pos, 199, GM_SEMODE_BOMB);
        }
    }
}

void MgRex_800DBC24(MGREX_WORK *work)
{
    MATRIX world;
    MATRIX rot;

    if (work->objWaist.action == 48 && work->objWaist.m_ctrl->info1.frame == 59)
    {
        NewMgSmoke2(&work->leg_l.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 30);
        NewMgSmoke2(&work->leg_r.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 30);
    }

    if (work->objWaist.action == 12 && work->objWaist.m_ctrl->info1.frame == 18)
    {
        NewMgSmoke2(&work->leg_l.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 8);
        NewMgSmoke2(&work->leg_r.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 8);
    }

    if (work->objWaist.action == 9 && work->objWaist.m_ctrl->info1.frame == 24)
    {
        NewMgSmoke2(&work->leg_l.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 10);
        NewMgSmoke2(&work->leg_r.objs->objs[7].world, &mgrex_leg_smoke_offset, &mgrex_leg_smoke_dir, 10);
    }

    if (work->leg_l.action == 13)
    {
        if (work->leg_l.m_ctrl->info1.frame >= 25)
        {
            s17a_dword_800E5E58 = (s17a_dword_800E5E58 + 1) & 1;
            if (s17a_dword_800E5E58 == 1)
            {
                DG_SetPos(&work->leg_l.objs->objs[10].world);
            }
            else
            {
                DG_SetPos(&work->leg_l.objs->objs[12].world);
            }

            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-200, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);
        }

        if (work->f1A64 == 25)
        {
            DG_SetPos(&work->leg_l.objs->objs[10].world);
            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-800, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);

            DG_SetPos(&work->leg_l.objs->objs[12].world);
            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-800, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);
        }
    }

    if (work->leg_r.action == 14)
    {
        if (work->leg_r.m_ctrl->info1.frame >= 25)
        {
            s17a_dword_800E5E58 = (s17a_dword_800E5E58 + 1) & 1;
            if (s17a_dword_800E5E58)
            {
                DG_SetPos(&work->leg_r.objs->objs[10].world);
            }
            else
            {
                DG_SetPos(&work->leg_r.objs->objs[12].world);
            }

            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-200, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);
        }

        if (work->f1A64 == 25)
        {
            DG_SetPos(&work->leg_r.objs->objs[10].world);
            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-800, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);

            DG_SetPos(&work->leg_r.objs->objs[12].world);
            DG_MovePos(&mgrex_spark_offset);
            ReadRotMatrix(&world);
            rot = DG_ZeroMatrix;
            RotMatrixX(-800, &rot);
            MulMatrix(&world, &rot);
            NewSpark2L(&world);
        }
    }
}
