#include "vrclear2.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
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
#define NUM_BUTTONS         5

// Work::state (menu)
#define MENU_SELECT         0
#define MENU_DECIDED        3

// Work::act_state
#define ACT_WAIT            0                   // waits for the "clear" message
#define ACT_INIT            1
#define ACT_MAIN            2

// The Work of vrclear.c with a few more fields (the fields not used by the C functions below are unknown yet)
typedef struct _Work
{
    GV_ACT      actor;                  // 0x000
    short       count;                  // 0x020
    short       cur;                    // 0x022 button that is selected
    short       sel;                    // 0x024 button under the cursor
    short       state;                  // 0x026
    int         name;                   // 0x028
    char        pad_2C[0xDC];           // 0x02C
    int         last_pad;               // 0x108
    char        pad_10C[0x2AA];         // 0x10C
    short       repeat;                 // 0x3B6
    char        pad_3B8[2];             // 0x3B8
    u_char      n_buttons;              // 0x3BA
    char        pad_3BB[0x3EC - 0x3BB]; // 0x3BB
    int         act_state;              // 0x3EC
    char        pad_3F0[4];             // 0x3F0
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
int Vrclear2GetResources(Work *work, int where);
void Vrclear2Init(Work *work);
void Vrclear2Draw(Work *work);

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

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2_1.s")

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
        Vrclear2Draw(work);
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
