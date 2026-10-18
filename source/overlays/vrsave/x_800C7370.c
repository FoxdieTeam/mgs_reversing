// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_save_memcard_8004B0A0), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "overlays/vrsave/vrsave.h"

extern int        GV_Clock;
extern int        GV_Time;
extern int        vrsave_dword_800C1AC8; /* index of the selected memory card */
extern DATA_INFO *vrsave_dword_800D1BEC;
extern MEMCARD   *vrsave_dword_800D1C10[2];
extern VR_SELECT_INFO *vrsave_dword_800D1C1C;

extern RECT          vrsave_dword_800D1370;
extern char          vrsave_dword_800D1378[]; // = "RECORD";
extern char          vrsave_dword_800D1380[]; // = "TIME";
extern char          vrsave_dword_800D1388[]; // = "NEW FILE [ NEED %d BLOCK%s ]";
extern char          vrsave_dword_800D13A8[]; // = "S";
extern char          vrsave_dword_800D13AC[]; // = "";
extern char          vrsave_dword_800D13B0[]; // = "FREE: %d BLOCK%s";
extern Menu_Triangle vrsave_dword_800C1AE4;
extern Menu_Triangle vrsave_dword_800C1AF4;

void vrsave_800CA450(int value, char *out);
void vrsave_800C6DF4(int x0, int y0, int x1, int y1, int divisor);
void vrsave_800C7020(SPRT *sprt);

void vrsave_800C7370(MenuWork *work, u_long *ot, VR_SELECT_INFO *info)
{
    TextConfig config;

    RECT rect;
    // FIXME: the original shares this stack slot between the time string
    // and the RECT of the final DrawMove; the union steers the frame layout.
    union
    {
        char str[16];
        RECT rect;
    } scratch;
    char timestr[16];
    char saveid[8];
    char newfile[32];
    char free_text[32];

    LINE_F2   *pLine;
    SPRT      *pSprt;
    TILE      *pTile;
    POLY_FT4  *pPoly;
    DR_TPAGE  *pTpage;
    DR_TPAGE  *pTpage2;
    DR_TPAGE  *pTpage3;
    TILE      *pTile2;
    DR_MOVE   *pMove2;
    DR_MOVE   *pMove;

    int          row;
    int          free_blocks;
    int          num_rows;
    int          top;
    int          spr_u;
    int          spr_v;
    int          width;
    int          row_height;
    VR_MENU_CURPOS *pos;
    MenuPrim       *prim;

    int tpage;
    int blocks;
    int y;
    int i;
    int j;
    int cur_h;
    int line_x;

    int unfold_step;
    int unfold_h;

    // FIXME: x/y origin of the list kept as (constant) variables, steers register allocation
    unsigned int s8;
    unsigned int s6;

    // FIXME: tile size kept in variables (steers constant folding)
    int tile_h, tile_w;

    prim = work->prim;
    s8 = 0;

    if (info->max_num == 0)
    {
        return;
    }

    top = info->top;
    num_rows = info->max_num - info->top;

    s6 = 200;
    if (num_rows > 6)
    {
        num_rows = 6;
    }
    spr_u = 0;
    spr_v = 274;

    y = 80;

    unfold_step = 52;
    unfold_h = 16;

    tile_h = 16;

    if (info->open_count > 0)
    {
        if (--info->open_count >= 5)
        {
            return;
        }

        width = (4 - info->open_count) * unfold_step;
    }
    else
    {
        width = s6 + 10;
    }

    if (info->field_18 > 0)
    {
        row_height = --info->field_18 * (unfold_h / 4);
    }
    else
    {
        row_height = tile_h;
        if (info->field_18 == 0)
        {
            row_height = 0;
        }
    }

    _NEW_PRIM(pTpage, prim);
    setDrawTPage(pTpage, 0, 1, getTPage(0, 1, 960, 256));
    addPrim(prim->ot, pTpage);

    rect = vrsave_dword_800D1370;
    _NEW_PRIM(pMove, prim);
    if (GV_Clock == 0)
    {
        SetDrawMove(pMove, &rect, 0, 200);
    }
    else
    {
        SetDrawMove(pMove, &rect, 320, 200);
    }
    addPrim(prim->ot, pMove);

    tile_w = 210;
    for (row = 0; row < num_rows; row++)
    {
        _NEW_PRIM(pTile, prim);
        LSTORE(0, &pTile->r0);

        setXY0(pTile, s8, s6);
        setWH(pTile, tile_w, tile_h);

        setTile(pTile);
        addPrim(prim->ot, pTile);

        tpage = 293;
        if (GV_Clock == 0)
        {
            tpage = 288;
        }

        _NEW_PRIM(pPoly, prim);
        LSTORE(0x80808080, &pPoly->r0);

        if ((top + row) == info->current)
        {
            cur_h = 16;
        }
        else
        {
            cur_h = row_height;
        }

        pPoly->x0 = 160 - (width / 2);
        pPoly->y0 = y;

        pPoly->x1 = 160 - (width / 2) + width;
        pPoly->y1 = y;

        pPoly->x2 = 160 - (width / 2);
        pPoly->y2 = y + cur_h;

        pPoly->x3 = 160 - (width / 2) + width;
        pPoly->y3 = y + cur_h;

        setUVWH(pPoly, s8, s6, 210, tile_h);

        pPoly->tpage = tpage;

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        addPrim(prim->ot, pPoly);

        if (((top + row) == info->current) && (info->enable != 0))
        {
            vrsave_800C6DF4(160, y + 9, info->height, 16, 2);
        }

        config.color = 0x66748956;
        config.flags = 0;
        y += cur_h;

        if (((unsigned int)info->menu[top + row].num) < 16)
        {
            pos = &info->menu[top + row];

            if (pos->mes[0] == 'R')
            {
                config.xpos = s8 + 165;
                config.ypos = s6 + 3;
                sprintf(timestr, vrsave_dword_800D1378);
                _menu_number_draw_string(prim, &config, timestr);
            }
            else
            {
                config.xpos = s8 + 178;
                config.ypos = s6 + 3;
                _menu_number_draw_string(prim, &config, vrsave_dword_800D1380);
            }

            config.xpos = s8 + 165;
            config.ypos = s6 + 10;

            vrsave_800CA450((short)(pos->mes[2] - 0x40 + (pos->mes[3] - 0x40) * 10 + (pos->mes[4] - 0x40) * 100 +
                                    (pos->mes[5] - 0x40) * 1000),
                            saveid);
            for (j = 0; j < 8; j++)
            {
                scratch.str[j] = saveid[j];
            }
            scratch.str[8] = 0;
            _menu_number_draw_string(prim, &config, scratch.str);
        }
        else
        {
            config.ypos = s6 + 8;
            config.flags = 0x2;
            config.xpos = s8 + (width / 2);
            blocks = vrsave_dword_800D1BEC->blocks_count;
            sprintf(newfile, vrsave_dword_800D1388, blocks,
                    (blocks >= 2) ? vrsave_dword_800D13A8 : vrsave_dword_800D13AC);

            _menu_number_draw_string2(prim, &config, newfile);
        }

        if (row == 6)
        {
            spr_u = 128;
            spr_v = 274;
        }

        _NEW_PRIM(pTpage2, prim);
        setDrawTPage(pTpage2, 0, 1, getTPage(0, 1, 960, 256));
        addPrim(prim->ot, pTpage2);

        _NEW_PRIM(pSprt, prim);
        vrsave_800C7020(pSprt);

        setUV0(pSprt, spr_u, spr_v);
        setWH(pSprt, 160, 14);
        setXY0(pSprt, s8, s6 + 2);

        addPrim(ot, pSprt);

        _NEW_PRIM(pTpage3, prim);
        setDrawTPage(pTpage3, 0, 1, getTPage(0, 1, 896, 256));
        addPrim(prim->ot, pTpage3);

        spr_v += 14;
    }

    _NEW_PRIM(pTile2, prim);
    LSTORE(0, &pTile2->r0);
    setXY0(pTile2, s8, s6);
    setWH(pTile2, tile_w, tile_h);
    setTile(pTile2);
    addPrim(prim->ot, pTile2);

    line_x = -(width + 10) / 2;

    for (i = 0; i < 2; i++)
    {
        _NEW_PRIM(pLine, prim);

        pLine->x0 = pLine->x1 = line_x + 160;
        pLine->y0 = 78;
        pLine->y1 = y + 4;

        LSTORE(0x748956, &pLine->r0);

        setLineF2(pLine);
        setSemiTrans(pLine, 1);
        addPrim(prim->ot, pLine);

        line_x += 10 + width;
    }

    if (info->field_18 < 0)
    {
        free_blocks = vrsave_dword_800D1C10[vrsave_dword_800C1AC8]->free_blocks;

        if (vrsave_dword_800D1C1C->max_num == 1)
        {
            config.xpos = 160;
        }
        else if (vrsave_dword_800C1AC8 == 0)
        {
            config.xpos = 96;
        }
        else
        {
            config.xpos = 224;
        }

        config.ypos = 68;
        config.flags = 0x2;
        config.color = 0x66748956;

        sprintf(free_text, vrsave_dword_800D13B0, free_blocks,
                (free_blocks >= 2) ? vrsave_dword_800D13A8 : vrsave_dword_800D13AC);
        _menu_number_draw_string2(prim, &config, free_text);

        // Blinking effect.
        if ((GV_Time % 32) > 10)
        {
            if (top > 0)
            {
                menu_draw_triangle(work->prim, &vrsave_dword_800C1AE4);
            }

            if ((top + 6) < info->max_num)
            {
                menu_draw_triangle(work->prim, &vrsave_dword_800C1AF4);
            }
        }
    }

    _NEW_PRIM(pMove2, work->prim);
    if (GV_Clock == 0)
    {
        scratch.rect.y = 200;
        scratch.rect.w = 210;
        scratch.rect.x = 0;
        scratch.rect.h = 16;
    }
    else
    {
        scratch.rect.x = 320;
        scratch.rect.y = 200;
        scratch.rect.w = 210;
        scratch.rect.h = 16;
    }
    SetDrawMove(pMove2, &scratch.rect, 430, 240);
    addPrim(work->prim->ot, pMove2);
}
