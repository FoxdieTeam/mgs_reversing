#include "gglsight.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"
#include "psyq.h"
#include "libgcl/hash.h"
#include "Game/linkvarbuf.h"

// night vision goggles / thermal goggles first person

extern int         GV_Clock_800AB920;
extern CONTROL *GM_PlayerControl_800AB9F4;

short word_8009F714[] = {0, 0};

/**
 * @brief Draw the horizontal lines of heading numbers on the overlay.
 *
 * @param work The goggles sight actor.
 */
void gglsight_act_helper_80077A24(GglSightWork *work)
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

    pTile = work->field_40_tile1[GV_Clock_800AB920];
    pOt = DG_ChanlOTag(1);
    // TextConfig_Flags_eCentreAlign_02 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
    MENU_Locate_80038B34(0, 0, 0x122);

    if (work->field_20_type == ITEM_N_V_G)
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
    MENU_Color_80038B4C(r, g, b);

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

            MENU_Locate_80038B34(x, 148, 0x122);
            MENU_Printf_80038C38("%02d", var_s0);

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
void gglsight_act_helper_80077C6C(GglSightWork *work)
{
    int r;  // $a0
    int g;  // $a1
    int b;  // $a2
    int vy; // $s0

    if (work->field_3C >= 6)
    {
        MENU_Locate_80038B34(40, 56, 0x120);

        if (work->field_20_type == ITEM_N_V_G)
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
        MENU_Color_80038B4C(r, g, b);
        vy = GM_PlayerControl_800AB9F4->rot.vy;
        MENU_Printf_80038C38("%ld\n", 8 * (vy & 2047));
        MENU_Printf_80038C38("%ld\n", 4 * (vy & 4095));
        MENU_Printf_80038C38("%ld\n", 16 * (vy & 1023));
    }
}

void gglsight_act_helper_80077D24(GglSightWork *work)
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

    pLine = work->field_280_lineF2[GV_Clock_800AB920];
    pPoly = work->field_2E0_polyF4[GV_Clock_800AB920];
    pTpage = &work->field_370_dr_tpage[GV_Clock_800AB920];

    pOt = DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];

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
 * @brief Draw the scan and mode text on the overlay.
 *
 * @param work The goggles sight actor.
 */
void gglsight_act_helper_80077F70(GglSightWork *work)
{
    int old_380; // $s1
    int r;       // $a0
    int g;       // $a1
    int b;       // $a2

    if (work->field_3C >= 6)
    {
        old_380 = work->field_380;
        //  TextConfig_Flags_eLargeFont_10 | TextConfig_Flags_eSemiTransparent_20 | TextConfig_Flags_eDark_100
        MENU_Locate_80038B34(41, 42, 304);
        if (work->field_20_type == ITEM_N_V_G)
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
        MENU_Color_80038B4C(r, g, b);

        work->field_380++;
        if (work->field_380 >= 17)
        {
            work->field_380 = -16;
        }

        if (old_380 > 0)
        {
            MENU_Printf_80038C38("SCAN"); // scan
        }

        MENU_Locate_80038B34(137, 42, 304);

        if (work->field_20_type == ITEM_N_V_G)
        {
            MENU_Printf_80038C38("MODE - B"); // MODE - B
        }
        else
        {
            MENU_Printf_80038C38("MODE - A"); // MODE - A
        }
    }
}

extern int              GV_PauseLevel_800AB928;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void gglsight_act_helper_80078054(int a1, unsigned short status, DVECTOR *pAxis, int dir, short sens, short max)
{
    if (a1 < 10)
    {
        return;
    }

    if (GV_PauseLevel_800AB928 || (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
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
                    if (pAxis->vx < max)
                    {
                        pAxis->vx += sens;
                    }
                }
                else if (pAxis->vx > -max)
                {
                    pAxis->vx -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (pAxis->vx > -max)
                {
                    pAxis->vx -= sens;
                }
            }
            else if (pAxis->vx < max)
            {
                pAxis->vx += sens;
            }
        }
        else if (pAxis->vx > 0)
        {
            pAxis->vx -= sens;
        }
        else if (pAxis->vx < 0)
        {
            pAxis->vx += sens;
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
                    if (pAxis->vy < max)
                    {
                        pAxis->vy += sens;
                    }
                }
                else if (pAxis->vy > -max)
                {
                    pAxis->vy -= sens;
                }
            }
            else if (dir & 4)
            {
                if (pAxis->vy < max)
                {
                    pAxis->vy += sens;
                }
            }
            else if (pAxis->vy > -max)
            {
                pAxis->vy -= sens;
            }
        }
        else if (pAxis->vy > 0)
        {
            pAxis->vy -= sens;
        }
        else if (pAxis->vy < 0)
        {
            pAxis->vy += sens;
        }
    }
}

extern GV_PAD GV_PadData_800B05C0[4];
extern int    dword_8009F604;

void gglsight_act_80078228(GglSightWork *work)
{
    short *ptr = word_8009F714;
    int type = work->field_20_type;
    int f24 = work->field_24;
    unsigned short status;
    int f3c;

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        status = GV_PadData_800B05C0[1].status;
    }
    else
    {
        status = GV_PadData_800B05C0[0].status;
    }

    GM_CheckShukanReverse_8004FBF8(&status);

    ptr[0] = 1;

    if (type == 5 && dword_8009F604 != f24)
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

    if (!(GM_PlayerStatus_800ABA50 & 8))
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


void gglsight_kill_800783F8(GV_ACT *pActor)
{
    word_8009F714[0] = 0;
}

void gglsight_loader1_80078404(GglSightWork *work)
{
    int     i;
    TILE_1 *pIter = &work->field_40_tile1[0][0];
    for (i = 0; i < 48; i++)
    {
        *(int *)&pIter->r0 = work->field_28_rgb;
        setTile1(pIter);
        pIter->y0 = 144;
        pIter++;
    }
}

void gglsight_loader2_80078444(GglSightWork *actor)
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

        *(int *)&line->r0 = actor->field_28_rgb;

        setLineF2(line);
        setSemiTrans(line, 1);
        line->x0 = pos + 3;
        line->x1 = pos + 6;

        *(int *)&poly->r0 = actor->field_28_rgb;

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

GglSightWork *gglsight_init_80078520(int type)
{
    GglSightWork *actor;
    int             status, count;
    short          *arr;
    short          *arr2;

    actor = (GglSightWork *)GV_NewActor_800150E4(7, sizeof(GglSightWork));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->actor, (TActorFunction)gglsight_act_80078228,
                                  (TActorFunction)gglsight_kill_800783F8, "gglsight.c");

        actor->field_20_type = type;

        if (type == 5)
        {
            actor->field_24 = 0x9c26;
            actor->field_28_rgb = 0xff;
        }
        else if (type == 6)
        {
            actor->field_24 = 0x5425;
            actor->field_28_rgb = 0x4aa041;
        }
        else
        {
            status = -1;
            goto cleanup;
        }

        gglsight_loader1_80078404(actor);
        gglsight_loader2_80078444(actor);

        count = 0;
        arr = (short *)actor;

        // The compiler is optimising this and causing a mismatch if we try to do this cleanly
        for (; count < 4; count++)
        {
            arr2 = &arr[22];
            arr2[0] = 0;
            arr2[1] = 0;
            arr += 2;
            arr2 = arr;
        }

        actor->field_380 = -0x10;
        actor->field_3C = 0;

        word_8009F714[0] = 0;

        status = 0;

    cleanup:
        if (status < 0)
        {
            GV_DestroyActor_800151C8(&actor->actor);
            return NULL;
        }
    }

    return actor;
}
