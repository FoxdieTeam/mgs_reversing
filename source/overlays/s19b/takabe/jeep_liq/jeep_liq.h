#ifndef __MGS_TAKABE_JEEP_LIQ_H__
#define __MGS_TAKABE_JEEP_LIQ_H__

#include "game/game.h"
#include "../jeep_system.h"

/* Liquid standing in the second jeep (jeep2.c) */
typedef struct _Work Work;

typedef void (*LiqStateFunc)(Work *work, int time);

struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL        *root_ctrl;      /* 0x020: the jeep's control */
    MATRIX         *root_mat;       /* 0x024: the jeep body's world matrix */
    CONTROL         control;        /* 0x028 */
    OBJECT          body;           /* 0x0A4 */
    MOTION_CONTROL  m_ctrl;         /* 0x188 */
    MOTION_SEGMENT  m_segs1[17];    /* 0x1D8 */
    MOTION_SEGMENT  m_segs2[17];    /* 0x43C */
    SVECTOR         rots[16];       /* 0x6A0 */
    SVECTOR         adjust[16];     /* 0x720 */
    SVECTOR         adjust2_target; /* 0x7A0: adjust[2] eases towards it */
    SVECTOR         adjust6_target; /* 0x7A8: adjust[6] eases towards it */
    char            pad_7B0[0x8];
    SVECTOR         head_adjust;    /* 0x7B8 */
    MATRIX          light[2];       /* 0x7C0 */
    OBJECT          gun;            /* 0x800 */
    TARGET         *target;         /* 0x8E4 */
    HOMING         *homing;         /* 0x8E8 */
    LiqStateFunc    state;          /* 0x8EC */
    char            pad_8F0[0x4];
    int             time;           /* 0x8F4: frames in the current state */
    char            pad_8F8[0x4];
    int             action;         /* 0x8FC */
    int             flags;          /* 0x900: requests of the AI to the state handlers */
    int             aim_dir;        /* 0x904 */
    char            pad_908[0x4];
    int             ai_off;         /* 0x90C */
    int             ai_mode;        /* 0x910 */
    int             ai_state;       /* 0x914 */
    int             ai_time;        /* 0x918 */
    char            pad_91C[0x4];
    int             field_920;      /* 0x920 */
    char            pad_924[0x930 - 0x924];
    int             player_dir;     /* 0x930 */
    int             player_dist;    /* 0x934 */
    char            pad_938[0x4];
    int             field_93C;      /* 0x93C */
    int             field_940;      /* 0x940 */
    int            *hit;            /* 0x944: Jeep2Work.liq_hit */
}; /* 0x948 */

/* spark2_m.c */
void s19b_spark2_m_800D964C(Work *work);

#endif // __MGS_TAKABE_JEEP_LIQ_H__
