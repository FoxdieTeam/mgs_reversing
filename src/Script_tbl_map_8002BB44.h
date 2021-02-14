#ifndef SCRIPT_TBL_MAP_H
#define SCRIPT_TBL_MAP_H

#include <util/idaTypes.h>

typedef struct      LitHeader
{
    int             field_0_num_lights;
} LitHeader;

typedef struct      map_record
{
    int             field_0_map_index_bit;
    short           field_4_map_num;
    unsigned short  field_6_bUsed;
    struct HzdMap   *field_8_hzd;
    LitHeader       *field_C_l_file;
    int             field_10_script_z_param_bit_index_zone_id;
} map_record;

typedef struct      Unk_800B4D98
{
    short           field_0;
    short           field_2_DiffcultyLevel;
    WORD            Flags;
    WORD            pad;
    short           StartingCdId;
    short           LastRand;
} Unk_800B4D98;

typedef struct      Vec3_snakePos
{
    short           x;
    short           y;
    short           z;
} Vec3_snakePos;

enum ItemsId
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

enum ConsummableItemsId
{
    eRATION_capacity = 0,
    eMEDICINE_capacity = 1,
    eDIAZEPAM_capacity = 2
};

enum WeaponsId
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

typedef struct      GameState
{
    Unk_800B4D98    unk;

    short           field_0_stageNameHashed;
    short           field_2_loader_param_m;
    Vec3_snakePos   field_4_snake_position;
    short           field_A_snake_current_health;
    short           field_C_snake_max_health;
    char            field_E_snake_flags; // is snake cold ? etc..
    char            field_F_pad; // check
    short           field_10_equipped_weapon;
    short           field_12_equipped_item;
    short           field_14;
    short           field_16_weapon_states[10];
    short           field_2A_weapon_capacity[10];
    short           field_3E_item_states[24];
    short           field_6E_consumable_items_capacity[3];
    short           field_74;
    short           field_76_PAL_card_icon_idx;
    short           field_78_PAL_card_timer;
    short           field_7A;
    short           field_7C;
    short           field_7E_bItems_frozen;
    short           field_80;
    short           field_82_freeze_items_timer;
    short           field_84;
//    short           field_86_snake_shake_delay;
    short           field_86_diazepam_timer;
    short           field_88_prevStageNameHashed;
    short           field_8A_snake_cold_timer;
    short           field_8C_times_spotted;
    short           field_8E_num_enemies_killed;
    int             field_90[3];
    short           field_9C_num_rations_used;
    short           field_9E_num_continues;
    short           field_A0_num_saves;
    short           field_A2_hours_played;
    short           field_A4_seconds_played;
    short           field_A6_total_hours_elapsed;
    short           field_A8_total_seconds_elapsed;
    short           field_AA;
    short           field_AC;
    short           field_AE;
    short           field_B0;
    short           field_B2;
} GameState;

#endif // SCRIPT_TBL_MAP_H
