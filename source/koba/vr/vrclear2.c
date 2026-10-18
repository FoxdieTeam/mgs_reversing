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

#define MSG_OPEN            0xEDAF              // opens the menu buttons

// The VR-DISC has its own sound effect table
#define VRCLEAR_SE_MENU     102
#define VRCLEAR_SE_EXIT     33

#define BUTTON_NEXT         0                   // NEXT (or REPLAY) button
#define BUTTON_RETRY        1
#define BUTTON_EXIT         2
#define BUTTON_SAVE         3
#define NUM_BUTTONS         5

/*---------------------------------------------------------------------------*/

// bss of the original vrclear2.c
u_long   SECTION(".bss") vrclear2_flags[16][6];
u_short *SECTION(".bss") vrclear2_replay_data;

// initialised data of the original vrclear2.c: the menu buttons, followed by the mode/weapon name tables
// (defined by the relocatable asm)
extern VR_MENU_ITEM vrclear2_buttons[NUM_BUTTONS];

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

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2_0.s")
