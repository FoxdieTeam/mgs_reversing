#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/camera.h"
#include "linkvar.h"
#include "okajima/blood.h"
#include "wolf_eye.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      field_20;
    int      field_24;
    CONTROL  field_28[3];
    OBJECT   field_19C[3];
    int            field_448[3];
    DG_DEF        *field_454;
    DG_DEF        *field_458;
    MOTION_CONTROL field_45C[3];
    MOTION_SEGMENT field_54C[3][19];
    SVECTOR        field_D50[3][18];
    SVECTOR  field_F00[3][18];   /* 0x90 per dog, the block Dog_800CA458 clears */
    SVECTOR  field_10B0[3];
    MATRIX   field_10C8[3][2];
    TARGET  *field_1188[3];
    TARGET   field_1194[3];
    HOMING  *field_126C[3];
    short    field_1278;
    short    field_127A[2];
    short    field_127E[2];
    short    field_1282[2];
    SVECTOR  field_1286[2][32];
    char     pad1486[0x2];
    int      field_1488[3];
    int      field_1494[3];
    u_short  field_14A0[3];
    char     pad14A6[0x2];
    int      field_14A8[3];
    int      field_14B4;
    int      field_14B8[3];
    int      field_14C4;
    int      field_14C8[3];
    int      field_14D4[3];
    int      field_14E0[3];
    int      field_14EC[3];
    int      field_14F8[3];
    int      field_1504[3];
    int      field_1510[3];
    int      field_151C[3];
    int      field_1528;
    SVECTOR  field_152C[3];
    int      field_1544[3];
    int      field_1550[3];
    int      field_155C[3];
    int      field_1568[3];
    int      field_1574[3];
    int      field_1580[3];
    int      field_158C[3];
    int      field_1598[3];
    int      field_15A4[3];
    int      field_15B0[3];
    int      field_15BC[3];
    int      field_15C8[3];
    char     pad15D4[0x8];
    int      field_15DC;
    int      field_15E0;
    char     pad15E4[0x4];
    SVECTOR  field_15E8;
    char     pad15F0[0x4];
    int      field_15F4;
    int      field_15F8;
    int      field_15FC;
    int      field_1600;
    int      field_1604;
    int      field_1608;
    int      field_160C;
    int      field_1610;
    int      field_1614;
    int      field_1618;
    SVECTOR  field_161C[3][4];
    DG_PRIM *field_167C[3];
    int      field_1688;
    SVECTOR  field_168C;
    char     pad1694[0x4];
    int      field_1698[30];
    char     pad1710[0x30];
    int      field_1740;
    int      field_1744;
    int      field_1748;
    SVECTOR  field_174C;
    SVECTOR  field_1754;
    SVECTOR  field_175C;
    SVECTOR  field_1764;
    int      field_176C;
    int      field_1770;
    int      field_1774;
    int      field_1778;
    int      field_177C;
    int      field_1780;
    int      field_1784;
    int      field_1788;
    SVECTOR  field_178C;
    int      field_1794;
    int      field_1798;
    int      field_179C;
    int      field_17A0;
    int      field_17A4;
    int      field_17A8;
    int      field_17AC;
    int      field_17B0;
    int      field_17B4;
    char     pad17B8[0x18];
    int      field_17D0[3];
    int      field_17DC[3];
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

#define BODY_DATA    GV_StrCode("wolfdog")
#define BODY_FLAG    (DG_FLAG_TEXT | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_IRTEXTURE)
#define MOTION_DATA  GV_StrCode("wolfdog")
#define MOTION_DATA2 GV_StrCode("wolfdog2")

/* work->field_1188[] target class while the dog is a live threat */
#define DOG_TARGET_CLASS (TARGET_AVAIL | TARGET_POWER | TARGET_PUSH | TARGET_SEEK)

SVECTOR s12c_dword_800C3430[2] = {{500, 0, 1000}, {-500, 0, 1000}};
SVECTOR s12c_dword_800C3440[2] = {{250, 0, 500}, {-250, 0, 500}};

SVECTOR s12c_dword_800C3450 = {0, 0, 100};
SVECTOR s12c_dword_800C3458 = {64512, 0, 0};

extern GM_CameraSystemWork GM_Camera;

void *AN_Unknown_800CA1EC(MATRIX *mat, int mark);
void  AN_Breath(MATRIX *world);
void  AN_Breath_2(MATRIX *world);
void  AN_Sleep(SVECTOR *pos);
void  AN_Unknown_800C3B7C(MATRIX *matrix);
void *AN_Unknown_800CA320(MATRIX *mat, int mark);
void  s12c_dog_800CEB74(Work *work, int index);

void Dog_800C9E4C(Work *work, int index)
{
    int mod;

    mod = work->field_155C[index] % 32;
    switch (index)
    {
    case 0:
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_28[0].mov, 0xA0, GM_SEMODE_NORMAL);
        }
        else if (mod == 15)
        {
            GM_SeSetMode(&work->field_28[0].mov, 0xA1, GM_SEMODE_NORMAL);
        }
        break;
    case 1:
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_28[1].mov, 0xA2, GM_SEMODE_NORMAL);
        }
        else if (mod == 15)
        {
            GM_SeSetMode(&work->field_28[1].mov, 0xA3, GM_SEMODE_NORMAL);
        }
        break;
    case 2:
        if (mod == 0 || mod == 15)
        {
            GM_SeSetMode(&work->field_28[2].mov, 0xA6, GM_SEMODE_NORMAL);
        }
        else if (mod == 7 || mod == 23)
        {
            GM_SeSetMode(&work->field_28[2].mov, 0xA7, GM_SEMODE_NORMAL);
        }
        break;
    }
}

void Dog_800C9F48(Work *work, int index)
{
    if (work->field_155C[index] & 7)
    {
        return;
    }

    switch (index)
    {
    case 0:
        GM_SeSetMode(&work->field_28[0].mov, 0xA4, GM_SEMODE_NORMAL);
        break;
    case 1:
        GM_SeSetMode(&work->field_28[1].mov, 0xA5, GM_SEMODE_NORMAL);
        break;
    }
}

void Dog_800C9FAC(Work *work, int index)
{
    work->field_15BC[index] = 0;
    DG_InvisiblePrim(work->field_167C[index]);
    DG_InvisibleObjs(work->field_19C[index].objs);
}

void Dog_800CA000(Work *work, int index)
{
    work->field_15BC[index] = 1;
    DG_VisiblePrim(work->field_167C[index]);
    DG_VisibleObjs(work->field_19C[index].objs);
}

void Dog_800CA058(Work *work)
{
    if (work->field_1774 > 0)
    {
        GM_PadVibration = 1;
        GM_PadVibration2 = 0xFF;
        work->field_1774--;
    }
    else
    {
        work->field_1774 = 0;
    }
}

void s12c_dog_800CA098(Work *work, int index)
{
    if (work->field_14F8[index] > 9 && work->field_14F8[index] < 14)
    {
        return;
    }

    if (work->field_1528 > 500)
    {
        return;
    }

    if ((GM_PlayerPosition.vx > -3500 && GM_PlayerPosition.vx < 7000 &&
         GM_PlayerPosition.vz > 2000 && GM_PlayerPosition.vz < 7500) ||
        (GM_PlayerPosition.vx > -14000 && GM_PlayerPosition.vx < -4000 &&
         GM_PlayerPosition.vz > -2000 && GM_PlayerPosition.vz < 8000))
    {
        if (work->field_28[0].mov.vx - work->field_28[1].mov.vx >= 0
                ? work->field_28[0].mov.vx - work->field_28[1].mov.vx < 500
                : work->field_28[1].mov.vx - work->field_28[0].mov.vx < 500)
        {
            if (work->field_28[0].mov.vx < work->field_28[1].mov.vx)
            {
                if (work->field_28[0].n_touches == 0)
                {
                    work->field_10B0[0].vx -= 20;
                    work->field_28[0].mov.vx -= 20;
                    work->field_1550[0] = GV_RandU(128) + 30;
                }

                if (work->field_28[1].n_touches == 0)
                {
                    work->field_10B0[1].vx += 20;
                    work->field_28[1].mov.vx += 20;
                    work->field_1550[1] = GV_RandU(128) + 30;
                }
            }
            else
            {
                if (work->field_28[0].n_touches == 0)
                {
                    work->field_10B0[0].vx += 20;
                    work->field_28[0].mov.vx += 20;
                    work->field_1550[0] = GV_RandU(128) + 30;
                }

                if (work->field_28[1].n_touches == 0)
                {
                    work->field_10B0[1].vx -= 20;
                    work->field_28[1].mov.vx -= 20;
                    work->field_1550[1] = GV_RandU(128) + 30;
                }
            }
        }
    }
    else if (GM_PlayerPosition.vx > 2000 && GM_PlayerPosition.vx < 10000 &&
             GM_PlayerPosition.vz > -2000 && GM_PlayerPosition.vz < 1500)
    {
        if (work->field_28[0].mov.vz - work->field_28[1].mov.vz >= 0
                ? work->field_28[0].mov.vz - work->field_28[1].mov.vz < 500
                : work->field_28[1].mov.vz - work->field_28[0].mov.vz < 500)
        {
            if (work->field_28[0].mov.vz < work->field_28[1].mov.vz)
            {
                if (work->field_28[0].n_touches == 0)
                {
                    work->field_10B0[0].vz -= 20;
                    work->field_28[0].mov.vz -= 20;
                    work->field_1550[0] = GV_RandU(128) + 30;
                }

                if (work->field_28[1].n_touches == 0)
                {
                    work->field_10B0[1].vz += 20;
                    work->field_28[1].mov.vz += 20;
                    work->field_1550[1] = GV_RandU(128) + 30;
                }
            }
            else
            {
                if (work->field_28[0].n_touches == 0)
                {
                    work->field_10B0[0].vz += 20;
                    work->field_28[0].mov.vz += 20;
                    work->field_1550[0] = GV_RandU(128) + 30;
                }

                if (work->field_28[1].n_touches == 0)
                {
                    work->field_10B0[1].vz -= 20;
                    work->field_28[1].mov.vz -= 20;
                    work->field_1550[1] = GV_RandU(128) + 30;
                }
            }
        }
    }
}

// Duplicate of d03a_red_alrt_800C437C
int Dog_800CA3C0(u_short name, int nhashes, u_short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void Dog_800CA458(void *base, int count, int idx)
{
    SVECTOR *dst = (SVECTOR *)((char *)base + (idx * 0x90 + 0xF00));
    int i;

    for (i = 0; i < count; i++)
    {
        *dst++ = DG_ZeroVector;
    }
}
int s12c_dog_800CA4B4(Work *work, int state, int index)
{
    CONTROL *control;

    control = &work->field_28[index];

    if (control->mov.vx > -14000 && control->mov.vx < -4000 && control->mov.vz > -2000 &&
        control->mov.vz < 8000)
    {
        if (GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_DOWNED))
        {
            work->field_1510[index] = state;
            work->field_10B0[index] = control->mov;
            control->turn.vy = work->field_152C[index].vy;
            work->field_1550[index] = index * 60 + 20;
            return 1;
        }

        if (control->mov.vz < 3000 && GM_PlayerPosition.vz > 2500 &&
            work->field_14F8[index] != 3)
        {
            work->field_14F8[index] = 10;
            work->field_1510[index] = 0;
            return 1;
        }

        if (control->mov.vz > 2000 && GM_PlayerPosition.vz < 2500)
        {
            work->field_14F8[index] = 11;
            work->field_1510[index] = 0;
            return 1;
        }
    }
    else if (control->mov.vx > 2000 && control->mov.vx < 10000 && control->mov.vz > -2000 &&
             control->mov.vz < 1500)
    {
        if (GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_DOWNED))
        {
            work->field_1510[index] = state;
            work->field_10B0[index] = control->mov;
            control->turn.vy = work->field_152C[index].vy;
            work->field_1550[index] = index * 60 + 20;
            return 1;
        }

        if (control->mov.vx < 6500 && GM_PlayerPosition.vx > 6000 &&
            work->field_14F8[index] != 12 && work->field_14F8[index] != 3)
        {
            work->field_14F8[index] = 12;
            work->field_1510[index] = 0;
            work->field_1598[index] = 0;
            return 1;
        }

        if (control->mov.vx > 5500 && GM_PlayerPosition.vx < 6000 &&
            work->field_14F8[index] != 13)
        {
            work->field_14F8[index] = 13;
            work->field_1510[index] = 0;
            work->field_1598[index] = 0;
            return 1;
        }
    }
    else if (control->mov.vx > -500 && control->mov.vx < 3500 && control->mov.vz > 500 &&
             control->mov.vz < 2000)
    {
        work->field_1510[index] = state;
        work->field_10B0[index] = control->mov;
        control->turn.vy = work->field_152C[index].vy;
        work->field_1550[index] = index * 60 + 20;
        return 2;
    }

    return 0;
}
void s12c_dog_800CA758(Work *work, int index)
{
    if (work->field_160C >= 2 || work->field_1604 != 0)
    {
        return;
    }

    if (((GM_Item == IT_Handkerchief || (GM_Item == IT_Box1 && (work->field_17B4 & 1)) ||
          (GM_Item == IT_Box2 && (work->field_17B4 & 2)) ||
          (GM_Item == IT_Box3 && (work->field_17B4 & 4))) &&
         work->field_14C8[index] <= 0 && work->field_1608 != 1) ||
        work->field_1608 == 1)
    {
        work->field_14C8[index] = GV_RandU(0x40) + 30;

        if (work->field_158C[index] == 0 && work->field_1598[index] == 0 &&
            work->field_14F8[index] != 5)
        {
            work->field_1598[index] = 1;
            work->field_14F8[index] = 5;
            work->field_1510[index] = 0;
            Dog_800CA458(work, 18, index);
        }
    }
    else if (work->field_158C[index] == 0 && work->field_1598[index] == 1 &&
             work->field_15B0[index] <= 0 && work->field_14C8[index] <= 0 &&
             work->field_14F8[index] != 3)
    {
        work->field_14C8[index] = GV_RandU(0x40) + 30;
        work->field_1598[index] = 0;
        work->field_15B0[index] = 0;
        work->field_14F8[index] = 3;
        work->field_1510[index] = 0;
        Dog_800CA458(work, 18, index);
    }
}

void Dog_800CA93C(Work *work)
{
    if (GV_PadData->press != 0)
    {
        work->field_1600++;
    }
    else
    {
        work->field_1600 = 0;
    }
}

void s12c_dog_800CA96C(Work *work, int index, int hp)
{
    TARGET  *target;
    CONTROL *control;
    int      max;

    if (GM_PlayerStatus & (PLAYER_NOT_PLAYABLE | PLAYER_DAMAGED))
    {
        return;
    }

    target = &work->field_1194[index];
    control = &work->field_28[index];

    target->vital = hp;

    max = 1;
    max = (abs(control->step.vx) > max) ? abs(control->step.vx) : max;
    max = (abs(control->step.vy) > max) ? abs(control->step.vy) : max;
    max = (abs(control->step.vz) > max) ? abs(control->step.vz) : max;

    if (max > 128)
    {
        target->force.vx = control->step.vx * 128 / max;
        target->force.vy = control->step.vy * 128 / max;
        target->force.vz = control->step.vz * 128 / max;
    }
    else
    {
        target->force = control->step;
    }

    GM_MoveTarget(target, &control->mov);

    if (GM_PowerTarget(target))
    {
        GM_SeSet2(0, 0x3F, 0x25);
    }
}

int Dog_800CAB34(Work *work, int arg1)
{
    if (arg1 == 0 || (arg1 == 1 && work->field_1528 < 2000))
    {
        return 1;
    }
    return 0;
}

void Dog_800CAB68(Work *work, int index, int hp)
{
    TARGET *target;

    if (GM_PlayerStatus & (PLAYER_NOT_PLAYABLE | PLAYER_DAMAGED | PLAYER_INVINCIBLE))
    {
        return;
    }

    target = &work->field_1194[index];
    target->vital = hp;
    target->force.vx = GV_RandU(32);
    target->force.vy = GV_RandU(32);
    target->force.vz = GV_RandU(32);
    GM_MoveTarget(target, &GM_PlayerPosition);
    GM_PowerTarget(target);
}

int Dog_800CABF4(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    SVECTOR sp10;
    int     vy;
    int     len;

    GV_SubVec3(arg1, arg0, &sp10);
    arg2->vy = ratan2(sp10.vx, sp10.vz) & 0xFFF;
    vy = sp10.vy;
    sp10.vy = 0;
    len = GV_VecLen3(&sp10);
    arg2->vx = (ratan2(len, vy) & 0xFFF) - 0x400;
    arg2->vz = 0;
    return len;
}

void s12c_dog_800CAC84(Work *work, int index, int state)
{
    if (work->field_1510[index] == 0x25 || work->field_14F8[index] == 12 ||
        work->field_14F8[index] == 13)
    {
        work->field_28[index].r_sphere = -2;
    }
    else if (index != 2)
    {
        if (work->field_1604 == 0)
        {
            work->field_28[index].r_sphere = 550;
        }
    }
    else
    {
        work->field_28[index].r_sphere = 250;
    }

    switch (state)
    {
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 17:
    case 18:
    case 19:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 28:
        work->field_15BC[index] = 1;
        break;

    case 1:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 20:
    case 26:
    case 27:
        work->field_15BC[index] = 0;
        break;
    }

    if (state == 1 || state == 12)
    {
        work->field_14D4[index]++;
    }
    else
    {
        work->field_14D4[index] = 0;
    }
}

const char s12c_dword_800D9B48[] = {0x0, 0x0, 0x0, 0x0};

void s12c_dog_800CAD8C(Work *work, int idx)
{
    SVECTOR vec;
    int     half;
    int     state = work->field_1494[idx];

    work->field_17D0[idx] = work->field_F00[idx][4].vx;
    work->field_17DC[idx] = work->field_F00[idx][5].vx;

    if (state == 0xB || state == 0x14)
    {
        if (work->field_151C[idx] >= 0xFA1)
        {
            work->field_F00[idx][4].vx = 0;
            work->field_F00[idx][5].vx = 0;
        }
        else
        {
            vec.vx = work->field_19C[idx].objs->objs[5].world.t[0];
            vec.vy = work->field_19C[idx].objs->objs[5].world.t[1];
            vec.vz = work->field_19C[idx].objs->objs[5].world.t[2];
            Dog_800CABF4(&vec, &GM_PlayerPosition, &vec);

            half = vec.vx / 2;
            work->field_F00[idx][4].vx = (half + work->field_17D0[idx] * 15) / 16;
            work->field_F00[idx][5].vx = (half + work->field_17DC[idx] * 15) / 16;
        }
    }
}

void s12c_dog_800CAEC8(Work *work, int index, int mark)
{
    CONTROL *control;

    if (work->field_14B8[index] <= 0)
    {
        work->field_14B8[index] = 0x3C;
        switch (index)
        {
        case 0:
            AN_Unknown_800CA1EC(&work->field_19C[0].objs->objs[5].world, mark);
            control = &work->field_28[0];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0x84);
            }
            break;
        case 1:
            AN_Unknown_800CA1EC(&work->field_19C[1].objs->objs[5].world, mark);
            control = &work->field_28[1];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0xBB);
            }
            break;
        case 2:
            AN_Unknown_800CA320(&work->field_19C[2].objs->objs[5].world, mark);
            control = &work->field_28[2];
            if (mark == 6)
            {
                GM_SeSet(&control->mov, 0xBC);
            }
            break;
        }
    }
}

void Dog_800CAFB0(Work *work, int index)
{
    SVECTOR svec1;
    SVECTOR svec2;
    TARGET *target1;
    TARGET *target2;

    if (index == 2)
    {
        svec1.vx = 300;
        svec1.vy = 1000;
        svec1.vz = 300;
        svec2.vx = 40;
        svec2.vy = 200;
        svec2.vz = 40;
    }
    else
    {
        svec1.vx = 500;
        svec1.vy = 1000;
        svec1.vz = 500;
        svec2.vx = 500;
        svec2.vy = 500;
        svec2.vz = 500;
    }
    target1 = work->field_1188[index];
    GM_SetTarget(target1, DOG_TARGET_CLASS, ENEMY_SIDE, &svec1);
    GM_SetPowerTarget(target1, POWER_DECREASE, -1, work->field_14B4, 0xFF, &DG_ZeroVector);

    target2 = &work->field_1194[index];
    GM_SetTarget(target2, TARGET_POWER, ENEMY_SIDE, &svec2);
    GM_SetPowerTarget(target2, POWER_ONCE, 2, 0, 0, &DG_ZeroVector);
}

void Dog_800CB0C8(int *value, int target, int steps)
{
    *value = ((*value * (steps - 1)) + target) / steps;
}

void s12c_dog_800CB114(Work *work, int index)
{
    RADAR_SIGHT_PARAM *r_param;

    r_param = &work->field_28[index].radar_param;
    r_param->dir = work->field_28[index].rot.vy + work->field_F00[index][5].vy;

    if (index != 2)
    {
        r_param->dis = 4000;
        r_param->range = 700;
    }
    else
    {
        r_param->dis = 5000;
        r_param->range = 400;
    }

    r_param->r = 0;
}

void s12c_dog_800CB180(Work *work, int index)
{
    RADAR_SIGHT_PARAM *r_param;

    r_param = &work->field_28[index].radar_param;
    r_param->dir = work->field_28[index].rot.vy + work->field_F00[index][5].vy;

    if (index != 2)
    {
        r_param->dis = work->field_1574[index] * 4000 / 255;
    }
    else
    {
        r_param->dis = work->field_1574[2] * 5000 / 255;
    }
}

void Dog_800CB23C(Work *work, int action, int next, int index)
{
    if (work->field_1494[index] != action)
    {
        s12c_dog_800CAC84(work, index, action);
        work->field_1494[index] = action;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[action], 0, 4);
    }
    else if (work->field_19C[index].is_end == 1)
    {
        if (work->field_1494[index] != 13)
        {
            work->field_14EC[index] = -1;
        }
        else
        {
            work->field_14EC[index] = 0;
        }
        work->field_1510[index] = next;
    }
}

void Dog_800CB324(Work *work, int action, int next_action, int next, int index)
{
    if (work->field_1494[index] != action)
    {
        work->field_1494[index] = action;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[action], 0, 4);
    }
    else if (work->field_19C[index].is_end == 1)
    {
        if (work->field_1494[index] != 13)
        {
            work->field_14EC[index] = -1;
        }
        else
        {
            work->field_14EC[index] = 0;
        }
        work->field_1494[index] = next_action;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[next_action], 0, 4);
        work->field_1510[index] = next;
    }
}

void s12c_dog_800CB42C(Work *work, int action, int next, int next_alt, int index, u_int chance)
{
    int cur;

    cur = work->field_1494[index];
    if (cur != action)
    {
        s12c_dog_800CAC84(work, index, action);
        work->field_1494[index] = action;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[action], 0, 4);
    }
    else if (work->field_19C[index].is_end == 1)
    {
        if (cur != 13)
        {
            work->field_14EC[index] = -1;
        }
        else
        {
            work->field_14EC[index] = 0;
        }
        if (GV_RandU(chance) != 0)
        {
            work->field_1510[index] = next;
        }
        else
        {
            work->field_1510[index] = next_alt;
        }
    }
}

int s12c_dog_800CB54C(Work *work, int index)
{
    CONTROL           *control;
    RADAR_SIGHT_PARAM *radar;

    if (work->field_1604 == 0 && GM_PlayerPosition.vx > -3500 && GM_PlayerPosition.vx < 7000 &&
        GM_PlayerPosition.vz > 2000 && GM_PlayerPosition.vz < 7500)
    {
        return 0;
    }

    control = &work->field_28[index];
    radar = &control->radar_param;

    if (control->map->index != GM_PlayerMap)
    {
        return 0;
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        return 0;
    }

    if ((index != 2 && work->field_151C[index] > 1000) ||
        (index == 2 && work->field_151C[index] > 1500))
    {
        if (work->field_151C[index] > radar->dis)
        {
            return 0;
        }
        if (GV_DiffDirAbs(radar->dir, work->field_152C[index].vy) > radar->range)
        {
            return 0;
        }
    }

    if (HZD_OnlineHazardCheck(control->map->hzd, &GM_PlayerPosition, &control->mov, 0xF, 2))
    {
        return 0;
    }

    work->field_15FC = 0x300;
    return 1;
}

void Dog_800CB6DC(Work *work, int arg1, int arg2)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (work->field_14F8[i] != 9)
        {
            work->field_14F8[i] = arg1;
            work->field_1510[i] = arg2;
        }
    }
}

void s12c_dog_800CB714(Work *work, int index)
{
    SVECTOR  pos[2];
    SVECTOR  head;
    SVECTOR  tail;
    MATRIX   cleared; /* zeroed on the stack by the original and never read */
    CONTROL *control;
    SVECTOR *quad;
    OBJECT  *object;

    cleared = DG_ZeroMatrix;
    object = &work->field_19C[index];

    head.vx = object->objs->objs[16].world.t[0];
    head.vy = 0;
    head.vz = object->objs->objs[16].world.t[2];

    tail.vx = object->objs->objs[4].world.t[0];
    tail.vy = 0;
    tail.vz = object->objs->objs[4].world.t[2];

    control = &work->field_28[index];

    Dog_800CABF4(&head, &tail, &tail);
    DG_SetPos2(&DG_ZeroVector, &tail);
    if (index != 2)
    {
        DG_PutVector(s12c_dword_800C3430, pos, 2);
    }
    else
    {
        DG_PutVector(s12c_dword_800C3440, pos, 2);
    }

    quad = work->field_161C[index];

    quad[0].vx = control->mov.vx + pos[0].vx;
    quad[3].vx = control->mov.vx - pos[0].vx;
    quad[0].vz = control->mov.vz + pos[0].vz;
    quad[3].vz = control->mov.vz - pos[0].vz;
    quad[1].vx = control->mov.vx + pos[1].vx;
    quad[2].vx = control->mov.vx - pos[1].vx;
    quad[1].vz = control->mov.vz + pos[1].vz;
    quad[2].vz = control->mov.vz - pos[1].vz;
    quad[0].vy = quad[1].vy = quad[2].vy = quad[3].vy = control->mov.vy - control->height;

    setRGB0((POLY_FT4 *)work->field_167C[index]->packs[GV_Clock], 0x46, 0x46, 0x46);
}
void s12c_dog_800CB97C(SVECTOR *cur, SVECTOR *target, int steps)
{
    SVECTOR diff;
    int     weight;

    if (steps == 0)
    {
        return;
    }

    cur->vx &= 0xFFF;
    cur->vy &= 0xFFF;
    cur->vz &= 0xFFF;

    target->vx &= 0xFFF;
    target->vy &= 0xFFF;
    target->vz &= 0xFFF;

    diff.vx = target->vx - cur->vx;
    diff.vy = target->vy - cur->vy;
    diff.vz = target->vz - cur->vz;

    if (diff.vx > 0x7FF)
    {
        cur->vx += 0x1000;
    }
    if (diff.vy > 0x7FF)
    {
        cur->vy += 0x1000;
    }
    if (diff.vz > 0x7FF)
    {
        cur->vz += 0x1000;
    }

    if (diff.vx < -0x7FF)
    {
        target->vx += 0x1000;
    }
    if (diff.vy < -0x7FF)
    {
        target->vy += 0x1000;
    }
    if (diff.vz < -0x7FF)
    {
        target->vz += 0x1000;
    }

    weight = steps - 1;
    cur->vy = (cur->vy * weight + target->vy) / steps;

    steps = 8;
    weight = steps - 1;
    cur->vx = (cur->vx * weight + target->vx) / steps;
    cur->vz = (cur->vz * weight + target->vz) / steps;
}

void Dog_800CBBE8(Work *work, int index)
{
    MATRIX  rot;
    SVECTOR pos;

    DG_SetPos(&GM_PlayerBody->objs[1].world);

    pos.vx = GV_RandU(0x800U);
    pos.vy = GV_RandU(0x1000U);
    pos.vz = 0;

    DG_RotatePos(&pos);

    ReadRotMatrix(&rot);
    NewBlood(&rot, 2);

    if (GV_RandU(16) == 0)
    {
        if (GV_RandU(2))
        {
            GM_SeSet(&work->field_28[index].mov, 0xB3);
        }
        else
        {
            GM_SeSet(&work->field_28[index].mov, 0xB4);
        }
    }
    else if (GV_RandU(2))
    {
        GM_SeSet(&work->field_28[index].mov, 0xB9);
    }
    else
    {
        GM_SeSet(&work->field_28[index].mov, 0xBA);
    }
}

void Dog_800CBCF4(Work *work, int arg1)
{
    MATRIX  rot;
    SVECTOR svec;

    DG_SetPos(&work->field_19C[arg1].objs->objs[6].world);

    svec.vx = GV_RandU(0x800);
    svec.vy = GV_RandU(0x1000);
    svec.vz = 0;
    DG_RotatePos(&svec);

    ReadRotMatrix(&rot);
    NewBlood(&rot, 2);

    if (GV_RandU(2) != 0)
    {
        GM_SeSetMode(&work->field_28[arg1].mov, 0xB9, GM_SEMODE_NORMAL);
    }
    else
    {
        GM_SeSetMode(&work->field_28[arg1].mov, 0xBA, GM_SEMODE_NORMAL);
    }

    work->field_1610 = 0;
}

void s12c_dog_800CBDC4(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    OBJECT  *object;
    int      dist;
    int      mod;

    object = &work->field_19C[index];
    control = &work->field_28[index];

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        Dog_800CA458(work, 18, index);

    case 1:
        target.vx = 0;
        target.vy = 0;
        target.vz = -500;
        dist = Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 2);

        if (dist < 1000)
        {
            work->field_1510[index] = 5;
            GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
        }
        else
        {
            Dog_800C9F48(work, index);
            Dog_800CB23C(work, 0, 1, index);
        }
        break;

    case 2:
        target.vx = 3500;
        target.vy = 0;
        target.vz = 0;
        dist = Dog_800CABF4(&control->mov, &target, &control->turn);
        control->turn.vx = 0;

        if (dist < 500)
        {
            work->field_1510[index] = 5;
            GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
        }
        else
        {
            Dog_800C9F48(work, index);
            Dog_800CB23C(work, 0, 1, index);
        }
        break;

    case 5:
        target.vx = 9500;
        target.vy = 0;
        target.vz = 0;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        Dog_800CB23C(work, 25, 14, index);

        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
        break;

    case 14:
        target.vx = 9500;
        target.vy = 0;
        target.vz = 0;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;
        Dog_800CB23C(work, 21, 17, index);
        break;

    case 17:
        target.vx = 9000;
        target.vy = 0;
        target.vz = 0;
        dist = Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;

        if (dist < 1000)
        {
            work->field_1510[index] = 20;
            break;
        }

        mod = work->field_155C[index] % 16;

        if (mod == 0)
        {
            GM_SeSet(&work->field_28[index].mov, 0xB6);
        }
        else if (mod == 8)
        {
            if (GV_RandU(2) != 0)
            {
                GM_SeSet(&work->field_28[index].mov, 0xB3);
            }
            else
            {
                GM_SeSet(&work->field_28[index].mov, 0xB4);
            }
        }

        Dog_800CB23C(work, 22, 17, index);
        break;

    case 20:
        Dog_800CB23C(work, 23, 27, index);
        break;

    case 27:
        if (work->field_15F8 != 1)
        {
            work->field_14F8[index] = 3;
        }
        else
        {
            work->field_14F8[index] = 6;
        }

        work->field_1510[index] = 0;
        work->field_1598[index] = 0;
        s12c_dog_800CA758(work, index);
        break;
    }
}

void s12c_dog_800CC180(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    OBJECT  *object;
    int      dist;
    int      mod;

    object = &work->field_19C[index];
    control = &work->field_28[index];

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        Dog_800CA458(work, 18, index);

    case 1:
        target.vx = 11000;
        target.vy = 0;
        target.vz = 0;
        dist = Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 2);

        if (dist < 1000)
        {
            work->field_1510[index] = 5;
            GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
        }
        else
        {
            Dog_800C9F48(work, index);
            Dog_800CB23C(work, 0, 1, index);
        }
        break;

    case 2:
        target.vx = 8500;
        target.vy = 0;
        target.vz = 0;
        dist = Dog_800CABF4(&control->mov, &target, &control->turn);
        control->turn.vx = 0;

        if (dist < 500)
        {
            work->field_1510[index] = 5;
            GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
        }
        else
        {
            Dog_800C9F48(work, index);
            Dog_800CB23C(work, 0, 1, index);
        }
        break;

    case 5:
        target.vx = 3000;
        target.vy = 0;
        target.vz = 0;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        Dog_800CB23C(work, 25, 14, index);

        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
        break;

    case 14:
        target.vx = 3000;
        target.vy = 0;
        target.vz = 0;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;
        Dog_800CB23C(work, 21, 17, index);
        break;

    case 17:
        target.vx = 3000;
        target.vy = 0;
        target.vz = 0;
        dist = Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;

        if (dist < 1000)
        {
            work->field_1510[index] = 20;
            break;
        }

        mod = work->field_155C[index] % 16;

        if (mod == 0)
        {
            GM_SeSet(&work->field_28[index].mov, 0xB6);
        }
        else if (mod == 8)
        {
            if (GV_RandU(2) != 0)
            {
                GM_SeSet(&work->field_28[index].mov, 0xB3);
            }
            else
            {
                GM_SeSet(&work->field_28[index].mov, 0xB4);
            }
        }

        Dog_800CB23C(work, 22, 17, index);
        break;

    case 20:
        Dog_800CB23C(work, 23, 27, index);
        break;

    case 27:
        if (work->field_15F8 != 1)
        {
            work->field_14F8[index] = 3;
        }
        else
        {
            work->field_14F8[index] = 6;
        }

        work->field_1510[index] = 0;
        work->field_1598[index] = 0;
        s12c_dog_800CA758(work, index);
        break;
    }
}
void s12c_dog_800CC53C(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    OBJECT  *object;
    int      dist;

    object = &work->field_19C[index];
    control = &work->field_28[index];

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        Dog_800CA458(work, 18, index);

    case 1:
        target.vx = index * 300 - 10600;
        target.vy = 0;
        target.vz = -400;
        dist = Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 2);

        switch (index)
        {
        case 0:
            if (dist < 1000)
            {
                if (work->field_1528 < 2000)
                {
                    if ((work->field_155C[0] & 0x1F) == 0)
                    {
                        GM_SeSet(&work->field_28[0].mov, 0x81);
                    }

                    Dog_800CB23C(work, 2, 5, 0);
                }
                else
                {
                    work->field_1510[0] = 5;
                }
            }
            else
            {
                if ((work->field_155C[0] & 7) == 0)
                {
                    GM_SeSetMode(&work->field_28[0].mov, 0xA4, GM_SEMODE_NORMAL);
                }

                Dog_800CB23C(work, 0, 1, 0);
            }
            break;

        case 1:
            if (dist < 1000)
            {
                work->field_1510[1] = 5;
                GM_SeSetMode(&work->field_28[1].mov, 0x85, GM_SEMODE_NORMAL);
            }
            else
            {
                if ((work->field_155C[1] & 7) == 0)
                {
                    GM_SeSetMode(&work->field_28[1].mov, 0xA5, GM_SEMODE_NORMAL);
                }

                Dog_800CB23C(work, 0, 1, 1);
            }
            break;
        }
        break;

    case 5:
        target.vx = -7500;
        target.vy = 0;
        target.vz = 5600;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        Dog_800CB23C(work, 25, 14, index);

        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
        break;

    case 14:
        work->field_1510[index] = 0x25;
        target.vx = -7500;
        target.vy = 0;
        target.vz = 5600;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;
        GM_SeSetMode(&work->field_28[index].mov, 0xB7, GM_SEMODE_NORMAL);

    case 37:
        Dog_800CB23C(work, 5, 17, index);
        break;

    case 17:
        GM_SeSetMode(&work->field_28[index].mov, 0xB5, GM_SEMODE_NORMAL);

        if (work->field_15F8 != 1)
        {
            work->field_14F8[index] = 3;
        }
        else
        {
            work->field_14F8[index] = 6;
        }

        work->field_1510[index] = 0;
        work->field_1598[index] = 0;
        s12c_dog_800CA758(work, index);
        break;
    }
}

void s12c_dog_800CC8B4(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    OBJECT  *object;
    int      dist;

    object = &work->field_19C[index];
    control = &work->field_28[index];

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        Dog_800CA458(work, 18, index);

    case 1:
        target.vx = -7000;
        target.vy = 0;
        target.vz = 5500;
        dist = Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 2);

        switch (index)
        {
        case 0:
            if (dist < 1000)
            {
                if (work->field_1528 < 2000)
                {
                    if ((work->field_155C[0] & 0x1F) == 0)
                    {
                        GM_SeSet(&work->field_28[0].mov, 0x81);
                    }

                    Dog_800CB23C(work, 2, 5, 0);
                }
                else
                {
                    work->field_1510[0] = 5;
                }
            }
            else
            {
                if ((work->field_155C[0] & 7) == 0)
                {
                    GM_SeSetMode(&work->field_28[0].mov, 0xA4, GM_SEMODE_NORMAL);
                }

                Dog_800CB23C(work, 0, 1, 0);
            }
            break;

        case 1:
            if (dist < 1000)
            {
                work->field_1510[1] = 5;
                GM_SeSetMode(&work->field_28[1].mov, 0x85, GM_SEMODE_NORMAL);
            }
            else
            {
                if ((work->field_155C[1] & 7) == 0)
                {
                    GM_SeSetMode(&work->field_28[1].mov, 0xA5, GM_SEMODE_NORMAL);
                }

                Dog_800CB23C(work, 0, 1, 1);
            }
            break;
        }
        break;

    case 5:
        target.vx = index * 300 - 10600;
        target.vy = 0;
        target.vz = -400;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        Dog_800CB23C(work, 25, 14, index);

        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
        break;

    case 14:
        work->field_1510[index] = 0x25;
        target.vx = index * 300 - 10600;
        target.vy = 0;
        target.vz = -400;
        Dog_800CABF4(&control->mov, &target, &control->turn);
        control->rot = control->turn;
        GM_SeSetMode(&work->field_28[index].mov, 0xB7, GM_SEMODE_NORMAL);

    case 37:
        Dog_800CB23C(work, 5, 17, index);
        break;

    case 17:
        GM_SeSetMode(&work->field_28[index].mov, 0xB5, GM_SEMODE_NORMAL);

        if (work->field_15F8 != 1)
        {
            work->field_14F8[index] = 3;
        }
        else
        {
            work->field_14F8[index] = 6;
        }

        work->field_1510[index] = 0;
        work->field_1598[index] = 0;
        s12c_dog_800CA758(work, index);
        break;
    }
}

void s12c_dog_800CCC3C(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  point;
    CONTROL *control;
    OBJECT  *object;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int      i;

    control = &work->field_28[index];
    object = &work->field_19C[index];
    hzd = control->map->hzd;

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        work->field_10B0[index] = control->mov;
        Dog_800CA458(work, 18, index);
        work->field_1550[index] = index * 20 + 20;
        control->turn.vy = work->field_152C[index].vy;

    case 1:
        if (work->field_151C[index] < 3000)
        {
            work->field_1550[index] = index * 20 + 20;
            work->field_1510[index] = 6;
            work->field_10B0[index] = control->mov;
            control->turn.vy = work->field_152C[index].vy;
            break;
        }

        if (work->field_1550[index]-- > 0)
        {
            control->mov.vx = work->field_10B0[index].vx;
            control->mov.vz = work->field_10B0[index].vz;

            if ((work->field_155C[index] & 0x1F) == 0)
            {
                GM_SeSet(&work->field_28[index].mov, 0x81);
            }

            control->turn.vy = work->field_152C[index].vy;
            Dog_800CB23C(work, 2, 1, index);
            break;
        }

        work->field_1510[index] = 2;
        GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
        break;

    case 2:
        if (work->field_151C[index] < 5000)
        {
            work->field_1550[index] = index * 20 + 20;
            work->field_1510[index] = 6;
            work->field_10B0[index] = control->mov;
            control->turn.vy = work->field_152C[index].vy;
            break;
        }

        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        Dog_800CB23C(work, 25, 4, index);

        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
        break;

    case 4:
        control->turn.vy = work->field_152C[index].vy;
        work->field_1510[index] = 5;

        if (work->field_1604 == 0 && s12c_dog_800CA4B4(work, 6, index) != 0)
        {
            break;
        }

    case 5:
        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
        work->field_1688 = HZD_GetAddress(hzd, &GM_PlayerPosition, -1);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_1688,
                                             &control->mov)];

        if (index == 0 && work->field_1528 < 1000)
        {
            for (i = 0; i < 6; i++)
            {
                if (zone->nears[i] == 0xFF)
                {
                    break;
                }
            }

            work->field_1688 = zone->nears[GV_RandU(0x1000) % i];
            work->field_1688 = HZD_GetAddress(hzd, &control->mov, work->field_1688);
            zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index],
                                                 work->field_1688, &control->mov)];
        }

        point.vx = zone->x;
        point.vy = zone->y;
        point.vz = zone->z;
        Dog_800CABF4(&control->mov, &point, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);

        if (work->field_151C[index] < 400 && Dog_800CAB34(work, index) != 0)
        {
            work->field_10B0[index] = control->mov;
            if (GM_PlayerBody->objs->objs[6].world.t[1] -
                    GM_PlayerBody->objs->objs[12].world.t[1] >=
                701)
            {
                work->field_1510[index] = 20;
            }
            else
            {
                work->field_1510[index] = 27;
            }

            control->turn.vy = work->field_152C[index].vy;
            break;
        }

        if (work->field_155C[index] % 128 < 100 &&
            work->field_151C[index] < index * 500 + 2000 &&
            ABS(work->field_28[0].mov.vx - work->field_28[1].mov.vx) >= 501 &&
            ABS(work->field_28[0].mov.vz - work->field_28[1].mov.vz) >= 501)
        {
            work->field_1550[index] = index * 40 + 40;
            work->field_1510[index] = 6;
            work->field_10B0[index] = control->mov;
            control->turn.vy = work->field_152C[index].vy;
            break;
        }

        Dog_800C9F48(work, index);
        Dog_800CB23C(work, 0, 4, index);
        break;

    case 6:
        if (work->field_1550[index]-- > 0)
        {
            control->mov.vx = work->field_10B0[index].vx;
            control->mov.vz = work->field_10B0[index].vz;

            if ((work->field_155C[index] & 0x1F) == 0)
            {
                GM_SeSet(&work->field_28[index].mov, 0x81);
            }

            control->turn.vy = work->field_152C[index].vy;
            Dog_800CB23C(work, 2, 6, index);
            break;
        }

        if ((GM_PlayerPosition.vx > -3500 && GM_PlayerPosition.vx < 7000 &&
             GM_PlayerPosition.vz > 2000 && GM_PlayerPosition.vz < 7500) ||
            (GM_PlayerPosition.vx > -14000 && GM_PlayerPosition.vx < -4000 &&
             GM_PlayerPosition.vz > -2000 && GM_PlayerPosition.vz < 8000) ||
            (GM_PlayerPosition.vx > 2000 && GM_PlayerPosition.vx < 10000 &&
             GM_PlayerPosition.vz > -2000 && GM_PlayerPosition.vz < 1500))
        {
            GM_SeSetMode(&work->field_28[index].mov, 0x85, GM_SEMODE_NORMAL);
            control->mov.vx = work->field_10B0[index].vx;
            control->mov.vz = work->field_10B0[index].vz;
            control->turn = work->field_152C[index];
            control->turn.vx = 0;
            work->field_1510[index] = 7;
            break;
        }

        work->field_155C[index] = 0;

        switch (GV_RandU(2))
        {
        case 0:
            work->field_1510[index] = 11;
            break;
        case 1:
            work->field_1510[index] = 13;
            break;
        }
        break;

    case 7:
        if (GV_RandU(16) == 0)
        {
            AN_Breath(&object->objs->objs[6].world);
        }

        Dog_800CB23C(work, 25, 32, index);
        break;

    case 11:
        if (work->field_155C[index] < 8 && work->field_155C[index] % 3 == 0)
        {
            switch (index)
            {
            case 0:
                GM_SeSetMode(&work->field_28[0].mov, 0xA4, GM_SEMODE_NORMAL);
                break;
            case 1:
                GM_SeSetMode(&work->field_28[1].mov, 0xA5, GM_SEMODE_NORMAL);
                break;
            }
        }
        else if (work->field_155C[index] == 8)
        {
            GM_SeSetMode(&work->field_28[index].mov, 0xB7, GM_SEMODE_NORMAL);
        }

        s12c_dog_800CA96C(work, index, 0x60);
        Dog_800CB23C(work, 4, 17, index);

        if (work->field_151C[index] < 400 && Dog_800CAB34(work, index) != 0)
        {
            work->field_10B0[index] = control->mov;
            if (GM_PlayerBody->objs->objs[6].world.t[1] -
                    GM_PlayerBody->objs->objs[12].world.t[1] >=
                701)
            {
                work->field_1510[index] = 20;
            }
            else
            {
                work->field_1510[index] = 27;
            }

            control->turn.vy = work->field_152C[index].vy;
        }
        break;

    case 13:
        s12c_dog_800CA96C(work, index, 0x60);
        Dog_800CB23C(work, 17, 17, index);

        if (work->field_151C[index] < 400 && Dog_800CAB34(work, index) != 0)
        {
            work->field_10B0[index] = control->mov;
            if (GM_PlayerBody->objs->objs[6].world.t[1] -
                    GM_PlayerBody->objs->objs[12].world.t[1] >=
                701)
            {
                work->field_1510[index] = 20;
            }
            else
            {
                work->field_1510[index] = 27;
            }

            control->turn.vy = work->field_152C[index].vy;
        }
        break;

    case 17:
        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
        work->field_15E8 = GM_PlayerPosition;
        work->field_15E0 = HZD_GetAddress(hzd, &work->field_15E8, -1);
        zone = &hzd->def->zones[work->field_15E0 & 0xFF];

        for (i = 0; i < 6; i++)
        {
            if (zone->nears[i] == 0xFF)
            {
                break;
            }
        }

        work->field_15E0 = zone->nears[GV_RandU(0x1000) % i];
        work->field_15E0 = HZD_GetAddress(hzd, &work->field_15E8, work->field_15E0);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_15E0,
                                             &control->mov)];
        point.vx = zone->x;
        point.vy = zone->y;
        point.vz = zone->z;
        Dog_800CABF4(&control->mov, &point, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);
        Dog_800C9F48(work, index);
        Dog_800CB23C(work, 0, 4, index);
        break;

    case 20:
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        Dog_800CB23C(work, 19, 20, index);

        if (work->field_1600 >= 2 || work->field_151C[index] >= 201)
        {
            work->field_1510[index] = 4;
        }

        if ((work->field_155C[index] & 0xF) == 0)
        {
            Dog_800CBBE8(work, index);
        }

        if (GM_PlayerBody->objs->objs[6].world.t[1] -
                GM_PlayerBody->objs->objs[12].world.t[1] <
            900)
        {
            work->field_1510[index] = 4;
        }

        Dog_800CAB68(work, index, 0x10);
        break;

    case 27:
        if ((GV_Time % 32 < 16 && index == 0 && work->field_14F8[1] == 6 &&
             work->field_1510[1] == 27) ||
            (GV_Time % 32 >= 16 && index == 1 && work->field_14F8[0] == 6 &&
             work->field_1510[0] == 27))
        {
            work->field_1510[index] = 4;
            break;
        }

        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        Dog_800CB23C(work, 6, 27, index);

        if (work->field_1600 >= 2 || work->field_151C[index] >= 501)
        {
            work->field_1510[index] = 4;
        }

        if ((work->field_155C[index] & 0xF) == 0)
        {
            Dog_800CBBE8(work, index);
        }

        if (GM_PlayerBody->objs->objs[6].world.t[1] -
                GM_PlayerBody->objs->objs[12].world.t[1] >=
            901)
        {
            work->field_1510[index] = 4;
        }

        Dog_800CAB68(work, index, 0x10);
        break;

    case 32:
        if (GV_RandU(2) != 0 && !(GM_PlayerStatus & PLAYER_INTRUDE))
        {
            work->field_155C[index] = 0;
            work->field_1510[index] = 11;
            break;
        }

        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index],
                                             work->field_14A8[index], &control->mov)];
        point.vx = zone->x;
        point.vy = zone->y;
        point.vz = zone->z;
        Dog_800CABF4(&control->mov, &point, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);
        Dog_800C9F48(work, index);
        Dog_800CB23C(work, 0, 0, index);
        break;
    }
}
void s12c_dog_800CDBC4(Work *work, int index)
{
    SVECTOR  rot;
    CONTROL *control;
    SVECTOR *route;
    short   *step;
    int     *slot;
    int      dist;
    int      delta;

    /* every per-dog int array sits at work + index * 4, so the state read below
       shares that base; taking it here is what keeps it live across the call.
       work->field_1510[index] compiles two instructions shorter. */
    slot = (int *)work + index;
    control = &work->field_28[index];
    step = &work->field_127E[index];
    route = work->field_1286[index];
    dist = Dog_800CABF4(&control->mov, &route[*step], &rot);
    rot.vx = work->field_14A0[index];

    if (slot[0x1510 / 4] != 0x11)
    {
        s12c_dog_800CB97C(&control->turn, &rot, 32);
    }

    if (dist < 500)
    {
        work->field_1282[index] = *step;
        (*step)++;

        if (*step >= work->field_127A[index])
        {
            *step = 0;
        }

        dist = Dog_800CABF4(&route[work->field_1282[index]], &route[*step], &rot);
        work->field_14A0[index] = rot.vx;
    }

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;

    case 1:
        work->field_F00[index][5].vy = rsin(work->field_1544[index]) / 8;
        delta = index * 2 + 16;
        work->field_1544[index] += delta;
        s12c_dog_800CB42C(work, 1, 1, 5, index, 16);
        work->field_10B0[index] = control->mov;
        break;

    case 5:
        if (dist >= 3001)
        {
            work->field_1544[index] = 0;
            work->field_1550[index] = 0;
            work->field_1510[index] = 20;
            break;
        }

        work->field_1544[index] = 0;
        work->field_1550[index] = 8;

    case 14:
        work->field_1510[index] = 17;
        work->field_1550[index]--;

    case 17:
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        work->field_F00[index][5].vy = work->field_F00[index][5].vy * 7 / 8;
        work->field_1544[index] = 0;
        Dog_800CB0C8(&work->field_1574[index], 0x80, 16);

        if (work->field_1550[index] > 0)
        {
            Dog_800CB23C(work, 9, 14, index);
        }
        else if (GV_RandU(0x40) != 0)
        {
            s12c_dog_800CB42C(work, 9, 1, 5, index, 4);
        }
        else
        {
            s12c_dog_800CB42C(work, 9, 1, 27, index, 2);
        }
        break;

    case 20:
        work->field_F00[index][5].vy = work->field_F00[index][5].vy * 7 / 8;
        work->field_1544[index] = 0;
        Dog_800CB23C(work, 8, 1, index);
        break;

    case 27:
        work->field_1544[index] = 0;
        work->field_1550[index] = 60;
        Dog_800CB324(work, 14, 13, 32, index);
        break;

    case 32:
        GM_SeSetMode(&work->field_28[index].mov, 0xB8, GM_SEMODE_NORMAL);

    case 33:
        work->field_1510[index] = 34;
        work->field_1550[index]--;
        GM_SeSetMode(&work->field_28[index].mov, 0xB8, GM_SEMODE_NORMAL);

    case 34:
        if (work->field_1550[index] > 0 || work->field_151C[index] > 1000)
        {
            Dog_800CB23C(work, 13, 33, index);
        }
        else
        {
            Dog_800CB23C(work, 15, 35, index);
        }
        break;

    case 35:
        Dog_800CB23C(work, 16, 1, index);
        break;
    }
}

/* The two field_10B0 stores go through a byte offset taken before the switch,
   which is what keeps index * 8 in a saved register across the GV_RandU call. */
void s12c_dog_800CE034(Work *work, int index)
{
    CONTROL *control;
    SVECTOR  saved_rot; /* written on the stack by the original and never read */
    int      off;

    saved_rot.vx = work->field_14A0[index];
    control = &work->field_28[index];
    off = index * 8;

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        work->field_1544[index] = 0;
        work->field_1550[index] = GV_RandU(16) + 32;
        *(u_short *)((char *)work + off + 0x10B0) = control->mov.vx;
        *(u_short *)((char *)work + off + 0x10B4) = control->mov.vz;

    case 1:
        work->field_1510[index] = 5;
        work->field_1550[index]--;

    case 5:
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;

        if (work->field_1550[index] > 0)
        {
            Dog_800CB0C8(&work->field_1574[index], 16, 16);
            Dog_800CB23C(work, 9, 1, index);
        }
        else
        {
            work->field_14F8[index] = 0;
            work->field_1510[index] = 0;
        }
        break;
    }
}
void s12c_dog_800CE194(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  point;
    SVECTOR  target;
    int      dist;
    CONTROL *control;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int     *slot;
    int      i;
    int      off;

    /* see s12c_dog_800CDBC4: the shared per-dog base has to be taken before the
       calls below for the 0x151C store to reuse it. Both work->field_151C[index]
       and an int *dist_out local re-derive it at the store instead. */
    dist = -1;
    off = index * 8;
    control = &work->field_28[index];
    slot = (int *)work + index;
    hzd = control->map->hzd;

    if (work->field_1608 == 1)
    {
        work->field_168C = s12c_800DA418;
        target.vx = 8500;
        target.vy = 0;
        target.vz = -9500;
        slot[0x151C / 4] =
            Dog_800CABF4(&control->mov, &work->field_168C, (SVECTOR *)((char *)work + (off + 0x152C)));
        dist = Dog_800CABF4(&control->mov, &target, &rot);
    }
    else
    {
        work->field_168C = GM_PlayerPosition;
        target = work->field_168C;
    }

    if (work->field_15B0[index] > 0)
    {
        work->field_15B0[index]--;
    }

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        work->field_1544[index] = GV_RandU(16) + 10;
        work->field_15B0[index] = 60;
        s12c_dog_800CAEC8(work, index, 6);

    case 1:
        if (work->field_1604 == 0 && index != 2 && work->field_151C[index] >= 1501 &&
            work->field_1608 != 1 && s12c_dog_800CA4B4(work, 5, index) != 0)
        {
            break;
        }

        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
        work->field_1688 = HZD_GetAddress(hzd, &target, -1);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_1688,
                                             &control->mov)];

        if (index == 0 && work->field_1528 < 1000)
        {
            if (work->field_28[0].n_touches != 0)
            {
                work->field_1510[0] = 5;
                break;
            }

            for (i = 0; i < 6; i++)
            {
                if (zone->nears[i] == 0xFF)
                {
                    break;
                }
            }

            work->field_1688 = zone->nears[GV_RandU(0x1000) % i];
            work->field_1688 = HZD_GetAddress(hzd, &control->mov, work->field_1688);
            zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index],
                                                 work->field_1688, &control->mov)];
        }

        point.vx = zone->x;
        point.vy = zone->y;
        point.vz = zone->z;
        Dog_800CABF4(&control->mov, &point, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);
        work->field_1544[index]--;

        if (work->field_1608 == 0 && work->field_1544[index] < 0 &&
            work->field_151C[index] < index * 500 + 1500)
        {
            work->field_1510[index] = 5;
            work->field_15B0[index] = 60;
            s12c_dog_800CAEC8(work, index, 6);
            break;
        }

        if (work->field_1608 == 1)
        {
            if (work->field_151C[index] < index * 200 + 1500 || dist < 4000)
            {
                work->field_1510[index] = 5;
                work->field_15B0[index] = 60;
                s12c_dog_800CAEC8(work, index, 6);
                break;
            }
        }

        Dog_800CB23C(work, 12, 1, index);

        if (index != 2 && work->field_151C[index] < 5000 && work->field_14D4[index] >= 91)
        {
            work->field_1510[index] = 5;
        }
        break;

    case 5:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        Dog_800CB23C(work, 10, 14, index);
        break;

    case 14:
        work->field_1510[index] = 15;

        if (work->field_155C[index] % 128 < 20)
        {
            work->field_15B0[index] = 60;
            s12c_dog_800CAEC8(work, index, 6);
        }

        work->field_1610 = 0;

        if (GM_Item == IT_Handkerchief && work->field_1608 != 1 && work->field_1794 != -1)
        {
            GCL_ExecProc(work->field_1794, NULL);
            work->field_1794 = -1;
        }

    case 15:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;

        if ((GV_Time & 0xF) == 0 && GV_RandU(2) != 0)
        {
            switch (GV_RandU(0x1000) % 3)
            {
            case 0:
                GM_SeSetMode(&work->field_28[index].mov, 0xB0, GM_SEMODE_NORMAL);
                break;
            case 1:
                GM_SeSetMode(&work->field_28[index].mov, 0xB1, GM_SEMODE_NORMAL);
                break;
            case 2:
                GM_SeSetMode(&work->field_28[index].mov, 0xB2, GM_SEMODE_NORMAL);
                break;
            }
        }

        s12c_dog_800CB42C(work, 11, 14, 17, index, 4);

        if (work->field_1608 != 1)
        {
            work->field_1550[index]--;

            if (work->field_1550[index] < 0 && work->field_151C[index] > index * 500 + 5000)
            {
                work->field_1510[index] = 1;
                work->field_1550[index] = GV_RandU(0x80) + 30;
            }
        }

        if (work->field_151C[index] < 1000 && work->field_1778 != GM_PlayerPosition.vy)
        {
            work->field_1510[index] = 0;
        }
        break;

    case 17:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;

        if (index == 2 && (work->field_155C[index] & 0x3F) == 0 && GV_RandU(4) == 0)
        {
            work->field_1510[index] = 0;
        }

        if ((work->field_155C[index] & 0x1FF) == 0 && GV_RandU(8) == 0)
        {
            work->field_1510[index] = 27;
        }

        s12c_dog_800CB42C(work, 20, 14, 17, index, 4);

        if (work->field_1608 != 1)
        {
            work->field_1550[index]--;

            if (work->field_1550[index] < 0 && work->field_151C[index] > index * 500 + 5000)
            {
                work->field_1510[index] = 1;
                work->field_1550[index] = GV_RandU(0x80) + 30;
            }
        }

        if (work->field_151C[index] < 1000 && work->field_1778 != GM_PlayerPosition.vy)
        {
            work->field_1510[index] = 0;
        }
        break;

    case 27:
        Dog_800CB324(work, 14, 13, 34, index);
        break;

    case 34:
        Dog_800CB0C8(&work->field_1574[index], 0, 32);

        if (work->field_151C[index] < index * 500 + 4000 && work->field_151C[index] > 1000)
        {
            if (GV_RandU(16) == 0)
            {
                Dog_800CB324(work, 13, 29, 35, index);
            }
            else
            {
                Dog_800CB324(work, 13, 13, 34, index);
            }
        }
        else
        {
            Dog_800CB324(work, 15, 16, 36, index);
        }
        break;

    case 35:
        Dog_800CB324(work, 29, 13, 34, index);
        break;

    case 36:
        Dog_800CB23C(work, 16, 0, index);
        break;
    }

    if (index == 2 && (work->field_1510[index] == 15 || work->field_1510[index] == 17))
    {
        int timer = work->field_1798;

        work->field_1798 = timer - 1;

        if (timer > 40 && timer < 61)
        {
            work->field_F00[index][4].vz += 8;
            work->field_F00[index][5].vz += 8;
        }

        if (work->field_1798 < 10)
        {
            work->field_F00[index][4].vz -= 16;
            work->field_F00[index][5].vz -= 16;
        }

        if (work->field_1798 < 0)
        {
            work->field_1798 = GV_RandU(0x200) + 256;
            Dog_800CA458(work, 18, index);
        }
    }
}

const char s12c_dword_800D9F08[] = {0x0, 0x0, 0x0, 0x0};

void DogExecProc_800CEB2C(Work *work)
{
    GCL_ARGS args;
    long     data[1];

    data[0] = work->field_17B4;

    args.argc = 1;
    args.argv = data;

    if (work->field_17B0 != -1)
    {
        GCL_ForceExecProc(work->field_17B0, &args);
    }
}

void s12c_dog_800CEB74(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  pos;
    MATRIX   mat1;
    MATRIX   mat2;
    CONTROL *control;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int     *slot;
    int      off8;

    /* as in s12c_dog_800CDBC4: the two per-dog bases are taken up front so the
       case 0 stores below reuse them; the member forms cost four instructions */
    control = &work->field_28[index];
    slot = (int *)work + index;
    off8 = index * 8;
    hzd = control->map->hzd;

    if (index != 2)
    {
        switch (slot[0x1510 / 4])
        {
        case 0:
            work->field_1510[index] = 1;
            ((Work *)((char *)work + off8))->field_10B0[0] = control->mov;
            Dog_800CA458(work, 18, index);
            control->turn.vy = ((Work *)((char *)work + off8))->field_152C[0].vy;

        case 1:
            control->mov.vx = work->field_10B0[index].vx;
            control->mov.vz = work->field_10B0[index].vz;

            if ((work->field_155C[index] & 0x1F) == 0)
            {
                GM_SeSet(&control->mov, 0x81);
            }

            Dog_800CB23C(work, 2, 1, index);
            break;
        }

        return;
    }

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        GM_GameStatus |= STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF;
        work->field_10B0[index] = control->mov;
        Dog_800CA458(work, 18, index);
        control->turn.vy = work->field_152C[index].vy;
        work->field_1550[index] = 30;
        work->field_1618 = -1;

    case 1:
        work->field_1550[index]--;

        if (GM_Item > IT_Scope && GM_Item < IT_NVG)
        {
            pos = GM_PlayerPosition;
            pos.vx = pos.vx < 10000 ? pos.vx + 800 : pos.vx - 800;

            if (work->field_151C[index] > 900 && work->field_151C[index] < 1100)
            {
                work->field_10B0[index] = control->mov;

                if (work->field_1550[index] < 0)
                {
                    work->field_179C = 0;

                    if (GV_RandU(2) != 0)
                    {
                        work->field_1510[index] = 7;
                    }
                    else
                    {
                        work->field_1510[index] = 9;
                    }
                }
                break;
            }
        }
        else if (work->field_1618 != -1)
        {
            work->field_1618--;
            control->mov = work->field_10B0[index];
            Dog_800CB23C(work, 9, 1, index);

            if (work->field_1618 > 0)
            {
                break;
            }

            if (work->field_1550[index] >= 0)
            {
                break;
            }

            work->field_1510[index] = 6;
            control->turn.vy = work->field_152C[index].vy;
            Dog_800CBCF4(work, index);
            Dog_800CAB68(work, index, 16);
            s12c_800DA420 &= ~1;
            break;
        }
        else if (work->field_151C[index] < 300)
        {
            work->field_1618 = 30;
            work->field_10B0[index] = control->mov;
            break;
        }
        else if (work->field_151C[index] < 3000)
        {
            control->turn.vy = work->field_152C[index].vy;

            if ((GV_Time & 7) == 0 && GV_RandU(2) == 0)
            {
                GM_SeSet2(0, 0x3F, 0xBD);
            }

            Dog_800CB23C(work, 12, 1, index);
            break;
        }
        else
        {
            work->field_14A8[index] =
                HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
            work->field_1688 = HZD_GetAddress(hzd, &GM_PlayerPosition, -1);
            zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index],
                                                 work->field_1688, &control->mov)];
            pos.vx = zone->x;
            pos.vy = zone->y;
            pos.vz = zone->z;
        }

        Dog_800CABF4(&control->mov, &pos, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);
        Dog_800CB23C(work, 12, 1, index);

        if ((GV_Time & 7) == 0 && GV_RandU(4) == 0)
        {
            GM_SeSet2(0, 0x3F, 0xBD);
        }
        break;

    case 6:
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        Dog_800CB23C(work, 6, 14, index);
        break;

    case 7:
        work->field_179C++;

        if (work->field_179C >= 39)
        {
            if (work->field_179C == 39)
            {
                GM_SeSet2(0, 0x7F, 0xC6);
            }

            mat1.t[0] = (GM_PlayerPosition.vx + control->mov.vx) / 2;
            mat1.t[1] = (GM_PlayerPosition.vy + control->mov.vy) / 2;
            mat1.t[2] = (GM_PlayerPosition.vz + control->mov.vz) / 2;
            AN_Unknown_800C3B7C(&mat1);
        }

        work->field_175C = control->mov;
        work->field_1764 = control->mov;
        work->field_175C.vz = GM_PlayerPosition.vz < -8000 ? work->field_175C.vz + 2000
                                                           : work->field_175C.vz - 2000;
        if (GM_PlayerPosition.vx < 10000)
        {
            work->field_1764.vx -= 1000;
        }
        else
        {
            work->field_1764.vx += 1000;
        }

        work->field_175C.vy += 2500;
        work->field_174C = work->field_175C;
        work->field_1754 = work->field_1764;
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        control->turn.vy -= 0x400;
        Dog_800CB23C(work, 26, 14, index);
        break;

    case 9:
        work->field_179C++;

        if (work->field_179C >= 39)
        {
            if (work->field_179C == 39)
            {
                GM_SeSet2(0, 0x7F, 0xC6);
            }

            mat2.t[0] = (GM_PlayerPosition.vx + control->mov.vx) / 2;
            mat2.t[1] = (GM_PlayerPosition.vy + control->mov.vy) / 2;
            mat2.t[2] = (GM_PlayerPosition.vz + control->mov.vz) / 2;
            AN_Unknown_800C3B7C(&mat2);
        }

        work->field_175C = control->mov;
        work->field_1764 = control->mov;
        work->field_175C.vz = GM_PlayerPosition.vz < -8000 ? work->field_175C.vz + 2000
                                                           : work->field_175C.vz - 2000;
        if (GM_PlayerPosition.vx < 10000)
        {
            work->field_1764.vx -= 1000;
        }
        else
        {
            work->field_1764.vx += 1000;
        }

        work->field_175C.vy += 2500;
        work->field_174C = work->field_175C;
        work->field_1754 = work->field_1764;
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        control->turn.vy += 0x400;
        Dog_800CB23C(work, 27, 14, index);
        break;

    case 14:
        if (GM_Item == IT_Box1)
        {
            work->field_17B4 |= 1;
        }

        if (GM_Item == IT_Box2)
        {
            work->field_17B4 |= 2;
        }

        if (GM_Item == IT_Box3)
        {
            work->field_17B4 |= 4;
        }

        DogExecProc_800CEB2C(work);
        work->field_14F8[index] = 5;
        work->field_1510[index] = 0;

        if (work->field_14F8[0] != 5)
        {
            work->field_14F8[0] = 5;
            work->field_1510[0] = 0;
        }

        if (work->field_14F8[1] != 5)
        {
            work->field_14F8[1] = 5;
            work->field_1510[1] = 0;
        }
        break;
    }
}

const char s12c_dword_800D9F48[] = {0x0, 0x0, 0x0, 0x0};

void s12c_dog_800CF578(Work *work, int idx)
{
    CONTROL *ctrl = &work->field_28[idx];
    SVECTOR  vec;

    switch (work->field_1510[idx])
    {
    case 0:
        work->field_1510[idx] = 1;
        GM_SeSetMode(&ctrl->mov, 0x8D, GM_SEMODE_NORMAL);
        work->field_126C[idx]->flag = 0;
        /* fall through */
    case 1:
        work->field_1574[idx] = 0;
        Dog_800CB23C(work, 0x18, 5, idx);
        break;
    case 5:
        if (work->field_151C[idx] >= 0xBB9)
        {
            Dog_800CABF4(&ctrl->mov, &GM_PlayerPosition, &vec);
            vec.vx = 0;
            s12c_dog_800CB97C(&ctrl->turn, &vec, 8);
        }
        Dog_800CB23C(work, 0x1C, 0xE, idx);
        break;
    case 0xE:
        work->field_14F8[idx] = 6;
        work->field_1510[idx] = 0;
        s12c_dog_800CA758(work, idx);
        work->field_126C[idx]->flag = 1;
        break;
    }
}
void s12c_dog_800CF6CC(Work *work, int index)
{
    CONTROL *control;
    TARGET  *target;

    control = &work->field_28[index];
    target = work->field_1188[index];

    work->field_1574[index] = 0;
    GM_ConfigControlAttribute(control, 1);

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        target->size = DG_ZeroVector;
        GM_SeSetMode(&work->field_28[index].mov, 0x91, GM_SEMODE_NORMAL);
        work->field_126C[index]->flag = 0;

    case 1:
        Dog_800CB23C(work, 24, 5, index);
        break;

    case 5:
        work->field_1510[index] = 6;
        work->field_155C[index] = 0;
        GM_UnkFlagA6++;

    case 6:
        work->field_19C[index].m_ctrl = NULL;

        if (work->field_155C[index] % 4 < 2)
        {
            Dog_800C9FAC(work, index);
        }
        else
        {
            Dog_800CA000(work, index);
        }

        if (work->field_155C[index] < 61)
        {
            break;
        }

        if (work->field_177C >= work->field_1780 || work->field_1608 == 1)
        {
            Dog_800C9FAC(work, index);
            work->field_1188[index]->class = (work->field_1188[index]->class & ~DOG_TARGET_CLASS) | TARGET_AVAIL;
            work->field_14F8[index] = 15;
            work->field_1510[index] = 0;
            work->field_15C8[index] = 1;
        }
        else
        {
            work->field_177C++;
            work->field_1510[index] = 14;
        }
        break;

    case 14:
        if (GM_PlayerPosition.vx < -2800)
        {
            control->mov.vx = 500;
            control->mov.vy = 1200;
            control->mov.vz = -1000;
        }
        else
        {
            control->mov.vx = -5300;
            control->mov.vy = 1200;
            control->mov.vz = 1000;
        }

        work->field_1510[index] = 17;
        work->field_19C[index].m_ctrl = &work->field_45C[index];
        Dog_800CA000(work, index);
        work->field_1188[index]->class |= DOG_TARGET_CLASS;
        break;

    case 17:
        GM_ConfigControlAttribute(control, 5);
        Dog_800CA000(work, index);
        Dog_800CAFB0(work, index);

        if (work->field_15F8 != 1)
        {
            work->field_14F8[index] = 3;
        }
        else
        {
            work->field_14F8[index] = 6;
        }

        work->field_1510[index] = 0;
        s12c_dog_800CA758(work, index);
        work->field_126C[index]->flag = 1;
        break;
    }
}

void s12c_dog_800CFA30(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int      i;

    control = &work->field_28[index];
    hzd = control->map->hzd;

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;

    case 1:
        if ((work->field_155C[index] & 0x3F) == 0 && GV_RandU(16) == 0)
        {
            work->field_14F8[index] = 1;
            work->field_1510[index] = 0;
            break;
        }

        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);

        if (work->field_1604 == 0 && GM_PlayerPosition.vx > -3500 &&
            GM_PlayerPosition.vx < 7000 && GM_PlayerPosition.vz > 2000 &&
            GM_PlayerPosition.vz < 7500)
        {
            work->field_15E8 = GM_PlayerPosition;
        }
        else
        {
            work->field_15E0 = HZD_GetAddress(hzd, &work->field_15E8, work->field_15E0);

            if (work->field_17A4 < 0)
            {
                if (work->field_17A0 == 3 && work->field_1604 == 0)
                {
                    work->field_17A4 = 300;
                }

                if ((GV_Time & 0x7F) == 0 && GV_RandU(0x20) == 0)
                {
                    work->field_15DC = 1 - work->field_15DC;
                    work->field_15E8 = work->field_28[work->field_15DC].mov;
                }

                if (GV_RandU(2) == 0)
                {
                    work->field_15E8 = work->field_28[work->field_15DC].mov;
                    zone = &hzd->def->zones[work->field_15E0 & 0xFF];

                    for (i = 0; i < 6; i++)
                    {
                        if (zone->nears[i] == 0xFF)
                        {
                            break;
                        }
                    }

                    work->field_15E0 = zone->nears[GV_RandU(0x1000) % i];
                }
            }
            else
            {
                work->field_17A4--;
                work->field_15E8.vx = 10555;
                work->field_15E8.vy = 0;
                work->field_15E8.vz = -7000;
            }
        }

        work->field_15E0 = HZD_GetAddress(hzd, &work->field_15E8, work->field_15E0);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_15E0,
                                             &control->mov)];
        target.vx = zone->x;
        target.vy = zone->y;
        target.vz = zone->z;
        Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);

        if (work->field_1604 != 0)
        {
            if ((work->field_155C[index] & 0xF) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xA6, GM_SEMODE_NORMAL);
            }
            else if (work->field_155C[index] % 16 == 8)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xA7, GM_SEMODE_NORMAL);
            }

            if ((GV_Time & 3) == 0 && GV_RandU(8) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xBD, GM_SEMODE_NORMAL);
            }

            Dog_800CB23C(work, 0, 1, index);
            break;
        }
        else
        {
            if (GM_PlayerPosition.vx > -3500 && GM_PlayerPosition.vx < 7000 &&
                GM_PlayerPosition.vz > 2000 && GM_PlayerPosition.vz < 7500)
            {
                work->field_1510[index] = 0x26;
                break;
            }

            if ((GV_Time & 3) == 0 && GV_RandU(8) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xBD, GM_SEMODE_NORMAL);
            }

            if ((work->field_155C[index] & 7) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xBE, GM_SEMODE_NORMAL);
            }

            Dog_800CB23C(work, 0, 1, index);
        }
        break;

    case 5:
        work->field_1510[index] = 6;
        GM_SeSetMode(&work->field_28[index].mov, 0xB7, GM_SEMODE_NORMAL);

    case 6:
        Dog_800CB23C(work, 5, 7, index);
        break;

    case 7:
        work->field_1510[index] = 1;
        GM_SeSetMode(&work->field_28[index].mov, 0xB5, GM_SEMODE_NORMAL);
        break;

    case 38:
        work->field_1510[index] = 0x27;
        work->field_168C = GM_PlayerPosition;

    case 39:
        work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
        work->field_1688 = HZD_GetAddress(hzd, &GM_PlayerPosition, -1);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_1688,
                                             &control->mov)];
        target.vx = zone->x;
        target.vy = zone->y;
        target.vz = zone->z;
        Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);

        if (work->field_151C[index] < 2000)
        {
            work->field_1510[index] = 0x28;
            break;
        }

        Dog_800CB23C(work, 12, 1, index);
        break;

    case 40:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;
        Dog_800CB23C(work, 10, 41, index);
        work->field_1798 = GV_RandU(0x80) + 60;
        break;

    case 41:
        work->field_1510[index] = 0x2A;

    case 42:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;

        if (work->field_151C[index] > 4000 ||
            (work->field_151C[index] < 1000 && work->field_1778 != GM_PlayerPosition.vy))
        {
            work->field_1510[index] = 1;
        }

        s12c_dog_800CB42C(work, 11, 41, 43, index, 4);

        if ((work->field_155C[index] & 0x1F) == 0 && GV_RandU(4) == 0)
        {
            GM_SeSetMode(&work->field_28[index].mov, 0xBC, GM_SEMODE_NORMAL);
        }
        break;

    case 43:
        control->turn = work->field_152C[index];
        control->turn.vx = 0;

        if (work->field_151C[index] > 4000 ||
            (work->field_151C[index] < 1000 && work->field_1778 != GM_PlayerPosition.vy))
        {
            work->field_1510[index] = 1;
        }

        s12c_dog_800CB42C(work, 20, 41, 43, index, 4);
        break;
    }

    if (index == 2 && (work->field_1510[index] > 40 && work->field_1510[index] < 44))
    {
        int timer = work->field_1798;

        work->field_1798 = timer - 1;

        if (timer > 40 && timer < 61)
        {
            work->field_F00[index][4].vz += 8;
            work->field_F00[index][5].vz += 8;
        }

        if (work->field_1798 < 10)
        {
            work->field_F00[index][4].vz -= 16;
            work->field_F00[index][5].vz -= 16;
        }

        if (work->field_1798 < 0)
        {
            work->field_1798 = GV_RandU(0x200) + 256;
            Dog_800CA458(work, 18, index);
        }
    }
}
void s12c_dog_800D0374(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    control = &work->field_28[index];
    hzd = control->map->hzd;

    work->field_14A8[index] = HZD_GetAddress(hzd, &control->mov, work->field_14A8[index]);
    zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index], work->field_1688,
                                         &control->mov)];

    target.vx = zone->x;
    target.vy = zone->y;
    target.vz = zone->z;

    work->field_F00[index][5].vy = work->field_F00[index][5].vy * 7 / 8;
    work->field_1544[index] = 0;

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;

    case 1:
        Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;
        s12c_dog_800CB97C(&control->turn, &rot, 8);

        if (work->field_1604 == 0)
        {
            if ((work->field_155C[index] & 0x1F) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xBE, GM_SEMODE_NORMAL);
            }
        }
        else
        {
            if ((work->field_155C[index] & 0x1F) == 0)
            {
                GM_SeSetMode(&work->field_28[index].mov, 0xBC, GM_SEMODE_NORMAL);
            }
        }

        Dog_800CB23C(work, 0, 1, index);

        if (HZD_ReachTo(hzd, work->field_14A8[index], work->field_1688) <= 0)
        {
            work->field_1510[index] = 5;
            work->field_1550[index] = 150;
        }
        break;

    case 5:
        Dog_800CB23C(work, 0, 1, index);

        if (Dog_800CABF4(&control->mov, &GM_NoisePosition, &control->turn) < 500 ||
            work->field_1550[index] < 0)
        {
            work->field_1510[index] = 14;
        }
        else
        {
            work->field_1550[index]--;
        }
        break;

    case 14:
        if (work->field_1550[index] > 0)
        {
            work->field_1550[index]--;
            Dog_800CABF4(&control->mov, &work->field_168C, &control->turn);
            control->turn.vx = 0;
            Dog_800CB0C8(&work->field_1574[index], 0x80, 16);
            Dog_800CB23C(work, 9, 5, index);
        }
        else
        {
            work->field_15F4 = 0;
            if (work->field_15F8 != 1)
            {
                work->field_14F8[index] = 3;
            }
            else
            {
                work->field_14F8[index] = 6;
            }

            work->field_1510[index] = 0;
        }
        break;
    }
}
void s12c_dog_800D0680(Work *work, int index)
{
    SVECTOR  rot;
    SVECTOR  target;
    CONTROL *control;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    control = &work->field_28[index];
    hzd = control->map->hzd;
    work->field_F00[index][5].vy = work->field_F00[index][5].vy * 7 / 8;
    work->field_1544[index] = 0;

    switch (work->field_1510[index])
    {
    case 0:
        if (index != 2)
        {
            work->field_1282[index] = GV_RandU(0x1000) % work->field_127A[index];
            work->field_127E[index] = work->field_1282[index] + 1;

            if (work->field_127E[index] >= work->field_127A[index])
            {
                work->field_127E[index] = 0;
            }

            work->field_168C = work->field_1286[index][work->field_127E[index]];
            work->field_15A4[index] = HZD_GetAddress(control->map->hzd, &work->field_168C, -1);
            work->field_1510[index] = 1;
        }
        else
        {
            work->field_14F8[index] = 0;
            work->field_1510[index] = 0;
            break;
        }

    case 1:
        if ((GV_Time & 0xF) == 0 && work->field_1604 == 0 && index != 2)
        {
            if (s12c_dog_800CA4B4(work, 5, index) == 1)
            {
                break;
            }

            work->field_1510[index] = 1;
        }

        work->field_14A8[index] =
            HZD_GetAddress(control->map->hzd, &control->mov, work->field_14A8[index]);
        zone = &hzd->def->zones[HZD_Navigate(hzd, work->field_14A8[index],
                                             work->field_15A4[index], &control->mov)];

        if (index == 0 && work->field_1528 < 1000)
        {
            work->field_1510[0] = 5;
            break;
        }

        target.vx = zone->x;
        target.vy = zone->y;
        target.vz = zone->z;
        Dog_800CABF4(&control->mov, &target, &rot);
        rot.vx = 0;

        if (work->field_1604 == 0 && index != 2)
        {
            if (control->mov.vx > -14000 && control->mov.vx < -4000 &&
                control->mov.vz > -2000 && control->mov.vz < 8000)
            {
                if (control->mov.vz < 3000 && target.vz > 2400)
                {
                    work->field_14F8[index] = 10;
                    work->field_1510[index] = 0;
                    break;
                }

                if (control->mov.vz > 2000 && target.vz < 2600)
                {
                    work->field_14F8[index] = 11;
                    work->field_1510[index] = 0;
                    break;
                }
            }

            if (control->mov.vx > 2000 && control->mov.vx < 10000 &&
                control->mov.vz > -2000 && control->mov.vz < 1500)
            {
                if (control->mov.vx < 6500 && target.vx > 5900)
                {
                    work->field_14F8[index] = 12;
                    work->field_1510[index] = 0;
                    break;
                }

                if (control->mov.vx > 5500 && target.vx < 6100)
                {
                    work->field_14F8[index] = 13;
                    work->field_1510[index] = 0;
                    break;
                }
            }
        }

        s12c_dog_800CB97C(&control->turn, &rot, GV_RandU(2) + 1);
        Dog_800CB23C(work, 1, 1, index);

        if (HZD_ReachTo(hzd, work->field_14A8[index], work->field_15A4[index]) <= 0)
        {
            work->field_14F8[index] = 0;
            work->field_1510[index] = 0;
        }

        if (work->field_14D4[index] >= 91)
        {
            work->field_1510[index] = 5;
        }
        break;

    case 5:
        work->field_10B0[index].vx = control->mov.vx;
        work->field_10B0[index].vz = control->mov.vz;
        work->field_1510[index] = 6;
        work->field_1568[index] = GV_RandU(0x20) + 60;

    case 6:
        control->mov.vx = work->field_10B0[index].vx;
        control->mov.vz = work->field_10B0[index].vz;
        work->field_F00[index][5].vy = work->field_F00[index][5].vy * 7 / 8;
        Dog_800CB23C(work, 9, 6, index);

        if (work->field_1604 != 0 || index == 2)
        {
            break;
        }

        work->field_1568[index]--;

        if (work->field_1568[index] < 0)
        {
            work->field_1510[index] = 1;
            work->field_1568[index] = GV_RandU(0x20) + 60;
        }
        else
        {
            s12c_dog_800CA4B4(work, 6, index);
        }
        break;
    }
}

int Dog_800D0BC4(Work *work)
{
    int i;

    if (!(GM_GameStatus & STATE_STUN))
    {
        return 0;
    }

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        if ((work->field_14F8[i] < 8 || work->field_14F8[i] > 9) && work->field_14F8[i] != 12 &&
            work->field_14F8[i] != 13 && work->field_14F8[i] != 10 && work->field_14F8[i] != 11)
        {
            work->field_158C[i] = 200;
            work->field_14F8[i] = 4;
            work->field_1510[i] = 0;
        }
    }
    return 1;
}

void s12c_dog_800D0C78(Work *work, int index)
{
    if (work->field_1510[index] != 5 && work->field_1510[index] != 14 &&
        work->field_158C[index] <= index / 2 * 25 + 60)
    {
        work->field_1510[index] = 5;
        Dog_800CA458(work, 18, index);

        if (work->field_1604 == 0)
        {
            GM_SeSetMode(&work->field_28[index].mov, 0x84, GM_SEMODE_NORMAL);
        }
        else
        {
            GM_SeSetMode(&work->field_28[index].mov, 0x86, GM_SEMODE_NORMAL);
        }
    }

    switch (work->field_1510[index])
    {
    case 0:
        work->field_1510[index] = 1;
        work->field_1544[index] = 0;
        Dog_800CA458(work, 18, index);
        work->field_10B0[index].vx = work->field_28[index].mov.vx;
        work->field_10B0[index].vz = work->field_28[index].mov.vz;
        GM_SeSetMode(&work->field_28[index].mov, 0x8D, GM_SEMODE_NORMAL);

    case 1:
        work->field_1574[index] = 0x80;

        if (work->field_1544[index] < 16)
        {
            work->field_1544[index]++;
        }

        work->field_F00[index][4].vx = work->field_1544[index] * 32;
        work->field_F00[index][5].vx = work->field_1544[index] * 32;
        work->field_28[index].mov.vx = work->field_10B0[index].vx;
        work->field_28[index].mov.vz = work->field_10B0[index].vz;
        Dog_800CB23C(work, 2, 1, index);
        break;

    case 5:
        Dog_800CB23C(work, 16, 14, index);
        break;

    case 14:
        if (work->field_1608)
        {
            /* the loop reuses index: it is dead once the switch has dispatched */
            for (index = 0; index < 3; index++)
            {
                if (work->field_15C8[index] == 0)
                {
                    work->field_14F8[index] = 5;
                    work->field_1510[index] = 0;

                    if (work->field_28[index].mov.vx < 6000 ||
                        work->field_28[index].mov.vz > -1500)
                    {
                        work->field_28[index].mov.vx = index * 500 + 8500;
                        work->field_28[index].mov.vy = 1000;
                        work->field_28[index].mov.vz = index * 500 - 1500;
                    }
                }
            }
        }
        else
        {
            work->field_15F4 = 0;
            work->field_14F8[index] = 3;
            work->field_1510[index] = 0;
        }
        break;
    }
}
void s12c_dog_800D0F30(Work *work, int index)
{
    CONTROL *control;
    OBJECT  *object;
    TARGET  *target;

    if (work->field_1604 != 0)
    {
        return;
    }

    control = &work->field_28[index];
    object = &work->field_19C[index];
    target = work->field_1188[index];

    if (work->field_14F8[index] == 8)
    {
        if (work->field_28[index].n_touches != 0 || work->field_14E0[index] == 1)
        {
            work->field_14E0[index] = 1;
            control->step.vx = 0;
            control->step.vz = 0;
            control->mov.vy = control->height;
        }
    }
    else
    {
        work->field_14E0[index] = 0;
    }

    if (work->field_1510[index] == 0x25)
    {
        control->height = object->height * 3 / 2;
        GM_ActControl(control);
        control->mov.vy = control->height;
    }
    else
    {
        GM_ActControl(control);
        control->height = object->height;

        if (control->r_sphere == -2)
        {
            control->mov.vy = control->height;
            work->field_1488[index] = 0;
        }
        else if (work->field_1488[index] < 0 && control->grounded != 0)
        {
            work->field_1488[index] = 0;
        }

        work->field_1488[index] -= 32;
        control->step.vy = work->field_1488[index];
    }

    GM_ActObject2(object);

    if (GM_Item == IT_ThermG)
    {
        DG_AmbientObjs(object->objs);
    }

    DG_GetLightMatrix2(&control->mov, work->field_10C8[index]);
    GM_MoveTarget(target, &control->mov);
    GM_PushTarget(target);

    if (work->field_14EC[index] == -1)
    {
        if ((work->field_155C[index] & 0x3F) == 0 && work->field_14F8[index] != 9)
        {
            AN_Breath(&object->objs->objs[6].world);
        }
    }
    else
    {
        work->field_14EC[index]++;

        if (work->field_14EC[index] >= 0x1F && (GV_Time & 3) == 0)
        {
            AN_Breath_2(&object->objs->objs[6].world);
        }

        if (work->field_14EC[index] == 0x1E)
        {
            AN_Sleep(&control->mov);
        }
    }

    s12c_dog_800CB714(work, index);
}
void s12c_dog_800D11D4(Work *work, int index)
{
    VECTOR   scale;
    CONTROL *control;
    OBJECT  *object;
    TARGET  *target;

    control = &work->field_28[index];
    target = work->field_1188[index];

    control->step.vx /= 2;
    control->step.vy /= 2;
    control->step.vz /= 2;

    object = &work->field_19C[index];

    if (work->field_14F8[2] != 14)
    {
        if (work->field_1604 == 0 && (control->mov.vx > 3800 && control->mov.vx < 14200) &&
            control->mov.vz > -14200 && control->mov.vz < -9800)
        {
            control->mov.vz = -9800;
        }

        if (work->field_1604 == 0 && control->mov.vx > -12200 && control->mov.vx < -1800 &&
            control->mov.vz > 11800 && control->mov.vz < 16200)
        {
            control->mov.vz = 11800;
        }
    }

    if (work->field_1604 == 0 &&
        ((control->mov.vx > -500 && control->mov.vx < 3500 && control->mov.vz > 0 &&
          control->mov.vz < 3500) ||
         (control->mov.vx > -11000 && control->mov.vx < -7000 && control->mov.vz > 0 &&
          control->mov.vz < 5000) ||
         (control->mov.vx > 3000 && control->mov.vx < 10000 && control->mov.vz > -2500 &&
          control->mov.vz < 3500)) &&
        (work->field_1494[index] == 0x18 || work->field_1494[index] == 0x1C))
    {
        if (object->height > 200)
        {
            control->height = 200;
        }
        else
        {
            control->height = object->height;
        }
    }
    else if (work->field_1494[index] == 5 || work->field_1494[index] == 0)
    {
        control->height = object->height / 3;
    }
    else
    {
        control->height = object->height / 2;
    }

    GM_ActControl(control);

    if (control->r_sphere == -2)
    {
        control->mov.vy = control->height;
        work->field_1488[index] = 0;
    }
    else if (work->field_1488[index] < 0 && control->grounded == 1)
    {
        work->field_1488[index] = 0;
    }

    work->field_1488[index] -= 32;
    control->step.vy = work->field_1488[index];

    GM_ActObject2(object);

    scale.vx = 0x800;
    scale.vy = 0x800;
    scale.vz = 0x800;
    ScaleMatrix(&object->objs->world, &scale);

    if (GM_Item == IT_ThermG)
    {
        DG_AmbientObjs(object->objs);
    }

    DG_GetLightMatrix2(&control->mov, work->field_10C8[index]);
    GM_MoveTarget(target, &control->mov);
    GM_PushTarget(target);

    if (work->field_14EC[index] == -1)
    {
        if (GV_RandU(16) == 0 && work->field_14F8[index] != 9)
        {
            AN_Breath_2(&object->objs->objs[6].world);
        }
    }
    else
    {
        work->field_14EC[index]++;

        if (work->field_14EC[index] >= 0x1F && (GV_Time & 3) == 0)
        {
            AN_Breath_2(&object->objs->objs[6].world);
        }

        if (work->field_14EC[index] == 0x1E)
        {
            AN_Sleep(&control->mov);
        }
    }

    s12c_dog_800CB714(work, index);
}

void Dog_800D1638(Work *work, int obj_index, int blood_count, int index)
{
    MATRIX rot;

    DG_SetPos(&work->field_19C[index].objs->objs[obj_index].world);
    DG_MovePos(&s12c_dword_800C3450);
    DG_RotatePos(&s12c_dword_800C3458);
    ReadRotMatrix(&rot);
    NewBlood(&rot, blood_count);
}


void s12c_dog_800D16C0(Work *work, int index)
{
    TARGET *target;

    target = work->field_1188[index];

    if ((target->damaged & 4) && work->field_1580[index] <= 0 &&
        work->field_14F8[index] != 9 && work->field_14F8[index] != 8)
    {
        work->field_1580[index] = 60;

        if (work->field_14F8[2] == 14 && (s12c_800DA420 & 1))
        {
            s12c_800DA420 = (s12c_800DA420 & ~1) | 2;
        }

        if (index == 2 ||
            (work->field_14F8[index] != 12 && work->field_14F8[index] != 13 &&
             work->field_1510[index] != 0x25))
        {
            if (target->a_mode == 4)
            {
                GM_SeSet(&work->field_28[index].mov, 0x34);
            }
            else if (target->a_mode == 3)
            {
                GM_SeSet(&work->field_28[index].mov, 0x35);
            }

            Dog_800D1638(work, GV_RandU(8), 2, index);
            Dog_800CA458(work, 18, index);

            if (target->vital < 0)
            {
                work->field_14F8[index] = 9;
                work->field_1510[index] = 0;
            }
            else
            {
                int prev = work->field_14F8[index];

                work->field_14F8[index] = 8;
                work->field_1510[index] = 0;
                work->field_1504[index] = prev;
            }
            return;
        }

        /* spelled out twice: cross-jumping merges it back into the tail below,
           but the extra references are what put target in $s0 */
        target->damaged &= ~4;
        return;
    }

    target->damaged &= ~4;
}
void s12c_dog_800D187C(Work *work)
{
    switch (work->field_160C)
    {
    case 1:
        break;

    case 2:
        work->field_175C = work->field_28[2].mov;
        work->field_175C.vy = 2500;
        work->field_1764 = GM_PlayerPosition;
        work->field_176C = GM_Item;
        work->field_1770 = GM_Weapon;
        work->field_160C = 3;

        if (GM_Item == IT_Scope || GM_Item == IT_Camera)
        {
            GM_Item = IT_None;
        }

        if (GM_Weapon == WP_Rifle || GM_Weapon == WP_Stinger)
        {
            GM_Weapon = WP_None;
        }

        if (!(GM_PlayerStatus & PLAYER_INTRUDE) && (GM_Item > IT_Scope && GM_Item < IT_NVG))
        {
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_175C, &work->field_1764, 320);
        }

    case 3:
        work->field_1610 = 1;

        if (work->field_151C[2] < 2500)
        {
            work->field_160C = 4;
        }

        if (!(GM_PlayerStatus & PLAYER_INTRUDE) && (GM_Item > IT_Scope && GM_Item < IT_NVG))
        {
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_175C, &work->field_1764, 320);
        }
        break;

    case 4:
        if (!(GM_PlayerStatus & PLAYER_INTRUDE) && (GM_Item > IT_Scope && GM_Item < IT_NVG))
        {
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_175C, &work->field_1764, 320);
        }

        if (work->field_151C[2] > 2500 || work->field_1610 != 1)
        {
            work->field_160C = 5;
            work->field_1614 = 60;
        }
        break;

    case 5:
        work->field_160C = 6;

        if (work->field_1770 == WP_Rifle || work->field_1770 == WP_Stinger)
        {
            GM_Weapon = work->field_1770;
            work->field_1614 = 0;
        }

        if (work->field_176C == IT_Scope || work->field_176C == IT_Camera)
        {
            GM_Item = work->field_176C;
            work->field_1614 = 0;
        }

    case 6:
        if (--work->field_1614 < 0)
        {
            work->field_160C = 1;
            GM_GameStatus &= ~(STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF);
            s12c_800DA420 &= ~1;
        }
        break;
    }
}
void s12c_dog_800D1B54(Work *work, int index)
{
    switch (work->field_14F8[index])
    {
    case 0:
        work->field_1598[index] = 0;
        if (index == 2)
        {
            s12c_dog_800CFA30(work, index);
        }
        else
        {
            s12c_dog_800CDBC4(work, index);
        }
        break;

    case 1:
        work->field_1598[index] = 0;
        s12c_dog_800CE034(work, index);
        break;

    case 2:
        work->field_1598[index] = 0;
        s12c_dog_800D0374(work, index);
        break;

    case 3:
        work->field_1598[index] = 0;
        work->field_15F8 = 0;
        work->field_15FC = 0;
        s12c_dog_800D0680(work, index);
        break;

    case 4:
        work->field_15F8 = 0;
        work->field_15FC = 0;
        work->field_1598[index] = 0;
        s12c_dog_800D0C78(work, index);
        break;

    case 5:
        work->field_15F8 = 0;
        work->field_15FC = 0;
        s12c_dog_800CE194(work, index);
        break;

    case 14:
        work->field_15F8 = 0;
        work->field_15FC = 0;
        s12c_dog_800CEB74(work, index);
        break;

    case 6:
        work->field_1598[index] = 0;
        if (index == 2)
        {
            s12c_dog_800CFA30(work, index);
        }
        else
        {
            s12c_dog_800CCC3C(work, index);
        }
        break;

    case 8:
        work->field_1598[index] = 0;
        s12c_dog_800CF578(work, index);
        break;

    case 9:
        work->field_1598[index] = 0;
        if (index == 2)
        {
            s12c_dog_800CF578(work, index);
        }
        else
        {
            s12c_dog_800CF6CC(work, index);
        }
        break;

    case 10:
        s12c_dog_800CC53C(work, index);
        break;

    case 11:
        s12c_dog_800CC8B4(work, index);
        break;

    case 12:
        s12c_dog_800CBDC4(work, index);
        break;

    case 13:
        s12c_dog_800CC180(work, index);
        break;
    }
}

// Modified s00a_watcher_800C4138
void Dog_800D1D24(DG_OBJS *objs, DG_DEF *def)
{
    int     i;
    DG_OBJ *obj;
    DG_FreeObjsPacket(objs, 0);
    DG_FreeObjsPacket(objs, 1);

    objs->def = def;
    obj = objs->objs;
    for (i = 0; i < 18; i++)
    {
        obj->model = &def->models[i];
        obj->n_packs = def->models[i].n_faces;
        obj++;
    }
}

void s12c_dog_800D1DA0(Work *work)
{
    SVECTOR diff;
    u_short names[3];
    int     sel;
    int     hit;
    int     count;
    int     flag;
    int     state;
    int     alive;
    int     i;

    if (work->field_17A8 < 100)
    {
        work->field_17A8++;
    }

    GM_CurrentMap = work->field_20;
    s12c_dog_800D187C(work);
    Dog_800CA93C(work);

    if (work->field_1784 == 1)
    {
        sel = 2;
    }
    else
    {
        sel = GV_Time % 3;
    }

    names[0] = GV_StrCode("happy");
    names[1] = GV_StrCode("unhappy");
    names[2] = GV_StrCode("trap");

    switch (Dog_800CA3C0(work->field_24, 3, names))
    {
    case 0:
        work->field_1608 = 1;

        if (work->field_17A8 < 10)
        {
            work->field_160C = 1;

            for (i = 0; i < 3; i++)
            {
                if (work->field_15C8[i] == 0)
                {
                    work->field_14F8[i] = 5;
                    work->field_1510[i] = 0;
                    work->field_28[i].mov.vx = GV_RandS(0x400) + 10000;
                    work->field_28[i].mov.vy = 1000;
                    work->field_28[i].mov.vz = -GV_RandU(0x400);
                }
            }
        }
        break;

    case 1:
        break;

    case 2:
        work->field_1608 = 1;
        work->field_160C = 1;

        for (i = 0; i < 3; i++)
        {
            if (work->field_15C8[i] == 0)
            {
                work->field_14F8[i] = 5;
                work->field_1510[i] = 0;

                if (work->field_28[i].mov.vx < 6000 || work->field_28[i].mov.vz > -1500)
                {
                    work->field_28[i].mov.vx = i * 500 + 8500;
                    work->field_28[i].mov.vy = 1000;
                    work->field_28[i].mov.vz = i * 500 - 1500;
                }
            }
        }
        break;
    }

    if (work->field_1608 == 1 && work->field_160C == 1 && (s12c_800DA420 & 1) != 0)
    {
        flag = 1;

        switch (work->field_14F8[2])
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 7:
            break;

        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            flag = 0;
            break;
        }

        if (flag != 0)
        {
            work->field_160C = 2;
            work->field_1610 = 0;
            work->field_14F8[0] = 14;
            work->field_1510[0] = 0;
            work->field_14F8[1] = 14;
            work->field_1510[1] = 0;
            work->field_14F8[2] = 14;
            work->field_1510[2] = 0;
        }
        else
        {
            s12c_800DA420 = (s12c_800DA420 & ~1) | 2;
        }
    }

    hit = Dog_800D0BC4(work);
    GV_SubVec3(&work->field_28[0].mov, &work->field_28[1].mov, &diff);
    work->field_1528 = GV_VecLen3(&diff);
    count = 0;

    if (work->field_14C4 > 0)
    {
        work->field_14C4--;
    }

    work->field_17A0 = 0;

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        if (work->field_1580[i] > 0)
        {
            work->field_1580[i]--;
        }

        if (work->field_14C8[i] > 0)
        {
            work->field_14C8[i]--;
        }

        state = work->field_14F8[i];
        alive = 0;

        if (work->field_15C8[i] != 0)
        {
            Dog_800C9FAC(work, i);
            work->field_126C[i]->flag = 0;

            if (work->field_1784 == 0 && work->field_1788 == 0)
            {
                if (work->field_1604 != 0)
                {
                    if (work->field_17AC > 0)
                    {
                        work->field_17AC--;
                        work->field_28[i].mov = GM_NoisePosition;
                    }
                    else if (GV_Time % 256 < 128)
                    {
                        work->field_28[i].mov = GM_PlayerPosition;
                    }
                    else if (GV_Time % 4096 < 3072)
                    {
                        work->field_28[i].mov.vx = 11000;
                        work->field_28[i].mov.vy = 0;
                        work->field_28[i].mov.vz = 12000;
                    }
                    else
                    {
                        work->field_28[i].mov.vx = 9000;
                        work->field_28[i].mov.vy = 0;
                        work->field_28[i].mov.vz = -8000;
                    }
                }
                else if (GV_Time % 256 < 128)
                {
                    work->field_28[i].mov = GM_PlayerPosition;
                }
                else
                {
                    work->field_28[i].mov.vx = 9000;
                    work->field_28[i].mov.vy = 0;
                    work->field_28[i].mov.vz = -8000;
                }
            }
            else if (GV_Time % 256 < 128)
            {
                work->field_28[i].mov = GM_PlayerPosition;
            }
            else
            {
                work->field_28[i].mov = work->field_178C;
            }
        }
        else
        {
            s12c_dog_800CB180(work, i);
            Dog_800CB0C8(&work->field_1574[i], 0xFF, 8);

            if (state < 8 || state > 13)
            {
                alive = 1;
                s12c_dog_800CA758(work, i);
            }

            if (work->field_19C[i].objs->bound_mode != 0 || sel == i || alive == 0 ||
                work->field_160C != 0)
            {
                work->field_17A0++;
                work->field_151C[i] = Dog_800CABF4(&work->field_28[i].mov, &GM_PlayerPosition,
                                                   &work->field_152C[i]);

                if (alive != 0)
                {
                    if (work->field_158C[i] > 0)
                    {
                        work->field_158C[i]--;
                    }

                    if (work->field_158C[i] == 1)
                    {
                        work->field_1598[i] = 0;
                    }

                    if (hit == 0 && work->field_1604 == 0)
                    {
                        if (s12c_dog_800CB54C(work, i) == 1)
                        {
                            count++;

                            if (work->field_158C[i] == 0 && work->field_1598[i] == 0 &&
                                state != 6 && work->field_1608 != 1 && work->field_15F8 != 1 &&
                                work->field_160C == 0)
                            {
                                work->field_15F8 = 1;
                                s12c_dog_800CAEC8(work, i, 0);

                                if (i != 2)
                                {
                                    work->field_1740 = 20;
                                    work->field_1744 = i;
                                }

                                if (work->field_14C4 <= 0)
                                {
                                    GM_SeSet(&work->field_28[i].mov, 0x53);
                                    work->field_14C4 = 30;
                                }

                                work->field_14F8[i] = 6;
                                work->field_1510[i] = 0;
                                work->field_1774 = 10;
                            }
                        }
                        else if (state != 6 && work->field_15F8 == 1)
                        {
                            work->field_14F8[i] = 6;
                            work->field_1510[i] = 0;
                        }
                    }
                }

                s12c_dog_800D1B54(work, i);
                s12c_dog_800CAD8C(work, i);

                if ((GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA)) != 0 ||
                    GM_Camera.first_person != 0)
                {
                    if (work->field_448[i] != 1)
                    {
                        work->field_448[i] = 1;
                        Dog_800D1D24(work->field_19C[i].objs, work->field_458);
                    }
                }
                else if (work->field_448[i] != 0)
                {
                    work->field_448[i] = 0;
                    Dog_800D1D24(work->field_19C[i].objs, work->field_454);
                }

                if (i == 2)
                {
                    s12c_dog_800D11D4(work, 2);
                }
                else
                {
                    s12c_dog_800CA098(work, i);
                    s12c_dog_800D0F30(work, i);
                }

                s12c_dog_800D16C0(work, i);
            }
        }

        if (work->field_14B8[i] >= -9)
        {
            work->field_14B8[i]--;
        }
    }

    for (i = 0; i < 3; i++)
    {
        work->field_155C[i]++;

        if (work->field_1494[i] == 1 || work->field_1494[i] == 12)
        {
            Dog_800C9E4C(work, i);
        }
    }

    if (work->field_14F8[0] != 9 && work->field_14F8[1] != 9 && work->field_14F8[2] != 9 &&
        work->field_15F8 == 1 && count <= 0 && !(GM_PlayerStatus & PLAYER_INTRUDE) &&
        --work->field_15FC < 0 && work->field_14F8[0] != 10 && work->field_14F8[1] != 10 &&
        work->field_14F8[0] != 11 && work->field_14F8[1] != 11 && work->field_14F8[0] != 12 &&
        work->field_14F8[1] != 12 && work->field_14F8[0] != 13 && work->field_14F8[1] != 13)
    {
        work->field_15F8 = 0;
        work->field_15FC = 0;
        Dog_800CB6DC(work, 3, 0);
    }

    work->field_1778 = GM_PlayerPosition.vy;
    Dog_800CA058(work);

    if (work->field_1740 > 0)
    {
        if (--work->field_1740 == 0)
        {
            GM_SeSetMode(&work->field_28[work->field_1744].mov, 0x82, GM_SEMODE_NORMAL);
        }
    }
}

void DogDie_800D2798(Work *work)
{
    int i;

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        GM_FreeControl(&work->field_28[i]);
        GM_FreeObject(&work->field_19C[i]);
        GM_FreePrim(work->field_167C[i]);
        GM_FreeTarget(work->field_1188[i]);
        GM_FreeHomingTarget(work->field_126C[i]);
    }
}

// Duplicate of Eventmouse_800C9890
void Dog_800D2864(POLY_FT4 *poly, DG_TEX *tex)
{
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    DG_SetPacketTexture4(poly, tex);
}

int DogGetSvec_800D28C4(char *opt, SVECTOR *out)
{
    char *res;

    res = GCL_NextStr();

    if (res == NULL)
    {
        return 0;
    }

    GCL_StrToSV(res, (short *)out);
    return 1;
}

// Duplicate of UjiGetInts_800C3A3C
int DogGetInts_800D2904(char *opt, int *out)
{
    int   count;
    int  *out2;
    char *result;

    count = 0;
    out2 = out; /* the walked copy is what keeps out in its own register */

    while ((result = GCL_NextStr()) != NULL)
    {
        *out2++ = GCL_StrToInt(result);
        count++;
    }

    return count;
}

int s12c_dog_800D295C(Work *work, int name, int map_name)
{
    int   routes[4];
    MAP  *map;
    char *opt;
    int   fill;
    int   i;
    int   j;

    CONTROL        *control;
    OBJECT         *object;
    DG_PRIM        *prim;
    DG_TEX         *tex;
    HZD_PAT        *pat;
    HZD_PTP        *pt;
    HZD_HDL        *hzd;

    work->field_20 = map_name;
    GM_CurrentMap = map_name;
    work->field_24 = name;
    map = GM_GetMap(work->field_20);

    if ((opt = GCL_GetOption('h')) != NULL)
    {
        work->field_1794 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_1794 = -1;
    }

    if ((opt = GCL_GetOption('o')) != NULL)
    {
        work->field_17B0 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_17B0 = -1;
    }

    if ((opt = GCL_GetOption('b')) != NULL)
    {
        work->field_17B4 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_17B4 = 0;
    }

    if ((opt = GCL_GetOption('s')) != NULL)
    {
        work->field_1604 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_1604 = 0;
    }

    if ((opt = GCL_GetOption('c')) == NULL || (work->field_1784 = GCL_StrToInt(opt)) != 1)
    {
        work->field_1784 = 0;
    }

    if (work->field_1604 != 0 || work->field_1784 != 0)
    {
        work->field_1278 = 2;
    }
    else
    {
        if ((opt = GCL_GetOption('r')) != NULL)
        {
            work->field_1278 = DogGetInts_800D2904(opt, routes);
        }

        if (work->field_1278 >= 3)
        {
            work->field_1278 = 2;
        }
    }

    if ((opt = GCL_GetOption('l')) != NULL)
    {
        work->field_14B4 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_14B4 = 256;
    }

    if ((opt = GCL_GetOption('d')) != NULL)
    {
        work->field_1780 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_1780 = 2;
    }

    if (work->field_1780 < 0 || work->field_1604 == 1 || work->field_1784 != 0)
    {
        work->field_14F8[0] = 15;
        work->field_1510[0] = 0;
        work->field_15C8[0] = 1;
        work->field_28[0].mov = GM_PlayerPosition;
        work->field_14F8[1] = 15;
        work->field_1510[1] = 0;
        work->field_15C8[1] = 1;
        work->field_28[1].mov = GM_PlayerPosition;
    }

    if ((opt = GCL_GetOption('p')) != NULL)
    {
        DogGetSvec_800D28C4(opt, &work->field_178C);
        work->field_1788 = 1;
    }
    else
    {
        work->field_1788 = 0;
    }

    object = NULL;

    for (i = 0; i < work->field_1278 + 1; i++)
    {
        control = &work->field_28[i];

        if (GM_InitControl(control, name, map_name) < 0)
        {
            return -1;
        }

        if (work->field_1784 == 0 || i == 2)
        {
            GM_ConfigControlAttribute(control, 5);
        }
        else
        {
            GM_ConfigControlAttribute(control, 0);
        }

        if (work->field_1604 != 1)
        {
            GM_ConfigControlHazard(control, -1, -2, 1000);
        }
        else if (i == 2)
        {
            GM_ConfigControlHazard(control, -1, -2, 1000);
        }
        else
        {
            GM_ConfigControlHazard(control, -1, -2, -1);
        }

        if (work->field_1604 != 1 && i == 2)
        {
            control->seg_flag = 1;
        }
        else
        {
            control->seg_flag = 2;
        }

        GM_ConfigControlInterp(control, 4);

        if (i != 2)
        {
            if (work->field_1604 != 1 && work->field_1784 == 0)
            {
            if (map->hzd->def->n_routes < routes[i] + 1)
            {
                routes[i] = 0;
            }

            pat = &map->hzd->def->routes[routes[i]];
            work->field_127A[i] = pat->n_points;

            if (work->field_127A[i] <= 0)
            {
                return -1;
            }

            if (work->field_127A[i] >= 32)
            {
                return -1;
            }

            pt = pat->points;

            for (j = 0; j < work->field_127A[i]; j++)
            {
                work->field_1286[i][j].vx = pt->x;
                work->field_1286[i][j].vy = pt->y;
                work->field_1286[i][j].vz = pt->z;
                pt++;
            }

            work->field_1282[i] = GV_RandU(0x1000) % work->field_127A[i];
            work->field_127E[i] = work->field_1282[i] + 1;

            if (work->field_127E[i] >= work->field_127A[i])
            {
                work->field_127E[i] = 0;
            }

            control->mov = work->field_1286[i][work->field_127E[i]];
            }
        }
        else
        {
            work->field_15DC = GV_RandU(2);
            control->mov = work->field_28[work->field_15DC].mov;
        }

        s12c_dog_800CB114(work, i);
        object = &work->field_19C[i];

        switch (work->field_1604)
        {
        case 0:
            GM_InitObject(object, BODY_DATA, BODY_FLAG, MOTION_DATA);
            GM_ConfigObjectJoint(object);
            GM_ConfigMotionControl(object, &work->field_45C[i], MOTION_DATA,
                                   work->field_54C[i], NULL, control, work->field_D50[i]);
            GM_ConfigObjectLight(object, work->field_10C8[i]);
            break;

        case 1:
            GM_InitObject(object, BODY_DATA, BODY_FLAG, MOTION_DATA2);
            GM_ConfigObjectJoint(object);
            GM_ConfigMotionControl(object, &work->field_45C[i], MOTION_DATA2,
                                   work->field_54C[i], NULL, control, work->field_D50[i]);
            GM_ConfigObjectLight(object, work->field_10C8[i]);
            break;
        }

        work->field_1188[i] = GM_AllocTarget();

        if (work->field_1188[i] != NULL)
        {
            Dog_800CAFB0(work, i);
        }

        work->field_126C[i] = GM_AllocHomingTarget(&object->objs->objs[5].world, control);
        work->field_126C[i]->flag = 1;
        prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->field_161C[i], NULL);
        work->field_167C[i] = prim;

        if (prim == NULL)
        {
            return -1;
        }

        prim->raise = 100;
        tex = DG_GetTexture(GV_StrCode("shadow"));

        if (tex == NULL)
        {
            return -1;
        }

        Dog_800D2864(prim->packs[0], tex);
        Dog_800D2864(prim->packs[1], tex);
        s12c_dog_800CB714(work, i);

        if (work->field_1784 == 0)
        {
            work->field_14F8[i] = 0;
            work->field_1510[i] = 0;
            work->field_1598[i] = 0;
            work->field_15C8[i] = 0;
        }
        else if (i == 2)
        {
            work->field_14F8[i] = 0;
            work->field_1510[i] = 0;
        }
        else
        {
            work->field_1188[i]->class = (work->field_1188[i]->class & ~DOG_TARGET_CLASS) | TARGET_AVAIL;
            work->field_126C[i]->flag = 0;
        }

        work->field_1544[i] = GV_RandU(0x1000);
        work->field_1488[i] = 0;
        work->field_14A0[i] = 0;
        work->field_1494[i] = 2;
        work->field_1574[i] = 255;
        work->field_155C[i] = GV_RandU(0x1000);
        work->field_158C[i] = 0;
        work->field_14E0[i] = 0;
        GM_ConfigMotionAdjust(object, work->field_F00[i]);

        if (i == 2)
        {
            hzd = control->map->hzd;
            work->field_15E8 = work->field_28[work->field_15DC].mov;
            work->field_15E0 = HZD_GetAddress(hzd, &work->field_15E8, -1);
            work->field_14A8[2] = HZD_GetAddress(hzd, &control->mov, -1);
        }

        if (work->field_1604 == 0)
        {
            NewWolfEye_800D3930(&work->field_19C[i].objs->objs[5].world, &work->field_15BC[i]);
        }
        else
        {
            GM_GameStatus |= GAME_FLAG_BIT_09;
        }

        work->field_15B0[i] = 0;
        work->field_14B8[i] = 0;
        work->field_14C8[i] = GV_RandU(0x40) + 30;
        work->field_14EC[i] = -1;
        work->field_1580[i] = 0;
        work->field_448[i] = 1;
    }

    work->field_458 = object->objs->def;
    work->field_454 = GV_GetCache(GV_CacheID(GV_StrCode("dog_low"), 'k'));
    work->field_14C4 = 0;
    work->field_15F4 = 0;
    work->field_15F8 = 0;
    work->field_1608 = 0;
    work->field_1748 = 0;
    work->field_1774 = 0;
    work->field_160C = 0;
    work->field_177C = 0;
    work->field_1740 = 0;
    work->field_1744 = 0;
    work->field_17A4 = 0;
    work->field_17A8 = 0;
    work->field_17AC = 0;

    switch (work->field_1604)
    {
    case 0:
        for (i = 29; i >= 0; i--)
        {
            work->field_1698[i] = i;
        }
        break;

    case 1:
        fill = -1;

        for (i = 29; i >= 0; i--)
        {
            work->field_1698[i] = fill;
        }

        work->field_1698[1] = 1;
        work->field_1698[2] = 2;
        work->field_1698[9] = 3;
        work->field_1698[16] = 6;
        work->field_1698[24] = 4;
        work->field_1698[0] = 0;
        work->field_1698[28] = 5;
        break;
    }

    return 0;
}


void *NewDog(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s12c_dog_800D1DA0, DogDie_800D2798, "dog.c");
        if (s12c_dog_800D295C(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return work;
}
