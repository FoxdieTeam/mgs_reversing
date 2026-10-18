// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D0B54, rank_800D0BC0 and neighbours), adapted from the asm.
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3928( int id, int count, int kind, int arg3 );

int vrtitle_800C8F5C( void *work );
int vrtitle_800C8EC4( void *work );
int vrtitle_800C8F10( void *work );
int vrtitle_800C8E78( void *work );
int vrtitle_800C8E2C( void *work );
int vrtitle_800C8DE0( void *work );
int vrtitle_800C8D94( void *work );
int vrtitle_800C8D48( void *work );
int vrtitle_800C8CFC( void *work );
void vrtitle_800C6B14();
void vrtitle_800C7318();
void vrtitle_800C74A0();

int vrtitle_800C8FB8( void *work )
{
    if ( vrtitle_800C8F5C( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8EC4( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8F10( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8E78( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8E2C( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8DE0( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8D94( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8D48( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C8CFC( work ) < 0 )
    {
        return -1;
    }
    return 0;
}

int vrtitle_800C9074( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 8, 4, 1, 1 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C6B14;
    return 0;
}

int vrtitle_800C90C0( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 9, 2, 0, 3 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C7318;
    return 0;
}

int vrtitle_800C910C( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 10, 7, 0, 1 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C74A0;
    obj->field_28 = 3;
    return 0;
}

int vrtitle_800C9160( void *work )
{
    if ( vrtitle_800C90C0( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800C910C( work ) < 0 )
    {
        return -1;
    }
    return 0;
}
