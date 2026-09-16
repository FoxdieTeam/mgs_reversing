#include "game/game.h"

/*---------------------------------------------------------------------------*/

SVECTOR SECTION(".bss") MERYL_position;
int     SECTION(".bss") MERYL_flag;
int     SECTION(".bss") MERYL_padding;

/*---------------------------------------------------------------------------*/

void ML9_Reset( void )
{
    MERYL_position = DG_ZeroVector;
    MERYL_flag = 0;
}

void ML9_Empty( void )
{
    /* do nothing */
}
