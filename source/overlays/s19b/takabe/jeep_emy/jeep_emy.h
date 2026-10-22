#ifndef __S19B_JEEP_EMY_H__
#define __S19B_JEEP_EMY_H__

#include "game/game.h"

struct _Work;

typedef void (*JBULLET_FN)(struct _Work *, int);

typedef struct _Work
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
    int            field_8D4;
    char           pad1[0x8];
    int            field_8E0;
    SVECTOR        field_8E4;
    SVECTOR        field_8EC;
    SVECTOR        field_8F4;
    int            field_8FC;
    SVECTOR        field_900[4];
    JBULLET_FN     field_920;
    char           pad2[0x4];
    int            field_928;
    char           pad3[0x4];
    int            field_930;
    int            field_934;
    int            field_938;
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
    int            field_954;
    char           pad4[0xC];
    int            field_964;
    int            field_968;
    char           pad5[0x28];
} Work;

#endif
