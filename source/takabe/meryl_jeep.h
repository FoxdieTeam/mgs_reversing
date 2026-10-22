#ifndef __TAKABE_MERYL_JEEP_H__
#define __TAKABE_MERYL_JEEP_H__

#include "game/game.h"

/* Meryl riding in the jeep, with Snake (s19a pkjp_mrl.c) or in the chase (s19b jeep_mrl.c). */
typedef struct _MerylJeepWork
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;           // 0x20
    MATRIX        *root_mat;            // 0x24
    CONTROL        control;             // 0x28
    OBJECT         body;                // 0xA4
    MOTION_CONTROL m_ctrl;              // 0x188
    MOTION_SEGMENT m_segs1[17];         // 0x1D8
    MOTION_SEGMENT m_segs2[17];         // 0x43C
    SVECTOR        rots[16];            // 0x6A0
    SVECTOR        adjust[16];          // 0x720
    MATRIX         light[2];            // 0x7A0
    int            face;                // 0x7E0
    int            head_rot;            // 0x7E4
    TARGET        *target;              // 0x7E8
    void          *action;              // 0x7EC
    char           pad_7F0[0x4];
    int            time;                // 0x7F4
    char           pad_7F8[0x4];
    int            action_id;           // 0x7FC
    int            flags;               // 0x800
    char           pad_804[0x14];
    short          voice1;              // 0x818
    short          voice2;              // 0x81A
    short          voice3;              // 0x81C
    short          voice4;              // 0x81E
} MerylJeepWork;

#endif
