#ifndef __S18A_LIQUID_H__
#define __S18A_LIQUID_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/* Liquid (rooftop fistfight on Metal Gear REX) */
typedef struct _LiquidWork
{
    GV_ACT         actor;         /* 0x000 */
    CONTROL        control;       /* 0x020 */
    OBJECT         body;          /* 0x09C */
    OBJECT         weapon;        /* 0x180 */
    MOTION_CONTROL m_ctrl;        /* 0x264 */
    MOTION_SEGMENT m_segs1[17];   /* 0x2B4 */
    MOTION_SEGMENT m_segs2[17];   /* 0x518 */
    SVECTOR        rots[16];      /* 0x77C */
    SVECTOR        adjust[16];    /* 0x7FC */
    MATRIX         light[2];      /* 0x87C */
    TARGET        *target;        /* 0x8BC */
    TARGET        *target2;       /* 0x8C0 */
    TARGET         attack;        /* 0x8C4 */
    int            f90C;          /* 0x90C */
    char           pad_910[0x92C - 0x910];
    void          *act;           /* 0x92C */
    int            f930;          /* 0x930 */
    int            time;          /* 0x934 */
    int            f938;          /* 0x938 */
    int            pose;          /* 0x93C */
    int            f940;          /* 0x940 */
    char           pad_944[0x948 - 0x944];
    int            f948;          /* 0x948 */
    HOMING        *hom;           /* 0x94C */
    int            cmd;           /* 0x950 */
    char           pad_954[0x958 - 0x954];
    int            f958;          /* 0x958 */
    int            f95C;          /* 0x95C */
    int            f960;          /* 0x960 */
    int            f964;          /* 0x964 */
    int            f968;          /* 0x968 */
    char           pad_96C[0x978 - 0x96C];
    int            f978;          /* 0x978 */
    char           pad_97C[0x980 - 0x97C];
    int            f980;          /* 0x980 */
    int            f984;          /* 0x984 */
    int            life;          /* 0x988 */
    char           pad_98C[0x990 - 0x98C];
    int            f990;          /* 0x990 */
    int            f994;          /* 0x994 */
    int            cam_mode;      /* 0x998 */
    int            f99C;          /* 0x99C */
    int            f9A0;          /* 0x9A0 */
    int            f9A4;          /* 0x9A4 */
    int            f9A8;          /* 0x9A8 */
    short          f9AC;          /* 0x9AC */
    short          f9AE;          /* 0x9AE */
    int            f9B0;          /* 0x9B0 */
    char           pad_9B4[0x9BC - 0x9B4];
    short          dead_timer;    /* 0x9BC */
    short          f9BE;          /* 0x9BE */
    char           pad_9C0[0x9E0 - 0x9C0];
    int            proc_e;        /* 0x9E0 */
    int            proc_b;        /* 0x9E4 */
    int            proc_s;        /* 0x9E8 */
    int            voices[19];    /* 0x9EC */
    void          *shadow;        /* 0xA38 */
    u_char         damage1[3];    /* 0xA3C */
    u_char         damage2[5];    /* 0xA3F */
    SVECTOR        last_pos;      /* 0xA44 */
} LiquidWork;

#endif // __S18A_LIQUID_H__
