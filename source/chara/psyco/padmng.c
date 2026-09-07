#include "game/game.h"

static int     padmng_alive = 0;
static u_short padmng_mask;

static void Act( GV_ACT *work )
{
    GV_PAD *pad;

    pad = &GV_PadData[ 0 ];
    pad->press &= ~padmng_mask;
    pad->release &= ~padmng_mask;
    pad->status &= ~padmng_mask;

    pad = &GV_PadData[ 1 ];
    pad->press &= ~padmng_mask;
    pad->release &= ~padmng_mask;
    pad->status &= ~padmng_mask;
}

static void Die( GV_ACT *work )
{
    padmng_alive = 0;
}

static int GetResources( GV_ACT *work )
{
    padmng_mask = 0;
    padmng_alive = 1;
    return 0;
}

void *NewPadManager( void )
{
    GV_ACT *work;

    if ( padmng_alive ) return NULL;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(GV_ACT) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "padmng.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}

void SetPadMask( u_short mask )
{
    padmng_mask |= mask;
}

void ClearPadMask( u_short mask )
{
    padmng_mask &= ~mask;
}
