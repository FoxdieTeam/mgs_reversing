#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/blood.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      field_20;
    int      field_24;
    CONTROL  field_28[3];
    OBJECT   field_19C[3];
    char     pad448[0xAB8];
    SVECTOR  field_F00[3][18];   /* 0x90 per dog, the block Dog_800CA458 clears */
    SVECTOR  field_10B0[3];
    MATRIX   field_10C8[3][2];
    TARGET  *field_1188[3];
    TARGET   field_1194[3];
    HOMING  *field_126C[3];
    short    field_1278;
    char     pad127A[0x20E];
    int      field_1488[3];
    int      field_1494[3];
    u_short  field_14A0[3];
    char     pad14A6[0xE];
    int      unk14B4;
    int      field_14B8[3];
    char     pad14C4[0x4];
    int      field_14C8[3];
    int      field_14D4[3];
    int      field_14E0[3];
    int      field_14EC[3];
    int      field_14F8[3];
    int      field_1504[3];
    int      field_1510[3];
    int      field_151C[3];
    int      field_1528;
    char     pad152C[0x152E - 0x152C];
    short    field_152E[11];     /* 8 bytes per dog: read as [index * 4] */
    int      field_1544[3];
    int      field_1550[3];
    int      field_155C[3];
    char     pad1568[0xC];
    int      field_1574[3];
    int      field_1580[3];
    int      field_158C[3];
    int      field_1598[3];
    char     pad15A4[0xC];
    int      field_15B0[3];
    int      field_15BC[3];
    int      field_15C8[3];
    char     pad15D4[0x20];
    int      field_15F4;
    int      field_15F8;
    int      field_15FC;
    int      field_1600;
    int      field_1604;
    int      field_1608;
    int      field_160C;
    int      field_1610;
    char     pad1614[0x8];
    SVECTOR  field_161C[3][4];
    DG_PRIM *field_167C[3];
    char     pad1688[0x10];
    int      field_1698[3];
    char     pad16A4[0xD0];
    int      field_1774;
    char     pad1778[0x38];
    int      field_17B0;
    int      field_17B4;
    char     pad17B8[0x18];
    int      field_17D0[3];
    int      field_17DC[3];
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

SVECTOR s12c_dword_800C3430[2] = {{500, 0, 1000}, {-500, 0, 1000}};
SVECTOR s12c_dword_800C3440[2] = {{250, 0, 500}, {-250, 0, 500}};

SVECTOR s12c_dword_800C3450 = {0, 0, 100};
SVECTOR s12c_dword_800C3458 = {64512, 0, 0};

void *AN_Unknown_800CA1EC(MATRIX *mat, int mark);
void  AN_Breath(MATRIX *world);
void  AN_Breath_2(MATRIX *world);
void  AN_Sleep(SVECTOR *pos);
void *AN_Unknown_800CA320(MATRIX *mat, int mark);

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

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA098.s")

// Duplicate of d03a_red_alrt_800C437C
int Dog_800CA3C0(unsigned short name, int nhashes, unsigned short *hashes)
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
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CA4B4.s")
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
const int  s12c_dword_800D9B4C = 0x800CBE4C;
const int  s12c_dword_800D9B50 = 0x800CBE6C;
const int  s12c_dword_800D9B54 = 0x800CBECC;
const int  s12c_dword_800D9B58 = 0x800CC164;
const int  s12c_dword_800D9B5C = 0x800CC164;
const int  s12c_dword_800D9B60 = 0x800CBF4C;
const int  s12c_dword_800D9B64 = 0x800CC164;
const int  s12c_dword_800D9B68 = 0x800CC164;
const int  s12c_dword_800D9B6C = 0x800CC164;
const int  s12c_dword_800D9B70 = 0x800CC164;
const int  s12c_dword_800D9B74 = 0x800CC164;
const int  s12c_dword_800D9B78 = 0x800CC164;
const int  s12c_dword_800D9B7C = 0x800CC164;
const int  s12c_dword_800D9B80 = 0x800CC164;
const int  s12c_dword_800D9B84 = 0x800CBFA4;
const int  s12c_dword_800D9B88 = 0x800CC164;
const int  s12c_dword_800D9B8C = 0x800CC164;
const int  s12c_dword_800D9B90 = 0x800CC000;
const int  s12c_dword_800D9B94 = 0x800CC164;
const int  s12c_dword_800D9B98 = 0x800CC164;
const int  s12c_dword_800D9B9C = 0x800CC104;
const int  s12c_dword_800D9BA0 = 0x800CC164;
const int  s12c_dword_800D9BA4 = 0x800CC164;
const int  s12c_dword_800D9BA8 = 0x800CC164;
const int  s12c_dword_800D9BAC = 0x800CC164;
const int  s12c_dword_800D9BB0 = 0x800CC164;
const int  s12c_dword_800D9BB4 = 0x800CC164;
const int  s12c_dword_800D9BB8 = 0x800CC120;
const int  s12c_dword_800D9BBC = 0x800CC208;
const int  s12c_dword_800D9BC0 = 0x800CC228;
const int  s12c_dword_800D9BC4 = 0x800CC288;
const int  s12c_dword_800D9BC8 = 0x800CC520;
const int  s12c_dword_800D9BCC = 0x800CC520;
const int  s12c_dword_800D9BD0 = 0x800CC308;
const int  s12c_dword_800D9BD4 = 0x800CC520;
const int  s12c_dword_800D9BD8 = 0x800CC520;
const int  s12c_dword_800D9BDC = 0x800CC520;
const int  s12c_dword_800D9BE0 = 0x800CC520;
const int  s12c_dword_800D9BE4 = 0x800CC520;
const int  s12c_dword_800D9BE8 = 0x800CC520;
const int  s12c_dword_800D9BEC = 0x800CC520;
const int  s12c_dword_800D9BF0 = 0x800CC520;
const int  s12c_dword_800D9BF4 = 0x800CC360;
const int  s12c_dword_800D9BF8 = 0x800CC520;
const int  s12c_dword_800D9BFC = 0x800CC520;
const int  s12c_dword_800D9C00 = 0x800CC3BC;
const int  s12c_dword_800D9C04 = 0x800CC520;
const int  s12c_dword_800D9C08 = 0x800CC520;
const int  s12c_dword_800D9C0C = 0x800CC4C0;
const int  s12c_dword_800D9C10 = 0x800CC520;
const int  s12c_dword_800D9C14 = 0x800CC520;
const int  s12c_dword_800D9C18 = 0x800CC520;
const int  s12c_dword_800D9C1C = 0x800CC520;
const int  s12c_dword_800D9C20 = 0x800CC520;
const int  s12c_dword_800D9C24 = 0x800CC520;
const int  s12c_dword_800D9C28 = 0x800CC4DC;
const int  s12c_dword_800D9C2C = 0x800CC5C4;
const int  s12c_dword_800D9C30 = 0x800CC5E4;
const int  s12c_dword_800D9C34 = 0x800CC898;
const int  s12c_dword_800D9C38 = 0x800CC898;
const int  s12c_dword_800D9C3C = 0x800CC898;
const int  s12c_dword_800D9C40 = 0x800CC748;
const int  s12c_dword_800D9C44 = 0x800CC898;
const int  s12c_dword_800D9C48 = 0x800CC898;
const int  s12c_dword_800D9C4C = 0x800CC898;
const int  s12c_dword_800D9C50 = 0x800CC898;
const int  s12c_dword_800D9C54 = 0x800CC898;
const int  s12c_dword_800D9C58 = 0x800CC898;
const int  s12c_dword_800D9C5C = 0x800CC898;
const int  s12c_dword_800D9C60 = 0x800CC898;
const int  s12c_dword_800D9C64 = 0x800CC7A4;
const int  s12c_dword_800D9C68 = 0x800CC898;
const int  s12c_dword_800D9C6C = 0x800CC898;
const int  s12c_dword_800D9C70 = 0x800CC834;
const int  s12c_dword_800D9C74 = 0x800CC898;
const int  s12c_dword_800D9C78 = 0x800CC898;
const int  s12c_dword_800D9C7C = 0x800CC898;
const int  s12c_dword_800D9C80 = 0x800CC898;
const int  s12c_dword_800D9C84 = 0x800CC898;
const int  s12c_dword_800D9C88 = 0x800CC898;
const int  s12c_dword_800D9C8C = 0x800CC898;
const int  s12c_dword_800D9C90 = 0x800CC898;
const int  s12c_dword_800D9C94 = 0x800CC898;
const int  s12c_dword_800D9C98 = 0x800CC898;
const int  s12c_dword_800D9C9C = 0x800CC898;
const int  s12c_dword_800D9CA0 = 0x800CC898;
const int  s12c_dword_800D9CA4 = 0x800CC898;
const int  s12c_dword_800D9CA8 = 0x800CC898;
const int  s12c_dword_800D9CAC = 0x800CC898;
const int  s12c_dword_800D9CB0 = 0x800CC898;
const int  s12c_dword_800D9CB4 = 0x800CC898;
const int  s12c_dword_800D9CB8 = 0x800CC898;
const int  s12c_dword_800D9CBC = 0x800CC898;
const int  s12c_dword_800D9CC0 = 0x800CC818;
const int  s12c_dword_800D9CC4 = 0x800CC93C;
const int  s12c_dword_800D9CC8 = 0x800CC95C;
const int  s12c_dword_800D9CCC = 0x800CCC20;
const int  s12c_dword_800D9CD0 = 0x800CCC20;
const int  s12c_dword_800D9CD4 = 0x800CCC20;
const int  s12c_dword_800D9CD8 = 0x800CCAAC;
const int  s12c_dword_800D9CDC = 0x800CCC20;
const int  s12c_dword_800D9CE0 = 0x800CCC20;
const int  s12c_dword_800D9CE4 = 0x800CCC20;
const int  s12c_dword_800D9CE8 = 0x800CCC20;
const int  s12c_dword_800D9CEC = 0x800CCC20;
const int  s12c_dword_800D9CF0 = 0x800CCC20;
const int  s12c_dword_800D9CF4 = 0x800CCC20;
const int  s12c_dword_800D9CF8 = 0x800CCC20;
const int  s12c_dword_800D9CFC = 0x800CCB1C;
const int  s12c_dword_800D9D00 = 0x800CCC20;
const int  s12c_dword_800D9D04 = 0x800CCC20;
const int  s12c_dword_800D9D08 = 0x800CCBBC;
const int  s12c_dword_800D9D0C = 0x800CCC20;
const int  s12c_dword_800D9D10 = 0x800CCC20;
const int  s12c_dword_800D9D14 = 0x800CCC20;
const int  s12c_dword_800D9D18 = 0x800CCC20;
const int  s12c_dword_800D9D1C = 0x800CCC20;
const int  s12c_dword_800D9D20 = 0x800CCC20;
const int  s12c_dword_800D9D24 = 0x800CCC20;
const int  s12c_dword_800D9D28 = 0x800CCC20;
const int  s12c_dword_800D9D2C = 0x800CCC20;
const int  s12c_dword_800D9D30 = 0x800CCC20;
const int  s12c_dword_800D9D34 = 0x800CCC20;
const int  s12c_dword_800D9D38 = 0x800CCC20;
const int  s12c_dword_800D9D3C = 0x800CCC20;
const int  s12c_dword_800D9D40 = 0x800CCC20;
const int  s12c_dword_800D9D44 = 0x800CCC20;
const int  s12c_dword_800D9D48 = 0x800CCC20;
const int  s12c_dword_800D9D4C = 0x800CCC20;
const int  s12c_dword_800D9D50 = 0x800CCC20;
const int  s12c_dword_800D9D54 = 0x800CCC20;
const int  s12c_dword_800D9D58 = 0x800CCBA0;
const int  s12c_dword_800D9D5C = 0x800CCCD0;
const int  s12c_dword_800D9D60 = 0x800CCD34;
const int  s12c_dword_800D9D64 = 0x800CCE48;
const int  s12c_dword_800D9D68 = 0x800CDBA0;
const int  s12c_dword_800D9D6C = 0x800CCEF8;
const int  s12c_dword_800D9D70 = 0x800CCF40;
const int  s12c_dword_800D9D74 = 0x800CD258;
const int  s12c_dword_800D9D78 = 0x800CD454;
const int  s12c_dword_800D9D7C = 0x800CDBA0;
const int  s12c_dword_800D9D80 = 0x800CDBA0;
const int  s12c_dword_800D9D84 = 0x800CDBA0;
const int  s12c_dword_800D9D88 = 0x800CD480;
const int  s12c_dword_800D9D8C = 0x800CDBA0;
const int  s12c_dword_800D9D90 = 0x800CD5D0;
const int  s12c_dword_800D9D94 = 0x800CDBA0;
const int  s12c_dword_800D9D98 = 0x800CDBA0;
const int  s12c_dword_800D9D9C = 0x800CDBA0;
const int  s12c_dword_800D9DA0 = 0x800CD68C;
const int  s12c_dword_800D9DA4 = 0x800CDBA0;
const int  s12c_dword_800D9DA8 = 0x800CDBA0;
const int  s12c_dword_800D9DAC = 0x800CD808;
const int  s12c_dword_800D9DB0 = 0x800CDBA0;
const int  s12c_dword_800D9DB4 = 0x800CDBA0;
const int  s12c_dword_800D9DB8 = 0x800CDBA0;
const int  s12c_dword_800D9DBC = 0x800CDBA0;
const int  s12c_dword_800D9DC0 = 0x800CDBA0;
const int  s12c_dword_800D9DC4 = 0x800CDBA0;
const int  s12c_dword_800D9DC8 = 0x800CD8F4;
const int  s12c_dword_800D9DCC = 0x800CDBA0;
const int  s12c_dword_800D9DD0 = 0x800CDBA0;
const int  s12c_dword_800D9DD4 = 0x800CDBA0;
const int  s12c_dword_800D9DD8 = 0x800CDBA0;
const int  s12c_dword_800D9DDC = 0x800CDABC;
const char s12c_dword_800D9DE0[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9DE4 = 0x800CDD10;
const int  s12c_dword_800D9DE8 = 0x800CDD20;
const int  s12c_dword_800D9DEC = 0x800CE008;
const int  s12c_dword_800D9DF0 = 0x800CE008;
const int  s12c_dword_800D9DF4 = 0x800CE008;
const int  s12c_dword_800D9DF8 = 0x800CDDB4;
const int  s12c_dword_800D9DFC = 0x800CE008;
const int  s12c_dword_800D9E00 = 0x800CE008;
const int  s12c_dword_800D9E04 = 0x800CE008;
const int  s12c_dword_800D9E08 = 0x800CE008;
const int  s12c_dword_800D9E0C = 0x800CE008;
const int  s12c_dword_800D9E10 = 0x800CE008;
const int  s12c_dword_800D9E14 = 0x800CE008;
const int  s12c_dword_800D9E18 = 0x800CE008;
const int  s12c_dword_800D9E1C = 0x800CDDE8;
const int  s12c_dword_800D9E20 = 0x800CE008;
const int  s12c_dword_800D9E24 = 0x800CE008;
const int  s12c_dword_800D9E28 = 0x800CDE04;
const int  s12c_dword_800D9E2C = 0x800CE008;
const int  s12c_dword_800D9E30 = 0x800CE008;
const int  s12c_dword_800D9E34 = 0x800CDECC;
const int  s12c_dword_800D9E38 = 0x800CE008;
const int  s12c_dword_800D9E3C = 0x800CE008;
const int  s12c_dword_800D9E40 = 0x800CE008;
const int  s12c_dword_800D9E44 = 0x800CE008;
const int  s12c_dword_800D9E48 = 0x800CE008;
const int  s12c_dword_800D9E4C = 0x800CE008;
const int  s12c_dword_800D9E50 = 0x800CDF1C;
const int  s12c_dword_800D9E54 = 0x800CE008;
const int  s12c_dword_800D9E58 = 0x800CE008;
const int  s12c_dword_800D9E5C = 0x800CE008;
const int  s12c_dword_800D9E60 = 0x800CE008;
const int  s12c_dword_800D9E64 = 0x800CDF50;
const int  s12c_dword_800D9E68 = 0x800CDF70;
const int  s12c_dword_800D9E6C = 0x800CDFAC;
const int  s12c_dword_800D9E70 = 0x800CDFF0;
const int  s12c_dword_800D9E74 = 0x800CE2F8;
const int  s12c_dword_800D9E78 = 0x800CE330;
const int  s12c_dword_800D9E7C = 0x800CEA2C;
const int  s12c_dword_800D9E80 = 0x800CEA2C;
const int  s12c_dword_800D9E84 = 0x800CEA2C;
const int  s12c_dword_800D9E88 = 0x800CE618;
const int  s12c_dword_800D9E8C = 0x800CEA2C;
const int  s12c_dword_800D9E90 = 0x800CEA2C;
const int  s12c_dword_800D9E94 = 0x800CEA2C;
const int  s12c_dword_800D9E98 = 0x800CEA2C;
const int  s12c_dword_800D9E9C = 0x800CEA2C;
const int  s12c_dword_800D9EA0 = 0x800CEA2C;
const int  s12c_dword_800D9EA4 = 0x800CEA2C;
const int  s12c_dword_800D9EA8 = 0x800CEA2C;
const int  s12c_dword_800D9EAC = 0x800CE658;
const int  s12c_dword_800D9EB0 = 0x800CE6E8;
const int  s12c_dword_800D9EB4 = 0x800CEA2C;
const int  s12c_dword_800D9EB8 = 0x800CE7F8;
const int  s12c_dword_800D9EBC = 0x800CEA2C;
const int  s12c_dword_800D9EC0 = 0x800CEA2C;
const int  s12c_dword_800D9EC4 = 0x800CEA2C;
const int  s12c_dword_800D9EC8 = 0x800CEA2C;
const int  s12c_dword_800D9ECC = 0x800CEA2C;
const int  s12c_dword_800D9ED0 = 0x800CEA2C;
const int  s12c_dword_800D9ED4 = 0x800CEA2C;
const int  s12c_dword_800D9ED8 = 0x800CEA2C;
const int  s12c_dword_800D9EDC = 0x800CEA2C;
const int  s12c_dword_800D9EE0 = 0x800CE940;
const int  s12c_dword_800D9EE4 = 0x800CEA2C;
const int  s12c_dword_800D9EE8 = 0x800CEA2C;
const int  s12c_dword_800D9EEC = 0x800CEA2C;
const int  s12c_dword_800D9EF0 = 0x800CEA2C;
const int  s12c_dword_800D9EF4 = 0x800CEA2C;
const int  s12c_dword_800D9EF8 = 0x800CEA2C;
const int  s12c_dword_800D9EFC = 0x800CE950;
const int  s12c_dword_800D9F00 = 0x800CE9F4;
const int  s12c_dword_800D9F04 = 0x800CEA14;
const char s12c_dword_800D9F08[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9F0C = 0x800CECB4;
const int  s12c_dword_800D9F10 = 0x800CED2C;
const int  s12c_dword_800D9F14 = 0x800CF554;
const int  s12c_dword_800D9F18 = 0x800CF554;
const int  s12c_dword_800D9F1C = 0x800CF554;
const int  s12c_dword_800D9F20 = 0x800CF554;
const int  s12c_dword_800D9F24 = 0x800CF06C;
const int  s12c_dword_800D9F28 = 0x800CF0C4;
const int  s12c_dword_800D9F2C = 0x800CF554;
const int  s12c_dword_800D9F30 = 0x800CF2AC;
const int  s12c_dword_800D9F34 = 0x800CF554;
const int  s12c_dword_800D9F38 = 0x800CF554;
const int  s12c_dword_800D9F3C = 0x800CF554;
const int  s12c_dword_800D9F40 = 0x800CF554;
const int  s12c_dword_800D9F44 = 0x800CF4A0;
const char s12c_dword_800D9F48[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800D9F4C = 0x800CF750;
const int  s12c_dword_800D9F50 = 0x800CF7B4;
const int  s12c_dword_800D9F54 = 0x800CFA10;
const int  s12c_dword_800D9F58 = 0x800CFA10;
const int  s12c_dword_800D9F5C = 0x800CFA10;
const int  s12c_dword_800D9F60 = 0x800CF7D0;
const int  s12c_dword_800D9F64 = 0x800CF7FC;
const int  s12c_dword_800D9F68 = 0x800CFA10;
const int  s12c_dword_800D9F6C = 0x800CFA10;
const int  s12c_dword_800D9F70 = 0x800CFA10;
const int  s12c_dword_800D9F74 = 0x800CFA10;
const int  s12c_dword_800D9F78 = 0x800CFA10;
const int  s12c_dword_800D9F7C = 0x800CFA10;
const int  s12c_dword_800D9F80 = 0x800CFA10;
const int  s12c_dword_800D9F84 = 0x800CF8F8;
const int  s12c_dword_800D9F88 = 0x800CFA10;
const int  s12c_dword_800D9F8C = 0x800CFA10;
const int  s12c_dword_800D9F90 = 0x800CF9A0;
const int  s12c_dword_800D9F94 = 0x800CFAA8;
const int  s12c_dword_800D9F98 = 0x800CFAB8;
const int  s12c_dword_800D9F9C = 0x800D0298;
const int  s12c_dword_800D9FA0 = 0x800D0298;
const int  s12c_dword_800D9FA4 = 0x800D0298;
const int  s12c_dword_800D9FA8 = 0x800CFF50;
const int  s12c_dword_800D9FAC = 0x800CFF80;
const int  s12c_dword_800D9FB0 = 0x800CFF90;
const int  s12c_dword_800D9FB4 = 0x800D0298;
const int  s12c_dword_800D9FB8 = 0x800D0298;
const int  s12c_dword_800D9FBC = 0x800D0298;
const int  s12c_dword_800D9FC0 = 0x800D0298;
const int  s12c_dword_800D9FC4 = 0x800D0298;
const int  s12c_dword_800D9FC8 = 0x800D0298;
const int  s12c_dword_800D9FCC = 0x800D0298;
const int  s12c_dword_800D9FD0 = 0x800D0298;
const int  s12c_dword_800D9FD4 = 0x800D0298;
const int  s12c_dword_800D9FD8 = 0x800D0298;
const int  s12c_dword_800D9FDC = 0x800D0298;
const int  s12c_dword_800D9FE0 = 0x800D0298;
const int  s12c_dword_800D9FE4 = 0x800D0298;
const int  s12c_dword_800D9FE8 = 0x800D0298;
const int  s12c_dword_800D9FEC = 0x800D0298;
const int  s12c_dword_800D9FF0 = 0x800D0298;
const int  s12c_dword_800D9FF4 = 0x800D0298;
const int  s12c_dword_800D9FF8 = 0x800D0298;
const int  s12c_dword_800D9FFC = 0x800D0298;
const int  s12c_dword_800DA000 = 0x800D0298;
const int  s12c_dword_800DA004 = 0x800D0298;
const int  s12c_dword_800DA008 = 0x800D0298;
const int  s12c_dword_800DA00C = 0x800D0298;
const int  s12c_dword_800DA010 = 0x800D0298;
const int  s12c_dword_800DA014 = 0x800D0298;
const int  s12c_dword_800DA018 = 0x800D0298;
const int  s12c_dword_800DA01C = 0x800D0298;
const int  s12c_dword_800DA020 = 0x800D0298;
const int  s12c_dword_800DA024 = 0x800D0298;
const int  s12c_dword_800DA028 = 0x800D0298;
const int  s12c_dword_800DA02C = 0x800CFFBC;
const int  s12c_dword_800DA030 = 0x800CFFF4;
const int  s12c_dword_800DA034 = 0x800D00C8;
const int  s12c_dword_800DA038 = 0x800D011C;
const int  s12c_dword_800DA03C = 0x800D012C;
const int  s12c_dword_800DA040 = 0x800D020C;
const int  s12c_dword_800DA044 = 0x800D1B44;
const int  s12c_dword_800DA048 = 0x800D18C0;
const int  s12c_dword_800DA04C = 0x800D19C0;
const int  s12c_dword_800DA050 = 0x800D1A28;
const int  s12c_dword_800DA054 = 0x800D1AA4;
const int  s12c_dword_800DA058 = 0x800D1AFC;

void s12c_dog_800CAD8C(Work *work, int idx)
{
    SVECTOR vec;
    int     half;
    int     state = work->field_1494[idx];
    char   *base = (char *)work + idx * 0x90;

    work->field_17D0[idx] = *(short *)(base + 0xF20);
    work->field_17DC[idx] = *(short *)(base + 0xF28);

    if (state == 0xB || state == 0x14)
    {
        if (work->field_151C[idx] >= 0xFA1)
        {
            *(short *)(base + 0xF20) = 0;
            *(short *)(base + 0xF28) = 0;
        }
        else
        {
            vec.vx = *(short *)((char *)work->field_19C[idx].objs + 0x228);
            vec.vy = *(short *)((char *)work->field_19C[idx].objs + 0x22C);
            vec.vz = *(short *)((char *)work->field_19C[idx].objs + 0x230);
            Dog_800CABF4(&vec, &GM_PlayerPosition, &vec);

            half = vec.vx / 2;
            *(short *)(base + 0xF20) = (half + work->field_17D0[idx] * 15) / 16;
            *(short *)(base + 0xF28) = (half + work->field_17DC[idx] * 15) / 16;
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
    GM_SetTarget(target1, ( 0x1D ), ENEMY_SIDE, &svec1);
    GM_SetPowerTarget(target1, POWER_DECREASE, -1, work->unk14B4, 0xFF, &DG_ZeroVector);

    target2 = &work->field_1194[index];
    GM_SetTarget(target2, TARGET_POWER, ENEMY_SIDE, &svec2);
    GM_SetPowerTarget(target2, POWER_ONCE, 2, 0, 0, &DG_ZeroVector);
}

void Dog_800CB0C8(int *arg0, int arg1, int arg2)
{
    *arg0 = ((*arg0 * (arg2 - 1)) + arg1) / arg2;
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

void Dog_800CB23C(Work *work, int arg1, int field_1510, int index)
{
    if (work->field_1494[index] != arg1)
    {
        s12c_dog_800CAC84(work, index, arg1);
        work->field_1494[index] = arg1;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg1], 0, 4);
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
        work->field_1510[index] = field_1510;
    }
}

void Dog_800CB324(Work *work, int arg1, int arg2, int field_1510, int index)
{
    if (work->field_1494[index] != arg1)
    {
        work->field_1494[index] = arg1;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg1], 0, 4);
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
        work->field_1494[index] = arg2;
        GM_ConfigObjectAction(&work->field_19C[index], work->field_1698[arg2], 0, 4);
        work->field_1510[index] = field_1510;
    }
}

void s12c_dog_800CB42C(Work *work, int index1, int arg2, int arg3, int index2, unsigned int arg5)
{
    int temp_a0;

    temp_a0 = work->field_1494[index2];
    if (temp_a0 != index1)
    {
        s12c_dog_800CAC84(work, index2, index1);
        work->field_1494[index2] = index1;
        GM_ConfigObjectAction(&work->field_19C[index2], work->field_1698[index1], 0, 4);
    }
    else if (work->field_19C[index2].is_end == 1)
    {
        if (temp_a0 != 13)
        {
            work->field_14EC[index2] = -1;
        }
        else
        {
            work->field_14EC[index2] = 0;
        }
        if (GV_RandU(arg5) != 0)
        {
            work->field_1510[index2] = arg2;
        }
        else
        {
            work->field_1510[index2] = arg3;
        }
    }
}

int s12c_dog_800CB54C(Work *work, int index)
{
    CONTROL           *control;
    RADAR_SIGHT_PARAM *radar;

    if (!work->field_1604)
    {
        if (GM_PlayerPosition.vx > -3500)
        {
            if (GM_PlayerPosition.vx < 7000)
            {
                if (GM_PlayerPosition.vz > 2000)
                {
                    if (GM_PlayerPosition.vz < 7500)
                    {
                        return 0;
                    }
                }
            }
        }
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
        if (GV_DiffDirAbs(radar->dir, work->field_152E[index * 4]) > radar->range)
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
    MATRIX   unused;
    CONTROL *control;
    SVECTOR *quad;
    OBJECT  *object;

    unused = DG_ZeroMatrix;
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

    ((POLY_FT4 *)work->field_167C[index]->packs[GV_Clock])->r0 = 0x46;
    ((POLY_FT4 *)work->field_167C[index]->packs[GV_Clock])->g0 = 0x46;
    ((POLY_FT4 *)work->field_167C[index]->packs[GV_Clock])->b0 = 0x46;
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

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CBDC4.s")
extern void s12c_dog_800CBDC4(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC180.s")
extern void s12c_dog_800CC180(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC53C.s")
extern void s12c_dog_800CC53C(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CC8B4.s")
extern void s12c_dog_800CC8B4(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CCC3C.s")
extern void s12c_dog_800CCC3C(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CDBC4.s")
extern void s12c_dog_800CDBC4(Work *work, int index);
/* The two field_10B0 stores go through a byte offset taken before the switch,
   which is what keeps index * 8 in a saved register across the GV_RandU call. */
void s12c_dog_800CE034(Work *work, int index)
{
    CONTROL *control;
    SVECTOR  unused;
    int      off;

    unused.vx = work->field_14A0[index];
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
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CE194.s")
extern void s12c_dog_800CE194(Work *work, int index);

void DogExecProc_800CEB2C(Work *work, int param)
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

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CEB74.s")
extern void s12c_dog_800CEB74(Work *work, int index);
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
            s12c_dog_800CB97C((SVECTOR *)((char *)ctrl + 0x4C), &vec, 8);
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
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CF6CC.s")
extern void s12c_dog_800CF6CC(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800CFA30.s")
extern void s12c_dog_800CFA30(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0374.s")
extern void s12c_dog_800D0374(Work *work, int index);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D0680.s")
extern void s12c_dog_800D0680(Work *work, int index);

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
        object->objs->flag |= 0x100;
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
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D11D4.s")

void Dog_800D1638(Work *work, int obj_index, int blood_count, int index)
{
    MATRIX rot;

    DG_SetPos(&work->field_19C[index].objs->objs[obj_index].world);
    DG_MovePos(&s12c_dword_800C3450);
    DG_RotatePos(&s12c_dword_800C3458);
    ReadRotMatrix(&rot);
    NewBlood(&rot, blood_count);
}

extern int s12c_800DA420;

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
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D187C.s")
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

const char s12c_aHappy_800DA098[] = "happy";
const char s12c_aUnhappy_800DA0A0[] = "unhappy";
const char s12c_aTrap_800DA0A8[] = "trap";
const char s12c_dword_800DA0B0[] = {0x0, 0x0, 0x0, 0x0};
const int  s12c_dword_800DA0B4 = 0x800D203C;
const int  s12c_dword_800DA0B8 = 0x800D203C;
const int  s12c_dword_800DA0BC = 0x800D203C;
const int  s12c_dword_800DA0C0 = 0x800D203C;
const int  s12c_dword_800DA0C4 = 0x800D2038;
const int  s12c_dword_800DA0C8 = 0x800D203C;
const int  s12c_dword_800DA0CC = 0x800D2038;
const int  s12c_dword_800DA0D0 = 0x800D203C;
const int  s12c_dword_800DA0D4 = 0x800D2038;
const int  s12c_dword_800DA0D8 = 0x800D2038;
const int  s12c_dword_800DA0DC = 0x800D2038;
const int  s12c_dword_800DA0E0 = 0x800D2038;
const int  s12c_dword_800DA0E4 = 0x800D2038;
const int  s12c_dword_800DA0E8 = 0x800D2038;
const int  s12c_dword_800DA0EC = 0x800D2038;
const char s12c_aWolfdog_800DA0F0[] = "wolfdog";
const char s12c_aWolfdog_800DA0F8[] = "wolfdog2";
const char s12c_aShadow_800DA104[] = "shadow";
const char s12c_aDoglow_800DA10C[] = "dog_low";

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

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D1DA0.s")
void s12c_dog_800D1DA0(Work *work);
#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D20A0.s")

void DogDie_800D2798(Work *work)
{
    // https://i.kym-cdn.com/photos/images/newsfeed/001/464/596/d38.jpg
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
    out2 = out;

    while ((result = GCL_NextStr()) != NULL)
    {
        *out2++ = GCL_StrToInt(result);
        count++;
    }

    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_dog_800D295C.s")
int s12c_dog_800D295C(Work *work, int, int);

void *NewDog(int arg0, int arg1)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s12c_dog_800D1DA0, DogDie_800D2798, "dog.c");
        if (s12c_dog_800D295C(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
