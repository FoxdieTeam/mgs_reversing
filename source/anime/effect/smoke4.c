#include "common.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anm_panel_smoke_data[] = {
    0x00,0x33,0x01,0x00, 0x05,0x01,0xfe,0x0c,
    0x00,0x04,0x01,0xff, 0x0a,0x00,0x0a,0x00,
    0x0a,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x20,
    0x01,0xff,0x04,0x00, 0x00,0x00,0x14,0x00,
    0x00,0x02,0x00,0x01, 0x0d,0x0c,0x00,0x2f,
    0x08,0xff,0xff,0xff, 0x01,0xff,0x0a,0x00,
    0x0a,0x00,0x0a,0x02, 0x00,0x01,0x0d,0x0f
};

static ANIMATION anm_panel_smoke = {
    PCX_SMOKE,                      // field_0_texture_hash
    8,                              // field_2
    4,                              // field_4
    30,                             // n_anims
    1,                              // n_vertices
    255,                            // field_A
    1,                              // field_C
    100,                            // field_E_xw
    100,                            // field_10_yh
    80,                             // field_12_rgb
    NULL,                           // pre_script
    (char *)anm_panel_smoke_data    // field_18_ptr
};

/*---------------------------------------------------------------------------*/

void AN_PanelSmoke(SVECTOR *pos)
{
    PRESCRIPT sp10;

    sp10.pos = *pos;

    sp10.speed = DG_ZeroVector;
    sp10.speed.vx = GV_RandU(4) - 2;
    sp10.speed.vy = GV_RandU(4) - 2;
    sp10.speed.vz = GV_RandU(4) - 2;

    sp10.s_anim = 0;
    anm_panel_smoke.pre_script = &sp10;
    sp10.scr_num = 0;

    NewAnime(NULL, NULL, &anm_panel_smoke);
}
