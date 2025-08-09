#ifndef __MGS_BULLET_BAKUDAN_H__
#define __MGS_BULLET_BAKUDAN_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "game/game.h"

// C4 bomb (armed)

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
    int            c4_index;               // the index in the GM_C4Datas_800BDD78 array
    int            map_index;              // the current map where the c4 is placed
} BakudanWork;

#define C4_COUNT 16

void *NewBakudan(MATRIX *world, SVECTOR *pos, int attached, int unused, void *data);

#endif // __MGS_BULLET_BAKUDAN_H__
