#include "Anime/animeconv/anime.h"
#include "strcode.h"

const char s08b_dword_800E4150[] = {0x0, '3', 0x1, 0x0};
const char s08b_dword_800E4154[] = {0x5, 0x1, 0xfe, 0xc};
const char s08b_dword_800E4158[] = {0x0, 0x4, 0x1, 0xff};
const char s08b_dword_800E415C[] = {'\n', 0x0, '\n', 0x0};
const char s08b_dword_800E4160[] = {'\n', 0x2, 0x0, 0x1};
const char s08b_dword_800E4164[] = {0xd, 0xc, 0x0, ' '};
const char s08b_dword_800E4168[] = {0x1, 0xff, 0x4, 0x0};
const char s08b_dword_800E416C[] = {0x0, 0x0, 0x14, 0x0};
const char s08b_dword_800E4170[] = {0x0, 0x2, 0x0, 0x1};
const char s08b_dword_800E4174[] = {0xd, 0xc, 0x0, '/'};
const char s08b_dword_800E4178[] = {0x8, 0xff, 0xff, 0xff};
const char s08b_dword_800E417C[] = {0x1, 0xff, '\n', 0x0};
const char s08b_dword_800E4180[] = {'\n', 0x0, '\n', 0x2};
const char s08b_dword_800E4184[] = {0x0, 0x1, 0xd, 0xf};

ANIMATION anm_800C3620 = {PCX_SMOKE, 8, 4, 30, 1, 255, 1, 100, 100, 80, NULL, (char *)s08b_dword_800E4150};

extern SVECTOR DG_ZeroVector_800AB39C;

void AN_Unknown_800DCE84(SVECTOR *pos)
{
    PRESCRIPT sp10;

    sp10.pos = *pos;

    sp10.speed = DG_ZeroVector_800AB39C;
    sp10.speed.vx = GV_RandU(4) - 2;
    sp10.speed.vy = GV_RandU(4) - 2;
    sp10.speed.vz = GV_RandU(4) - 2;

    sp10.s_anim = 0;
    anm_800C3620.pre_script = &sp10;
    sp10.scr_num = 0;

    NewAnime_8005FBC8(NULL, NULL, &anm_800C3620);
}