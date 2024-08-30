#ifndef _DEMOTHRD_H_
#define _DEMOTHRD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
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
  short rot_y;
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

typedef struct dmo_m1e1_data
{
  OBJECT  field_0[2][3];
  int     field_558_idx[2];
  int     field_560;
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
  CONTROL        field_0_ctrl;
  OBJECT         field_7C_obj;
  MATRIX         field_160_mtx[2];
  dmo_m1e1_data *field_1A0_pM1OrHind; // union, can be dmo_hind also, depending on the current stage
} dmo_model_0x1A4;

typedef struct dmo_chain_0x10
{
  int field_0_type;
  int field_4_type;
  int field_8_xy;
  int field_C_zpad;
} dmo_chain_0x10;

typedef struct DemothrdWork_0x78_Chain
{
  struct DemothrdWork_0x78_Chain *field_0_pPrev;
  struct DemothrdWork_0x78_Chain *field_4_pNext;
  char field_8_fileNameBuffer[4]; // union, also an int
  GV_ACT *field_C_actor1;
  GV_ACT *field_10_actor2;
  dmo_chain_0x10 field_14[3];
  int field_44;
  int field_48;
  int field_4C;
  short field_50;
  short field_52;
  short field_54;
  short field_56;
  MATRIX field_58;
} DemothrdWork_0x78_Chain;
STATIC_ASSERT_SIZE(DemothrdWork_0x78_Chain, 0x78);

typedef struct DemothrdWork
{
    GV_ACT             actor;
    int                field_20_flag;
    int                field_24_ticks;
    int                field_28_map;
    int                field_2C_timer_ticks;
    demothrd_0x1C     *field_30_dmo_header;
    dmo_model_0x1A4   *field_34_pModels;
    DemothrdWork_0x78_Chain field_38;
    int                field_B0;
    int                field_B4;
    int                field_B8;
    int                field_BC;
    demothrd_0x1C     *field_C0_pHeader;
    CONTROL            field_C4_ctrl;
    OBJECT             field_140_obj;
    MATRIX             field_224_light_mtx[2];
    int                field_264;
    int                field_268;
    int                field_26C;
    TChanl_Fn          field_270_pOldRenderFn;
    int                field_274_old_game_state_flags;
    GM_Camera          field_278;
    int                field_2F4_old_equipped_item;
    int                field_2F8_old_equipped_weapon;
} DemothrdWork;

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

typedef struct M1E1Work
{
    GV_ACT  actor;
    CONTROL control;
    MATRIX  field_9C_light_matrices[2];
    OBJECT  field_DC;
    OBJECT  field_1C0[3];
    OBJECT  field_46C[3];
    TARGET *field_718_targets[10];
    int     field_740;
    char    field_744[0x61C];
    int     field_D60;
    int     field_D64;
    int     field_D68;
    int     field_D6C;
    char    field_D70[0x1C];
    int     field_D8C;
    char    field_D90[0xD0];
    int     field_E60;
    int     field_E64;
    int     field_E68;
    int     field_E6C;
    int     field_E70;
    int     field_E74;
    int     field_E78;
    int     field_E7C;
    int     field_E80;
    int     field_E84;
    int     field_E88;
    SVECTOR field_E8C;
    SVECTOR field_E94;
    char    field_E9C[0xC4];
    int     field_F60;
    int     field_F64;
    int     field_F68;
    int     field_F6C;
    int     field_F70;
    int     field_F74;
} M1E1Work;

int  DM_ThreadStream_80079460(int flag, int unused);
int  DM_ThreadFile_800794E4(int param_1, int param_2);
void demothrd_cd_act_80079664(DemothrdWork *work);
void demothrd_cd_stream_die_800797CC(DemothrdWork *work);
int  DestroyDemo_8007A66C(DemothrdWork *work);
void demothrd_remove_via_id_8007CD60(DemothrdWork *pThis, int id_to_remove);

#endif // _DEMOTHRD_H_
