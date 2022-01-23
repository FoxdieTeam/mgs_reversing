#ifndef SCRIPT_TBL_MAP_H
#define SCRIPT_TBL_MAP_H

#include <util/idaTypes.h>

// todo: remove this file and put this stuff in libgcl\gcl.h

typedef struct      Vec3_snakePos
{
    short           x;
    short           y;
    short           z;
} Vec3_snakePos;

typedef struct      GameState_800B4D98
{
//    short           short_access[0];
    short           field_00;
    short           field_02_diffcultyLevel; // -1,0,1,2,3
    short           field_04_flags; // bit 12 (0x800) = radar on/off
    short           field_06_newgameplus_count; // 1 = bandana, 2 = stealth, > 2 = tuxedo
    short           field_08_cd_number; // 1 or 2
    short           field_0A_random_value;
    short           field_0C_current_stage; // hash
    short           field_0E_current_map; // hash
    Vec3_snakePos   field_10_snake_position;
    short           field_16_snake_current_health;
    short           field_18_snake_max_health; // 256 to around 1400
    short           field_1A_snake_flags; // bit 1 (0x1) = common cold
    short           field_1C_equipped_weapon;
    short           field_1E_equipped_item;
    short           field_20_snake_stance; // 0 = standing, 1 = crouching, 2 = lying down
    short           field_22_weapon_states[10];
    short           field_36_weapon_capacity[10];
    short           field_4A_item_states[24];
    short           field_7A_consumable_items_capacity[3];
    short           field_80_temp_per_second; // default to 10 or -10 (-30 in warehouse, 30 in blast furnace)
    short           field_82_pal_key_shape; // 0-2-1 icon index
    short           field_84_pal_key_temp; // -7200 in warehouse, 7200 in blast furnace
    short           field_86_pal_key_temp_max; // 9000
    short           field_88_pal_key_temp_min; // -9000
    short           field_8A_frozen_items;
    short           field_8C_frozen_items_unknown;
    short           field_8E_frozen_items_temp;
    short           field_90_frozen_items_temp_min; // -7200
    short           field_92_diazepam_timer;
    short           field_94_previous_stage; // hash
    short           field_96_snake_cold_timer;
    short           field_98_snake_cold_unk1;
    short           field_9A_snake_cold_unk2;
    short           field_9C_total_being_found; // score screen
    short           field_9E_total_enemies_killed; // score screen
    short           field_A0[6];
    short           field_AC_total_rations_used; // score screen
    short           field_AE_total_continues; // score screen
    short           field_B0_total_saves; // score screen
    short           field_B2_hours_played;
    short           field_B4_seconds_played;
    short           field_B6_total_hours_elapsed; // score screen
    short           field_B8_total_seconds_elapsed; // score screen
    short           field_BA;
    short           field_BC;
    short           field_BE;
} GameState_800B4D98;

typedef struct      GCL_Vars
{
    short           var[1024];
} GCL_Vars;

typedef struct      BindStruct
{
    short           field_0;
    short           field_2_param_m;

    short           field_4;
    unsigned short  field_6;

    unsigned char   field_8_param_i_c_flags;
    char            field_9_param_s;
    char            field_A_param_b;
    unsigned char   field_B_param_e;

    short           field_C_param_d;
    short           field_E_param_d_or_512;

    int             field_10_every;
    int             field_14_proc_and_block;
} BindStruct;

enum                ItemsId
{
    eCIGS = 0,
    eSCOPE = 1,
    eC_BOX_A = 2,
    eC_BOX_B = 3,
    eC_BOX_C = 4,
    eN_V_G = 5,
    eTHERM_G = 6,
    eGASMASK = 7,
    eB_ARMOR = 8,
    eKETCHUP = 9,
    eSTEALTH = 10,
    eBANDANA = 11,
    eCAMERA = 12,
    eRATION = 13,
    eMEDICINE = 14,
    eDIAZEPAM = 15,
    ePAL_KEY = 16,
    eCARD = 17,
    eTIMER_B = 18,
    eMINE_D = 19,
    eDISC = 20,
    eROPE = 21,
    eHANDKER = 22,
    eSUPPR = 23
};

enum                ConsummableItemsId
{
    eRATION_capacity = 0,
    eMEDICINE_capacity = 1,
    eDIAZEPAM_capacity = 2
};

enum                WeaponsId
{
    eSOCOM = 0,
    eFAMAS = 1,
    eGRENADE = 2,
    eNIKITA = 3,
    eSTINGER = 4,
    eCLAYMORE = 5,
    eC4 = 6,
    eSTUN_G = 7,
    eCHAFF_G = 8,
    ePSG1 = 9
};

void GM_SetBinds_80029A5C(int, BindStruct *, int);

#endif // SCRIPT_TBL_MAP_H
