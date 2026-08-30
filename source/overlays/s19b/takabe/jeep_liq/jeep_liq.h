#ifndef __MGS_TAKABE_JEEP_LIQ_H__
#define __MGS_TAKABE_JEEP_LIQ_H__

#include "game/game.h"

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

/* jeep_liq.c */
void s19b_jeep_liq_800D6FB8(Work *work);

/* spark2_m.c */
void s19b_spark2_m_800D964C(Work *work);

#endif // __MGS_TAKABE_JEEP_LIQ_H__
