// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D0A24..rank_800D0B54), adapted from the asm.
#include "game/game.h"
#include "overlays/vrtitle/vrpocket.h"

PocketObj *vrtitle_800C3928( int id, int count, int kind, int arg3 );

void vrtitle_800C5324();
void vrtitle_800C5744();
void vrtitle_800C5D3C();
void vrtitle_800C5F3C();
void vrtitle_800C60D8();
void vrtitle_800C6280();
void vrtitle_800C6418();
void vrtitle_800C65B8();

int vrtitle_800C8CFC( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 1, 3, 0, 7 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C5324;
    return 0;
}

int vrtitle_800C8D48( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 2, 1, 0, 6 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C5744;
    return 0;
}

int vrtitle_800C8D94( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 3, 3, 0, 5 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C5D3C;
    return 0;
}

int vrtitle_800C8DE0( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 4, 2, 0, 1 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C5F3C;
    return 0;
}

int vrtitle_800C8E2C( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 5, 2, 0, 2 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C60D8;
    return 0;
}

int vrtitle_800C8E78( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 6, 1, 0, 4 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C6280;
    return 0;
}

int vrtitle_800C8EC4( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 128, 0, 0, 0 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C65B8;
    return 0;
}

int vrtitle_800C8F10( void *work )
{
    PocketObj *obj;

    obj = vrtitle_800C3928( 7, 1, 0, 1 );
    if ( obj == NULL )
    {
        return -1;
    }
    obj->update = vrtitle_800C6418;
    return 0;
}
