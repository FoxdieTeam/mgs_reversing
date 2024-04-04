#include "select.h"
#include "libgcl/libgcl.h"

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

extern GV_PAD GV_PadData_800B05C0[4];

#define EXEC_LEVEL 3

void SelectUpdateCurrentEntry_800C3218(Work *work, int dir)
{
    int   i;
    int   proc_id;
    char *entry_name;

    work->current_idx += dir;
    if (work->current_idx < 0)
    {
        work->current_idx = 0;
    }

    GCL_SetArgTop_80020690(work->gcl_menu_entries);
    for (i = 0; i <= work->current_idx; i++)
    {
        if (GCL_Get_Param_Result_80020AA4() == 0)
        {
            work->current_idx = i;
            break;
        }
        // entry_name = "s00a", "title", etc.
        entry_name = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        proc_id = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    work->current_entry_name = entry_name;
    work->current_entry_proc_id = proc_id;
}

void SelectAct_800C32D8(Work *work)
{
    int     dir;
    GV_PAD *pPad;

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
                SelectUpdateCurrentEntry_800C3218(work, dir);
                work->movement_delay_remaining = 2;
            }
        }
        else
        {
            SelectUpdateCurrentEntry_800C3218(work, dir);
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
        GCL_ExecProc_8001FF2C(work->current_entry_proc_id, NULL);
        GV_DestroyActor_800151C8(&work->actor);
    }
    menu_Text_Init_80038B98();
    MENU_Locate_80038B34(160, 120, 2);
    MENU_Printf_80038C38(work->current_entry_name);
}

int SelectGetResources_800C33D0(Work *work, int param_2, int param_3)
{
    if (!GCL_GetOption_80020968('s'))
    {
        printf("NO MENU\n");
        return -1;
    }

    work->gcl_menu_entries = GCL_Get_Param_Result_80020AA4();
    work->current_idx = 0;
    work->previous_dir = 0;
    SelectUpdateCurrentEntry_800C3218(work, 0);
    return 0;
}

GV_ACT *NewSelect_800C3434(int name, int where, int argc, char **argv)
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SelectAct_800C32D8, NULL, "select.c");
        if (SelectGetResources_800C33D0(work, where, name) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
