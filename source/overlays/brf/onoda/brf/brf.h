#ifndef _BRF_H_
#define _BRF_H_

#include "game/game.h"

/* Data table types of b_select.c and b_graph.c */

typedef struct
{
    const char *name;
    int         offset;
    int         size;
} BrfResource;

typedef struct
{
    short type; /* 0: vram files only, 1: vram and main memory files */
    short file;
} BrfLoad;

typedef struct
{
    u_char arg1;
    u_char arg2;
    u_char arg3;
    u_char arg5;
    short  arg6;
    short  arg7;
} BrfCountParam;

typedef struct
{
    int   index; /* poly index */
    short x0, y0;
    short x1, y1;
} BrfPolyRect;

typedef struct
{
    short type;
    short flag;
    short x0, y0;
    short x1, y1;
    int   tex_id;
} BrfLayout;

typedef struct
{
    short time;
    short scene;
} BrfKeyframe;

typedef struct
{
    int         len;
    const char *text;
} BrfText;

/* b_graph.c data (overlay2.c) */
extern short          brf_poly_counts[20];
extern BrfKeyframe   *brf_timelines[19];
extern u_short       *brf_mouth_textures[12];
extern u_short       *brf_blink_textures[3];
extern u_short        brf_800C50E8[6];
extern u_short        brf_800C50F4[6];

extern BrfPolyRect brf_800C35F4[2];
extern BrfPolyRect brf_800C360C[11];
extern BrfPolyRect brf_800C3690[2];
extern BrfPolyRect brf_800C36A8[2];
extern BrfPolyRect brf_800C36C0[9];
extern BrfPolyRect brf_800C372C[2];
extern BrfPolyRect brf_800C3744[3];
extern BrfPolyRect brf_800C3768[4];
extern BrfPolyRect brf_800C3798[1];
extern BrfPolyRect brf_800C37A4[4];
extern BrfPolyRect brf_800C37D4[6];
extern BrfPolyRect brf_800C381C[7];
extern BrfPolyRect brf_800C3870[2];
extern BrfPolyRect brf_800C3888[2];
extern BrfPolyRect brf_800C38A0[6];
extern BrfPolyRect brf_800C38E8[3];
extern BrfPolyRect brf_800C390C[6];
extern BrfPolyRect brf_800C3954[3];
extern BrfPolyRect brf_800C3978[5];
extern BrfPolyRect brf_800C39B4[2];

#endif // _BRF_H_
