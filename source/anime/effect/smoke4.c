#include "mgstype.h"
#include "game/game.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anm_panelsmoke_form_script[] = {
    0x00,0x33,0x01,0x00, 0x05,0x01,0xfe,0x0c, 0x00,0x04,0x01,0xff, 0x0a,0x00,0x0a,0x00,
    0x0a,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x20, 0x01,0xff,0x04,0x00, 0x00,0x00,0x14,0x00,
    0x00,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x2f, 0x08,0xff,0xff,0xff, 0x01,0xff,0x0a,0x00,
    0x0a,0x00,0x0a,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_panelsmoke_form = {
    PCX_SMOKE,                  // tex
    8,                          // texdev_x
    4,                          // texdev_y
    30,                         // n_anime
    1,                          // n_verts
    255,                        // raise
    1,                          // amb
    100,                        // size_w
    100,                        // size_h
    80,                         // v
    NULL,                       // pre_script
    (char *)anm_panelsmoke_form_script // script
};

/*---------------------------------------------------------------------------*/

void AN_PanelSmoke(SVECTOR *pos)
{
    PRESCRIPT pre;

    pre.pos = *pos;

    pre.speed = DG_ZeroVector;
    pre.speed.vx = GV_RandU(4) - 2;
    pre.speed.vy = GV_RandU(4) - 2;
    pre.speed.vz = GV_RandU(4) - 2;

    pre.s_anim = 0;
    anm_panelsmoke_form.pre_script = &pre;
    pre.scr_num = 0;

    NewAnime(NULL, NULL, &anm_panelsmoke_form);
}
