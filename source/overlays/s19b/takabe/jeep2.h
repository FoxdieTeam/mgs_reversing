#ifndef __S19B_JEEP2_H__
#define __S19B_JEEP2_H__

#include "game/game.h"

/* The jeep Liquid drives (jeep2.c). Its behaviour handlers live in jeep_liq.c. */
typedef struct _Jeep2Work Jeep2Work;

typedef void (*Jeep2Func)(Jeep2Work *work);

struct _Jeep2Work
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ GV_ACT        *liquid;          // jeep_liq.c actor
    /* +0x024 */ CONTROL        control;
    /* +0x0A0 */ TARGET        *target;
    /* +0x0A4 */ OBJECT         jeep_b;
    /* +0x188 */ OBJECT         jeep_t;
    /* +0x26C */ OBJECT_NO_ROTS gun;
    /* +0x290 */ MATRIX         light[2];
    /* +0x2D0 */ OBJECT_NO_ROTS fhl;
    /* +0x2F4 */ OBJECT_NO_ROTS hl;
    /* +0x318 */ MATRIX         light2;
    /* +0x338 */ char           pad_338[0x358 - 0x338];
    /* +0x358 */ VECTOR         pos;             // world position
    /* +0x368 */ VECTOR         old_pos;
    /* +0x378 */ SVECTOR        speed;
    /* +0x380 */ SVECTOR        field_380;
    /* +0x388 */ SVECTOR        old_speed;
    /* +0x390 */ SVECTOR        rot;
    /* +0x398 */ SVECTOR        old_rot;
    /* +0x3A0 */ int            lateral;         // offset from the road centre
    /* +0x3A4 */ int            lateral_target;
    /* +0x3A8 */ int            velocity;
    /* +0x3AC */ int            old_velocity;
    /* +0x3B0 */ int            target_velocity;
    /* +0x3B4 */ int            flags;
    /* +0x3B8 */ int            shake;           // swerve amplitude after a hit
    /* +0x3BC */ int            se_timer;
    /* +0x3C0 */ int            field_3C0;
    /* +0x3C4 */ int            liq_hit;         // set by jeep_liq.c when Liquid is hit
    /* +0x3C8 */ int            time;
    /* +0x3CC */ int            step;            // step of the current state
    /* +0x3D0 */ Jeep2Func      state;
    /* +0x3D4 */ int            field_3D4;
    /* +0x3D8 */ int            field_3D8;
    /* +0x3DC */ Jeep2Func      speed_func;
    /* +0x3E0 */ int            sub_time;        // counter of steer_func / mode_func
    /* +0x3E4 */ int            sub_step;        // step of steer_func / mode_func
    /* +0x3E8 */ Jeep2Func      steer_func;
    /* +0x3EC */ int            field_3EC;
    /* +0x3F0 */ int            field_3F0;
    /* +0x3F4 */ int            field_3F4;
    /* +0x3F8 */ Jeep2Func      mode_func;
}; /* 0x3FC */

/* jeep_liq.c */
void s19b_jeep_liq_800D76B0(Jeep2Work *work);
void s19b_jeep_liq_800D7ACC(Jeep2Work *work);
void s19b_jeep_liq_800D7BB0(Jeep2Work *work);
void s19b_jeep_liq_800D7D68(Jeep2Work *work);
void s19b_jeep_liq_800D81A8(Jeep2Work *work);
GV_ACT *s19b_spark2_m_800D8670(CONTROL *root_ctrl, MATRIX *root_mat, int *hit);

#endif
