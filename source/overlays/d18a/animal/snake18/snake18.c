#include "common.h"

#include "snake18.h"

int d18a_snake18_800CB710(Snake18Work *work, int a1);

void d18a_snake18_800CABEC(Snake18Work *arg0)
{
    int            i;
    unsigned char *p;
    short         *temp;

    temp = arg0->f8A4;
    arg0->f7E4 &= ~0x4000;
    if ((temp[5] != 0) && (((unsigned short)temp[0] & 0xF000) != 0))
    {
        p = (unsigned char *)temp + 0xC;
        for (i = 0; i < 4; p++)
        {
            i += 1;
            if ((*p - 0x50) >= 0x61U)
            {
                arg0->f7E4 |= 0x4000;
                return;
            }
        }
    }
}

int d18a_snake18_800CAC68(int arg0, int arg1)
{
    int temp_v1;

    if (arg1 < 0)
    {
        return 0;
    }

    temp_v1 = (arg1 - arg0) & 0xFFF;

    if (temp_v1 < 0x800)
    {
        if (temp_v1 < 0x100)
        {
            return 1;
        }

        if (temp_v1 >= 0x501)
        {
            return 3;
        }

        return 4;
    }

    if (temp_v1 >= 0xF01)
    {
        return 1;
    }

    if (temp_v1 < 0xB00)
    {
        return 3;
    }

    return 2;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CACD0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CAD90.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CAEC0.s")
int d18a_snake18_800CAF20(Snake18Work *work)
{
    HZD_VEC  sp10;
    SVECTOR  sp18;
    CONTROL *control;
    int      temp;

    control = &work->control;
    if ((control->levels[1] - control->mov.vy) >= 0x5DC)
    {
        sp18.vy = 0;
        sp18.vx = 0;
        sp18.vz = 0xC8;

        DG_PutVector(&sp18, &sp18, 1);
        sp10.long_access[0] = 0;
        temp = 0x7FFF;
        sp10.long_access[1] = temp;
        HZD_LevelTestHazard(control->map->hzd, &sp18, 3);
        HZD_LevelMinMaxHeights((int *)&sp10);

        if ((sp10.long_access[1] - sp18.vy) >= 0x5DC)
        {
            sp18.vy = 0;
            sp18.vx = 0;
            sp18.vz = -0x3E8;

            DG_PutVector(&sp18, &sp18, 1);
            sp10.long_access[0] = 0;
            sp10.long_access[1] = temp;
            HZD_LevelTestHazard(control->map->hzd, &sp18, 3);
            HZD_LevelMinMaxHeights((int *)&sp10);

            return (sp10.long_access[1] - sp18.vy) < 0x5DC;
        }
    }

    return 1;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB030.s")
extern int d18a_dword_800DAEF0;

int d18a_snake18_800CB134(Snake18Work *work)
{
    int temp_s0;
    int temp_s0_2;
    int temp_s0_3;

    if (work->control.touch_flag < 2)
    {
        return 0;
    }

    temp_s0 = GV_VecDir2(&work->control.nearvecs[0]);
    temp_s0_2 = GV_VecDir2(&work->control.nearvecs[1]);
    temp_s0_3 = GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0);

    if (((GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0_2) + 0x380) < 0x701U))
    {
        if (((temp_s0_3 + 0x380) < 0x701U))
        {
            return 1;
        }
    }

    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB1C8.s")
void d18a_snake18_800CB228(Snake18Work *work, int arg1)
{
    int var_v1;

    var_v1 = GV_DiffDirS(arg1, work->control.rot.vy);

    if (var_v1 >= 0x81)
    {
        var_v1 = 0x80;
    }
    else if (var_v1 < -0x80)
    {
        var_v1 = -0x80;
    }

    work->control.turn.vz = var_v1;
}

int d18a_snake18_800CB280(Snake18Work *work, int arg1)
{
    if (arg1 == 0)
    {
        return work->f8A8->str[0];
    }
    else if (arg1 == 1)
    {
        return work->f8A8->str[2];
    }
    else if (arg1 == 2)
    {
        return work->f8A8->str[3];
    }

    return -1;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB2EC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB34C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB378.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB3E8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB42C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB470.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB514.s")
void d18a_snake18_800CB59C(Snake18Work *work)
{
    short temp_s0;

    if (d18a_dword_800DAEF0 >= 0)
    {
        temp_s0 = work->control.turn.vy;

        if (GV_DiffDirS(temp_s0, d18a_dword_800DAEF0) != 0)
        {
            work->control.turn.vy = GV_NearSpeed(GV_NearPhase(temp_s0, d18a_dword_800DAEF0), d18a_dword_800DAEF0, 0x40);
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB60C.s")
int d18a_snake18_800CB710(Snake18Work *work, int a1)
{
    SVECTOR *vec = (a1 == 1) ? &work->f184 : &work->f19C;
    int      val = (a1 == 1) ? work->body.action : work->body.action2;

    if ((vec->vx + vec->vy) == 1)
    {
        return val;
    }

    return -1;
}

void d18a_snake18_800CB760(Snake18Work *work, int arg1)
{
    if (arg1 != work->f18C)
    {
        work->f1A4 = (int)~arg1;
        work->f18C = arg1;

        if ((arg1 == 0xFFFF) && (d18a_snake18_800CB710(work, 2) >= 0))
        {
            work->f1C0 = 4;
            work->f1B0 = 2;
        }
    }
}
void d18a_snake18_800CB7BC(Snake18Work *work, int arg1)
{
    work->f854 = arg1;
    work->f858 = 0;
    work->f86E = 0;
    work->f86C = 0;
}
extern SVECTOR d18a_dword_800C3850;
extern SVECTOR d18a_dword_800C3858;
extern void NewBlood(MATRIX *mat, int count);

void d18a_snake18_800CB7D0(Snake18Work *work, int arg1)
{
    MATRIX *mat;
    MATRIX  sp10;

    mat = &work->body.objs->objs[arg1].world;

    DG_SetPos(mat);
    DG_MovePos(&d18a_dword_800C3850);
    DG_RotatePos(&d18a_dword_800C3858);
    ReadRotMatrix(&sp10);
    NewBlood(&sp10, 1);
}
void d18a_snake18_800CB838(Snake18Work *work)
{
    if (!(work->f868 & 4) && (GM_PlayerStatus & 0x800) && (work->f86C != 3))
    {
        work->f85C = (int)(work->f85C | 9);
    }
}
extern char d18a_dword_800C3860[];
extern char d18a_dword_800C3864[];

void d18a_snake18_800CB888(Snake18Work *work)
{
    if (work->f90C != 0)
    {
        NewPadVibration(d18a_dword_800C3860, 1);
        work->f90C = (unsigned char)(work->f90C - 1);
    }

    if (work->f90D != 0)
    {
        NewPadVibration(d18a_dword_800C3864, 2);
        work->f90D = (unsigned char)(work->f90D - 1);
        return;
    }

    work->f90E = 0;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CB908.s")
typedef struct _Snake18Arg9CC
{
    char pad0[0x18];
    int  f18;
    int  f1C;
} Snake18Arg9CC;

extern void GM_Target_8002DCB4(TARGET *target, int a_mode, int faint, int *a4, SVECTOR *a5);

int d18a_snake18_800CB9CC(Snake18Work *arg0, Snake18Arg9CC *arg1)
{
    SVECTOR sp18;
    TARGET *temp_s1;
    int     temp_v0;

    temp_s1 = &arg0->f7EC;
    GM_SetTarget(temp_s1, 2, arg0->f930, (SVECTOR *)((char *)arg1 + 0x8));
    GM_Target_8002DCB4(temp_s1, arg1->f18, arg1->f1C, (int *)((char *)arg0 + 0x840), &arg0->f848);
    DG_PutVector((SVECTOR *)arg1, &sp18, 1);
    GM_MoveTarget(temp_s1, &sp18);
    temp_v0 = (int)GM_CaptureTarget(temp_s1);
    arg0->f834 = temp_v0;
    return temp_v0 != 0;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBA64.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBB34.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBBC8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBD34.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBD80.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBE58.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBEC0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CBF98.s")

void d18a_snake18_800CC008(void)
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC010.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC174.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC288.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC3C8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC410.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC490.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC6CC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC7F4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC8B0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC8E0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CC90C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CCB0C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CCB50.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CCF30.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD040.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD2C4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD4C0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD64C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD768.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD808.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD888.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD930.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CD9A8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDB04.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDC3C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDD4C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDE8C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CDFC8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE09C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE210.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE38C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE4E4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE6B0.s")

void d18a_snake18_800CE7BC(void)
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE7C4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE834.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE8E0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CE998.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEA84.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEB78.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEC68.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CECE0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CED2C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEDB0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEE60.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEEAC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEF0C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CEF44.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF03C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF198.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF39C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF574.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF718.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF744.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF850.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CF990.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFB04.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFD18.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFEE8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFF5C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800CFFD4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0054.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D00E0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D01D8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0974.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D09B4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0A10.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0AF8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0B4C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0B84.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0BF4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D0E3C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1064.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D11A8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1300.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1424.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1598.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1750.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1814.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D18EC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D198C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1A08.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1A6C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1ACC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1B3C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1BAC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1CE8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D1F90.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D200C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D20EC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D22C8.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D23F0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D24CC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2660.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D26E4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D281C.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D28CC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2A80.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2D88.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D2FBC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4084.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D40F0.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4388.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D46CC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4784.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D48FC.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D49FC.s")
int d18a_snake18_800D4B84(Snake18Work *work)
{
    d18a_snake18_800CB2EC(work);
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4BA4.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4C44.s")
#pragma INCLUDE_ASM("asm/overlays/d18a/d18a_snake18_800D4E94.s")
