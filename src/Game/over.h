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
    short    field_22;
    short    field_24;
    short    field_26;
    short    field_28;
    char     field_2a_pad[0x1632];
    TILE     field_165c_tiles[2];
    DR_TPAGE field_167c_tpages[2];
    DVECTOR  field_168c_directions[120];
} Actor_Over;

STATIC_ASSERT_SIZE(Actor_Over, 0x186c);

Actor_Over * over_init_800376F8(int field_28);

#endif // _OVER_H_
