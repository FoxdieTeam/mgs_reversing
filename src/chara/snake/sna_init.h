#ifndef _SNA_INIT_H_
#define _SNA_INIT_H_

#include "actor.h"
#include "GM_Control.h"
#include "game.h"
#include "target.h"
#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

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
    SVECTOR field_0;
    SVECTOR field_8_size;
    int field_10;
    int field_14;
    int field_18;
    unsigned int field_1C;
} Target_Data;

typedef struct Sna_1D0
{
    // types are wrong. lots of mixed read/write sizes so hard to tell
    // most seem to be shorts though
    int field_1D0;
    int field_1D4;
    int field_1D8;
    int field_1DC;
    int field_1E0;
    int field_1E4;
    int field_1E8;
    int field_1EC;
    int field_1F0;
} Sna_1D0;

// probably animation related, probably has vectors
typedef struct Sna_1F4
{
    // first 32 bytes seem consistent with a MATRIX,
    // but asm doesnt look like gte macro
    short field_0; // vec1?
    short field_2;
    short field_4;
    short field_6;
    short field_8; // vec2?
    short field_A;
    short field_C;
    short field_E;
    int   field_10;
    int   field_14;
    short field_18;
    short field_1A;
    char  field_1C;
    char  field_1D;
    char  field_1E;
    char  field_1F;
    char  field_20;
    char  field_21; // these next three are guessed
    char  field_22;
    char  field_23;
} Sna_1F4;

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

// might belong in another header
// camera references this is a lot
typedef struct UnkMaybeCameraStruct // @ 800B77B8
{
    short field_0;
    short field_2;
    int field_4;
    int field_8;
    short field_C;
    short field_E;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    short field_28_aim_assist; // dont know what this really is
    short field_2A;
    int field_2C;
} UnkMaybeCameraStruct;
STATIC_ASSERT_SIZE(UnkMaybeCameraStruct, 0x30);

typedef enum
{
    SNA_FLAG1_UNK1  = 0x1,
    SNA_FLAG1_UNK2  = 0x2,
    SNA_FLAG1_UNK3  = 0x4,
    SNA_FLAG1_UNK4  = 0x8,
    SNA_FLAG1_UNK5  = 0x10,
    SNA_FLAG1_UNK6  = 0x20,
    SNA_FLAG1_UNK7  = 0x40,
    SNA_FLAG1_UNK8  = 0x80,
    SNA_FLAG1_UNK9  = 0x100,
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
    SNA_FLAG2_UNK1  = 0x1,
    SNA_FLAG2_UNK2  = 0x2,
    SNA_FLAG2_UNK3  = 0x4,
    SNA_FLAG2_UNK4  = 0x8,
    SNA_FLAG2_UNK5  = 0x10,
    SNA_FLAG2_UNK6  = 0x20,
    SNA_FLAG2_UNK7  = 0x40,
    SNA_FLAG2_UNK8  = 0x80,
    SNA_FLAG2_UNK9  = 0x100,
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

enum
{
    SNA_STANCE_STANDING = 0,
    SNA_STANCE_CROUCH = 1,
    SNA_STANCE_GROUND = 2, // prone + knocked down
    // ... more?
};

// TODO: Many fields and sub structures are not yet recovered/incorrect
typedef struct Actor_SnaInit
{
    Actor field_0_actor;
    GM_Control field_20_ctrl;
    OBJECT field_9C_obj;
    int field_C0; // here until field_17F is zeroed during normal gameplay
    char field_C4;
    char field_C5;
    char field_C6;
    char field_C7;
    char field_C8;
    char field_C9;
    char field_CA;
    char field_CB;
    char field_CC;
    char field_CD;
    char field_CE;
    char field_CF;
    char field_D0;
    char field_D1;
    char field_D2;
    char field_D3;
    char field_D4;
    char field_D5;
    char field_D6;
    char field_D7;
    char field_D8;
    char field_D9;
    char field_DA;
    char field_DB;
    char field_DC;
    char field_DD;
    char field_DE;
    char field_DF;
    char field_E0;
    char field_E1;
    char field_E2;
    char field_E3;
    char field_E4;
    char field_E5;
    char field_E6;
    char field_E7;
    char field_E8;
    char field_E9;
    char field_EA;
    char field_EB;
    char field_EC;
    char field_ED;
    char field_EE;
    char field_EF;
    char field_F0;
    char field_F1;
    char field_F2;
    char field_F3;
    char field_F4;
    char field_F5;
    char field_F6;
    char field_F7;
    char field_F8;
    char field_F9;
    char field_FA;
    char field_FB;
    char field_FC;
    char field_FD;
    char field_FE;
    char field_FF;
    char field_100;
    char field_101;
    char field_102;
    char field_103;
    char field_104;
    char field_105;
    char field_106;
    char field_107;
    char field_108;
    char field_109;
    char field_10A;
    char field_10B;
    char field_10C;
    char field_10D;
    char field_10E;
    char field_10F;
    char field_110;
    char field_111;
    char field_112;
    char field_113;
    char field_114;
    char field_115;
    char field_116;
    char field_117;
    char field_118;
    char field_119;
    char field_11A;
    char field_11B;
    char field_11C;
    char field_11D;
    char field_11E;
    char field_11F;
    char field_120;
    char field_121;
    char field_122;
    char field_123;
    char field_124;
    char field_125;
    char field_126;
    char field_127;
    char field_128;
    char field_129;
    char field_12A;
    char field_12B;
    char field_12C;
    char field_12D;
    char field_12E;
    char field_12F;
    char field_130;
    char field_131;
    char field_132;
    char field_133;
    char field_134;
    char field_135;
    char field_136;
    char field_137;
    char field_138;
    char field_139;
    char field_13A;
    char field_13B;
    char field_13C;
    char field_13D;
    char field_13E;
    char field_13F;
    char field_140;
    char field_141;
    char field_142;
    char field_143;
    char field_144;
    char field_145;
    char field_146;
    char field_147;
    char field_148;
    char field_149;
    char field_14A;
    char field_14B;
    char field_14C;
    char field_14D;
    char field_14E;
    char field_14F;
    char field_150;
    char field_151;
    char field_152;
    char field_153;
    char field_154;
    char field_155;
    char field_156;
    char field_157;
    char field_158;
    char field_159;
    char field_15A;
    char field_15B;
    char field_15C;
    char field_15D;
    char field_15E;
    char field_15F;
    char field_160;
    char field_161;
    char field_162;
    char field_163;
    char field_164;
    char field_165;
    char field_166;
    char field_167;
    char field_168;
    char field_169;
    char field_16A;
    char field_16B;
    char field_16C;
    char field_16D;
    char field_16E;
    char field_16F;
    char field_170;
    char field_171;
    char field_172;
    char field_173;
    char field_174;
    char field_175;
    char field_176;
    char field_177;
    char field_178;
    char field_179;
    char field_17A;
    char field_17B;
    char field_17C;
    char field_17D;
    char field_17E;
    char field_17F; // zeroed during normal gameplay end
    MOTION_CONTROL field_180;
    Sna_1D0 field_1D0;
    Sna_1F4 field_1F4[33]; // bottom half of array is weapon related
    Sna_Joint_Rotations field_698_joint_rotations;
    SVECTOR field_718[16]; // same size as above, related / same struct?
    int field_798;
    int field_79C;
    int field_7A0;
    int field_7A4;
    int field_7A8;
    int field_7AC;
    int field_7B0;
    int field_7B4;
    int field_7B8;
    int field_7BC;
    int field_7C0;
    int field_7C4;
    int field_7C8;
    int field_7CC;
    int field_7D0;
    int field_7D4;
    int field_7D8;
    int field_7DC;
    int field_7E0;
    int field_7E4;
    int field_7E8;
    int field_7EC;
    int field_7F0;
    int field_7F4;
    int field_7F8;
    int field_7FC;
    int field_800;
    int field_804;
    int field_808;
    int field_80C;
    int field_810;
    int field_814;
    int field_818;
    int field_81C;
    int field_820;
    int field_824;
    int field_828;
    int field_82C;
    int field_830;
    int field_834;
    int field_838;
    int field_83C;
    int field_840;
    int field_844;
    MATRIX field_848_lighting_mtx; // .t is R, G, B
    MATRIX field_868_lighting_mtx2;
    Actor *field_888_pShadow;
    unsigned int *field_88C;
    unsigned short field_890_autoaim_max_dist;
    unsigned short field_892_autoaim_min_angle;
    SnaFlag1 field_894_flags1;
    SnaFlag2 field_898_flags2;
    GM_Target *field_89C_pTarget;
    GM_Target field_8A0_target;
    GM_Target *field_8E8_pTarget;
    SVECTOR field_8EC_vec;
    int field_8F4;
    int field_8F8;
    int field_8FC;
    int field_900;
    int field_904_frames_last_choke;
    Actor *field_908_weapon_actor;
    void *field_90C_pWeaponFn;
    int field_910;
    int field_914;
    short *field_918_pWeaponState;
    int field_91C_weapon_idx;
    int field_920_tbl_8009D580;
    short field_924;
    short field_926;
    DG_TEX *field_928;
    DG_OBJS *field_92C;
    SVECTOR field_930;
    SVECTOR field_938;
    SVECTOR field_940;
    SVECTOR field_948;
    int field_950;
    int field_954;
    int field_958;
    int field_95C;
    int field_960;
    int field_964;
    int field_968;
    int field_96C;
    int field_970;
    int field_974;
    int field_978;
    int field_97C;
    int field_980;
    int field_984;
    int field_988;
    int field_98C;
    int field_990;
    int field_994;
    int field_998;
    int field_99C;
    int field_9A0;
    Actor *field_9A4_item_actor;
    int field_9A8;
    int field_9AC;
    GV_PAD *field_9B0_pad_ptr;
    Sna_ActionTable *field_9B4_action_table;
    void *field_9B8_fn_anim;
    int field_9BC_anim_frame;
    void *field_9C0;
    int field_9C4;
    void *field_9C8_anim_update_fn_3p; // called for every anim/state while in third person
    void *field_9CC_anim_update_fn_1p; // same except first person. caller: 8005a7e0
    SVECTOR field_9D0[3];
    short field_9E8;
    short field_9EA;
    short field_9EC;
    short field_9EE;
    short field_9F0;
    short field_9F2;
    int field_9F4;
    int field_9F8;
    int field_9FC;
    SVECTOR field_A00;
    int field_A08;
    int field_A0C;
    int field_A10;
    int field_A14;
    int field_A18;
    int field_A1C;
    short field_A20;
    short field_A22_snake_current_health;
    char field_A24_invuln_frames;
    char field_A25;
    short field_A26_fn_stance_idx; // SNA_STANCE_...
    short field_A28;
    short field_A2A;
    short field_A2C;
    short field_A2E;
    short field_A30;
    short field_A32;
    int field_A34;
    short field_A38;
    short field_A3A;
    int field_A3C;
    int field_A40;
    int field_A44;
    short field_A48;
    short field_A4A;
    int field_A4C;
    short field_A50;
    short field_A52;
    // var reused in differenet contexts, union is better than a generic name for all contexts
    union { short choke_count; short prone_bool_thing; short wall_thing; } field_A54;
    short field_A56;
    short field_A58;
    short field_A5A;
    int field_A5C;
    SVECTOR field_A60;
    SVECTOR field_A68;
    int field_A70;
} Actor_SnaInit;

#endif // _SNA_INIT_H_
