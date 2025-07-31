#include "select.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

extern GV_PAD GV_PadData_800B05C0[4];

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL3

typedef struct Work
{
    GV_ACT         actor;
    unsigned char *gcl_menu_entries;
    char          *current_entry_name;
    int            current_entry_proc_id;
    int            current_idx;

    // when you are holding PAD_DOWN/PAD_UP
    // it will continue moving through entries,
    // this slows down the speed of this movement
    int            movement_delay_remaining;

    int            previous_dir;
} Work;

#ifdef DEV_EXE
int isStageSelectionMenu; // Used to print the extended info below only in stage selection menu.
char* extendedInfo[] = {
    "%s [ %d ]", // TITLE
    "%s: LOADING DOCK - CUTSCENE [ %d ]", // D00A
    "%s: LOADING DOCK [ %d ]", // S00A
    "%s: HELIPORT - CUTSCENE [ %d ]", // D01A
    "%s: HELIPORT - USING SCOPE [ %d ]", // S01A
    "%s: HELIPORT [ %d ]", // S01A1
    "%s: TANK HANGAR [ %d ]", // S02A
    "%s: TANK HANGAR 2 [ %d ]", // S02B
    "%s: TANK HANGAR - BEFORE CONTACTING MERYL [ %d ]", // S02C
    "%s: TANK HANGAR - AFTER CONTACTING MERYL [ %d ]", // S02D
    "%s: TANK HANGAR - AFTER TORTURE [ %d ]", // S02E
    "%s: HOLDING CELL [ %d ]", // S03A
    "%s: MEDICAL ROOM [ %d ]", // S03B
    "%s: MEDICAL ROOM 2 [ %d ]", // S03C
    "%s: ARMORY [ %d ]", // S04A
    "%s: ARMORY SOUTH - VS OCELOT [ %d ]", // S04B
    "%s [ %d ]" // RETURN
};
#endif // DEV_EXE

/*---------------------------------------------------------------------------*/

static void SelectUpdateCurrentEntry(Work *work, int dir)
{
    int   i;
    int   proc_id;
    char *entry_name;

    work->current_idx += dir;
#ifdef DEV_EXE
    // Circular scrolling (only in stage selection menu to keep things simple).
    if (work->current_idx < 0)
    {
        work->current_idx = isStageSelectionMenu ? 16 : 0;
    }
    else if (isStageSelectionMenu && work->current_idx > 16)
    {
        work->current_idx = 0;
    }
#else
    if (work->current_idx < 0)
    {
        work->current_idx = 0;
    }
#endif

    GCL_SetArgTop(work->gcl_menu_entries);
    for (i = 0; i <= work->current_idx; i++)
    {
        if (GCL_GetParamResult() == 0)
        {
            work->current_idx = i;
            break;
        }
        // entry_name = "s00a", "title", etc.
        entry_name = GCL_ReadString(GCL_GetParamResult());
        proc_id = GCL_StrToInt(GCL_GetParamResult());
    }
    work->current_entry_name = entry_name;
    work->current_entry_proc_id = proc_id;
}

// See also menu_radio_do_file_mode_helper13_8004BCF8() in datasave.c
static void Act(Work *work)
{
    int     dir;
    GV_PAD *pPad;
#ifdef DEV_EXE
    char stageInfo[55];
#endif

    pPad = &GV_PadData_800B05C0[0];

    if (pPad->status & (PAD_UP | PAD_DOWN))
    {
        dir = 1;
        if (pPad->status & PAD_UP)
        {
            dir = -1;
        }
        if (work->previous_dir == dir)
        {
            if (--work->movement_delay_remaining < 0)
            {
                SelectUpdateCurrentEntry(work, dir);
                work->movement_delay_remaining = 2;
            }
        }
        else
        {
            SelectUpdateCurrentEntry(work, dir);
            work->movement_delay_remaining = 10;
            work->previous_dir = dir;
        }
    }
    else
    {
        work->previous_dir = 0;
    }
    if (pPad->press & PAD_CIRCLE)
    {
        GCL_ExecProc(work->current_entry_proc_id, NULL);
        GV_DestroyActor(&work->actor);
    }
    menu_Text_Init_80038B98();
    MENU_Locate(160, 120, 2);

#ifdef DEV_EXE
    if (isStageSelectionMenu)
    {
        sprintf(stageInfo, extendedInfo[work->current_idx], work->current_entry_name, work->current_entry_proc_id);
    }
    else
    {
        strcpy(stageInfo, work->current_entry_name);
    }
    MENU_Printf(stageInfo);
#else
    MENU_Printf(work->current_entry_name);
#endif
}

static int GetResources(Work *work, int where, int name)
{
    if (!GCL_GetOption('s'))
    {
        printf("NO MENU\n");
        return -1;
    }

    work->gcl_menu_entries = GCL_GetParamResult();
    work->current_idx = 0;
    work->previous_dir = 0;
    SelectUpdateCurrentEntry(work, 0);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSelect(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, NULL, "select.c");
        if (GetResources(work, where, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

#ifdef DEV_EXE
    isStageSelectionMenu = name == 10524;
#endif

    return (void *)work;
}
