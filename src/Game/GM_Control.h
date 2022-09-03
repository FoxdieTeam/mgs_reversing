#ifndef GM_CONTROL_H
#define GM_CONTROL_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
//#include "map/map.h"

typedef struct Res_Control_unknown
{
    short   field_0_scriptData_orHashedName;
    short   field_2_name_hash;
    short   field_4_trigger_Hash_Name_or_camera_w;
    short   field_6_count;
    short   field_8;
    short   field_A;
    short   field_C;
    short   field_E;
    int     field_10;
    SVECTOR field_14_vec;
} Res_Control_unknown;

struct map_record;

enum
{
    CONTROL_FLAG_UNK1 = 0x1,
    CONTROL_FLAG_UNK2 = 0x2,
    CONTROL_FLAG_UNK4 = 0x4, // affects collision
    CONTROL_FLAG_UNK8 = 0x8,
    CONTROL_FLAG_UNK10 = 0x10,
    CONTROL_FLAG_UNK20 = 0x20,
    CONTROL_FLAG_UNK40 = 0x40,
    CONTROL_FLAG_UNK80 = 0x80,
}; // can't typedef char enums :(

typedef struct GM_Control
{
    // Position vector, mainly controlled by 80025A7C().
    // - 0x80025cd4 (W): controls vx during gameplay;
    // - 0x80025db8 (W): contributes to collision detection on the vx axis;
    // - 0x80025f00 (W): appears to control vx during animations;
    // - 0x80025ba0 (W): controls vy during gameplay when going up;
    // - 0x80026040 (W): controls vy during gameplay when going down;
    // - 0x80025cec (W): controls vz during gameplay;
    // - 0x80025dcc (W): appears to control vz during or when exiting animations (eg against walls).
    SVECTOR field_0_position;

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
    short field_34;
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
    unsigned char field_55_flags; // CONTROL_FLAG_...
    char          field_56;
    char          field_57;

    // Appears to indicate proximity to a wall, where 1 is close and 0 is far.
    // Going up against a wall requires a 0->1 write by 80025A7C() @ 0x80025d1c and a read by 800596FC() @ 0x80059858.
    signed char    field_58;
    char           field_59;
    char           field_5A[2];
    struct GV_MSG *field_5C_mesg;

    // The first of these two vectors is heavily used in collision detection.
    SVECTOR  field_60_vecs_ary[2];
    SVECTOR *field_70[2];

    // Shadow offset.
    short field_78;
    short field_7A;
} GM_Control;

#define MAX_CONTROLS 96

void GM_FreeControl_800260CC(GM_Control *pControl);

#endif // GM_CONTROL_H
