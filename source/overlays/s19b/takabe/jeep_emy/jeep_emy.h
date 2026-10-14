#ifndef __S19B_JEEP_EMY_H__
#define __S19B_JEEP_EMY_H__

#include "game/game.h"

/* Soldier shooting at the jeep (jeep_emy.c: actor and states, jeep_emy2.c: AI) */
typedef struct _Work Work;

typedef void (*JBULLET_FN)(Work *, int);

struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[16 + 1];
    MOTION_SEGMENT m_segs2[16 + 1];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    OBJECT         weapon;
    int            lod;
    DG_DEF        *models[2];
    TARGET        *target1;
    TARGET        *target2;
    HOMING        *hom;
    int            fall_step;    /* 0x8D4 */
    char           pad_8D8[0x8];
    int            pushed;       /* 0x8E0 */
    SVECTOR        push_step;    /* 0x8E4 */
    SVECTOR        start_pos;    /* 0x8EC */
    SVECTOR        goal_pos;     /* 0x8F4: one of points[] */
    int            n_points;     /* 0x8FC: 'n' option */
    SVECTOR        points[4];    /* 0x900: 'a' option */
    JBULLET_FN     action;       /* 0x920 */
    char           pad_924[0x4];
    int            time;         /* 0x928 */
    char           pad_92C[0x4];
    int            motion;       /* 0x930 */
    int            field_934;    /* 0x934 */
    int            shot_time;    /* 0x938 */
    int            input;        /* 0x93C: pad-like input of the AI (or of pad 1) */
    int            input_dir;    /* 0x940 */
    int            field_944;    /* 0x944: pad 1 controls the soldier when set */
    int            ai_mode;      /* 0x948 */
    int            ai_state;     /* 0x94C */
    int            ai_time;      /* 0x950 */
    int            field_954;    /* 0x954 */
    char           pad_958[0xC];
    int            player_dir;   /* 0x964 */
    int            player_dist;  /* 0x968 */
    char           pad_96C[0x28];
};

#endif
