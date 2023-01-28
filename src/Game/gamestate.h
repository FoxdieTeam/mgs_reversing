#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "libgv/libgv.h"

// in its own file because circular dep w/ gcl.h

#define MAX_HISTORY 8

typedef struct AreaHistory
{
    short history[MAX_HISTORY];
} AreaHistory;

#define GAMESTATE_ITEM_STATES 24
#define GAMESTATE_WEAPON_STATES 10

#define GM_Difficulty      1
#define GM_Flags           2

#define GM_CurrentDisc     4
#define GM_LastResult      5
#define GM_CurrentStage    6
#define GM_CurrentMap      7
#define GM_CurrentPosX     8
#define GM_CurrentPosY     9
#define GM_CurrentPosZ     10
#define GM_CurrentHealth   11
#define GM_MaxHealth       12

#define GM_CurrentWeapon   14
#define GM_CurrentItem     15
#define GM_Stance          16

#define GM_WeaponBase      17

#define GM_ItemBase        37

#define GM_ItemRation      50

#define GM_ItemTimerB      55

#define GM_ItemSilencer    60

#define GM_FrozenItems     69

#define GM_PreviousStage   74

#define GM_RationCount     86
#define GM_ContinueCount   87
#define GM_SaveCount       88

#define GM_PlaytimeHours   91
#define GM_PlaytimeSeconds 92
#define GM_LastSaveHours   93
#define GM_LastSaveSeconds 94

/*
typedef struct GameState
{
    short  field_00;
    short  field_02_diffcultyLevel; // -1,0,1,2,3
    short  field_04_flags;          // bit 12 (0x800) = radar on/off
    short  field_06_bonus_items;    // 0 = none, 1 = bandana, 2 = stealth, > 2 = tuxedo
    short  field_08_cd_number;      // 1 or 2
    short  field_0A_last_result;
    short  field_0C_current_stage; // hash
    short  field_0E_current_map;   // hash
    GV_Vec field_10_snake_position;
    short  field_16_snake_current_health;
    short  field_18_snake_max_health; // 256 to around 1400
    short  field_1A_snake_flags;      // bit 1 (0x1) = common cold
    short  field_1C_equipped_weapon;
    short  field_1E_equipped_item;
    short  field_20_snake_stance; // 0 = standing, 1 = crouching, 2 = lying down
    short  field_22_weapon_states[10];
    short  field_36_weapon_capacity[10];
    short  field_4A_item_states[24];
    short  field_7A_consumable_items_capacity[3];
    short  field_80_temp_per_second;  // default to 10 or -10 (-30 in warehouse, 30 in blast furnace)
    short  field_82_pal_key_shape;    // 0-2-1 icon index
    short  field_84_pal_key_temp;     // -7200 in warehouse, 7200 in blast furnace
    short  field_86_pal_key_temp_max; // 9000
    short  field_88_pal_key_temp_min; // -9000
    short  field_8A_frozen_items;
    short  field_8C_frozen_items_unknown;
    short  field_8E_frozen_items_temp;
    short  field_90_frozen_items_temp_min; // -7200
    short  field_92_diazepam_timer;
    short  field_94_previous_stage; // hash
    short  field_96_snake_cold_timer;
    short  field_98_snake_cold_unk1;
    short  field_9A_snake_cold_unk2;
    short  field_9C_total_being_found;    // score screen
    short  field_9E_total_enemies_killed; // score screen
    short  field_A0;
    short  field_A2;
    short  field_A4;
    short  field_A6;
    short  field_A8;
    short  field_AA;
    short  field_AC_total_rations_used; // score screen
    short  field_AE_total_continues;    // score screen
    short  field_B0_total_saves;        // score screen
    short  field_B2_hours_played;
    short  field_B4_seconds_played;
    short  field_B6_total_hours_elapsed;   // score screen
    short  field_B8_total_seconds_elapsed; // score screen
    short  field_BA_last_save_hours;
    short  field_BC_last_save_seconds;
    short  field_BE;
} GameState;
*/

#define GM_GetWeapon(x) (&gGameState_800B4D98[GM_WeaponBase + (x)])

#define GM_WeaponSocom    GM_GetWeapon(eSOCOM)
#define GM_WeaponFamas    GM_GetWeapon(eFAMAS)
#define GM_WeaponGrenade  GM_GetWeapon(eGRENADE)
#define GM_WeaponNikita   GM_GetWeapon(eNIKITA)
#define GM_WeaponStinger  GM_GetWeapon(eSTINGER)
#define GM_WeaponClaymore GM_GetWeapon(eCLAYMORE)
#define GM_WeaponC4       GM_GetWeapon(eC4)
#define GM_WeaponStunG    GM_GetWeapon(eSTUN_G)
#define GM_WeaponChaffG   GM_GetWeapon(eCHAFF_G)
#define GM_WeaponPSG1     GM_GetWeapon(ePSG1)

static inline short *GM_GetCurrentWeapon( void )
{
    extern short gGameState_800B4D98[ 0x60 ];
    return GM_GetWeapon(gGameState_800B4D98[GM_CurrentWeapon]);
}

#endif // _GAMESTATE_H_
