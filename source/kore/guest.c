#include "game/game.h"

/*---------------------------------------------------------------------------*/

SVECTOR KORE_GuestPosition;
int     KORE_GuestFlag;

/*---------------------------------------------------------------------------*/

void KORE_InitGuest( void )
{
    KORE_GuestPosition = DG_ZeroVector;
    KORE_GuestFlag = 0;
}

void KORE_UseGuest( void )
{
    /* do nothing */
}
