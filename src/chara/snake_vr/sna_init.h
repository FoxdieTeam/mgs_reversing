// FIXME: copy-pasta of snake/sna_init.h

#ifndef _sna_H_
#define _sna_H_

#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/target.h"
#include "chara/snake/shadow.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

typedef struct Sna_E1
{
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
    unsigned char field_4;
    unsigned char field_5;
    unsigned char field_6;
    unsigned char field_7;
} Sna_E1;

typedef struct Sna_E2
{
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
    unsigned char field_4;
    unsigned char field_5;
    unsigned char field_6;
    unsigned char field_7;
    unsigned char field_8;
    unsigned char field_9;
    unsigned char field_A;
    unsigned char field_B;
} Sna_E2;

typedef struct Sna_E6
{
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
} Sna_E6;

typedef struct Target_Data
{
    SVECTOR      field_0;
    SVECTOR      field_8_size;
    int          field_10;
    int          field_14;
    int          field_18;
    unsigned int field_1C;
} Target_Data;

typedef struct Sna_Joint_Rotations
{
    SVECTOR field_0_lower_body;
    SVECTOR field_8_upper_body;
    SVECTOR field_10_right_shoulder;
    SVECTOR field_18_right_elbow;
    SVECTOR field_20_right_wrist;
    SVECTOR field_28_neck;
    SVECTOR field_30_neck2;
    SVECTOR field_38_right_shoulder;
    SVECTOR field_40_right_elbow;
    SVECTOR field_48_right_wrist;
    SVECTOR field_50_right_leg;
    SVECTOR field_58_right_knee;
    SVECTOR field_60_right_ankle;
    SVECTOR field_68_left_leg;
    SVECTOR field_70_left_knee;
    SVECTOR field_78_left_ankle;
} Sna_Joint_Rotations;

typedef struct Sna_ActionTable
{
    Sna_E1 *field_0;
    Sna_E2 *field_4;
    Sna_E1 *field_8;
    Sna_E2 *field_C;
    Sna_E2 *field_10;
    Sna_E6 *field_14;
    Sna_E1 *field_18;
} Sna_ActionTable;

typedef enum
{
    SNA_FLAG1_UNK1 = 0x1,
    SNA_FLAG1_UNK2 = 0x2,
    SNA_FLAG1_UNK3 = 0x4,
    SNA_FLAG1_UNK4 = 0x8,
    SNA_FLAG1_UNK5 = 0x10,
    SNA_FLAG1_UNK6 = 0x20,
    SNA_FLAG1_UNK7 = 0x40,
    SNA_FLAG1_UNK8 = 0x80,
    SNA_FLAG1_UNK9 = 0x100,
    SNA_FLAG1_UNK10 = 0x200,
    SNA_FLAG1_UNK11 = 0x400,
    SNA_FLAG1_UNK12 = 0x800,
    SNA_FLAG1_UNK13 = 0x1000,
    SNA_FLAG1_UNK14 = 0x2000,
    SNA_FLAG1_UNK15 = 0x4000,
    SNA_FLAG1_UNK16 = 0x8000,
    SNA_FLAG1_UNK17 = 0x10000,
    SNA_FLAG1_UNK18 = 0x20000,
    SNA_FLAG1_UNK19 = 0x40000,
    SNA_FLAG1_UNK20 = 0x80000,
    SNA_FLAG1_UNK21 = 0x100000,
    SNA_FLAG1_UNK22 = 0x200000,
    SNA_FLAG1_UNK23 = 0x400000,
    SNA_FLAG1_UNK24 = 0x800000,
    SNA_FLAG1_UNK25 = 0x1000000,
    SNA_FLAG1_UNK26 = 0x2000000,
    SNA_FLAG1_UNK27 = 0x4000000,
    SNA_FLAG1_UNK28 = 0x8000000,
    SNA_FLAG1_UNK29 = 0x10000000,
    SNA_FLAG1_UNK30 = 0x20000000,
    SNA_FLAG1_UNK31 = 0x40000000,
    SNA_FLAG1_UNK32 = 0x80000000,
} SnaFlag1;

typedef enum
{
    SNA_FLAG2_UNK1 = 0x1,
    SNA_FLAG2_UNK2 = 0x2,
    SNA_FLAG2_UNK3 = 0x4,
    SNA_FLAG2_UNK4 = 0x8,
    SNA_FLAG2_UNK5 = 0x10,
    SNA_FLAG2_UNK6 = 0x20,
    SNA_FLAG2_UNK7 = 0x40,
    SNA_FLAG2_UNK8 = 0x80,
    SNA_FLAG2_UNK9 = 0x100,
    SNA_FLAG2_UNK10 = 0x200,
    SNA_FLAG2_UNK11 = 0x400,
    SNA_FLAG2_UNK12 = 0x800,
    SNA_FLAG2_UNK13 = 0x1000,
    SNA_FLAG2_UNK14 = 0x2000,
    SNA_FLAG2_UNK15 = 0x4000,
    SNA_FLAG2_UNK16 = 0x8000,
    SNA_FLAG2_UNK17 = 0x10000,
    SNA_FLAG2_UNK18 = 0x20000,
    SNA_FLAG2_UNK19 = 0x40000,
    SNA_FLAG2_UNK20 = 0x80000,
    SNA_FLAG2_UNK21 = 0x100000,
    SNA_FLAG2_UNK22 = 0x200000,
    SNA_FLAG2_UNK23 = 0x400000,
    SNA_FLAG2_UNK24 = 0x800000,
    SNA_FLAG2_UNK25 = 0x1000000,
    SNA_FLAG2_UNK26 = 0x2000000,
    SNA_FLAG2_UNK27 = 0x4000000,
    SNA_FLAG2_UNK28 = 0x8000000,
    SNA_FLAG2_UNK29 = 0x10000000,
    SNA_FLAG2_UNK30 = 0x20000000,
    SNA_FLAG2_UNK31 = 0x40000000,
    SNA_FLAG2_UNK32 = 0x80000000,
} SnaFlag2;

// sub struct of Actor_SnaInit
typedef struct UnkSnakeStruct2
{
    unsigned short field_9E4;
    short          field_9E6;
    short          field_9E8;
    short          field_9EA;
    short          field_9EC_flags3;
    short          field_9EE;
    short          field_9F0;
    short          field_9F2;
    SVECTOR        field_9F4;
} UnkSnakeStruct2;

typedef struct SnaAutoMove // @ field_A00 in Actor_SnaInit
{
    VECTOR field_0_ivec; // dunno why int vector. this is something like the direction snake is moving
    SVECTOR field_10_vec1; // these last two are related to the target position snake wants to move to
    SVECTOR field_18_vec2;
} SnaAutoMove;

struct Actor_SnaInit;
typedef void (*TSnakeFunction)(struct Actor_SnaInit *, int);

// TODO: Many fields and sub structures are not yet recovered/incorrect
typedef struct Actor_SnaInit
{
    GV_ACT              field_0_actor;
    CONTROL             field_20_ctrl;
    OBJECT              field_9C_obj;
    MOTION_CONTROL      field_180;
    OAR_RECORD          field_1D0[34]; // bottom half of array is weapon related
    Sna_Joint_Rotations field_698_joint_rotations;
    SVECTOR             field_718[16]; // same size as above, related / same struct?
    int                 field_798_p_height;
    int                 field_79C;
    int                 field_7A0_msg_count;
    GV_MSG              field_7A4_msgs[8];
    int                 field_844;
    MATRIX              field_848_lighting_mtx; // .t is R, G, B
    MATRIX              field_868_lighting_mtx2;
    Actor_Shadow       *field_888_pShadow;
    int                *field_88C; // shadow enabled?
    unsigned short      field_890_autoaim_max_dist;
    unsigned short      field_892_autoaim_min_angle;
    SnaFlag1            field_894_flags1;
    // field_898_flags2 removed here
    TARGET             *field_89C_pTarget;
    TARGET              field_8A0_target;
    TARGET             *field_8E8_pTarget;
    SVECTOR             field_8EC_vec;
    int                 field_8F4;
    int                 field_8F8;
    SVECTOR             field_8FC;
    int                 field_904_frames_last_choke;
    GV_ACT             *field_908_weapon_actor;
    TSnakeFunction      field_90C_pWeaponFn;
    int                 field_910;
    int                 field_914_trigger;
    short              *field_918_n_bullets;
    int                 field_91C_weapon_idx;
    int                 field_920_tbl_8009D580;
    short               field_924;
    short               field_926;
    DG_TEX             *field_928;
    DG_PRIM            *field_92C;
    SVECTOR             field_930;
    SVECTOR             field_938;
    SVECTOR             field_940;
    SVECTOR             field_948;
    POLY_FT4            field_950[2];
    int                 field_9A0;
    GV_ACT             *field_9A4_item_actor;
    int                 field_9A8_current_item;
    int                 field_9AC;
    GV_PAD             *field_9B0_pad_ptr;
    Sna_ActionTable    *field_9B4_action_table;
    TSnakeFunction      field_9B8_fn_anim;
    int                 field_9BC_anim_frame;
    TSnakeFunction      field_9C0;
    int                 field_9C4;
    TSnakeFunction      field_9C8_anim_update_fn_3p; // called for every anim/state while in third person
    TSnakeFunction      field_9CC_anim_update_fn_1p; // same except first person. caller: 8005a7e0
    short               field_9D0[10];
    UnkSnakeStruct2     field_9E4;
    void               *field_9FC;
    SnaAutoMove         field_A00; // auto movement of snake during mini cutscenes. some above fields may also be this
    short               field_A20;
    short               field_A22_snake_current_health;
    char                field_A24_invuln_frames;
    char                field_A25;
    short               field_A26_stance; // SNA_STANCE_...
    short               field_A28;
    short               field_A2A;
    SVECTOR             field_A2C;
    char                field_A34;
    char                field_A35_vibtime2;
    char                field_A36;
    char                field_A37;
    short               field_A38_local_data;
    short               field_A3A;
    SVECTOR             field_A3C;
    SVECTOR             field_A44;
    int                 field_A4C;
    short               field_A50;
    short               field_A52;
    // var reused in differenet contexts, union is better than a generic name for all contexts
    union {
        short choke_count;
        short prone_bool_thing;
        short wall_thing;
        short knockdown_thing;
    } field_A54;
    short          field_A56;
    short          field_A58;
    unsigned short field_A5A;
    unsigned short field_A5C;
    short          field_A5E;
    SVECTOR        field_A60;
    SVECTOR        field_A68;
    int            field_A70;
} Actor_SnaInit;

typedef int (*TSnakeActFunction)(Actor_SnaInit *);
typedef GV_ACT * (*TSnakeEquipFuncion)(CONTROL *, OBJECT *, int);

void         sna_start_anim_8004E1F4(Actor_SnaInit *pActor, void *pFn);
void         SetAction_8004E22C(Actor_SnaInit *pActor, int action_flag, int interp);
void         sna_8004E260(Actor_SnaInit *pActor, int a2, int interp, int a4);
int          GM_CheckPlayerStatusFlag_8004E29C(PlayerStatusFlag arg0);
int          GM_SetPlayerStatusFlag_8004E2B4(PlayerStatusFlag arg0);
void         GM_ClearPlayerStatusFlag_8004E2D4(PlayerStatusFlag flag);
void         sna_set_flags1_8004E2F4(Actor_SnaInit *snake, SnaFlag1 flags);
void         sna_clear_flags1_8004E308(Actor_SnaInit *snake, SnaFlag1 flags);
int          sna_check_flags1_8004E31C(Actor_SnaInit *snake, SnaFlag1 flags);
void         sna_set_flags2_8004E330(Actor_SnaInit *snake, SnaFlag2 flag);
void         sna_clear_flags2_8004E344(Actor_SnaInit *snake, SnaFlag2 flags);
unsigned int sna_sub_8004E358(Actor_SnaInit *snake, SnaFlag2 param_2);
void         CheckSnakeDead_8004E384(Actor_SnaInit *snake);
void         sna_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags);
int          sub_8004E458(short param_1, int param_2);
int          sub_8004E4C0(Actor_SnaInit *pActor, int param_2);
int          sub_8004E51C(SVECTOR *param_1, void *param_2, int param_3, int param_4);
void         sub_8004E588(HZD_HDL *param_1, SVECTOR *param_2, HZD_VEC *param_3);
int          sub_8004E930(Actor_SnaInit *snake, int arg1);
void         sub_8004E9D0(Actor_SnaInit *pActor);
void         sub_8004EA50(Actor_SnaInit *pActor, int param_2);
int          sna_8004EAA8(Actor_SnaInit *pActor, int a2);
void         sub_8004EB74(Actor_SnaInit *pActor);
void         sna_8004EC00(Actor_SnaInit *pActor);
void         sna_8004EC8C(Actor_SnaInit *pActor);
void         sub_8004ED08(Actor_SnaInit *pActor);
void         sub_8004EEB0(Actor_SnaInit *pActor);
int          sub_8004EFE4(Actor_SnaInit *pActor, int param_2);
void         sna_8004F034(Actor_SnaInit *pActor, unsigned int bits);
void         sna_act_helper2_helper4_8004F090(Actor_SnaInit *pActor, int param_2);
void         sub_8004F14C(Actor_SnaInit *param_1);
void         sub_8004F204(Actor_SnaInit *param_1);
void         sna_set_invuln_8004F2A0(Actor_SnaInit *pActor, char invuln_frames);
void         sna_clear_invuln_8004F2EC(Actor_SnaInit *snake);
void         sub_8004F338(Actor_SnaInit *param_1);
int          sna_act_unk_helper4_8004FA3C(void);
void         sna_8004FA74(Actor_SnaInit *param_1);
void         sub_8004FA9C(Actor_SnaInit *snake);
int          sna_current_item_8004FB38(void);
SVECTOR    **sub_8004FB90(void);
int          sna_8004E808(Actor_SnaInit *pActor, int a2, int a3, int a4, int a5);

// TODO: move these to game.h even though theyre defined in sna_init.c?
// .. or move the implementation to a static inline in game.h which the definition in sna_init calls?
int  GM_Next_BulName_8004FBA0();
void GM_ClearBulName_8004FBE4(int idx);
void GM_CheckShukanReverse_8004FBF8(unsigned short *pInput);
void GM_CheckShukanReverseAnalog_8004FC70(unsigned char *pInput);

void sna_check_knock_800501F8(Actor_SnaInit *pActor, int time);
int  sna_prone_check_standup_80050398(Actor_SnaInit *pActor);
void sna_80050440(Actor_SnaInit *pActor);
void sna_80050568(Actor_SnaInit *pActor);
int  sub_800507D8(Actor_SnaInit *param_1);
void sna_80051FD0(Actor_SnaInit *pActor);
void sna_fn_80052120(Actor_SnaInit *pActor, int time);
void sub_8005230C(Actor_SnaInit *pActor, int time);
void sub_80052468(Actor_SnaInit *pActor, int time);
void sna_fn_80052540(Actor_SnaInit *pActor, int time);
void sna_fn_800525F8(Actor_SnaInit *pActor, int time);
void sna_act_helper2_helper_helper_800526BC(Actor_SnaInit *pActor, int time);
void sna_anim_idle_8005275C(Actor_SnaInit *pActor, int time);
void sna_anim_crouch_800527DC(Actor_SnaInit *param_1, int time);
void sna_anim_prone_idle_800528BC(Actor_SnaInit *pActor, int time);
void sna_anim_run_8005292C(Actor_SnaInit *pActor, int time);
void sna_anim_prone_move_800529C0(Actor_SnaInit *pActor, int time);
void sna_anim_wall_idle_and_c4_80052A5C(Actor_SnaInit *pActor, int time);
void sna_anim_wall_move_80052BA8(Actor_SnaInit *pActor, int time);
void sna_anim_wall_crouch_80052CCC(Actor_SnaInit *pActor, int time);
void sna_fn_80052E58(Actor_SnaInit *pActor, int time);
void sna_anim_crouch_helper_80053014(Actor_SnaInit *pActor, int time);
void sna_fn_800531F4(Actor_SnaInit *pActor, int time);
void sna_fn_nothing_80053B80(Actor_SnaInit *param_1, int time);
void sna_anim_run_begin_80053B88(Actor_SnaInit *param_1, int time);
void sna_anim_prone_begin_80053BE8(Actor_SnaInit *pActor, int time);
void sna_anim_prone_standup_80053D74(Actor_SnaInit *pActor, int time);
void sna_anim_enter_duct_80053E9C(Actor_SnaInit *pActor, int time);
void sub_80053FAC(Actor_SnaInit *pActor, int time);
void sna_gun_800540D0(Actor_SnaInit *pActor, int time);
void sna_bomb_800541A8(Actor_SnaInit *pActor);
void sna_anim_chokethrow_begin1_80054210(Actor_SnaInit *pActor, int time);
void sna_8005425C(Actor_SnaInit *pActor, int time);
void sna_80054318(Actor_SnaInit *pActor, int time);
void sna_fn_800543A8(Actor_SnaInit *pActor, int time);
void sna_anim_duct_move_80054424(Actor_SnaInit *pActor, int time);
void sna_anim_duct_idle_80054488(Actor_SnaInit *pActor, int time);
void sna_anim_shot_flinch_800544E0(Actor_SnaInit *pActor, int time);
void sna_act_helper2_helper7_80054648(Actor_SnaInit *pActor, int time);
void sna_anim_knockdown_80054710(Actor_SnaInit *pActor, int time);
void sna_anim_knockdown_idle_80054930(Actor_SnaInit *pActor, int time);
void sna_anim_knockdown_getup_80054A10(Actor_SnaInit *pActor, int time);
void sna_anim_knockdown_shot_80054B50(Actor_SnaInit *pActor);
void sna_anim_knockdown_shot_tank_80054C08(Actor_SnaInit *pActor, int time);
void sna_anim_scope_80055334(Actor_SnaInit *param_1, int time);
void sna_anim_jpegcam_800553CC(Actor_SnaInit *pActor, int time);
void sna_anim_box_idle_800553EC(Actor_SnaInit *pActor, int time);
void sna_anim_box_move_8005544C(Actor_SnaInit *pActor, int time);
void sna_anim_box_stop_800554B4(Actor_SnaInit *pActor, int time);
void sub_8005684C(Actor_SnaInit *pActor);
void sub_8005688C(Actor_SnaInit *pActor, int time);
void sub_80056928(Actor_SnaInit *param_1, int time);
void sna_knockdown_check_getup_80056A1C(Actor_SnaInit *pActor, int time);
void sna_80056A54(Actor_SnaInit *pActor, int time);
void sna_fn_80056AD8(Actor_SnaInit *pActor, int time);
void sna_anim_shoot_weapon_80056B88(Actor_SnaInit *pActor, int time);
void sna_anim_rungun_begin_80056BDC(Actor_SnaInit *param_1, int time);
void sna_anim_rungun_80056C3C(Actor_SnaInit *param_1, int time);
void sna_anim_stinger_800570C0(Actor_SnaInit *pActor, int time);
void sna_80057118(Actor_SnaInit *pActor, int time);
void sna_800571B8(Actor_SnaInit *pActor, int time);
void sna_80057378(Actor_SnaInit *pActor, int time);
void sna_anim_shoot_weapon_helper_80057590(Actor_SnaInit *pActor, int time);
void sna_anim_rungun_begin_helper_800577B4(Actor_SnaInit *pActor, int time);
void sna_auto_aim_800579A0(Actor_SnaInit *pActor);
void OP_ShootStinger_80058378(Actor_SnaInit *pActor, int time);
void sub_80058644(Actor_SnaInit *pActor, int time);
void sna_anim_punch_80058C10(Actor_SnaInit *pActor, int time);
void sna_anim_chokethrow_begin2_80058C80(Actor_SnaInit *pActor, int time);
void sna_anim_choke_80058E88(Actor_SnaInit *pActor, int time);
void sna_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int time);
void sna_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int time);
void sna_anim_choke_kill_80058F88(Actor_SnaInit *pActor, int time);
void snake_vr_sna_init_80055500(Actor_SnaInit *pActor, int time);
void sna_anim_choke_drag_80059054(Actor_SnaInit *pActor, int time);
void sna_anim_choke_hold_80059154(Actor_SnaInit *pActor, int time);
void sub_800591BC(Actor_SnaInit *pActor);
void sna_anim_choke_helper_8005951C(Actor_SnaInit *pActor, int time);
void sna_anim_choke_rechoke_helper_8005961C(Actor_SnaInit *pActor, int time);
void sna_kill_8005B52C(Actor_SnaInit *pActor);
void sna_anim_psg1_helper_80057FD4(Actor_SnaInit *pActor, int a2);
void sna_80051DA0(Actor_SnaInit *pActor);
void sna_80053360(Actor_SnaInit *pActor, int time);
void sub_80057BF0(Actor_SnaInit *pActor, int a2);
void sna_anim_throw_800589C8(Actor_SnaInit *pActor, int a2);
void sna_gun_800540D0(Actor_SnaInit *pActor, int a2);
void sna_anim_punch_helper_800591F4(Actor_SnaInit *pActor, int a2);
int  sna_8004FDE8(Actor_SnaInit *pActor, Target_Data *pVec);
void sna_8004F8E4(Actor_SnaInit *pActor, int a2);
void sna_fn_800535B8(Actor_SnaInit *pActor, int time);
void sna_knockdown_getup_80050668(Actor_SnaInit *pActor);
void sna_anim_grenade_80058470(struct Actor_SnaInit *pActor, int a2);
void sna_anim_claymore_80057474(struct Actor_SnaInit *pActor, int a2);
void sna_anim_psg1_80056DDC(struct Actor_SnaInit *pActor, int a2);
void sna_8004EE28(Actor_SnaInit *pActor);
void sna_8004EB14(Actor_SnaInit *pActor);
void sna_anim_wall_idle_and_c4_helper_800537D4(Actor_SnaInit *pActor, int time);
void sna_anim_wall_crouch_helper_80053A54(Actor_SnaInit *pActor, int time);
void sub_8004FAE8(Actor_SnaInit *pActor);
void sna_anim_wall_move_helper_800538CC(Actor_SnaInit *pActor, int time);
void sna_knock_80054D68(Actor_SnaInit *pActor, int time);
void sna_anim_rungun_helper_80057844(Actor_SnaInit *pActor, int time);
int  sna_8005009C(Actor_SnaInit *pActor);
int  sub_80051BA4(Actor_SnaInit *pActor);
int  sub_8004EFE4(Actor_SnaInit *pActor, int param_2);
int  sub_8004E5E8(Actor_SnaInit *pActor, int param_2);
int  sub_8004E808(Actor_SnaInit *pActor, int, int, int, int); // dummy signature
int  sna_act_unk_helper2_helper3_80060684(SnaAutoMove *, SVECTOR *);
void sna_anim_claymore_helper_80058780(Actor_SnaInit *pActor, int time);
int  HZD_GetAddress_8005C6C4(HZD_HDL *hzd, SVECTOR *vec, int param_3);
void sna_act_unk2_80051170(TARGET *pTarget);
void sna_act_helper3_helper_80056650(Actor_SnaInit *pActor, int time);
void sna_act_unk_helper3_80055DD8(Actor_SnaInit *pActor, int time);
void sna_anim_mini_cutscene_800559D8(Actor_SnaInit *pActor, int time);
void sna_anim_dying_80055524(Actor_SnaInit *pActor, int time);
void sna_act_unk_helper2_helper2_800605DC(SnaAutoMove *autoMove, HZD_HDL *pHzd, SVECTOR *pVec);
int  sna_unk_helper2_helper_8006070C(SnaAutoMove *pAutoMove, CONTROL *pControl);
void sna_80057A90(Actor_SnaInit *pActor, int time);
void sna_8004EF14(Actor_SnaInit *pActor);
GV_ACT *sna_NewSnake_8005B650(int name, int where, int argc, char **argv);
int HZD_ReachTo_8005C89C(HZD_HDL *pHzd, int, int);
int sna_act_unk_helper2_helper_helper_8005C974(HZD_HDL *pHzd, int, int, CONTROL *pControl);
void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
int sna_ration_available_8004FB4C(void);

// TODO: move these to indivudual weapon headers
GV_ACT *NewSOCOM_80065D74(CONTROL *a1, OBJECT *parentObj, int unit, int *a4, int a5);
GV_ACT *famas_create_80066374(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *grenade_create_80066A4C(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *NewRCM_80066FF0(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *mine_init_800677BC(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *NewBomb_80067B20(CONTROL *a1, OBJECT *parentObj, int unit, int *a4, int a5);
GV_ACT *NewStanGrenade_80066A74(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *NewChaffGrenade_80066AA0(CONTROL *a1, OBJECT *parentObj, int unit, int a4, int a5);
GV_ACT *NewRifle_80068214(CONTROL *a1, OBJECT *parentObj, int unit, int *a4, int a5);

#endif // _sna_H_
