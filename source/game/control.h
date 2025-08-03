#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <sys/types.h>
#include <libgte.h>
#include "libgv/libgv.h"
#include "game/map.h"

enum
{
    CTRL_SKIP_MESSAGE    = 0x01,
    CTRL_SKIP_TRAP       = 0x02,
    CTRL_SKIP_NEAR_CHECK = 0x04,
    CTRL_BOTH_CHECK      = 0x08,
}; // can't typedef char enums :(

enum // radar_attr
{
    RADAR_OFF     = 0,
    RADAR_VISIBLE = 0x1,  // Enables dot at entity position
    RADAR_SIGHT   = 0x4,  // Enables vision cone for entities
    RADAR_ALL_MAP = 0x8,
    RADAR_NOISE   = 0x10, // Enables noise at position on radar (e.g. DARPA Chief)
    RADAR_UNK1    = 0x20, // Extends distance before entity is no longer drawn on the radar?
    RADAR_UNK2    = 0x40, // Enables RADAR_SIGHT if within certain height of Snake?
    RADAR_UNK4    = 0x1000,
    RADAR_UNK3    = 0x2000,
};

    // vx = dir;
    // vy = len;
    // vz = ang;

typedef struct RADAR_CONE
{
    unsigned short dir;
    unsigned short len;
    unsigned short ang;
    unsigned short _pad;
} RADAR_CONE;

typedef struct CONTROL
{
    // Position vector, mainly controlled by 80025A7C().
    // - 0x80025cd4 (W): controls vx during gameplay;
    // - 0x80025db8 (W): contributes to collision detection on the vx axis;
    // - 0x80025f00 (W): appears to control vx during animations;
    // - 0x80025ba0 (W): controls vy during gameplay when going up;
    // - 0x80026040 (W): controls vy during gameplay when going down;
    // - 0x80025cec (W): controls vz during gameplay;
    // - 0x80025dcc (W): appears to control vz during or when exiting animations (eg against walls).
    SVECTOR mov;

    // Rotator, in which each field (other than padding) is a fixed-point number ranging from 0 to ONE (ie 4096,
    // unclamped and using modulo for values outside of this range) where ONE is a full rotation:
    // - vx: pitch;
    // - vy: yaw;
    // - vz: roll.
    // During normal gameplay, controlled by 800269A0() @ 0x80026a08.
    SVECTOR rot;

    HZD_EVT event;
    MAP    *map;
    u_short name;

    // Base height, written to by 800596FC() and read by 80025A7C() as an offset to determine the position vector's vy
    // component.
    short height;

    // If 80025A7C() @ 0x80025b8c is not allowed to read this field, Snake goes through walls.
    short hzd_height;
    short field_36;
    short field_38;

    u_short    radar_atr;
    RADAR_CONE radar_cone;

    // Movement vector, added to the position vector each frame to determine Snake's new position.
    // 800356FC() @ 0x80035974 (vx) and 0x8003597c (vz) seems to be the main function responsible for calculating the
    // movement vector, since it is the only writing function which if disabled prevents Snake from moving entirely.
    SVECTOR     step;
    SVECTOR     turn;
    signed char field_54;
    char        skip_flag; // CTRL_...
    signed char n_messages;
    signed char field_57;
    signed char touch_flag;   // > 0 if collision detected
    char        exclude_flag; // exclude all surfaces where (flag & exclude_flag) != 0
    char        field_5A[2];
    GV_MSG     *messages;

    // The first of these two vectors is heavily used in collision detection.
    SVECTOR  field_60_vecs_ary[2];
    HZD_FLR *field_70[2]; //  HZD_FLR when b1.h >= 0, HZD_SEG when b1.h < 0

    // Shadow offset.
    short levels[2];
} CONTROL;

#define MAX_CONTROLS 96

/* control.c */
// int  GM_ControlPushBack(CONTROL *control);
// void GM_ControlRemove(CONTROL *control);
void GM_InitWhereSystem(void);
int  GM_InitControl(CONTROL *control, int scriptData, int scriptBinds);
void GM_ActControl(CONTROL *control);
void GM_FreeControl(CONTROL *control);
void GM_ConfigControlVector(CONTROL *control, SVECTOR *pos, SVECTOR *rot);
void GM_ConfigControlMatrix(CONTROL *control, MATRIX *matrix);
void GM_ConfigControlString(CONTROL *control, char *param_pos, char *param_dir);
void GM_ConfigControlHazard(CONTROL *control, short height, short f36, short f38);
void GM_ConfigControlAttribute(CONTROL *control, int radar_atr);
void GM_ConfigControlInterp(CONTROL *control, char f5a);
int  GM_CheckControlTouches(CONTROL *control, int param_2);
// void GM_ConfigControlRadarparam(CONTROL *control, u_short dir, u_short len, u_short ang, u_short pad);
void GM_ConfigControlTrapCheck(CONTROL *control);
GV_MSG *GM_CheckMessage(GV_ACT *actor, int msgType, int toFind);

#endif // _CONTROL_H_
