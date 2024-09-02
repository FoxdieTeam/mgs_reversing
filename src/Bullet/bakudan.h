#ifndef _BAKUDAN_H_
#define _BAKUDAN_H_

#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/target.h"

// c4 (armed)

typedef struct BakudanWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS kmd;
    MATRIX         light_mtx[2];
    MATRIX        *transform;              // transform matrix (assigned if the c4 is placed on a moving target)
    SVECTOR       *position;               // position (assigned if the c4 is placed on a moving target)
    int            detonator_btn_pressed;  // 1 if the detonator button is pressed, 0 otherwise
    int            detonator_frames_count; // number of actor actions to wait before detonate
    GV_PAD        *active_pad;             // pointer to the currently active gamepad
    int            c4_index;               // the index in the c4_actors_800BDD78 array
    int            map_index;              // the current map where the c4 is placed
} BakudanWork;

#define C4_COUNT 16

GV_ACT *NewBakudan_8006A6CC(MATRIX *world, SVECTOR *pos, int attached, int unused, void *data);

#endif // _BAKUDAN_H_
