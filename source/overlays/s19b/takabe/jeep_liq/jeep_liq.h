#ifndef __S19B_JEEP_LIQ_H__
#define __S19B_JEEP_LIQ_H__

#include "mgstype.h"
#include "game/game.h"

typedef void (*LiqFn)();

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
    int      field_44;
    char     pad3d[0x54 - 0x44 - sizeof(int)];
    int      field_54;
    char     pad5c[0x5C - 0x54 - sizeof(int)];
    int      field_5C;
    char     pad60[0x68 - 0x5C - sizeof(int)];
    OBJECT  *liq_obj;
} JEEP_SYSTEM_S;

extern JEEP_SYSTEM_S Takabe_JeepSystem;
extern SVECTOR       Takabe_JeepLiqPos;

#endif // __S19B_JEEP_LIQ_H__
