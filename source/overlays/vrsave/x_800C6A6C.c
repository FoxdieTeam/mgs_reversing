// vrsave: VR revision copy of overlays/rank/menu/pocket.c
// (rank_800CD568, rank_800CD688), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>
#include "mts/mts.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

#include "overlays/rank/menu/pocket.h"
#include "overlays/vrsave/vrsave.h"

/*---------------------------------------------------------------------------*/

extern RadioFileModeStru_800ABB7C *vrsave_dword_800D1C24;
extern int                         vrsave_dword_800C1AD0[];

void vrsave_800C66AC( MenuPrim *prim, RadioFileModeStruElem *elem );
void vrsave_800C6978( MenuPrim *prim, RadioFileModeStruElem *elem );

/*---------------------------------------------------------------------------*/

void vrsave_800C6A6C( int idx, int x, int y, int divisor, int idx2 )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk2          *unk;
    RadioFileModeStruElem      *elem;

    rfm = vrsave_dword_800D1C24;
    unk = &rfm->field_c0_array[ idx ];
    elem = &rfm->field_0_array[ idx ];

    unk->field_4 = (const char *)vrsave_dword_800C1AD0[ idx2 ];

    elem->field_8_pFn = vrsave_800C66AC;
    elem->field_C_unk1 = (RadioFileModeUnk1 *)unk;

    if ( idx2 < 0 )
    {
        elem->field_0 = 0;
        return;
    }

    if ( divisor <= 0 )
    {
        unk->field_8 = x * 65536;
        unk->field_10 = y * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_C = ( x * 65536 - unk->field_8 ) / divisor;
        unk->field_14 = ( y * 65536 - unk->field_10 ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_18 = 0x748956;
    elem->field_4 = divisor;
}

void vrsave_800C6B8C( int idx, int x, int y, int divisor, VR_SELECT_INFO *info )
{
    RadioFileModeStru_800ABB7C *rfm;
    RadioFileModeUnk1          *unk;
    RadioFileModeStruElem      *elem;

    rfm = vrsave_dword_800D1C24;
    elem = &rfm->field_0_array[ idx ];
    unk = &rfm->field_220_unk1;

    elem->field_8_pFn = vrsave_800C6978;
    elem->field_C_unk1 = unk;

    if ( divisor <= 0 )
    {
        unk->field_4 = x * 65536;
        unk->field_C = y * 65536;
        elem->field_0 = 2;
    }
    else
    {
        unk->field_8 = ( x * 65536 - unk->field_4 ) / divisor;
        unk->field_10 = ( y * 65536 - unk->field_C ) / divisor;
        elem->field_0 = 1;
    }

    unk->field_14 = (int)info;
    elem->field_4 = divisor;
}
