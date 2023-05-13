#ifndef _DEMOTHRD_H_
#define _DEMOTHRD_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/camera.h"

typedef struct dmo_model_0x14
{
  int field_0_type;
  int field_4_flags;
  int field_8;
  int field_C_hashCode;
  int field_10;
} dmo_model_0x14;

typedef struct Dmo_Map8
{
    int field_0;
    int field_8;
} Dmo_Map8;

typedef struct demothrd_0x1C
{
  int field_0_magic;
  int field_4_chunk_size;
  int field_8_movie_frames;
  int field_C_num_maps;
  int field_10_num_models;
  Dmo_Map8* field_14_pMaps;
  dmo_model_0x14 *field_18_pModels;
} demothrd_0x1C;


typedef struct dmo_data_0x34
{
  int field_0;
  int field_4_type;
  short field_8_x;
  short field_A_y;
  short field_C_z;
  short field_E_x;
  short field_10_y;
  short field_12_z;
  short field_14;
  short field_16;
  int field_18;
  short field_1C;
  short field_1E;
  int field_20;
  char field_24;
  char field_25;
  char field_26;
  char field_27;
  short field_28;
  short field_2A;
  int field_2C;
  short field_30;
  short field_32;
} dmo_data_0x34;

typedef struct dmo_6
{
  short field_0;
  short field_2;
  short field_4;
} dmo_6;

typedef struct dmo_data_0x18
{
  int field_0_type;
  short field_4;
  short field_6_rot_x;
  short field_8_rot_y;
  short field_A_rot_z;
  short field_C_pos_x;
  short field_E_pos_y;
  short field_10_pos_z;
  short field_12_total;
  dmo_6 *field_14_pEndData;
} dmo_data_0x18;

typedef struct dmo_data_0x28
{
  int field_0;
  int field_4;
  short field_8_xpos;
  short field_A_ypos;
  short field_C_zpos;
  short field_E_x;
  short field_10_y;
  short field_12_z;
  short field_14_z;
  short field_16;
  short field_18_count;
  short field_1A;
  dmo_data_0x34 *field_1C_dmo_data_offset;
  short field_20_count;
  short field_22;
  dmo_data_0x18 *field_24_pDmoEnd;
} dmo_data_0x28;


typedef struct dmo_m1e1
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  int field_48;
  int field_4C;
  int field_50;
  int field_54;
  int field_58;
  int field_5C;
  int field_60;
  int field_64;
  int field_68;
  int field_6C;
  int field_70;
  int field_74;
  int field_78;
  int field_7C;
  int field_80;
  int field_84;
  int field_88;
  int field_8C;
  int field_90;
  int field_94;
  int field_98;
  int field_9C;
  int field_A0;
  int field_A4;
  int field_A8;
  int field_AC;
  int field_B0;
  int field_B4;
  int field_B8;
  int field_BC;
} dmo_m1e1;

typedef struct dmo_m1e1_entry
{
  OBJECT field_0;
  dmo_m1e1 field_24;
} dmo_m1e1_entry;

typedef struct dmo_m1e1_data
{
  dmo_m1e1_entry field_0[2][3];
  int field_558_idx[2];
  int field_560;
  SVECTOR field_564[2];
} dmo_m1e1_data;

typedef struct dmo_hind
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
} dmo_hind;


typedef struct dmo_model_0x1A4
{
  CONTROL field_0_ctrl;
  OBJECT field_7C_obj;
  SVECTOR field_A0[1]; // TODO: Seems to be an array, perhaps up to a fixed size
  short field_A8;
  short field_AA;
  int field_AC;
  short field_B0;
  short field_B2;
  int field_B4;
  int field_B8;
  int field_BC;
  int field_C0;
  int field_C4;
  int field_C8;
  int field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  int field_100;
  int field_104;
  int field_108;
  int field_10C;
  int field_110;
  int field_114;
  int field_118;
  int field_11C;
  int field_120;
  int field_124;
  int field_128;
  int field_12C;
  int field_130;
  int field_134;
  int field_138;
  int field_13C;
  int field_140;
  int field_144;
  int field_148;
  int field_14C;
  int field_150;
  int field_154;
  int field_158;
  int field_15C;
  MATRIX field_160_mtx;
  int field_180;
  int field_184;
  int field_188;
  int field_18C;
  int field_190;
  int field_194;
  int field_198;
  int field_19C;
  dmo_m1e1_data *field_1A0_pM1OrHind; // union, can be dmo_hind also, depending on the current stage
} dmo_model_0x1A4;

typedef struct Actor_demothrd_0x78_Chain
{
  struct Actor_demothrd_0x78_Chain *field_0_pPrev;
  struct Actor_demothrd_0x78_Chain *field_4_pNext;
  char field_8_fileNameBuffer[4]; // union, also an int
  GV_ACT *field_C_actor1;
  GV_ACT *field_10_actor2;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  int field_48;
  int field_4C;
  short field_50;
  short field_52;
  short field_54;
  short field_56;
  MATRIX field_58;
} Actor_demothrd_0x78_Chain;
STATIC_ASSERT_SIZE(Actor_demothrd_0x78_Chain, 0x78);

typedef struct Actor_demothrd
{
    GV_ACT              field_0_actor;
    int                field_20_flag;
    int                field_24_ticks;
    int                field_28_map;
    int                field_2C_timer_ticks;
  demothrd_0x1C *field_30_dmo_header;
  dmo_model_0x1A4 *field_34_pModels;
  Actor_demothrd_0x78_Chain field_38;
  int field_B0;
  int field_B4;
  int field_B8;
  int field_BC;
  demothrd_0x1C *field_C0_pHeader;
  CONTROL field_C4_ctrl;
  OBJECT field_140_obj;
  int field_164;
  int field_168;
  int field_16C;
  int field_170;
  int field_174;
  int field_178;
  int field_17C;
  int field_180;
  int field_184;
  int field_188;
  int field_18C;
  int field_190;
  int field_194;
  int field_198;
  int field_19C;
  int field_1A0;
  int field_1A4;
  int field_1A8;
  int field_1AC;
  int field_1B0;
  int field_1B4;
  int field_1B8;
  int field_1BC;
  int field_1C0;
  int field_1C4;
  int field_1C8;
  int field_1CC;
  int field_1D0;
  int field_1D4;
  int field_1D8;
  int field_1DC;
  int field_1E0;
  int field_1E4;
  int field_1E8;
  int field_1EC;
  int field_1F0;
  int field_1F4;
  int field_1F8;
  int field_1FC;
  int field_200;
  int field_204;
  int field_208;
  int field_20C;
  int field_210;
  int field_214;
  int field_218;
  int field_21C;
  int field_220;
    MATRIX             field_224_light_mtx;
    int                field_244;
    int                field_248;
    int                field_24C;
    int                field_250;
    int                field_254;
    int                field_258;
    int                field_25C;
    int                field_260;
    int                field_264;
    int                field_268;
    int                field_26C;
    TChanl_Fn                field_270_pOldRenderFn;
    int                field_274_old_game_state_flags;
    GM_Camera      field_278;
    int                field_2F4_old_equipped_item;
    int                field_2F8_old_equipped_weapon;
} Actor_demothrd;

typedef struct dmo_data_0x36
{
    int field_0;
    int field_4_type;

    DG_SVECTOR field_8_vec1;
    DG_SVECTOR field_E_vec2;

    // TODO: Is there a cleaner way to model this structure?
    // Some of the variants are very similar. Once all
    // MakeChara functions are decompiled those fields
    // should be named properly (and maybe it'll be easier
    // to find patterns then).
    union {
        struct
        {
            int   field_14;
            short field_18;
        } variant_0x3;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x4;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x5;

        struct
        {
            short field_14;
        } variant_0x6;

        struct
        {
            short field_14;
        } variant_0x7;

        struct
        {
            short field_14;
        } variant_0x9;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
        } variant_0xA;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0xC;

        struct
        {
            int     field_14;
            SVECTOR field_18;
            short   field_20;
            short   field_22;
            short   field_24;
            short   field_26;
        } variant_0xE;

        struct
        {
            short field_14;
        } variant_0xF;

        struct
        {
            int field_14;
            int field_18;
            int field_1C;
            int field_20;
            int field_24;
            int field_28;
            int field_2C;
            int field_30;
        } variant_0x10;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
        } variant_0x12;

        struct
        {
            short field_14;
        } variant_0x13;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x14;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x15;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
        } variant_0x17;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x18;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
        } variant_0x19;

        struct
        {
            int field_14;
        } variant_0x1A;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x1B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
        } variant_0x1C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x1D;

        struct
        {
            short field_14;
        } variant_0x1E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
            short field_20;
        } variant_0x20;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x21;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x22;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
        } variant_0x23;

        struct
        {
            short field_14;
        } variant_0x24;

        struct
        {
            short field_14;
        } variant_0x25;

        struct
        {
            DG_OBJS *field_14;
            int      field_18;
        } variant_0x26;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x28;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x29;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x2A;

        struct
        {
            short field_14;
        } variant_0x2B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
        } variant_0x2C;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
            short field_22;
        } variant_0x2D;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
        } variant_0x2E;

        struct
        {
            short field_14;
        } variant_0x2F;

        struct
        {
            int   field_14;
            int   field_18;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
        } variant_0x34;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
        } variant_0x35;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x36;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
        } variant_0x37;

        struct
        {
            short field_14;
        } variant_0x39;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
        } variant_0x3A;

        struct
        {
            int   field_14;
            int   field_18;
            int   field_1C;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
        } variant_0x3B;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
            short field_34;
        } variant_0x3C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3D;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x3E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3F;

        struct
        {
            short field_14;
        } variant_0x41;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x42;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x43;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x44;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x45;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x46;

        struct
        {
            short field_14;
        } variant_0x49;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
        } variant_0x4A;
    } data;
} dmo_data_0x36;

#define stru_80700000 ((demothrd_80700000 *)0x80700000)

typedef struct demothrd_80700000 {
    int field_0;
    int field_4;
    int field_8;
} demothrd_80700000;

int  DM_ThreadStream_80079460(int flag, int unused);
int  DM_ThreadFile_800794E4(int param_1, int param_2);
void demothrd_cd_act_80079664(Actor_demothrd *pActor);
void demothrd_cd_stream_die_800797CC(Actor_demothrd *pActor);
int  DestroyDemo_8007A66C(Actor_demothrd *pActor);
void FS_EnableMemfile_800799A8(int cache_read_enable, int clear_cache_buffer);
void demothrd_remove_via_id_8007CD60(Actor_demothrd *pThis, int id_to_remove);

#endif // _DEMOTHRD_H_
