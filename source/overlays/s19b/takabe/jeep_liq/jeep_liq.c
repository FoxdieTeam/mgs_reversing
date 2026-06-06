#include "common.h"
#include "game/game.h"
#include "linkvar.h"
#include "psxdefs.h"
#include <rand.h>

typedef struct _JeepLiqWork
{
    GV_ACT          actor;        /* 0x000 */
    CONTROL        *control;      /* 0x020 */
    DG_PRIM        *prim;         /* 0x024 */
    MATRIX          world;        /* 0x028 */
    SVECTOR         vecs[11];     /* 0x048 */
    char            pad_obj[0x0A4 - 0x048 - sizeof(SVECTOR[11])];
    OBJECT          obj;          /* 0x0A4 */
    MOTION_CONTROL  m_ctrl;       /* 0x188 */
    /* m_segs1[17] @ 0x1D8 - poked as scalars below by the setters */
    char            pad_seg1[0x1F0 - 0x188 - sizeof(MOTION_CONTROL)];
    int             f1F0;         /* 0x1F0 */
    char            pad_360[0x360 - 0x1F4];
    int             field_360;    /* 0x360 */
    char            pad_3A0[0x3A0 - 0x360 - sizeof(int)];
    int             field_3A0;    /* 0x3A0 */
    int             field_3A4;    /* 0x3A4 */
    int             field_3A8;    /* 0x3A8 */
    char            pad_3B0[0x3B0 - 0x3A8 - sizeof(int)];
    int             field_3B0;    /* 0x3B0 */
    int             field_3B4;    /* 0x3B4 */
    char            pad_3D4[0x3D4 - 0x3B4 - sizeof(int)];
    int             field_3D4;
    int             field_3D8;
    int             field_3DC;
    int             field_3E0;
    int             field_3E4;
    int             field_3E8;
    char            pad_3F8[0x3F8 - 0x3EC];
    int             field_3F8;    /* 0x3F8 */
    char            pad_segs2[0x43C - 0x3F8 - sizeof(int)];
    MOTION_SEGMENT  m_segs2[17];  /* 0x43C */
    SVECTOR         svecs1[16];   /* 0x6A0 */
    SVECTOR         svecs2[16];   /* 0x720 */
    SVECTOR         sv_7A0;       /* 0x7A0 */
    SVECTOR         sv_7A8;       /* 0x7A8 */
    char            pad_7C0[0x7C0 - 0x7A8 - sizeof(SVECTOR)];
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
} JeepLiqWork;

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
    char     pad3c[0x54 - 0x30 - sizeof(int)];
    int      field_54;
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
extern void  s19b_jeep_liq_800D6FB8(JeepLiqWork *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D6FB8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7114.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7200.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7330.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D769C.s")
void s19b_jeep_liq_800D76B0(JeepLiqWork *work)
{
    ((void (*)(void))work->field_3DC)();
    work->field_3A0 = 0;
    ((void (*)(JeepLiqWork *))work->field_3F8)(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(JeepLiqWork *work, int arg1)
{
    if (work->field_3DC != arg1)
    {
        work->field_3DC = arg1;
        work->field_3D8 = 0;
        work->field_3D4 = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D771C.s")
void s19b_jeep_liq_800D77F0(JeepLiqWork *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x753, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7860.s")
void s19b_jeep_liq_800D797C(JeepLiqWork *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D79EC(JeepLiqWork *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, -0x177, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7A5C(JeepLiqWork *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0xbb8, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}
void s19b_jeep_liq_800D7ACC(JeepLiqWork *work)
{
    int v = work->field_360 - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->field_3B0 = s19b_jeep_liq_800D771C(work->field_3B0, 0x1194, v);
    work->field_3A8 = GV_NearSpeed(work->field_3A8, work->field_3B0, 5);
}

void s19b_jeep_liq_800D7B3C(JeepLiqWork *work, int arg1)
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
void s19b_jeep_liq_800D7BB0(JeepLiqWork *work)
{
    if (++work->field_3E0 == 0x1e)
    {
        work->field_3A4 = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->field_3E0 = 0;
    }
    work->field_3A0 = GV_NearSpeed(work->field_3A0, work->field_3A4, 0x1e);
}
void s19b_jeep_liq_800D7C0C(JeepLiqWork *work)
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
void s19b_jeep_liq_800D7CBC(JeepLiqWork *work)
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
void s19b_jeep_liq_800D7D68(JeepLiqWork *work)
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
void s19b_jeep_liq_800D7E2C(JeepLiqWork *work)
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
void s19b_jeep_liq_800D7F20(JeepLiqWork *work)
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
void s19b_jeep_liq_800D8014(JeepLiqWork *work, int arg1)
{
    if (work->field_3F8 != arg1)
    {
        work->field_3F8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
        work->field_3B4 &= ~2;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8044.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8118.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D81A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8250.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8420.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8620.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8670.s")

void s19b_spark2_m_800D8724(JeepLiqWork *work, int arg1, int arg2)
{
    MATRIX  m;
    DG_OBJ *obj = &work->obj.objs->objs[arg1];

    DG_SetPos(&obj->world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AA0);
    DG_RotatePos((SVECTOR *)&s19b_dword_800C3AA8);
    ReadRotMatrix(&m);
    NewJeepBlood(&m, arg2, &obj->world);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D87A4.s")
extern int s19b_spark2_m_800D87A4(JeepLiqWork *work);

int s19b_spark2_m_800D88D8(JeepLiqWork *work)
{
    if (s19b_spark2_m_800D87A4(work) != 0)
    {
        work->f8E4->class = 1;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8918(JeepLiqWork *work)
{
    TARGET *target = work->f8E4;
    int     level  = GM_DifficultyFlag;
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

int s19b_spark2_m_800D899C(JeepLiqWork *work)
{
    int v = work->f900;

    if (v & 0x1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8BC8;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return 1;
    }
    if (v & 0x2)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8CEC;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return 1;
    }
    if (v & 0x4)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8E10;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return 1;
    }
    if (v & 0x10)
    {
        work->f8EC = (void *)s19b_spark2_m_800D90A8;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return 1;
    }
    if (v & 0x04000000)
    {
        work->f8EC = (void *)s19b_spark2_m_800D92C8;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8A48(JeepLiqWork *work)
{
    GV_NearExp4PV(&work->svecs2[2], &work->sv_7A0, 3);
    GV_NearExp4PV(&work->svecs2[6], &work->sv_7A8, 3);
}

void s19b_spark2_m_800D8A88(JeepLiqWork *work)
{
    int v = work->f930 - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AAC(JeepLiqWork *work)
{
    int base = work->f930 + 0xCC0;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8ACC(JeepLiqWork *work)
{
    int base = work->f930 + 0x340;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AEC(JeepLiqWork *work)
{
    MATRIX m;

    DG_SetPos(&work->obj.objs->objs[4].world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AC0);
    ReadRotMatrix(&m);
    NewJeepBullet(&m, 2, 1, 0);
    GM_SeSet((SVECTOR *)&work->world, 0x2E);
    s19b_jblood_800C7FB8(&m);
}

void s19b_spark2_m_800D8B54(JeepLiqWork *work, int mode)
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

extern void s19b_spark2_m_800D8F34(JeepLiqWork *work, int mode);

void s19b_spark2_m_800D8BC8(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8F34;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D8FB0(JeepLiqWork *work, int mode);

void s19b_spark2_m_800D8CEC(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8FB0;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D902C(JeepLiqWork *work, int mode);

void s19b_spark2_m_800D8E10(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D902C;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8F34(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8FB0(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D902C(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D9148(JeepLiqWork *work);

void s19b_spark2_m_800D90A8(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9148.s")

void s19b_spark2_m_800D91DC(JeepLiqWork *work, int mode)
{
    if (mode < 8 && (work->f900 & 0x10))
    {
        work->f8EC = (void *)s19b_spark2_m_800D9148;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
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
    work->vecs[6].vx = 0;
    work->vecs[5].vz = 0;
}

void s19b_spark2_m_800D932C(JeepLiqWork *work, int mode);

void s19b_spark2_m_800D92C8(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
}

void s19b_spark2_m_800D932C(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
}

void s19b_spark2_m_800D9390(JeepLiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 20;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 20, 0, 4);
        GM_SeSet((SVECTOR *)&work->world, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
        work->f940 = 45;
        work->f93C = 0;
    }
}

void s19b_spark2_m_800D9434(JeepLiqWork *work, int mode)
{
    if (s19b_spark2_m_800D899C(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        GM_SeSet((SVECTOR *)&work->world, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (mode < 0x11)
    {
        return;
    }
    work->f8EC = (void *)s19b_spark2_m_800D8B54;
    work->f8F4 = 0;
    work->vecs[6].vx = 0;
    work->vecs[5].vz = 0;
}

void s19b_spark2_m_800D94C8(JeepLiqWork *work, int mode)
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
        work->vecs[6].vx = 0;
        work->vecs[5].vz = 0;
    }
}

void s19b_spark2_m_800D9558(JeepLiqWork *work)
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
    ((void (*)(JeepLiqWork *, int))handler)(work, old);

    s19b_spark2_m_800D8A48(work);

    if (work->f940 != 0)
    {
        work->f8E4->class = 1;
        work->f940 -= 1;
    }
}

void s19b_spark2_m_800D95FC(JeepLiqWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, (SVECTOR *)&work->world, &diff);
    diff.vy = 0;
    work->f930 = GV_VecDir2(&diff);
    work->f934 = GV_VecLen3(&diff);
}

extern void s19b_spark2_m_800D9C04(JeepLiqWork *work);

void s19b_spark2_m_800D964C(JeepLiqWork *work)
{
    s19b_spark2_m_800D95FC(work);
    s19b_spark2_m_800D9C04(work);
    s19b_spark2_m_800D9558(work);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9680.s")
extern int s19b_spark2_m_800D9680(JeepLiqWork *work);

void s19b_spark2_m_800D9704(JeepLiqWork *work)
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

void s19b_spark2_m_800D97A8(JeepLiqWork *work)
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

void s19b_spark2_m_800D985C(JeepLiqWork *work)
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

void s19b_spark2_m_800D9910(JeepLiqWork *work)
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

void s19b_spark2_m_800D99C4(JeepLiqWork *work)
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

void s19b_spark2_m_800D9A30(JeepLiqWork *work)
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

void s19b_spark2_m_800D9A74(JeepLiqWork *work)
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
extern void s19b_spark2_m_800D9AA8(JeepLiqWork *work);

void s19b_spark2_m_800D9B38(JeepLiqWork *work)
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

void s19b_spark2_m_800D9B88(JeepLiqWork *work)
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

void s19b_spark2_m_800D9C04(JeepLiqWork *work)
{
    short *table = (short *)&s19b_dword_800C3AC8;
    int    idx;

    work->f904 = -1;
    work->f900 = 0;
    idx = GM_DifficultyFlag + 1;
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA0B4.s")
