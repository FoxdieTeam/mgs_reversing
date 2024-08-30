#include "psyq.h"
#include "radio.h"
#include "Game/game.h"
#include "Game/jimctrl.h"
#include "libdg/libdg.h"
#include "Menu/menuman.h"
#include "mts/taskid.h"

RECT rect_800AB6D8 = {1008, 432, 5, 20};
int  dword_800AB6E0 = 0;

menu_chara_struct *dword_800ABB38;
menu_chara_struct *SECTION(".sbss") dword_800ABB38; // force gp

extern int dword_800ABB3C;
int        dword_800ABB3C;


extern int GV_Clock_800AB920;
extern menu_0x14 stru_800BDA48[ 2 ];

void sub_80048124()
{
    PANEL_TEXTURE pPanelTex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&pPanelTex, 43, 42);
    LoadImage(&rect_800AB6D8, pPanelTex.field_0_pixels);

    rect = rect_800AB6D8;
    rect.w = 16;
    rect.h = 1;
    rect.y += rect_800AB6D8.h;

    LoadImage(&rect, pPanelTex.field_4_word_ptr_pixels);
    dword_800ABB3C = (rect.y << 6) | (rect.x >> 4 & 0x3f);
}

void radio_draw_face_frame_800481CC(MenuPrim *pGlue, int x, int y, int w, int h)
{
    POLY_FT4  *polys[8];
    int        xn, yn;
    int        xend, yend;
    int        size;
    int        i;
    POLY_FT4 * pPoly;
    int        px, py;
    POLY_FT4 **ppPoly;
    POLY_FT4  *pPoly2;
    int        x2, y2;

    x += 3;
    y += 3;
    w -= 7;
    h -= 7;

    if (w < 0)
    {
        return;
    }

    // No idea why it copies x and y
    xn = x;
    yn = y;

    xend = xn + w;
    yend = yn + h;

    size = 9;

    for (i = 0; i < 8; i++)
    {
        _NEW_PRIM(pPoly, pGlue);
        LSTORE(0x80808080, &pPoly->r0);
        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        pPoly->clut = dword_800ABB3C;
        pPoly->tpage = getTPage(0, 1, 960, 256);

        if (i < 4)
        {
            px = (i % 2) * 10 - 64;
            py = (i / 2) * 10 - 80;
            setUVWH(pPoly, px, py, 9, 9);
        }

        addPrim(pGlue->mPrimBuf.mOt, pPoly);
        polys[i] = pPoly;
    }

    polys[0]->x0 = polys[2]->x0 = xn - size;
    polys[1]->x0 = polys[3]->x0 = xend;
    polys[0]->y0 = polys[1]->y0 = yn - size;
    polys[2]->y0 = polys[3]->y0 = yend;

    for (i = 0, ppPoly = polys; i < 4; ppPoly++, i++)
    {
        pPoly2 = *ppPoly;

        x2 = pPoly2->x0;
        y2 = pPoly2->y0;

        pPoly2->x1 = x2 + size;
        pPoly2->y1 = y2;
        pPoly2->x2 = x2;
        pPoly2->y2 = y2 + size;
        pPoly2->x3 = x2 + size;
        pPoly2->y3 = y2 + size;
    }

    setUVWH(polys[4], 201, 176, 1, 9);
    setXYWH(polys[4], xn, yn - size, w, 9);

    setUVWH(polys[5], 201, 186, 1, 9);
    setXYWH(polys[5], xn, yend, w, 9);

    setUVWH(polys[6], 192, 185, 9, 1);
    setXYWH(polys[6], xn - size, yn, 9, h);

    setUVWH(polys[7], 202, 185, 9, 1);
    setXYWH(polys[7], xend, yn, 9, h);
}

void menu_radio_draw_face_helper6_800486A0( menu_chara_struct_sub *a1, int idx )
{
    int v1, v2, result;

    result = jimctrl_helper_80037F68( a1->field_2_chara );

    v2 = result >> 8;
    v1 = a1->field_E == 0;
    if ( v1 && v2 )
    {
        a1->field_E = 1;
    }
    v1 = (char)result;
    a1->field_4C_leftCodecPortraitFrame = v1;
}

void menu_radio_draw_face_helper2_800486F4(menu_chara_struct_sub *pSub, int idx)
{
    face_anim_image *image1;
    face_anim_image *image2;

    image1 = image2 = NULL;
    if (pSub->field_0_animState == 1)
    {
        if (pSub->field_E > 0)
        {
            image2 = pSub->field_14_face_anim.simple_anim->field_8_eyes[(pSub->field_E + 1) / 2 - 1];
            pSub->field_E++;
            if (pSub->field_E > 6)
            {
                pSub->field_E = 0;
            }
        }
        if (pSub->field_4C_leftCodecPortraitFrame > 0)
        {
            image1 = pSub->field_14_face_anim.simple_anim->field_14_mouth[pSub->field_4C_leftCodecPortraitFrame - 1];
        }
        sub_80046B10(pSub->field_14_face_anim.simple_anim->field_4_face, idx);
        if (image1)
        {
            sub_80046B10(image1, idx);
        }
        if (image2)
        {
            sub_80046B10(image2, idx);
        }
    }
}

void menu_radio_draw_face_helper3_800487DC(menu_chara_struct *pStru, int idx)
{
    RECT rect;

    menu_radio_load_palette_80046B74(pStru->field_24_pImgData256, idx);
    rect.x = idx * 32 + 960;
    rect.y = 336;
    rect.w = 26;
    rect.h = 89;

    // TODO: the following code loads
    // an image from a random area of the memory.
    // It looks like this is a trick to quickly get
    // a pseudorandom noise. But, maybe this match is not correct
    // and 0x80010000 should not be hardcoded.
    LoadImage(&rect, (u_long *)(0x80010000 + (rand() % 32) * 0x2000 + GV_Clock_800AB920 * 0x1000));
}

void menu_radio_draw_face_helper4_80048868(MenuPrim *prim, menu_chara_struct_sub *a2, int idx)
{
    LINE_F4 *line_f4;
    short    coord;

    if (a2->field_4 < 5)
    {
        coord = a2->field_4 * 14;
    }
    else
    {
        coord = 54;
    }

    _NEW_PRIM(line_f4, prim);

    LSTORE(0x1a1f13, &line_f4->r0);

    if (idx == 0)
    {
        line_f4->x0 = 83 - coord;
        line_f4->x3 = 83 - coord;
        line_f4->y0 = 30;
        line_f4->y1 = 30;
        coord = 78 - coord;
        line_f4->x1 = coord;
        line_f4->x2 = coord;
        line_f4->y2 = 118;
        line_f4->y3 = 118;
    }
    else
    {
        line_f4->x0 = coord + 236;
        line_f4->x3 = coord + 236;
        line_f4->y0 = 30;
        line_f4->y1 = 30;
        coord = coord + 241;
        line_f4->x1 = coord;
        line_f4->x2 = coord;
        line_f4->y2 = 118;
        line_f4->y3 = 118;
    }

    setLineF4(line_f4);
    addPrim(prim->mPrimBuf.mOt, line_f4);
}

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

static inline void draw_face_anim(menu_chara_struct_sub *a1, int i, menu_chara_struct *chara_struct, MenuPrim *prim)
{
    switch ( a1->field_0_animState )
    {
    case 0:
        return;

    case 1:
        if ( a1->field_A > 0 )
        {
            a1->field_A--;
        }
        else
        {
            if ( stru_800BDA48[ i ].field_2_bTaskWup )
            {
                mts_wup_tsk_8008A540( MTSID_CD_READ );
                stru_800BDA48[ i ].field_2_bTaskWup = 0;
            }
            menu_radio_draw_face_helper6_800486A0( a1, i );
            menu_radio_draw_face_helper2_800486F4( a1, i );
        }
        break;

    case 2:
        if ( a1->field_A > 0 )
        {
            a1->field_A--;
        }
        else if ( a1->field_E < 1 )
        {
            if ( !sub_80046C90( a1, i, a1->field_14_face_anim.full_anim, a1->field_8_animFrameNum + 1 ) &&
                 ( a1->field_E = 0x7000, stru_800BDA48[ i ].field_2_bTaskWup != 0 ) )
            {
                mts_wup_tsk_8008A540( MTSID_CD_READ );
                stru_800BDA48[ i ].field_2_bTaskWup = 0;
            }
        }
        else
        {
            a1->field_E--;
        }
        break;

    case 3: // Static noise effect for radio face, used when deepthroat is talking
        menu_radio_draw_face_helper3_800487DC( chara_struct, i );
    case 4:
    default:
        break;
    }

    menu_radio_draw_face_helper5_8004896C( prim, a1, i );
}

void menu_radio_draw_face_80048DB0( MenuWork *work, menu_chara_struct *chara_struct )
{
    menu_chara_struct_sub *chara_struct_sub;
    MenuPrim              *prim;
    int                    i;

    if ( chara_struct == NULL )
    {
        return;
    }
    if ( !chara_struct->field_1C_radioDatFragment )
    {
        chara_struct->field_3C[ 0 ].field_0_animState = 0;
        chara_struct->field_3C[ 1 ].field_0_animState = 0;
    }
    prim = work->field_20_otBuf;
    dword_800AB6E0 = dword_800AB6E0 + 1;

    if ( dword_800AB6E0 > 0x6d )
    {
        dword_800AB6E0 = 0;
    }
    for ( i = 0; i < 2; i++ )
    {
        chara_struct_sub = &chara_struct->field_3C[ i ];
        menu_radio_draw_face_helper_800470F4( i );
        if ( chara_struct->field_38 != 0 )
        {
            draw_face_anim(chara_struct_sub, i, chara_struct, prim);
        }
        menu_radio_draw_face_helper4_80048868( prim, chara_struct_sub, i );
    }
}

int menu_radio_end_check_80048F98()
{
    int idx;
    for (idx = 0; idx < 2; idx++)
    {
        if ( dword_800ABB38->field_3C[idx].field_4 )
        {
            return 0;
        }

        dword_800ABB38->field_3C[idx].field_0_animState = 0;
    }
    return 1;
}
