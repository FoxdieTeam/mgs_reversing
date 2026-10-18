// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D0DA0), adapted from the asm.
#include "libgv/libgv.h"
#include "game/game.h"

extern int vrtitle_dword_800D9CF4;
extern int vrtitle_dword_800D9CF8;

extern const char vrtitle_dword_800D8FE4[]; // "vrtitle.c"

void vrtitle_800C8918( GV_ACT *actor );
void vrtitle_800C8A74( GV_ACT *actor );
int  vrtitle_800C94E8( GV_ACT *actor, int arg );

GV_ACT *vrtitle_800C97E0( int name, int arg )
{
    GV_ACT *actor;

    vrtitle_dword_800D9CF4 = 0;
    vrtitle_dword_800D9CF8 = 0;
    GM_GameStatus |= STATE_ALL_OFF;

    actor = GV_NewActor( 1, 0x1A48 );
    if ( actor != NULL )
    {
        GV_SetNamedActor( actor, vrtitle_800C8918, vrtitle_800C8A74, vrtitle_dword_800D8FE4 );
        if ( vrtitle_800C94E8( actor, arg ) < 0 )
        {
            GV_DestroyActor( actor );
            return NULL;
        }
    }
    return actor;
}
