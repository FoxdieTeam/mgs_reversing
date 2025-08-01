#include "equip.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/control.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "thing/sight.h"
#include "chara/snake/sna_init.h"
#include "linkvar.h"

extern int    dword_8009F604;

/*---------------------------------------------------------------------------*/
// Night Vision/Thermal Goggles sight

#define EXEC_LEVEL GV_ACTOR_AFTER2

#define NV_GOGGLE_ID        0x9c26  // GV_StrCode("nv_ggle")
#define NV_GOGGLE_SIGHT1    0x8504  // GV_StrCode("nv_ggle1")
#define NV_GOGGLE_SIGHT2    0x8505  // GV_StrCode("nv_ggle2")
#define NV_GOGGLE_SIGHT3    0x8506  // GV_StrCode("nv_ggle3")

#define IR_GOGGLE_ID        0x5425  // GV_StrCode("ir_ggle")
#define IR_GOGGLE_SIGHT1    0x84db  // GV_StrCode("ir_ggle1")
#define IR_GOGGLE_SIGHT2    0x84dc  // GV_StrCode("ir_ggle2")
#define IR_GOGGLE_SIGHT3    0x84dd  // GV_StrCode("ir_ggle3")

#define HUD_DISP_DELAY      6
#define HUD_MOVE_DELAY      10

#define NV_HUD_COLOR        COLOR_RED
#define IR_HUD_COLOR        MAKE_RGB0(65,160,74)

typedef struct _Work
{
    GV_ACT   actor;
    int      type;
    int      field_24;
    int      color;
    DVECTOR  field_2C_4Array[4];
    int      timer;
    TILE_1   field_40_tile1[2][24];
    LINE_F2  field_280_lineF2[2][3];
    POLY_F4  field_2E0_polyF4[2][3];
    DR_TPAGE field_370_dr_tpage[2];
    int      scan_timer;
} Work;

STATIC short word_8009F714[] = {0, 0};

/*---------------------------------------------------------------------------*/

/**
 * @brief Draw the horizontal lines of heading numbers on the overlay.
 *
 * @param work The goggles sight actor.
 */
static void DrawHudNumbers(Work *work)
{
    int r, g, b;
    TILE_1 *tile;
    u_long *ot;

    short a1;
    short a2;
    short a3;
    short a4;

    short var_s0; // last number printed on the overlay (0-32)
    short var_s1;
    short x;

    if (work->timer < HUD_DISP_DELAY)
    {
        return;
    }

    tile = work->field_40_tile1[GV_Clock];
    ot = (u_long *)DG_ChanlOTag(1);
    // TextConfig_Flags_eCentreAlign_02 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
    MENU_Locate(0, 0, 0x122);

    if (work->type == IT_NVG)
    {
        r = GET_R_FROM_RGBA(NV_HUD_COLOR);
        g = GET_G_FROM_RGBA(NV_HUD_COLOR);
        b = GET_B_FROM_RGBA(NV_HUD_COLOR);
    }
    else // thermal goggles
    {
        r = GET_R_FROM_RGBA(IR_HUD_COLOR);
        g = GET_G_FROM_RGBA(IR_HUD_COLOR);
        b = GET_B_FROM_RGBA(IR_HUD_COLOR);
    }

    // set the color of the first person overlay menu
    MENU_Color(r, g, b);

    // PlayerHeading
    a1 = GM_PlayerControl->rot.vy & 0xfff;
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

            tile->x0 = x;
            addPrim(ot, tile);
            tile++;
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
static void DrawHudVector(Work *work)
{
    int r, g, b;
    int vy;

    if (work->timer >= HUD_DISP_DELAY)
    {
        MENU_Locate(40, 56, 0x120);

        if (work->type == IT_NVG)
        {
            r = GET_R_FROM_RGBA(NV_HUD_COLOR);
            g = GET_G_FROM_RGBA(NV_HUD_COLOR);
            b = GET_B_FROM_RGBA(NV_HUD_COLOR);
        }
        else
        {
            r = GET_R_FROM_RGBA(IR_HUD_COLOR);
            g = GET_G_FROM_RGBA(IR_HUD_COLOR);
            b = GET_B_FROM_RGBA(IR_HUD_COLOR);
        }
        MENU_Color(r, g, b);
        vy = GM_PlayerControl->rot.vy;
        MENU_Printf("%ld\n",  8 * (vy & 0x07ff));
        MENU_Printf("%ld\n",  4 * (vy & 0x0fff));
        MENU_Printf("%ld\n", 16 * (vy & 0x03ff));
    }
}

static void DrawHudBarGraph(Work *work)
{
    LINE_F2 *line;
    POLY_F4 *poly;
    DR_TPAGE *tpage;
    u_long *ot;
    int y, y2;

    if (work->timer < HUD_DISP_DELAY)
    {
        return;
    }

    line = work->field_280_lineF2[GV_Clock];
    poly = work->field_2E0_polyF4[GV_Clock];
    tpage = &work->field_370_dr_tpage[GV_Clock];

    ot = (u_long *)DG_Chanl(1)->mOrderingTables[GV_Clock];

    y = GM_PlayerControl->rot.vy & 4095;
    y2 = ((y + 1024) & 2047) >> 5;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    poly->y0 = poly->y1 = line->y0 = line->y1 = 140 - y2;

    addPrim(ot, line);
    addPrim(ot, poly);

    line++;
    poly++;

    y2 = (unsigned int)y >> 6;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    poly->y0 = poly->y1 = line->y0 = line->y1 = 140 - y2;

    addPrim(ot, line);
    addPrim(ot, poly);

    line++;
    poly++;

    y2 = ((y - 1024) & 1023) >> 4;

    if (y2 < 32)
    {
        y2 = 64 - y2;
    }

    poly->y0 = poly->y1 = line->y0 = line->y1 = 140 - y2;

    addPrim(ot, line);
    addPrim(ot, poly);
    addPrim(ot, tpage);
}

/**
 * @brief Draw the "SCAN" and "MODE" text on the overlay.
 *
 * @param work The goggles sight actor.
 */
static void DrawHudText(Work *work)
{
    int time;
    int r, g, b;

    if (work->timer >= HUD_DISP_DELAY)
    {
        time = work->scan_timer;
        //  TextConfig_Flags_eLargeFont_10 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
        MENU_Locate(41, 42, 304);
        if (work->type == IT_NVG)
        {
            r = GET_R_FROM_RGBA(NV_HUD_COLOR);
            g = GET_G_FROM_RGBA(NV_HUD_COLOR);
            b = GET_B_FROM_RGBA(NV_HUD_COLOR);
        }
        else
        {
            r = GET_R_FROM_RGBA(IR_HUD_COLOR);
            g = GET_G_FROM_RGBA(IR_HUD_COLOR);
            b = GET_B_FROM_RGBA(IR_HUD_COLOR);
        }
        MENU_Color(r, g, b);

        work->scan_timer++;
        if (work->scan_timer >= 17)
        {
            work->scan_timer = -16;
        }

        if (time > 0)
        {
            MENU_Printf("SCAN");
        }

        MENU_Locate(137, 42, 304);

        if (work->type == IT_NVG)
        {
            MENU_Printf("MODE - B");
        }
        else
        {
            MENU_Printf("MODE - A");
        }
    }
}

static void MoveSightElement(int time, u_short status, DVECTOR *axis, int dir, short sens, short max)
{
    if (time < HUD_MOVE_DELAY)
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

static void Act(Work *work)
{
    short *ptr = word_8009F714;
    int type = work->type;
    int f24 = work->field_24;
    u_short status;
    int time;

    if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
    {
        status = GV_PadData[1].status;
    }
    else
    {
        status = GV_PadData[0].status;
    }

    GM_CheckShukanReverse(&status);

    ptr[0] = 1;

    if (type == IT_NVG && dword_8009F604 != f24)
    {
        NewSight(NV_GOGGLE_SIGHT1, f24, ptr, IT_Scope, NULL);
        NewSight(NV_GOGGLE_SIGHT2, f24, ptr, IT_Scope, (short *)&work->field_2C_4Array[1]);
        NewSight(NV_GOGGLE_SIGHT3, f24, ptr, IT_Scope, (short *)&work->field_2C_4Array[2]);
    }
    else if (dword_8009F604 != f24)
    {
        NewSight(IR_GOGGLE_SIGHT1, f24, ptr, IT_Scope, NULL);
        NewSight(IR_GOGGLE_SIGHT2, f24, ptr, IT_Scope, (short *)&work->field_2C_4Array[1]);
        NewSight(IR_GOGGLE_SIGHT3, f24, ptr, IT_Scope, (short *)&work->field_2C_4Array[2]);
    }

    time = work->timer++;

    if (!(GM_PlayerStatus & PLAYER_NORMAL_WATCH))
    {
        status &= ~(PAD_UP | PAD_DOWN);
    }

    MoveSightElement(time, status, &work->field_2C_4Array[1], 3, 2, 20);
    MoveSightElement(time, status, &work->field_2C_4Array[2], 5, 1, 12);

    // Draw the horizontal lines of heading numbers
    DrawHudNumbers(work);
    // Draw the SCAN and MODE text
    DrawHudText(work);
    // Draw the 3 heading integer indicators
    DrawHudVector(work);
    // Draw the 3 heading vertical lines
    DrawHudBarGraph(work);
}

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    word_8009F714[0] = 0;
}

/*---------------------------------------------------------------------------*/

static void GoggleSightSetup1(Work *work)
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

static void GoggleSightSetup2(Work *actor)
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

void *NewGoggleSight(int type)
{
    Work *work;
    int status, count;
    short *arr;
    short *arr2;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "gglsight.c");

        work->type = type;

        if (type == IT_NVG)
        {
            work->field_24 = NV_GOGGLE_ID;
            work->color = NV_HUD_COLOR;
        }
        else if (type == IT_ThermG)
        {
            work->field_24 = IR_GOGGLE_ID;
            work->color = IR_HUD_COLOR;
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

        work->scan_timer = -16;
        work->timer = 0;

        word_8009F714[0] = 0;

        status = 0;

    cleanup:
        if (status < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
