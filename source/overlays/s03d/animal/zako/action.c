#include "zako.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "mgstype.h"
#include "game/game.h"
#include "game/item.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "enemy/asiato.h"
#include "okajima/blood.h"
#include "bullet/tenage.h"
#include "okajima/bullet.h"

void s03d_800D0CD4(Work *work);
void s03d_800D0D6C(Work *work);
void s03d_800D0DF0(Work *work);
void s03d_800D0E2C(Work *work);

extern const char ItemMsgFamas[];
extern const char ItemMsgSocom[];
extern const char ItemMsgRation[];

short ZakoActionTable[] = {
    19, 20, 10, 22,  9, 34, 35, 36,
    45, 13, 12, 26, 15, 14, 16, 27,
     8, 21, 30, 31, 32, 33, 37, 25,
     5,  2, 42,  4, 39, 40,  6,  7,
    38,  3, 41, 17, 18, 43, 23, 24,
    28, 29,  0,  1, 51, 17, 18, 43,
    22
};

SVECTOR ThrowPos2 = {4250, 250, 500};
SVECTOR ThrowPos = {4250, 250, 500};
SVECTOR ThrowStep = {0, 50, 200};
SVECTOR CatchOffset = {-150, 0, 300};
SVECTOR BloodPos = {0, 0, 100};
SVECTOR BloodRot = {-1024, 0, 0};
SVECTOR FogPos = {0, 0, 100};
SVECTOR FogRot = {-1024, 0, 0};

const char *ItemMessages[] = {
    ItemMsgRation,
    ItemMsgSocom,
    ItemMsgFamas,
};

PUTFUNC PutChars[] = {
    s03d_800D0CD4,
    s03d_800D0D6C,
    s03d_800D0DF0,
    s03d_800D0E2C,
};

SVECTOR MuzzlePos = {5, -500, 80};
SVECTOR MuzzleRot = {1024, 0, 0};
SVECTOR s03d_dword_800C3AB0 = {8000, 0, -1000};

extern int s03d_dword_800DC2F4;
extern SVECTOR s03d_dword_800C3B88;

void AN_Fog(SVECTOR *svec);
void AN_Sleep(SVECTOR *svec);
void *AN_Breath(MATRIX *world);
void *AN_HeadMark(MATRIX *world, int mark);

void s03d_800D05DC(Work *work, int arg);
void s03d_800D0698(Work *work, int arg);
void s03d_800D0754(Work *work, int arg);
void s03d_800D07DC(Work *work, int arg);
void s03d_800D085C(Work *work, int arg);
void s03d_800D08DC(Work *work, int arg);
void s03d_800D0958(Work *work, int arg);
void s03d_800D09D8(Work *work, int arg);
void s03d_800CE5B4(Work *work, int arg);
void s03d_800CE644(Work *work, int arg);
int s03d_800CDF94(Work *work);
void s03d_800CE318(Work *work, int arg);
void s03d_800CFB04(Work *work, int arg);
void s03d_800CF844(Work *work, int arg);
void s03d_800CFA04(Work *work, int arg);
void s03d_800CF4D4(Work *work, int arg);
void s03d_800CFFF0(Work *work, int arg);
void s03d_800CF90C(Work *work, int arg);
void s03d_800CF114(Work *work);
void s03d_800CE8F4(Work *work, int arg);
void s03d_800CE9E8(Work *work, int arg);
void s03d_800CEB38(Work *work, int arg);
void s03d_800CECBC(Work *work, int arg);
void s03d_800CE2C0(Work *work, int arg1);
void s03d_800D01C4(struct _Work *work, int arg);
void s03d_800D0324(struct _Work *work, int arg);
void s03d_800CF68C(struct _Work *work, int arg);
void s03d_800CE12C(struct _Work *work, int arg);
void s03d_800CF548(struct _Work *work, int arg);
void s03d_800CEE3C(struct _Work *work, int arg);
void s03d_800CF194(struct _Work *work, int arg);
void Zako_800D0BEC(Work *work, int type);
void Zako_800D0B18(Work *work, int index, int count);
void Zako_800D0B88(Work *work);
int  s03d_800CDE1C(Work *work);
void s03d_800CE720(struct _Work *work, int arg);
int  Zako_800D0EF0(Work *work, int index);
int  Zako_800D0F38(Work *work, PUTFUNC func);
void s03d_800CDB5C(Work *work);
int  s03d_800CD61C(Work *work);
int  s03d_800CD75C(Work *work);
int  s03d_800CD984(Work *work);
void s03d_800D041C(Work *work);
void s03d_800D14AC(Work *work);
void s03d_800D13F8(Work *work);
void s03d_800D3B5C(Work *work);
void s03d_800D153C(Work *work);
int  ZakoCom_800D4038(void);

int s03d_800CD61C(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & TARGET_CAPTURE)
    {
        if (t->a_mode == 0x24)
        {
            SetMode(work, s03d_800CEE3C);
            t->damaged = 0;
        }
        else
        {
            SetMode(work, s03d_800CF194);
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
int s03d_800CD75C(Work *work)
{
    TARGET *target;

    target = work->target;
    if (!(target->damaged & TARGET_POWER))
    {
        return 0;
    }

    switch (target->a_mode)
    {
    case 3:
        target->force = DG_ZeroVector;
        if (target->faint <= 0)
        {
            work->act.field_14 = 1;
            SetMode(work, s03d_800CFB04);
        }
        else
        {
            SetMode(work, s03d_800CFA04);
        }
        break;
    case 4:
        work->act.field_14 = 0;
        SetMode(work, s03d_800CFB04);
        break;
    case 1:
        target->force = DG_ZeroVector;
        if (target->vital <= 0)
        {
            if (target->vital != work->last_vital - 0x40)
            {
                work->field_BA0 = 1;
                printf(" meryl KILLED !!! \n");
            }
            else
            {
                printf(" SNAKE KILLED !!! \n");
            }
            work->act.field_14 = 1;
            SetMode(work, s03d_800CFB04);
        }
        else
        {
            SetMode(work, s03d_800CFA04);
        }
        break;
    case 2:
        if (Zako_800CD720(&target->force) < 100)
        {
            work->act.field_14 = 3;
        }
        else
        {
            work->act.field_14 = 2;
        }
        SetMode(work, s03d_800CFB04);
        break;
    case 5:
        work->act.field_14 = 3;
        SetMode(work, s03d_800CFB04);
        break;
    case 8:
        SetMode(work, s03d_800CF4D4);
        break;
    case 9:
        SetMode(work, s03d_800CF548);
        break;
    }

    target->damage = 0;
    target->damaged = 0;
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

    SetMode(work, s03d_800CF548);
    return 1;
}
int Zako_800CDA04(Work *work)
{
    int a = s03d_800CD61C(work);
    int b = s03d_800CD75C(work);
    int c = s03d_800CD984(work);

    if (a | b | c)
    {
        work->target->class = TARGET_AVAIL;
        return 1;
    }
    return 0;
}
void Zako_800CDA70(Work *work)
{
    TARGET *t = work->target;
    int     b14 = work->param.life;
    int     b16 = work->param.faint;

    GM_SetTarget(t, TARGET_FLAG, ENEMY_SIDE, &ZAKO_TARGET_SIZE);
    GM_SetPowerTarget(t, POWER_DECREASE, -1, b14, b16, &ZAKO_TARGET_FORCE);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_SetC4Target(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->attack, TARGET_POWER, PLAYER_SIDE, &ZAKO_ATTACK_SIZE);
    GM_SetPowerTarget(&work->attack, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO_ATTACK_FORCE);
}
void s03d_800CDB5C(Work *work)
{
    CONTROL *ctrl;
    HZD_ZON *zone;
    int      reset;

    ctrl = &work->control;
    work->n_dead = ZakoCom_800D4038();
    work->visible = 1;
    GM_ConfigControlAttribute(ctrl, RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP);
    Zako_800CDA70(work);

    if (ZakoGameFlag < 4)
    {
        reset = work->param.index * 2 + 25;
        printf("aaa reset wait zone id = %d z=%d\n", work->param.index, reset);
    }
    else
    {
        reset = ZakoCommand.zones[work->param.index % 2];
        printf("bbb reset fight zone id = %d z=%d\n", work->param.index, reset);
    }

    zone = HZD_GetZone(ctrl->map->hzd, reset);
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;
    if (work->param.index == 2)
    {
        ctrl->mov.vz += 500;
    }

    ctrl->map = GM_GetMap(work->start_map);

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->field_AD4 = work->n_nodes - 1;
    work->target_addr = work->start_addr;
    work->target_pos = work->start_pos;
    work->vision.range = 512;
    work->vision.length = 4000;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.field_4 = 1;
    work->field_BA0 = 0;
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
    SVECTOR force = {5, 0, 100};
    SVECTOR size = {400, 1000, 400};

    target = &work->punch;
    GM_SetTarget(target, TARGET_POWER, ENEMY_SIDE, &size);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_RotVector(&force, &svec, 1);
    GM_SetPowerTarget(target, POWER_ONCE, 2, 32, 1, &svec);
    DG_PutVector(&rp_shift, &target->center, 1);
    return GM_PowerTarget(target);
}

/* 4 unreferenced bytes of rdata (unknown origin) */
const char s03d_dword_800DB560[4] = {0};

void Zako_800CDF2C(Work *work)
{
    TARGET *t = &work->attack;

    GM_SetPowerTarget(t, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO_ATTACK_FORCE);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}
int s03d_800CDF94(Work *work)
{
    int status;

    status = work->pad.press;

    if (status & 1)
    {
        SetMode2(work, s03d_800D05DC);
        return 0;
    }

    if (status & 2)
    {
        SetMode2(work, s03d_800D0698);
        return 0;
    }

    if (status & 4)
    {
        SetMode2(work, s03d_800D0754);
        return 0;
    }

    if (status & 0x40)
    {
        SetMode2(work, s03d_800D07DC);
        return 0;
    }

    if (status & 0x80)
    {
        SetMode2(work, s03d_800D085C);
        return 0;
    }

    if (status & 0x400)
    {
        SetMode2(work, s03d_800D08DC);
        return 0;
    }

    if (status & 0x800)
    {
        SetMode2(work, s03d_800D0958);
        return 0;
    }

    if (status & 0x200)
    {
        SetMode2(work, s03d_800D09D8);
        return 0;
    }

    if (status & 0x100)
    {
        SetMode(work, s03d_800CE5B4);
        return 1;
    }

    if (status & 0x20)
    {
        SetMode(work, s03d_800CE644);
        return 1;
    }

    if (status & 0x30000)
    {
        SetMode(work, s03d_800CE720);
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}
void s03d_800CE12C(Work *work, int arg)
{
    work->target->class |= TARGET_FLAG;
    if (ZakoCommand.alert_mode == 0)
    {
        work->target->class |= TARGET_C4;
    }
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        SetAction(work, 0, 4);
    }
    if (Zako_800CDA04(work) || s03d_800CDF94(work))
    {
        UnsetMode(work);
    }
    else
    {
        if (work->pad.dir >= 0)
        {
            if (GV_DiffDirAbs(work->control.rot.vy, work->pad.dir) < 0x100)
            {
                if (work->pad.field_4 & 1)
                {
                    SetAction(work, 2, 4);
                }
                else
                {
                    SetAction(work, 1, 4);
                }
                SetMode(work, s03d_800CE318);
            }
            else
            {
                work->control.turn.vy = work->pad.dir;
            }
        }
        work->vision.facedir = GV_NearExp4P(work->vision.facedir, work->control.rot.vy);
    }
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
void s03d_800CE318(Work *work, int arg)
{
    CONTROL *ctrl;
    SVECTOR *vecs;
    int      dir, motion, touches, touch, touch2, size;

    work->target->class |= TARGET_FLAG;
    if (ZakoCommand.alert_mode == 0)
    {
        work->target->class |= TARGET_C4;
    }
    work->vision.length = 0xFA0;

    if (Zako_800CDA04(work))
    {
        UnsetMode(work);
        return;
    }

    if (s03d_800CDF94(work))
    {
        UnsetMode(work);
        return;
    }

    touch = -1;
    ctrl = &work->control;
    vecs = ctrl->vecs;
    dir = work->pad.dir;
    motion = work->act.motion1;

    if ((work->pad.field_4 & 1) && motion != 2)
    {
        SetAction(work, 2, 4);
    }

    if (dir < 0)
    {
        SetMode(work, s03d_800CE12C);
        UnsetMode(work);
        return;
    }

    touches = ctrl->n_touches;
    if (touches > 0)
    {
        touch = GV_VecDir2(vecs);
        if (touches > 1)
        {
            touch2 = GV_VecDir2(&ctrl->vecs[1]);
            if (GV_DiffDirAbs(dir, touch2) < GV_DiffDirAbs(dir, touch))
            {
                touch = touch2;
            }
        }
    }

    if (dir < 0)
    {
        SetMode(work, s03d_800CE12C);
        UnsetMode(work);
        return;
    }

    switch (Zako_800CDD40(dir, touch))
    {
    case 1:
        dir = (touch - 1024) & 4095;
        break;
    case 2:
        dir = (touch + 1024) & 4095;
        break;
    }

    if (work->body.objs->bound_mode == 0)
    {
        ctrl->rot.vy = dir;
    }
    ctrl->turn.vy = dir;

    size = 0;
    if (motion == 1)
    {
        size = 50;
    }
    else if (motion == 2)
    {
        size = 100;
    }

    ctrl->step.vx = size * rsin(dir) / 4096;
    ctrl->step.vz = size * rcos(dir) / 4096;
    s03d_800CE2C0(work, dir);
    work->vision.facedir = GV_NearExp4P(work->vision.facedir, work->control.rot.vy);
}
void s03d_800CE5B4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->act.field_14 = 3;
        SetAction(work, 31, 4);
    }
    if (Zako_800CDA04(work) == 0 && work->body.is_end)
    {
        work->pad.field_8 = 0;
        SetMode(work, s03d_800CF68C);
    }
}
void s03d_800CE644(Work *work, int arg)
{
    CONTROL *control = &work->control;
    work->target->class |= TARGET_FLAG;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        SetAction(work, 16, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end || !(work->pad.press & 0x20))
    {
        SetMode(work, s03d_800CE12C);
    }
    else
    {
        short vy = work->sn_dir;
        control->step.vx = 0;
        control->step.vz = 0;
        control->turn.vy = vy;
    }
}
void s03d_800CE720(Work *work, int arg)
{
    int status;

    work->target->class |= TARGET_FLAG;
    status = work->pad.press;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        if (status & 0x10000)
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
    if (!(status & 0x30000))
    {
        SetMode(work, s03d_800CE12C);
        return;
    }
    if (status & 0x40000)
    {
        SetModeNoAdjust(work, s03d_800CE8F4);
        return;
    }
    if (status & 0x80000)
    {
        SetModeNoAdjust(work, s03d_800CE9E8);
        return;
    }
    if (status & 0x100000)
    {
        SetModeNoAdjust(work, s03d_800CEB38);
        return;
    }
    if (status & 0x200000)
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
void s03d_800CE8F4(Work *work, int arg)
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        if (work->pad.press & 0x10000)
        {
            SetAction(work, 4, 0);
        }
        else
        {
            SetAction(work, 6, 0);
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
        SetModeNoAdjust(work, s03d_800CE720);
    }
}
void s03d_800CE9E8(Work *work, int arg)
{
    SVECTOR *rot;
    work->target->class |= TARGET_FLAG;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    rot = &work->control.rot;
    if (arg == 1 || arg == 7)
    {
        rot->vy = ((u_short)rot->vy - 0x100) & 0xFFF;
    }
    if (arg == 3 || arg == 5)
    {
        rot->vy = ((u_short)rot->vy + 0x100) & 0xFFF;
    }
    if (arg == 2 || arg == 4 || arg == 6)
    {
        SetAction(work, 6, 0);
        Zako_800D0EF0(work, 3);
    }
    Zako_800CDD94(work);
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            SetMode(work, s03d_800CE720);
        }
        work->control.rot.vy = rot->vy;
    }
}
void s03d_800CEB38(Work *work, int arg)
{
    SVECTOR *pos;
    SVECTOR *step;
    SVECTOR *target;
    SVECTOR  out;
    SVECTOR  rot;
    SVECTOR  svec;
    int      dist;

    if (arg == 0)
    {
        SetAction(work, 7, 4);
    }
    if (arg == 17)
    {
        GM_SeSet(&work->control.mov, 0x2C);
    }
    if (arg == 45)
    {
        if (work->param.index == 2)
        {
            pos = &ThrowPos2;
        }
        else
        {
            pos = &ThrowPos;
        }
        target = &work->throw_pos;
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
void s03d_800CECBC(Work *work, int arg)
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        SetAction(work, 8, 0);
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
        SetMode(work, s03d_800CE720);
    }
}
void s03d_800CED94(Work *work, int arg)
{
    work->vision.length = 0;
    if (arg == 0)
    {
        SetAction(work, 19, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    work->target->class |= TARGET_FLAG;
    if (work->body.is_end)
    {
        work->field_8F8 = 1;
        SetMode(work, s03d_800CE12C);
    }
}
void s03d_800CEE3C(Work *work, int arg)
{
    TARGET  *target;
    CONTROL *ctrl;
    int      diff;

    target = work->target;
    ctrl = &work->control;
    work->act.field_1C = 0;
    if (arg == 0)
    {
        work->act.field_14 = 6;
        SetAction(work, 27, 4);
    }
    if (arg >= 8 && arg <= 17)
    {
        Zako_800CDF2C(work);
    }
    if (work->act.motion1 == 0x1B)
    {
        if (arg == 22)
        {
            diff = ctrl->mov.vy - ctrl->levels[0];
            if (diff < 2000)
            {
                GM_SeSet(&ctrl->mov, 0x8D);
                GM_SeSet(&ctrl->mov, 0x33);
                Zako_800D0B18(work, 6, 0);
                GM_SetNoise(100, 4, &ctrl->mov);
            }
            else if (diff > 4000)
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
        Zako_800D0B18(work, 6, 1);
        if (work->target->vital <= 0)
        {
            SetMode(work, s03d_800D01C4);
        }
        else
        {
            SetMode(work, s03d_800CF68C);
        }
    }
    if (arg < 24)
    {
        ctrl->turn = *target->field_1C;
    }
    if (arg < 22)
    {
        work->control.hzd_height = -32767;
    }
}
void s03d_800CF114(Work *work)
{
    SVECTOR vec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&CatchOffset, &vec, 1);
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
        Zako_800D0B18(work, 5, 0);
        GM_SeSet(&work->control.mov, 0x8F);

        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = 0;

        if (target->vital <= 0)
        {
            if (target->a_mode == 1)
            {
                work->field_BA0 = 1;
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
            s03d_dword_800DC2F4 = 4;
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
void s03d_800CF4D4(Work *work, int arg)
{
    if (arg == 0)
    {
        SetAction(work, 34, 4);
    }
    if (work->body.is_end)
    {
        SetMode(work, s03d_800D01C4);
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
        SetAction(work, 28, 4);
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
        SetAction(work, 33, 4);
    }
    else
    {
        work->target->class |= TARGET_FLAG;
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
        SetMode(work, s03d_800CF68C);
    }
}
void s03d_800CF68C(Work *work, int time)
{
    int x;

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
            x = work->control.mov.vx % 90;
        }
        else
        {
            x = work->control.mov.vx % 30;
        }
        if (x < 0)
        {
            x = -x;
        }
        work->field_AF6 = x + 10;
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
void s03d_800CF844(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            SetAction(work, 42, 4);
        }
        else
        {
            SetAction(work, 43, 4);
        }
        GM_SeSet(&work->control.mov, 0x36);
    }
    if (arg == 4)
    {
        Zako_800D0BEC(work, 0);
    }
    if (work->body.is_end)
    {
        SetMode(work, s03d_800D01C4);
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
                SetAction(work, 40, 4);
            }
            else
            {
                SetAction(work, 38, 4);
            }
        }
        else
        {
            if (work->field_AF6 >= 0x96)
            {
                SetAction(work, 41, 4);
            }
            else
            {
                SetAction(work, 39, 4);
            }
        }
    }
    if (work->body.is_end)
    {
        SetMode(work, s03d_800CE12C);
    }
}
void s03d_800CFA04(Work *work, int arg)
{
    TARGET *t;
    work->act.field_1C = 0;
    work->target->class |= TARGET_FLAG;
    work->vision.length = 0xFA0;
    if (Zako_800CDA04(work))
    {
        return;
    }
    t = work->target;
    if (arg == 0)
    {
        SetAction(work, 15, 4);
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
        SetMode(work, s03d_800CE12C);
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
            Zako_800D0B18(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 1:
            SetAction(work, 33, 4);
            if (work->target->vital <= 0)
            {
                if (GM_Weapon == WP_Rifle)
                {
                    Zako_800D0B18(work, 6, 2);
                }
                else
                {
                    Zako_800D0B18(work, 6, 1);
                }
            }
            else
            {
                Zako_800D0B18(work, 5, 0);
            }
            GM_SeSet(&control->mov, SE_V_ENE_PUNCHED);
            work->field_AF6 = 46;
            break;
        case 3:
            GM_SeSet(&control->mov, SE_EDMG01);
            SetAction(work, 31, 4);
            Zako_800D0B18(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 2:
            GM_SeSet(&control->mov, SE_V_ENE_THROWN);
            SetAction(work, 32, 4);
            Zako_800D0B18(work, 5, 0);
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
            Zako_800D0B18(work, 6, 0);
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
    if (work->act.motion1 < 35)
    {
        if (work->body.is_end)
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
        }
    }
    else if (ctrl->grounded)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet(&ctrl->mov, SE_HIT_FLOOR);
        Zako_800D0B18(work, 6, 1);
        SetMode(work, s03d_800D01C4);
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
                SetAction(work, 47, 4);
            }
            else
            {
                SetAction(work, 45, 4);
            }
        }
        else
        {
            SetAction(work, 46, 4);
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
        SetMode(work, s03d_800D0324);
    }
}

const char ItemMsgFamas[] = "FA-MAS/BULLET * 25";
const char ItemMsgSocom[] = "SOCOM/BULLET * 12";
const char ItemMsgRation[] = "RATION";

void s03d_800D0324(Work *work, int arg)
{
    if (arg == 0)
    {
        work->visible = 0;
        work->control.mov = s03d_dword_800C3B88;
        ZakoCommand.watchers[work->param.index].field_4 = 1;
        if (work->field_BA0 == 0)
        {
            GM_EnemyKillCount++;
        }
    }

    if (ZakoCommand.watchers[work->param.index].field_4 != 2)
    {
        return;
    }

    s03d_800CDB5C(work);
    SetMode(work, s03d_800CE12C);
}
int Zako_800D0408(Work *work)
{
    return work->control.mov.vx >= 0x1195;
}
void s03d_800D041C(Work *work)
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
    work->field_8F8 = 0;
    work->field_B9C = 0;

    control->height = work->body.height;
    control->hzd_height = control->levels[0] + 750;

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
        control->r_sphere = GV_NearExp2(control->r_sphere, act->r_sphere);
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

    if (ZakoCommand.watchers[work->param.index].field_4 == 1)
    {
        work->hom->flag = 0;
    }

    if (Zako_800D0408(work) == 0)
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

    work->last_vital = work->target->vital;
}
void s03d_800D05DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[9], 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 1))
    {
        UnsetMode(work);
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = ((u_short)work->control.rot.vy - (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = ((u_short)work->control.rot.vy - 0x400) & 0xFFF;
    }
}
void s03d_800D0698(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[10], 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 2))
    {
        UnsetMode(work);
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = ((u_short)work->control.rot.vy + (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = ((u_short)work->control.rot.vy + 0x400) & 0xFFF;
    }
}
void s03d_800D0754(Work *work, int arg1)
{
    work->vision.length = 0x7D0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[11], 0, 4, 0x3FE);
    }
    if (!(work->pad.press & 4))
    {
        UnsetMode(work);
    }
}
void s03d_800D07DC(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[22], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        UnsetMode(work);
    }
}
void s03d_800D085C(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[20], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        UnsetMode(work);
    }
}
void s03d_800D08DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[21], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        UnsetMode(work);
    }
}
void s03d_800D0958(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[17], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        UnsetMode(work);
    }
}
void s03d_800D09D8(Work *work, int arg1)
{
    SVECTOR pos;

    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ZakoActionTable[18], 0, 4, 0x3FE);
        if (work->control.map->index == GM_PlayerMap && GV_RandU(12) >= 5)
        {
            work->pad.sound = 0xF0;
        }
    }
    if (arg1 == 20)
    {
        pos = work->control.mov;
        pos.vy += 500;
        AN_Sleep(&pos);
    }
    if (work->pad.press & 0x1000)
    {
        SetMode(work, s03d_800CED94);
        UnsetMode(work);
    }
    else if (arg1 == 0x82)
    {
        UnsetMode(work);
    }
}
void Zako_800D0B18(Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&BloodPos);
    DG_RotatePos(&BloodRot);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
}
void Zako_800D0B88(Work *work)
{
    MATRIX  m;
    SVECTOR sv;

    DG_SetPos(&work->body.objs->objs[1].world);
    DG_MovePos(&FogPos);
    DG_RotatePos(&FogRot);
    ReadRotMatrix(&m);
    sv.vx = m.t[0];
    sv.vy = m.t[1];
    sv.vz = m.t[2];
    AN_Fog(&sv);
}
void Zako_800D0BEC(Work *work, int type)
{
    SVECTOR   step = work->act.field_0C;
    SVECTOR  *pos = &work->control.mov;
    ITEM_INFO info;

    if (type >= 0)
    {
        if (type < 2)
        {
            info.type = 4;
            info.id = IT_Ration;
            info.num = 1;
            info.message = ItemMessages[0];
        }
        else if (type < 4)
        {
            info.type = 2;
            info.id = WP_Socom;
            info.num = 0xC;
            info.message = ItemMessages[1];
        }
    }
    info.time = 0x384;
    NewItemPut(pos, &step, &info);
}
void s03d_800D0C90(Work *work, int mark)
{
    if (work->control.map->index == GM_PlayerMap)
    {
        AN_HeadMark(&work->body.objs->objs[6].world, mark);
    }
}

void s03d_800D0CD4(Work *work)
{
    int action = work->act.motion1;
    int frame = work->m_ctrl.info1.frame;
    int l = 160 + (work->param.index % 4) * 2;
    int r = 160 + (work->param.index % 4) * 2 + 1;

    if (action == 1)
    {
        if (frame == 22)
        {
            GM_SeSet(&work->control.mov, r);
        }
        else if (frame == 11)
        {
            GM_SeSet(&work->control.mov, l);
        }
    }
    else if (action == 2)
    {
        if (frame == 16)
        {
            GM_SeSet(&work->control.mov, r);
        }
        else if (frame == 8)
        {
            GM_SeSet(&work->control.mov, l);
        }
    }
}

void s03d_800D0D6C(Work *work)
{
    if (ZakoCommand.alert_mode == 1)
    {
        return;
    }
    if (!(work->control.map->index == GM_PlayerMap))
    {
        return;
    }
    if (GV_Time % 64 == work->param.index * 16)
    {
        AN_Breath(&work->body.objs->objs[6].world);
    }
}

void s03d_800D0DF0(Work *work)
{
    if (work->vision.pad == 2)
    {
        NewLSight(&GM_PlayerPosition, &work->control.mov, 0x8F);
    }
}

void s03d_800D0E2C(Work *work)
{
    MATRIX  m;
    MATRIX *world;

    world = &work->body.objs->objs[4].world;
    DG_SetPos(world);
    DG_MovePos(&MuzzlePos);
    DG_RotatePos(&MuzzleRot);
    ReadRotMatrix(&m);
    NewBulletEx(0x100, &m, 2, 1, 0, 10, work->param.damage, 10000, 750);
    GM_SeSet(&work->control.mov, 0x2D);
    AN_BulletSmoke(world, 0);
    AN_FamasFlash(&m);
    Zako_800D0F38(work, s03d_800D0E2C);
}
int Zako_800D0EF0(Work *work, int index)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->putchar[i] == NULL)
        {
            work->putchar[i] = PutChars[index];
            return 1;
        }
    }
    return 0;
}
int Zako_800D0F38(Work *work, PUTFUNC func)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->putchar[i] == func)
        {
            work->putchar[i] = NULL;
            return 1;
        }
    }
    return 0;
}
void Zako_800D0F6C(Work *work)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->putchar[i])
        {
            work->putchar[i](work);
        }
    }
}
void Zako_800D0FCC(Work *work)
{
    VISION            *vision = &work->vision;
    RADAR_SIGHT_PARAM *rp = &work->control.radar_param;

    rp->dir = vision->facedir;
    rp->dis = vision->length;
    rp->range = vision->range;
    rp->r = 0;
}

void Zako_800D0FF4(Work *work)
{
    if (work->modetime[7] & 4)
    {
        if (work->target->damaged & 6)
        {
            work->modetime[6] |= 4;
        }
        if (work->attack.damaged & 0x80)
        {
            work->vision.pad = 2;
        }
    }
}
int s03d_800D1054(HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2)
{
    int from;
    int to;

    from = HZD_GetAddress(hzd, pos, -1);
    to = HZD_GetAddress(hzd, pos2, -1);
    from &= 0xFF;
    to &= 0xFF;
    return HZD_ZoneDistance(hzd, from, to);
}

void s03d_800D10B4(Work *work)
{
    CONTROL *ctrl;
    int      dist;

    if (!(work->modetime[7] & 1))
    {
        return;
    }

    ctrl = &work->control;
    if (ctrl->map->index != GM_PlayerMap)
    {
        return;
    }

    if (!GM_NoisePower)
    {
        return;
    }

    switch (GM_NoisePower)
    {
    case 5:
        if (GV_DiffVec3(&GM_NoisePosition, &ctrl->mov) < 500)
        {
            break;
        }
        return;
    case 200:
        if (GV_DiffVec3(&GM_NoisePosition, &ctrl->mov) < 4000)
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        dist = GV_DiffVec3(&GM_NoisePosition, &ctrl->mov);
        fprintf(1, "noise dis  =%d,\n", dist);
        if (dist < 4000)
        {
            dist = s03d_800D1054(ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition);
            if (dist < 300)
            {
                work->modetime[6] |= 1;
                GM_NoiseLength = 0;
                GM_NoisePower = 0;
            }
        }
        return;
    default:
        return;
    }
    work->modetime[6] |= 1;
}

void s03d_800D123C(Work *work)
{
    if ((work->modetime[7] & 2) && work->vision.pad == 2 && (GM_PlayerStatus & PLAYER_CB_BOX))
    {
        if (GV_DiffVec3(&work->player_pos, &GM_PlayerPosition) > 50 || work->player_dir != GM_WhereList[0]->rot.vy)
        {
            if (ZakoCommand.alert_mode == 1)
            {
                return;
            }
            work->player_pos = GM_PlayerPosition;
            work->player_dir = GM_WhereList[0]->rot.vy;
            work->modetime[6] |= 2;
        }
        work->vision.pad = 0;
    }
}

void s03d_800D1324(Work *work)
{
    CONTROL *ctrl;
    HZD_HDL *hzd;
    VISION  *vision;

    if (!(work->modetime[7] & 0x10))
    {
        return;
    }

    if (work->think2 == 5)
    {
        return;
    }

    ctrl = &work->control;
    hzd = work->control.map->hzd;
    vision = &work->vision;
    if (!AsiatoCheck(hzd, &ctrl->mov))
    {
        return;
    }

    if (SearchNearAsiato(hzd, &ctrl->mov, vision->facedir, vision->range, vision->length) < 0)
    {
        return;
    }

    work->modetime[6] |= 0x10;
    fprintf(1, " Asiato mikke!! [%d]\n", NearAsiato());
}
void Zako_800D13E8(Work *work)
{
    SVECTOR unused[2];

    (void)unused;
    work->modetime[6] = 0;
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

void s03d_800D14AC(Work *work)
{
    SVECTOR  diff;
    SVECTOR *pos;
    CONTROL *control;
    int      height;

    control = &work->control;
    GV_SubVec3(&s03d_dword_800C3AB0, &control->mov, &diff);
    work->field_B98 = GV_VecDir2(&diff);
    pos = &GM_PlayerPosition;
    GV_SubVec3(pos, &control->mov, &diff);
    diff.vy = 0;
    work->sn_dir = GV_VecDir2(&diff);
    work->sn_dis = GV_VecLen3(&diff);

    /* unused result, but it keeps pos live across the calls */
    height = ABS(pos->vy - work->control.mov.vy);
    work->vision.pad = 2;
}

void s03d_800D153C(Work *work)
{
    if (work->act.motion1 < 0x2D)
    {
        Zako_800D0FCC(work);
        s03d_800D14AC(work);
        Zako_800D13E8(work);
        s03d_800D13F8(work);
        s03d_800D3B5C(work);
        Zako_800D0F6C(work);
    }
    s03d_800D041C(work);
}

void s03d_800D15A8(Work *work)
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

    last_set = work->act.motion1;
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
        ctrl->r_sphere = GV_NearExp2(ctrl->r_sphere, work->act.r_sphere);
    }
}
