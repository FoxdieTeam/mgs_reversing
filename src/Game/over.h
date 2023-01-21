#ifndef _OVER_H_
#define _OVER_H_

#include "gamestate.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "linker.h"
#include "strctrl.h"
#include "game.h"

typedef struct _Actor_Over
{
    Actor    field_0_actor;
    short    field_20;
    short    field_22_step;         // This seems to be a timer step
    short    field_24_option;       // 0 = CONTINUE, 1 = EXIT
    short    field_26;
    short    field_28_can_continue; // Disables continue if Snake dies during the Ocelot torture sequence
    char     field_2a_pad[0x1632];
    TILE     field_165c_tiles[2];
    DR_TPAGE field_167c_tpages[2];
    DVECTOR  field_168c_directions[120];
} Actor_Over;

enum 
{
    OVER_CONTINUE,
    OVER_EXIT,
};

STATIC_ASSERT_SIZE(Actor_Over, 0x186c);

Actor_Over * over_init_800376F8(int can_continue);

#endif // _OVER_H_
