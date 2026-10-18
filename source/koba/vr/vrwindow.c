#include "vrwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

// GCL options
#define OPT_NO_PAUSE       's'    // do not pause the game
#define OPT_N_LINES        'i'    // number of lines
#define OPT_TEXT           'b'    // the lines
#define OPT_WINDOW         'w'    // window rect
#define OPT_MARGIN         'm'    // margin rect
#define OPT_PROC           'p'    // proc run when closed
#define OPT_FREE_FONT      'f'    // release the font area


// Act states: the window opens (OPEN_W, OPEN_H), types the lines (TYPING), waits for the
// "close" message (WAIT) and shrinks again (CLOSE_H, CLOSE_W)
#define VRWIN_STATE_WAIT        0
#define VRWIN_STATE_OPEN_W      1
#define VRWIN_STATE_OPEN_H      2
#define VRWIN_STATE_TYPING      3
#define VRWIN_STATE_CLOSE_H     4
#define VRWIN_STATE_CLOSE_W     5
#define VRWIN_STATE_CLOSED      6

#define VRWIN_LINE_H            18      // height of a text line
#define VRWIN_MAX_LINES         16
#define VRWIN_PAUSE_DELAY       10      // frames until the game is paused

/*---------------------------------------------------------------------------*/

// The VR-DISC has its own sound effect table
#ifdef VR_EXE
#define VRWIN_SE_OPEN           182
#define VRWIN_SE_CHAR           196
#define VRWIN_SE_START          181
#else
#define VRWIN_SE_OPEN           SE_MENU_SELECT
#define VRWIN_SE_CHAR           179
#define VRWIN_SE_START          SE_MENU_SELECT
#endif

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT         actor;
    RECT           m_rect;      // margin?
    RECT           w_rect;      // window?
    short          step;
    int            line;        // 0x34: first displayed line
    char           state;
    int            proc;
    char           i_num;       // number of lines
    char          *b_text[VRWIN_MAX_LINES];
    u_short        name;
    u_short        clut;
    KCB            kcb;
    SPRT           sprts[2];
    TILE           tiles[2];
    LINE_F3        lines1[2];
    LINE_F3        lines2[2];
    DR_TPAGE       tpages[2];
    int            max_lines;   // 0x16C: lines that fit the window
    char           pad[0x4];
    RECT           font_rect;   // 0x174: area of the font texture in VRAM
    int            flag;
    int            n_chars;     // 0x180: characters typed so far in the current line
    void          *font_buffer;
    short          pause_timer; // 0x188: frames until the game is paused
    short          pausing;     // 0x18A: pause the game while the window is open
} Work;

/*---------------------------------------------------------------------------*/

int vrwindow_X1 = 896;
int vrwindow_Y1 = 256;
int vrwindow_X2 = 896;
int vrwindow_Y2 = 510;

char SECTION(".bss") vrwindow_strbuf[100];

/*---------------------------------------------------------------------------*/

static void DrawWindowRect(Work *work, RECT *rect)
{
    setXY0(&work->tiles[GV_Clock], rect->x, rect->y);
    setWH(&work->tiles[GV_Clock], rect->w, rect->h);

    setXY3(&work->lines1[GV_Clock],
           rect->x, rect->y,
           rect->x + rect->w, rect->y,
           rect->x + rect->w, rect->y + rect->h);

    setXY3(&work->lines2[GV_Clock],
           rect->x, rect->y,
           rect->x, rect->y + rect->h,
           rect->x + rect->w, rect->y + rect->h);
}

static int CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     n_msgs;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == 0x3213)
        {
            return 1;
        }
    }

    return 0;
}

static void CloseWindow(Work *work)
{
    if (!(GV_PadData[2].status & (PAD_UDLR | PAD_ABXY)))
    {
        return;
    }

    if (work->proc != 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }

    GM_SeSet2(0, 63, VRWIN_SE_OPEN);

    switch (work->state)
    {
    case VRWIN_STATE_WAIT:
        work->state = VRWIN_STATE_CLOSE_H;
        work->step = 0;
        break;

    case VRWIN_STATE_OPEN_W:
        work->state = VRWIN_STATE_CLOSE_W;
        work->step = 4 - work->step;
        break;

    case VRWIN_STATE_OPEN_H:
        work->state = VRWIN_STATE_CLOSE_H;
        work->step = 4 - work->step;
        break;

    case VRWIN_STATE_TYPING:
        work->state = VRWIN_STATE_CLOSE_H;
        work->step = 0;
        break;
    }
}

static int PrintMessage(Work *work, int size)
{
    int i;
    int len;
    int idx;

    font_clear(&work->kcb);

    for (i = 0; i < work->max_lines; i++)
    {
        if (i >= work->i_num)
        {
            break;
        }

        len = strlen(work->b_text[work->line + i]);

        if (size < len)
        {
            strncpy(vrwindow_strbuf, work->b_text[work->line + i], size);

            idx = work->n_chars;
            work->n_chars = 0;

            while (idx < size)
            {
                if ((work->n_chars != 0) || (vrwindow_strbuf[idx] > 0x1F && vrwindow_strbuf[idx] < 0x7F))
                {
                    work->n_chars = 0;
                }
                else
                {
                    work->n_chars = size;
                }

                idx++;
            }

            if (size != 0 && work->n_chars != 0)
            {
                vrwindow_strbuf[size - 1] = '\0';
                work->n_chars = size - 1;
            }
            else
            {
                vrwindow_strbuf[size] = '\0';
                work->n_chars = size;
            }

            if (work->n_chars != 0 && vrwindow_strbuf[work->n_chars - 1] != ' ')
            {
                GM_SeSet2(0, 63, VRWIN_SE_CHAR);
            }

            font_draw_string(&work->kcb, 0, i * VRWIN_LINE_H, vrwindow_strbuf, work->kcb.color);
            font_update(&work->kcb);
            break;
        }

        font_draw_string(&work->kcb, 0, i * VRWIN_LINE_H, work->b_text[work->line + i], work->kcb.color);
        font_update(&work->kcb);

        size -= len;
        work->n_chars = 0;
    }

    if (i == work->max_lines || i == work->i_num)
    {
        return 0;
    }

    return 1;
}

static void Act(Work *work)
{
    RECT rect;

    if (work->pausing != 0)
    {
        if (work->pause_timer >= 0 && work->pause_timer < VRWIN_PAUSE_DELAY)
        {
            work->pause_timer++;
        }
        else if (work->pause_timer == VRWIN_PAUSE_DELAY)
        {
            GV_PauseLevel |= GV_PAUSE_MENU;
            work->pause_timer++;
        }
    }

    switch (work->state)
    {
    case VRWIN_STATE_WAIT:
        if (CheckMessage(work))
        {
            work->state = VRWIN_STATE_CLOSE_H;
        }

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        CloseWindow(work);
        break;

    case VRWIN_STATE_OPEN_W:
        rect.w = (work->w_rect.w * work->step) / 5;
        rect.h = 1;
        rect.x = work->w_rect.x + (work->w_rect.w - rect.w) / 2;
        rect.y = work->w_rect.y + work->w_rect.h / 2;
        DrawWindowRect(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_OPEN_H;
            work->step = 0;
        }

        CloseWindow(work);
        break;

    case VRWIN_STATE_OPEN_H:
        rect.w = work->w_rect.w;
        rect.h = work->w_rect.h * work->step / 4;
        rect.x = work->w_rect.x;
        rect.y = work->w_rect.y + (work->w_rect.h - rect.h) / 2;
        DrawWindowRect(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_TYPING;
            work->step = 0;
        }

        CloseWindow(work);
        break;

    case VRWIN_STATE_TYPING:
        work->step += 2;
        if (!PrintMessage(work, work->step))
        {
            work->step -= strlen(work->b_text[work->line]) * 2;
            work->n_chars = 0;

            if (work->i_num <= (work->line++ + work->max_lines))
            {
                work->state = VRWIN_STATE_WAIT;
                work->step = 0;
            }
        }

        DrawWindowRect(work, &work->w_rect);

        addPrim(DG_ChanlOTag(1), &work->sprts[GV_Clock]);
        CloseWindow(work);
        break;

    case VRWIN_STATE_CLOSE_H:
        rect.w = work->w_rect.w;
        rect.h = work->w_rect.h * (4 - work->step) / 4;
        rect.x = work->w_rect.x;
        rect.y = work->w_rect.y + (work->w_rect.h - rect.h) / 2;
        DrawWindowRect(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_CLOSE_W;
            work->step = 0;
        }
        break;

    case VRWIN_STATE_CLOSE_W:
        rect.w = work->w_rect.w * (4 - work->step) / 4;
        rect.h = 1;
        rect.x = work->w_rect.x + (work->w_rect.w - rect.w) / 2;
        rect.y = work->w_rect.y + work->w_rect.h / 2;
        DrawWindowRect(work, &rect);

        if (++work->step == 5)
        {
            work->state = VRWIN_STATE_CLOSED;
            work->step = 0;
        }
        break;

    case VRWIN_STATE_CLOSED:
        if (++work->step == 3)
        {
            GV_DestroyActor(&work->actor);
            GV_PauseLevel &= ~GV_PAUSE_MENU;
        }
        return;
    }

    addPrim(DG_ChanlOTag(1), &work->lines1[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->lines2[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->tiles[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->tpages[GV_Clock]);
}

static void FreeFontRect(RECT *rect);

static void Die(Work *work)
{
    if (work->flag)
    {
        FreeFontRect(&work->font_rect);
    }

    GV_Free(work->font_buffer);
}

static void AllocFontRect(Work *work, RECT *rect)
{
    rect->x = vrwindow_X1;
    rect->y = vrwindow_Y1;
    rect->w = work->m_rect.w / 4;
    rect->h = work->m_rect.h;

    vrwindow_Y1 += work->w_rect.h;
    if (vrwindow_Y1 > 512)
    {
        printf("vrwindow: Can\'t alloc !! \n");
    }
}

static void FreeFontRect(RECT *rect)
{
    vrwindow_Y1 = 256;
    vrwindow_X2 = 960;
}

static u_short AllocClut(RECT *rect)
{
    rect->x = vrwindow_X2;
    rect->y = vrwindow_Y2;
    rect->w = 16;
    rect->h = 1;

    vrwindow_X2 += 16;

    return getClut(rect->x, rect->y);
}

static void InitWindowText(KCB *kcb, int x, int y, Work *work)
{
    RECT rect;

    AllocFontRect(work, &work->font_rect);
    ClearImage(&work->font_rect, 0, 0, 0);

    work->clut = AllocClut(&rect);
    font_init_kcb(kcb, &work->font_rect, rect.x, rect.y);
    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    work->font_buffer = GV_Malloc(font_get_buffer_size(kcb));
    font_set_buffer(kcb, work->font_buffer);

    font_set_color(kcb, 0, 0x6739, 0);
    font_clut_update(kcb);
}

static int GetResources(Work *work, int map)
{
    int i;

    GM_CurrentMap = map;

    work->pause_timer = 0;
    InitWindowText(&work->kcb, work->m_rect.w, work->m_rect.h + VRWIN_LINE_H, work);

    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->tpages[i], 1, 0, getTPage(0, 0, 896, 256));

        LSTORE(COLOR_GRAY, &work->sprts[i].r0);
        LCOPY(&work->m_rect.x, &work->sprts[i].x0);
        LCOPY(&work->m_rect.w, &work->sprts[i].w);
        setSprt(&work->sprts[i]);
        setUV0(&work->sprts[i], (work->font_rect.x - 896) * 4, work->font_rect.y);
        work->sprts[i].clut = work->clut;

        setTile(&work->tiles[i]);
        setRGB0(&work->tiles[i], 0, 0, 0);
        setXY0(&work->tiles[i], work->w_rect.x, work->w_rect.y);
        setWH(&work->tiles[i], work->w_rect.w, work->w_rect.h);
        setSemiTrans(&work->tiles[i], 1);

        setLineF3(&work->lines1[i]);
        setLineF3(&work->lines2[i]);
        setRGB0(&work->lines1[i], 64, 64, 64);
        setRGB0(&work->lines2[i], 64, 64, 64);

        work->n_chars = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrWindow(int name, int where)
{
    Work    *work;
    int     i;
    int     width;

    work = GV_NewActor(GV_ACTOR_ASSIST, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrwindow.c");

        work->state = VRWIN_STATE_OPEN_W;
        work->step = 0;
        work->line = 0;

        GM_SeSet2(0, 63, VRWIN_SE_START);

        if (GCL_GetOption(OPT_NO_PAUSE))
        {
            work->pausing = 0;
        }
        else
        {
            work->pausing = 1;
        }

        work->i_num = GCL_StrToInt(GCL_GetOption(OPT_N_LINES));

        if (GCL_GetOption(OPT_TEXT))
        {
            for (i = 0; i < work->i_num; i++)
            {
                work->b_text[i] = GCL_GetString(GCL_NextStr());
                if (work->b_text[i] == 0)
                {
                    break;
                }
            }
        }

        if (GCL_GetOption(OPT_WINDOW))
        {
            work->w_rect.x = GCL_StrToInt(GCL_NextStr());
            work->w_rect.y = GCL_StrToInt(GCL_NextStr());
            work->w_rect.w = GCL_StrToInt(GCL_NextStr());
            work->w_rect.h = GCL_StrToInt(GCL_NextStr());

            width = work->w_rect.w;
            if (width & 3)
            {
                work->w_rect.w += 4 - (width % 4);
            }

            // FIXME: x, y and h read above are overwritten (dead stores kept like the original)
            work->w_rect.h = (work->i_num * VRWIN_LINE_H) + VRWIN_LINE_H;
            work->w_rect.x = (FRAME_WIDTH - work->w_rect.w) >> 1;
            work->w_rect.y = (FRAME_HEIGHT - work->w_rect.h) >> 1;
        }
        else
        {
            work->w_rect.x = 0;
            work->w_rect.y = 0;
            work->w_rect.w = 256;
            work->w_rect.h = 13;
        }

        if (GCL_GetOption(OPT_MARGIN))
        {
            work->m_rect.x = work->w_rect.x + GCL_StrToInt(GCL_NextStr());
            work->m_rect.y = work->w_rect.y + GCL_StrToInt(GCL_NextStr());
            work->m_rect.w = GCL_StrToInt(GCL_NextStr());
            work->m_rect.h = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->m_rect.x = work->w_rect.x;
            work->m_rect.y = work->w_rect.y;
            work->m_rect.w = work->w_rect.w;
            work->m_rect.h = work->w_rect.h;
        }

        // FIXME: the margin read above is overwritten (dead stores kept like the original)
        work->m_rect.x = work->w_rect.x + 16;
        work->m_rect.y = work->w_rect.y + 12;
        work->m_rect.w = work->w_rect.w - 16;
        work->m_rect.h = work->w_rect.h - 12;

        if (GCL_GetOption(OPT_PROC))
        {
            work->proc = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->proc = 0;
        }

        if (GCL_GetOption(OPT_FREE_FONT))
        {
            work->flag = TRUE;
        }
        else
        {
            work->flag = FALSE;
        }

        work->name = name;
        work->max_lines = work->m_rect.h / VRWIN_LINE_H;

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
