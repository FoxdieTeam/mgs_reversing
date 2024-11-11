#include "common.h"
#include "libgv/libgv.h"
#include "Anime/animeconv/anime.h"
#include "strcode.h"

const char s03c_dword_800D7B34[] = {
    0x0, 0x15, 0x1, 0x0,
    0x5, 0x1, 0xfe, 0xc,
    0x0, 0x7, '\n', 0x0,
    0xc8, 0x0, 0xc8, 0x1,
    0xff, 0x8, 0xf8, 0xf8,
    0xf8, 0x2, 0x0, 0x1,
    0xd, 0xf
};

ANIMATION s03c_dword_800C33DC = {PCX_SMOKE, 8, 4, 30, 1, 0, 2, 1500, 1500, 64, NULL, (char *)s03c_dword_800D7B34};

const char s03c_dword_800D7B50[] = {
    0x0, '6', 0x2, 0x0,
    0x7, 0x0, 0x1c, 0x1,
    0xfe, 0xc, 0x0, 0x7,
    '\n', 0x1, ',', 0x1,
    ',', 0x1, 0xff, 0x8,
    0xf8, 0xf8, 0xf8, 0x2,
    0x0, 0x1, 0xd, 0xf,
    0x1, 0xfe, '\n', 0x1,
    0xf4, 0x1, 0xf4, 0x8,
    0xbe, 0xbe, 0xbe, 0x2,
    0x0, 0x1, 0xc, 0x0,
    0xf, '\n', 0x0, 0xc8,
    0x0, 0xc8, 0x1, 0xff,
    0x8, 0xf0, 0xf0, 0xf0,
    0x2, 0x0, 0x1, 0xd,
    0xf
};

ANIMATION s03c_dword_800C33F8 = {PCX_SMOKE, 8, 4, 30, 1, 0, 1, 800, 800, 64, NULL, (char *)s03c_dword_800D7B50};

void AN_Unknown_800CCA40(SVECTOR *pos)
{
    PRESCRIPT  prescript;
    SVECTOR   *prepos, *speed;
    ANIMATION *anime;

    prepos = &prescript.pos;
    prepos->vx = pos->vx + GV_RandS(512) - 64;
    prepos->vy = pos->vy + GV_RandS(256) - 128;
    prepos->vz = pos->vz;

    speed = &prescript.speed;
    speed->vx = GV_RandS(64);
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anime = &s03c_dword_800C33DC;
    anime->pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, anime);

    if (!(GV_Time & 3))
    {
        prepos->vx = pos->vx + GV_RandS(512) - 64;
        prepos->vy = pos->vy + GV_RandS(256) - 128;
        prepos->vz = pos->vz;

        speed->vx = GV_RandS(64);
        speed->vy = GV_RandS(128) + 64;
        speed->vz = 0;

        prescript.scr_num = 0;
        prescript.s_anim = 0;

        anime = &s03c_dword_800C33F8;
        anime->pre_script = &prescript;
        NewAnime_8005FBC8(NULL, NULL, anime);
    }
}

void AN_Unknown_800CCB84(SVECTOR *pos)
{
    PRESCRIPT prescript;
    SVECTOR  *prepos, *speed;

    prepos = &prescript.pos;
    prepos->vx = pos->vx + GV_RandS(2048);
    prepos->vy = pos->vy;
    prepos->vz = pos->vz + GV_RandS(2048);

    speed = &prescript.speed;
    speed->vx = 0;
    speed->vy = GV_RandU(128) + 64;
    speed->vz = 0;

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    s03c_dword_800C33F8.pre_script = &prescript;

    NewAnime_8005FBC8(NULL, NULL, &s03c_dword_800C33F8);
}
