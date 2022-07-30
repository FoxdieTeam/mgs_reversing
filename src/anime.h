#ifndef _ANIME_H_
#define _ANIME_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>
#include "libdg.h"
#include "actor.h"
#include "data.h"

typedef struct anime_0x34
{
  int field_0_counter;
  int field_4;
  SVECTOR field_8_vec;
  char field_10_r;
  char field_11_g;
  char field_12_b;
  unsigned char field_13; // some countr
  unsigned char* field_14; // loop/jump target?
  unsigned char *field_18_op_code;
  short field_1C[2]; // todo: might be biggr
  int field_20;
  unsigned char* field_24_saved_op_code[2]; // todo: might be bigger
  int field_2C;
  int field_30;
} anime_0x34;

typedef struct Actor_anime
{
  Actor field_0_actor;
  DG_TEX *field_20_pTexture;
  DG_PRIM *field_24_pPrim;
  RECT field_28_prim_rect;
  MATRIX *field_30_mtx;
  int field_34_map;
  unsigned char field_38_active_buff;
  char field_39;
  short field_3A_data_2;
  short field_3C_data_4;
  short field_3E_maybe_data_count;
  short field_40_data_C;
  short field_42_count;
  short field_44_data_A;
  short field_46;
  SVECTOR *field_48_pPrimVec;
  anime_0x34 field_4C_items[0];
} Actor_anime;

typedef struct anime_data_0x14
{
  SVECTOR field_0_vec;
  SVECTOR field_8_vec;
  short field_10_anim_idx;
  short field_12;
} anime_data_0x14;

// TODO: not used by any code yet
typedef struct anime_item_8
{
  int field_0;
  int field_4;
} anime_item_8;

typedef struct Anim_Data
{
  short field_0_texture_hash;
  short field_2;
  int field_4;
  short field_8_count;
  short field_A;
  short field_C;
  short field_E_xw;
  short field_10_yh;
  short field_12_rgb;
  anime_data_0x14 *field_14;
  void *field_18_ptr;
} Anim_Data;

#endif // _ANIME_H_
