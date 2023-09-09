#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "libdg/libdg.h"
#include "psyq.h"

extern int GV_Time_800AB330;

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *stru_800ABB98;

extern short word_800ABB9C;
short        word_800ABB9C;

int gRadioCodecIdx_800AB770 = 0;

Menu_Triangle stru_8009EC44 = {155, 125, 160, 120, 165, 125, 0x80808080};
Menu_Triangle stru_8009EC54 = {156, 212, 160, 216, 164, 212, 0x80808080};

void menu_radio_codec_helper_helper5_8004D628(Actor_MenuMan *pMenuMan, unsigned char *pOt)
{
    TextConfig config;
    char       buffer[32];

    int count;
    RadioCodecStru_800ABB98 *pCodec;

    MenuPrim *pPrim;

    int x, y;
    int i;
    int yend;

    RadioMemory *pMemory;

    int temp_s0;
    int var_a1;
    int var_a3;

    TILE     *pTile;
    SPRT     *pSprt;
    SPRT     *pSprt2;
    DR_TPAGE *pTpage;
    LINE_F2  *pLine;
    LINE_F4  *pLine2;

    int temp;

    if ( (pMenuMan->field_212 == 0) && ((GV_Time_800AB330 % 16) >= 5) )
    {
        if (stru_800ABB98->field_2 > 0)
        {
            menu_draw_triangle_800435EC(pMenuMan->field_20_otBuf, &stru_8009EC44);
        }

        if ((stru_800ABB98->field_2 + 8) < stru_800ABB98->field_4_count)
        {
            menu_draw_triangle_800435EC(pMenuMan->field_20_otBuf, &stru_8009EC54);
        }
    }

    pCodec = stru_800ABB98;
    temp_s0 = stru_800ABB98->field_2;
    count = stru_800ABB98->field_4_count - stru_800ABB98->field_2;
    pPrim = pMenuMan->field_20_otBuf;

    if (count > 8)
    {
        count = 8;
    }

    y = 0;
    x = 0;

    for (i = 0; i < 8; i++)
    {
        if (i < count)
        {
            config.xpos = x + 26;
            config.ypos = y + 136;
            config.colour = 0x643D472E;
            config.flags = 0;

            pMemory = &pCodec->field_10_array[temp_s0 + i];

            sprintf(buffer, "%03d", pMemory->frequency / 100);
            menu_number_draw_string_80042BF4(pPrim, &config, buffer);

            config.xpos = x + 46;

            sprintf(buffer, "%02d", pMemory->frequency % 100);
            menu_number_draw_string_80042BF4(pPrim, &config, buffer);

            _NEW_PRIM(pTile, pPrim);
            LSTORE(config.colour, &pTile->r0);
            setXY0(pTile, x + 44, y + 139);
            setWH(pTile, 1, 2);
            setTile(pTile);
            addPrim(pPrim->mPrimBuf.mOt, pTile);

            _NEW_PRIM(pSprt, pPrim);
            LSTORE(0x80808080, &pSprt->r0);
            setUV0(pSprt, (i & 1) ? 96 : 0, ((i / 2) * 12) + 4);
            setWH(pSprt, 96, 12);
            pSprt->clut = getClut(960, 510);
            setXY0(pSprt, x + 64, y + 133);
            setSprt(pSprt);
            addPrim(pOt, pSprt);

            if ((temp_s0 + i) == pCodec->field_0_idx)
            {
                LSTORE(0x66C0C0C0, &pSprt->r0);

                for (var_a3 = -1; var_a3 < 2; var_a3++)
                {
                    for (var_a1 = -1; var_a1 < 2; var_a1++)
                    {
                        if ((var_a1 != 0) || (var_a3 != 0))
                        {
                            _NEW_PRIM(pSprt2, pPrim);
                            *pSprt2 = *pSprt;
                            LSTORE(0x66606060, &pSprt2->r0);
                            pSprt2->x0 += var_a1;
                            pSprt2->y0 += var_a3;
                            addPrim(pOt, pSprt2);
                        }
                    }
                }
            }

            _NEW_PRIM(pTpage, pPrim);
            setDrawTPage(pTpage, 1, 0, getTPage(0, 1, 960, 256));
            addPrim(pOt, pTpage);
        }

        _NEW_PRIM(pTile, pPrim);
        LSTORE(0x1A1F13, &pTile->r0);
        setXY0(pTile, x + 25, y + 134);
        setWH(pTile, 35, 9);
        setTile(pTile);
        addPrim(pPrim->mPrimBuf.mOt, pTile);

        _NEW_PRIM(pLine, pPrim);

        pLine->x0 = x + 23;
        pLine->x1 = x + 159;

        pLine->y0 = y + 145;
        pLine->y1 = y + 145;

        LSTORE(0x1A1F13, &pLine->r0);
        setLineF2(pLine);
        addPrim(pPrim->mPrimBuf.mOt, pLine);

        _NEW_PRIM(pTile, pPrim);
        LSTORE(0, &pTile->r0);
        setXY0(pTile, x + 22, y + 133);
        setWH(pTile, 138, 16);
        setTile(pTile);
        addPrim(pPrim->mPrimBuf.mOt, pTile);

        x = 138;

        if (i & 1)
        {
            x = 0;

            if (pMenuMan->field_212 > 0)
            {
                temp = y + 20;
                y = temp - pMenuMan->field_212 * 5;
            }
            else
            {
                y += 20;
            }
        }
    }

    yend = y + 136;

    NEW_PRIM(pLine2, pMenuMan);
    LSTORE(0x1A1F13, &pLine2->r0);

    pLine2->x0 = 75;
    pLine2->y0 = 114;

    pLine2->y1 = 114;
    pLine2->x1 = 16;

    pLine2->x2 = 16;
    pLine2->y2 = yend;

    pLine2->y3 = yend;
    pLine2->x3 = 160;

    setLineF4(pLine2);
    addPrim(pOt, pLine2);

    NEW_PRIM(pLine2, pMenuMan);
    LSTORE(0x1A1F13, &pLine2->r0);

    pLine2->x0 = 244;
    pLine2->y0 = 114;

    pLine2->y1 = 114;
    pLine2->x1 = 304;

    pLine2->x2 = 304;
    pLine2->y2 = yend;

    pLine2->y3 = yend;
    pLine2->x3 = 160;

    setLineF4(pLine2);
    addPrim(pOt, pLine2);

    if (word_800ABB9C != 0)
    {
        pMenuMan->field_212 += word_800ABB9C;

        if ( (pMenuMan->field_212 < 1) || (pMenuMan->field_212 > 4) )
        {
            word_800ABB9C = 0;
        }
    }
}
