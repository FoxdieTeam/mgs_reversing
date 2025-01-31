#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"

typedef struct SecondWork
{
    GV_ACT actor;
    int    field_20;
    int    field_24;
    char  *field_28;
} SecondWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern GV_PAD GV_PadData_800B05C0[4];
extern int    GM_PlayerStatus;

void s07c_second_800C56A0(SecondWork *work)
{
    if (GV_PadData_800B05C0[1].status && work->field_20 == 0)
    {
        work->field_20 = 1;
        printf("SECOND!!\n");
        MENU_JimakuWrite(work->field_28, 20000);
    }
    else if (work->field_20 == 1 && GV_PadData_800B05C0[0].status)
    {
        work->field_20 = 0;
        MENU_JimakuClear();
    }
}

GV_ACT *s07c_second_800C5728(int name, int where, int argc, char **argv)
{
    SecondWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SecondWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s07c_second_800C56A0, NULL, "second.c");
        work->field_28 = GCL_ReadString(GCL_GetParamResult());
        work->field_20 = 0;
    }
    return &work->actor;
}

int s07c_second_800C5790(void)
{
    GM_PlayerStatus |= PLAYER_SECOND_AVAILABLE;
    return 1;
}
