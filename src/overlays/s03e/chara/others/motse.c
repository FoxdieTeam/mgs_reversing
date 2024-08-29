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

extern int              GM_PlayerAction_800ABA40;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_800AB9D4;

void Motse_800C57CC(MotseWork *work)
{
    MotseElem *elem;
    int        i;

    if ((GM_PlayerStatus_800ABA50 & PLAYER_UNK4) && GM_PlayerAction_800ABA40 == work->field_20)
    {
        for (i = 0, elem = work->field_28_elems; i < work->field_24_count; i++, elem++)
        {
            if (elem->param1 == dword_800AB9D4)
            {
                GM_SeSetMode_800329C4(&GM_PlayerControl_800AB9F4->mov, elem->param2, GM_SEMODE_BOMB);
                return;
            }
        }
    }
}

void Motse_800C5864(MotseWork *work)
{
    GV_DelayedFree_80016254(work->field_28_elems);
}

int Motse_800C5888(MotseWork *work, int name)
{
    int            i, count;
    unsigned char *param;
    MotseElem     *elems;

    work->field_20 = GCL_StrToInt_800209E8(GCL_GetOption_80020968('m'));
    work->field_24_count = count = GCL_StrToInt_800209E8(GCL_GetOption_80020968('n'));
    work->field_28_elems = elems = GV_Malloc_8001620C(count * sizeof(MotseElem));

    GCL_GetOption_80020968('s');

    for (i = 0; (param = GCL_Get_Param_Result_80020AA4()) && i != count; i++, elems++)
    {
        elems->param1 = GCL_StrToInt_800209E8(param);
        elems->param2 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    return 0;
}

GV_ACT *NewMotse_800C5944(int name, int where, int argc, char **argv)
{
    MotseWork *work;

    work = (MotseWork *)GV_NewActor_800150E4(6, sizeof(MotseWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Motse_800C57CC,
                                  (TActorFunction)Motse_800C5864, "motse.c");
        if (Motse_800C5888(work, name) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
