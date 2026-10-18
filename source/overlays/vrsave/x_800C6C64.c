// vrsave: VR revision copy of overlays/rank/menu/pocket.c
// (rank_800CD760, rank_800CD8D8, rank_800CD8F0, rank_800CDA44, rank_800CDB1C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

#include "overlays/rank/menu/pocket.h"

/*---------------------------------------------------------------------------*/

extern RadioFileModeStruElem *vrsave_dword_800D1C24;

void vrsave_800C6734( MenuPrim *prim, RadioFileModeStruElem *elem );
void vrsave_800C6830( MenuPrim *prim, RadioFileModeStruElem *elem );

/*---------------------------------------------------------------------------*/

void vrsave_800C6C64( int idx, int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk1          *unk;
    RadioFileModeStruElem      *elem;

    rfm = (RadioFileModeStru_800ABB7C *)vrsave_dword_800D1C24;
    elem = &rfm->field_0_array[ idx ];
    unk = &rfm->field_130_array[ idx - 5 ];

    elem->field_8_pFn = vrsave_800C6734;
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

void vrsave_800C6DDC( int index )
{
    RadioFileModeStruElem *entry;

    entry = &vrsave_dword_800D1C24[ index ];
    entry->field_0 = 0;
}

void vrsave_800C6DF4( int x0, int y0, int x1, int y1, int divisor )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeStruElem      *elem;
    RadioFileModeUnk1          *unk;

    rfm = (RadioFileModeStru_800ABB7C *)vrsave_dword_800D1C24;
    elem = &rfm->field_0_array[ 11 ];
    unk = (RadioFileModeUnk1 *)&rfm->field_220_unk1.field_18;

    elem->field_8_pFn = vrsave_800C6830;
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

void vrsave_800C6F48( void *prim )
{
    RadioFileModeStruElem *entry;
    int i;

    entry = vrsave_dword_800D1C24;
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

void vrsave_800C7020( SPRT *sprt )
{
    LSTORE( 0x80808080, &sprt->r0 );
    setSprt( sprt );
    setClut( sprt, 960, 510 );
}
