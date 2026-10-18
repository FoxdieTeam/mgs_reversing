// vrsave: VR revision copy of game/sndtst.c
// (NewSoundTest), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgv/libgv.h"

#define SAVEMNGR_WORK_SIZE 0x31C

void vrsave_800CB6F0( void );
void vrsave_800CB9D4( void );
int  vrsave_800CBA1C( GV_ACT *actor, int where, int name );

extern char vrsave_dword_800D173C[]; // "savemngr.c"

void *vrsave_800CBE9C( int name, int where )
{
    GV_ACT *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( GV_ACTOR_AFTER2, SAVEMNGR_WORK_SIZE );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, vrsave_800CB6F0, vrsave_800CB9D4, vrsave_dword_800D173C );

        if ( vrsave_800CBA1C( work, where, name ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }

    return work;
}
