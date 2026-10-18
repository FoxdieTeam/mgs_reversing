// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (no C twin in the main tree, rank overlay asm: rank_800D20B0, rank_800CF288), VR revision adapted from the asm
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C2F0C( void );
void      *vrtitle_800C3028( int count, int flag );

PocketObj *vrtitle_800C3928( int id, int count, int kind, int arg3 )
{
    PocketObj *obj;
    void      *entries;

    obj = vrtitle_800C2F0C();
    if ( obj == NULL )
    {
        return NULL;
    }

    obj->count = count;
    obj->kind = kind;
    obj->field_1C = arg3;

    if ( count > 0 )
    {
        entries = vrtitle_800C3028( count, kind );
        if ( entries == NULL )
        {
            return NULL;
        }
        obj->entries = entries;
    }

    obj->id = id;
    return obj;
}

// Random number in [0, n)
int vrtitle_800C39BC( int n )
{
    int m;
    int t;
    int offset;
    int r;

    t = n;
    m = 1;
    while ( t >= 2 )
    {
        t /= 2;
        m *= 2;
    }
    m *= 2;

    offset = m - n;
    do
    {
        r = GV_RandU( m ) - offset;
    } while ( r < 0 );

    return r;
}
