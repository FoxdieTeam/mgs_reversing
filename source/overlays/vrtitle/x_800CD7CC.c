// vrtitle: VR revision copy of overlays/rank/menu/pocket.c
// (rank_800CD760, rank_800CD8D8, rank_800CD8F0, rank_800CDA44, rank_800CDB1C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT    actor;
    KCB       kcb;
    int       proc_id;
    int       field_50;
    MenuPrim *prim_ptr;
    MenuPrim  prim;
    char      primbuf[ 2 ][ 0x2000 ];
} Work;

/*---------------------------------------------------------------------------*/

extern RadioFileModeStruElem *vrtitle_dword_800D9D64;

void vrtitle_800CD29C( MenuPrim *prim, RadioFileModeStruElem *elem );
void vrtitle_800CD398( MenuPrim *prim, RadioFileModeStruElem *elem );

/*---------------------------------------------------------------------------*/

void vrtitle_800CD7CC( int idx, int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk1          *unk;
    RadioFileModeStruElem      *elem;

    rfm = (RadioFileModeStru_800ABB7C *)vrtitle_dword_800D9D64;
    elem = &rfm->field_0_array[ idx ];
    unk = &rfm->field_130_array[ idx - 5 ];

    elem->field_8_pFn = vrtitle_800CD29C;
    elem->field_C_unk1 = unk;
    if ( divisor <= 0 )
    {
        unk->field_4 = x0 * 65536;
        unk->field_C = y0 * 65536;
        unk->field_14 = x1 * 65536;
        unk->field_1C = y1 * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x0 * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y0 * 65536 - unk->field_C ) / divisor;
        unk->field_18 = ( x1 * 65536 - unk->field_14 ) / divisor;
        unk->field_20 = ( y1 * 65536 - unk->field_1C ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_24 = 0x3d482e;
    elem->field_4 = divisor;
}

void vrtitle_800CD944( int index )
{
    RadioFileModeStruElem *entry;

    entry = &vrtitle_dword_800D9D64[ index ];
    entry->field_0 = 0;
}

void vrtitle_800CD95C( int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeStruElem      *elem;
    RadioFileModeUnk1          *unk;

    rfm = (RadioFileModeStru_800ABB7C *)vrtitle_dword_800D9D64;
    elem = &rfm->field_0_array[ 11 ];
    unk = (RadioFileModeUnk1 *)&rfm->field_220_unk1.field_18;

    elem->field_8_pFn = vrtitle_800CD398;
    elem->field_C_unk1 = unk;

    if ( divisor <= 0 )
    {
        unk->field_4 = x0 * 65536;
        unk->field_C = y0 * 65536;
        unk->field_14 = x1 * 65536;
        unk->field_1C = y1 * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x0 * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y0 * 65536 - unk->field_C ) / divisor;
        unk->field_18 = ( x1 * 65536 - unk->field_14 ) / divisor;
        unk->field_20 = ( y1 * 65536 - unk->field_1C ) / divisor;
        elem->field_0 = 1;
    }

    elem->field_4 = divisor;
}

void vrtitle_800CDAB0( void *prim )
{
    RadioFileModeStruElem *entry;
    int i;

    entry = vrtitle_dword_800D9D64;
    for ( i = 0; i < 12; i++, entry++ )
    {
        if ( entry->field_0 == 0 ) continue;

        if ( entry->field_4 < 0 )
        {
            entry->field_4++;
        }
        else
        {
            entry->field_8_pFn( prim, entry );
            if ( entry->field_0 == 1 && --entry->field_4 == 0 ) entry->field_0 = 2;
        }
    }
}

void vrtitle_800CDB88( SPRT *sprt )
{
    LSTORE( 0x80808080, &sprt->r0 );
    setSprt( sprt );
    setClut( sprt, 960, 510 );
}
