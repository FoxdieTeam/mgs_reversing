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

typedef struct      GameState
{
    Unk_800B4D98    unk;

    short           field_0_stageNameHashed;
    short           field_2_loader_param_m;
//    short           field_4_param_p_vec[3];
    Vec3_snakePos   field_4_snake_position;
    short           field_A_snake_current_health;
    short           field_C_snake_max_health;
    char            field_E_snake_flags; // is snake cold ? etc..
    char            field_F_pad; // check
//    short           field_10_load_item_fn_idx;
    short           field_10_equipped_weapon;
//    short           field_12_selected_menu_item_idx;
    short           field_12_equipped_item;
    short           field_14;
    short           field_16_weapon_states[10];
    short           field_2A_weapon_capacity[10];
    short           field_3E_item_states[24];
//    short           field_6E[3];
    short           field_6E_consumable_items_capacity[3]; // ration, medicine and diazepam capacity
    short           field_74;
    short           field_76_PAL_card_icon_idx;
//    short           field_78;
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
//    short           field_A2;
    short           field_A2_hours_played;
//    short           field_A4;
    short           field_A4_seconds_played;
//    short           field_A6_game_time1;
    short           field_A6_total_hours_elapsed;
//    short           field_A8_game_time2;
    short           field_A8_total_seconds_elapsed;
    short           field_AA;
    short           field_AC;
    short           field_AE;
    short           field_B0;
    short           field_B2;
} GameState;

#endif // SCRIPT_TBL_MAP_H
