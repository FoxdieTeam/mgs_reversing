#ifndef __S19B_JEEP_H__
#define __S19B_JEEP_H__

#include "game/game.h"

/* The jeep Snake rides in (jeep.c); jeep_mrl.c holds its state handlers. */
typedef struct _JeepWork JeepWork;

typedef void (*JeepFunc)(JeepWork *);

struct _JeepWork
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ GV_ACT        *mrl;
    /* +0x024 */ int            map;
    /* +0x028 */ CONTROL        control;
    /* +0x0A4 */ TARGET        *target;
    /* +0x0A8 */ OBJECT         jeep_b;
    /* +0x18C */ OBJECT         jeep_t;
    /* +0x270 */ MATRIX         light[2];
    /* +0x2B0 */ TARGET         target2;
    /* +0x2F8 */ OBJECT_NO_ROTS fhl;
    /* +0x31C */ OBJECT_NO_ROTS hl;
    /* +0x340 */ MATRIX         light2;
    /* +0x360 */ char           pad_360[0x20];
    /* +0x380 */ VECTOR         pos;
    /* +0x390 */ VECTOR         old_pos;
    /* +0x3A0 */ SVECTOR        speed;
    /* +0x3A8 */ SVECTOR        field_3A8;
    /* +0x3B0 */ SVECTOR        field_3B0;
    /* +0x3B8 */ SVECTOR        rot;
    /* +0x3C0 */ SVECTOR        field_3C0;
    /* +0x3C8 */ short          field_3C8;
    /* +0x3CA */ short          field_3CA;
    /* +0x3CC */ int            field_3CC;
    /* +0x3D0 */ int            field_3D0;
    /* +0x3D4 */ int            field_3D4;
    /* +0x3D8 */ int            field_3D8;
    /* +0x3DC */ int            field_3DC;
    /* +0x3E0 */ int            vibrate_timer;
    /* +0x3E4 */ int            field_3E4;
    /* +0x3E8 */ int            field_3E8;
    /* +0x3EC */ int            field_3EC;
    /* +0x3F0 */ int            field_3F0;
    /* +0x3F4 */ int            field_3F4;
    /* +0x3F8 */ JeepFunc       func_3F8;
};

#endif
