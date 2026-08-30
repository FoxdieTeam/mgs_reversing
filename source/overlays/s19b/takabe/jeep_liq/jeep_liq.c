#include "common.h"
#include "game/game.h"
#include "linkvar.h"
#include "psxdefs.h"
#include <rand.h>

typedef struct _Work
{
    GV_ACT          actor;        /* 0x000 */
    CONTROL        *control;      /* 0x020 */
    DG_PRIM        *prim;         /* 0x024 */
    CONTROL         ctrl;         /* 0x028 */
    OBJECT          obj;          /* 0x0A4 */
    MOTION_CONTROL  m_ctrl;       /* 0x188 */
    /* m_segs1[17] @ 0x1D8 - poked as scalars below by the setters */
    char            pad_seg1[0x1F0 - 0x188 - sizeof(MOTION_CONTROL)];
    int             f1F0;         /* 0x1F0 */
    char            pad_360[0x360 - 0x1F4];
    int             field_360;    /* 0x360 */
    char            pad_364[0x378 - 0x360 - sizeof(int)];
    short           field_378;    /* 0x378 */
    char            pad_37A[0x37C - 0x378 - sizeof(short)];
    short           field_37C;    /* 0x37C */
    char            pad_37E[0x390 - 0x37C - sizeof(short)];
    SVECTOR         field_390;    /* 0x390 */
    char            pad_398[0x3A0 - 0x390 - sizeof(SVECTOR)];
    int             field_3A0;    /* 0x3A0 */
    int             field_3A4;    /* 0x3A4 */
    int             field_3A8;    /* 0x3A8 */
    int             field_3AC;    /* 0x3AC */
    int             field_3B0;    /* 0x3B0 */
    int             field_3B4;    /* 0x3B4 */
    int             field_3B8;    /* 0x3B8 */
    char            pad_3BC[0x3C8 - 0x3B8 - sizeof(int)];
    int             field_3C8;    /* 0x3C8 */
    int             field_3CC;    /* 0x3CC */
    int             field_3D0;    /* 0x3D0 */
    int             field_3D4;
    int             field_3D8;
    int             field_3DC;
    int             field_3E0;
    int             field_3E4;
    int             field_3E8;
    int             field_3EC;    /* 0x3EC */
    int             field_3F0;    /* 0x3F0 */
    char            pad_3F4[0x3F8 - 0x3F0 - sizeof(int)];
    int             field_3F8;    /* 0x3F8 */
    char            pad_segs2[0x43C - 0x3F8 - sizeof(int)];
    MOTION_SEGMENT  m_segs2[17];  /* 0x43C */
    SVECTOR         svecs1[16];   /* 0x6A0 */
    SVECTOR         svecs2[16];   /* 0x720 */
    SVECTOR         sv_7A0;       /* 0x7A0 */
    SVECTOR         sv_7A8;       /* 0x7A8 */
    char            pad_7B0[0x7B8 - 0x7A8 - sizeof(SVECTOR)];
    SVECTOR         sv_7B8;       /* 0x7B8 */
    MATRIX          mtx[2];       /* 0x7C0 */
    OBJECT          obj2;         /* 0x800 */
    TARGET         *f8E4;         /* 0x8E4 */
    HOMING         *homing;       /* 0x8E8 */
    void           *f8EC;         /* 0x8EC */
    char            pad_8F4[0x8F4 - 0x8EC - sizeof(void *)];
    int             f8F4;         /* 0x8F4 */
    char            pad_8FC[0x8FC - 0x8F4 - sizeof(int)];
    int             f8FC;         /* 0x8FC */
    int             f900;         /* 0x900 */
    int             f904;         /* 0x904 */
    char            pad_90C[0x90C - 0x904 - sizeof(int)];
    int             f90C;         /* 0x90C */
    int             f910;         /* 0x910 */
    int             f914;         /* 0x914 */
    int             f918;         /* 0x918 */
    char            pad_920[0x920 - 0x918 - sizeof(int)];
    int             f920;         /* 0x920 */
    char            pad_930[0x930 - 0x920 - sizeof(int)];
    int             f930;         /* 0x930 */
    int             f934;         /* 0x934 */
    char            pad_93C[0x93C - 0x934 - sizeof(int)];
    int             f93C;         /* 0x93C */
    int             f940;         /* 0x940 */
    int            *f944;         /* 0x944 */
} Work;

typedef struct _JEEP_SYSTEM_S
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3a[0x24 - 0x18 - sizeof(SVECTOR)];
    short    field_24;
    char     pad3b[0x30 - 0x24 - sizeof(short)];
    int      field_30;
    char     pad3c[0x40 - 0x30 - sizeof(int)];
    int      field_40;
    int      field_44;
    char     pad3d[0x54 - 0x44 - sizeof(int)];
    int      field_54;
    char     pad5c[0x5C - 0x54 - sizeof(int)];
    int      field_5C;
    char     pad60[0x138 - 0x5C - sizeof(int)];
    SVECTOR  field_138;
} JEEP_SYSTEM_S;

extern JEEP_SYSTEM_S Takabe_JeepSystem;

extern int  s19b_dword_800C3AA0;
extern int  s19b_dword_800C3AA8;
extern int  s19b_dword_800C3AB0;
extern int  s19b_dword_800C3AB8;
extern int  s19b_dword_800C3AC0;
extern int  s19b_dword_800C3AC8;
extern int  s19b_dword_800DE650;

extern void *NewJeepBlood(MATRIX *world, int count, MATRIX *root);
extern void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2);
extern void  s19b_jblood_800C7FB8(MATRIX *world);
extern void  ReadRotMatrix(MATRIX *m);

extern int   s19b_jeep_mrl_800D399C(void);
extern int   s19b_jeep_liq_800D771C(int center, int from, int to);
extern void  s19b_jeep_liq_800D6FB8(Work *work);
extern void  s19b_jeep_liq_800D7114(Work *work);
extern void  s19b_jeep_liq_800D7A5C(Work *work);
extern void  s19b_jeep_liq_800D7860(Work *work);
extern void  s19b_jeep_liq_800D7CBC(Work *work);
extern void  s19b_jeep_liq_800D77F0(Work *work);
extern void  s19b_jeep_liq_800D797C(Work *work);
extern void  s19b_jeep_liq_800D7C0C(Work *work);
extern void  s19b_jeep_liq_800D8014(Work *work, int arg1);
extern void  s19b_jeep_liq_800D8118(Work *work);
extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void  s19b_spark2_m_800D964C(Work *work);
extern void  sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
extern const char s19b_dword_800DDE60[];
extern int   s19b_jeep_gls_800CEDFC(int arg0, int arg1);

void s19b_jeep_liq_800D6FB8(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->field_3A8;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->field_390);
    DG_RotVector(&rot, &rot, 1);
    work->field_378 = rot.vx;
    work->field_37C = rot.vz;
    s19b_jeep_gls_800CEC24(pos->vz - 0x640, &vec);
    GV_SubVec3(&vec, pos, &vec);
    vec.vx += work->field_3A0;
    vec.vx += rsin(work->field_3C8 << 5) * 50 >> 12;
    vec.vx += (rsin(work->field_3C8 << 7) << 1) * work->field_3B8 >> 12;
    work->field_390.vy = GV_VecDir2(&vec);
    work->field_3C8++;
    work->field_3AC = work->field_3A8;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7114.s")
void s19b_jeep_liq_800D7200(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;

    switch (work->field_3CC)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 10)
        {
            work->field_3CC = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D7860(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7CBC(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 12)
        {
            work->field_3CC = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D77F0(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 650, 50);
        if (work->field_3A0 == 650)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7114;
            work->field_3A4 = 650;
            work->field_3CC = 0;
        }
        break;
    }
}
void s19b_jeep_liq_800D7330(Work *work)
{
    SVECTOR *pos = (SVECTOR *)&work->prim;

    switch (work->field_3CC)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 11)
        {
            work->field_3CC = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7C0C(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 13)
        {
            work->field_3CC = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 750, 50);
        if (work->field_3A0 == 750)
        {
            work->field_3D0 = (int)s19b_jeep_liq_800D7114;
            s19b_jeep_liq_800D8014(work, (int)s19b_jeep_liq_800D8118);
            work->field_3CC = 0;
        }
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7468.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D769C.s")
void s19b_jeep_liq_800D76B0(Work *work)
{
    ((void (*)(void))work->field_3DC)();
    work->field_3A0 = 0;
    ((void (*)(Work *))work->field_3F8)(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(Work *work, int arg1)
{
    if (work->field_3DC != arg1)
    {
        work->field_3DC = arg1;
        work->field_3D8 = 0;
        work->field_3D4 = 0;
    }
}

int s19b_jeep_liq_800D771C(int center, int from, int to)
{
    int diff = to - from;
    int base = s19b_jeep_mrl_800D399C();

    if (diff >= 0)
    {
        if (diff > 3000)
        {
            center = GV_NearSpeed(center, base + 100, 15);
        }
        else if (diff > 750)
        {
            center = GV_NearSpeed(center, base + 50, 8);
        }
        else if (diff > 93)
        {
            center = GV_NearSpeed(center, base + 15, 3);
        }
    }
    else
    {
        if (diff < -3000)
        {
            center = GV_NearSpeed(center, base - 100, 15);
        }
        else if (diff < -750)
        {
            center = GV_NearSpeed(center, base - 50, 8);
        }
        else if (diff < -93)
        {
            center = GV_NearSpeed(center, base - 15, 3);
        }
    }
    return center;
}
void s19b_jeep_liq_800D77F0(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x753, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7860(Work *work)
{
    int s1 = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    int a1 = s19b_jeep_mrl_800D399C();

    if (work->field_3D4 == 0)
    {
        if (work->field_3B4 & 8)
        {
            int v1 = work->field_3A8 - 0x32;
            int v0;
            work->field_3A8 = v1;
            v0 = v1 - v1 / 16;
            work->field_3A8 = v0;
            work->field_3B0 = v0;
            work->field_3D4 = 0x3c;
            Takabe_JeepSystem.field_54 |= 2;
        }
        else if (s1 >= 0x5dd)
        {
            work->field_3B0 = GV_NearSpeed(work->field_3B0, a1 + 0x32, 7);
            Takabe_JeepSystem.field_54 |= 0x1000;
        }
    }
    else
    {
        work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0xbb8, s1);
        work->field_3D4--;
    }
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D797C(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D79EC(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, -0x177, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7A5C(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0xbb8, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7ACC(Work *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x1194, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}

void s19b_jeep_liq_800D7B3C(Work *work, int arg1)
{
    if (work->field_3E8 != arg1)
    {
        work->field_3E8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
    }
}

int s19b_jeep_liq_800D7B60(int center, int range)
{
    return (rand() * range >> 15) - range / 2 + center;
}
void s19b_jeep_liq_800D7BB0(Work *work)
{
    if (++work->field_3E0 == 0x1e)
    {
        work->field_3A4 = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->field_3E0 = 0;
    }
    work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
}
void s19b_jeep_liq_800D7C0C(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        work->field_3A4 = 0x546;
        work->field_3A0 = GV_NearSpeed(work->field_3A0, 0x546, 0x32);
        if (work->field_3E0 == 0x28)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0x13;
        }
        break;
    case 1:
        if (n == 0x14)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x4e2, 0xfa);
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7CBC(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        work->field_3A4 = 0x5dc;
        if (work->field_3E0 == 0x28)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0x13;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x32);
        break;
    case 1:
        if (n == 0x14)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x5dc, 0xfa);
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7D68(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0x190);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x32);
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = -0x226;
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 0;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x64);
        break;
    }
}
void s19b_jeep_liq_800D7E2C(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(-0x2ee, 0x96);
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        {
            int r = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x4b);
            work->field_3A0 = r;
            if (r == work->field_3A4)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(-0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D7F20(Work *work)
{
    int n = work->field_3E0 + 1;
    work->field_3E0 = n;

    switch (work->field_3E4)
    {
    case 0:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0x96);
            work->field_3E0 = 0;
        }
        else if (n == 0x3c)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        {
            int r = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x4b);
            work->field_3A0 = r;
            if (r == work->field_3A4)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->field_3A4 = s19b_jeep_liq_800D7B60(0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->field_3E4 = 1;
            work->field_3E0 = 0;
        }
        work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D8014(Work *work, int arg1)
{
    if (work->field_3F8 != arg1)
    {
        work->field_3F8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
        work->field_3B4 &= ~2;
    }
}
extern unsigned char s19b_dword_800C3A9C[];
extern int s19b_jeep_mrl_800D39B4(SVECTOR *dst);

void s19b_jeep_liq_800D8044(Work *work)
{
    SVECTOR sp10;

    s19b_jeep_mrl_800D39B4(&sp10);
    if (Takabe_JeepSystem.field_5C != 0 && work->field_3F0 >= 0x15)
    {
        work->field_3F0 = 0;
        if (work->field_3A0 > 0)
        {
            s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7E2C);
        }
        else
        {
            s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7F20);
        }
        Takabe_JeepSystem.field_54 |= 0x1000;
        GM_SeSet((SVECTOR *)&work->prim, s19b_dword_800C3A9C[GV_RandU(4)]);
    }
    else
    {
        work->field_3F0++;
    }
}
void s19b_jeep_liq_800D8118(Work *work)
{
    SVECTOR dst;
    int     d;

    s19b_jeep_mrl_800D39B4(&dst);
    d = work->ctrl.mov.vx - dst.vz;
    if (d < 0)
    {
        work->field_3EC = 5;
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7D68);
    }
    else
    {
        work->field_3EC = 2;
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, (int)s19b_jeep_liq_800D7F20);
    }
}
extern void s19b_jlamp_800D0A20(int arg0);
extern void s19b_jeep_liq_800D7114(Work *work);

void s19b_jeep_liq_800D81A8(Work *work)
{
    int n = work->field_3F0;
    work->field_3F0 = n + 1;
    if (n == 0)
    {
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF | STATE_PADRELEASE;
        s19b_jlamp_800D0A20(0);
    }
    else if (n >= 0x150)
    {
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_RADAR_OFF | STATE_PADRELEASE);
        s19b_jeep_liq_800D8014(work, (int)s19b_jeep_liq_800D8044);
        s19b_jeep_liq_800D76F8(work, (int)s19b_jeep_liq_800D77F0);
        work->field_3D0 = (int)s19b_jeep_liq_800D7114;
    }
}
void s19b_jeep_liq_800D8250(Work *work)
{
    OBJECT  *body = &work->obj;
    CONTROL *ctl = &work->ctrl;
    DG_OBJS *objs;
    SVECTOR *jpos = &Takabe_JeepSystem.field_138;
    SVECTOR  pos = *(SVECTOR *)&s19b_dword_800DDE60;

    GM_ActMotion(body);
    ctl->rot = ctl->turn = DG_ZeroVector;
    ctl->mov = pos;
    GM_ActControl(ctl);
    GM_ActObject(body);
    objs = body->objs;
    CompMatrix((MATRIX *)work->prim, &objs->world, &objs->world);
    DG_GetLightMatrix(&ctl->mov, &work->mtx[0]);
    ctl->mov.vx = objs->world.t[0];
    ctl->mov.vy = objs->world.t[1];
    ctl->mov.vz = objs->world.t[2];
    jpos->vx = body->objs->objs[6].world.t[0];
    jpos->vy = body->objs->objs[6].world.t[1];
    jpos->vz = body->objs->objs[6].world.t[2];
    GM_MoveTarget(work->f8E4, &ctl->mov);
    s19b_spark2_m_800D964C(work);
    sna_act_helper2_helper2_80033054(0x7BF2, &work->sv_7B8);
    work->svecs2[6].vx = work->sv_7B8.vx;
    if ((work->f940 & 3) == 1)
    {
        body->objs->flag |= 0x80;
    }
    else
    {
        body->objs->flag &= ~0x80;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8420.s")
void s19b_spark2_m_800D8620(Work *work)
{
    GM_FreeTarget(work->f8E4);
    GM_FreeHomingTarget(work->homing);
    GM_FreeObject(&work->obj2);
    GM_FreeControl(&work->ctrl);
    GM_FreeObject(&work->obj);
}
extern void s19b_jeep_liq_800D8250(Work *work);
extern int  s19b_jeep_liq_800D8420(Work *work, int name);
extern const char s19b_aJeepliqc_800DDE80[];
extern const char s19b_dword_800DDE8C[];

void *s19b_spark2_m_800D8670(CONTROL *arg0, DG_PRIM *arg1, int *arg2)
{
    Work *work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_liq_800D8250, s19b_spark2_m_800D8620,
                         s19b_aJeepliqc_800DDE80);
        work->control = arg0;
        work->prim = arg1;
        work->f944 = arg2;
        if (s19b_jeep_liq_800D8420(work, GV_StrCode(s19b_dword_800DDE8C)) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}

void s19b_spark2_m_800D8724(Work *work, int arg1, int arg2)
{
    MATRIX  m;
    DG_OBJ *obj = &work->obj.objs->objs[arg1];

    DG_SetPos(&obj->world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AA0);
    DG_RotatePos((SVECTOR *)&s19b_dword_800C3AA8);
    ReadRotMatrix(&m);
    NewJeepBlood(&m, arg2, &obj->world);
}

extern void s19b_spark2_m_800D9390(Work *work, int mode);
extern void s19b_spark2_m_800D9434(Work *work, int mode);
extern void s19b_spark2_m_800D94C8(Work *work, int mode);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D87A4.s")
extern int s19b_spark2_m_800D87A4(Work *work);

int s19b_spark2_m_800D88D8(Work *work)
{
    if (s19b_spark2_m_800D87A4(work) != 0)
    {
        work->f8E4->class = 1;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8918(Work *work)
{
    TARGET *target = work->f8E4;
    int     level  = GM_GameLevel;
    int     vital;

    if (level > 0)
    {
        vital = (level << 6) + 0xBF;
    }
    else
    {
        vital = 0xBF;
    }

    GM_SetTarget(target, 20, 2, (SVECTOR *)&s19b_dword_800C3AB0);
    GM_SetPowerTarget(target, 1, -1, vital, 7, (SVECTOR *)&s19b_dword_800C3AB8);
}

extern void s19b_spark2_m_800D8BC8();
extern void s19b_spark2_m_800D8CEC();
extern void s19b_spark2_m_800D8E10();
extern void s19b_spark2_m_800D90A8();
extern void s19b_spark2_m_800D92C8();

int s19b_spark2_m_800D899C(Work *work)
{
    int v = work->f900;

    if (v & 0x1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8BC8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x2)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8CEC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x4)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8E10;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x10)
    {
        work->f8EC = (void *)s19b_spark2_m_800D90A8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x04000000)
    {
        work->f8EC = (void *)s19b_spark2_m_800D92C8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8A48(Work *work)
{
    GV_NearExp4PV(&work->svecs2[2], &work->sv_7A0, 3);
    GV_NearExp4PV(&work->svecs2[6], &work->sv_7A8, 3);
}

void s19b_spark2_m_800D8A88(Work *work)
{
    int v = work->f930 - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AAC(Work *work)
{
    int base = work->f930 + 0xCC0;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8ACC(Work *work)
{
    int base = work->f930 + 0x340;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AEC(Work *work)
{
    MATRIX m;

    DG_SetPos(&work->obj.objs->objs[4].world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AC0);
    ReadRotMatrix(&m);
    NewJeepBullet(&m, 2, 1, 0);
    GM_SeSet(&work->ctrl.mov, 0x2E);
    s19b_jblood_800C7FB8(&m);
}

void s19b_spark2_m_800D8B54(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 0;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0, 0, 4);
    }
    if (s19b_spark2_m_800D88D8(work) == 0)
    {
        if (s19b_spark2_m_800D899C(work) == 0)
        {
            work->f8E4->class |= 0x14;
        }
    }
}

extern void s19b_spark2_m_800D8F34(Work *work, int mode);

void s19b_spark2_m_800D8BC8(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 1;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 1, 0, 4);
    }
    s19b_spark2_m_800D8A88(work);

    if (!(f900 & 1))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8F34;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D8FB0(Work *work, int mode);

void s19b_spark2_m_800D8CEC(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 3;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 3, 0, 4);
    }
    s19b_spark2_m_800D8AAC(work);

    if (!(f900 & 2))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8FB0;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D902C(Work *work, int mode);

void s19b_spark2_m_800D8E10(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 2;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 2, 0, 4);
    }
    s19b_spark2_m_800D8ACC(work);

    if (!(f900 & 4))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D902C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8F34(Work *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8BC8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8FB0(Work *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8CEC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D902C(Work *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8E10;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D9148(Work *work, int mode);
extern void s19b_spark2_m_800D91DC(Work *work, int mode);

void s19b_spark2_m_800D90A8(Work *work, int mode)
{
    if (mode < 8)
    {
        work->f8E4->class |= 0x14;
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->f8FC = 0x10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D9148;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9148(Work *work, int mode)
{
    int f900 = work->f900;

    if (!(f900 & 0x10))
    {
        work->f8EC = (void *)s19b_spark2_m_800D91DC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }
    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (mode == 0)
    {
        work->f8FC = 0x11;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x11, 0, 4);
    }
    if (mode >= 0x5B)
    {
        work->f8EC = (void *)s19b_spark2_m_800D91DC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D91DC(Work *work, int mode)
{
    if (mode < 8 && (work->f900 & 0x10))
    {
        work->f8EC = (void *)s19b_spark2_m_800D9148;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (mode >= 8)
    {
        work->f8E4->class |= 0x14;
    }

    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }

    if (work->f93C != 0 && mode >= 0xB)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->f93C = 0;
    }

    if (mode == 0)
    {
        work->f8FC = 0x12;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x12, 0, 4);
    }

    if (work->obj.is_end == 0)
    {
        return;
    }

    work->f8EC = (void *)s19b_spark2_m_800D8B54;
    work->f8F4 = 0;
    work->ctrl.turn.vz = 0;
    work->ctrl.turn.vx = 0;
}

void s19b_spark2_m_800D932C(Work *work, int mode);

void s19b_spark2_m_800D92C8(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D932C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D932C(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D932C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9390(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 20;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 20, 0, 4);
        GM_SeSet(&work->ctrl.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->f940 = 45;
        work->f93C = 0;
    }
}

void s19b_spark2_m_800D9434(Work *work, int mode)
{
    if (s19b_spark2_m_800D899C(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        GM_SeSet(&work->ctrl.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (mode < 0x11)
    {
        return;
    }
    work->f8EC = (void *)s19b_spark2_m_800D8B54;
    work->f8F4 = 0;
    work->ctrl.turn.vz = 0;
    work->ctrl.turn.vx = 0;
}

void s19b_spark2_m_800D94C8(Work *work, int mode)
{
    work->f8E4->class |= 0x14;
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->f8FC = 0x13;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x13, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9558(Work *work)
{
    int   old;
    void *handler;

    work->f8E4->class = 1;
    old     = work->f8F4;
    handler = work->f8EC;
    work->f8F4 = old + 1;

    if (handler == NULL)
    {
        s19b_spark2_m_800D8918(work);
        handler       = (void *)s19b_spark2_m_800D8B54;
        work->f8EC    = handler;
    }
    ((void (*)(Work *, int))handler)(work, old);

    s19b_spark2_m_800D8A48(work);

    if (work->f940 != 0)
    {
        work->f8E4->class = 1;
        work->f940 -= 1;
    }
}

void s19b_spark2_m_800D95FC(Work *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->ctrl.mov, &diff);
    diff.vy = 0;
    work->f930 = GV_VecDir2(&diff);
    work->f934 = GV_VecLen3(&diff);
}

extern void s19b_spark2_m_800D9C04(Work *work);

void s19b_spark2_m_800D964C(Work *work)
{
    s19b_spark2_m_800D95FC(work);
    s19b_spark2_m_800D9C04(work);
    s19b_spark2_m_800D9558(work);
}

int s19b_spark2_m_800D9680(Work *work)
{
    int js = Takabe_JeepSystem.field_54;

    if (js & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
        return 1;
    }
    if (js & 0x2)
    {
        work->f900 |= 0x02000000;
    }
    else if (js & 0x8000)
    {
        work->f900 = 0x04000000;
        return 1;
    }
    else if (work->f8FC == 0x14)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D9704(Work *work)
{
    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f934 < 0xFA0 || work->f93C != 0)
    {
        int f930 = work->f930;
        int new_f914;

        if ((unsigned)(f930 - 0x601) < 0x3FF)
        {
            new_f914 = 1;
        }
        else if ((unsigned)(f930 - 0x201) < 0x3FF)
        {
            new_f914 = 3;
        }
        else if ((unsigned)(f930 - 0xA01) < 0x3FF)
        {
            new_f914 = 2;
        }
        else
        {
            work->f918 += 1;
            return;
        }

        work->f914 = new_f914;
        work->f918 = 0;
        return;
    }

    work->f918 += 1;
}

void s19b_spark2_m_800D97A8(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 1)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->f900 |= 8;
    }
    work->f900 |= 1;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D985C(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 3)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->f900 |= 8;
    }
    work->f900 |= 2;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D9910(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 2)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->f900 |= 8;
    }
    work->f900 |= 4;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D99C4(Work *work)
{
    int js = Takabe_JeepSystem.field_54;
    work->f900 |= 0x10;
    if (work->f918 >= 61 || (js & 0x2000))
    {
        work->f93C = 1;
        work->f914 = 0;
    }
    if (js & 0x2)
    {
        work->f914 = 1;
        work->f900 |= 0x02000000;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9A30(Work *work)
{
    if (Takabe_JeepSystem.field_54 & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
    }
    else
    {
        work->f918 += 1;
    }
}

void s19b_spark2_m_800D9A74(Work *work)
{
    int new_f900 = work->f900 | 0x10;
    int js = Takabe_JeepSystem.field_54;
    work->f900 = new_f900;
    if (js & 0x2000)
    {
        work->f914 = 0;
    }
    work->f918 += 1;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9AA8.s")
extern void s19b_spark2_m_800D9AA8(Work *work);

void s19b_spark2_m_800D9B38(Work *work)
{
    switch (work->f914)
    {
    case 0:
        s19b_spark2_m_800D9A30(work);
        break;
    case 4:
        s19b_spark2_m_800D9A74(work);
        break;
    }
}

void s19b_spark2_m_800D9B88(Work *work)
{
    switch (work->f910)
    {
    case 0: s19b_spark2_m_800D9AA8(work); break;
    case 1: s19b_spark2_m_800D9B38(work); break;
    }

    if (Takabe_JeepSystem.field_54 & 0x10000000)
    {
        work->f910 = 1;
    }
    else
    {
        work->f910 = 0;
    }
}

void s19b_spark2_m_800D9C04(Work *work)
{
    short *table = (short *)&s19b_dword_800C3AC8;
    int    idx;

    work->f904 = -1;
    work->f900 = 0;
    idx = GM_GameLevel + 1;
    s19b_dword_800DE650 = table[idx];

    if (work->f90C == 0)
    {
        s19b_spark2_m_800D9B88(work);
    }

    Takabe_JeepSystem.field_54 &= 0xFFFF0000;
    work->f920 += 1;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9C90.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9EC0.s")
void s19b_spark2_m_800DA0B4(POLY_FT4 *poly, int arg1, SVECTOR *from, SVECTOR *to)
{
    int d = (arg1 << 12) / 1178;
    int dy;
    int step;

    poly->x0 += d;
    poly->x1 += d;
    poly->x2 += d;
    poly->x3 += d;

    dy = from->vy - to->vy;
    if (arg1 < 0)
    {
        dy = -dy;
    }
    step = dy * 4;
    poly->y2 = GV_NearExp4P(poly->y2, step);
    poly->y3 = GV_NearExp4P(poly->y3, step);
    *to = *from;
}
