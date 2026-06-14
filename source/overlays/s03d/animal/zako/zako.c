#include "common.h"
#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    OBJECT          field_180;      /* 0x180 */
    char            pad_264[0x728 - 0x264];
    short           field_728;      /* 0x728 */
    char            pad_72A[0x748 - 0x72A];
    short           field_748;      /* 0x748 */
    char            pad_74A[0x750 - 0x74A];
    short           field_750;      /* 0x750 */
    char            pad_752[0x8C8 - 0x752];
    int             field_8C8;      /* 0x8C8 */
    int             field_8CC;      /* 0x8CC */
    char            pad_8D0[0x8DC - 0x8D0];
    int             field_8DC;      /* 0x8DC */
    short           field_8E0;      /* 0x8E0 */
    short           field_8E2;      /* 0x8E2 */
    short           field_8E4;      /* 0x8E4 */
    char            pad_8E6[0x8E8 - 0x8E6];
    int             field_8E8;      /* 0x8E8 */
    int             field_8EC;      /* 0x8EC */
    int             field_8F0;      /* 0x8F0 */
    int             field_8F4;      /* 0x8F4 */
    int             field_8F8;      /* 0x8F8 */
    short          *field_8FC;      /* 0x8FC */
    TARGET          field_900;      /* 0x900 */
    char            pad_948[0x954 - 0x948];
    int             field_954;      /* 0x954 */
    int             field_958;      /* 0x958 */
    int             field_95C;      /* 0x95C */
    int             field_960;      /* 0x960 */
    int             field_964;      /* 0x964 */
    int             field_968;      /* 0x968 */
    int             field_96C;      /* 0x96C */
    short           field_970;      /* 0x970 */
    short           field_972;      /* 0x972 */
    int             field_974;      /* 0x974 */
    int             field_978;      /* 0x978 */
    int             field_97C;      /* 0x97C */
    int             field_980;      /* 0x980 */
    int             field_984;      /* 0x984 */
    int             field_988;      /* 0x988 */
    int             field_98C;      /* 0x98C */
    int             field_990;      /* 0x990 */
    int             field_994;      /* 0x994 */
    short           field_998;      /* 0x998 */
    short           field_99A;      /* 0x99A */
    short           field_99C;      /* 0x99C */
    short           field_99E;      /* 0x99E */
    int             field_9A0;      /* 0x9A0 */
    int             field_9A4;      /* 0x9A4 */
    int             field_9A8;      /* 0x9A8 */
    char            pad_9AC[0xAA8 - 0x9AC];
    int             field_AA8[8];   /* 0xAA8 */
    char            pad_AC8[0xB20 - 0xAC8];
    unsigned short  field_B20;      /* 0xB20 */
    unsigned short  field_B22;      /* 0xB22 */
    unsigned short  field_B24;      /* 0xB24 */
    short           field_B26;      /* 0xB26 */
    char            pad_B28[0xB32 - 0xB28];
    unsigned char   field_B32;      /* 0xB32 */
    unsigned char   field_B33;      /* 0xB33 */
    char            pad_B34[0xC00 - 0xB34];
} Work;

extern int s03d_dword_800DC2F8;
extern int s03d_dword_800C39A0;
extern int s03d_dword_800C39C8;
extern int s03d_dword_800C3A90[];

void s03d_800CC374(Work *work);
int  s03d_800CC4EC(Work *work, int arg);
void s03d_800CC984(Work *work);
int  s03d_800CD61C(Work *work);
int  s03d_800CD75C(Work *work);
int  s03d_800CD984(Work *work);

void Zako_800CCA64(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB9E8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBA60.s")
void Zako_800CBAEC(Work *work)
{
    int v = work->field_96C;

    work->field_728 = v;
    work->field_748 = v;
    if (v < 0)
    {
        work->field_750 = v * 3;
    }
    else
    {
        work->field_750 = v * 3 / 2;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBC10.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC244.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC374.s")
void Zako_800CC430(Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_9A4 = GV_VecDir2(&vec);
    work->field_9A8 = GV_VecLen3(&vec);
}
void Zako_800CC480(Work *work)
{
    Zako_800CC430(work);
    Zako_800CCA64(work);
    s03d_800CC374(work);
}
int Zako_800CC4B4(SVECTOR *from, SVECTOR *to)
{
    SVECTOR vec;

    GV_SubVec3(to, from, &vec);
    vec.vy = 0;
    return GV_VecDir2(&vec);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC4EC.s")
void Zako_800CC5B8(Work *work)
{
    work->field_974 |= 4;
    work->field_968 = work->field_9A4;
    if (s03d_dword_800DC2F8 == 0 || s03d_dword_800DC2F8 == 4)
    {
        work->field_984 = 1;
        work->field_988 = 0;
    }
    else
    {
        work->field_988++;
    }
}
void Zako_800CC60C(Work *work)
{
    if (s03d_dword_800DC2F8 == 2)
    {
        work->field_984 = 0;
        work->field_988 = 0;
    }
    else if (s03d_dword_800DC2F8 == 6)
    {
        s03d_800CC4EC(work, 2);
        work->field_970 = 0x5A;
        work->field_984 = 4;
        work->field_988 = 0;
    }
    else
    {
        if (work->field_990 < 0x12C)
        {
            if (s03d_800CC4EC(work, 0x100))
            {
                work->field_974 |= 1;
            }
            else
            {
                work->field_974 |= 4;
            }
        }
        work->field_988++;
    }
}
void Zako_800CC6C4(Work *work)
{
    if (s03d_dword_800DC2F8 == 0xE)
    {
        work->field_984 = 6;
        work->field_988 = 0;
    }
    else
    {
        if (s03d_800CC4EC(work, 8))
        {
            work->field_974 |= 1;
            if ((work->field_990 & 0x3F) == 0)
            {
                work->field_970 = GV_RandU(8) + 0xE;
                work->field_984 = 3;
                work->field_988 = 0;
                return;
            }
        }
        else
        {
            work->field_974 |= 1;
        }
        work->field_988++;
    }
}
void Zako_800CC768(Work *work)
{
    int flags = work->field_974;

    work->field_974 = flags | 1;
    if (work->field_970 < work->field_988)
    {
        work->field_984 = 2;
        work->field_988 = 0;
    }
    else
    {
        if (work->field_988 % 3 == 0)
        {
            work->field_974 = flags | 3;
        }
        work->field_988++;
    }
}
void Zako_800CC7D4(Work *work)
{
    work->field_974 |= 1;
    if (work->field_970 < work->field_988)
    {
        work->field_984 = 5;
        work->field_988 = 0;
    }
    else
    {
        if (work->field_988 % 10 == 0)
        {
            if (s03d_800CC4EC(work, 8))
            {
                GV_DiffDirAbs(work->field_968, work->field_9A4);
            }
        }
        if (work->field_988 % 3 == 0)
        {
            work->field_974 |= 2;
        }
        work->field_988++;
    }
}
void Zako_800CC8C0(Work *work)
{
    if (work->field_988 < 4)
    {
        work->field_974 |= 8;
    }
    if (s03d_dword_800DC2F8 == 8)
    {
        work->field_984 = 2;
    }
    work->field_988++;
}
void Zako_800CC910(Work *work)
{
    SVECTOR vec;

    GV_SubVec3((SVECTOR *)&s03d_dword_800C39A0, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_978 = GV_VecDir2(&vec);
    if (GV_VecLen3(&vec) < 500)
    {
        work->field_984 = 7;
        work->field_988 = 0;
    }
    else
    {
        work->field_988++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CC984.s")
void Zako_800CCA34(Work *work)
{
    if (work->field_980 == 0)
    {
        s03d_800CC984(work);
    }
}
void Zako_800CCA64(Work *work)
{
    work->field_978 = -1;
    work->field_974 = 0;
    if (work->field_97C == 0)
    {
        Zako_800CCA34(work);
    }
    work->field_98C++;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCAB0.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCCF4.s")
void Zako_800CCDE0(Work *work)
{
    short *p = (short *)&work->field_8C8;

    GV_ZeroMemory(p, 0x20);
    work->field_8C8 = 0;
    p[0x0D] = 0x1C2;
    p[0x0E] = 1;
    work->field_8E8 = 0;
    work->field_8EC = 0;
    work->field_8F0 = 0;
    work->field_8F4 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCE3C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD0C8.s")
int Zako_800CD16C(char *opt, char *out)
{
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != NULL)
    {
        *out++ = GCL_StrToInt(str);
        count++;
    }
    return count;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD1C4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD61C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD6A8.s")
int Zako_800CD720(SVECTOR *vec)
{
    int x = vec->vx;
    int y = vec->vy;
    int z = vec->vz;

    return ABS(x) + ABS(y) + ABS(z);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD75C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD984.s")
int Zako_800CDA04(Work *work)
{
    int a = s03d_800CD61C(work);
    int b = s03d_800CD75C(work);
    int c = s03d_800CD984(work);

    if (a | b | c)
    {
        *work->field_8FC = 1;
        return 1;
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDA70.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDB5C.s")
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDD94.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDE1C.s")
void Zako_800CDF2C(Work *work)
{
    TARGET *t = &work->field_900;

    GM_SetPowerTarget(t, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDF94.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE12C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE2C0.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CF114.s")
int Zako_800D0408(Work *work)
{
    return work->control.mov.vx >= 0x1195;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D041C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0B18.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0B88.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0BEC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0C90.s")
int Zako_800D0EF0(Work *work, int index)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_AA8[i] == 0)
        {
            work->field_AA8[i] = s03d_dword_800C3A90[index];
            return 1;
        }
    }
    return 0;
}
int Zako_800D0F38(Work *work, int value)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_AA8[i] == value)
        {
            work->field_AA8[i] = 0;
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
        if (work->field_AA8[i])
        {
            ((void (*)(Work *))work->field_AA8[i])(work);
        }
    }
}
void Zako_800D0FCC(Work *work)
{
    unsigned short    *src = &work->field_B20;
    RADAR_SIGHT_PARAM *rp = &work->control.radar_param;

    rp->dir = src[0];
    rp->dis = src[2];
    rp->range = src[1];
    rp->r = 0;
}

void Zako_800D0FF4(Work *work)
{
    if (work->field_B33 & 4)
    {
        if (((unsigned short *)work->field_8FC)[3] & 6)
        {
            work->field_B32 |= 4;
        }
        if (work->field_900.damaged & 0x80)
        {
            work->field_B26 = 2;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D1054.s")
void Zako_800D13E8(Work *work)
{
    SVECTOR unused[2];

    (void)unused;
    work->field_B32 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D13F8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D14AC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D153C.s")
