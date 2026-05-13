#ifndef __MGS_ANIME_H__
#define __MGS_ANIME_H__

// "It's like one of my Japanese animes..."
// 「これじゃ まるでアニメじゃないか」

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct PRESCRIPT
{
    SVECTOR pos;
    SVECTOR speed;
    short   scr_num;
    short   s_anim;
} PRESCRIPT;

typedef struct ANIMATION
{
    u_short    tex;
    short      texdev_x, texdev_y;
    short      n_anime;
    short      n_verts;
    short      raise;
    short      amb;
    short      size_w, size_h;
    short      v;
    PRESCRIPT *pre_script;
    char      *script;
} ANIMATION;

void *NewAnime( MATRIX *world, int map, ANIMATION *animation );
void *NewAnime2( MATRIX *world, int map, ANIMATION *animation );

// TODO: New header
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
