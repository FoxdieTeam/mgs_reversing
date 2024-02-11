#include "select.h"
#include "libgcl/libgcl.h"

typedef struct Work
{
    GV_ACT         actor;
    unsigned char *field_20;
    char          *field_24;
    int            field_28;
    int            field_2c;
    int            field_30;
    int            field_34;
} Work;

extern GV_PAD GV_PadData_800B05C0[4];

#define EXEC_LEVEL 3

void Select_helper_800c3218(Work *work, int addend)
{
    int   i;
    int   gcl_int;
    char *gcl_string;

    work->field_2c += addend;
    if (work->field_2c < 0)
    {
        work->field_2c = 0;
    }

    GCL_SetArgTop_80020690(work->field_20);
    for (i = 0; i <= work->field_2c; i++)
    {
        if (GCL_Get_Param_Result_80020AA4() == 0)
        {
            work->field_2c = i;
            break;
        }
        gcl_string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        gcl_int = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    work->field_24 = gcl_string;
    work->field_28 = gcl_int;
}

void Select_Act_800c32d8(Work *work)
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
        if (work->field_34 == dir)
        {
            if (--work->field_30 < 0)
            {
                Select_helper_800c3218(work, dir);
                work->field_30 = 2;
            }
        }
        else
        {
            Select_helper_800c3218(work, dir);
            work->field_30 = 10;
            work->field_34 = dir;
        }
    }
    else
    {
        work->field_34 = 0;
    }
    if (pPad->press & PAD_CIRCLE)
    {
        GCL_ExecProc_8001FF2C(work->field_28, NULL);
        GV_DestroyActor_800151C8(&work->actor);
    }
    menu_Text_Init_80038B98();
    MENU_Locate_80038B34(160, 120, 2);
    MENU_Printf_80038C38(work->field_24);
}

int Select_helper_800c33d0(Work *work, int param_2, int param_3)
{
    if (GCL_GetOption_80020968('s') == 0)
    {
        printf("NO MENU\n");
        return -1;
    }

    work->field_20 = GCL_Get_Param_Result_80020AA4();
    work->field_2c = 0;
    work->field_34 = 0;
    Select_helper_800c3218(work, 0);
    return 0;
}

GV_ACT *NewSelect_800c3434(int name, int where, int argc, char **argv)
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Select_Act_800c32d8, 0, "select.c");
        if (Select_helper_800c33d0(work, where, name) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
