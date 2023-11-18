#include "libgcl/hash.h"
#include "Anime/animeconv/anime.h"

extern SVECTOR DG_ZeroVector_800AB39C;

const char s00a_dword_800E0288[] = {
    0x00, 0x1c, 0x01, 0x00, 0x05, 0x01, 0xfe, 0x04,
    0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x0c, 0x00,
    0x09, 0x01, 0xff, 0x0a, 0x00, 0x14, 0x00, 0x14,
    0x08, 0xe7, 0xe7, 0xe7, 0x02, 0x00, 0x01, 0x0d,
    0x0f
};

ANIMATION s00a_dword_800C3490 = { PCX_PCH_FOG, 1, 1,  1, 1, 800, 3, 600, 600, 250, 0, (char *)s00a_dword_800E0288 };

void s00a_command_800CA618( SVECTOR *pos )
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;

    anm = &s00a_dword_800C3490;
    anm->field_14_pre_script = &pre;
    pre.scr_num = 0;

    NewAnime_8005FBC8( NULL, 0, anm );
}
