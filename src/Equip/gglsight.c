#include "equip.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"
#include "Game/linkvarbuf.h"
#include "strcode.h"

extern int      GV_Clock;
extern CONTROL *GM_PlayerControl_800AB9F4;

extern int              GV_PauseLevel;
extern PlayerStatusFlag GM_PlayerStatus;

extern GV_PAD GV_PadData_800B05C0[4];
extern int    dword_8009F604;

/*---------------------------------------------------------------------------*/
// Night Vision/Thermal Goggles sight

typedef struct GoggleSightWork
{
    GV_ACT   actor;
    int      type;
    int      field_24;
    int      color;
    DVECTOR  field_2C_4Array[4];
    int      field_3C;
    TILE_1   field_40_tile1[2][24];
    LINE_F2  field_280_lineF2[2][3];
    POLY_F4  field_2E0_polyF4[2][3];
    DR_TPAGE field_370_dr_tpage[2];
    int      field_380;
} GoggleSightWork;

#define EXEC_LEVEL 7

short word_8009F714[] = {0, 0};

/*---------------------------------------------------------------------------*/

/**
 * @brief Draw the horizontal lines of heading numbers on the overlay.
 *
 * @param work The goggles sight actor.
 */
STATIC void gglsight_act_helper_80077A24(GoggleSightWork *work)
{
    int r, g, b;
    TILE_1 *pTile;
    unsigned char *pOt;

    short a1;
    short a2;
    short a3;
    short a4;

    short var_s0; // last number printed on the overlay (0-32)
    short var_s1;
    short x;

    if (work->field_3C < 6)
    {
        return;
    }

    pTile = work->field_40_tile1[GV_Clock];
    pOt = DG_ChanlOTag(1);
    // TextConfig_Flags_eCentreAlign_02 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
    MENU_Locate(0, 0, 0x122);

    if (work->type == ITEM_N_V_G)
    {
        r = 255;
        g = 0;
        b = 0;
    }
    else // thermal goggles
    {
        r = 65;
        g = 160;
        b = 74;
    }

    // set the color of the first person overlay menu
    MENU_Color(r, g, b);

    // PlayerHeading
    a1 = GM_PlayerControl_800AB9F4->rot.vy & 0xfff;
    a2 = a1 / 64;
    a3 = a1 % 64;
    a4 = ((a3 * 24) / 64) + 160;
    x = a4 - ((a4 / 24) * 24);
    var_s1 = a2 + (a4 / 24);

    while (x < 300)
    {
        if (x >= 20)
        {
            var_s0 = var_s1 - 64;

            if (var_s1 < 65)
            {
                if (var_s1 < 0)
                {
                    var_s0 = -var_s1;
                }
                else
                {
                    var_s0 = var_s1;

                    if (var_s1 > 32)
                    {
                        var_s0 = 64 - var_s1;
                    }
                }
            }

            MENU_Locate(x, 148, 0x122);
            MENU_Printf("%02d", var_s0);

            pTile->x0 = x;
            addPrim(pOt, pTile);
            pTile++;
        }

        x += 24;
        var_s1--;
    }
}

/**
 * @brief Draw the 3 numbers on the overlay based on the player's heading.
 *
 * @param work the goggles sight work actor.
 */
STATIC void gglsight_act_helper_80077C6C(GoggleSightWork *work)
{
    int r;  // $a0
    int g;  // $a1
    int b;  // $a2
    int vy; // $s0

    if (work->field_3C >= 6)
    {
        MENU_Locate(40, 56, 0x120);

        if (work->type == ITEM_N_V_G)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else
        {
            r = 65;
            g = 160;
            b = 74;
        }
        MENU_Color(r, g, b);
        vy = GM_PlayerControl_800AB9F4->rot.vy;
        MENU_Printf("%ld\n", 8 * (vy & 2047));
        MENU_Printf("%ld\n", 4 * (vy & 4095));
        MENU_Printf("%ld\n", 16 * (vy & 1023));
    }
}

STATIC void gglsight_act_helper_80077D24(GoggleSightWork *work)
{
    LINE_F2 *pLine;
    POLY_F4 *pPoly;
    DR_TPAGE *pTpage;
    unsigned char *pOt;
    int y, y2;

    if (work->field_3C < 6)
    {
        return;
    }

    pLine = work->field_280_lineF2[GV_Clock];
    pPoly = work->field_2E0_polyF4[GV_Clock];
    pTpage = &work->field_370_dr_tpage[GV_Clock];

    pOt = DG_Chanl(1)->mOrderingTables[GV_Clock];

    y = GM_PlayerControl_800AB9F4->rot.vy & 4095;
    y2 = ((y + 1024) & 2047) >> 5;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    pPoly->y0 = pPoly->y1 = pLine->y0 = pLine->y1 = 140 - y2;

    addPrim(pOt, pLine);
    addPrim(pOt, pPoly);

    pLine++;
    pPoly++;

    y2 = (unsigned int)y >> 6;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    pPoly->y0 = pPoly->y1 = pLine->y0 = pLine->y1 = 140 - y2;

    addPrim(pOt, pLine);
    addPrim(pOt, pPoly);

    pLine++;
    pPoly++;

    y2 = ((y - 1024) & 1023) >> 4;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    pPoly->y0 = pPoly->y1 = pLine->y0 = pLine->y1 = 140 - y2;

    addPrim(pOt, pLine);
    addPrim(pOt, pPoly);
    addPrim(pOt, pTpage);
}

/**
 * @brief Draw the "SCAN" and "MODE" text on the overlay.
 *
 * @param work The goggles sight actor.
 */
STATIC void gglsight_act_helper_80077F70(GoggleSightWork *work)
{
    int old_380; // $s1
    int r;       // $a0
    int g;       // $a1
    int b;       // $a2

    if (work->field_3C >= 6)
    {
        old_380 = work->field_380;
        //  TextConfig_Flags_eLargeFont_10 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
        MENU_Locate(41, 42, 304);
        if (work->type == ITEM_N_V_G)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else
        {
            r = 65;
            g = 160;
            b = 74;
        }
        MENU_Color(r, g, b);

        work->field_380++;
        if (work->field_380 >= 17)
        {
            work->field_380 = -16;
        }

        if (old_380 > 0)
        {
            MENU_Printf("SCAN"); // scan
        }

        MENU_Locate(137, 42, 304);

        if (work->type == ITEM_N_V_G)
        {
            MENU_Printf("MODE - B"); // MODE - B
        }
        else
        {
            MENU_Printf("MODE - A"); // MODE - A
        }
    }
}

STATIC void gglsight_act_helper_80078054(int a1, unsigned short status, DVECTOR *axis, int dir, short sens, short max)
{
    if (a1 < 10)
    {
        return;
    }

    if (GV_PauseLevel || (GM_PlayerStatus & PLAYER_PAD_OFF))
    {
        status = 0;
    }

    if (dir & 1)
    {
        if (status & (PAD_LEFT | PAD_RIGHT))
        {
            if (status & PAD_RIGHT)
            {
                if (!(dir & 4))
                {
                    if (axis->vx < max)
                    {
                        axis->vx += sens;
                    }
                }
                else if (axis->vx > -max)
                {
                    axis->vx -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (axis->vx > -max)
                {
                    axis->vx -= sens;
                }
            }
            else if (axis->vx < max)
            {
                axis->vx += sens;
            }
        }
        else if (axis->vx > 0)
        {
            axis->vx -= sens;
        }
        else if (axis->vx < 0)
        {
            axis->vx += sens;
        }
    }

    if (dir & 2)
    {
        if (status & (PAD_DOWN | PAD_UP))
        {
            if (status & PAD_DOWN)
            {
                if (!(dir & 4))
                {
                    if (axis->vy < max)
                    {
                        axis->vy += sens;
                    }
                }
                else if (axis->vy > -max)
                {
                    axis->vy -= sens;
                }
            }
            else if (dir & 4)
            {
                if (axis->vy < max)
                {
                    axis->vy += sens;
                }
            }
            else if (axis->vy > -max)
            {
                axis->vy -= sens;
            }
        }
        else if (axis->vy > 0)
        {
            axis->vy -= sens;
        }
        else if (axis->vy < 0)
        {
            axis->vy += sens;
        }
    }
}

/*---------------------------------------------------------------------------*/

STATIC void GoggleSightAct(GoggleSightWork *work)
{
    short *ptr = word_8009F714;
    int type = work->type;
    int f24 = work->field_24;
    unsigned short status;
    int f3c;

    if (GM_PlayerStatus & PLAYER_USING_CONTROLLER_PORT_2)
    {
        status = GV_PadData_800B05C0[1].status;
    }
    else
    {
        status = GV_PadData_800B05C0[0].status;
    }

    GM_CheckShukanReverse(&status);

    ptr[0] = 1;

    if (type == ITEM_N_V_G && dword_8009F604 != f24)
    {
        NewSight_80071CDC(SGT_NV_GGLE1, f24, ptr, 1, 0);
        NewSight_80071CDC(SGT_NV_GGLE2, f24, ptr, 1, (short *)&work->field_2C_4Array[1]);
        NewSight_80071CDC(SGT_NV_GGLE3, f24, ptr, 1, (short *)&work->field_2C_4Array[2]);
    }
    else if (dword_8009F604 != f24)
    {
        NewSight_80071CDC(SGT_IR_GGLE1, f24, ptr, 1, 0);
        NewSight_80071CDC(SGT_IR_GGLE2, f24, ptr, 1, (short *)&work->field_2C_4Array[1]);
        NewSight_80071CDC(SGT_IR_GGLE3, f24, ptr, 1, (short *)&work->field_2C_4Array[2]);
    }

    f3c = work->field_3C++;

    if (!(GM_PlayerStatus & 8))
    {
        status &= 0xafff;
    }

    gglsight_act_helper_80078054(f3c, status, &work->field_2C_4Array[1], 3, 2, 20);
    gglsight_act_helper_80078054(f3c, status, &work->field_2C_4Array[2], 5, 1, 12);

    // Draw the horizontal lines of heading numbers
    gglsight_act_helper_80077A24(work);
    // Draw the SCAN and MODE text
    gglsight_act_helper_80077F70(work);
    // Draw the 3 heading integer indicators
    gglsight_act_helper_80077C6C(work);
    // Draw the 3 heading vertical lines
    gglsight_act_helper_80077D24(work);
}

STATIC void GoggleSightDie(GoggleSightWork *work)
{
    word_8009F714[0] = 0;
}

STATIC void GoggleSightSetup1(GoggleSightWork *work)
{
    int     i;
    TILE_1 *tile = &work->field_40_tile1[0][0];

    for (i = 0; i < 48; i++)
    {
        *(int *)&tile->r0 = work->color;
        setTile1(tile);
        tile->y0 = 144;
        tile++;
    }
}

STATIC void GoggleSightSetup2(GoggleSightWork *actor)
{
    int pos, count;

    DR_TPAGE *tpage;
    LINE_F2  *line;
    POLY_F4  *poly;

    tpage = actor->field_370_dr_tpage;
    line = actor->field_280_lineF2[0];
    poly = actor->field_2E0_polyF4[0];
    pos = 40;

    for (count = 0; count < 6; count++) {
        if (count == 3) pos = 40;

        *(int *)&line->r0 = actor->color;

        setLineF2(line);
        setSemiTrans(line, 1);
        line->x0 = pos + 3;
        line->x1 = pos + 6;

        *(int *)&poly->r0 = actor->color;

        setPolyF4(poly);
        setSemiTrans(poly, 1);
        poly->x2 = pos;
        poly->x0 = pos;
        poly->x3 = pos + 3;
        poly->x1 = pos + 3;
        poly->y3 = 0x8c;
        poly->y2 = 0x8c;

        line++;
        poly++;

        pos += 12;
    }

    SetDrawTPage(&tpage[0], 0, 1, 32);
    SetDrawTPage(&tpage[1], 0, 1, 32);
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewGoggleSight(int type)
{
    GoggleSightWork *work;
    int status, count;
    short *arr;
    short *arr2;

    work = (GoggleSightWork *)GV_NewActor(EXEC_LEVEL, sizeof(GoggleSightWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)GoggleSightAct,
                         (GV_ACTFUNC)GoggleSightDie, "gglsight.c");

        work->type = type;

        if (type == ITEM_N_V_G)
        {
            work->field_24 = 0x9c26;
            work->color = 0xff;
        }
        else if (type == ITEM_THERM_G)
        {
            work->field_24 = 0x5425;
            work->color = 0x4aa041;
        }
        else
        {
            status = -1;
            goto cleanup;
        }

        GoggleSightSetup1(work);
        GoggleSightSetup2(work);

        count = 0;
        arr = (short *)work;

        // The compiler is optimising this and causing a mismatch if we try to do this cleanly
        for (; count < 4; count++)
        {
            arr2 = &arr[22];
            arr2[0] = 0;
            arr2[1] = 0;
            arr += 2;
            arr2 = arr;
        }

        work->field_380 = -0x10;
        work->field_3C = 0;

        word_8009F714[0] = 0;

        status = 0;

    cleanup:
        if (status < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (GV_ACT *)work;
}
