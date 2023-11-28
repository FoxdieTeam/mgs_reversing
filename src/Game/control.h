#ifndef CONTROL_H
#define CONTROL_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include "libgv/libgv.h"
#include "Game/map.h"

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
    RADAR_UNK3    = 0x2000,
};

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
    SVECTOR field_0_mov;

    // Rotator, in which each field (other than padding) is a fixed-point number ranging from 0 to ONE (ie 4096,
    // unclamped and using modulo for values outside of this range) where ONE is a full rotation:
    // - vx: pitch;
    // - vy: yaw;
    // - vz: roll.
    // During normal gameplay, controlled by 800269A0() @ 0x80026a08.
    SVECTOR             field_8_rot;
    HZD_EVT field_10_events;
    MAP  *field_2C_map;
    unsigned short      field_30_scriptData;

    // Base height, written to by 800596FC() and read by 80025A7C() as an offset to determine the position vector's vy
    // component.
    short field_32_height;

    // If 80025A7C() @ 0x80025b8c is not allowed to read this field, Snake goes through walls.
    short field_34_hzd_height;
    short field_36;
    short field_38;

    unsigned short field_3A_radar_atr;

    // Radar vision cone direction/distance.
    // Not actually an SVECTOR.
    SVECTOR field_3C;

    // Movement vector, added to the position vector each frame to determine Snake's new position.
    // 800356FC() @ 0x80035974 (vx) and 0x8003597c (vz) seems to be the main function responsible for calculating the
    // movement vector, since it is the only writing function which if disabled prevents Snake from moving entirely.
    SVECTOR       field_44_step;
    SVECTOR       field_4C_turn;
    signed char   field_54;
    unsigned char field_55_skip_flag; // CTRL_...
    signed char   field_56; //n_messages
    signed char   field_57;

    // Appears to indicate proximity to a wall, where 1 is close and 0 is far.
    // Going up against a wall requires a 0->1 write by 80025A7C() @ 0x80025d1c and a read by 800596FC() @ 0x80059858.
    signed char    field_58;
    char           field_59;
    char           field_5A[2];
    GV_MSG        *field_5C_mesg;

    // The first of these two vectors is heavily used in collision detection.
    SVECTOR  field_60_vecs_ary[2];
    SVECTOR *field_70[2];

    // Shadow offset.
    short field_78_levels[2];
} CONTROL;

#define MAX_CONTROLS 96

void GM_FreeControl_800260CC(CONTROL *pControl);
void GM_ConfigControlVector_800260FC(CONTROL *pControl, SVECTOR *pVec1, SVECTOR *pVec2);

#endif // CONTROL_H
