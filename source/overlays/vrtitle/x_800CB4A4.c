// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D0A24 .. rank_800D0B54 second set), adapted from the asm.
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C9C74( int id, int count, int kind, int arg3 );

void vrtitle_800CA3B8();
void vrtitle_800CA780();
void vrtitle_800CACD8();
void vrtitle_800CAE68();

int vrtitle_800CB4A4( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C9C74( 0, 3, 0, 7 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800CA3B8;
    return 0;
}

int vrtitle_800CB4F0( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C9C74( 1, 1, 0, 6 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800CA780;
    return 0;
}

int vrtitle_800CB53C( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C9C74( 2, 3, 0, 5 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800CACD8;
    return 0;
}

int vrtitle_800CB588( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C9C74( 128, 0, 0, 0 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800CAE68;
    return 0;
}

int vrtitle_800CB5D4( void *work )
{
    if ( vrtitle_800CB588( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800CB53C( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800CB4F0( work ) < 0 )
    {
        return -1;
    }
    if ( vrtitle_800CB4A4( work ) < 0 )
    {
        return -1;
    }
    return 0;
}
