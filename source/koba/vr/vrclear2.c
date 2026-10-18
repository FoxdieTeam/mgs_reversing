#include "vrclear2.h"

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
#include "vr.h"
#include "vrmenu.h"

/*---------------------------------------------------------------------------*/
// VR-DISC "VRCLEAR2": the "MISSION CLEARED" screen of the ADVANCED VR missions (vab_* overlays), a sibling of
// vrclear.c (result times, record table, RETRY / NEXT / EXIT / SAVE menu) with a bigger Work and a different
// result page.
//
// FIXME: only the functions that do not use the Work are in C so far, the rest is relocatable asm
// (INCLUDE_ASM_RELOC, build/gen_reloc_obj.py) that keeps this object shareable between overlays.

#define EXEC_LEVEL          GV_ACTOR_AFTER2

#define MSG_OPEN            0xEDAF              // opens the menu buttons

// The VR-DISC has its own sound effect table
#define VRCLEAR_SE_MENU     102
#define VRCLEAR_SE_EXIT     33
#define VRCLEAR_SE_CURSOR   31

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

// Work::state (menu)
#define MENU_SELECT         0
#define MENU_IDLE           1
#define MENU_WAIT_OPEN      2
#define MENU_DECIDED        3
#define MENU_OPEN_WINDOW    4
#define MENU_CLOSING        5
#define MENU_HIDDEN         6

// Work::act_state
#define ACT_WAIT            0                   // waits for the "clear" message
#define ACT_INIT            1
#define ACT_MAIN            2

// The Work of vrclear.c with a few more fields (the fields that are not used by the C functions are still unknown)
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
    char        pad_40[0x30];           // 0x040
    DR_AREA     area[2];                // 0x070
    DR_ENV      env[2];                 // 0x088
    int         last_pad;               // 0x108
    RECT        cursor;                 // 0x10C
    POLY_FT4    cursor_polys[2][8];     // 0x114
    TILE        cursor_tiles[2];        // 0x394
    short       pad_3B4;                // 0x3B4
    short       repeat;                 // 0x3B6
    u_char      weapon;                 // 0x3B8
    u_char      unit;                   // 0x3B9 frames per remaining bullet
    u_char      n_buttons;              // 0x3BA
    char        pad_3BB;                // 0x3BB
    char       *title[2];               // 0x3BC
    char       *stage_var;              // 0x3C4
    int         f3C8;                   // 0x3C8
    short       title_x;                // 0x3CC
    short       pad_3CE;                // 0x3CE
    int         win_h;                  // 0x3D0
    int         win_w;                  // 0x3D4
    int         stage;                  // 0x3D8
    int         category;               // 0x3DC
    int         mode;                   // 0x3E0
    int         weapon_name;            // 0x3E4
    char        pad_3E8[4];             // 0x3E8
    int         act_state;              // 0x3EC
    int         voice_flag;             // 0x3F0
    u_int       replay : 1;             // 0x3F4
    u_int       f3F4_1 : 1;
    u_int       has_replay : 1;
    u_int       custom_title : 1;
    u_int       blink : 5;
} Work;                                 // 0x3F8

/*---------------------------------------------------------------------------*/

// bss of the original vrclear2.c
u_long   SECTION(".bss") vrclear2_flags[16][6];
u_short *SECTION(".bss") vrclear2_replay_data;

// initialised data of the original vrclear2.c: the menu buttons, followed by the mode/weapon name tables
// (defined by the relocatable asm)
extern VR_MENU_ITEM vrclear2_buttons[NUM_BUTTONS];

// still in the relocatable asm
void Vrclear2DrawTitle(Work *work);
void Vrclear2DrawResult(int timer, Work *work);
int Vrclear2GetResources(Work *work, int where);

/*---------------------------------------------------------------------------*/

static void SetClearFlag(int category, int stage)
{
    RECT   rect = { 160, 224, 12, 16 };
    int    word;
    u_long flags;


    StoreImage(&rect, vrclear2_flags);
    DrawSync(0);

    if (stage > 0)
    {
        word = stage >> 5;
        printf("stage = %d\n", stage);
        printf("area = %d\n", word);
        flags = vrclear2_flags[category - 1][word];
        flags |= 1 << (stage - (word << 5));
        vrclear2_flags[category - 1][word] = flags;
        printf("clearflags[%d][%d] = %d\n", category - 1, word, 1 << (stage - (word << 5)));
    }

    LoadImage(&rect, vrclear2_flags);
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
        vrclear2_buttons[i].state = VR_MENU_ITEM_STATE_GROW_W;
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

/*---------------------------------------------------------------------------*/

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

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2_0.s")

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

        next = vrclear2_buttons[work->cur].link[dir];
        if (next != -1)
        {
            if (vrclear2_buttons[next].tex_id <= 0)
            {
                do
                {
                    next = vrclear2_buttons[next].link[dir];
                    if (next == -1)
                    {
                        return 0;
                    }
                } while (vrclear2_buttons[next].tex_id <= 0);
            }

            work->sel = next;
            work->state = MENU_SELECT;
            GM_SeSet2(0, 63, VRCLEAR_SE_CURSOR);
            return 0;
        }
    }

    status = pad->press;
    if ((status & PAD_CIRCLE) && vrclear2_buttons[work->cur].proc >= 0)
    {
        VR_MENU_ITEM *button;
        int           n;

        work->state = MENU_DECIDED;

        button = vrclear2_buttons;
        n = work->n_buttons;
        while (n != 0)
        {
            n--;
            button->state = VR_MENU_ITEM_STATE_SHRINK_H;
            button->step = 0;
            button++;
        }

        vrclear2_buttons[work->cur].state = VR_MENU_ITEM_STATE_OPEN;
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
    int           n;
    int           busy;
    int           skip;

    Vrclear2DrawTitle(work);

    switch (work->state)
    {
    case MENU_SELECT:
        work->cur = work->sel;

        button = vrclear2_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);
            button++;
        }

        Vrclear2DrawResult(work->timer++, work);
        DrawWindow(work);

        if (!(VR_Flags & VRFLAG_AMMO_BONUS))
        {
            MoveCursor(work);
            VrMenu_UpdateFrame(&work->cursor, &vrclear2_buttons[work->sel].label,
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
        work->count++;

        if (OpenButtons(CheckMessage(work)))
        {
            work->state = MENU_SELECT;
            work->count = 0;
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

        button = vrclear2_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);

            if (button != &vrclear2_buttons[work->cur])
            {
                busy |= (button->state != VR_MENU_ITEM_STATE_CLOSED && button->state != VR_MENU_ITEM_STATE_OPEN);
            }

            button++;
        }

        Vrclear2DrawResult(work->timer++, work);
        DrawWindow(work);

        if (!busy && work->state == MENU_DECIDED)
        {
            if (work->cur == BUTTON_EXIT && work->replay)
            {
                GCL_SetVar(work->stage_var, -1);
            }

            // FIXME: executed twice, the fade out of vrclear.c is missing here
            VrMenu_ExecItem(&vrclear2_buttons[work->cur]);
            work->state = MENU_CLOSING;
            VrMenu_ExecItem(&vrclear2_buttons[work->cur]);
            work->state = MENU_CLOSING;
        }

        VrMenu_UpdateFrame(&work->cursor, &vrclear2_buttons[work->sel].label,
                          work->cursor_polys[GV_Clock], &work->cursor_tiles[GV_Clock]);
        break;

    case MENU_HIDDEN:
        DrawWindow(work);

        button = vrclear2_buttons;
        for (n = work->n_buttons; n != 0; n--)
        {
            VrMenu_DrawItem(button);
            button++;
        }
        break;
    }
}

// Init does not byte-match from C (the schedule of the loads of VR_Flags / Work::flags around the rank and the
// button count differs, and the rank lives in a1 instead of a0), so the original code is kept as RELOCATABLE asm.
void Vrclear2Init(Work *work);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2_1.s")

#if 0 /* NON_MATCHING best C attempt */
static void Init(Work *work)
{
    char    units[10] = { 10, 1, 10, 10, 10, 30, 10, 10, 10, 10 };
    RECT    rect;
    int     i;
    int     rank;
    DG_TEX *tex;

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
    work->has_replay = 0;
    work->n_buttons = 3;
    vrclear2_buttons[BUTTON_RETRY].link[LINK_UP] = -1;

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

    if (vrclear2_buttons[BUTTON_RETRY].proc == vrclear2_buttons[BUTTON_EXIT].proc)
    {
        work->sel = BUTTON_EXIT;

        if ((VR_Flags & VRFLAG_RESULT) && work->has_replay)
        {
            vrclear2_buttons[BUTTON_NEXT].link[LINK_UP] = BUTTON_SAVE;
            vrclear2_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_NEXT;
            vrclear2_buttons[BUTTON_SAVE].rect.y = vrclear2_buttons[BUTTON_RETRY].rect.y;
            vrclear2_buttons[BUTTON_SAVE].label.y = vrclear2_buttons[BUTTON_RETRY].label.y;
        }
        else
        {
            vrclear2_buttons[BUTTON_NEXT].link[LINK_UP] = -1;
            vrclear2_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_RETRY;
        }

        vrclear2_buttons[BUTTON_RETRY].rect.w = 0;
        vrclear2_buttons[BUTTON_RETRY].rect.h = 0;
        vrclear2_buttons[BUTTON_RETRY].rect.x = 0;
    }
    else
    {
        work->sel = BUTTON_RETRY;
    }

    if (VR_Flags & VRFLAG_NO_NEXT)
    {
        work->sel = BUTTON_NEXT;
    }

    if ((VR_Flags & VRFLAG_RESULT) && work->has_replay)
    {
        work->sel = BUTTON_SAVE;
    }

    if (work->replay == 1)
    {
        work->sel = BUTTON_EXIT;

        vrclear2_buttons[BUTTON_NEXT].link[LINK_UP] = -1;
        vrclear2_buttons[BUTTON_SAVE].link[LINK_DOWN] = BUTTON_RETRY;
        vrclear2_buttons[BUTTON_RETRY].rect.w = 0;
        vrclear2_buttons[BUTTON_RETRY].rect.h = 0;
        vrclear2_buttons[BUTTON_RETRY].rect.x = 0;
        work->n_buttons = 3;

        vrclear2_buttons[BUTTON_NEXT].tex_id = GV_StrCode("replay");
        tex = DG_GetTexture(vrclear2_buttons[BUTTON_NEXT].tex_id);
        vrclear2_buttons[BUTTON_NEXT].tex = tex;
        DG_SetPacketTexture4(&vrclear2_buttons[BUTTON_NEXT].polys[0], tex);
        DG_SetPacketTexture4(&vrclear2_buttons[BUTTON_NEXT].polys[1], tex);

        vrclear2_buttons[BUTTON_NEXT].rect.w = 56;
        vrclear2_buttons[BUTTON_NEXT].rect.h = 8;
        vrclear2_buttons[BUTTON_NEXT].rect.x = 132;
        vrclear2_buttons[BUTTON_NEXT].label.w = 76;
        vrclear2_buttons[BUTTON_NEXT].label.h = 14;
        vrclear2_buttons[BUTTON_NEXT].label.x = 121;
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
#endif

static void Act(Work *work)
{
    switch (work->act_state)
    {
    case ACT_WAIT:
        if (VR_Flags & VRFLAG_RESULT)
        {
            work->replay = 0;
        }
        else
        {
            work->replay = 1;
        }

        CheckMessage(work);
        DrawReplayLabel(work);
        break;

    case ACT_INIT:
        Vrclear2Init(work);
        work->act_state++;
        break;

    case ACT_MAIN:
        Draw(work);
        break;
    }
}

static void Die(Work *work)
{
}

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2_2.s")

void *NewVrClear2(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vrclear2.c");

        work->act_state = ACT_WAIT;

        if (Vrclear2GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
