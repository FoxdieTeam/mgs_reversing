#include "common.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

static const char anm_fog_data[] = {
    0x00,0x1c,0x01,0x00, 0x05,0x01,0xfe,0x04,
    0x00,0x00,0x01,0x90, 0x00,0x00,0x0c,0x00,
    0x09,0x01,0xff,0x0a, 0x00,0x14,0x00,0x14,
    0x08,0xe7,0xe7,0xe7, 0x02,0x00,0x01,0x0d,
    0x0f,
};

static ANIMATION anm_fog_form = {
    PCX_PCH_FOG,                // field_0_texture_hash
    1,                          // field_2
    1,                          // field_4
    1,                          // n_anims
    1,                          // n_vertices
    800,                        // field_A
    3,                          // field_C
    600,                        // field_E_xw
    600,                        // field_10_yh
    250,                        // field_12_rgb
    NULL,                       // pre_script
    (char *)anm_fog_data        // field_18_ptr
};

/*---------------------------------------------------------------------------*/

void AN_Fog( SVECTOR *pos )
{
    ANIMATION *anm;
    PRESCRIPT  pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.s_anim = 0;

    anm = &anm_fog_form;
    anm->pre_script = &pre;
    pre.scr_num = 0;

    NewAnime( NULL, 0, anm );
}
