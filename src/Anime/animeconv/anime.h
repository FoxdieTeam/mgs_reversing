#ifndef _ANIME_H_
#define _ANIME_H_

// "It's like one of my Japanese animes..."

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/control.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct anime_0x34
{
    int         field_0_counter;
    int         field_4;
    SVECTOR     center;
    char        field_10_r;
    char        field_11_g;
    char        field_12_b;
    char        field_13; // index into field_1C
    const char *field_14; // loop/jump target?
    const char *field_18_op_code;
    short       field_1C[2]; // todo: might be biggr
    int         field_20;
    const char *field_24_saved_op_code[2]; // todo: might be bigger
    int         field_2C;
    int         field_30;
} anime_0x34;

typedef struct AnimeWork
{
    GV_ACT        field_0_actor;
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
} AnimeWork;

typedef int (*TAnimeVMFn)(AnimeWork *, int);

typedef struct PRESCRIPT
{
    SVECTOR pos;
    SVECTOR speed;
    short   scr_num;
    short   s_anim;
} PRESCRIPT;

typedef struct ANIMATION
{
    unsigned short field_0_texture_hash;
    short          field_2;
    short          field_4;
    short          field_6;
    short          field_8_count;
    short          field_A;
    short          field_C;
    short          field_E_xw;
    short          field_10_yh;
    short          field_12_rgb;
    PRESCRIPT     *field_14_pre_script;
    char          *field_18_ptr;
} ANIMATION;

AnimeWork *NewAnime_8005FBC8(MATRIX *pMtx, int map, ANIMATION *pAnimData);
AnimeWork *anime_create_8005D604(MATRIX *pMtx);
void anime_create_8005DF50(SVECTOR *v1, SVECTOR *v2);
void anime_create_8005E334(MATRIX *pMtx);

void anime_change_prim_8005E7EC(POLY_FT4 *pPrims, DG_TEX *pTexture, int item_f4, AnimeWork *work);
int  anime_loader_8005F994(AnimeWork *work, int param_2, struct ANIMATION *param_3);
void anime_act_8005F4AC(AnimeWork *param_1);
void anime_create_8005E6A4(SVECTOR *pVec);
void anime_create_8005DE70(MATRIX *pMtx);
void anime_create_8005D6BC(MATRIX *pMtx, int a2);
void anime_create_8005D988(MATRIX *a1, MATRIX *a2, int a3);
void anime_create_8005DDE0(MATRIX *pMtx);
void anime_create_8005E508(SVECTOR *pos);
void anime_create_8005E090(SVECTOR *pPos);

int anime_fn_0_8005EC1C(AnimeWork *work, int idx);
int anime_fn_1_8005ED0C(AnimeWork *work, int idx);
int anime_fn_2_8005ED74(AnimeWork *work, int idx);
int anime_fn_3_8005EDDC(AnimeWork *work, int idx);
int anime_fn_4_8005EE44(AnimeWork *work, int idx);
int anime_fn_5_8005EEA4(AnimeWork *work, int idx);
int anime_fn_6_8005EF04(AnimeWork *work, int idx);
int anime_fn_7_8005EFF8(AnimeWork *work, int idx);
int anime_fn_8_8005F0F0(AnimeWork *work, int idx);
int anime_fn_9_8005F180(AnimeWork *work, int idx);
int anime_fn_10_8005F288(AnimeWork *work, int idx);
int anime_fn_11_8005F2F4(AnimeWork *work, int idx);
int anime_fn_12_8005F37C(AnimeWork *work, int idx);
int anime_fn_13_8005F408(AnimeWork *work, int idx);
int anime_fn_14_8005F438(AnimeWork *work, int idx);

#endif // _ANIME_H_
