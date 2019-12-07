#include "linker.h"
#include <sys/types.h>
#include <libgte.h>

int SECTION(".sbss") gControlCount_800AB9B4;

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

typedef struct Res_Control
{
    SVECTOR field_0_vec;
    SVECTOR field_8_vec;
    Res_Control_unknown field_10_pStruct_hzd_unknown;
    struct map_record *field_2C_map;
    unsigned short field_30_scriptData;
    short field_32_height;
    short field_34;
    short field_36;
    short field_38;
    short field_3A;
    short field_3C;
    short field_3E;
    short field_40;
    short field_42;
    SVECTOR field_44_vec;
    SVECTOR field_4C_turn_vec;
    char field_54;
    char field_55_flags;
    char field_56;
    char field_57;
    char field_58;
    char field_59;
    short field_5A;
    int field_5C_mesg;
    SVECTOR field_60_vecs_ary[2];
    int field_70;
    int field_74;
    short field_78;
    short field_7A;
} Res_Control;

#define MAX_CONTROLS 96
Res_Control *SECTION(".gControlArray_800B56D0") gControlArray_800B56D0[96];
Res_Control SECTION(".gDefaultControl_800B5650") gDefaultControl_800B5650;

int GM_ControlPushBack_800258B0(Res_Control *pControlToAdd)
{
    // sna_init must always be the first item
    if (pControlToAdd->field_30_scriptData == 0x21CA)
    {
        gControlArray_800B56D0[0] = pControlToAdd;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        gControlArray_800B56D0[gControlCount_800AB9B4] = pControlToAdd;
        gControlCount_800AB9B4++;
    }

    return 0;
}

void GM_ControlRemove_80025904(Res_Control *pControl)
{
    int i = gControlCount_800AB9B4;
    int val = gControlCount_800AB9B4;
    Res_Control **pControlIter = gControlArray_800B56D0;

    while (i > 0)
    {
        i--;

        if (*pControlIter == pControl)
        {
            goto lol;
        }
        pControlIter++;
    }


    return;

lol:

    if (pControlIter != gControlArray_800B56D0)
    {
        *pControlIter = gControlArray_800B56D0[--val];
        gControlCount_800AB9B4 = val;
    }
    else
    {
        gControlArray_800B56D0[0] = &gDefaultControl_800B5650;
    }
}
