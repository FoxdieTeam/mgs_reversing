#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "menu/menuman.h"
#include "game/camera.h"
#include "game/object.h"
#include "thing/sight.h"
#include "chara/snake/sna_init.h"
#include "game/object.h"
#include "linkvar.h"
#include "sd/g_sound.h"

extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern int              DG_CurrentGroupID;
extern int              dword_8009F604;
extern GM_CAMERA        GM_Camera;
extern short            dword_800ABBDC;
extern short            dword_800ABBD4;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER2

#define SCOPE_SIGHT     0x51c8  // GV_StrCode("scope")
#define SCOPE_MODEL     GV_StrCode("goggles")

#define HUD_DISP_DELAY  16

#define COLOR_DARK_CYAN     MAKE_RGB0( 46, 65, 65)
#define COLOR_LIGHT_GREEN   MAKE_RGB0(135,177,104)
#define COLOR_DARK_GREEN    MAKE_RGB0( 71,113, 40)

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    short          saved_packs;
    short          saved_raise;
    MAP           *map;
    GV_PAD        *old_pad;
    int            field_58;
    short          hud_delay; // Adds some delay before showing the HUD of the scope.
    short          field_5E; // Initialized with 2 but aparently never read.
    short          field_60; // Value set to 0 and 1 but aparently never read.
    short          field_62; // Some helper for side lines.
    SVECTOR        field_64_vec;
    SVECTOR        field_6C_turn_vec;
    LINE_F2       *side_lines[2]; // Vertical lines on left and right side of the HUD that move when zooming in/out.
    LINE_F4       *rect_lines[2]; // Top, right and bottom border of the moving rectangle in the center of the HUD.
    short          rect_offset[2]; // (x, y) offset of the top left corner of the moving rectangle.
    LINE_F3       *bar_graph[2]; // Vertical lines that "randomly" change their height.
    LINE_F3       *zoom_line[2]; // The horizontal zoom level line on top of the HUD.
    int            zoom_counter; // Used to play the sound when zooming in/out at a fixed rate.
    int            flags;
} Work;

/*---------------------------------------------------------------------------*/

STATIC short scope_created_8009F2C4 = FALSE;

STATIC SVECTOR svecs_8009F2C8[2] = {
    { 0, 0,    0, 0 },
    { 0, 0, 3200, 0 }
};

static void addPrimEX(u_long *ot, void *prim)
{
    if ((GM_PlayerStatus & PLAYER_NOT_SIGHT) == 0)
    {
        addPrim(ot, prim);
    }
}

// If the scope is zoomed in and you move the view towards an object which is
// closer than the zoom level, then the zoom is automatically decreased.
static int GetZoomLimit(Work *work)
{
    MATRIX *eye;
    DG_OBJS *objs;
    int bCalcLen;
    int vecLen;
    MATRIX mtx;
    SVECTOR vecs[2];

    if ( GM_GameStatus < 0 )
    {
        eye = &DG_Chanl(0)->field_30_eye;
    }
    else
    {
        objs = GM_PlayerBody->objs;
        eye = &mtx;
        mtx = GM_PlayerBody->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.eye.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.eye.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.eye.vz;
    }
    DG_SetPos(eye);
    DG_PutVector(svecs_8009F2C8, vecs, 2);
    bCalcLen = 0;
    if ( HZD_LineCheck(work->map->hzd, vecs, &vecs[1], HZD_CHECK_ALL, 0x81) )
    {
        HZD_LineNearVec(&vecs[1]);
        bCalcLen = 1;
    }

    vecLen = 3200;
    if ( bCalcLen != 0 )
    {
        GV_SubVec3(&vecs[1], vecs, vecs);
        vecLen = GV_VecLen3(vecs);
    }

    return vecLen;
}

static void SetSideLinesPairPosition(LINE_F2 *lines, int x, int y)
{
    int offsetIndex;
    lines->x1 = x;
    lines->x0 = x;
    offsetIndex = 4;
    lines[offsetIndex].x1 = 320 - x;
    lines[offsetIndex].x0 = 320 - x;
    lines[offsetIndex].y0 = y;
    lines->y0 = y;
    lines[offsetIndex].y1 = 240 - y; // Bottom y.
    lines->y1 = 240 - y;
}

static void DrawSideLines(LINE_F2 *lines, int param_2)
{
    int i;
    int x;
    int y;

    x = param_2 + 258;
    y = 66 - (param_2 * 9) / 15;

    for (i = 0; i < 4; i++)
    {
        SetSideLinesPairPosition(lines, x, y);
        lines++;
        x += 15;
        y -= 9;
    }
}

static void scope_act_helper_8006258C(Work *work)
{
    int      iVar1;
    int      iVar3;
    int      temp;
    u_long  *ot;
    LINE_F2 *lines;
    int      i;

    temp = work->field_58;

    if (GV_PauseLevel == 0)
    {
        work->field_58++;
    }

    if (temp >= 6)
    {
        temp = 6;
        work->flags |= 1 << GV_Clock;
    }

    iVar1 = 12 * temp;
    iVar3 = 320 - iVar1;

    ot = (u_long *)DG_ChanlOTag(1);
    lines = work->side_lines[GV_Clock];

    for (i = 0; i < 4; i++)
    {
        SetSideLinesPairPosition(lines, iVar3, 66 - (((iVar3 - 258) * 9) / 15));
        addPrimEX(ot, lines);
        addPrimEX(ot, lines + 4);

        iVar3 += iVar1 / 4;
        lines++;
    }
}

static void ManagePadInput(Work *work, unsigned short pad_status)
{
    SVECTOR vec;
    int zoomLevel;
    int iVar5;
    int vx;
    int vy;
    int vxMin;
    int vxMax;
    CONTROL *control;
    short *pRectOffset; // (x, y) offset of the top left corner of the moving rectangle.

    zoomLevel = GM_Camera.zoom;
    pRectOffset = work->rect_offset;

    if (GM_PlayerControl)
    {
        vx = work->field_6C_turn_vec.vx;

        if (vx < dword_800ABBDC)
        {
            vx = dword_800ABBDC;
        }
        else if (vx > dword_800ABBD4)
        {
            vx = dword_800ABBD4;
        }

        work->field_6C_turn_vec.vx = vx;
    }

    if ((pad_status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT)) != 0)
    {
        vx = work->field_6C_turn_vec.vx;
        vy = work->field_6C_turn_vec.vy;

        vec = work->field_64_vec;

        if (GM_PlayerControl)
        {
            vec.vx = GM_PlayerControl->turn.vx;
        }

        if (zoomLevel <= 1023)
        {
            iVar5 = 16;
        }
        else
        {
            if (zoomLevel < 2048)
            {
                iVar5 = 4;
            }
            else
            {
                iVar5 = 1;
            }
        }

        vxMin = vec.vx - 512;
        vxMax = vec.vx + 512;

        if (GM_PlayerControl)
        {
            if (vxMin < dword_800ABBDC)
            {
                vxMin = dword_800ABBDC;
            }

            if (vxMax > dword_800ABBD4)
            {
                vxMax = dword_800ABBD4;
            }
        }

        if ((pad_status & (PAD_UP | PAD_DOWN)) != 0)
        {
            if ((pad_status & PAD_UP) != 0)
            {
                vx -= iVar5;

                if (--pRectOffset[1] < -8)
                {
                    pRectOffset[1] = -8;
                }
            }
            else
            {
                vx += iVar5;

                if (++pRectOffset[1] > 8)
                {
                    pRectOffset[1] = 8;
                }
            }
        }

        if (vx < vxMin)
        {
            vx = vxMin;
        }

        if (vx > vxMax)
        {
            vx = vxMax;
        }

        if ((pad_status & (PAD_LEFT | PAD_RIGHT)) != 0)
        {
            if ((pad_status & PAD_RIGHT) != 0)
            {
                pRectOffset[0]++;

                vy = vy - iVar5;
                vy &= 0xfff;

                if (pRectOffset[0] > 8)
                {
                    pRectOffset[0] = 8;
                }
            }
            else
            {
                pRectOffset[0]--;

                vy = vy + iVar5;
                vy &= 0xfff;

                if (pRectOffset[0] < -8)
                {
                    pRectOffset[0] = -8;
                }
            }
        }

        work->field_6C_turn_vec.vx = vx;
        work->field_6C_turn_vec.vy = vy;
    }
    else if (GV_PauseLevel == 0)
    {
        if (pRectOffset[0] != 0)
        {
            iVar5 = (pRectOffset[0] > 0) ? -1 : 1;
            pRectOffset[0] += iVar5;
        }

        if (pRectOffset[1] != 0)
        {
            iVar5 = (pRectOffset[1] > 0) ? -1 : 1;
            pRectOffset[1] += iVar5;
        }
    }

    control = GM_PlayerControl;

    if (control)
    {
        control->turn = work->field_6C_turn_vec;
        control->rot = control->turn;
    }
}

static void ManageZoom(Work *work, u_long *ot, int pad_status)
{
    short    zoomLineLength;
    int      iVar3;
    int      zoomLevel;
    int      maxZoomLevel;
    LINE_F2 *pSideLine_f2;
    LINE_F3 *pZoomLevelLine_F3;
    int      i;
    int      maxDistance;

    zoomLevel = GM_Camera.zoom;
    pSideLine_f2 = work->side_lines[GV_Clock];
    pZoomLevelLine_F3 = work->zoom_line[GV_Clock];

    maxZoomLevel = 3200;

    if (pad_status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_CROSS | PAD_CIRCLE))
    {
        maxDistance = GetZoomLimit(work);

        if (maxDistance < 3200)
        {
            maxZoomLevel = maxDistance;
        }

        if (maxDistance < 320)
        {
            maxZoomLevel = 320;
        }

        if (maxZoomLevel < zoomLevel)
        {
            zoomLevel = maxZoomLevel;
        }
    }

    iVar3 = work->field_62;

    if ((((pad_status & PAD_CIRCLE) != 0) && (zoomLevel != maxZoomLevel)) || (((pad_status & PAD_CROSS) != 0) && (zoomLevel != 320)))
    {
        if (((pad_status & PAD_CIRCLE) != 0) && (zoomLevel != maxZoomLevel))
        {
            zoomLevel += zoomLevel / 32;

            if (zoomLevel >= maxZoomLevel)
            {
                zoomLevel = maxZoomLevel;
            }
            else
            {
                iVar3++;
            }

            if (iVar3 == 15)
            {
                iVar3 = 0;
            }
        }
        else
        {
            zoomLevel -= zoomLevel / 32;

            if (zoomLevel <= 320)
            {
                zoomLevel = 320;
            }
            else
            {
                iVar3--;
            }

            if (iVar3 == -1)
            {
                iVar3 = 14;
            }
        }

        DrawSideLines(pSideLine_f2, iVar3);
        work->field_62 = iVar3;
        work->field_60 = 1;

        if (GV_PauseLevel == 0)
        {
            if ((work->zoom_counter & 3U) == 0) // When field is 0, 4, 8, 12...
            {
                GM_SeSet2(0, 0x3F, SE_SCOPE_ZOOM);
            }

            work->zoom_counter++;
        }
    }
    else
    {
        DrawSideLines(pSideLine_f2, iVar3);
        work->field_60 = 0;
        work->zoom_counter = 0;
    }

    if (zoomLevel < 320)
    {
        zoomLevel = 320;
    }

    zoomLineLength = ((zoomLevel - 320) / 16) + 48;

    pZoomLevelLine_F3->x2 = zoomLineLength;
    pZoomLevelLine_F3->x1 = zoomLineLength;
    addPrimEX(ot, pZoomLevelLine_F3);
    for (i = 0; i < 8; i++)
    {
        addPrimEX(ot, pSideLine_f2);
        pSideLine_f2++;
    }

    GM_Camera.zoom = zoomLevel;
}

static void DrawMovingRectangle(Work *work, u_long *ot)
{
    LINE_F4 *pRect; // Top, right and bottom border.
    LINE_F2 *pLeftBorder;
    short    xy; // Left x, then top y.
    short    xRight;
    short    y0;

    pRect = work->rect_lines[GV_Clock];
    pLeftBorder = (LINE_F2 *)(pRect + 1);

    xy = work->rect_offset[0] + 130;
    xRight = work->rect_offset[0] + 189;
    y0 = work->rect_offset[1];

    pLeftBorder->x1 = xy; // Bottom point.
    pLeftBorder->x0 = xy; // Top point.
    pRect->x3 = xy; // Bottom left corner.
    pRect->x0 = xy; // Top left corner.

    xy = y0 + 102; // x -> y swap.
    y0 = y0 + 137; // Top y -> bottom y.

    pRect->x2 = xRight; // Bottom right corner.
    pRect->x1 = xRight; // Top right corner.
    pLeftBorder->y0 = xy; // Top point.
    pRect->y1 = xy; // Top right corner.
    pRect->y0 = xy; // Top left corner.
    pLeftBorder->y1 = y0; // Bottom point.
    pRect->y3 = y0; // Bottom left corner.
    pRect->y2 = y0; // Bottom right corner.

    addPrimEX(ot, pRect);
    addPrimEX(ot, pLeftBorder);
}

static void DrawMovingBarGraph(Work *work, u_long *ot)
{
    short    lineHeight;
    int      primCount;
    int      i;
    LINE_F3 *pLine_F3;
    u_char  *otMin;
    u_char  *chnlOt;
    u_char  *curPrim;
    int      numOTEntries;

    pLine_F3 = work->bar_graph[GV_Clock];
    chnlOt = DG_Chanl(0)->mOrderingTables[1 - GV_Clock];

    numOTEntries = DG_Chanl(0)->word_6BC374_8 - 4;
    for (i = 0; i < 16; i++)
    {
        otMin = chnlOt + ((i << numOTEntries) * 4);
        for (curPrim = chnlOt + (((i + 1) << numOTEntries) * 4), primCount = 0; (otMin < curPrim) || (curPrim < chnlOt);
             curPrim = nextPrim(curPrim))
        {
            if (getlen(curPrim) != 0)
            {
                primCount++;
            }

            if (primCount == 0x128)
            {
                break;
            }
        }

        primCount /= 2;
        lineHeight = 178 - primCount;
        pLine_F3->y1 = lineHeight;
        pLine_F3->y0 = lineHeight;
        addPrimEX(ot, pLine_F3);
        pLine_F3++;
    }
}

static void DrawHudText(Work *work)
{
    if ( (GM_PlayerStatus & PLAYER_NOT_SIGHT) == 0 )
    {
        MENU_Locate(20, 34, 0);
        MENU_Color(127, 166, 97);
        MENU_Printf("- ZOOM LEVEL - - %d -", 100 * (GM_Camera.zoom / 320));
        MENU_Color(101, 133, 77);
        MENU_Locate(32, 101, 1);
        MENU_Printf("%d", -work->field_6C_turn_vec.vx);
        menu_Text_Init_80038B98();
    }
}

static void Act(Work *work)
{
    int             model;
    OBJECT         *parent_obj;
    OBJECT_NO_ROTS *obj;
    u_long         *ot;
    u_short         pad_status;

    if (!(work->flags & 0x8000))
    {
        parent_obj = work->parent;

        if (work->parent->objs->n_models >= 7 && (work->parent->objs->flag & DG_FLAG_INVISIBLE))
        {
            obj = &work->object;
            model = SCOPE_MODEL;

            GM_InitObjectNoRots(obj, model, 0x6d, 0);

            if (work->object.objs)
            {
                GM_ConfigObjectRoot((OBJECT *)obj, parent_obj, 6);
                GM_ConfigObjectLight((OBJECT *)obj, parent_obj->light);
                EQ_InvisibleHead(parent_obj, &work->saved_packs, &work->saved_raise);
                work->flags |= 0x8000;
            }
        }
    }

    if (work->flags & 0x8000)
    {
        GM_CurrentMap = work->control->map->index;
        DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

        if ((GM_PlayerStatus & PLAYER_NOT_SIGHT) != 0)
        {
            if (!(work->parent->objs->flag & DG_FLAG_INVISIBLE))
            {
                DG_VisibleObjs(work->object.objs);
            }

            GM_Camera.zoom = 320;
            return;
        }

        DG_InvisibleObjs(work->object.objs);
    }

    // Add some delay before showing the HUD of the scope (don't know why it is needed).
    if (work->hud_delay > 0)
    {
        if (GV_PauseLevel == 0)
        {
            work->hud_delay--;
        }

        return;
    }

    if (dword_8009F604 != SCOPE_SIGHT)
    {
        NewSight(SCOPE_SIGHT, SCOPE_SIGHT, &GM_CurrentItemId, IT_Scope, NULL);
        GM_SeSet2(0, 63, SE_ITEM_OPENWINDOW);
    }

    if ((work->flags & 3) != 3)
    {
        scope_act_helper_8006258C(work);
        return;
    }

    if ((GM_PlayerStatus & PLAYER_SECOND_CONTROLLER) != 0)
    {
        work->old_pad = &GV_PadData[3];
    }
    else
    {
        work->old_pad = &GV_PadData[2];
    }

    pad_status = work->old_pad->status;
    GM_CheckShukanReverse(&pad_status);

    if ((GV_PauseLevel != 0) || (GM_PlayerStatus & PLAYER_PAD_OFF) ||
        (GM_GameStatus < 0))
    {
        pad_status = 0;
    }

    ot = (u_long *)DG_ChanlOTag(1);

    ManagePadInput(work, pad_status);
    ManageZoom(work, ot, pad_status);
    DrawMovingRectangle(work, ot);
    DrawMovingBarGraph(work, ot);
    DrawHudText(work);
}

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    if ( work->side_lines[0] )
    {
        GV_DelayedFree(work->side_lines[0]);
    }

    if ( work->rect_lines[0] )
    {
        GV_DelayedFree(work->rect_lines[0]);
    }

    if ( work->bar_graph[0] )
    {
        GV_DelayedFree(work->bar_graph[0]);
    }

    if ( work->zoom_line[0] )
    {
        GV_DelayedFree(work->zoom_line[0]);
    }

    GM_Camera.zoom = 320;

    if ( (work->flags & 0x8000) != 0 )
    {
        EQ_VisibleHead(work->parent, &work->saved_packs, &work->saved_raise);
        GM_FreeObject((OBJECT *)&work->object);
    }

    scope_created_8009F2C4 = FALSE;
}

/*---------------------------------------------------------------------------*/

static void InitSideLines(LINE_F2 *lines)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        LSTORE(COLOR_DARK_CYAN, &lines->r0);
        setLineF2(lines);
        setSemiTrans(lines, 1);
        lines++;
    }
}

static void InitMovingRectangle(LINE_F4 *lines)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        LSTORE(COLOR_LIGHT_GREEN, &lines->r0); // Top, right and bottom borders.
        setLineF4(lines);
        lines++;

        LSTORE(COLOR_LIGHT_GREEN, &lines->r0); // Left border.
        setLineF2(lines);
        lines++;
    }
}

static void InitMovingBarGraph(Work *work)
{
    LINE_F3 *line;
    int i, j;

    line = work->bar_graph[0];
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 16; j++)
        {
            line->x0 = 68 + j * 12;
            line->x2 = 76 + j * 12;
            line->x1 = 76 + j * 12;

            LSTORE(COLOR_DARK_GREEN, &line->r0);

            setLineF3(line);
            setSemiTrans(line, 1);

            line->y2 = 178;
            line++;
        }
    }
}

static void InitZoomLevelLine(LINE_F3 *pZoomLevelLine)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        LSTORE(COLOR_DARK_GREEN, &pZoomLevelLine->r0);
        setLineF3(pZoomLevelLine);
        pZoomLevelLine->x0 = pZoomLevelLine->x1 = pZoomLevelLine->x2 = 48;
        pZoomLevelLine->y0 = pZoomLevelLine->y1 = 46;
        pZoomLevelLine->y2 = 52;
        pZoomLevelLine++;
    }
}

static int GetResources(Work *work, CONTROL *control, OBJECT *parent)
{
    MAP *map;

    work->side_lines[0] = GV_Malloc(sizeof(LINE_F2) * 16);
    if (!work->side_lines[0])
    {
        return -1;
    }

    work->side_lines[1] = work->side_lines[0] + 8;

    work->rect_lines[0] = GV_Malloc(sizeof(LINE_F4) * 4);
    if (!work->rect_lines[0])
    {
        return -1;
    }

    work->rect_lines[1] = work->rect_lines[0] + 2;

    work->bar_graph[0] = GV_Malloc(sizeof(LINE_F3) * 32);

    if (!work->bar_graph[0])
    {
        return -1;
    }

    work->bar_graph[1] = work->bar_graph[0] + 16;

    work->zoom_line[0] = GV_Malloc(sizeof(LINE_F3) * 2);
    if (!work->zoom_line[0])
    {
        return -1;
    }

    work->zoom_line[1] = work->zoom_line[0] + 1;

    InitSideLines(work->side_lines[0]);
    InitMovingRectangle(work->rect_lines[0]);
    InitMovingBarGraph(work);
    InitZoomLevelLine(work->zoom_line[0]);

    work->old_pad = &GV_PadData[2];
    work->hud_delay = HUD_DISP_DELAY;
    work->field_58 = 0;
    work->field_5E = 2;
    work->field_60 = 0;
    work->field_62 = 0;

    work->field_6C_turn_vec.vy = work->field_64_vec.vy = control->turn.vy;
    work->field_6C_turn_vec.vx = work->field_64_vec.vx = control->turn.vx;

    work->field_64_vec.vz = 0;
    work->field_6C_turn_vec.vz = 0;

    work->rect_offset[1] = 0;
    work->rect_offset[0] = 0;

    map = control->map;

    work->flags = 0;
    work->control = control;
    work->parent = parent;
    work->map = map;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewScope(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work;

    if ( scope_created_8009F2C4 )
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if ( work )
    {
        GV_SetNamedActor(&work->actor, Act, Die, "scope.c");
        if ( GetResources(work, control, parent) < 0 )
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        scope_created_8009F2C4 = TRUE;
    }

    return (void *)work;
}
