#include "common.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "strcode.h"

const char s00a_dword_800E0288[] = {
    0x0, 0x1c, 0x1, 0x0,
    0x5, 0x1, 0xfe, 0x4,
    0x0, 0x0, 0x1, 0x90,
    0x0, 0x0, 0xc, 0x0,
    0x9, 0x1, 0xff, '\n',
    0x0, 0x14, 0x0, 0x14,
    0x8, 0xe7, 0xe7, 0xe7,
    0x2, 0x0, 0x1, 0xd,
    0xf,
};

ANIMATION s00a_dword_800C3490 = { PCX_PCH_FOG, 1, 1,  1, 1, 800, 3, 600, 600, 250, 0, (char *)s00a_dword_800E0288 };

void AN_Fog_800CA618( SVECTOR *pos )
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;

    anm = &s00a_dword_800C3490;
    anm->pre_script = &pre;
    pre.scr_num = 0;

    NewAnime( NULL, 0, anm );
}
