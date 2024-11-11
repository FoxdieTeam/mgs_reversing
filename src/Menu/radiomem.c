#include <stdio.h>
#include "common.h"
#include "menuman.h"
#include "Game/game.h"
#include "Menu/radio.h"
#include "SD/g_sound.h"

extern RadioMemory gRadioMemory_800BDB38[ RADIO_MEMORY_COUNT ];

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *stru_800ABB98;

extern short gRadioCodecFrequency_800ABB9E;
short        gRadioCodecFrequency_800ABB9E;

extern short word_800ABB9C;
short        word_800ABB9C;

int gRadioCodecIdx_800AB770 = 0;

Menu_Triangle stru_8009EC44 = {155, 125, 160, 120, 165, 125, 0x80808080};
Menu_Triangle stru_8009EC54 = {156, 212, 160, 216, 164, 212, 0x80808080};

RadioMemory       *menu_radio_table_find_8004D380( int frequency )
{
    RadioMemory *contact;
    int          i;

    contact = &gRadioMemory_800BDB38[ 0 ];
    for ( i = 0; i < RADIO_MEMORY_COUNT; i++ )
    {
        if ( contact->frequency == frequency )
        {
            return contact;
        }
        contact++;
    }
    return 0;
}

RadioMemory *menu_radio_table_next_free_8004D3B8( void )
{
    // Try to find a free entry
    return menu_radio_table_find_8004D380( 0 );
}

void menu_radio_compact_free_vars_8004D3D8( void )
{
    RadioMemory *contact, *next;
    int          i, j;

    contact = &gRadioMemory_800BDB38[ 0 ];
    for ( i = 0; i < RADIO_MEMORY_COUNT; i++, contact++ )
    {
        j = i + 1;
        if ( contact->frequency == 0 )
        {
            for ( next = contact + 1; j < RADIO_MEMORY_COUNT; j++, next++ )
            {
                if ( next->frequency != 0 )
                {
                    *contact = *next;
                    next->frequency = 0;
                    break;
                }
            }
            if ( j == RADIO_MEMORY_COUNT )
            {
                return;
            }
        }
    }
}

void sub_8004D4A0(RadioCodecStru_800ABB98 *pStru)
{
    int  i;
    int  field_2;
    int  param_2, param_3;
    int  count;
    KCB *kcb;

    char pad[32]; // unused stack...

    kcb = pStru->field_c_kcb;
    font_clear(kcb);

    field_2 = pStru->field_2;
    count = pStru->field_4_count - field_2;
    if (count > 8)
    {
        count = 8;
    }

    param_3 = 0;
    param_2 = 0;
    for (i = 0; i < count; i++)
    {
        font_draw_string(kcb, param_2, param_3, pStru->field_10_array[i + field_2].name, 2);

        param_2 = 96;
        if (i % 2)
        {
            param_2 = 0;
            param_3 = param_3 + 12;
        }
    }

    font_update(kcb);
}

void sub_8004D580(int pressed)
{
    int                      new_idx;
    RadioCodecStru_800ABB98 *pStru;

    if (pressed != 0)
    {
        GM_SeSet2(0, 0x3f, SE_RADIO_CURSOR);
    }

    pStru = stru_800ABB98;
    stru_800ABB98->field_0_idx += pressed;
    new_idx = stru_800ABB98->field_0_idx;

    if (new_idx < 0 || new_idx >= pStru->field_4_count)
    {
        pStru->field_0_idx -= pressed;
    }
    else if (new_idx < pStru->field_2)
    {
        pStru->field_2 -= 2;
    }
    else if (pStru->field_2 + 8 <= new_idx)
    {
        pStru->field_2 += 2;
    }

    sub_8004D4A0(pStru);
}

void menu_radio_codec_helper_helper5_8004D628(MenuWork *work, unsigned char *pOt)
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

    if ( (work->field_212 == 0) && ((GV_Time % 16) >= 5) )
    {
        if (stru_800ABB98->field_2 > 0)
        {
            menu_draw_triangle_800435EC(work->field_20_otBuf, &stru_8009EC44);
        }

        if ((stru_800ABB98->field_2 + 8) < stru_800ABB98->field_4_count)
        {
            menu_draw_triangle_800435EC(work->field_20_otBuf, &stru_8009EC54);
        }
    }

    pCodec = stru_800ABB98;
    temp_s0 = stru_800ABB98->field_2;
    count = stru_800ABB98->field_4_count - stru_800ABB98->field_2;
    pPrim = work->field_20_otBuf;

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
            _menu_number_draw_string_80042BF4(pPrim, &config, buffer);

            config.xpos = x + 46;

            sprintf(buffer, "%02d", pMemory->frequency % 100);
            _menu_number_draw_string_80042BF4(pPrim, &config, buffer);

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

            if (work->field_212 > 0)
            {
                temp = y + 20;
                y = temp - work->field_212 * 5;
            }
            else
            {
                y += 20;
            }
        }
    }

    yend = y + 136;

    NEW_PRIM(pLine2, work);
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

    NEW_PRIM(pLine2, work);
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
        work->field_212 += word_800ABB9C;

        if ( (work->field_212 < 1) || (work->field_212 > 4) )
        {
            word_800ABB9C = 0;
        }
    }
}

//onwards is definitely radiomem.c
void menu_radio_codec_helper_helper4_8004DE20(MenuWork *work)
{
    RadioCodecStru_800ABB98 *stru_800ABB98_copy;
    RadioMemory             *radioMemoryIter;
    int                      i;
    int                      count;

    init_radio_message_board_80040F74(work);
    stru_800ABB98 = (RadioCodecStru_800ABB98 *)GV_AllocMemory(GV_PACKET_MEMORY0, sizeof(RadioCodecStru_800ABB98));
    stru_800ABB98_copy = stru_800ABB98;
    count = 0;
    i = 0;
    radioMemoryIter = gRadioMemory_800BDB38;

    for (; i < RADIO_MEMORY_COUNT; i++, radioMemoryIter++)
    {
        if (radioMemoryIter->frequency != 0)
        {
            stru_800ABB98_copy->field_10_array[count] = *radioMemoryIter;
            count++;
        }
    }

    stru_800ABB98_copy->field_4_count = count;
    stru_800ABB98_copy->field_0_idx = gRadioCodecIdx_800AB770;
    stru_800ABB98->field_2 = 0;
    stru_800ABB98_copy->field_6 = 2;
    stru_800ABB98_copy->field_8 = 14;
    word_800ABB9C = -1;
    stru_800ABB98->field_c_kcb = work->field_214_font;
    work->field_212 = 4;
    sub_8004D580(0);
    font_set_color(stru_800ABB98->field_c_kcb, 2, 0x1d05, 0);
}

void menu_radio_codec_helper__helper3_sub_8004DF44(void)
{
    GV_FreeMemory(GV_PACKET_MEMORY0, stru_800ABB98);
}

int menu_radio_codec_helper_helper2_8004DF68(MenuWork *work, GV_PAD *pPad)
{
    RadioCodecStru_800ABB98 *pStru;
    int                      pressed;

    pStru = stru_800ABB98;
    pressed = 0;
    if (pPad->status & (PAD_UP | PAD_DOWN))
    {
        if (pPad->status & PAD_UP)
        {
            pressed = -2;
        }
        else
        {
            pressed = 2;
        }
    }
    else if (pPad->status & (PAD_LEFT | PAD_RIGHT))
    {
        if (pPad->status & PAD_LEFT)
        {
            pressed = -1;
        }
        else
        {
            pressed = 1;
        }
    }

    if (pressed != 0)
    {
        if (pStru->field_6 == pressed)
        {
            pStru->field_8--;
            if (pStru->field_8 < 0)
            {
                sub_8004D580(pressed);
                pStru->field_8 = 2;
            }
        }
        else
        {
            sub_8004D580(pressed);
            pStru->field_8 = 10;
            pStru->field_6 = pressed;
        }
    }
    else
    {
        pStru->field_6 = 0;
    }

    if (pPad->press & PAD_CIRCLE)
    {
        gRadioCodecIdx_800AB770 = pStru->field_0_idx;
        gRadioCodecFrequency_800ABB9E = pStru->field_10_array[gRadioCodecIdx_800AB770].frequency;
        word_800ABB9C = 1;
        GM_SeSet2(0, 0x3f, SE_RADIO_SELECT);
    }
    if (pPad->press & PAD_CROSS)
    {
        gRadioCodecFrequency_800ABB9E = -1;
        word_800ABB9C = 1;
        GM_SeSet2(0, 0x3f, SE_RADIO_CANCEL);
    }
    if (word_800ABB9C == 0 && work->field_212 > 4)
    {
        return gRadioCodecFrequency_800ABB9E;
    }
    else
    {
        return 0;
    }
}

void MENU_InitRadioMemory_8004E0EC(void)
{
    RadioMemory *contact;
    int          i;

    contact = &gRadioMemory_800BDB38[0];
    for (i = RADIO_MEMORY_COUNT - 1; i >= 0; i--)
    {
        contact->frequency = 0;
        contact++;
    }
}

void MENU_SetRadioMemory_8004E110(int frequency, const char *name)
{
    RadioMemory *contact;

    if (!(contact = menu_radio_table_find_8004D380(frequency)))
    {
        contact = menu_radio_table_next_free_8004D3B8();
    }

    if (!strcmp(name, "clear"))
    {
        gRadioCodecIdx_800AB770 = 0;
        contact->frequency = 0;
    }
    else
    {
        contact->frequency = frequency;
        strcpy(contact->name, name);
    }

    menu_radio_compact_free_vars_8004D3D8();
}

void menu_radio_codec_helper_helper_8004E198(int toFind)
{
    RadioMemory *contact;

    contact = menu_radio_table_find_8004D380(toFind);
    if (contact)
    {
        gRadioCodecIdx_800AB770 = contact - gRadioMemory_800BDB38;
    }
}
