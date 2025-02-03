#include "motse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"

typedef struct MotseElem
{
    int param1;
    int param2;
} MotseElem;

typedef struct MotseWork
{
    GV_ACT     actor;
    int        field_20;
    int        field_24_count;
    MotseElem *field_28_elems;
} MotseWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

extern int              GM_PlayerAction;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern PlayerStatusFlag GM_PlayerStatus;
extern int              dword_800AB9D4;

void Motse_800C57CC(MotseWork *work)
{
    MotseElem *elem;
    int        i;

    if ((GM_PlayerStatus & PLAYER_ACT_ONLY) && GM_PlayerAction == work->field_20)
    {
        for (i = 0, elem = work->field_28_elems; i < work->field_24_count; i++, elem++)
        {
            if (elem->param1 == dword_800AB9D4)
            {
                GM_SeSetMode(&GM_PlayerControl_800AB9F4->mov, elem->param2, GM_SEMODE_BOMB);
                return;
            }
        }
    }
}

void Motse_800C5864(MotseWork *work)
{
    GV_DelayedFree(work->field_28_elems);
}

int Motse_800C5888(MotseWork *work, int name)
{
    int            i, count;
    unsigned char *param;
    MotseElem     *elems;

    work->field_20 = GCL_StrToInt(GCL_GetOption('m'));
    work->field_24_count = count = GCL_StrToInt(GCL_GetOption('n'));
    work->field_28_elems = elems = GV_Malloc(count * sizeof(MotseElem));

    GCL_GetOption('s');

    for (i = 0; (param = GCL_GetParamResult()) && i != count; i++, elems++)
    {
        elems->param1 = GCL_StrToInt(param);
        elems->param2 = GCL_StrToInt(GCL_GetParamResult());
    }

    return 0;
}

void *NewMotse_800C5944(int name, int where, int argc, char **argv)
{
    MotseWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(MotseWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Motse_800C57CC, Motse_800C5864, "motse.c");
        if (Motse_800C5888(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
