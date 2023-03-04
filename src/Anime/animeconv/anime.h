#ifndef _ANIME_H_
#define _ANIME_H_

// "It's like one of my Japanese animes..."

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/GM_Control.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "data/data/data.h"

typedef struct anime_0x34
{
    int            field_0_counter;
    int            field_4;
    SVECTOR        field_8_vec;
    char           field_10_r;
    char           field_11_g;
    char           field_12_b;
    unsigned char  field_13; // some countr
    unsigned char *field_14; // loop/jump target?
    unsigned char *field_18_op_code;
    short          field_1C[2]; // todo: might be biggr
    int            field_20;
    unsigned char *field_24_saved_op_code[2]; // todo: might be bigger
    int            field_2C;
    int            field_30;
} anime_0x34;

typedef struct Actor_anime
{
    GV_ACT         field_0_actor;
    DG_TEX       *field_20_pTexture;
    DG_PRIM      *field_24_pPrim;
    RECT          field_28_prim_rect;
    MATRIX       *field_30_mtx;
    int           field_34_map;
    unsigned char field_38_active_buff;
    char          field_39;
    short         field_3A_data_2;
    short         field_3C_data_4;
    short         field_3E_maybe_data_count;
    short         field_40_data_C;
    short         field_42_count;
    short         field_44_data_A;
    short         field_46;
    SVECTOR      *field_48_pPrimVec;
    anime_0x34    field_4C_items[0];
} Actor_anime;

typedef int (*TAnimeVMFn)(Actor_anime *, int);

typedef struct PRESCRIPT
{
    SVECTOR pos;
    SVECTOR speed;
    short   scr_num;
    short   s_anim;
} PRESCRIPT;

typedef struct ANIMATION
{
    short      field_0_texture_hash;
    short      field_2;
    int        field_4;
    short      field_8_count;
    short      field_A;
    short      field_C;
    short      field_E_xw;
    short      field_10_yh;
    short      field_12_rgb;
    PRESCRIPT *field_14_pre_script;
    void      *field_18_ptr;
} ANIMATION;

Actor_anime *NewAnime_8005FBC8(MATRIX *pMtx, int map, ANIMATION *pAnimData);
Actor_anime *anime_create_8005D604(MATRIX *pMtx);
Actor_anime *anime_create_8005DF50(SVECTOR *v1, SVECTOR *v2);

void   anime_change_prim_8005E7EC(POLY_FT4 *pPrims, DG_TEX *pTexture, int item_f4, Actor_anime *pActor);
int    anime_loader_8005F994(Actor_anime *pActor, int param_2, struct ANIMATION *param_3);
void   anime_act_8005F4AC(Actor_anime *param_1);
void   anime_create_8005E6A4(SVECTOR *pVec);
void   anime_create_8005DE70(MATRIX *pMtx);
void   anime_create_8005D6BC(MATRIX *pMtx, int a2);
void   anime_create_8005D988(MATRIX *a1, MATRIX *a2, int a3);
void   anime_create_8005DDE0(MATRIX *pMtx);

#endif // _ANIME_H_
