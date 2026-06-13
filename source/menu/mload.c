#include "game/game.h"
#include "libgcl/libgcl.h"
#include "menu/radio.h"

void *NewMenuLoad(int name, int where)
{
    int proc_id;
    char *code;

    proc_id = GCL_GetNextInt();
    code = GCL_NextStr();
    MENU_SetLoad(proc_id, code, 1);
    return code;
}

static void Act(GV_ACT *work)
{
    gTotalFrameTime = 0;

    if (GM_LoadRequest != 0)
    {
        GV_DestroyActor(work);
    }
}

void *NewMenuSave(int name, int where)
{
    int proc_id;
    char *code;
    GV_ACT *work;

    proc_id = GCL_GetNextInt();
    code = GCL_NextStr();
    MENU_SetLoad(proc_id, code, 2);

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(GV_ACT));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, NULL, "mload.c");
    }
    return (void *)work;
}
