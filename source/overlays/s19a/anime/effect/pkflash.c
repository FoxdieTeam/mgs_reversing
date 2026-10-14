#include "anime/animconv/anime.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

/* muzzle flash used by the parked jeep characters (a copy of AN_FamasFlash with its own animation);
   the original file name is unknown */

static const char pkflash_script[] = {
    0x00, 0x07, 0x01, 0x00, 0x05, 0x09, 0x01, 0xF4, 0x02, 0x00, 0x01, 0x0F
};

ANIMATION pkflash_anim = {
    0xC61C,                     // tex
    2,                          // texdev_x
    2,                          // texdev_y
    3,                          // n_anime
    1,                          // n_verts
    300,                        // raise
    1,                          // amb
    800,                        // size_w
    800,                        // size_h
    128,                        // v
    NULL,                       // pre_script
    (char *)pkflash_script      // script
};

void *AN_PkFlash(MATRIX *world)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    int        rnd;

    pre.pos.vx = world->t[0];
    pre.pos.vy = world->t[1];
    pre.pos.vz = world->t[2];
    pre.speed = DG_ZeroVector;

    pre.scr_num = 0;
    pre.s_anim = 0;

    rnd = GV_RandU(16);
    if (rnd >= 5)
    {
        pre.s_anim = 2;
    }
    else if (rnd > 0)
    {
        pre.s_anim = 1;
    }
    else
    {
        pre.s_anim = 0;
    }

    anm = &pkflash_anim;
    anm->pre_script = &pre;

    return NewAnime(NULL, 0, anm);
}
