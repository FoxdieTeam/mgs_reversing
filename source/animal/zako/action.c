#include "zako.h"

#include <stdio.h>
#include "bullet/tenage.h"

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO_ATTACK_SIZE = {400, 500, 400};
SVECTOR ZAKO_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO_TOUCH_FORCE = {0, 0, 0};

short ActionTable[] = {
    0x0013, 0x0014, 0x000A, 0x0016, 0x0009, 0x0022, 0x0023, 0x0024,
    0x002D, 0x000D, 0x000C, 0x001A, 0x000F, 0x000E, 0x0010, 0x001B,
    0x0008, 0x0015, 0x001E, 0x001F, 0x0020, 0x0021, 0x0025, 0x0019,
    0x0005, 0x0002, 0x002A, 0x0004, 0x0027, 0x0028, 0x0006, 0x0007,
    0x0026, 0x0003, 0x0029, 0x0011, 0x0012, 0x002B, 0x0017, 0x0018,
    0x001C, 0x001D, 0x0000, 0x0001, 0x0033, 0x0011, 0x0012, 0x002B,
    0x0016
};

/*---------------------------------------------------------------------------*/

static void s03d_800D0324( Work *work, int time );

static SVECTOR ThrowPos = {4250, 250, 500};
static SVECTOR ThrowPos2 = {4250, 250, 500};
static SVECTOR ThrowStep = {0, 50, 200};
static SVECTOR s03d_dword_800C3A5C = {-150, 0, 300};

/*---------------------------------------------------------------------------*/

int s03d_800CD61C(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & TARGET_CAPTURE)
    {
        if (t->a_mode == 0x24)
        {
            SetMode( work, s03d_800CEE3C );
            t->damaged = 0;
        }
        else
        {
            SetMode( work, s03d_800CF194 );
            t->damaged = 0;
        }
        return 1;
    }
    return 0;
}

int Zako_800CD6A8(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & 4)
    {
        if (t->a_mode == 1)
        {
            t->force = DG_ZeroVector;
            if (t->vital <= 0)
            {
                return 1;
            }
        }
        t->damage = 0;
        t->damaged = 0;
    }
    return 0;
}

int Zako_800CD720(SVECTOR *vec)
{
    int x = vec->vx;
    int y = vec->vy;
    int z = vec->vz;

    return ABS(x) + ABS(y) + ABS(z);
}

int s03d_800CD75C( Work *work )
{
    TARGET *trg;

    trg = work->target;
    if ( !(trg->damaged & TARGET_POWER) ) return 0;

    switch ( trg->a_mode )
    {
    case 3:
        trg->force = DG_ZeroVector;
        if ( trg->faint <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, s03d_800CFB04 );
        }
        else
        {
            SetMode( work, s03d_800CFA04 );
        }
        break;
    case 4:
        work->act.field_14 = 0;
        SetMode( work, s03d_800CFB04 );
        break;
    case 1:
        trg->force = DG_ZeroVector;
        if ( trg->vital <= 0 )
        {
            if ( trg->vital != ( work->vital_prev - 64 ) )
            {
                work->in_grip = 1;
                printf(" meryl KILLED !!! \n");
            }
            else
            {
                printf(" SNAKE KILLED !!! \n");
            }

            work->act.field_14 = 1;
            SetMode( work, s03d_800CFB04 );
        }
        else
        {
            SetMode( work, s03d_800CFA04 );
        }
        break;
    case 2:
        if ( Zako_800CD720( &trg->force ) < 100 )
        {
            work->act.field_14 = 3;
        }
        else
        {
            work->act.field_14 = 2;
        }

        SetMode( work, s03d_800CFB04 );
        break;
    case 5:
        work->act.field_14 = 3;
        SetMode( work, s03d_800CFB04 );
        break;
    case 8:
        SetMode( work, s03d_800CF4D4 );
        break;
    case 9:
        SetMode( work, s03d_800CF548 );
        break;
    }

    trg->damage = 0;
    trg->damaged = 0;
    return 1;
}

int s03d_800CD984(Work *work)
{
    if (work->control.mov.vx < 0x1194)
    {
        return 0;
    }
    if (work->control.mov.vz >= 0xBB9 || !(GM_GameStatus & 2))
    {
        return 0;
    }

    SetMode( work, s03d_800CF548 );
    return 1;
}

int Zako_800CDA04(Work *work)
{
    int a = s03d_800CD61C(work);
    int b = s03d_800CD75C(work);
    int c = s03d_800CD984(work);

    if (a | b | c)
    {
        work->target->class = 1;
        return 1;
    }
    return 0;
}

void Zako_800CDA70(Work *work)
{
    TARGET *t = work->target;
    int     b14 = work->param.life;
    int     b16 = work->param.faint;

    GM_SetTarget(t, TARGET_FLAG, 2, &ZAKO_TARGET_SIZE);
    GM_SetPowerTarget(t, 1, -1, b14, b16, &ZAKO_TARGET_FORCE);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_SetC4Target(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->attack, 4, 1, &ZAKO_ATTACK_SIZE);
    GM_SetPowerTarget(&work->attack, 7, 5, 0, 3, &ZAKO_ATTACK_FORCE);
}

void s03d_800CDB5C( Work *work )
{
    CONTROL *control;
    int z;
    HZD_ZON *zone;

    control = &work->control;

    work->n_dead = ZAKOSetDead();
    work->visible = 1;

    GM_ConfigControlAttribute( control, RADAR_ALL_MAP | RADAR_SIGHT | RADAR_VISIBLE );
    Zako_800CDA70( work );

    if ( ZAKO_GameFlag < 4 )
    {
        z = work->param.index * 2 + 25;
        printf( "aaa reset wait zone id = %d z=%d\n", work->param.index, z );
    }
    else
    {
        z = ZAKOCommand.zones[ work->param.index % 2 ];
        printf( "bbb reset fight zone id = %d z=%d\n", work->param.index, z );
    }

    zone = HZD_GetZone( control->map->hzd, z );
    control->mov.vx = zone->x;
    control->mov.vy = zone->y + 1000;
    control->mov.vz = zone->z;

    if ( work->param.index == 2 )
    {
        control->mov.vz += 500;
    }

    control->map = GM_GetMap( work->start_map );
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->next_node = work->n_nodes - 1;
    work->target_addr = work->start_addr;
    work->target_pos = work->start_pos;
    work->vision.range = 512;
    work->vision.length = 4000;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.mode = 1;
    work->in_grip = 0;
    work->target_map = work->start_map;
    work->next_pos = work->start_pos;
    work->last_addr = work->next_addr = work->start_addr;
}

int Zako_800CDD40(int from, int to)
{
    int dir;

    if (to < 0)
    {
        return 0;
    }
    if (from < 0)
    {
        return 0;
    }
    dir = GV_DiffDirS(from, to);
    if ((unsigned int)(dir + 0x380) >= 0x701)
    {
        return 0;
    }
    if (dir >= 0)
    {
        return 1;
    }
    return 2;
}

void Zako_800CDD94(Work *work)
{
    int diff;
    int v;

    diff = GM_PlayerBody->objs->objs[6].world.t[1] -
           work->body.objs->objs[6].world.t[1];
    v = GV_NearExp8(work->adjust[2].vx, (ratan2(work->sn_dis, diff) & 0xFFF) - 0x400);
    work->adjust[2].vx = v;
    work->adjust[6].vx = v;
    if (v < 0)
    {
        work->adjust[7].vx = v * 3;
    }
    else
    {
        work->adjust[7].vx = v * 3 / 2;
    }
}

int s03d_800CDE1C(Work *work)
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift = {-200, 1000, 600};
    SVECTOR force    = {5, 0, 100};
    SVECTOR size     = {400, 1000, 400};

    target = (TARGET *)((char *)work + 0x948);
    GM_SetTarget(target, 4, ENEMY_SIDE, &size);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_RotVector(&force, &svec, 1);
    GM_SetPowerTarget(target, POWER_ONCE, 2, 32, 1, &svec);
    DG_PutVector(&rp_shift, &target->center, 1);
    return GM_PowerTarget(target);
}

void Zako_800CDF2C(Work *work)
{
    TARGET *t = &work->attack;

    GM_SetPowerTarget(t, 7, 5, 0, 3, &ZAKO_ATTACK_FORCE);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}

int s03d_800CDF94( Work *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetMode2( work, ActOverScoutR );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetMode2( work, ActOverScoutL );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetMode2( work, s03d_800D0754 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s03d_800D07DC );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s03d_800D085C );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s03d_800D08DC );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s03d_800D0958 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s03d_800D09D8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s03d_800CE5B4 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s03d_800CE644 );
        return 1;
    }

    if ( press & ( 0x20000 | 0x10000 ) )
    {
        SetMode( work, s03d_800CE720 );
        work->adjust[ 2 ].vx = 0;
        return 1;
    }

    return 0;
}

void s03d_800CE12C( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;

    if ( ZAKOCommand.field_1C == 0 )
    {
        work->target->class |= TARGET_C4;
    }

    work->vision.length = 4000;

    if ( time == 0 )
    {
        SetAction( work, 0, 4 );
    }

    if ( Zako_800CDA04( work ) || s03d_800CDF94( work ) )
    {
        UnsetMode( work );
        return;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 256 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, 2, 4 );
            }
            else
            {
                SetAction( work, 1, 4 );
            }

            SetMode( work, s03d_800CE318 );
        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = GV_NearExp4P( work->vision.facedir, work->control.rot.vy );
}

void s03d_800CE2C0(Work *work, int arg1)
{
    int dir = GV_DiffDirS(arg1, work->control.rot.vy);

    if (dir > 128)
    {
        dir = 128;
    }
    else if (dir < -128)
    {
        dir = -128;
    }

    work->control.turn.vz = dir;
}

void s03d_800CE318( Work *work, int time )
{
    CONTROL *ctrl;
    SVECTOR *vecs;
    int dir, motion, touches, touch, touch2, size;

    work->target->class |= TARGET_FLAG;

    if ( ZAKOCommand.field_1C == 0 )
    {
        work->target->class |= TARGET_C4;
    }

    work->vision.length = 4000;

    if ( Zako_800CDA04( work ) || s03d_800CDF94( work ) )
    {
        UnsetMode( work );
        return;
    }

    touch = -1;
    ctrl = &work->control;
    vecs = ctrl->vecs;
    dir = work->pad.dir;
    motion = work->act.motion1;

    if ( ( work->pad.mode & 0x1 ) && motion != 2 )
    {
        SetAction( work, 2, 4 );
    }

    if ( dir < 0 )
    {
        SetMode( work, s03d_800CE12C );
        UnsetMode( work );
        return;
    }

    touches = ctrl->n_touches;
    if ( touches > 0 )
    {
        touch = GV_VecDir2( vecs );
        if ( touches > 1 )
        {
            touch2 = GV_VecDir2( &ctrl->vecs[ 1 ] );
            if ( GV_DiffDirAbs( dir, touch2 ) < GV_DiffDirAbs( dir, touch ) )
            {
                touch = touch2;
            }
        }
    }

    if ( dir < 0 )
    {
        SetMode( work, s03d_800CE12C );
        UnsetMode( work );
        return;
    }

    switch ( Zako_800CDD40( dir, touch ) )
    {
    case 1:
        dir = ( touch - 1024 ) & 4095;
        break;
    case 2:
        dir = ( touch + 1024 ) & 4095;
        break;
    }

    if ( work->body.objs->bound_mode == 0 )
    {
        ctrl->rot.vy = dir;
        ctrl->turn.vy = dir;
    }
    else
    {
        ctrl->turn.vy = dir;
    }

    size = 0;
    if ( motion == 1 )
    {
        size = 50;
    }
    else if ( motion == 2 )
    {
        size = 100;
    }

    ctrl->step.vx = size * rsin( dir ) / 4096;
    ctrl->step.vz = size * rcos( dir ) / 4096;
    s03d_800CE2C0( work, dir );
    work->vision.facedir = GV_NearExp4P( work->vision.facedir, work->control.rot.vy );
}

void s03d_800CE5B4(Work *work, int time)
{
    if (time == 0)
    {
        work->act.field_14 = 3;
        SetAction( work, 31, 4 );
    }

    if (Zako_800CDA04(work) == 0 && work->body.is_end)
    {
        work->pad.tmp = 0;
        SetMode( work, s03d_800CF68C );
    }
}

void s03d_800CE644( Work *work, int time )
{
    CONTROL *control;

    control = &work->control;

    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;

    if ( time == 0 )
    {
        SetAction( work, 16, 4 );
    }

    if ( Zako_800CDA04( work ) ) return;

    if ( work->body.is_end || !(work->pad.press & 0x20) )
    {
        SetMode( work, s03d_800CE12C );
    }
    else
    {
        control->turn.vy = work->sn_dir;
        control->step.vx = 0;
        control->step.vz = 0;
    }
}

void s03d_800CE720( Work *work, int time )
{
    int press;

    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;

    press = work->pad.press;

    if (time == 0)
    {
        if (press & 0x10000)
        {
            SetAction(work, 3, 4);
        }
        else
        {
            SetAction(work, 5, 4);
        }

        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    if (work->param.index != 1 || !(GV_Time & 0x100))
    {
        Zako_800CDD94(work);
    }

    if (Zako_800CDA04(work))
    {
        return;
    }

    if (!(press & 0x30000))
    {
        SetMode(work, s03d_800CE12C);
        return;
    }

    if (press & 0x40000)
    {
        SetModeNoAdjust(work, s03d_800CE8F4);
        return;
    }

    if (press & 0x80000)
    {
        SetModeNoAdjust(work, s03d_800CE9E8);
        return;
    }

    if (press & 0x100000)
    {
        SetModeNoAdjust(work, s03d_800CEB38);
        return;
    }

    if (press & 0x200000)
    {
        SetModeNoAdjust(work, s03d_800CECBC);
        return;
    }

    if (work->param.index != 1 || !(GV_Time & 0x100))
    {
        if (work->pad.dir >= 0)
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    else
    {
        work->control.turn.vy = work->field_B98;
    }

    work->vision.facedir = work->control.rot.vy;
}

void s03d_800CE8F4( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;

    if ( time == 0 )
    {
        if ( work->pad.press & 0x10000 )
        {
            SetAction( work, 4, 0 );
        }
        else
        {
            SetAction( work, 6, 0 );
        }

        ZAKO_SetPutChar( work, GUNSHOOT );
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    if ( work->param.index != 1 || !(GV_Time & 0x100) )
    {
        Zako_800CDD94( work );
    }

    if ( !Zako_800CDA04( work ) )
    {
        SetModeNoAdjust( work, s03d_800CE720 );
    }
}

void s03d_800CE9E8(Work *work, int time)
{
    SVECTOR *rot;
    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;
    if (time == 0)
    {
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    rot = &work->control.rot;
    if (time == 1 || time == 7)
    {
        rot->vy = (*(unsigned short *)&rot->vy - 0x100) & 0xFFF;
    }
    if (time == 3 || time == 5)
    {
        rot->vy = (*(unsigned short *)&rot->vy + 0x100) & 0xFFF;
    }
    if (time == 2 || time == 4 || time == 6)
    {
        SetAction( work, 6, 0 );
        ZAKO_SetPutChar( work, GUNSHOOT );
    }
    Zako_800CDD94(work);
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            SetMode( work, s03d_800CE720 );
        }
        work->control.rot.vy = rot->vy;
    }
}

void s03d_800CEB38( Work *work, int time )
{
    SVECTOR *pos;
    SVECTOR *step;
    SVECTOR *target;
    SVECTOR  out;
    SVECTOR  rot;
    SVECTOR  svec;
    int      dist;

    if (time == 0)
    {
        SetAction(work, 7, 4);
    }

    if (time == 17)
    {
        GM_SeSet(&work->control.mov, 0x2C);
    }

    if (time == 45)
    {
        if (work->param.index == 2)
        {
            pos = &ThrowPos;
        }
        else
        {
            pos = &ThrowPos2;
        }

        target = &work->current_pos;
        dist = GV_DiffVec3(pos, target);
        step = &ThrowStep;
        step->vz = dist / 8;
        GV_SubVec3(target, pos, &svec);
        rot.vx = 0;
        rot.vy = GV_VecDir2(&svec);
        rot.vz = 0;
        DG_SetPos2(pos, &rot);
        DG_RotVector(step, &out, 1);
        NewTenage3(pos, &out, 60, 0, 0x3b88, 0, 0);
    }

    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            SetMode(work, s03d_800CE720);
        }

        work->control.turn.vy = work->pad.dir;
    }
}

void s03d_800CECBC(Work *work, int time)
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;
    if (time == 0)
    {
        SetAction( work, 8, 0 );
    }
    if (time == 3 && s03d_800CDE1C(work))
    {
        GM_SeSet(&work->control.mov, 0x25);
    }
    work->control.turn.vy = work->sn_dir;
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end)
    {
        SetMode( work, s03d_800CE720 );
    }
}

void s03d_800CED94(Work *work, int time)
{
    work->vision.length = 0;
    if (time == 0)
    {
        SetAction( work, 19, 4 );
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    work->target->class |= TARGET_FLAG;
    if (work->body.is_end)
    {
        work->actend = 1;
        SetMode( work, s03d_800CE12C );
    }
}

void s03d_800CEE3C( Work *work, int time )
{
    TARGET  *target;
    CONTROL *ctrl;

    target = work->target;
    ctrl = &work->control;

    work->act.field_1C = 0;

    if (time == 0)
    {
        work->act.field_14 = 6;
        SetAction(work, 27, 4);
    }

    if (time >= 8 && time <= 17)
    {
        Zako_800CDF2C(work);
    }

    if (work->act.motion1 == 27)
    {
        if (time == 22)
        {
            if ((ctrl->mov.vy - ctrl->levels[0]) < 2000)
            {
                GM_SeSet(&ctrl->mov, 0x8D);
                GM_SeSet(&ctrl->mov, 0x33);
                ZAKO_PutBlood(work, 6, 0);
                GM_SetNoise(100, 4, &ctrl->mov);
            }
            else if ((ctrl->mov.vy - ctrl->levels[0]) > 4000)
            {
                work->target->vital = 0;
                GM_SeSet(&ctrl->mov, 0x8E);
            }
        }

        if (work->body.is_end)
        {
            if (ctrl->grounded == 0)
            {
                SetAction(work, 36, 4);
            }
            else
            {
                SetMode(work, s03d_800CF68C);
            }
        }
    }
    else if (ctrl->grounded)
    {
        GM_SeSet(&ctrl->mov, 0x8D);
        GM_SeSet(&ctrl->mov, 0x33);
        GM_SetNoise(100, 4, &ctrl->mov);
        ZAKO_PutBlood(work, 6, 1);

        if (work->target->vital <= 0)
        {
            SetMode(work, s03d_800D01C4);
        }
        else
        {
            SetMode(work, s03d_800CF68C);
        }
    }

    if (time < 24)
    {
        ctrl->turn = *target->field_1C;
    }

    if (time < 22)
    {
        work->control.hzd_height = -32767;
    }
}

void s03d_800CF114(Work *work)
{
    SVECTOR vec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&s03d_dword_800C3A5C, &vec, 1);
    GV_SubVec3(&vec, &work->control.mov, &work->control.step);
}

void s03d_800CF194(Work *work, int time)
{
    TARGET *target;
    int     motion;

    target = work->target;
    motion = work->act.motion1;

    work->act.field_1C = 0;

    if (time == 0)
    {
        work->field_AF6 = target->faint;
        GM_SeSet(&work->control.mov, 0x8F);
    }

    if (work->field_AF6 != target->faint)
    {
        GM_SeSet(&work->control.mov, 0x8F);
        work->field_AF6 = target->faint;
    }

    if (target->damaged & TARGET_POWER)
    {
        ZAKO_PutBlood(work, 5, 0);
        GM_SeSet(&work->control.mov, 0x8F);

        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = 0;

        if (target->vital <= 0)
        {
            if (target->a_mode == 1)
            {
                work->in_grip = 1;
            }

            work->act.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode(work, s03d_800CFB04);
            target->captured = 0;
        }
    }

    switch (GM_PlayerAction)
    {
    case 7:
    case 13:
        if (motion != 23 && motion != 44)
        {
            target->side = 0;
            SetAction(work, 23, 4);
            work->field_AF8 = 0;
        }

        if (work->field_AF8 == 50 && target->faint > 0)
        {
            SetAction(work, 44, 4);
        }

        if (motion == 44 && !(work->field_AF8 & 7))
        {
            ZAKO_VibTime = 4;
        }

        work->control.turn = GM_PlayerControl->rot;
        s03d_800CF114(work);
        work->field_AF8++;
        break;
    case 38:
        if (motion != 24)
        {
            target->side = 0;
            SetAction(work, 24, 4);
        }

        work->control.turn = GM_PlayerControl->rot;
        s03d_800CF114(work);
        break;
    case 39:
        work->act.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode(work, s03d_800CFB04);
        return;
    default:
        work->act.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode(work, s03d_800CFB04);
        return;
    }

    if (work->sn_dis > 800)
    {
        target->captured = 0;
    }

    work->target->class |= TARGET_POWER | TARGET_SEEK;
}

void s03d_800CF4D4( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, 34, 4 );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s03d_800D01C4 );
    }
}

void s03d_800CF548(Work *work, int time)
{
    SVECTOR *pos = &work->control.mov;
    int phase;
    work->act.field_1C = 0;
    work->vision.length = 0;
    if (time == 0)
    {
        SetAction( work, 28, 4 );
        work->target->faint = 0;
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    phase = 0xA;
    if (time == phase)
    {
        work->act.field_14 = 1;
        SetAction( work, 33, 4 );
    }
    else
    {
        work->target->class |= TARGET_FLAG;
    }
    if (time == phase + 0x18)
    {
        GM_SeSet(pos, 0x51);
    }
    if (time == phase + 0x2E)
    {
        GM_SeSet(pos, 0x33);
    }
    if (time >= phase + 0x32 && work->body.is_end)
    {
        SetMode( work, s03d_800CF68C );
    }
}

void s03d_800CF68C(Work *work, int time)
{
    int phase;

    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                SetAction(work, 37, 4);
            }
            else
            {
                SetAction(work, 35, 4);
            }
        }
        else
        {
            SetAction(work, 36, 4);
        }

        if (work->target->faint <= 0)
        {
            phase = work->control.mov.vx % 90;
        }
        else
        {
            phase = work->control.mov.vx % 30;
        }

        work->field_AF6 = abs(phase) + 10;
    }

    if (Zako_800CD6A8(work))
    {
        SetMode(work, s03d_800CF844);
    }
    else if (work->field_AF6 < time)
    {
        if (work->target->faint <= 0)
        {
            work->target->faint = work->param.faint;
        }

        SetMode(work, s03d_800CF90C);
    }
}

void s03d_800CF844(Work *work, int time)
{
    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            SetAction( work, 42, 4 );
        }
        else
        {
            SetAction( work, 43, 4 );
        }

        GM_SeSet(&work->control.mov, 0x36);
    }
    if (time == 4)
    {
        ZAKO_PutItem(work, 0);
    }
    if (work->body.is_end)
    {
        SetMode( work, s03d_800D01C4 );
    }
}

void s03d_800CF90C(Work *work, int time)
{
    work->act.field_1C = 0;
    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->field_AF6 >= 0x96)
            {
                SetAction( work, 40, 4 );
            }
            else
            {
                SetAction( work, 38, 4 );
            }
        }
        else
        {
            if (work->field_AF6 >= 0x96)
            {
                SetAction( work, 41, 4 );
            }
            else
            {
                SetAction( work, 39, 4 );
            }
        }
    }
    if (work->body.is_end)
    {
        SetMode( work, s03d_800CE12C );
    }
}

void s03d_800CFA04(Work *work, int time)
{
    TARGET *t;
    work->act.field_1C = 0;
    work->target->class |= TARGET_FLAG;
    work->vision.length = 4000;
    if (Zako_800CDA04(work))
    {
        return;
    }
    t = work->target;
    if (time == 0)
    {
        SetAction( work, 15, 4 );
        GM_SeSet(&work->control.mov, 0x8D);
        if (t->a_mode == 3)
        {
            GM_SeSet(&work->control.mov, 0x34);
            ZAKO_PutDust(work);
        }
        else
        {
            ZAKO_PutBlood(work, 5, 0);
        }
    }
    if (work->body.is_end)
    {
        SetMode( work, s03d_800CE12C );
    }
}

void s03d_800CFB04(Work *work, int time)
{
    ACT     *act;
    CONTROL *control;

    act = &work->act;
    control = &work->control;

    control->step = work->target->force;

    if (act->field_14 != 1)
    {
        work->act.field_1C = 0;
    }

    if (time == 0)
    {
        switch (act->field_14)
        {
        case 0:
            GM_SeSet(&control->mov, SE_PUNCHIT1);
            SetAction(work, 30, 4);
            GM_SeSet(&control->mov, SE_V_ENE_PUNCHED);
            ZAKO_PutBlood(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 1:
            SetAction(work, 33, 4);

            if (work->target->vital <= 0)
            {
                if (GM_Weapon == WP_Rifle)
                {
                    ZAKO_PutBlood(work, 6, 2);
                }
                else
                {
                    ZAKO_PutBlood(work, 6, 1);
                }
            }
            else
            {
                ZAKO_PutBlood(work, 5, 0);
            }

            GM_SeSet(&control->mov, SE_V_ENE_PUNCHED);
            work->field_AF6 = 46;
            break;
        case 3:
            GM_SeSet(&control->mov, SE_EDMG01);
            SetAction(work, 31, 4);
            ZAKO_PutBlood(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 2:
            GM_SeSet(&control->mov, SE_V_ENE_THROWN);
            SetAction(work, 32, 4);
            ZAKO_PutBlood(work, 5, 0);
            work->field_AF6 = 22;
            break;
        case 4:
            GM_SeSet(&control->mov, SE_V_ENE_SNAPPED);
            SetAction(work, 25, 4);
            work->field_AF6 = 67;
            break;
        case 5:
            SetAction(work, 26, 4);
            work->field_AF6 = 15;
            break;
        }
    }

    switch (act->field_14)
    {
    case 0:
        if (time < 12)
        {
            control->turn.vy += 170;
        }

        if (time > 0 && time < 6)
        {
            Zako_800CDF2C(work);
        }

        if (time < 20)
        {
            work->control.hzd_height = -32767;
        }
        break;
    case 1:
        if (time == 24)
        {
            GM_SeSet(&control->mov, SE_ENEMY_COLLAPSE);
        }
        break;
    case 3:
        if (time > 0 && time < 15)
        {
            Zako_800CDF2C(work);
        }

        if (time < 15)
        {
            control->hzd_height = -32767;
        }
        break;
    case 2:
        if (time > 0 && time < 30)
        {
            Zako_800CDF2C(work);
        }

        if (time < 20)
        {
            control->hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        break;
    }

    if (time > 16 && control->grounded != 0)
    {
        control->step = DG_ZeroVector;
    }

    if (time == work->field_AF6)
    {
        if ((control->mov.vy - control->levels[0]) < 2000)
        {
            GM_SeSet(&control->mov, SE_HIT_FLOOR);
            GM_SetNoise(100, 4, &control->mov);
            ZAKO_PutBlood(work, 6, 0);
        }
        else if ((control->mov.vy - control->levels[0]) > 4000)
        {
            work->target->vital = 0;
            SetMode(work, s03d_800CFFF0);
            return;
        }
    }

    if (work->body.is_end)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;

        if (work->target->vital <= 0)
        {
            SetMode(work, s03d_800D01C4);
        }
        else
        {
            SetMode(work, s03d_800CF68C);
        }
    }
}

void s03d_800CFFF0(Work *work, int time)
{
    CONTROL *ctrl = &work->control;

    work->act.field_1C = 0;
    ctrl->step = work->target->force;
    if (time == 0 && work->act.field_14 != 2)
    {
        GM_SeSet(&ctrl->mov, SE_V_ENE_THROWN);
    }
    if (time > 16 && ctrl->grounded)
    {
        ctrl->step = DG_ZeroVector;
    }
    if (work->act.motion1 < 35)
    {
        if (work->body.is_end)
        {
            if (work->act.field_14 < 3)
            {
                if (work->act.field_14 == 1)
                {
                    SetAction( work, 37, 4 );
                }
                else
                {
                    SetAction( work, 35, 4 );
                }
            }
            else
            {
                SetAction( work, 36, 4 );
            }
        }
    }
    else if (ctrl->grounded)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet(&ctrl->mov, SE_HIT_FLOOR);
        ZAKO_PutBlood(work, 6, 1);
        SetMode( work, s03d_800D01C4 );
    }
}

void s03d_800D01C4(Work *work, int time)
{
    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                SetAction( work, 47, 4 );
            }
            else
            {
                SetAction( work, 45, 4 );
            }
        }
        else
        {
            SetAction( work, 46, 4 );
        }
        GM_ConfigControlAttribute(&work->control, 0);
        work->alert_level = 0;
    }
    if (time == 4)
    {
        int n_dead;

        n_dead = work->n_dead;
        printf("n_dead = %d \n", n_dead);

        if (n_dead == 6 || n_dead == 10 || n_dead == 14)
        {
            ZAKO_PutItem(work, 2);
        }

        if (n_dead == 8 || n_dead == 12)
        {
            ZAKO_PutItem(work, 0);
        }
    }
    if (time & 2)
    {
        work->visible = 0;
    }
    else
    {
        work->visible = 1;
    }
    if (time >= 9)
    {
        SetMode( work, s03d_800D0324 );
    }
}

static void s03d_800D0324( Work *work, int time )
{
    if ( time == 0 )
    {
        work->visible = 0;
        work->control.mov = ZAKO_NO_POINT;

        ZAKOCommand.watchers[ work->param.index ].field_4 = 1;

        if ( work->in_grip == 0 )
        {
            GM_EnemyKillCount++;
        }
    }

    if ( ZAKOCommand.watchers[ work->param.index ].field_4 == 2 )
    {
        s03d_800CDB5C( work );
        SetMode( work, s03d_800CE12C );
    }
}

static int Zako_800D0408( Work *work )
{
    return work->control.mov.vx > 4500;
}

/*---------------------------------------------------------------------------*/

void ZAKO_Action( Work *work )
{
    ACT     *act;
    CONTROL *control;
    ACTION   action;
    int      time;

    act = &work->act;
    control = &work->control;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    action = work->action;

    work->actend = 0;
    work->act_status = 0;

    control->height = work->body.height;
    control->hzd_height = control->levels[ 0 ] + 750;

    time = work->time++;
    if (action == NULL)
    {
        action = s03d_800CE12C;
        work->action = s03d_800CE12C;
    }

    action(work, time);

    action = work->action2;
    if (action != NULL)
    {
        time = work->time2++;
        action(work, time);
    }

    if (act->field_1C == 0)
    {
        control->r_sphere = GV_NearExp2(control->r_sphere, act->field_1A);
    }
    else
    {
        control->r_sphere = -1;
    }

    if (work->target->class & TARGET_POWER)
    {
        work->hom->flag = 1;
    }
    else
    {
        work->hom->flag = 0;
    }

    if (ZAKOCommand.watchers[work->param.index].field_4 == 1)
    {
        work->hom->flag = 0;
    }

    if ( !Zako_800D0408( work ) )
    {
        work->hom->flag = 0;
        work->target->class = TARGET_AVAIL;
    }

    if (act->field_04 < 0 && control->grounded)
    {
        act->field_04 = 0;
    }

    act->field_04 -= 16;
    control->step.vy = act->field_04;

    work->vital_prev = work->target->vital;
}
