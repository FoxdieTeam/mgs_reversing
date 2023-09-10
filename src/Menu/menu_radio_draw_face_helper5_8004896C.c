#include "Game/game.h"
#include "libdg/libdg.h"
#include "radio.h"

extern int dword_800AB6E0;
int        dword_800AB6E0;

extern int GV_Clock_800AB920;

void menu_radio_draw_face_helper5_8004896C( MenuPrim *pPrim, menu_chara_struct_sub *pChara, int idx )
{
    int        x, y, w, h;
    int        color;
    DR_TPAGE  *pTpage;
    POLY_FT4  *pPoly;
    POLY_FT4  *pPoly2;
    LINE_F2   *pLine;
    int        shade;

    x = (idx == 0) ? 31 : 237;
    y = 30;
    w = 52;
    h = 89;

    if ( pChara->field_6 != 0 )
    {
        if ( ( idx == 0 ) && ( pChara->field_4 == 0 ) && ( pChara->field_6 == 1 ) )
        {
            GM_SeSet2_80032968( 0, 63, 84 ); // Codec open sound
        }

        pChara->field_4 += pChara->field_6;

        if ( pChara->field_4 <= 0 )
        {
            pChara->field_4 = 0;
            pChara->field_6 = 0;
        }

        if ( pChara->field_4 < 5 )
        {
            return;
        }

        h = (pChara->field_4 - 4) * 15;

        if ( h > 89 )
        {
            h = 89;
            pChara->field_6 = 0;
        }
        else
        {
            y += ( 89 - h ) / 2;
        }
    }

    radio_draw_face_frame_800481CC( pPrim, x, y, w, h );

    _NEW_PRIM( pTpage, pPrim );

    setDrawTPage( pTpage, 0, 1, getTPage( 0, 0, 960, 256 ) );
    addPrim( pPrim->mPrimBuf.mOt, pTpage );

    if ( dword_800AB6E0 >= 0 && dword_800AB6E0 < h )
    {
        _NEW_PRIM( pLine, pPrim );

        setXY2(pLine, x, dword_800AB6E0 + y, x + w, dword_800AB6E0 + y);
        LSTORE( ( GV_Clock_800AB920 != 0 ) ? 0x80808 : 0x202020, &pLine->r0 );

        setLineF2( pLine );
        setSemiTrans( pLine, 1 );
        addPrim( pPrim->mPrimBuf.mOt, pLine );
    }

    color = 0x808080;

    if ( pChara->field_A > 0 )
    {
        _NEW_PRIM( pPoly, pPrim );

        shade = ( pChara->field_A << 7 ) / pChara->field_C;

        setUVWH( pPoly, idx * 64, 80, 52, 89 );
        setXYWH( pPoly, x, y, w, h );
        setClut( pPoly, 768, idx + 258 );
        setTPage( pPoly, 1, 1, 896, 256 );
        LSTORE( shade | ( ( shade << 16 ) | ( shade << 8 ) ), &pPoly->r0 );

        setPolyFT4( pPoly );
        setSemiTrans( pPoly, 1 );
        addPrim( pPrim->mPrimBuf.mOt, pPoly );

        shade = 128 - shade;
        color = ( shade << 16 ) | ( shade << 8 ) | shade;
    }

    _NEW_PRIM( pPoly2, pPrim );

    setUVWH( pPoly2, idx * 64, 80, 52, 89 );
    setXYWH( pPoly2, x, y, w, h );
    setClut( pPoly2, 768, idx + 256 );
    setTPage( pPoly2, 1, 1, 960, 256 );
    LSTORE( color, &pPoly2->r0 );

    setPolyFT4( pPoly2 );
    setSemiTrans( pPoly2, 1 );
    addPrim( pPrim->mPrimBuf.mOt, pPoly2 );
}
