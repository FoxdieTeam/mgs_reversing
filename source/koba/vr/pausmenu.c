#include "pausmenu.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "sound/sd_cli.h"
#include "vrmenu.h"

/*---------------------------------------------------------------------------*/

// GCL options
#define OPT_PROCS          'p'    // procs of the menu items
#define OPT_CONTINUES      'c'    // restart continues the game

// The pause menu of the VR missions: CONTINUE / RESTART / EXIT

#define PCX_CONTINUE        0xedaf  // GV_StrCode("continue")
#define PCX_RESTART         0xe43c  // GV_StrCode("restart")
#define PCX_EXIT            0x6dc8  // GV_StrCode("exit")

#define ITEM_CONTINUE       0
#define ITEM_RESTART        1
#define ITEM_EXIT           2
#define NUM_ITEMS           4       // the 4th item is never shown
#define NUM_SHOWN_ITEMS     3

#define LINK_UP             0
#define LINK_DOWN           2

#define FADE_TIME           30
#define REPEAT_FIRST        10
#define REPEAT_NEXT         1

// The VR-DISC has its own sound effect table
#define PAUSMENU_SE_CURSOR  31
#define PAUSMENU_SE_EXIT    33

// messages to the pause menu (from the VR stage scripts)
#define MSG_DISABLE         0x2103
#define MSG_ENABLE          0x15b8

#define MSG_DEMO_STOP       0x32a1  // sent to the "demo" actor when the mission is restarted

typedef struct _Work
{
    GV_ACT    actor;
    short     fade;                     // 0x20: counts down after an item was chosen
    short     cursor;                   // 0x22
    short     next_cursor;              // 0x24
    short     pad26;
    int       name;                     // 0x28
    short     repeat;                   // 0x2C: up/down auto repeat counter
    short     pad2E;
    int       game_status;              // 0x30: GM_GameStatus before the menu was opened
    int       last_dir;                 // 0x34: up/down buttons held last frame
    RECT      frame_rect;               // 0x38: frame around the selected item
    POLY_FT4  frame_polys[2][VR_MENU_FRAME_POLYS];    // 0x40
    TILE      frame_tiles[2];           // 0x2C0
    short     open;                     // 0x2E0
    short     pad2E2;
    TILE      fade_tiles[2];            // 0x2E4
    DR_TPAGE  fade_tpages[2];           // 0x304
    int       restart_continues;        // 0x314: RESTART continues from the last checkpoint ('c' option)
    u_char    visible;                  // 0x318
    u_char    disabled;                 // 0x319: START does not open the menu
} Work;

/*---------------------------------------------------------------------------*/

VR_MENU_ITEM pausmenu_items[NUM_ITEMS] = {
    {{126, 151, 68,  8}, {-1, -1,  1, -1}, PCX_CONTINUE, 0, {120, 148, 80, 14}},
    {{128, 169, 64,  8}, { 0, -1,  2, -1}, PCX_RESTART,  1, {122, 166, 76, 14}},
    {{132, 188, 56, 14}, { 1, -1, -1, -1}, PCX_EXIT,     1, {132, 188, 57, 14}},
    {{160, 171,  0,  8}, {-1, -1, -1, -1}, PCX_EXIT,     0, {160, 171,  0,  8}},
};

/*---------------------------------------------------------------------------*/

static void StopDemo(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("demo");
    msg.message[0] = MSG_DEMO_STOP;
    msg.message_len = 1;
    GV_SendMessage(&msg);
}

static int CheckVisible(Work *work)
{
    if (work->visible && (GM_GameStatus & STATE_PADDEMO))
    {
        if (mts_read_pad(1) & (PAD_START | PAD_CIRCLE | PAD_CROSS))
        {
            work->visible = FALSE;
            return 0;
        }
    }

    return work->visible;
}

static int Control(Work *work)
{
    GV_PAD *pad;
    int     buttons;
    int     link;
    short   next;

    pad = &GV_PadData[2];
    buttons = pad->press;   // FIXME: one variable for press and status steers the register allocation

    if (buttons & PAD_CIRCLE)
    {
        if (work->cursor == ITEM_CONTINUE)
        {
            work->open = FALSE;
            GV_PauseLevel &= ~GV_PAUSE_MENU;
            GM_GameStatus = work->game_status;
            GV_PadData[0].press = 0;
            GV_PadData[0].status = 0;
        }
        else
        {
            work->fade = FADE_TIME;

            if (work->cursor == ITEM_RESTART)
            {
                GM_SetSound(0x01ffff0a, SD_ASYNC);
            }
            else
            {
                GM_SetSound(0x01ffff0b, SD_ASYNC);
                GM_SeSet2(0, 63, PAUSMENU_SE_EXIT);
            }
        }
    }

    buttons = pad->status & (PAD_UP | PAD_DOWN);

    if (buttons == work->last_dir)
    {
        if (work->repeat-- > 0)
        {
            return 0;
        }

        work->repeat = REPEAT_NEXT;
    }
    else
    {
        work->last_dir = buttons;
        work->repeat = REPEAT_FIRST;
    }

    if (buttons & (PAD_UP | PAD_DOWN))
    {
        link = ((buttons & PAD_DOWN) != 0) * 2;

        next = pausmenu_items[work->cursor].link[link];
        if (next == -1)
        {
            return 0;
        }

        while (pausmenu_items[next].tex_id <= 0)
        {
            next = pausmenu_items[next].link[link];
            if (next == -1)
            {
                return 0;
            }
        }

        work->next_cursor = next;
        GM_SeSet2(0, 63, PAUSMENU_SE_CURSOR);
    }

    return 0;
}

static void Reset(Work *work)
{
    int i;

    for (i = 0; i < NUM_ITEMS; i++)
    {
        VrMenu_InitItem(&pausmenu_items[i], 0, VR_MENU_ITEM_STATE_OPEN);
    }

    work->cursor = 3;
    work->next_cursor = ITEM_CONTINUE;
    work->fade = 0;
    work->frame_rect = pausmenu_items[0].label;
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    GV_MSG       *msg;
    int           n_msgs;
    int           shade;
    int           i;
    VR_MENU_ITEM *item;
    GV_PAD       *pad;

    if (GV_PauseLevel == 0)
    {
        n_msgs = GV_ReceiveMessage(work->name, &msg);
        for (; n_msgs > 0; n_msgs--, msg++)
        {
            if (msg->message[0] == MSG_DISABLE)
            {
                work->disabled = TRUE;
            }

            if (msg->message[0] == MSG_ENABLE)
            {
                work->disabled = FALSE;
            }
        }
    }

    if (work->disabled && !(GM_GameStatus & STATE_PADRELEASE))
    {
        GV_PadMask |= PAD_START;
    }
    else
    {
        GV_PadMask &= ~PAD_START;
    }

    if (work->fade != 0)
    {
        if (work->cursor == ITEM_RESTART)
        {
            work->fade--;
        }

        work->fade--;

        shade = ((FADE_TIME - 1 - work->fade) * 223) / 28 + 32;
        if (shade > 255)
        {
            shade = 255;
        }

        setRGB0(&work->fade_tiles[GV_Clock], shade, shade, shade);
        addPrim(DG_ChanlOTag(1), &work->fade_tiles[GV_Clock]);
        addPrim(DG_ChanlOTag(1), &work->fade_tpages[GV_Clock]);

        if (work->fade == 0)
        {
            GV_PadData[0].press = 0;
            GV_PadData[0].status = 0;
            GV_PauseLevel &= ~GV_PAUSE_MENU;

            if (work->cursor == ITEM_RESTART && !work->restart_continues)
            {
                StopDemo();
                GM_LoadRequest = 0x81;
            }
            else
            {
                VrMenu_ExecItem(&pausmenu_items[work->cursor]);
            }

            if (work->cursor == ITEM_RESTART && work->restart_continues)
            {
                GM_ContinueStart();
            }

            work->open = FALSE;
        }
        return;
    }

    pad = GV_PadData;

    if (pad[2].press & PAD_START)
    {
        if (!work->open)
        {
            if (GM_GameStatus & STATE_PADRELEASE)
            {
                return;
            }

            if (GV_PauseLevel & GV_PAUSE_MENU)
            {
                return;
            }

            Reset(work);
            VrMenu_LoadFrameTexture();

            work->open = TRUE;
            work->game_status = GM_GameStatus;
            GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;
            work->last_dir = pad[2].status & (PAD_UP | PAD_DOWN);
            work->repeat = REPEAT_FIRST;
        }
        else
        {
            GV_PauseLevel &= ~GV_PAUSE_MENU;
            work->open = FALSE;
            GM_GameStatus = work->game_status;
        }
    }

    if (!work->open)
    {
        return;
    }

    if (GM_GameStatus & STATE_PADRELEASE)
    {
        GV_PauseLevel &= ~GV_PAUSE_MENU;
        work->open = FALSE;
        GM_GameStatus = work->game_status;
        return;
    }

    GV_PauseLevel |= GV_PAUSE_MENU;

    if (!CheckVisible(work))
    {
        return;
    }

    MENU_Locate(160, 80, 0x12);
    MENU_Printf("PAUSE");

    work->cursor = work->next_cursor;

    for (item = pausmenu_items, i = NUM_SHOWN_ITEMS; i != 0; i--, item++)
    {
        VrMenu_DrawItem(item);
    }

    Control(work);

    VrMenu_UpdateFrame(&work->frame_rect, &pausmenu_items[work->next_cursor].label,
                       work->frame_polys[GV_Clock], &work->frame_tiles[GV_Clock]);

    addPrim(DG_ChanlOTag(1), &work->fade_tiles[GV_Clock]);
    addPrim(DG_ChanlOTag(1), &work->fade_tpages[GV_Clock]);
}

static void Die(Work *work)
{
}

static int GetResources(Work *work, int where)
{
    int           procs[4];
    char         *opt;
    int          *proc;
    int           i;
    VR_MENU_ITEM *item;

    GM_CurrentMap = where;

    opt = GCL_GetOption(OPT_PROCS);
    if (opt)
    {
        // FIXME: i counts the procs too (one variable steers the register allocation)
        i = GCL_StrToInt(opt);
        for (proc = procs; i != 0; proc++)
        {
            i--;
            *proc = GCL_StrToInt(GCL_NextStr());
        }
    }

    for (i = 0, item = pausmenu_items, proc = procs; i < NUM_ITEMS; i++, item++)
    {
        if (VrMenu_InitItem(item, *proc, VR_MENU_ITEM_STATE_OPEN))
        {
            proc++;
        }
    }

    Reset(work);
    VrMenu_InitFrame(work->frame_polys, work->frame_tiles, VrMenu_LoadFrameTexture());

    work->frame_rect.x = 160;
    work->frame_rect.y = 112;
    work->frame_rect.w = 0;
    work->frame_rect.h = 0;

    for (i = 0; i < 2; i++)
    {
        setDrawTPage(&work->fade_tpages[i], 0, 1, getTPage(0, 2, 0, 0));

        setTile(&work->fade_tiles[i]);
        setXY0(&work->fade_tiles[i], 0, 0);
        setWH(&work->fade_tiles[i], FRAME_WIDTH, FRAME_HEIGHT);
        setRGB0(&work->fade_tiles[i], 32, 32, 32);
        setSemiTrans(&work->fade_tiles[i], 1);
    }

    work->open = FALSE;

    if (GCL_GetOption(OPT_CONTINUES))
    {
        work->restart_continues = TRUE;
    }
    else
    {
        work->restart_continues = FALSE;
    }

    work->visible = TRUE;
    work->disabled = FALSE;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrPauseMenu(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_PAUSE_OFF;

    work = GV_NewActor(GV_ACTOR_PREV2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "pausmenu.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
