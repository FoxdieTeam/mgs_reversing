#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT actor;
    int    using_pad2;
    int    _unused1;
    char  *message;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (GV_PadData[1].status && work->using_pad2 == FALSE)
    {
        work->using_pad2 = TRUE;
        printf("SECOND!!\n");
        MENU_JimakuWrite(work->message, 20000);
    }
    else if (work->using_pad2 == TRUE && GV_PadData[0].status)
    {
        work->using_pad2 = FALSE;
        MENU_JimakuClear();
    }
}

/*---------------------------------------------------------------------------*/

void *NewSecond(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, NULL, "second.c");
        work->message = GCL_ReadString(GCL_GetParamResult());
        work->using_pad2 = 0;
    }
    return (void *)work;
}

int GM_SetSecondAvailable(void)
{
    GM_PlayerStatus |= PLAYER_SECOND_AVAILABLE;
    return 1;
}
