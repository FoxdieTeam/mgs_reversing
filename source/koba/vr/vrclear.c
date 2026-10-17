#include "vrclear.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/strctrl.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "takabe/fadeio.h"
#include "vr.h"
#include "vrmenu.h"

/*---------------------------------------------------------------------------*/
// VR-DISC: the "MISSION CLEARED" screen of the VR missions (result times,
// record table and the RETRY / NEXT / EXIT / SAVE menu)

#define EXEC_LEVEL          GV_ACTOR_AFTER2

#define MSG_OPEN            0xEDAF              // opens the menu buttons
#define PROC_GO_VRSAVE      "GO_VRSAVE"

// The VR-DISC has its own sound effect table
#define VRCLEAR_SE_MENU     102
#define VRCLEAR_SE_EXIT     33
#define VRCLEAR_SE_CURSOR   31
#define VRCLEAR_SE_COUNT    187
#define VRCLEAR_SE_RECORD   192
#define VRCLEAR_SE_TITLE    195

// Work::act_state
#define ACT_WAIT            0                   // waits for the "clear" message
#define ACT_INIT            1
#define ACT_MAIN            2

// Work::state (menu)
#define MENU_SELECT         0
#define MENU_IDLE           1
#define MENU_WAIT_OPEN      2
#define MENU_DECIDED        3
#define MENU_OPEN_WINDOW    4
#define MENU_CLOSING        5
#define MENU_HIDDEN         6

// VR_MENU_ITEM::link[] (cursor movement)
#define LINK_UP             0
#define LINK_LEFT           1
#define LINK_DOWN           2
#define LINK_RIGHT          3

#define BUTTON_NEXT         0                   // NEXT (or REPLAY) button
#define BUTTON_RETRY        1
#define BUTTON_EXIT         2
#define BUTTON_SAVE         3
#define BUTTON_CURSOR       4
#define NUM_BUTTONS         5

// Work::mode
#define MODE_ADVANCED       6
#define MODE_NINJA          9
#define MODE_MYSTERY        12
#define NUM_MODES           17

#define NUM_WEAPONS         10

#define LOADREQ_GAMEOVER    0x81

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT      actor;                  // 0x000
    short       count;                  // 0x020
    short       cur;                    // 0x022 button that is selected
    short       sel;                    // 0x024 button under the cursor
    short       state;                  // 0x026
    int         name;                   // 0x028
    int         voice[4];               // 0x02C
    int         timer;                  // 0x03C
    DR_AREA     area[2];                // 0x040
    DR_ENV      env[2];                 // 0x058
    int         last_pad;               // 0x0D8
    RECT        cursor;                 // 0x0DC
    POLY_FT4    cursor_polys[2][8];     // 0x0E4
    TILE        cursor_tiles[2];        // 0x364
    short       repeat;                 // 0x384
    u_char      weapon;                 // 0x386
    u_char      unit;                   // 0x387 frames per remaining bullet
    u_char      n_buttons;              // 0x388
    char        pad_389[3];             // 0x389
    char       *title[2];               // 0x38C
    char       *stage_var;              // 0x394
    int         f398;                   // 0x398
    short       title_x;                // 0x39C
    short       win_h;                  // 0x39E
    short       win_w;                  // 0x3A0
    short       stage;                  // 0x3A2
    int         mode;                   // 0x3A4
    int         weapon_name;            // 0x3A8
    u_char      category;               // 0x3AC
    u_char      level;                  // 0x3AD
    u_char      act_state;              // 0x3AE
    u_char      voice_flag;             // 0x3AF
    u_int       replay : 1;             // 0x3B0
    u_int       f3B0_1 : 1;
    u_int       has_replay : 1;
    u_int       custom_title : 1;
    u_int       f3B0_4 : 1;
    u_int       blink : 5;
    int         fade;                   // 0x3B4
} Work;

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

VR_MENU_ITEM vrclear_buttons[NUM_BUTTONS] = {
    { { 122, 169,  76,  8 }, {  1, -1,  2, -1 }, 0x8D82,  1, { 111, 166,  96, 14 } },
    { { 115, 153,  92,  8 }, { -1, -1,  0, -1 }, 0x7F9C,  1, { 103, 150, 114, 14 } },
    { { 132, 184,  56, 14 }, {  0, -1, -1, -1 }, 0x6DC8,  1, { 132, 184,  57, 14 } },
    { { 110, 138, 100,  8 }, { -1, -1,  1, -1 }, 0x023C, -1, {  98, 135, 120, 14 } },
    { { 160, 171,   0,  8 }, { -1, -1, -1, -1 }, 0x6DC8,  0, { 160, 171,   0,  8 } },
};

int vrclear_last_count = -1;

u_long   SECTION(".bss") vrclear_flags[16][6];
u_short *SECTION(".bss") vrclear_replay_data;

/*---------------------------------------------------------------------------*/

static void SetClearFlag(int category, int stage)
{
    RECT   rect = { 160, 224, 12, 16 };
    int    word;
    u_long flags;


    StoreImage(&rect, vrclear_flags);
    DrawSync(0);

    if (stage > 0)
    {
        word = stage >> 5;
        printf("stage = %d\n", stage);
        printf("area = %d\n", word);
        flags = vrclear_flags[category - 1][word];
        flags |= 1 << (stage - (word << 5));
        vrclear_flags[category - 1][word] = flags;
        printf("clearflags[%d][%d] = %d\n", category - 1, word, 1 << (stage - (word << 5)));
    }

    LoadImage(&rect, vrclear_flags);
    DrawSync(0);
}

static int OpenButtons(int message)
{
    int i;

    if (message != MSG_OPEN)
    {
        return 0;
    }

    for (i = 0; i < NUM_BUTTONS; i++)
    {
        vrclear_buttons[i].state = VR_MENU_ITEM_STATE_GROW_W;
    }

    return 1;
}

static void PlayDecideSound(int unused, int button)
{
    if (button == BUTTON_NEXT)
    {
        GM_SeSet2(0, 63, VRCLEAR_SE_MENU);
    }

    if (button == BUTTON_RETRY)
    {
        GM_SeSet2(0, 63, VRCLEAR_SE_MENU);
    }

    if (button == BUTTON_EXIT)
    {
        GM_SeSet2(0, 63, VRCLEAR_SE_EXIT);
    }

    if (button == BUTTON_SAVE)
    {
        GM_SeSet2(0, 63, VRCLEAR_SE_EXIT);
    }
}

static void DrawDemo(void)
{
    MENU_Color(200, 200, 200);
    MENU_Locate(8, 8, 0x10);
    MENU_Printf("DEMO");

    MENU_Color(10, 10, 10);
    MENU_Locate(9, 9, 0x10);
    MENU_Printf("DEMO");
}

static void DrawReplay(void)
{
    MENU_Color(200, 200, 200);
    MENU_Locate(8, 8, 0x10);
    MENU_Printf("REPLAY");

    MENU_Color(10, 10, 10);
    MENU_Locate(9, 9, 0x10);
    MENU_Printf("REPLAY");
}

static void DrawReplayLabel(Work *work)
{
    work->blink++;

    if (work->blink >= 16 && work->replay)
    {
        if (VR_Flags & VRFLAG_RESULT)
        {
            DrawReplay();
        }
        else
        {
            DrawDemo();
        }
    }
}

static void PrintTwoDigits(int value, char *buf)
{
    buf[1] = (value % 10) + '0';
    buf[0] = ((value / 10) % 10) + '0';
}

// formats a time in frames as "MM:SS:CC"
static void FormatTime(char *buf, int time, int mode, Work *work)
{
    char    cents_str[8];
    char    secs_str[8];
    char    mins_str[8];
    int     total;
    int     secs, mins, cents;
    u_char  digit;
    u_char  jitter;
    int     ammo;

    time = (time < 0) ? 0 : time;

    if (mode != 0)
    {
        total = VR_Records[3];
    }
    else
    {
        total = time;
    }

    if (mode == 3)
    {
        time = total;

        if (work->mode == MODE_ADVANCED)
        {
            switch (VR_FoundCount)
            {
            case 0:
                time = total + 90;
                break;

            case 1:
                time = total + 30;
                break;
            }
        }
    }

    cents = ((time % 30) * 100) / 30;
    time /= 30;
    secs = time - (time / 60) * 60;
    mins = time / 60;
    digit = (((total % 30) * 100) / 30) % 10;
    jitter = ((total % 30) / 3) * ((total / 30) + digit * 29);
    jitter >>= 1;

    if (digit == 6)
    {
        jitter &= 3;
    }
    else
    {
        jitter %= 3;
    }

    cents += jitter;

    ammo = linkvarbuf[work->weapon + 16] * work->unit;
    if (mode == 3)
    {
        cents += ((ammo % 30) * 100) / 30;
        secs += cents / 100;
        secs += ammo / 30;
        cents %= 100;
        mins += secs / 60;
        secs %= 60;
    }

    PrintTwoDigits(cents, cents_str);
    PrintTwoDigits(secs, secs_str);
    PrintTwoDigits(mins, mins_str);

    buf[8] = '\0';
    buf[7] = cents_str[1];
    buf[6] = cents_str[0];
    buf[5] = ':';
    buf[4] = secs_str[1];
    buf[3] = secs_str[0];
    buf[2] = ':';
    buf[1] = mins_str[1];
    buf[0] = mins_str[0];
}

static void DrawResult(int timer, Work *work)
{
    char  buf[16];
    char *ranks[4] = { "1st", "2nd", "3rd", "record" };
    int   ammo;
    int   unit;
    int   t;
    int   count;
    int   time;
    int   len;
    int   rank;
    int   y;
    int   i;

    if (!(VR_Flags & VRFLAG_RESULT))
    {
        return;
    }

    MENU_Color(208, 107, 57);

    if (VR_Flags & VRFLAG_AMMO_BONUS)
    {
        unit = work->unit;
        ammo = linkvarbuf[work->weapon + 16];

        t = timer - 30;
        t = (t < 0) ? 0 : t;

        count = ammo - t / 2;
        if (count < 0)
        {
            count = 0;
        }

        if (count != vrclear_last_count && t != 0)
        {
            GM_SeSet2(0, 63, VRCLEAR_SE_COUNT);
        }

        vrclear_last_count = count;

        if (t == 0)
        {
            time = VR_Records[3];
            if (time < 0)
            {
                time = 0;
            }

            FormatTime(buf, time, 3, work);
        }
        else
        {
            time = VR_Records[3] + unit * count;
            if (time < 0)
            {
                time = 0;
            }

            FormatTime(buf, time, 1, work);
        }

        MENU_Locate(159, 108, 0x10);
        MENU_Printf("%s", buf);

        MENU_Locate(99, 108, 0x10);
        MENU_Printf("%s", ranks[3]);

        MENU_Locate(219, 72, 0x11);
        MENU_Printf("%d", count);

        MENU_Locate(99, 72, 0x10);
        MENU_Printf("bullet   X");

        if ((ammo - (t + 1) / 2) < -15)
        {
            VR_Flags &= ~VRFLAG_AMMO_BONUS;
        }

        if (work->mode == MODE_ADVANCED)
        {
            MENU_Locate(160, 84, 0x12);

            switch (VR_FoundCount)
            {
            case 0:
                MENU_Printf("SNEAKING BONUS  -3 SEC");
                break;

            case 1:
                MENU_Printf("SNEAKING BONUS  -1 SEC");
                break;
            }
        }
    }
    else
    {
        len = 8;
        if (timer < 9)
        {
            len = timer;
        }

        rank = (u_int)(VR_Flags & VRFLAG_RANK_MASK) >> 1;
        if (rank >= 3)
        {
            rank = -1;
        }

        y = 60;

        if (rank >= 0 && ((timer + 15) % 30) == 0 && !work->replay)
        {
            GM_SeSet2(0, 63, VRCLEAR_SE_RECORD);
        }

        i = 0;
        if (work->replay)
        {
            i = 3;
        }

        for (; i < 4; i++)
        {
            if (i != rank || ((timer / 15) & 1))
            {
                time = VR_Records[i];
                if (time < 0)
                {
                    time = -time;
                }

                FormatTime(buf, time, 0, work);
                buf[len] = '\0';

                if (i == 3)
                {
                    y += 12;
                }

                if (VR_Records[i] > 0)
                {
                    MENU_Color(208, 107, 57);
                }
                else
                {
                    MENU_Color(104, 53, 28);
                }

                MENU_Locate(159, y, 0x10);
                MENU_Printf("%s", buf);

                MENU_Color(208, 107, 57);
                MENU_Locate(99, y, 0x10);
                MENU_Printf("%s", ranks[i]);
            }

            y += 12;
        }
    }
}

static void SetupMode(Work *work)
{
    int mode;
    int weapon_name;

    if (work->category < 5)
    {
        if (work->stage < 20)
        {
            work->level = work->stage;

            mode = 3;
            if (!(work->category & 1))
            {
                mode = 4;
            }
            work->mode = mode;

            weapon_name = 1;
            if (work->category < 3)
            {
                weapon_name = 2;
            }
            work->weapon_name = weapon_name;
        }
        else
        {
            work->level = work->stage % 10;
            work->weapon_name = work->stage / 10;

            if (work->category < 3)
            {
                work->mode = work->category;
            }
            else
            {
                work->mode = work->category + 2;
            }
        }
    }
    else
    {
        work->weapon_name = 0;
        work->mode = work->category + 2;
        work->level = work->stage % 10;

        if (work->category < 7)
        {
            work->level = 0;
            work->weapon_name = work->stage % 10;
        }

        if (work->level == 0 && work->mode == MODE_MYSTERY)
        {
            work->level = 10;
        }
    }

    if (work->weapon_name >= NUM_WEAPONS)
    {
        work->weapon_name = NUM_WEAPONS - 1;
    }

    if (work->mode >= NUM_MODES)
    {
        work->mode = NUM_MODES - 1;
    }
}

char *vrclear_mode_names[NUM_MODES] = {
    "",
    "WEAPON MODE",
    "WEAPON MODE",
    "SNEAKING MODE",
    "SNEAKING MODE",
    "ADVANCED MODE",
    "ADVANCED MODE",
    "1 MIN. BATTLE - VS. ENEMY",
    "1 MIN. BATTLE - VS. TARGET",
    "NINJA",
    "",
    "PUZZLE",
    "MYSTERY",
    "VS. 12 BATTLE",
    "",
    "VR MISSION",
    "VARIETY"
};

char *vrclear_weapon_names[NUM_WEAPONS] = {
    "",
    "NO WEAPON",
    "SOCOM",
    "C4",
    "FAMAS",
    "GRENADE",
    "CLAYMORE",
    "NIKITA",
    "PSG1",
    "STINGER"
};

static void DrawTitle(Work *work)
{
    char level[3];
    int  y;
    int  i;
    int  top, bottom;

    level[2] = '\0';
    level[1] = (work->level % 10) + '0';
    level[0] = (work->level / 10) + '0';

    y = 0;
    if (!(VR_Flags & VRFLAG_RESULT))
    {
        y = 15;
    }

    if (work->state == MENU_HIDDEN)
    {
        return;
    }

    if (work->title_x > 160)
    {
        if (work->title_x == 320)
        {
            GM_SeSet2(0, 63, VRCLEAR_SE_TITLE);
        }

        work->title_x -= 20;
    }

    top = y + 25;
    bottom = y + 40;

    for (i = 0; i < 2; i++)
    {
        if (i != 0)
        {
            MENU_Color(50, 50, 50);
        }
        else
        {
            MENU_Color(200, 200, GV_Clock * 200);
        }

        if (work->custom_title)
        {
            MENU_Locate(work->title_x + i, top + i, 0x12);
            MENU_Printf("%s", work->title[0]);
            MENU_Locate(FRAME_WIDTH - work->title_x + i, bottom + i, 0x12);
            MENU_Printf("%s", work->title[1]);
        }
        else if (work->level != 0)
        {
            MENU_Locate(work->title_x + i, top + i, 0x12);

            if (work->weapon_name != 0)
            {
                MENU_Printf("%s - %s", vrclear_mode_names[work->mode], vrclear_weapon_names[work->weapon_name]);
            }
            else
            {
                MENU_Printf("%s %s", vrclear_mode_names[work->mode], vrclear_weapon_names[0]);
            }

            MENU_Locate(FRAME_WIDTH - work->title_x + i, bottom + i, 0x12);
            MENU_Printf("LEVEL %s  CLEARED", level);
        }
        else
        {
            MENU_Locate(work->title_x + i, top + i, 0x12);
            MENU_Printf("%s", vrclear_mode_names[work->mode]);
            MENU_Locate(FRAME_WIDTH - work->title_x + i, bottom + i, 0x12);
            MENU_Printf("%s  CLEARED", vrclear_weapon_names[work->weapon_name]);
        }
    }
}

static int MoveCursor(Work *work)
{
    GV_PAD *pad;
    int     status;
    int     dir;
    short   next;

    pad = &GV_PadData[2];
    status = pad->status;

    if (status == work->last_pad)
    {
        if (work->repeat-- > 0)
        {
            return 0;
        }

        work->repeat = 1;
    }
    else
    {
        work->last_pad = status;
        work->repeat = 10;
    }

    if (status & PAD_UDLR)
    {
        if (status & PAD_LEFT)
        {
            dir = LINK_LEFT;
        }
        else if (status & PAD_DOWN)
        {
            dir = LINK_DOWN;
        }
        else if (status & PAD_RIGHT)
        {
            dir = LINK_RIGHT;
        }
        else
        {
            dir = LINK_UP;
        }

        next = vrclear_buttons[work->cur].link[dir];
        if (next != -1)
        {
            if (vrclear_buttons[next].tex_id <= 0)
            {
                do
                {
                    next = vrclear_buttons[next].link[dir];
                    if (next == -1)
                    {
                        return 0;
                    }
                } while (vrclear_buttons[next].tex_id <= 0);
            }

            work->sel = next;
            work->state = MENU_SELECT;
            GM_SeSet2(0, 63, VRCLEAR_SE_CURSOR);
            return 0;
        }
    }

    status = pad->press;
    if ((status & PAD_CIRCLE) && vrclear_buttons[work->cur].proc >= 0)
    {
        VR_MENU_ITEM *button;
        int       n;

        work->state = MENU_DECIDED;

        button = vrclear_buttons;
        n = work->n_buttons;
        while (n != 0)
        {
            n--;
            button->state = VR_MENU_ITEM_STATE_SHRINK_H;
            button->step = 0;
            button++;
        }

        vrclear_buttons[work->cur].state = VR_MENU_ITEM_STATE_OPEN;
        PlayDecideSound(0, work->cur);
    }

    return 0;
}

static int CheckPad(Work *work)
{
    int status;

    status = GV_PadData[2].status;
    if (status != work->last_pad)
    {
        work->repeat = 10;
        work->last_pad = status;

        if (status & (PAD_UDLR | PAD_ABXY))
        {
            return 1;
        }
    }

    return 0;
}

static void LoadReplayData(Work *work)
{
    RECT     rect1 = { 0, 224, 160, 32 };
    RECT     rect2 = { 320, 224, 2, 1 };
    u_short *data;

    data = GV_GetCache(GV_CacheID(GV_StrCode("replay"), 'c'));
    vrclear_replay_data = data + 1;
    work->has_replay = (data[1] != 0);

    LoadImage(&rect1, (u_long *)(data + 1));
    DrawSync(0);

    LoadImage(&rect2, (u_long *)&VR_Records[3]);
    DrawSync(0);
}

static int CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     n_msgs;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == MSG_OPEN)
        {
            return MSG_OPEN;
        }

        if (msg->message[0] == GV_StrCode("clear"))
        {
            work->act_state = ACT_INIT;
        }
    }

    return 0;
}

static void DrawWindow(Work *work)
{
    RECT rect;

    if (work->win_h < 111)
    {
        work->win_h += 12;
    }
    else
    {
        work->win_h = 111;
    }

    if (work->win_w < 160)
    {
        work->win_w += 12;
    }
    else
    {
        work->win_w = 160;
    }

    rect.x = work->win_w;
    rect.y = work->win_h;
    rect.w = FRAME_WIDTH - work->win_w * 2;
    rect.h = FRAME_HEIGHT - work->win_h * 2;
    SetDrawArea(&work->area[0], &rect);

    rect.x = work->win_w + FRAME_WIDTH;
    rect.y = work->win_h;
    rect.w = FRAME_WIDTH - work->win_w * 2;
    rect.h = FRAME_HEIGHT - work->win_h * 2;
    SetDrawArea(&work->area[1], &rect);

    if ((work->timer << 6) > 320)
    {
        // FIXME: written as *(env + n) so the address is summed as (n * 64) + work
        *(work->env + GV_Clock) = DG_Chanl(0)->env1[GV_Clock];
        addPrim(DG_ChanlOTag(0) + 196, &work->area[GV_Clock]);
        addPrim(DG_ChanlOTag(0), &work->env[GV_Clock]);
    }
}

static void Draw(Work *work)
{
    VR_MENU_ITEM *button;
    int       n;
    int       busy;
    int       skip;

    if (!(GM_PlayerStatus & PLAYER_PAD_OFF))
    {
        GM_PlayerStatus |= PLAYER_PAD_OFF;
    }

    DrawTitle(work);

    switch (work->state)
    {
    case MENU_SELECT:
        work->cur = work->sel;

        button = vrclear_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);
            button++;
        }

        DrawResult(work->timer++, work);
        DrawWindow(work);

        if (!(VR_Flags & VRFLAG_AMMO_BONUS))
        {
            MoveCursor(work);
            VrMenu_UpdateFrame(&work->cursor, &vrclear_buttons[work->sel].label,
                              work->cursor_polys[GV_Clock], &work->cursor_tiles[GV_Clock]);
        }
        else if (CheckPad(work))
        {
            skip = linkvarbuf[work->weapon + 16] * 2 + 30;
            if (skip < work->timer)
            {
                skip = work->timer;
            }

            work->timer = skip;
        }
        break;

    case MENU_IDLE:
        break;

    case MENU_WAIT_OPEN:
        if (OpenButtons(CheckMessage(work)))
        {
            work->state = MENU_SELECT;
            work->timer = 0;

            if (work->voice[0] != 0 && !work->replay)
            {
                GM_StreamPlayStart();
            }

            work->last_pad = GV_PadData[2].status;
        }
        break;

    case MENU_OPEN_WINDOW:
        DrawWindow(work);
        work->timer++;
        break;

    case MENU_DECIDED:
    case MENU_CLOSING:
        busy = 0;

        button = vrclear_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);

            if (button != &vrclear_buttons[work->cur])
            {
                busy |= (button->state != VR_MENU_ITEM_STATE_CLOSED && button->state != VR_MENU_ITEM_STATE_OPEN);
            }

            button++;
        }

        DrawResult(work->timer++, work);
        DrawWindow(work);

        if (!busy && work->state == MENU_DECIDED)
        {
            if (work->cur == BUTTON_EXIT && work->replay)
            {
                GCL_SetVar(work->stage_var, -1);
            }

            if (work->cur == BUTTON_NEXT && !(VR_Flags & VRFLAG_NO_NEXT))
            {
                work->fade = 1;
                NewFadeInOut(FADEIO_MODE_TOBLACK, 10);
            }
            else
            {
                VrMenu_ExecItem(&vrclear_buttons[work->cur]);
            }

            work->state = MENU_CLOSING;
        }

        VrMenu_UpdateFrame(&work->cursor, &vrclear_buttons[work->sel].label,
                          work->cursor_polys[GV_Clock], &work->cursor_tiles[GV_Clock]);
        break;

    case MENU_HIDDEN:
        DrawWindow(work);

        button = vrclear_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);
            button++;
        }
        break;
    }
}

static void Init(Work *work)
{
    char  units[10] = { 10, 1, 10, 10, 10, 30, 10, 10, 10, 10 };
    RECT  rect;
    int   i;
    int   rank;
    DG_TEX   *tex;

    for (i = 0; linkvarbuf[i + 17] < 0; i++)
    {
        if (i >= 11)
        {
            break;
        }
    }

    if (i == 10)
    {
        work->weapon = 1;
        work->unit = 0;
        GM_SocomFlag = 0;
    }
    else
    {
        work->weapon = i + 1;
        if ((u_char)i < 10)
        {
            work->unit = units[work->weapon - 1];
        }
    }

    if (work->voice_flag == 0)
    {
        VR_Flags &= ~VRFLAG_AMMO_BONUS;
    }

    if (work->voice_flag == 16)
    {
        VR_Flags = 0;
    }

    if (work->category != 0 && !work->replay)
    {
        SetClearFlag(work->category, work->stage);
    }

    rank = (u_int)(VR_Flags & VRFLAG_RANK_MASK) >> 1;
    LoadReplayData(work);

    if (work->category >= 5)
    {
        work->has_replay = 0;
    }

    if ((VR_Flags & VRFLAG_RESULT) && work->has_replay)
    {
        work->n_buttons = 4;
        vrclear_buttons[BUTTON_RETRY].link[LINK_UP] = BUTTON_SAVE;
    }
    else
    {
        work->n_buttons = 3;
        vrclear_buttons[BUTTON_RETRY].link[LINK_UP] = -1;
    }

    if (rank >= 3)
    {
        rank = -1;
    }

    if (work->voice[0] != 0)
    {
        if ((VR_Flags & VRFLAG_RESULT) && rank != -1)
        {
            GM_VoxStream(work->voice[rank], 0x40000000);
        }
        else
        {
            GM_VoxStream(work->voice[3], 0x40000000);
        }
    }

    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    SetDrawArea(&work->area[0], &rect);
    SetDrawArea(&work->area[1], &rect);

    if (vrclear_buttons[BUTTON_RETRY].proc == vrclear_buttons[BUTTON_EXIT].proc)
    {
        work->sel = BUTTON_EXIT;

        if ((VR_Flags & VRFLAG_RESULT) && work->has_replay)
        {
            vrclear_buttons[BUTTON_NEXT].link[LINK_UP] = BUTTON_SAVE;
            vrclear_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_NEXT;
            vrclear_buttons[BUTTON_SAVE].rect.y = vrclear_buttons[BUTTON_RETRY].rect.y;
            vrclear_buttons[BUTTON_SAVE].label.y = vrclear_buttons[BUTTON_RETRY].label.y;
        }
        else
        {
            vrclear_buttons[BUTTON_NEXT].link[LINK_UP] = -1;
            vrclear_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_RETRY;
        }

        vrclear_buttons[BUTTON_RETRY].rect.w = 0;
        vrclear_buttons[BUTTON_RETRY].rect.h = 0;
        vrclear_buttons[BUTTON_RETRY].rect.x = 0;
    }
    else
    {
        work->sel = BUTTON_RETRY;
    }

    if (VR_Flags & VRFLAG_NO_NEXT)
    {
        work->sel = BUTTON_EXIT;
    }

    if ((VR_Flags & VRFLAG_RESULT) && work->has_replay)
    {
        work->sel = BUTTON_SAVE;
    }

    if (work->replay == 1)
    {
        work->sel = BUTTON_EXIT;

        vrclear_buttons[BUTTON_NEXT].link[LINK_UP] = -1;
        vrclear_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_RETRY;
        vrclear_buttons[BUTTON_RETRY].rect.w = 0;
        vrclear_buttons[BUTTON_RETRY].rect.h = 0;
        vrclear_buttons[BUTTON_RETRY].rect.x = 0;
        work->n_buttons = 3;

        vrclear_buttons[BUTTON_NEXT].tex_id = GV_StrCode("replay");
        tex = DG_GetTexture(vrclear_buttons[BUTTON_NEXT].tex_id);
        vrclear_buttons[BUTTON_NEXT].tex = tex;
        DG_SetPacketTexture4(&vrclear_buttons[BUTTON_NEXT].polys[0], tex);
        DG_SetPacketTexture4(&vrclear_buttons[BUTTON_NEXT].polys[1], tex);

        vrclear_buttons[BUTTON_NEXT].rect.w = 56;
        vrclear_buttons[BUTTON_NEXT].rect.h = 8;
        vrclear_buttons[BUTTON_NEXT].rect.x = 132;
        vrclear_buttons[BUTTON_NEXT].label.w = 76;
        vrclear_buttons[BUTTON_NEXT].label.h = 14;
        vrclear_buttons[BUTTON_NEXT].label.x = 121;
    }

    work->cur = BUTTON_CURSOR;
    work->state = MENU_WAIT_OPEN;
    work->count = 0;
    work->win_h = 0;
    work->win_w = 0;

    if ((VR_Flags & (VRFLAG_RESULT | VRFLAG_NO_NEXT)) == VRFLAG_NO_NEXT)
    {
        work->state = MENU_OPEN_WINDOW;
    }

    VrMenu_InitFrame(work->cursor_polys[0], work->cursor_tiles, VrMenu_LoadFrameTexture());

    work->cursor.x = 160;
    work->cursor.y = 112;
    work->cursor.w = 0;
    work->cursor.h = 0;
}

static void Act(Work *work)
{
    switch (work->act_state)
    {
    case ACT_WAIT:
        DrawReplayLabel(work);
        CheckMessage(work);
        break;

    case ACT_INIT:
        Init(work);
        work->act_state++;
        break;

    case ACT_MAIN:
        Draw(work);

        if (work->fade != 0)
        {
            if (work->fade == 12)
            {
                GM_LoadRequest = LOADREQ_GAMEOVER;
                work->fade = 0;
            }
            else
            {
                work->fade++;
            }
        }
        break;
    }
}

static void Die(Work *work)
{
}

static int GetResources(Work *work, int where)
{
    int   procs[NUM_BUTTONS];
    int  *proc;
    char *opt;
    int   n;
    int   i;

    GM_CurrentMap = where;
    work->title_x = 320;

    opt = GCL_GetOption('c');
    if (opt)
    {
        work->voice_flag = GCL_StrToInt(opt);
    }
    else
    {
        work->voice_flag = 1;
    }

    opt = GCL_GetOption('p');
    if (opt)
    {
        n = GCL_StrToInt(opt);
        if (n == 4)
        {
            n = 3;
        }

        proc = procs;
        while (n != 0)
        {
            n--;
            *proc++ = GCL_StrToInt(GCL_NextStr());
        }
    }

    opt = GCL_GetOption('s');
    work->stage_var = opt;
    if (opt)
    {
        work->stage = GCL_StrToInt(opt);
        work->category = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->stage = 0;
        work->category = 0;
    }

    SetupMode(work);

    work->title[1] = "";
    work->title[0] = "";
    work->custom_title = 0;

    if (GCL_GetOption('z'))
    {
        work->custom_title = 1;

        for (i = 0; i < 2; i++)
        {
            work->title[i] = GCL_GetString(GCL_NextStr());
        }
    }

    VR_FoundCount = 0;
    if (work->mode != MODE_ADVANCED || work->custom_title)
    {
        VR_FoundCount = 2;
    }

    if (work->mode == MODE_NINJA && !work->custom_title)
    {
        VR_FoundCount = 3;
    }

    opt = GCL_GetOption('d');
    if (opt)
    {
        work->replay = GCL_StrToInt(opt);
    }
    else
    {
        work->replay = 0;
    }

    if (GCL_GetOption('t'))
    {
        for (i = 0; i < 4; i++)
        {
            work->voice[i] = GCL_StrToInt(GCL_NextStr());
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            work->voice[i] = 0;
        }
    }

    n = 0;
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        if (VrMenu_InitItem(&vrclear_buttons[i], procs[n], 1))
        {
            n++;
        }
    }

    vrclear_buttons[BUTTON_SAVE].proc = GV_StrCode(PROC_GO_VRSAVE);

    work->fade = 0;
    work->f3B0_4 = 0;
    work->blink = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVrClear(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrclear.c");

        work->act_state = ACT_WAIT;

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
