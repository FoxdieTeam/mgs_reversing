#include "animal/zako/zako.h"

#include <stdio.h>
#include "game/item.h"
#include "okajima/blood.h"

/*---------------------------------------------------------------------------*/

extern int s03d_dword_800C39B0;
extern int s03d_dword_800C39B8;
extern int s03d_dword_800C39C0;
extern int s03d_dword_800C39C8;
extern void *s03d_dword_800C3A90[];
extern int s03d_dword_800C3A64;
extern int s03d_dword_800C3A6C;
extern int s03d_dword_800C3A84;
extern int s03d_dword_800C3A88;
extern int s03d_dword_800C3A74;
extern int s03d_dword_800C3A7C;
extern short s03d_word_800C39F0[2];
extern int s03d_dword_800C39F4;
extern short s03d_word_800C3A00[2];
extern int s03d_dword_800C3A04;
extern int s03d_dword_800C3A08;
extern int s03d_dword_800C3A0C;
extern int s03d_dword_800C39E0;
extern int s03d_dword_800C39FC;
extern short s03d_word_800C3A38[2];
extern short s03d_word_800C3A3C[2];
extern short s03d_word_800C39E8[2];
extern short s03d_word_800C39EC[2];
extern int s03d_dword_800C3A5C;
extern short s03d_word_800C3A10[20];

extern void AN_Fog( SVECTOR *pos );

void s03d_800D01C4( Work *work, int arg );
void s03d_800D0324( Work *work, int arg );
void s03d_800CF68C( Work *work, int arg );
void s03d_800CE12C( Work *work, int arg );
void s03d_800CF548( Work *work, int arg );
void s03d_800CEE3C( Work *work, int arg );
void s03d_800CF194( Work *work, int arg );
void Zako_800D0BEC( Work *work, int type );
void Zako_800D0B18( Work *work, int index, int count );
void Zako_800D0B88( Work *work );
int  s03d_800CDE1C( Work *work );
void s03d_800CE720( Work *work, int arg );
void s03d_800CDB5C( Work *work );
int  s03d_800CC4EC( Work *work, int arg );
void s03d_800CC984( Work *work );
int  s03d_800CD61C( Work *work );
int  s03d_800CD75C( Work *work );
int  s03d_800CD984( Work *work );
void s03d_800D041C( Work *work );
void s03d_800D14AC( Work *work );
void s03d_800D13F8( Work *work );

/*---------------------------------------------------------------------------*/

int s03d_800CD61C(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & TARGET_CAPTURE)
    {
        if (t->a_mode == 0x24)
        {
            work->action = s03d_800CEE3C;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, 0);
            t->damaged = 0;
        }
        else
        {
            work->action = s03d_800CF194;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, 0);
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

const char s03d_dword_800DB4B4[] = " meryl KILLED !!! \n";
const char s03d_dword_800DB4C8[] = " SNAKE KILLED !!! \n";

const int s03d_dword_800DB4DC = 0x800CD840;
const int s03d_dword_800DB4E0 = 0x800CD8D8;
const int s03d_dword_800DB4E4 = 0x800CD7C8;
const int s03d_dword_800DB4E8 = 0x800CD828;
const int s03d_dword_800DB4EC = 0x800CD910;
const int s03d_dword_800DB4F0 = 0x800CD964;
const int s03d_dword_800DB4F4 = 0x800CD964;
const int s03d_dword_800DB4F8 = 0x800CD92C;
const int s03d_dword_800DB4FC = 0x800CD940;
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD75C.s")

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

    work->action = s03d_800CF548;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, 0);
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

    GM_SetTarget(t, 0x9E, 2, (SVECTOR *)&s03d_dword_800C39B0);
    GM_SetPowerTarget(t, 1, -1, b14, b16, (SVECTOR *)&s03d_dword_800C39B8);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_SetC4Target(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->attack, 4, 1, (SVECTOR *)&s03d_dword_800C39C0);
    GM_SetPowerTarget(&work->attack, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
}

void s03d_800CDB5C( Work *work )
{
    CONTROL *control;
    int z;
    HZD_ZON *zone;

    control = &work->control;

    work->n_dead = ZAKO_800D4038();
    work->visible = 1;

    GM_ConfigControlAttribute( control, 0x8 | 0x4 | 0x1 );
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

    GM_SetPowerTarget(t, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDF94.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE12C.s")

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

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE318.s")

void s03d_800CE5B4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->act.field_14 = 3;
        work->act.field_18 = 0x1F;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[7], 0, 4);
    }
    if (Zako_800CDA04(work) == 0 && work->body.is_end)
    {
        work->pad.tmp = 0;
        work->action = s03d_800CF68C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800CE644(Work *work, int arg)
{
    CONTROL *control = &work->control;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        work->act.field_18 = 0x10;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A00[0], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end || !(work->pad.press & 0x20))
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
    else
    {
        short vy = work->sn_dir;
        control->step.vx = 0;
        control->step.vz = 0;
        control->turn.vy = vy;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE720.s")

void s03d_800CE8F4(Work *work, int arg)
{
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        if (work->pad.press & 0x10000)
        {
            work->act.field_18 = 4;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39E8[0], 0, 0);
        }
        else
        {
            work->act.field_18 = 6;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        }
        Zako_800D0EF0(work, 3);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    if (work->param.index != 1 || !(GV_Time & 0x100))
    {
        Zako_800CDD94(work);
    }
    if (!Zako_800CDA04(work))
    {
        work->action = s03d_800CE720;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s03d_800CE9E8(Work *work, int arg)
{
    SVECTOR *rot;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    rot = &work->control.rot;
    if (arg == 1 || arg == 7)
    {
        rot->vy = (*(unsigned short *)&rot->vy - 0x100) & 0xFFF;
    }
    if (arg == 3 || arg == 5)
    {
        rot->vy = (*(unsigned short *)&rot->vy + 0x100) & 0xFFF;
    }
    if (arg == 2 || arg == 4 || arg == 6)
    {
        work->act.field_18 = 6;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        Zako_800D0EF0(work, 3);
    }
    Zako_800CDD94(work);
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            work->action = s03d_800CE720;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        work->control.rot.vy = rot->vy;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CEB38.s")

void s03d_800CECBC(Work *work, int arg)
{
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        work->act.field_18 = 8;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39F0[0], 0, 0);
    }
    if (arg == 3 && s03d_800CDE1C(work))
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
        work->action = s03d_800CE720;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800CED94(Work *work, int arg)
{
    work->vision.length = 0;
    if (arg == 0)
    {
        work->act.field_18 = 0x13;
        GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C3A04)[1], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    work->target->class |= 0x9E;
    if (work->body.is_end)
    {
        work->actend = 1;
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CEE3C.s")

void s03d_800CF114(Work *work)
{
    SVECTOR vec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector((SVECTOR *)&s03d_dword_800C3A5C, &vec, 1);
    GV_SubVec3(&vec, &work->control.mov, &work->control.step);
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CF194.s")

void s03d_800CF4D4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->act.field_18 = 0x22;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[10], 0, 4);
    }
    if (work->body.is_end)
    {
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800CF548(Work *work, int arg)
{
    SVECTOR *pos = &work->control.mov;
    int phase;
    work->act.field_1C = 0;
    work->vision.length = 0;
    if (arg == 0)
    {
        work->act.field_18 = 0x1C;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[4], 0, 4);
        work->target->faint = 0;
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    phase = 0xA;
    if (arg == phase)
    {
        work->act.field_14 = 1;
        work->act.field_18 = 0x21;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[9], 0, 4);
    }
    else
    {
        work->target->class |= 0x9E;
    }
    if (arg == phase + 0x18)
    {
        GM_SeSet(pos, 0x51);
    }
    if (arg == phase + 0x2E)
    {
        GM_SeSet(pos, 0x33);
    }
    if (arg >= phase + 0x32 && work->body.is_end)
    {
        work->action = s03d_800CF68C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CF68C.s")

void s03d_800CF844(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            work->act.field_18 = 0x2A;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[18], 0, 4);
        }
        else
        {
            work->act.field_18 = 0x2B;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[19], 0, 4);
        }
        GM_SeSet(&work->control.mov, 0x36);
    }
    if (arg == 4)
    {
        Zako_800D0BEC(work, 0);
    }
    if (work->body.is_end)
    {
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800CF90C(Work *work, int arg)
{
    work->act.field_1C = 0;
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->field_AF6 >= 0x96)
            {
                work->act.field_18 = 0x28;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[16], 0, 4);
            }
            else
            {
                work->act.field_18 = 0x26;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[14], 0, 4);
            }
        }
        else
        {
            if (work->field_AF6 >= 0x96)
            {
                work->act.field_18 = 0x29;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[17], 0, 4);
            }
            else
            {
                work->act.field_18 = 0x27;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[15], 0, 4);
            }
        }
    }
    if (work->body.is_end)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800CFA04(Work *work, int arg)
{
    TARGET *t;
    work->act.field_1C = 0;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (Zako_800CDA04(work))
    {
        return;
    }
    t = work->target;
    if (arg == 0)
    {
        work->act.field_18 = 0xF;
        GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C39FC)[1], 0, 4);
        GM_SeSet(&work->control.mov, 0x8D);
        if (t->a_mode == 3)
        {
            GM_SeSet(&work->control.mov, 0x34);
            Zako_800D0B88(work);
        }
        else
        {
            Zako_800D0B18(work, 5, 0);
        }
    }
    if (work->body.is_end)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

const char s03d_dword_800DB560[] = {0x0, 0x0, 0x0, 0x0};
const int s03d_dword_800DB564 = 0x800CFB9C;
const int s03d_dword_800DB568 = 0x800CFBEC;
const int s03d_dword_800DB56C = 0x800CFCB4;
const int s03d_dword_800DB570 = 0x800CFC70;
const int s03d_dword_800DB574 = 0x800CFCF8;
const int s03d_dword_800DB578 = 0x800CFD2C;
const int s03d_dword_800DB57C = 0x800CFD84;
const int s03d_dword_800DB580 = 0x800CFDCC;
const int s03d_dword_800DB584 = 0x800CFE0C;
const int s03d_dword_800DB588 = 0x800CFDEC;
const int s03d_dword_800DB58C = 0x800CFE34;
const int s03d_dword_800DB590 = 0x800CFE34;
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CFB04.s")

void s03d_800CFFF0(Work *work, int arg)
{
    CONTROL *ctrl = &work->control;

    work->act.field_1C = 0;
    ctrl->step = work->target->force;
    if (arg == 0 && work->act.field_14 != 2)
    {
        GM_SeSet(&ctrl->mov, SE_V_ENE_THROWN);
    }
    if (arg > 16 && ctrl->grounded)
    {
        ctrl->step = DG_ZeroVector;
    }
    if (work->act.field_18 < 35)
    {
        if (work->body.is_end)
        {
            if (work->act.field_14 < 3)
            {
                if (work->act.field_14 == 1)
                {
                    work->act.field_18 = 37;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[13], 0, 4);
                }
                else
                {
                    work->act.field_18 = 35;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[11], 0, 4);
                }
            }
            else
            {
                work->act.field_18 = 36;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[12], 0, 4);
            }
        }
    }
    else if (ctrl->grounded)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet(&ctrl->mov, SE_HIT_FLOOR);
        Zako_800D0B18(work, 6, 1);
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800D01C4(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                work->act.field_18 = 0x2F;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A3C[1], 0, 4);
            }
            else
            {
                work->act.field_18 = 0x2D;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A38[1], 0, 4);
            }
        }
        else
        {
            work->act.field_18 = 0x2E;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A3C[0], 0, 4);
        }
        GM_ConfigControlAttribute(&work->control, 0);
        work->alert_level = 0;
    }
    if (arg == 4)
    {
        int b04 = work->n_dead;

        printf("n_dead = %d \n", b04);
        if (b04 == 6 || b04 == 0xA || b04 == 0xE)
        {
            Zako_800D0BEC(work, 2);
        }
        if (b04 == 8 || b04 == 0xC)
        {
            Zako_800D0BEC(work, 0);
        }
    }
    if (arg & 2)
    {
        work->visible = 0;
    }
    else
    {
        work->visible = 1;
    }
    if (arg >= 9)
    {
        work->action = s03d_800D0324;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

void s03d_800D0324(Work *work, int arg)
{
    if (arg == 0)
    {
        work->visible = 0;
        work->control.mov = ZAKO_NO_POINT;

        ZAKOCommand.watchers[work->param.index].field_4 = 1;

        if (work->in_grip == 0)
        {
            GM_EnemyKillCount++;
        }
    }

    if (ZAKOCommand.watchers[work->param.index].field_4 == 2)
    {
        s03d_800CDB5C(work);

        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

int Zako_800D0408(Work *work)
{
    return work->control.mov.vx > 4500;
}

const char s03d_dword_800DB5A4[] = "FA-MAS/BULLET * 25";
const char s03d_dword_800DB5B8[] = "SOCOM/BULLET * 12";
const char s03d_dword_800DB5CC[] = "RATION";
const char s03d_dword_800DB5D4[] = "noise dis  =%d,\n";
const char s03d_dword_800DB5E8[] = " Asiato mikke!! [%d]\n";

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D041C.s")

// override.c

void s03d_800D05DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39F0[1], 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 1))
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy - (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy - 0x400) & 0xFFF;
    }
}

void s03d_800D0698(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39F4, 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 2))
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + 0x400) & 0xFFF;
    }
}

void s03d_800D0754(Work *work, int arg1)
{
    work->vision.length = 0x7D0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ((short *)&s03d_dword_800C39F4)[1], 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 4))
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s03d_800D07DC(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A0C, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s03d_800D085C(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A08, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s03d_800D08DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ((short *)&s03d_dword_800C3A08)[1], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s03d_800D0958(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C3A00[1], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D09D8.s")

// put.c

void Zako_800D0B18(Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3A64);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3A6C);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
}

void Zako_800D0B88(Work *work)
{
    MATRIX  m;
    SVECTOR sv;

    DG_SetPos(&work->body.objs->objs[1].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3A74);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3A7C);
    ReadRotMatrix(&m);
    sv.vx = *(short *)&m.t[0];
    sv.vy = *(short *)&m.t[1];
    sv.vz = *(short *)&m.t[2];
    AN_Fog(&sv);
}

void Zako_800D0BEC(Work *work, int type)
{
    SVECTOR step;
    ITEM_INFO info;
    SVECTOR *pos;

    step = work->act.field_0C;
    pos = &work->control.mov;

    if (type >= 0)
    {
        if (type < 2)
        {
            info.type = 4;
            info.id = IT_Ration;
            info.num = 1;
            info.message = (const char *)s03d_dword_800C3A84;
        }
        else if (type < 4)
        {
            info.type = 2;
            info.id = WP_Socom;
            info.num = 0xC;
            info.message = (const char *)s03d_dword_800C3A88;
        }
    }
    info.time = 0x384;
    NewItemPut(pos, &step, &info);
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0C90.s")

int Zako_800D0EF0( Work *work, int index )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putfuncs[ i ] == NULL )
        {
            work->putfuncs[ i ] = s03d_dword_800C3A90[ index ];
            return 1;
        }
    }

    return 0;
}

int Zako_800D0F38( Work *work, void *func )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putfuncs[ i ] == func )
        {
            work->putfuncs[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

void Zako_800D0F6C(Work *work)
{
    int i;
    PUTFUNC func;

    for ( i = 0; i < 8; i++ )
    {
        if ( work->putfuncs[ i ] != NULL )
        {
            func = work->putfuncs[ i ];
            func( work );
        }
    }
}

// zakoact.c

void Zako_800D0FCC( Work *work )
{
    VISION *vision;
    RADAR_SIGHT_PARAM *r_param;

    vision = &work->vision;
    r_param = &work->control.radar_param;

    r_param->dir = vision->facedir;
    r_param->dis = vision->length;
    r_param->range = vision->range;
    r_param->r = 0;
}

void Zako_800D0FF4(Work *work)
{
    if (work->modetime[ 7 ] & 4)
    {
        if (work->target->damaged & 6)
        {
            work->modetime[ 6 ] |= 4;
        }
        if (work->attack.damaged & 0x80)
        {
            work->vision.pad = 2;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D1054.s")

void Zako_800D13E8(Work *work)
{
    SVECTOR unused[2];

    (void)unused;

    work->modetime[ 6 ] = 0;
}

void s03d_800D13F8(Work *work)
{
    switch (work->vision.pad)
    {
    case 0:
        if (work->alert_level != 255 || !(GM_PlayerStatus & PLAYER_INTRUDE))
        {
            work->alert_level -= 4;
        }
        break;
    case 1:
        work->alert_level--;
        break;
    case 2:
        work->alert_level++;
        break;
    }

    if (work->alert_level < 0)
    {
        work->alert_level = 0;
    }
    else if (work->alert_level > 255)
    {
        work->alert_level = 255;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D14AC.s")

void ZakoActionMain(Work *work)
{
    if (work->act.field_18 < 0x2D)
    {
        Zako_800D0FCC(work);
        s03d_800D14AC(work);
        Zako_800D13E8(work);
        s03d_800D13F8(work);
        ZakoThink(work);
        Zako_800D0F6C(work);
    }
    s03d_800D041C(work);
}

void ZakoPushMove(Work *work)
{
    TARGET  *trg;
    CONTROL *ctrl;
    int      turn;
    int      last_set;

    trg = work->target;
    turn = 0;
    if (!(trg->damaged & TARGET_PUSH))
    {
        return;
    }

    GV_AddVec3(&trg->offset, &work->control.step, &work->control.step);
    trg->damaged &= ~TARGET_PUSH;

    last_set = work->act.field_18;
    if (last_set == 1 || last_set == 2)
    {
        if (trg->offset.pad != 0)
        {
            if (GV_Time & 0x100)
            {
                if (work->param.index & 1)
                {
                    turn = trg->offset.pad << 10;
                }
                else
                {
                    turn = (trg->offset.pad + 2) << 10;
                }
            }
            else
            {
                if (work->param.index & 1)
                {
                    turn = (trg->offset.pad + 2) << 10;
                }
                else
                {
                    turn = trg->offset.pad << 10;
                }
            }
            turn &= 0xFFF;
        }

        ctrl = &work->control;
        ctrl->turn.vy = turn;
        ctrl->r_sphere = GV_NearExp2(ctrl->r_sphere, work->act.field_1A);
    }
}
