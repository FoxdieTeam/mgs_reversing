#ifndef CONTROL_H
#define CONTROL_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
//#include "map/map.h"

#include "libgv/libgv.h"

typedef struct Res_Control_unknown
{
    unsigned short  field_0_scriptData_orHashedName;
    unsigned short  field_2_name_hash;
    short           field_4_trigger_Hash_Name_or_camera_w;
    short           field_6_count;
    unsigned short  field_8_array[6];
    SVECTOR         field_14_vec;
} Res_Control_unknown;

struct map_record;

enum
{
	CTRL_SKIP_MESSAGE    = 0x01,
	CTRL_SKIP_TRAP       = 0x02,
	CTRL_SKIP_NEAR_CHECK = 0x04,
	CTRL_BOTH_CHECK      = 0x08,
}; // can't typedef char enums :(

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
    SVECTOR             field_8_rotator;
    Res_Control_unknown field_10_pStruct_hzd_unknown;
    struct map_record  *field_2C_map;
    unsigned short      field_30_scriptData;

    // Base height, written to by 800596FC() and read by 80025A7C() as an offset to determine the position vector's vy
    // component.
    short field_32_height;

    // If 80025A7C() @ 0x80025b8c is not allowed to read this field, Snake goes through walls.
    short field_34_hzd_height;
    short field_36;
    short field_38;
    short field_3A;

    SVECTOR field_3C;
    // short field_3C;
    // short field_3E;
    // short field_40;
    // short field_42;

    // Movement vector, added to the position vector each frame to determine Snake's new position.
    // 800356FC() @ 0x80035974 (vx) and 0x8003597c (vz) seems to be the main function responsible for calculating the
    // movement vector, since it is the only writing function which if disabled prevents Snake from moving entirely.
    SVECTOR       field_44_movementVector;
    SVECTOR       field_4C_turn_vec;
    char          field_54;
    unsigned char field_55_skip_flag; // CTRL_...
    signed char   field_56;
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
