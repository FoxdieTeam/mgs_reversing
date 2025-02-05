#include "common.h"
#include "libdg/libdg.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

const char s00a_dword_800E0288[] =
{
    0x00, 0x1C, 0x01, 0x00,
    0x05, 0x01, 0xFE, 0x04,
    0x00, 0x00, 0x01, 0x90,
    0x00, 0x00, 0x0C, 0x00,
    0x09, 0x01, 0xFF, 0x0A,
    0x00, 0x14, 0x00, 0x14,
    0x08, 0xE7, 0xE7, 0xE7,
    0x02, 0x00, 0x01, 0x0D,
    0x0f,
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
