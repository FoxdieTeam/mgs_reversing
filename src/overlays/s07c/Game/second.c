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

extern GV_PAD GV_PadData_800B05C0[4];
extern int    GM_PlayerStatus_800ABA50;

void s07c_second_800C56A0(SecondWork *work)
{
    if (GV_PadData_800B05C0[1].status && work->field_20 == 0)
    {
        work->field_20 = 1;
        printf("SECOND!!\n");
        MENU_JimakuWrite_800494E8(work->field_28, 20000);
    }
    else if (work->field_20 == 1 && GV_PadData_800B05C0[0].status)
    {
        work->field_20 = 0;
        MENU_JimakuClear_80049518();
    }
}

GV_ACT *s07c_second_800C5728(int name, int where, int argc, char **argv)
{
    SecondWork *work;

    work = (SecondWork *)GV_NewActor(5, sizeof(SecondWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)s07c_second_800C56A0, NULL, "second.c");
        work->field_28 = GCL_ReadString(GCL_GetParamResult());
        work->field_20 = 0;
    }
    return &work->actor;
}

int s07c_second_800C5790(void)
{
    GM_PlayerStatus_800ABA50 |= PLAYER_CAN_USE_CONTROLLER_PORT_2;
    return 1;
}
