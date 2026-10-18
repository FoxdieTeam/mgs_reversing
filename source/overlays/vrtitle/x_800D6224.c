// vrtitle: VR revision copy of onoda/change/change.c
// (NewCdChange), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgv/libgv.h"

#define PHOTOSEL_WORK_SIZE 0x49F0

void vrtitle_800D5E5C( void );
void vrtitle_800D5EC0( void );
int  vrtitle_800D61B4( GV_ACT *actor, int where );

extern char vrtitle_dword_800D9C2C[]; // "photosel.c"

void *vrtitle_800D6224( int name, int where )
{
    GV_ACT *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( GV_ACTOR_MANAGER, PHOTOSEL_WORK_SIZE );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, vrtitle_800D5E5C, vrtitle_800D5EC0, vrtitle_dword_800D9C2C );

        if ( vrtitle_800D61B4( work, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }

    return work;
}
