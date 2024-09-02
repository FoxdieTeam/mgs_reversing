#ifndef _ANIME_H_
#define _ANIME_H_

// "It's like one of my Japanese animes..."

#include "libgv/libgv.h"

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

GV_ACT * NewAnime_8005FBC8(MATRIX *pMtx, int map, ANIMATION *pAnimData);
GV_ACT * NewAnime_8005D604(MATRIX *pMtx);

void NewAnime_8005DF50(SVECTOR *v1, SVECTOR *v2);
void NewAnime_8005E334(MATRIX *pMtx);
void NewAnime_8005E6A4(SVECTOR *pVec);
void NewAnime_8005DE70(MATRIX *pMtx);
void NewAnime_8005D6BC(MATRIX *pMtx, int a2);
void NewAnime_8005D988(MATRIX *a1, MATRIX *a2, int a3);
void NewAnime_8005DDE0(MATRIX *pMtx);
void NewAnime_8005E508(SVECTOR *pos);
void NewAnime_8005E090(SVECTOR *pPos);

#endif // _ANIME_H_
