#ifndef GM_CONTROL_H
#define GM_CONTROL_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>

typedef struct Res_Control_unknown
{
    short field_0_scriptData_orHashedName;
    short field_2_name_hash;
    short field_4_trigger_Hash_Name_or_camera_w;
    short field_6_count;
    int field_8_wordPtr;
    int field_C;
    int field_10;
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
    SVECTOR field_0_position;
    SVECTOR field_8_vec;
    Res_Control_unknown field_10_pStruct_hzd_unknown;
    struct map_record *field_2C_map;
    unsigned short field_30_scriptData;
    short field_32_height;
    short field_34;
    short field_36;
    short field_38;
    short field_3A;

    SVECTOR field_3C;
    //short field_3C;
    //short field_3E;
    //short field_40;
    //short field_42;
    
    SVECTOR field_44_vec;
    SVECTOR field_4C_turn_vec;
    char field_54;
    unsigned char field_55_flags; // CONTROL_FLAG_...
    char field_56;
    char field_57;
    signed char field_58;
    char field_59;
    char field_5A[2];
    struct GV_MSG *field_5C_mesg;
    SVECTOR field_60_vecs_ary[2];
    SVECTOR* field_70[2];
    short field_78;
    short field_7A;
} GM_Control;

#define MAX_CONTROLS 96

void GM_FreeControl_800260CC(GM_Control *pControl);

#endif // GM_CONTROL_H
