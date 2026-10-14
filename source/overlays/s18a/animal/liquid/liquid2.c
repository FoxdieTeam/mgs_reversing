#include "liquid.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "linkvar.h"
#include "mts/mts.h" // for fprintf
#include "okajima/blood.h"
#include "anime/animconv/anime.h"
#include "takabe/cineutil.h"

/* Liquid's brain and moves (a cut-down copy of the snake code), original file name unknown */

void s18a_800CC4F0(LiquidWork *work);
void s18a_800CC56C(LiquidWork *work);
void s18a_800CC574(LiquidWork *work);

short s18a_liquid_motions[40] = {
    0, 0, 1, 2, 37, 2, 36, 38, 3, 4, 23, 7, 5, 6, 9, 8, 11, 10, 29, 12,
    13, 17, 18, 19, 15, 16, 20, 21, 22, 27, 24, 25, 26, 30, 31, 32, 33, 34, 35, 28
};
SVECTOR s18a_dword_800C3368 = {2500, 10000, 500, 0};
SVECTOR s18a_dword_800C3370 = {0, 0, -1000, 0};
SVECTOR s18a_dword_800C3378 = {0, 0, 100, 0};
SVECTOR s18a_dword_800C3380 = {-1024, 0, 0, 0};
void *s18a_dword_800C3388[] = {s18a_800CC4F0, s18a_800CC56C, s18a_800CC574};
SVECTOR s18a_dword_800C3394 = {5, -500, 80, 0};
SVECTOR s18a_dword_800C339C[4][2] = {
    {{3125, 12000, 750, 0}, {-125, 12000, 500, 0}},
    {{3125, 12000, -750, 0}, {-125, 12000, -500, 0}},
    {{1875, 12000, 750, 0}, {5125, 12000, 500, 0}},
    {{1875, 12000, -750, 0}, {5125, 12000, -500, 0}},
};
SVECTOR s18a_dword_800C33DC[4][2] = {
    {{5125, 12000, 250, 0}, {3125, 12000, -1000, 0}},
    {{5125, 12000, -250, 0}, {3125, 12000, 1000, 0}},
    {{-125, 12000, 250, 0}, {1875, 12000, -1000, 0}},
    {{-125, 12000, -250, 0}, {1875, 12000, 1000, 0}},
};
SVECTOR s18a_dword_800C341C[4][2] = {
    {{3750, 12000, 1250, 0}, {5250, 12000, 1000, 0}},
    {{3750, 12000, -750, 0}, {5250, 12000, -1000, 0}},
    {{1000, 12000, 1250, 0}, {-500, 12000, 1000, 0}},
    {{1000, 12000, -750, 0}, {-500, 12000, -1000, 0}},
};
int s18a_dword_800C345C = 0x00000000;
int s18a_dword_800C3460 = 0x00000000;
int s18a_dword_800C3464 = 0x00000000;
int s18a_dword_800C3468[4] = {14, 15, 6, 5};
int s18a_dword_800C3478[2] = {6, 2};
int s18a_dword_800C3480 = 0x00000000;
int s18a_dword_800C3484 = 0x00000000;
int s18a_dword_800C3488 = 0x00000000;
int s18a_dword_800C348C = 0x00000000;
int s18a_dword_800C3490 = 0x00000000;
int s18a_dword_800C3494 = 0x00000000;
int s18a_dword_800C3498 = 0x00000000;
int s18a_dword_800C349C = 0x00000000;

static inline void s18a_liquid_SetAct(LiquidWork *work, void *act)
{
    work->act = act;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s18a_800C84B8(LiquidWork *work, int time);
void s18a_800C8558(LiquidWork *work, int time);
void s18a_800C863C(LiquidWork *work, int time);
void s18a_800C8754(LiquidWork *work, int time);
void s18a_800C886C(LiquidWork *work, int time);
void s18a_800C8990(LiquidWork *work, int time);
void s18a_800C8A8C(LiquidWork *work, int time);
void s18a_800C8BB0(LiquidWork *work, int time);
void s18a_800CB56C(LiquidWork *work, int time);
void s18a_800C91D4(LiquidWork *work, int time);
void s18a_800C9384(LiquidWork *work, int time);
void s18a_800C8CD4(LiquidWork *work, int time);
void s18a_800C8DC4(LiquidWork *work, int time);
void s18a_800C8EBC(LiquidWork *work, int time);
void s18a_800C9044(LiquidWork *work, int time);
void s18a_800C9534(LiquidWork *work, int time);
void s18a_800C966C(LiquidWork *work, int time);
void s18a_800C97AC(LiquidWork *work, int time);
void s18a_800C990C(LiquidWork *work, int time);
void s18a_800C9A0C(LiquidWork *work, int time);
void s18a_800C9B20(LiquidWork *work, int time);
void s18a_800C9C2C(LiquidWork *work, int time);
void s18a_800CA1A4(LiquidWork *work, int time);
void s18a_800CA3B4(LiquidWork *work, int time);
void s18a_800CA440(LiquidWork *work, int time);
void s18a_800CA6E0(LiquidWork *work, int time);
void s18a_800CA9FC(LiquidWork *work, int time);
void s18a_800CAD88(LiquidWork *work, int time);
void s18a_800CB114(LiquidWork *work, int time);
void s18a_800CB310(LiquidWork *work, int time);
void s18a_800CB418(LiquidWork *work, int time);
void s18a_800CB640(LiquidWork *work, int time);
void s18a_800CB9D0(LiquidWork *work, int time);
void s18a_800CBB50(LiquidWork *work, int time);
void s18a_800CBF38(LiquidWork *work, int time);
void s18a_800CC0F0(LiquidWork *work, int time);
static inline void s18a_liquid_ResetOverride(LiquidWork *work)
{
    GM_ConfigObjectOverride(&work->body, s18a_liquid_motions[0], 0, 4, 0);
    work->act2 = 0;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void s18a_liquid_SetPose(LiquidWork *work, int pose)
{
    work->pose = pose;
    GM_ConfigObjectAction(&work->body, s18a_liquid_motions[pose], 0, 4);
}

int  s18a_800C7684(LiquidWork *work);
void s18a_800C82A4(LiquidWork *work, int time);
void s18a_800C839C(LiquidWork *work, int time);
static inline int s18a_liquid_Scale(int value, int scale)
{
    return value * scale / 4096;
}

static inline int s18a_liquid_After(int time, int start)
{
    return time > start;
}

void s18a_800CC488(LiquidWork *work, int arg1);
void s18a_800CB780(LiquidWork *work, int time);
void s18a_800CB8AC(LiquidWork *work, int time);
extern int s18a_dword_800E3EF0;
void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
int s18a_800CC6A8(LiquidWork *work, void *func);
void s18a_800CC1F0(LiquidWork *work);
void s18a_800CC278(LiquidWork *work);
void s18a_800D0D28(LiquidWork *work);
void s18a_800CC2A0(LiquidWork *work);
int s18a_800CC9E4(SVECTOR *pos);
int s18a_800CCA20(int area, int dir);
int s18a_800CCA88(int area, int dir);
int s18a_800CCAE0(int area, int dir);
int s18a_800CCB38(int area, int dir);
int s18a_800CCB90(int area, int dir);
int s18a_800CCBE8(int area, int dir);
void  s18a_800CCDA8(void);
void  s18a_liquid_800C5200(int mode);
void *NewCountdown(int time, int proc);
void  SetCountdownTime(int time);
static inline void s18a_liquid_SetPhase(LiquidWork *work, int phase)
{
    work->f964 = phase;
    work->f97C = 0;
    work->f968 = 0;
}
/*--FUNCS--*/

int s18a_800C722C(SVECTOR *pos, short *out)
{
    int vz = pos->vz;
    int vx = pos->vx;

    if (vz >= 0x128F)
    {
        printf("climb area  0 \n");
        *out = 0x800;
        return 0;
    }
    if (vz < -0x4E2)
    {
        printf("climb area  4 \n");
        *out = 0xFE8;
        return 4;
    }
    if (vx < -0x2EE)
    {
        printf("climb area  3 \n");
        *out = 0x400;
        return 3;
    }
    if (vx < 0x4E2)
    {
        printf("climb area  2 \n");
        *out = 0x6D2;
        return 2;
    }
    if (vx < 0x9C4)
    {
        printf("climb area  1 \n");
        *out = 0x480;
        return 1;
    }
    if (vx < 0xCB2)
    {
        printf("climb area  7 \n");
        *out = 0xB42;
        return 7;
    }
    else if (vx < 0x157C)
    {
        printf("climb area  6 \n");
        *out = 0x911;
        return 6;
    }
    else
    {
        printf("climb area  5 \n");
        *out = 0xBE8;
        return 5;
    }
}

int s18a_800C736C(LiquidWork *work)
{
    if (work->cmd == 0)
    {
        return 0;
    }

    switch (work->cmd)
    {
    case 1:
        s18a_liquid_SetAct(work, s18a_800C84B8);
        return 1;
    case 2:
        s18a_liquid_SetAct(work, s18a_800C8558);
        return 1;
    case 3:
        s18a_liquid_SetAct(work, s18a_800C863C);
        return 1;
    case 4:
        s18a_liquid_SetAct(work, s18a_800C8754);
        return 1;
    case 5:
        s18a_liquid_SetAct(work, s18a_800C886C);
        return 1;
    case 6:
        s18a_liquid_SetAct(work, s18a_800C8990);
        return 1;
    case 7:
        s18a_liquid_SetAct(work, s18a_800C8A8C);
        return 1;
    case 8:
        s18a_liquid_SetAct(work, s18a_800C8BB0);
        return 1;
    case 9:
        s18a_liquid_SetAct(work, s18a_800CB56C);
        return 1;
    case 10:
        s18a_liquid_SetAct(work, s18a_800C91D4);
        return 1;
    case 11:
        s18a_liquid_SetAct(work, s18a_800C9384);
        return 1;
    case 12:
        s18a_liquid_SetAct(work, s18a_800C8CD4);
        return 1;
    case 13:
        s18a_liquid_SetAct(work, s18a_800C8DC4);
        return 1;
    case 14:
        s18a_liquid_SetAct(work, s18a_800C8EBC);
        return 1;
    case 15:
        s18a_liquid_SetAct(work, s18a_800C9044);
        return 1;
    case 16:
        s18a_liquid_SetAct(work, s18a_800C9534);
        return 1;
    case 17:
        s18a_liquid_SetAct(work, s18a_800C966C);
        return 1;
    case 18:
        s18a_liquid_SetAct(work, s18a_800C97AC);
        return 1;
    case 19:
        s18a_liquid_SetAct(work, s18a_800C990C);
        return 1;
    case 20:
        s18a_liquid_SetAct(work, s18a_800C9A0C);
        return 1;
    case 21:
        s18a_liquid_SetAct(work, s18a_800C9B20);
        return 1;
    case 22:
        s18a_liquid_SetAct(work, s18a_800C9C2C);
        return 1;
    case 23:
        s18a_liquid_SetAct(work, s18a_800CA1A4);
        return 1;
    case 30:
        s18a_liquid_SetAct(work, s18a_800CA3B4);
        return 1;
    case 24:
        s18a_liquid_SetAct(work, s18a_800CA440);
        return 1;
    case 25:
        s18a_liquid_SetAct(work, s18a_800CA6E0);
        return 1;
    case 26:
        s18a_liquid_SetAct(work, s18a_800CA9FC);
        return 1;
    case 27:
        s18a_liquid_SetAct(work, s18a_800CAD88);
        return 1;
    }

    return 0;
}

int s18a_800C7584(LiquidWork *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        fprintf(1, "WEAPON=0x%x a_mode=0x%x p_faint=%d\n", GM_Weapon, target->a_mode, target->faint);

        switch (target->a_mode)
        {
        case 3:
            target->force = DG_ZeroVector;
            s18a_liquid_SetAct(work, s18a_800CB310);
            break;

        case 4:
            if (work->life < 64)
            {
                s18a_liquid_SetAct(work, s18a_800CB640);
            }
            else
            {
                s18a_liquid_SetAct(work, s18a_800CB418);
            }
            break;
        }

        target->damage = 0;
        target->damaged = 0;
        return 1;
    }

    return 0;
}

const int s18a_dword_800E2EA0 = 0x25736F70;
const int s18a_dword_800E2EA4 = 0x64252064;
const int s18a_dword_800E2EA8 = 0x20642520;
const int s18a_dword_800E2EAC = 0x0000000A;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800C7684.s")
int s18a_800C7878(LiquidWork *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 0x24)
        {
            s18a_liquid_SetAct(work, s18a_800CB9D0);
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800CC0F0);
            GM_ConfigMotionAdjust(&work->body, NULL);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s18a_800C7904(LiquidWork *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        switch (target->a_mode)
        {
        case 3:
            target->force = DG_ZeroVector;
            s18a_liquid_SetAct(work, s18a_800CB56C);
            break;

        case 4:
            s18a_liquid_SetAct(work, s18a_800CB114);
            break;
        }

        target->damage = 0;
        target->damaged = 0;
        return 1;
    }

    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 0x24)
        {
            s18a_liquid_SetAct(work, s18a_800CB9D0);
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800CC0F0);
            GM_ConfigMotionAdjust(&work->body, NULL);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s18a_800C7A18(LiquidWork *work)
{
    if (!s18a_800C7584(work) && !s18a_800C7878(work))
    {
        return 0;
    }

    work->target->class = 1;
    return 1;
}

int s18a_800C7A68(LiquidWork *work, int type)
{
    SVECTOR  force;
    SVECTOR  pos0 = {-200, 1000, 600};
    SVECTOR  pos1 = {200, 1000, 600};
    SVECTOR  pos2 = {0, 1000, 900};
    SVECTOR  pos3 = {0, 0, 900};
    SVECTOR  pos4 = {0, 1000, 900};
    SVECTOR  pos5 = {0, 1000, 900};
    SVECTOR  pos6 = {0, -1000, 500};
    SVECTOR  pos7 = {0, -3000, 1000};
    SVECTOR  pos8 = {0, 1000, 500};
    SVECTOR  pos9 = {0, 1000, 0};
    SVECTOR  size0 = {200, 400, 500};
    SVECTOR  size1 = {200, 400, 300};
    SVECTOR  size2 = {200, 500, 700};
    SVECTOR  size3 = {400, 500, 700};
    SVECTOR  force0 = {0, 0, 50};
    SVECTOR  force1 = {0, 0, 0};
    SVECTOR  force2 = {5, 200, 100};
    TARGET  *target;

    target = &work->attack;
    DG_SetPos2(&work->control.mov, &work->control.rot);

    switch (type)
    {
    case 0:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 3, work->damage2[0], 1, &force);
        DG_PutVector(&pos0, &target->center, 1);
        break;

    case 1:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 3, work->damage2[0], 1, &force);
        DG_PutVector(&pos1, &target->center, 1);
        break;

    case 2:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size2);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 2, work->damage2[1], 1, &force);
        DG_PutVector(&pos2, &target->center, 1);
        break;

    case 3:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size2);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 2, work->damage2[1], 1, &force);
        DG_PutVector(&pos4, &target->center, 1);
        break;

    case 4:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
        DG_RotVector(&force2, &force, 1);
        GM_SetPowerTarget(target, 0, 2, work->damage2[2], 1, &force);
        DG_PutVector(&pos5, &target->center, 1);
        break;

    case 5:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size3);
        DG_RotVector(&force1, &force, 1);
        GM_SetPowerTarget(target, 0, 3, work->damage2[3], 1, &force);
        DG_PutVector(&pos6, &target->center, 1);
        break;

    case 6:
        if (GM_GameLevel < 4)
        {
            if (GM_GameLevel > 0)
            {
                GM_SetTarget(target, 4, ENEMY_SIDE, &size1);
            }
            else
            {
                GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
            }
        }
        else
        {
            GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
        }
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 2, work->damage2[4], 1, &force);
        DG_PutVector(&pos8, &target->center, 1);
        break;

    case 7:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size0);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 2, 100, 1, &force);
        DG_PutVector(&pos9, &target->center, 1);
        break;

    case 8:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size3);
        DG_RotVector(&force1, &force, 1);
        GM_SetPowerTarget(target, 0, 3, work->damage2[3], 1, &force);
        DG_PutVector(&pos7, &target->center, 1);
        break;

    case 9:
        GM_SetTarget(target, 4, ENEMY_SIDE, &size2);
        DG_RotVector(&force0, &force, 1);
        GM_SetPowerTarget(target, 0, 2, work->damage2[1], 1, &force);
        DG_PutVector(&pos3, &target->center, 1);
        break;
    }

    return GM_PowerTarget(target);
}

int s18a_800C80B8(LiquidWork *work, int type)
{
    SVECTOR  size0 = {400, 200, 400};
    SVECTOR  pos0 = {0, 1000, 500};
    SVECTOR  size1 = {1000, 200, 1000};
    SVECTOR  pos1 = {0, 1000, -500};
    TARGET  *target;
    SVECTOR *size;
    SVECTOR *pos;

    target = &work->attack;

    if (type == 1)
    {
        size = &size1;
        pos = &pos1;
    }
    else
    {
        size = &size0;
        pos = &pos0;
    }

    GM_SetTarget(target, 2, 2, size);
    GM_SetCaptureTarget(target, 0, 0, &work->f918, &work->f920);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(pos, &target->center, 1);

    work->f928 = GM_CaptureTarget(target);
    return work->f928 != 0;
}

void s18a_800C8210(LiquidWork *work)
{
    int dir;
    int diff;

    dir = ratan2(work->f9B0, GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1]);
    dir = (dir & 0xFFF) - 1024;

    if (dir > 512)
    {
        dir = 512;
    }
    else if (dir < -512)
    {
        dir = -512;
    }

    work->adjust[6].vx = dir;

    diff = GV_DiffDirS(work->control.rot.vy, work->f9AC);
    if (diff >= -511 && diff < 512)
    {
        work->adjust[6].vy = diff;
    }
}

void s18a_800C82A4(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 0);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    s18a_800C8210(work);

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (s18a_800C736C(work))
    {
        s18a_liquid_ResetOverride(work);
        return;
    }

    if (work->f954 >= 0)
    {
        s18a_liquid_SetAct(work, s18a_800C839C);
    }

    work->target->class |= 0x17;
}

void s18a_800C839C(LiquidWork *work, int time)
{
    int      dir;
    CONTROL *control;

    dir = work->f954;
    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 8);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (s18a_800C736C(work))
    {
        s18a_liquid_ResetOverride(work);
        return;
    }

    if (dir < 0)
    {
        s18a_liquid_SetAct(work, s18a_800C82A4);
        s18a_liquid_ResetOverride(work);
        return;
    }

    control->turn.vy = dir;
    work->target->class |= 0x17;
}

void s18a_800C84B8(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 6);
    }

    if (time == 53)
    {
        GM_SeSet(&work->control.mov, 50);
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C8990);
    }
    else
    {
        work->target2->class = 1;
    }
}

void s18a_800C8558(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 7);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    if (work->body.is_end)
    {
        s18a_liquid_SetPose(work, 4);
    }

    if (work->cmd == 2)
    {
        return;
    }

    if (s18a_800C736C(work))
    {
        s18a_liquid_ResetOverride(work);
    }
    else
    {
        s18a_liquid_SetAct(work, s18a_800C82A4);
    }
}

void s18a_800C863C(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 1);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->f954 >= 0)
    {
        work->control.turn.vy = work->f954;
    }

    if (work->cmd != 3)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8754(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 2);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->f954 >= 0)
    {
        work->control.turn.vy = work->f954;
    }

    if (work->cmd != 4)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C886C(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 3);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (GV_DiffDirAbs(work->control.rot.vy, work->f9AC) >= 1024)
    {
        work->control.turn.vy = work->f9AC;
    }

    if (work->cmd != 5)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8990(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 4);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7904(work))
    {
        return;
    }

    work->control.turn.vy = work->f9AC;

    if (work->cmd != 6)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8A8C(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 3);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (GV_DiffDirAbs(work->control.rot.vy, work->f9AC) >= 1024)
    {
        work->control.turn.vy = work->f9AC;
    }

    if (work->cmd != 7)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8BB0(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 5);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7904(work))
    {
        return;
    }

    if (GV_DiffDirAbs(work->control.rot.vy, work->f9AC) >= 1024)
    {
        work->control.turn.vy = work->f9AC;
    }

    if (work->cmd != 8)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8CD4(LiquidWork *work, int time)
{
    CONTROL *control;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 10);
        control->turn.vy = work->f954;
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->cmd != 12 || time >= 11)
    {
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8DC4(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 11);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->f954 >= 0)
    {
        work->control.turn.vy = work->f954;
    }

    if (work->body.is_end || work->cmd != 13)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C8EBC(LiquidWork *work, int time)
{
    CONTROL *control;
    int      speed;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 12);
    }

    if (time == 14)
    {
        s18a_liquid_SetPose(work, 12);
    }

    control->rot.vy = control->turn.vy = work->f9AC;

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time >= 29)
    {
        if (work->cmd == 14)
        {
            work->f940 = 1;
        }

        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (work->m_ctrl.info1.frame < 8)
    {
        speed = 12;
        control->step.vx += rsin(work->f9AC) * speed / 4096;
        control->step.vz += rcos(work->f9AC) * speed / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800C9044(LiquidWork *work, int time)
{
    CONTROL *control;
    int      speed;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 13);
    }

    if (time == 14)
    {
        s18a_liquid_SetPose(work, 13);
    }

    control->rot.vy = control->turn.vy = work->f9AC;

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time >= 29 || work->cmd != 15)
    {
        if (work->cmd == 15)
        {
            work->f940 = 1;
        }

        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (work->m_ctrl.info1.frame < 8)
    {
        speed = 12;
        control->step.vx += rsin(work->f9AC) * speed / 4096;
        control->step.vz += rcos(work->f9AC) * speed / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800C91D4(LiquidWork *work, int time)
{
    CONTROL *control;
    int      dir;
    int      speed;
    int      step;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 12);
    }

    control->rot.vy = control->turn.vy = work->f9AC;

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (work->cmd != 10)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    if (work->m_ctrl.info1.frame < 8)
    {
        control->step.vx += s18a_liquid_Scale(rsin(work->f9AC), 64);
        control->step.vz += s18a_liquid_Scale(rcos(work->f9AC), 64);

        dir = work->f9AC - 1024;
        dir &= 0xFFF;
        speed = 48;
        control->step.vx += rsin(dir) * speed / 4096;
        control->step.vz += rcos(dir) * speed / 4096;
    }
}

void s18a_800C9384(LiquidWork *work, int time)
{
    CONTROL *control;
    int      dir;
    int      speed;
    int      step;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 13);
    }

    control->rot.vy = control->turn.vy = work->f9AC;

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (work->cmd != 11)
    {
        if (s18a_800C736C(work))
        {
            s18a_liquid_ResetOverride(work);
        }
        else
        {
            s18a_liquid_SetAct(work, s18a_800C82A4);
        }
        return;
    }

    if (work->m_ctrl.info1.frame < 8)
    {
        control->step.vx += s18a_liquid_Scale(rsin(work->f9AC), 64);
        control->step.vz += s18a_liquid_Scale(rcos(work->f9AC), 64);

        dir = work->f9AC + 1024;
        dir &= 0xFFF;
        speed = 48;
        control->step.vx += rsin(dir) * speed / 4096;
        control->step.vz += rcos(dir) * speed / 4096;
    }
}

void s18a_800C9534(LiquidWork *work, int time)
{
    CONTROL *control;
    int      step;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 14);
        work->control.turn.vy = work->f954;
    }

    if (time == 3)
    {
        s18a_800C7A68(work, 0);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 4)
    {
        control->step.vx = s18a_liquid_Scale(rsin(work->f9AC), 128);
        control->step.vz = s18a_liquid_Scale(rcos(work->f9AC), 128);
    }

    work->target->class |= 0x17;
}

void s18a_800C966C(LiquidWork *work, int time)
{
    CONTROL *control;
    int      speed;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 15);
        work->control.turn.vy = work->f954;
    }

    if (time == 7)
    {
        s18a_800C7A68(work, 1);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 8)
    {
        speed = 24;
        control->step.vx = rsin(work->f9AC) * speed / 4096;
        control->step.vz = rcos(work->f9AC) * speed / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800C97AC(LiquidWork *work, int time)
{
    int      hit;
    CONTROL *control;

    hit = 0;
    control = &work->control;

    if (time == 0)
    {
        control->turn.vy = work->f9AC;
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
    }

    if (time == 6)
    {
        hit = s18a_800C7A68(work, 1);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 11)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
    }

    if (time == 15)
    {
        hit = s18a_800C7A68(work, 0);
        GM_SeSet(&control->mov, 56);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (hit)
    {
        GM_SeSet(&control->mov, 52);
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C990C(LiquidWork *work, int time)
{
    int hit;

    hit = 0;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 16);
        work->control.turn.vy = work->f9AC;
    }

    if (time == 4)
    {
        hit = s18a_800C7A68(work, 9);
        GM_SeSet(&work->control.mov, 57);
    }

    if (hit)
    {
        GM_SeSet(&work->control.mov, 52);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
    }

    work->target->class |= 0x17;
}

void s18a_800C9A0C(LiquidWork *work, int time)
{
    CONTROL *control;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 17);
        control->turn.vy = work->f9AC;
    }

    if (time == 10)
    {
        GM_SeSet(&control->mov, 57);
    }

    if (time == 12)
    {
        if (s18a_800C7A68(work, 3))
        {
            GM_SeSet(&control->mov, 53);
        }
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    control->step.vx = 0;
    control->step.vz = 0;
    work->target->class |= 0x17;
}

void s18a_800C9B20(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 18);
        work->control.turn.vy = work->f954;
    }

    if (time == 12)
    {
        if (GM_PlayerStatus & PLAYER_ACT_ONLY)
        {
            s18a_800C7A68(work, 8);
        }
        else
        {
            s18a_800C7A68(work, 5);
        }
        GM_SeSet(&work->control.mov, 180);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800C9C2C(LiquidWork *work, int time)
{
    int      speed;
    int      hit;
    CONTROL *control;
    int      frame;

    speed = 0;
    hit = 0;
    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 14);
        control->turn.vy = work->f9AC;
    }

    if (time == 3)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 12)
    {
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 19)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 30)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 33)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 40)
    {
        s18a_liquid_SetPose(work, 17);
        control->turn.vy = work->f9AC;
    }

    if (time == 52)
    {
        hit = s18a_800C7A68(work, 3);
        GM_SeSet(&control->mov, 57);
    }

    if (time == 65)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 68)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 76)
    {
        s18a_liquid_SetPose(work, 16);
        control->turn.vy = work->f9AC;
    }

    if (time == 80)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&work->control.mov, 57);
    }

    if (time == 86)
    {
        s18a_liquid_SetPose(work, 17);
        control->turn.vy = work->f9AC;
    }

    if (time == 98)
    {
        hit = s18a_800C7A68(work, 3);
        GM_SeSet(&work->control.mov, 57);
    }

    if (time == 110)
    {
        s18a_liquid_SetPose(work, 16);
        control->turn.vy = work->f9AC;
    }

    if (time == 114)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&work->control.mov, 57);
    }

    if (time == 120)
    {
        s18a_liquid_SetPose(work, 14);
        control->turn.vy = work->f9AC;
    }

    if (time == 123)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&work->control.mov, 56);
    }

    if (time == 143)
    {
        s18a_liquid_SetPose(work, 17);
        control->turn.vy = work->f9AC;
    }

    if (time == 155)
    {
        hit = s18a_800C7A68(work, 3);
        GM_SeSet(&work->control.mov, 57);
    }

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 14:
        if (frame < 4)
        {
            speed = 128;
        }
        break;

    case 15:
        if (frame < 8)
        {
            speed = 24;
        }
        break;

    case 16:
        if (frame <= 0)
        {
            speed = 128;
        }
        break;

    case 17:
        if (frame < 4)
        {
            speed = 48;
        }
        break;
    }

    if (hit)
    {
        work->time = 156;
    }

    if (work->body.is_end)
    {
        work->pose = 1;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[1], 0, 15);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 190)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    control->step.vx = speed * rsin(work->f9AC) / 4096;
    control->step.vz = speed * rcos(work->f9AC) / 4096;
    work->target->class |= 0x17;
}

void s18a_800CA1A4(LiquidWork *work, int time)
{
    int      hit;
    CONTROL *control;
    int      base;
    int      i;

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    hit = 0;
    control = &work->control;

    if (time == 0)
    {
        work->pose = 29;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[29], 0, 8);
        GM_SeSetMode(&control->mov, 132, 1);
    }

    if (time < 15)
    {
        work->control.turn.vy = work->f9AC;
    }

    base = 15;

    if (time == base)
    {
        s18a_liquid_SetPose(work, 30);
    }

    if (time == base + 2)
    {
        GM_SeSet(&control->mov, 57);
    }

    if (time == base + 16)
    {
        work->pose = 0;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[0], 0, 15);
    }

    if (time > base + 2 && time < 43)
    {
        hit = s18a_800C7A68(work, 6);
    }

    if (hit > 0)
    {
        GM_SeSet(&work->control.mov, 181);
        work->time = base + 15;
    }

    if (time > base + 4 && time < base + 15)
    {
        for (i = 0; i < control->n_touches; i++)
        {
            if (GV_DiffDirAbs(control->rot.vy, GV_VecDir2(&control->vecs[i])) < 512)
            {
                work->time = base + 15;
                break;
            }
        }
    }

    if (time > base + 61)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800CA3B4(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 32);
        s18a_800C80B8(work, 0);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
    }
}

void s18a_800CA440(LiquidWork *work, int time)
{
    int      speed;
    CONTROL *control;
    int      frame;

    speed = 0;
    control = &work->control;

    if (time == 0)
    {
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 7)
    {
        s18a_800C7A68(work, 1);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 12)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 17)
    {
        s18a_800C7A68(work, 0);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 21)
    {
        s18a_liquid_SetPose(work, 16);
        control->turn.vy = work->f9AC;
    }

    if (time == 25)
    {
        s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 57);
    }

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 14:
        speed = 4;
        if (frame < 4)
        {
            speed = 128;
        }
        break;

    case 15:
        speed = 4;
        if (frame < 8)
        {
            speed = 24;
        }
        break;

    case 16:
        speed = 4;
        if (frame <= 0)
        {
            speed = 128;
        }
        break;

    case 17:
        speed = 4;
        if (frame < 4)
        {
            speed = 48;
        }
        break;
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 40)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    control->step.vx = speed * rsin(work->f9AC) / 4096;
    control->step.vz = speed * rcos(work->f9AC) / 4096;
    work->target->class |= 0x17;
}

void s18a_800CA6E0(LiquidWork *work, int time)
{
    int      speed;
    int      hit;
    CONTROL *control;
    int      frame;

    speed = 0;
    hit = 0;
    control = &work->control;

    if (time == 0)
    {
        control->turn.vy = work->f9AC;
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
    }

    if (time == 6)
    {
        hit = s18a_800C7A68(work, 1);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 11)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
    }

    if (time == 15)
    {
        hit = s18a_800C7A68(work, 0);
        GM_SeSet(&control->mov, 56);
    }

    if (time == 19)
    {
        s18a_liquid_SetPose(work, 16);
    }

    if (time == 23)
    {
        hit = s18a_800C7A68(work, 2);
        GM_SeSet(&control->mov, 57);
    }

    if (time == 35)
    {
        work->pose = 0;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[0], 0, 10);
    }

    if (hit)
    {
        control->rot.vy = work->f9AC;
        control->turn.vy = work->f9AC;

        if (!s18a_liquid_After(time, 15))
        {
            GM_SeSet(&control->mov, 52);
        }
        else
        {
            GM_SeSet(&control->mov, 53);
        }
    }

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 14:
        speed = 4;
        if (frame < 4)
        {
            speed = 128;
        }
        break;

    case 15:
        speed = 4;
        if (frame < 8)
        {
            speed = 24;
        }
        break;

    case 16:
        speed = 4;
        if (frame <= 0)
        {
            speed = 128;
        }
        break;

    case 17:
        speed = 4;
        if (frame < 4)
        {
            speed = 48;
        }
        break;
    }

    speed /= 2;

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 36)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (work->pose != 10)
    {
        control->step.vx = speed * rsin(control->rot.vy) / 4096;
        control->step.vz = speed * rcos(control->rot.vy) / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800CA9FC(LiquidWork *work, int time)
{
    int      speed;
    int      hit;
    CONTROL *control;
    int      frame;
    int      dir;

    speed = 0;
    control = &work->control;
    hit = 0;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 12);
    }

    if (time == 14)
    {
        s18a_liquid_SetPose(work, 12);
    }

    if (time < 28)
    {
        control->rot.vy = control->turn.vy = work->f9AC;
        speed = 24;
    }

    if (time == 28)
    {
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 46)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 57)
    {
        s18a_liquid_SetPose(work, 16);
        control->turn.vy = work->f9AC;
    }

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 14:
        speed = 4;
        if (frame < 4)
        {
            speed = 128;
        }
        break;

    case 15:
        speed = 4;
        if (frame < 8)
        {
            speed = 24;
        }
        break;

    case 16:
        speed = 4;
        if (frame <= 0)
        {
            speed = 128;
        }
        break;

    case 17:
        speed = 4;
        if (frame < 4)
        {
            speed = 48;
        }
        break;
    }

    if (hit)
    {
        work->time = 70;
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 75)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 28)
    {
        control->step.vx += speed * rsin(work->f9AC) / 4096;
        control->step.vz += speed * rcos(work->f9AC) / 4096;

        dir = work->f9AC - 1024;
        dir &= 0xFFF;
        speed = 48;
        control->step.vx += rsin(dir) * speed / 4096;
        control->step.vz += rcos(dir) * speed / 4096;
    }
    else
    {
        control->step.vx = speed * rsin(work->f9AC) / 4096;
        control->step.vz = speed * rcos(work->f9AC) / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800CAD88(LiquidWork *work, int time)
{
    int      speed;
    int      hit;
    CONTROL *control;
    int      frame;
    int      dir;

    speed = 0;
    control = &work->control;
    hit = 0;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 13);
    }

    if (time == 14)
    {
        s18a_liquid_SetPose(work, 13);
    }

    if (time < 28)
    {
        control->rot.vy = control->turn.vy = work->f9AC;
        speed = 24;
    }

    if (time == 28)
    {
        work->pose = 15;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[15], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 46)
    {
        work->pose = 14;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[14], 0, 0);
        control->turn.vy = work->f9AC;
    }

    if (time == 57)
    {
        s18a_liquid_SetPose(work, 16);
        control->turn.vy = work->f9AC;
    }

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 14:
        speed = 4;
        if (frame < 4)
        {
            speed = 128;
        }
        break;

    case 15:
        speed = 4;
        if (frame < 8)
        {
            speed = 24;
        }
        break;

    case 16:
        speed = 4;
        if (frame <= 0)
        {
            speed = 128;
        }
        break;

    case 17:
        speed = 4;
        if (frame < 4)
        {
            speed = 48;
        }
        break;
    }

    if (hit)
    {
        work->time = 70;
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 75)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 28)
    {
        control->step.vx += speed * rsin(work->f9AC) / 4096;
        control->step.vz += speed * rcos(work->f9AC) / 4096;

        dir = work->f9AC + 1024;
        dir &= 0xFFF;
        speed = 48;
        control->step.vx += rsin(dir) * speed / 4096;
        control->step.vz += rcos(dir) * speed / 4096;
    }
    else
    {
        control->step.vx = speed * rsin(work->f9AC) / 4096;
        control->step.vz = speed * rcos(work->f9AC) / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800CB114(LiquidWork *work, int time)
{
    CONTROL *control;
    int      speed;
    int      dir;

    control = &work->control;

    if (time == 0)
    {
        if (GV_Time & 1)
        {
            s18a_liquid_SetPose(work, 12);
        }
        else
        {
            s18a_liquid_SetPose(work, 13);
        }
    }

    control->rot.vy = control->turn.vy = work->f9AC;

    s18a_800C8210(work);

    if (s18a_800C7684(work))
    {
        return;
    }

    if (time >= 15)
    {
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (work->m_ctrl.info1.frame < 8)
    {
        speed = 24;
        control->step.vx += rsin(work->f9AC) * speed / 4096;
        control->step.vz += rcos(work->f9AC) * speed / 4096;

        if (work->pose == 12)
        {
            dir = work->f9AC - 1024;
        }
        else
        {
            dir = work->f9AC + 1024;
        }

        dir &= 0xFFF;

        speed = 64;
        if (work->m_ctrl.info1.frame < 2)
        {
            speed = 128;
        }

        control->step.vx += speed * rsin(dir) / 4096;
        control->step.vz += speed * rcos(dir) / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800CB310(LiquidWork *work, int time)
{
    CONTROL *control;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 19);

        work->life -= work->damage1[0];
        if (work->life < 0)
        {
            work->life = 0;
        }

        GM_SeSet(&control->mov, 52);
        GM_SeSetMode(&control->mov, 135, 1);
        s18a_800CC488(work, 6);
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (s18a_800C7584(work))
    {
        return;
    }

    if (time >= 11)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        work->f948 = 30;
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800CB418(LiquidWork *work, int time)
{
    CONTROL *control;
    int      speed;

    if (s18a_800C7684(work))
    {
        return;
    }

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 20);

        work->life -= work->damage1[1];
        if (work->life < 0)
        {
            work->life = 0;
        }

        GM_SeSet(&control->mov, 53);
        GM_SeSetMode(&control->mov, 134, 1);
        s18a_800CC488(work, 6);
    }

    if (time >= 11)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        work->f948 = 30;
        return;
    }

    if (time < 3)
    {
        speed = -256;
        control->step.vx = rsin(work->f9AC) * speed / 4096;
        control->step.vz = rcos(work->f9AC) * speed / 4096;
    }

    work->target->class |= 0x17;
}

void s18a_800CB56C(LiquidWork *work, int time)
{
    CONTROL *control;

    control = &work->control;

    if (time == 0)
    {
        work->pose = 31;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[31], 0, 1);
        GM_SeSet(&control->mov, 57);
    }

    work->f90C = -1000;

    if (s18a_800C7684(work))
    {
        return;
    }

    if (work->cmd == 9)
    {
        return;
    }

    work->f940 = 1;

    if (s18a_800C736C(work))
    {
        s18a_liquid_ResetOverride(work);
    }
    else
    {
        s18a_liquid_SetAct(work, s18a_800C82A4);
    }
}

void s18a_800CB640(LiquidWork *work, int time)
{
    CONTROL *control;

    if (s18a_800C7684(work))
    {
        return;
    }

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 21);

        work->life -= work->damage1[1];
        if (work->life < 0)
        {
            work->life = 0;
        }

        GM_SeSet(&control->mov, 53);
        GM_SeSetMode(&control->mov, 134, 1);
        control->rot.vy = control->turn.vy = work->f9AC;
    }

    work->f944 = 1;
    work->target2->class = 1;

    if (time == 10)
    {
        GM_SeSet(&work->control.mov, 177);
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800CB780);
        return;
    }

    control->step.vx /= 2;
    control->step.vz /= 2;
}

void s18a_800CB780(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 22);

        if (work->life >= 31)
        {
            work->time = 30;
        }
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (work->life < 30)
    {
        if (GM_GameLevel < 4)
        {
            if (GM_GameLevel < 2)
            {
                goto easy;
            }

            if ((time & 7) == 0)
            {
                work->life++;
            }
        }
        else
        {
easy:
            if ((time & 1) == 0)
            {
                work->life++;
            }
        }
    }

    work->f944 = 1;

    if ((255 - work->life) / 25 < time)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800CB8AC);
    }
}

void s18a_800CB8AC(LiquidWork *work, int time)
{
    int      hit;
    CONTROL *control;

    if (s18a_800C7684(work))
    {
        return;
    }

    hit = 0;
    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 23);
    }

    if (time == 12)
    {
        GM_SeSet(&control->mov, 182);
    }

    if (time == 32)
    {
        hit = s18a_800C7A68(work, 4);
    }

    if (hit)
    {
        GM_SeSet(&control->mov, 53);
    }

    if (time == 41)
    {
        GM_SeSetMode(&control->mov, 161, 0);
    }

    if (time == 43)
    {
        GM_SeSetMode(&control->mov, 160, 0);
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 32)
    {
        work->f944 = 1;
    }
}

void s18a_800CB9D0(LiquidWork *work, int time)
{
    CONTROL *control;
    int      dir;

    control = &work->control;

    if (time == 0)
    {
        s18a_liquid_SetPose(work, 24);
        GM_SeSetMode(&control->mov, 134, 1);

        work->life -= work->damage1[2];
        if (work->life < 0)
        {
            work->life = 0;
        }
    }

    if (s18a_800C7684(work))
    {
        return;
    }

    if (time == 21)
    {
        GM_SeSet(&work->control.mov, 177);
        GM_SeSetMode(&work->control.mov, 135, 1);
    }

    if (time == 59)
    {
        dir = control->rot.vy + 2048;
        control->turn.vy = control->rot.vy = dir & 0xFFF;
        work->pose = 3;
        GM_ConfigObjectAction(&work->body, s18a_liquid_motions[3], 0, 0);
    }

    if (time >= 61)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    if (time < 24)
    {
        control->turn = *work->target->field_1C;
    }

    work->f944 = 1;
    work->target2->class = 1;
}

void s18a_800CBB50(LiquidWork *work, int time)
{
    SVECTOR  near;
    SVECTOR  unused;
    CONTROL *control;
    int      seg;
    int      base;

    control = &work->control;

    if (time == 0)
    {
        work->control.mov = work->last_pos;
        printf("pos0 %d %d %d \n", work->control.mov.vx, control->mov.vy, control->mov.vz);

        work->f914 = s18a_800C722C(&control->mov, &work->control.turn.vy);
        printf(" climb type = %d \n", work->f914);

        switch (work->f914)
        {
        case 2:
        case 5:
        case 6:
        case 7:
            s18a_liquid_SetPose(work, 26);
            break;

        case 0:
        case 1:
        case 3:
            s18a_liquid_SetPose(work, 33);
            break;

        case 4:
            s18a_liquid_SetPose(work, 36);
            break;
        }

        work->f9A4 = 1;
        work->f910 = control->levels[0];

        seg = (work->f914 & 1) ? 0x20 : 0x10;
        if (!HZD_NearHazardCheck(control->map->hzd, &work->control.mov, 5000, 4, seg))
        {
            printf(" Err Err Err Liquid Near Err !! \n");
        }
        else
        {
            HZD_GetNearVector(&near);
        }

        control->mov.vx += near.vx;
        control->mov.vy += near.vy;
        control->mov.vz += near.vz;
        control->step.vx = 0;
        control->step.vz = 0;
        GM_SeSet(&control->mov, 178);
        return;
    }

    base = 30;

    if (time == 26)
    {
        switch (work->f914)
        {
        case 2:
        case 5:
        case 6:
        case 7:
            s18a_liquid_SetPose(work, 27);
            break;

        case 0:
        case 1:
        case 3:
            s18a_liquid_SetPose(work, 34);
            break;

        case 4:
            s18a_liquid_SetPose(work, 37);
            break;
        }
    }
    else if (time == 58)
    {
        switch (work->f914)
        {
        case 2:
        case 5:
        case 6:
        case 7:
            s18a_liquid_SetPose(work, 28);
            break;

        case 0:
        case 1:
        case 3:
            s18a_liquid_SetPose(work, 35);
            break;

        case 4:
            s18a_liquid_SetPose(work, 38);
            break;
        }

        GM_SeSet(&control->mov, 179);
    }

    if (time > base + 30)
    {
        if (work->body.is_end)
        {
            work->control.height = work->body.height = 1100;
            work->pose = 0;
            GM_ConfigObjectAction(&work->body, s18a_liquid_motions[0], 0, 0);
            work->f940 = 1;
            work->f948 = 30;
            work->f9A4 = 0;
            s18a_liquid_SetAct(work, s18a_800C82A4);
            return;
        }
    }

    if (time >= 27 && time < base + 28)
    {
        control->step.vx = 0;
        control->step.vz = 0;
    }

    if (work->f914 == 2 || work->f914 == 6)
    {
        if (time > base + 30 && time < base + 50)
        {
            work->f910 += 16;
        }
    }
}

void s18a_800CBF38(LiquidWork *work, int time)
{
    SVECTOR  diff1;
    SVECTOR  diff2;
    SVECTOR  pos;
    SVECTOR  rot;
    MATRIX   mat;
    CONTROL *control;
    HZD_SEG *seg;
    int      dir;
    int      dir1;
    int      dir2;
    int      diff;

    control = &work->control;

    if (time != 0)
    {
        return;
    }

    s18a_liquid_SetPose(work, 39);
    work->f9A4 = 2;
    work->f910 = control->levels[0];

    if (HZD_OnlineHazardCheck(control->map->hzd, &s18a_dword_800C3368, &control->mov, 4, 4))
    {
        diff1.vx = s18a_dword_800C3368.vx - work->control.mov.vx;
        diff1.vy = 0;
        diff1.vz = s18a_dword_800C3368.vz - control->mov.vz;
        dir = GV_VecDir2(&diff1);

        seg = HZD_GetOnlineHazard();
        diff2.vx = seg->p2.x - seg->p1.x;
        diff2.vy = 0;
        diff2.vz = seg->p2.z - seg->p1.z;
        dir1 = GV_VecDir2(&diff2) + 1024;
        dir1 &= 0xFFF;

        diff = GV_DiffDirAbs(dir1, dir);
        dir2 = dir1 + 2024;
        dir2 &= 0xFFF;

        if (diff < GV_DiffDirAbs(dir2, dir))
        {
            control->turn.vy = dir1;
        }
        else
        {
            control->turn.vy = dir2;
        }

        HZD_GetOnlinePoint(&pos);
        rot.vx = 0;
        rot.vy = control->turn.vy;
        rot.vz = 0;
        DG_SetPos2(&pos, &rot);
        DG_MovePos(&s18a_dword_800C3370);
        ReadRotMatrix(&mat);
        control->mov.vx = mat.t[0];
        control->mov.vy = mat.t[1];
        control->mov.vz = mat.t[2];
    }
    else
    {
        printf(" Err Err Err Liquid Err !! \n");
    }

    s18a_dword_800E3EF0 = control->mov.vy;
}

void s18a_800CC0F0(LiquidWork *work, int time)
{
    if (time == 0)
    {
        s18a_liquid_SetPose(work, 25);
        work->control.turn = GM_PlayerControl->rot;
        s18a_800C80B8(work, 1);
        GM_SeSetMode(&work->control.mov, 135, 1);
    }

    if (s18a_800C7A18(work))
    {
        return;
    }

    if (time == 35)
    {
        GM_SeSet(&work->control.mov, 187);
    }

    if (work->body.is_end)
    {
        work->f940 = 1;
        s18a_liquid_SetAct(work, s18a_800C82A4);
        return;
    }

    work->target->class |= 0x17;
}

void s18a_800CC1F0(LiquidWork *work)
{
    if (work->f948 > 0)
    {
        if (work->f948 & 2)
        {
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
        }
        else
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        }

        work->target->class = 1;
        work->target->captured = 0;
        work->f948--;
        work->target2->class = 1;
    }
    else
    {
        work->f948 = 0;
    }
}

void s18a_800CC278(LiquidWork *work)
{
    sna_act_helper2_helper2_80033054(work->control.name, &work->adjust[5]);
}

void s18a_800CC2A0(LiquidWork *work)
{
    void   (*act)(LiquidWork *, int);
    int      time;
    CONTROL *control;
    OBJECT  *body;

    work->target->class = 1;

    if (!(GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND)))
    {
        work->target2->class = 9;
    }
    else
    {
        work->target2->class = 1;
    }

    control = &work->control;
    act = work->act;
    time = work->time;
    body = &work->body;

    work->f940 = 0;
    work->f944 = 0;
    work->f9A8 = 0;
    work->time = time + 1;

    if (!act)
    {
        act = s18a_800C82A4;
        work->act = act;
    }

    act(work, time);

    act = work->act2;
    if (act)
    {
        time = work->time2;
        work->time2 = time + 1;
        act(work, time);
    }

    work->target->damaged = 0;
    s18a_800CC1F0(work);
    s18a_800CC278(work);

    control->height = body->height;

    if (work->f9A4 == 1)
    {
        control->r_sphere = -2;
        control->mov.vy = work->f910 + body->height;
    }
    else if (work->f9A4 == 2)
    {
        control->r_sphere = -2;
        work->f90C -= 4;
        control->mov.vy += control->step.vy = work->f90C;
    }
    else if (work->f9A4 == 3)
    {
        control->r_sphere = -2;
        work->f90C -= 1;
        control->mov.vy += control->step.vy = work->f90C;
    }
    else if (work->f944)
    {
        control->r_sphere = -1;
    }
    else
    {
        control->r_sphere = GV_NearExp2(control->r_sphere, 450);
    }

    if (work->f9A4 == 0)
    {
        if (work->f90C < 0 && control->grounded)
        {
            work->f90C = 0;
        }

        work->f90C -= 16;
        control->step.vy = work->f90C;
    }
}

void s18a_800CC488(LiquidWork *work, int joint)
{
    MATRIX mat;

    DG_SetPos(&work->body.objs->objs[joint].world);
    DG_MovePos(&s18a_dword_800C3378);
    DG_RotatePos(&s18a_dword_800C3380);
    ReadRotMatrix(&mat);
    NewBlood(&mat, 0);
}

void s18a_800CC4F0(LiquidWork *work)
{
    MATRIX  mat;
    MATRIX *world;

    world = &work->body.objs->objs[4].world;
    DG_SetPos(world);
    DG_MovePos(&s18a_dword_800C3394);
    ReadRotMatrix(&mat);
    GM_SeSet(&work->control.mov, 73);
    AN_SocomFlash(world, &mat, 0);
    s18a_800CC6A8(work, s18a_800CC4F0);
}

void s18a_800CC56C(LiquidWork *work)
{
}

void s18a_800CC574(LiquidWork *work)
{
    int frame;

    frame = work->m_ctrl.info1.frame;

    switch (work->pose)
    {
    case 8:
        if (frame == 16)
        {
            GM_SeSetMode(&work->control.mov, 161, 0);
        }
        else if (frame == 8)
        {
            GM_SeSetMode(&work->control.mov, 160, 0);
        }
        break;

    case 10:
        if (frame == 4)
        {
            GM_SeSetMode(&work->control.mov, 161, 0);
        }
        break;

    case 11:
        if (frame == 8 || frame == 13)
        {
            GM_SeSetMode(&work->control.mov, 161, 0);
        }
        else if (frame == 15)
        {
            GM_SeSetMode(&work->control.mov, 160, 0);
        }
        break;

    case 13:
        if (frame == 6 || frame == 14)
        {
            GM_SeSetMode(&work->control.mov, 161, 0);
        }
        else if (frame == 15)
        {
            GM_SeSetMode(&work->control.mov, 160, 0);
        }
        break;

    case 12:
        if (frame == 6 || frame == 14)
        {
            GM_SeSetMode(&work->control.mov, 161, 0);
        }
        else if (frame == 15)
        {
            GM_SeSetMode(&work->control.mov, 160, 0);
        }
        break;
    }
}

int s18a_800CC660(LiquidWork *work, int index)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->funcs[i] == NULL)
        {
            work->funcs[i] = s18a_dword_800C3388[index];
            return 1;
        }
    }

    return 0;
}

int s18a_800CC6A8(LiquidWork *work, void *func)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->funcs[i] == func)
        {
            work->funcs[i] = NULL;
            return 1;
        }
    }

    return 0;
}

void s18a_800CC6DC(LiquidWork *work)
{
    int i;
    void (*func)(LiquidWork *);

    for (i = 0; i < 8; i++)
    {
        func = work->funcs[i];
        if (func != NULL)
        {
            func(work);
        }
    }
}

void s18a_800CC73C(LiquidWork *work)
{
    TARGET *target;
    int     flag;

    target = work->target;
    flag = target->damaged;
    work->f9B8 = 0;

    if (flag & (TARGET_POWER | TARGET_CAPTURE))
    {
        work->f9B8 = target->a_mode;
    }
}

void s18a_800CC76C(LiquidWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;
    work->f9AC = GV_VecDir2(&diff);
    work->f9B0 = GV_VecLen3(&diff);
}

void s18a_800CC7BC(LiquidWork *work)
{
    s18a_800CC76C(work);
    s18a_800CC73C(work);
    s18a_800D0D28(work);
    s18a_800CC2A0(work);
    s18a_800CC6DC(work);
}

void s18a_800CC800(LiquidWork *work)
{
    work->f970 = GM_PlayerPosition;
}

const int s18a_dword_800E3044 = 0x253A782C;
const int s18a_dword_800E3048 = 0x3A792064;
const int s18a_dword_800E304C = 0x7A206425;
const int s18a_dword_800E3050 = 0x2064253A;
const int s18a_dword_800E3054 = 0x0000000A;
const int s18a_dword_800E3058 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CC830.s")
void s18a_800CC8B0(LiquidWork *work, int index, int which)
{
    work->f970 = s18a_dword_800C341C[index][which];
}

int s18a_800CC8F0(LiquidWork *work, int range)
{
    SVECTOR diff;
    int     dx;
    int     dz;

    dx = work->f970.vx - work->control.mov.vx;
    diff.vx = dx;
    dz = work->f970.vz - work->control.mov.vz;
    diff.vz = dz;

    if (dx > -range && dx < range && dz > -range && dz < range)
    {
        return 1;
    }

    work->f954 = GV_VecDir2(&diff);
    return 0;
}

int s18a_800CC96C(SVECTOR *pos)
{
    int area;

    if (pos->vx >= 376 && pos->vx < 4375 && pos->vz > 1000 && pos->vz < -1000)
    {
        return -1;
    }

    if (pos->vx >= 2251)
    {
        area = pos->vz < 1;
    }
    else
    {
        area = 3;
        if (pos->vz > 0)
        {
            area = 2;
        }
    }

    return area;
}

int s18a_800CC9E4(SVECTOR *pos)
{
    int area;

    area = 4;
    if (pos->vz < 2251)
    {
        if (pos->vx >= 2251)
        {
            area = pos->vz < 1;
        }
        else
        {
            area = 3;
            if (pos->vz > 0)
            {
                area = 2;
            }
        }
    }

    return area;
}

int s18a_800CCA20(int area, int dir)
{
    int ret;

    ret = 0;

    switch (area)
    {
    case 0:
        if (dir > 512 && dir < 2560) ret = 1; else ret = 0;
        break;

    case 1:
        if (dir > 1536 && dir < 3584) ret = 1; else ret = 0;
        break;

    case 2:
        if (dir > 1536 && dir < 3584) ret = 0; else ret = 1;
        break;

    case 3:
        if (dir > 512 && dir < 2560) ret = 0; else ret = 1;
        break;

    case 4:
        if (dir < 2048) ret = 1; else ret = 0;
        break;
    }

    return ret;
}

int s18a_800CCA88(int area, int dir)
{
    int ret;

    ret = 2;

    switch (area)
    {
    case 0:
        ret = 1;
        if (dir > 512 && dir < 2560)
        {
            ret = 2;
        }
        break;

    case 1:
        ret = 2;
        break;

    case 3:
        ret = 0;
        break;

    case 2:
    case 4:
        ret = 1;
        break;
    }

    return ret;
}

const int s18a_dword_800E3088 = 0; /* padding */

int s18a_800CCAE0(int area, int dir)
{
    int ret;

    ret = 3;

    switch (area)
    {
    case 0:
        ret = 3;
        break;

    case 1:
        ret = 3;
        if (dir > 1536 && dir < 3584)
        {
            ret = 0;
        }
        break;

    case 3:
        ret = 0;
        break;

    case 2:
    case 4:
        ret = 1;
        break;
    }

    return ret;
}

const int s18a_dword_800E30A0 = 0x00000000;

int s18a_800CCB38(int area, int dir)
{
    int ret;

    ret = 3;

    switch (area)
    {
    case 1:
        ret = 2;
        break;

    case 2:
        ret = 3;
        if (dir > 1536 && dir < 3584)
        {
            ret = 0;
        }
        break;

    case 3:
        ret = 0;
        break;

    case 0:
    case 4:
        ret = 3;
        break;
    }

    return ret;
}

const int s18a_dword_800E30B8 = 0x00000000;

int s18a_800CCB90(int area, int dir)
{
    int ret;

    ret = 3;

    switch (area)
    {
    case 1:
        ret = 2;
        break;

    case 2:
        ret = 1;
        break;

    case 3:
        ret = 1;
        if (dir > 512 && dir < 2560)
        {
            ret = 2;
        }
        break;

    case 0:
    case 4:
        ret = 3;
        break;
    }

    return ret;
}

const int s18a_dword_800E30D0 = 0x00000000;

int s18a_800CCBE8(int area, int dir)
{
    int ret;

    ret = 3;
    if (GV_Time & 1)
    {
        ret = 1;
    }

    return ret;
}

int s18a_800CCC0C(LiquidWork *work)
{
    int area;
    int player;
    int ret;

    area = s18a_800CC9E4(&work->control.mov);
    ret = player = s18a_800CC9E4(&GM_PlayerPosition);

    switch (area)
    {
    case 0:
        ret = s18a_800CCA88(player, work->f9AC);
        break;

    case 1:
        ret = s18a_800CCAE0(player, work->f9AC);
        break;

    case 2:
        ret = s18a_800CCB38(player, work->f9AC);
        break;

    case 3:
        ret = s18a_800CCB90(player, work->f9AC);
        break;

    case 4:
        ret = s18a_800CCBE8(player, work->f9AC);
        break;
    }

    return ret;
}

SVECTOR *s18a_800CCCE0(int idx, SVECTOR *pos)
{
    SVECTOR *a;
    SVECTOR *b;
    int      dist;

    a = s18a_dword_800C339C[idx];
    dist = GV_DiffVec3(a, pos);
    b = s18a_dword_800C33DC[idx];

    if (dist < GV_DiffVec3(b, pos))
    {
        return a;
    }

    return b;
}

int s18a_800CCD5C(SVECTOR *pos)
{
    if (pos->vx < -500)
    {
        return 1;
    }

    if (s18a_liquid_After(pos->vx, 5000))
    {
        return 1;
    }

    if (pos->vz < -750)
    {
        return 1;
    }

    return s18a_liquid_After(pos->vz, 1250);
}

void s18a_800CCDA8(void)
{
    s18a_dword_800C345C = 0;
    s18a_dword_800C3460 = 0;
    s18a_dword_800C3464 = 0;
    s18a_dword_800C3480 = 0;
    s18a_dword_800C3484 = 0;
    s18a_dword_800C3488 = 0;
    s18a_dword_800C348C = 0;
    s18a_dword_800C3490 = 0;
}

void s18a_800CCDEC(int vox)
{
    if (GM_StreamStatus() == -1)
    {
        GM_VoxStream(vox, 0);
    }
}

void s18a_800CCE24(LiquidWork *work, int type)
{
    switch (type)
    {
    case 0:
        printf(" vox chouhatu =%d \n", s18a_dword_800C345C);
        if (work->dead_timer == 0)
        {
            s18a_800CCDEC(work->voices[s18a_dword_800C3468[s18a_dword_800C345C]]);
        }
        if (++s18a_dword_800C345C >= 4)
        {
            s18a_dword_800C345C = 0;
        }
        break;

    case 1:
        printf(" vox saisku  =%d \n", s18a_dword_800C3460);
        if (work->dead_timer == 0)
        {
            s18a_800CCDEC(work->voices[s18a_dword_800C3478[s18a_dword_800C3460]]);
        }
        if (++s18a_dword_800C3460 >= 2)
        {
            s18a_dword_800C3460 = 0;
        }
        break;

    case 2:
        break;
    }
}

void s18a_800CCF48(LiquidWork *work)
{
    int r;

    if (s18a_dword_800C3480 == 0)
    {
        s18a_dword_800C3484 = 0;
        s18a_dword_800C3488 = 0;
        s18a_dword_800C348C = 0;
        s18a_dword_800C3490 = 0;
    }

    if (s18a_dword_800C3484 == 0 && s18a_dword_800C3480 > 30)
    {
        if (GM_StreamStatus() == -1)
        {
            if (work->dead_timer == 0)
            {
                GM_VoxStream(work->voices[13], 0);
            }
            s18a_dword_800C3484++;
        }
    }

    switch (s18a_dword_800C3488)
    {
    case 0:
        if (GM_PlayerStatus & PLAYER_ACT_ONLY)
        {
            s18a_dword_800C3488 = 1;
        }
        break;

    case 1:
        if (GM_StreamStatus() == -1)
        {
            switch (work->control.mov.vy % 2)
            {
            case 0:
                if (work->dead_timer == 0)
                {
                    GM_VoxStream(work->voices[1], 0);
                }
                break;
            }

            s18a_dword_800C3488 = 2;
        }
        else
        {
            s18a_dword_800C3488 = 2;
        }
        break;

    case 2:
        if (!(GM_PlayerStatus & PLAYER_ACT_ONLY))
        {
            s18a_dword_800C3488 = 0;
        }
        break;
    }

    switch (s18a_dword_800C348C)
    {
    case 0:
        if (GM_PlayerStatus & (PLAYER_DAMAGED | PLAYER_DOWNED))
        {
            s18a_dword_800C348C = 1;
        }
        break;

    case 1:
        if (GM_StreamStatus() == -1)
        {
            r = work->control.mov.vy % 4;
            if (work->dead_timer == 0)
            {
                switch (r)
                {
                case 0:
                    GM_VoxStream(work->voices[6], 0);
                    break;

                case 1:
                    GM_VoxStream(work->voices[2], 0);
                    break;
                }
            }

            s18a_dword_800C348C = 2;
        }
        else
        {
            s18a_dword_800C348C = 2;
        }
        break;

    case 2:
        if (!(GM_PlayerStatus & (PLAYER_DAMAGED | PLAYER_DOWNED)))
        {
            s18a_dword_800C348C = 0;
        }
        break;
    }

    if (GM_StreamStatus() == -1)
    {
        r = s18a_dword_800C3490 % 12;
        if (work->dead_timer == 0)
        {
            switch (r)
            {
            case 1:
                GM_VoxStream(work->voices[5], 0);
                s18a_dword_800C3490++;
                break;

            case 4:
                GM_VoxStream(work->voices[15], 0);
                s18a_dword_800C3490++;
                break;

            case 7:
                GM_VoxStream(work->voices[14], 0);
                s18a_dword_800C3490++;
                break;

            case 10:
                GM_VoxStream(work->voices[2], 0);
                s18a_dword_800C3490++;
                break;
            }
        }
    }

    s18a_dword_800C3480++;
}

void s18a_800CD2D8(LiquidWork *work)
{
    int r;

    if (s18a_dword_800C3480 == 0)
    {
        s18a_dword_800C3484 = 0;
        s18a_dword_800C3488 = 0;
        s18a_dword_800C348C = 0;
        s18a_dword_800C3490 = 0;
    }

    if (s18a_dword_800C3484 == 0 && s18a_dword_800C3480 > 30)
    {
        if (GM_StreamStatus() == -1)
        {
            if (work->dead_timer == 0)
            {
                GM_VoxStream(work->voices[13], 0);
            }
            s18a_dword_800C3484++;
        }
    }

    switch (s18a_dword_800C3488)
    {
    case 0:
        if (GM_PlayerStatus & (PLAYER_DOWNED | PLAYER_ACT_ONLY))
        {
            s18a_dword_800C3488 = 1;
        }
        break;

    case 1:
        if (GM_StreamStatus() == -1)
        {
            r = work->control.mov.vy % 2;
            if (work->dead_timer == 0)
            {
                switch (r)
                {
                case 0:
                    GM_VoxStream(work->voices[4], 0);
                    break;

                case 1:
                    GM_VoxStream(work->voices[7], 0);
                    break;
                }
            }

            s18a_dword_800C3488 = 2;
        }
        else
        {
            s18a_dword_800C3488 = 2;
        }
        break;

    case 2:
        if (!(GM_PlayerStatus & (PLAYER_DOWNED | PLAYER_ACT_ONLY)))
        {
            s18a_dword_800C3488 = 0;
        }
        break;
    }

    s18a_dword_800C3480++;
}

int s18a_800CD4AC(LiquidWork *work)
{
    int mode;

    mode = work->f9B8;
    if (mode == 3 || mode == 4 || mode == 36)
    {
        if (mode == 4)
        {
            work->f99C = 0;
        }
        else
        {
            work->f99C = 1;
        }

        work->f960 = 4;
        work->f964 = 29;
        return 1;
    }

    return 0;
}

int s18a_800CD504(LiquidWork *work)
{
    int mode;

    mode = work->f9B8;
    if (mode == 3 || mode == 4 || mode == 36)
    {
        work->f960 = 4;
        work->f964 = 29;
        return 1;
    }

    return 0;
}

int s18a_800CD544(LiquidWork *work)
{
    int mode;

    mode = work->f9B8;
    if (mode == 3 || mode == 4 || mode == 36)
    {
        if (mode == 4)
        {
            work->f99C = 0;
        }
        else
        {
            work->f99C = 1;
        }

        work->f960 = 4;
        work->f964 = 29;
        return 1;
    }

    return 0;
}

void s18a_800CD59C(LiquidWork *work)
{
    s18a_800CCDA8();

    if (work->f9BE)
    {
        NewCountdown(5400, -1);
        GM_AlertModeSet(4);
        s18a_liquid_800C5200(4);
        work->f964 = 18;

        if (work->proc_s >= 0)
        {
            GCL_ExecProc(work->proc_s, NULL);
        }

        DG_InvisibleObjs(work->weapon.objs);
    }
    else
    {
        work->f964 = 1;
    }

    work->f97C = 0;
    work->f968 = 0;
}

void s18a_800CD62C(LiquidWork *work)
{
    work->cmd = 6;
    GM_GameStatus |= STATE_PADRELEASE;
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        OpenCinemaScreen(1, 60000);
        GM_VoxStream(work->voices[16], 0x40000000);
        NewCountdown(5400, -1);
    }

    SetCountdownTime(5400);

    if (work->f968 > 30)
    {
        work->f964 = 2;
        work->f97C = 0;
        work->f968 = 0;
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CD6D0(LiquidWork *work)
{
    if (work->f968 == 0)
    {
        work->cmd = 1;
    }

    if (work->f968 < 54)
    {
        SetCountdownTime(5400);
    }

    if (work->f968 > 70)
    {
        work->cmd = 6;
        s18a_liquid_SetPhase(work, 3);
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CD758(LiquidWork *work)
{
    work->cmd = 6;
    work->f954 = work->f9AC;

    if (work->f968 > 0 && GM_StreamStatus() == 1)
    {
        GM_StreamPlayStart();
    }

    if (work->f968 > 100 && GM_StreamStatus() == -1)
    {
        s18a_liquid_SetPhase(work, 4);
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CD7F4(LiquidWork *work)
{
    work->cmd = 6;
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->voices[17], 0x40000000);
        }

        s18a_liquid_800C5200(1);
    }

    if (work->f968 == 60)
    {
        GM_StreamPlayStart();
    }

    if (work->f968 > 200 && GM_StreamStatus() == -1)
    {
        s18a_liquid_SetPhase(work, 5);
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CD8B4(LiquidWork *work)
{
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->voices[18], 0x40000000);
        }

        s18a_liquid_800C5200(2);
    }

    if (work->f968 == 30)
    {
        GM_StreamPlayStart();
    }

    if (work->f968 < 30)
    {
        work->cmd = 6;
    }
    else
    {
        work->cmd = 2;
    }

    if (work->f968 > 300 && GM_StreamStatus() == -1)
    {
        s18a_liquid_SetPhase(work, 6);
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CD98C(LiquidWork *work)
{
    work->cmd = 6;
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        s18a_liquid_800C5200(3);
        GM_VoxStream(work->voices[0], 0x40000000);
    }

    if (work->f968 > 160 && GM_StreamStatus() == 1)
    {
        DG_InvisibleObjs(work->weapon.objs);
        work->f960 = 1;
        s18a_liquid_SetPhase(work, 1);
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CDA40(LiquidWork *work)
{
    work->cmd = 3;
    GM_GameStatus |= STATE_PADRELEASE;
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        GM_VoxStream(work->voices[0], 0x40000000);
    }

    if (work->f968 > 60 && GM_StreamStatus() == 1)
    {
        GM_StreamPlayStart();
        work->f960 = 1;
        s18a_liquid_SetPhase(work, 2);
    }

    work->f968++;
}

void s18a_800CDAF8(LiquidWork *work)
{
    work->cmd = 3;
    work->f954 = work->f9AC;

    if (work->f968 == 0)
    {
        GM_StreamPlayStart();

        if (work->proc_s >= 0)
        {
            GCL_ExecProc(work->proc_s, NULL);
        }
    }

    if (work->f968 == 30)
    {
        GM_AlertModeSet(4);
    }

    if (work->f968 > 30 && GM_StreamStatus() == -1)
    {
        CloseCinemaScreen();
        s18a_liquid_SetPhase(work, 2);
    }

    work->f968++;
}

void s18a_800CDBB8(LiquidWork *work)
{
    GM_GameStatus |= STATE_PADRELEASE;

    if (work->f968 > 15)
    {
        GM_GameStatus &= ~STATE_PADRELEASE;
        s18a_liquid_800C5200(6);
        work->f95C = 3;
        work->f960 = 1;
        s18a_liquid_SetPhase(work, 3);
        work->f978 = 5400;
    }
    else
    {
        work->f968++;
    }
}

void s18a_800CDC40(LiquidWork *work)
{
    int dist;

    work->cmd = 5;
    work->f954 = work->f9AC;
    dist = work->f9B0;

    if (dist > 8000)
    {
        work->f960 = 3;
        s18a_liquid_SetPhase(work, 13);
    }
    else if (dist > 3000)
    {
        work->f960 = 2;
        s18a_liquid_SetPhase(work, 8);
    }
    else if (dist < 1500)
    {
        work->f960 = 2;
        s18a_liquid_SetPhase(work, 9);
    }
    else if (work->f968 > 5)
    {
        work->f960 = 2;
        s18a_liquid_SetPhase(work, 10);
    }
    else
    {
        work->f968++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDCD4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDD28.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDD68.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDDE0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDEFC.s")
const int s18a_dword_800E3110 = 0x635F6120;
const int s18a_dword_800E3114 = 0x746E756F;
const int s18a_dword_800E3118 = 0x25203D20;
const int s18a_dword_800E311C = 0x000A2064;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CDFCC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE0F8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE170.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE314.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE3F8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE4CC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE530.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE584.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE634.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE674.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE6B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE710.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE770.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE858.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE93C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CE97C.s")
const int s18a_dword_800E3120 = 0x65726120;
const int s18a_dword_800E3124 = 0x203D2061;
const int s18a_dword_800E3128 = 0x000A6425;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEA0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEB78.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEBC4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CED40.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CED80.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEDCC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEE0C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEE58.s")
const char s18a_dword_800E312C[] = "go tekken 1";
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEEBC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEF30.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEF70.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CEFE4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF090.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF0EC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF138.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF184.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF1CC.s")
const int s18a_dword_800E3138 = 0x73616870;
const int s18a_dword_800E313C = 0x6C203265;
const int s18a_dword_800E3140 = 0x20656669;
const int s18a_dword_800E3144 = 0x6425203D;
const int s18a_dword_800E3148 = 0x00000A20;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF214.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF338.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF3B0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF470.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF4BC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF508.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF554.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF5DC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF628.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF684.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF6E0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF72C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF778.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF7E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF838.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF884.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF8F0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF94C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF998.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CF9E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFA50.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFA90.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFAEC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFB48.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFB94.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFBE0.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFC24.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFC70.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFCB4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFD54.s")
const int s18a_dword_800E314C = 0x800CFE14;
const int s18a_dword_800E3150 = 0x800CFE24;
const int s18a_dword_800E3154 = 0x800CFE34;
const int s18a_dword_800E3158 = 0x800CFE44;
const int s18a_dword_800E315C = 0x800CFE54;
const int s18a_dword_800E3160 = 0x800CFE64;
const int s18a_dword_800E3164 = 0x800CFE74;
const int s18a_dword_800E3168 = 0x800CFE8C;
const int s18a_dword_800E316C = 0x800CFE8C;
const int s18a_dword_800E3170 = 0x800CFE8C;
const int s18a_dword_800E3174 = 0x800CFE8C;
const int s18a_dword_800E3178 = 0x800CFE8C;
const int s18a_dword_800E317C = 0x800CFE8C;
const int s18a_dword_800E3180 = 0x800CFE8C;
const int s18a_dword_800E3184 = 0x800CFE8C;
const int s18a_dword_800E3188 = 0x800CFE8C;
const int s18a_dword_800E318C = 0x800CFE8C;
const int s18a_dword_800E3190 = 0x800CFE8C;
const int s18a_dword_800E3194 = 0x800CFE84;
const int s18a_dword_800E3198 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFDDC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFE9C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFF18.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFF48.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800CFFB8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0028.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D00C4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0114.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0164.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D01B4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D01E4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0254.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D02DC.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D034C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D03C0.s")
const int s18a_dword_800E319C = 0x800D04A8;
const int s18a_dword_800E31A0 = 0x800D04B8;
const int s18a_dword_800E31A4 = 0x800D0488;
const int s18a_dword_800E31A8 = 0x800D0498;
const int s18a_dword_800E31AC = 0x800D0478;
const int s18a_dword_800E31B0 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0434.s")
const int s18a_dword_800E31B4 = 0x800D054C;
const int s18a_dword_800E31B8 = 0x800D053C;
const int s18a_dword_800E31BC = 0x800D055C;
const int s18a_dword_800E31C0 = 0x800D056C;
const int s18a_dword_800E31C4 = 0x800D0574;
const int s18a_dword_800E31C8 = 0x800D0574;
const int s18a_dword_800E31CC = 0x800D0574;
const int s18a_dword_800E31D0 = 0x800D0574;
const int s18a_dword_800E31D4 = 0x800D0574;
const int s18a_dword_800E31D8 = 0x800D0574;
const int s18a_dword_800E31DC = 0x800D0574;
const int s18a_dword_800E31E0 = 0x800D0574;
const int s18a_dword_800E31E4 = 0x800D0574;
const int s18a_dword_800E31E8 = 0x800D0574;
const int s18a_dword_800E31EC = 0x800D0574;
const int s18a_dword_800E31F0 = 0x800D0574;
const int s18a_dword_800E31F4 = 0x800D0574;
const int s18a_dword_800E31F8 = 0x800D0574;
const int s18a_dword_800E31FC = 0x800D0574;
const int s18a_dword_800E3200 = 0x800D0574;
const int s18a_dword_800E3204 = 0x800D0574;
const int s18a_dword_800E3208 = 0x800D0574;
const int s18a_dword_800E320C = 0x800D0574;
const int s18a_dword_800E3210 = 0x800D0574;
const int s18a_dword_800E3214 = 0x800D0574;
const int s18a_dword_800E3218 = 0x800D052C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D04E8.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D059C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D060C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D063C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D066C.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D069C.s")
const int s18a_dword_800E321C = 0x800D0740;
const int s18a_dword_800E3220 = 0x800D07C8;
const int s18a_dword_800E3224 = 0x800D0730;
const int s18a_dword_800E3228 = 0x800D07C8;
const int s18a_dword_800E322C = 0x800D07C0;
const int s18a_dword_800E3230 = 0x800D0750;
const int s18a_dword_800E3234 = 0x800D07C8;
const int s18a_dword_800E3238 = 0x800D0760;
const int s18a_dword_800E323C = 0x800D0770;
const int s18a_dword_800E3240 = 0x800D0780;
const int s18a_dword_800E3244 = 0x800D0790;
const int s18a_dword_800E3248 = 0x800D07B0;
const int s18a_dword_800E324C = 0x800D07A0;
const int s18a_dword_800E3250 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D06EC.s")
const int s18a_dword_800E3254 = 0x800D0844;
const int s18a_dword_800E3258 = 0x800D08CC;
const int s18a_dword_800E325C = 0x800D0834;
const int s18a_dword_800E3260 = 0x800D08CC;
const int s18a_dword_800E3264 = 0x800D08B4;
const int s18a_dword_800E3268 = 0x800D08CC;
const int s18a_dword_800E326C = 0x800D08CC;
const int s18a_dword_800E3270 = 0x800D0874;
const int s18a_dword_800E3274 = 0x800D0884;
const int s18a_dword_800E3278 = 0x800D0854;
const int s18a_dword_800E327C = 0x800D0864;
const int s18a_dword_800E3280 = 0x800D08A4;
const int s18a_dword_800E3284 = 0x800D0894;
const int s18a_dword_800E3288 = 0x800D08C4;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D07F0.s")
const int s18a_dword_800E328C = 0x800D0938;
const int s18a_dword_800E3290 = 0x800D09D0;
const int s18a_dword_800E3294 = 0x800D09C8;
const int s18a_dword_800E3298 = 0x800D0948;
const int s18a_dword_800E329C = 0x800D0958;
const int s18a_dword_800E32A0 = 0x800D0988;
const int s18a_dword_800E32A4 = 0x800D0998;
const int s18a_dword_800E32A8 = 0x800D0968;
const int s18a_dword_800E32AC = 0x800D0978;
const int s18a_dword_800E32B0 = 0x800D09A8;
const int s18a_dword_800E32B4 = 0x800D09D0;
const int s18a_dword_800E32B8 = 0x800D09D0;
const int s18a_dword_800E32BC = 0x800D09D0;
const int s18a_dword_800E32C0 = 0x800D09D0;
const int s18a_dword_800E32C4 = 0x800D09B8;
const int s18a_dword_800E32C8 = 0x00000000;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D08F4.s")
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D09F8.s")
const int s18a_dword_800E32CC = 0x800D0AC4;
const int s18a_dword_800E32D0 = 0x800D0AD4;
const int s18a_dword_800E32D4 = 0x800D0AE4;
const int s18a_dword_800E32D8 = 0x800D0AF4;
const int s18a_dword_800E32DC = 0x800D0B0C;
const int s18a_dword_800E32E0 = 0x800D0B04;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0A8C.s")
const int s18a_dword_800E32E4 = 0x800D0B60;
const int s18a_dword_800E32E8 = 0x800D0B80;
const int s18a_dword_800E32EC = 0x800D0B70;
const int s18a_dword_800E32F0 = 0x800D0BA0;
const int s18a_dword_800E32F4 = 0x800D0B90;
const int s18a_dword_800E32F8 = 0x800D0BB0;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0B1C.s")
const int s18a_dword_800E32FC = 0x800D0C0C;
const int s18a_dword_800E3300 = 0x800D0C1C;
const int s18a_dword_800E3304 = 0x800D0C2C;
const int s18a_dword_800E3308 = 0x800D0C4C;
const int s18a_dword_800E330C = 0x800D0C3C;
const int s18a_dword_800E3310 = 0x800D0C5C;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0BD0.s")
const int s18a_dword_800E3314 = 0x800D0CB8;
const int s18a_dword_800E3318 = 0x800D0CC8;
const int s18a_dword_800E331C = 0x800D0CD8;
const int s18a_dword_800E3320 = 0x800D0CF8;
const int s18a_dword_800E3324 = 0x800D0CE8;
const int s18a_dword_800E3328 = 0x800D0D08;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0C74.s")
const int s18a_dword_800E332C = 0x800D0DD8;
const int s18a_dword_800E3330 = 0x800D0DE8;
const int s18a_dword_800E3334 = 0x800D0DF8;
const int s18a_dword_800E3338 = 0x800D0E08;
const int s18a_dword_800E333C = 0x800D0E18;
#pragma INCLUDE_ASM("asm/overlays/s18a/s18a_800D0D28.s")
