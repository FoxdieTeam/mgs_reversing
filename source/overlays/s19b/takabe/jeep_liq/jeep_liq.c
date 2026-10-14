#include <rand.h>

#include "psxdefs.h"
#include "mgstype.h"
#include "game/game.h"

typedef struct _JeepWork JeepWork;

typedef void (*JeepFn)();
typedef void (*LiqFn)();

/* The jeep the Liquid chases/drives: same actor as jeep2.c (s19b_jeep2_800D6B18 builds it). The functions
   here are its movement state machines; the Liquid actor itself is LiqWork below. */
struct _JeepWork
{
    GV_ACT          actor;        /* 0x000 */
    void           *liq_actor;    /* 0x020 */
    CONTROL         control;      /* 0x024 */
    TARGET         *target;       /* 0x0A0 */
    OBJECT          jeep_b;       /* 0x0A4 */
    OBJECT          jeep_t;       /* 0x188 */
    OBJECT_NO_ROTS  gun;          /* 0x26C */
    MATRIX          light[2];     /* 0x290 */
    OBJECT_NO_ROTS  fhl;          /* 0x2D0 */
    OBJECT_NO_ROTS  hl;           /* 0x2F4 */
    char            pad_318[0x358 - 0x318];
    int             road[4];      /* 0x358 */
    int             road2[4];     /* 0x368 */
    SVECTOR         sv_378;       /* 0x378 */
    SVECTOR         sv_380;       /* 0x380 */
    SVECTOR         sv_388;       /* 0x388 */
    SVECTOR         rot;          /* 0x390 */
    char            pad_398[0x3A0 - 0x398];
    int             side;         /* 0x3A0 */
    int             side_target;  /* 0x3A4 */
    int             speed;        /* 0x3A8 */
    int             speed_prev;   /* 0x3AC */
    int             speed_target; /* 0x3B0 */
    int             flags;        /* 0x3B4 */
    int             wobble;       /* 0x3B8 */
    char            pad_3BC[0x3C0 - 0x3BC];
    int             f3C0;         /* 0x3C0 */
    int             liq_flags;    /* 0x3C4 */
    int             frame;        /* 0x3C8 */
    int             phase;        /* 0x3CC */
    JeepFn          act_fn;       /* 0x3D0 */
    int             speed_timer;  /* 0x3D4 */
    int             speed_fn_time;/* 0x3D8 */
    JeepFn          speed_fn;     /* 0x3DC */
    int             side_count;   /* 0x3E0 */
    int             side_step;    /* 0x3E4 */
    JeepFn          side_fn;      /* 0x3E8 */
    int             mode;         /* 0x3EC */
    int             shoot_count;  /* 0x3F0 */
    int             f3F4;         /* 0x3F4 */
    JeepFn          mode_fn;      /* 0x3F8 */
};

/* The Liquid actor riding the jeep (named "jeep_liq.c"). */
typedef struct _LiqWork
{
    GV_ACT          actor;        /* 0x000 */
    CONTROL        *jeep_control; /* 0x020 */
    DG_OBJS        *jeep_objs;    /* 0x024 */
    CONTROL         control;      /* 0x028 */
    OBJECT          obj;          /* 0x0A4 */
    MOTION_CONTROL  m_ctrl;       /* 0x188 */
    MOTION_SEGMENT  m_segs1[17];  /* 0x1D8 */
    MOTION_SEGMENT  m_segs2[17];  /* 0x43C */
    SVECTOR         rots[16];     /* 0x6A0 */
    SVECTOR         adjust[16];   /* 0x720 */
    SVECTOR         sv_7A0;       /* 0x7A0 */
    SVECTOR         sv_7A8;       /* 0x7A8 */
    SVECTOR         sv_7B0;       /* 0x7B0 */
    SVECTOR         sv_7B8;       /* 0x7B8 */
    MATRIX          light[2];     /* 0x7C0 */
    OBJECT          obj2;         /* 0x800 */
    TARGET         *target;       /* 0x8E4 */
    HOMING         *homing;       /* 0x8E8 */
    LiqFn           state;       /* 0x8EC */
    int             f8F0;         /* 0x8F0 */
    int             state_time;   /* 0x8F4 */
    int             f8F8;         /* 0x8F8 */
    int             action;       /* 0x8FC */
    int             cmd;          /* 0x900 */
    int             cmd_dir;      /* 0x904 */
    int             f908;         /* 0x908 */
    int             f90C;         /* 0x90C */
    int             f910;         /* 0x910 */
    int             f914;         /* 0x914 */
    int             f918;         /* 0x918 */
    int             f91C;         /* 0x91C */
    int             f920;         /* 0x920 */
    int             f924;         /* 0x924 */
    int             f928;         /* 0x928 */
    int             f92C;         /* 0x92C */
    int             player_dir;   /* 0x930 */
    int             player_dist;  /* 0x934 */
    int             f938;         /* 0x938 */
    int             f93C;         /* 0x93C */
    int             f940;         /* 0x940 */
    int            *jeep_flags;   /* 0x944 */
} LiqWork;

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
    char     pad3d[0x54 - 0x40 - sizeof(int)];
    int      field_54;
    char     pad5c[0x5C - 0x54 - sizeof(int)];
    int      field_5C;
    char     pad60[0x68 - 0x5C - sizeof(int)];
    OBJECT  *liq_obj;
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
extern void  s19b_jeep_gls_800CEC24(int z, SVECTOR *out);
extern int   s19b_jeep_gls_800CEDFC(int z, int arg1);
extern void  s19b_jlamp_800D0A20(int arg0);

extern int   s19b_jeep_liq_800D771C(int cur, int center, int pos);
extern void  s19b_jeep_liq_800D76F8(JeepWork *work, JeepFn fn);
extern void  s19b_jeep_liq_800D7B3C(JeepWork *work, JeepFn fn);
extern void  s19b_jeep_liq_800D8014(JeepWork *work, JeepFn fn);
extern void  s19b_jeep_liq_800D77F0(JeepWork *work);
extern void  s19b_jeep_liq_800D7860(JeepWork *work);
extern void  s19b_jeep_liq_800D797C(JeepWork *work);
extern void  s19b_jeep_liq_800D7A5C(JeepWork *work);
extern void  s19b_jeep_liq_800D7BB0(JeepWork *work);
extern void  s19b_jeep_liq_800D7C0C(JeepWork *work);
extern void  s19b_jeep_liq_800D7CBC(JeepWork *work);
extern void  s19b_jeep_liq_800D8044(JeepWork *work);
extern void  s19b_jeep_liq_800D8118(JeepWork *work);
extern void  s19b_jeep_liq_800D7114(JeepWork *work);
extern void  s19b_jeep_liq_800D7200(JeepWork *work);
extern void  s19b_jeep_liq_800D7330(JeepWork *work);
extern void  s19b_jeep_liq_800D7468(JeepWork *work);

void s19b_jeep_liq_800D6FB8(JeepWork *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->speed;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->rot);
    DG_RotVector(&rot, &rot, 1);
    work->sv_378.vx = rot.vx;
    work->sv_378.vz = rot.vz;
    s19b_jeep_gls_800CEC24(ctl->mov.vz - 0x640, &vec);
    GV_SubVec3(&vec, &ctl->mov, &vec);
    vec.vx += work->side;
    vec.vx += rsin(work->frame << 5) * 50 >> 12;
    vec.vx += (rsin(work->frame << 7) << 1) * work->wobble >> 12;
    work->rot.vy = GV_VecDir2(&vec);
    work->frame++;
    work->speed_prev = work->speed;
}

void s19b_jeep_liq_800D7114(JeepWork *work)
{
    work->speed_fn();
    work->side_fn(work);
    work->mode_fn(work);
    s19b_jeep_liq_800D6FB8(work);

    if (Takabe_JeepSystem.field_40 != 0)
    {
        if (Takabe_JeepSystem.field_40 == 6)
        {
            work->act_fn = s19b_jeep_liq_800D7200;
        }
        else if (Takabe_JeepSystem.field_40 == 7)
        {
            work->act_fn = s19b_jeep_liq_800D7330;
        }
        else if (Takabe_JeepSystem.field_40 == 8)
        {
            work->act_fn = s19b_jeep_liq_800D7468;
        }
    }

    if (work->act_fn != s19b_jeep_liq_800D7114)
    {
        work->mode = 0;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D77F0);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7BB0);
        s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8044);
        work->phase = 0;
    }
}

void s19b_jeep_liq_800D7200(JeepWork *work)
{
    CONTROL *ctl = &work->control;
    int      side;

    switch (work->phase)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0x2EE, 0x32);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x7D0) == 10)
        {
            work->phase = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D7860(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7CBC(work);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0xBB8) == 12)
        {
            work->phase = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D77F0(work);
        s19b_jeep_liq_800D6FB8(work);
        side = GV_NearSpeed(work->side, 0x28A, 0x32);
        work->side = side;
        if (side == 0x28A)
        {
            work->act_fn = s19b_jeep_liq_800D7114;
            work->side_target = side;
            work->phase = 0;
        }
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7330.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7468.s")
void s19b_jeep_liq_800D76B0(JeepWork *work)
{
    work->speed_fn();
    work->side = 0;
    work->mode_fn(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(JeepWork *work, JeepFn arg1)
{
    if (work->speed_fn != arg1)
    {
        work->speed_fn = arg1;
        work->speed_fn_time = 0;
        work->speed_timer = 0;
    }
}

int s19b_jeep_liq_800D771C(int cur, int center, int pos)
{
    int d    = pos - center;
    int base = s19b_jeep_mrl_800D399C();

    if (d >= 0)
    {
        if (d > 0xBB8)
        {
            cur = GV_NearSpeed(cur, base + 0x64, 0xF);
        }
        else if (d > 0x2EE)
        {
            cur = GV_NearSpeed(cur, base + 0x32, 8);
        }
        else if (d > 0x5D)
        {
            cur = GV_NearSpeed(cur, base + 0xF, 3);
        }
    }
    else
    {
        if (d < -0xBB8)
        {
            cur = GV_NearSpeed(cur, base - 0x64, 0xF);
        }
        else if (d < -0x2EE)
        {
            cur = GV_NearSpeed(cur, base - 0x32, 8);
        }
        else if (d < -0x5D)
        {
            cur = GV_NearSpeed(cur, base - 0xF, 3);
        }
    }
    return cur;
}
void s19b_jeep_liq_800D77F0(JeepWork *work)
{
    int v = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0x753, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7860(JeepWork *work)
{
    int s1 = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    int a1 = s19b_jeep_mrl_800D399C();

    if (work->speed_timer == 0)
    {
        if (work->flags & 8)
        {
            int v1 = work->speed - 0x32;
            int v0;
            work->speed = v1;
            v0 = v1 - v1 / 16;
            work->speed = v0;
            work->speed_target = v0;
            work->speed_timer = 0x3c;
            Takabe_JeepSystem.field_54 |= 2;
        }
        else if (s1 >= 0x5dd)
        {
            work->speed_target = GV_NearSpeed(work->speed_target, a1 + 0x32, 7);
            Takabe_JeepSystem.field_54 |= 0x1000;
        }
    }
    else
    {
        work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0xbb8, s1);
        work->speed_timer--;
    }
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D797C(JeepWork *work)
{
    int v = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D79EC(JeepWork *work)
{
    int v = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, -0x177, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7A5C(JeepWork *work)
{
    int v = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0xbb8, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7ACC(JeepWork *work)
{
    int v = work->road[2] - (Takabe_JeepSystem.field_30 - Takabe_JeepSystem.field_24);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0x1194, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}

void s19b_jeep_liq_800D7B3C(JeepWork *work, JeepFn arg1)
{
    if (work->side_fn != arg1)
    {
        work->side_fn = arg1;
        work->side_step = 0;
        work->side_count = 0;
    }
}

int s19b_jeep_liq_800D7B60(int center, int range)
{
    return (rand() * range >> 15) - range / 2 + center;
}
void s19b_jeep_liq_800D7BB0(JeepWork *work)
{
    if (++work->side_count == 0x1e)
    {
        work->side_target = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->side_count = 0;
    }
    work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
}
void s19b_jeep_liq_800D7C0C(JeepWork *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        work->side_target = 0x546;
        work->side = GV_NearSpeed(work->side, 0x546, 0x32);
        if (work->side_count == 0x28)
        {
            work->side_step = 1;
            work->side_count = 0x13;
        }
        break;
    case 1:
        if (n == 0x14)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x4e2, 0xfa);
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7CBC(JeepWork *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        work->side_target = 0x5dc;
        if (work->side_count == 0x28)
        {
            work->side_step = 1;
            work->side_count = 0x13;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x32);
        break;
    case 1:
        if (n == 0x14)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x5dc, 0xfa);
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7D68(JeepWork *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0x190);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x32);
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = -0x226;
        }
        else if (n == 0x3c)
        {
            work->side_step = 0;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x64);
        break;
    }
}
void s19b_jeep_liq_800D7E2C(JeepWork *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(-0x2ee, 0x96);
        }
        else if (n == 0x3c)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        {
            int r = GV_NearSpeed(work->side, work->side_target, 0x4b);
            work->side = r;
            if (r == work->side_target)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(-0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D7F20(JeepWork *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0x96);
            work->side_count = 0;
        }
        else if (n == 0x3c)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        {
            int r = GV_NearSpeed(work->side, work->side_target, 0x4b);
            work->side = r;
            if (r == work->side_target)
            {
                Takabe_JeepSystem.field_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D8014(JeepWork *work, JeepFn arg1)
{
    if (work->mode_fn != arg1)
    {
        work->mode_fn = arg1;
        work->side_step = 0;
        work->side_count = 0;
        work->flags &= ~2;
    }
}
extern unsigned char s19b_dword_800C3A9C[];
extern int s19b_jeep_mrl_800D39B4(SVECTOR *dst);

void s19b_jeep_liq_800D8044(JeepWork *work)
{
    SVECTOR sp10;

    s19b_jeep_mrl_800D39B4(&sp10);
    if (Takabe_JeepSystem.field_5C != 0 && work->shoot_count >= 0x15)
    {
        work->shoot_count = 0;
        if (work->side > 0)
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7E2C);
        }
        else
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
        }
        Takabe_JeepSystem.field_54 |= 0x1000;
        GM_SeSet(&work->control.mov, s19b_dword_800C3A9C[GV_RandU(4)]);
    }
    else
    {
        work->shoot_count++;
    }
}
void s19b_jeep_liq_800D8118(JeepWork *work)
{
    SVECTOR dst;
    int     d;

    s19b_jeep_mrl_800D39B4(&dst);
    d = work->control.mov.vz - dst.vz;
    if (d < 0)
    {
        work->mode = 5;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7D68);
    }
    else
    {
        work->mode = 2;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
    }
}

void s19b_jeep_liq_800D81A8(JeepWork *work)
{
    int n = work->shoot_count;
    work->shoot_count = n + 1;
    if (n == 0)
    {
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_RADAR_OFF | STATE_PADRELEASE;
        s19b_jlamp_800D0A20(0);
    }
    else if (n >= 0x150)
    {
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_RADAR_OFF | STATE_PADRELEASE);
        s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8044);
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D77F0);
        work->act_fn = s19b_jeep_liq_800D7114;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8250.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8420.s")
void s19b_spark2_m_800D8620(LiqWork *work)
{
    GM_FreeTarget(work->target);
    GM_ResetHomingTarget(work->homing);
    GM_FreeObject(&work->obj2);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->obj);
}
extern void s19b_jeep_liq_800D8250(LiqWork *work);
extern int  s19b_jeep_liq_800D8420(LiqWork *work, int name);
extern const char s19b_aJeepliqc_800DDE80[];
extern const char s19b_dword_800DDE8C[];

void *s19b_spark2_m_800D8670(CONTROL *arg0, DG_OBJS *arg1, int *arg2)
{
    LiqWork *work = GV_NewActor(GV_ACTOR_USER, sizeof(LiqWork));

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_liq_800D8250, s19b_spark2_m_800D8620,
                         s19b_aJeepliqc_800DDE80);
        work->jeep_control = arg0;
        work->jeep_objs = arg1;
        work->jeep_flags = arg2;
        if (s19b_jeep_liq_800D8420(work, GV_StrCode(s19b_dword_800DDE8C)) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}

void s19b_spark2_m_800D8724(LiqWork *work, int arg1, int arg2)
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
extern int s19b_spark2_m_800D87A4(LiqWork *work);

int s19b_spark2_m_800D88D8(LiqWork *work)
{
    if (s19b_spark2_m_800D87A4(work) != 0)
    {
        work->target->class = 1;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8918(LiqWork *work)
{
    TARGET *target = work->target;
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

int s19b_spark2_m_800D899C(LiqWork *work)
{
    int v = work->cmd;

    if (v & 0x1)
    {
        work->state = s19b_spark2_m_800D8BC8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x2)
    {
        work->state = s19b_spark2_m_800D8CEC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x4)
    {
        work->state = s19b_spark2_m_800D8E10;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x10)
    {
        work->state = s19b_spark2_m_800D90A8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x04000000)
    {
        work->state = s19b_spark2_m_800D92C8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8A48(LiqWork *work)
{
    GV_NearExp4PV(&work->adjust[2], &work->sv_7A0, 3);
    GV_NearExp4PV(&work->adjust[6], &work->sv_7A8, 3);
}

void s19b_spark2_m_800D8A88(LiqWork *work)
{
    int v = work->player_dir - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AAC(LiqWork *work)
{
    int base = work->player_dir + 0xCC0;
    int v    = base - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8ACC(LiqWork *work)
{
    int base = work->player_dir + 0x340;
    int v    = base - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AEC(LiqWork *work)
{
    MATRIX m;

    DG_SetPos(&work->obj.objs->objs[4].world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AC0);
    ReadRotMatrix(&m);
    NewJeepBullet(&m, 2, 1, 0);
    GM_SeSet(&work->control.mov, 0x2E);
    s19b_jblood_800C7FB8(&m);
}

void s19b_spark2_m_800D8B54(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 0;
        GM_ConfigObjectAction(&work->obj, 0, 0, 4);
    }
    if (s19b_spark2_m_800D88D8(work) == 0)
    {
        if (s19b_spark2_m_800D899C(work) == 0)
        {
            work->target->class |= 0x14;
        }
    }
}

extern void s19b_spark2_m_800D8F34(LiqWork *work, int mode);

void s19b_spark2_m_800D8BC8(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 1;
        GM_ConfigObjectAction(&work->obj, 1, 0, 4);
    }
    s19b_spark2_m_800D8A88(work);

    if (!(cmd & 1))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D8F34;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

extern void s19b_spark2_m_800D8FB0(LiqWork *work, int mode);

void s19b_spark2_m_800D8CEC(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 3;
        GM_ConfigObjectAction(&work->obj, 3, 0, 4);
    }
    s19b_spark2_m_800D8AAC(work);

    if (!(cmd & 2))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D8FB0;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

extern void s19b_spark2_m_800D902C(LiqWork *work, int mode);

void s19b_spark2_m_800D8E10(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 2;
        GM_ConfigObjectAction(&work->obj, 2, 0, 4);
    }
    s19b_spark2_m_800D8ACC(work);

    if (!(cmd & 4))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D902C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D8F34(LiqWork *work, int mode)
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
        work->state = s19b_spark2_m_800D8BC8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D8FB0(LiqWork *work, int mode)
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
        work->state = s19b_spark2_m_800D8CEC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D902C(LiqWork *work, int mode)
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
        work->state = s19b_spark2_m_800D8E10;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}

extern void s19b_spark2_m_800D9148(LiqWork *work);

void s19b_spark2_m_800D90A8(LiqWork *work, int mode)
{
    if (mode < 8)
    {
        work->target->class |= 0x14;
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->action = 0x10;
        GM_ConfigObjectAction(&work->obj, 0x10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D9148;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9148.s")

void s19b_spark2_m_800D91DC(LiqWork *work, int mode)
{
    if (mode < 8 && (work->cmd & 0x10))
    {
        work->state = s19b_spark2_m_800D9148;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (mode >= 8)
    {
        work->target->class |= 0x14;
    }

    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }

    if (work->f93C != 0 && mode >= 0xB)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->f93C = 0;
    }

    if (mode == 0)
    {
        work->action = 0x12;
        GM_ConfigObjectAction(&work->obj, 0x12, 0, 4);
    }

    if (work->obj.is_end == 0)
    {
        return;
    }

    work->state = s19b_spark2_m_800D8B54;
    work->state_time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_spark2_m_800D932C(LiqWork *work, int mode);

void s19b_spark2_m_800D92C8(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 10;
        GM_ConfigObjectAction(&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D932C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D932C(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 10;
        GM_ConfigObjectAction(&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D932C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9390(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 20;
        GM_ConfigObjectAction(&work->obj, 20, 0, 4);
        GM_SeSet(&work->control.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->jeep_flags |= 1;
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->f940 = 45;
        work->f93C = 0;
    }
}

void s19b_spark2_m_800D9434(LiqWork *work, int mode)
{
    if (s19b_spark2_m_800D899C(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        GM_SeSet(&work->control.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->jeep_flags |= 1;
    }
    if (mode < 0x11)
    {
        return;
    }
    work->state = s19b_spark2_m_800D8B54;
    work->state_time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_spark2_m_800D94C8(LiqWork *work, int mode)
{
    work->target->class |= 0x14;
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->action = 0x13;
        GM_ConfigObjectAction(&work->obj, 0x13, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9558(LiqWork *work)
{
    int   old;
    LiqFn handler;

    work->target->class = 1;
    old     = work->state_time;
    handler = work->state;
    work->state_time = old + 1;

    if (handler == NULL)
    {
        s19b_spark2_m_800D8918(work);
        handler       = s19b_spark2_m_800D8B54;
        work->state    = handler;
    }
    handler(work, old);

    s19b_spark2_m_800D8A48(work);

    if (work->f940 != 0)
    {
        work->target->class = 1;
        work->f940 -= 1;
    }
}

void s19b_spark2_m_800D95FC(LiqWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;
    work->player_dir = GV_VecDir2(&diff);
    work->player_dist = GV_VecLen3(&diff);
}

extern void s19b_spark2_m_800D9C04(LiqWork *work);

void s19b_spark2_m_800D964C(LiqWork *work)
{
    s19b_spark2_m_800D95FC(work);
    s19b_spark2_m_800D9C04(work);
    s19b_spark2_m_800D9558(work);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9680.s")
extern int s19b_spark2_m_800D9680(LiqWork *work);

void s19b_spark2_m_800D9704(LiqWork *work)
{
    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->player_dist < 0xFA0 || work->f93C != 0)
    {
        int player_dir = work->player_dir;
        int new_f914;

        if ((unsigned)(player_dir - 0x601) < 0x3FF)
        {
            new_f914 = 1;
        }
        else if ((unsigned)(player_dir - 0x201) < 0x3FF)
        {
            new_f914 = 3;
        }
        else if ((unsigned)(player_dir - 0xA01) < 0x3FF)
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

void s19b_spark2_m_800D97A8(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 1)
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
        work->cmd |= 8;
    }
    work->cmd |= 1;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D985C(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 3)
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
        work->cmd |= 8;
    }
    work->cmd |= 2;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D9910(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 2)
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
        work->cmd |= 8;
    }
    work->cmd |= 4;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D99C4(LiqWork *work)
{
    int js = Takabe_JeepSystem.field_54;
    work->cmd |= 0x10;
    if (work->f918 >= 61 || (js & 0x2000))
    {
        work->f93C = 1;
        work->f914 = 0;
    }
    if (js & 0x2)
    {
        work->f914 = 1;
        work->cmd |= 0x02000000;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9A30(LiqWork *work)
{
    if (Takabe_JeepSystem.field_54 & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->cmd |= 0x10;
    }
    else
    {
        work->f918 += 1;
    }
}

void s19b_spark2_m_800D9A74(LiqWork *work)
{
    int new_f900 = work->cmd | 0x10;
    int js = Takabe_JeepSystem.field_54;
    work->cmd = new_f900;
    if (js & 0x2000)
    {
        work->f914 = 0;
    }
    work->f918 += 1;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9AA8.s")
extern void s19b_spark2_m_800D9AA8(LiqWork *work);

void s19b_spark2_m_800D9B38(LiqWork *work)
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

void s19b_spark2_m_800D9B88(LiqWork *work)
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

void s19b_spark2_m_800D9C04(LiqWork *work)
{
    short *table = (short *)&s19b_dword_800C3AC8;
    int    idx;

    work->cmd_dir = -1;
    work->cmd = 0;
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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA0B4.s")
