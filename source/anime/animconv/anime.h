#ifndef __MGS_ANIME_H__
#define __MGS_ANIME_H__

// "It's like one of my Japanese animes..."

#include <sys/types.h>
#include <libgte.h>
#include "libgv/libgv.h"
#include "libdg/libdg.h"

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
    short          n_anims;
    short          n_vertices;
    short          field_A;
    short          field_C;
    short          field_E_xw;
    short          field_10_yh;
    short          field_12_rgb;
    PRESCRIPT     *pre_script;
    char          *field_18_ptr;
} ANIMATION;

void *NewAnime(MATRIX *world, int map, ANIMATION *animation);
void *NewAnime2(DG_PRIM *prim, int map, ANIMATION *animation);

// TODO: figure out better names for these
void *NewAnime_8005D604(MATRIX *pMtx);

void NewAnime_8005DF50(SVECTOR *v1, SVECTOR *v2);
void NewAnime_8005E334(MATRIX *pMtx);
void NewAnime_8005E6A4(SVECTOR *pVec);
void NewAnime_8005DE70(MATRIX *pMtx);
void NewAnime_8005D6BC(MATRIX *pMtx, int a2);
void NewAnime_8005D988(MATRIX *a1, MATRIX *a2, int a3);
void NewAnime_8005DDE0(MATRIX *pMtx);
void NewAnime_8005E508(SVECTOR *pos);
void NewAnime_8005E090(SVECTOR *pPos);

#endif // __MGS_ANIME_H__
