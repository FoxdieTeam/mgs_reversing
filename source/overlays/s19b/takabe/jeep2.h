#ifndef __S19B_JEEP2_H__
#define __S19B_JEEP2_H__

#include "game/game.h"

typedef struct _Jeep2Work Jeep2Work;

typedef void (*Jeep2Func)(Jeep2Work *);

/* The second jeep, the one Liquid chases/drives (jeep2.c builds and updates it,
 * jeep_liq.c holds its movement state machines). */
struct _Jeep2Work
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ GV_ACT        *liq;
    /* +0x024 */ CONTROL        control;
    /* +0x0A0 */ TARGET        *target;
    /* +0x0A4 */ OBJECT         body;
    /* +0x188 */ OBJECT         tyres;
    /* +0x26C */ OBJECT_NO_ROTS gun;
    /* +0x290 */ MATRIX         light[2];
    /* +0x2D0 */ OBJECT_NO_ROTS front_headlights;
    /* +0x2F4 */ OBJECT_NO_ROTS headlights;
    /* +0x318 */ MATRIX         light2;
    /* +0x338 */ char           pad_338[0x20];
    /* +0x358 */ VECTOR         pos;
    /* +0x368 */ VECTOR         old_pos;
    /* +0x378 */ SVECTOR        move;
    /* +0x380 */ SVECTOR        field_380;
    /* +0x388 */ SVECTOR        field_388;
    /* +0x390 */ SVECTOR        rot;
    /* +0x398 */ SVECTOR        field_398;
    /* +0x3A0 */ int            side;
    /* +0x3A4 */ int            side_target;
    /* +0x3A8 */ int            speed;
    /* +0x3AC */ int            speed_prev;
    /* +0x3B0 */ int            speed_target;
    /* +0x3B4 */ int            flags;
    /* +0x3B8 */ int            wobble;         // set to 20 when hit, counts down
    /* +0x3BC */ int            se_timer;
    /* +0x3C0 */ int            field_3C0;
    /* +0x3C4 */ int            hit;
    /* +0x3C8 */ int            frame;
    /* +0x3CC */ int            phase;
    /* +0x3D0 */ Jeep2Func      act_fn;
    /* +0x3D4 */ int            speed_timer;
    /* +0x3D8 */ int            speed_fn_time;
    /* +0x3DC */ void          (*speed_fn)();  // called without arguments, work is still in $a0
    /* +0x3E0 */ int            side_count;
    /* +0x3E4 */ int            side_step;
    /* +0x3E8 */ Jeep2Func      side_fn;
    /* +0x3EC */ int            mode;
    /* +0x3F0 */ int            shoot_count;
    /* +0x3F4 */ int            field_3F4;
    /* +0x3F8 */ Jeep2Func      mode_fn;
};

#endif
