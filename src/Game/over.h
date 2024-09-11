#ifndef _OVER_H_
#define _OVER_H_

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "strctrl.h"
#include "game.h"

typedef struct _OverWork
{
    GV_ACT   actor;
    short    field_20_seq_anim;     // Sequence value controlling GAME OVER animation
    short    field_22_seq;          // Sequence value controlling when animations/inputs are enabled
    short    field_24_option;       // 0 = CONTINUE, 1 = EXIT
    short    field_26_gradient;     // 64-step sweep controlling color of CONTINUE and EXIT buttons
    short    field_28_can_continue; // Disables continue if Snake dies during the Ocelot torture sequence
    short    field_2a_unused;
    POLY_G4  field_2c_polys[2][12];
    LINE_G2  field_38c_lines[2][120];
    DR_TPAGE field_164c_tpages[2];
    TILE     field_165c_tiles[2];
    DR_TPAGE field_167c_tpages[2];
    DVECTOR  field_168c_directions[120];
} OverWork;

STATIC_ASSERT_SIZE(OverWork, 0x186c);

enum 
{
    OVER_CONTINUE,
    OVER_EXIT,
};

OverWork * over_init_800376F8(int can_continue);

#endif // _OVER_H_
