#include "util/idaTypes.h"
#include "linker.h"
#include "jimctrl.h"
#include "Script_tbl_map_8002BB44.h"
#include "data/data/data.h"

int  FS_StreamGetData_800240E0(DWORD);
void sub_800241B4(int);
int  FS_StreamOpen_80024060(void);
void FS_StreamClose_80024098(void);

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];
extern unk_8009E280         dword_8009E280;

extern DWORD                 gotohell_800B9358;
extern GameState_800B4D98    gGameState_800B4D98;
extern const char            aJimctrlC[];
extern dword_800B9358_struct array_800B9358[2];

Actor_JimCtrl SECTION(".gJimCtrlActor_800B82F0") jimCtrlActor_800B82F0;

void jimctrl_helper_null_80037FFC(void)
{
}

void MENU_JimakuClear_80049518(void);

void jimctrl_kill_helper_clear_80038004(Actor_JimCtrl *pJimCtrl)
{
    array_800B933C_child *pIter;
    int                   i;

    if (pJimCtrl->field_44 != 0)
    {
        MENU_JimakuClear_80049518();
    }

    if (pJimCtrl->field_38 != 0)
    {
        i = 0;
        pIter = &array_800B933C[i] + 1;
        for (; i < array_800B933C_SIZE - 1; i++)
        {
            pIter->field_2 = 0;
            pIter->field_3 = 0;
            pIter++;
        }
    }
}
#pragma INCLUDE_ASM("asm/jimctrl_act_80038070.s")

void jimctrl_kill_8003853C(Actor_JimCtrl *pJimCtrl)
{
    jimctrl_kill_helper_clear_80038004(pJimCtrl);
    dword_8009E280.dword_8009E28C = 0;
    FS_StreamClose_80024098();
}

Actor *jimctrl_init_80038568(DWORD flags)
{
    int            seekResult;
    DWORD          toSeek = 4;
    Actor_JimCtrl *pJimActor = &jimCtrlActor_800B82F0;
    if (flags & 0x80)
    {
        toSeek = 7;
    }
    seekResult = FS_StreamGetData_800240E0(toSeek);

    if (gGameState_800B4D98.field_04_flags & 0x100)
    {
        jimCtrlActor_800B82F0.field_27 = 3;
        jimCtrlActor_800B82F0.field_26 = 6;
    }
    else
    {
        jimCtrlActor_800B82F0.field_27 = 6;
        jimCtrlActor_800B82F0.field_26 = 3;
    }

    if (seekResult != 0)
    {
        sub_800241B4(seekResult);
    }

    if (pJimActor->field_0_base.mFnUpdate == (TActorFunction)jimctrl_act_80038070)
    {
        return &pJimActor->field_0_base;
    }
    else
    {
        flags &= 0xf;
        pJimActor->field_28 = 0;
        jimctrl_init_helper_clear_80037FB8();
        GV_InitActor_800150A8(1, &pJimActor->field_0_base, 0);

        GV_SetNamedActor_8001514C(&pJimActor->field_0_base, (TActorFunction)jimctrl_act_80038070,
                                  (TActorFunction)jimctrl_kill_8003853C, aJimctrlC);

        pJimActor->field_24 = flags;

        FS_StreamOpen_80024060();

        pJimActor->field_30 = -1;
        pJimActor->field_2C = 0;
        pJimActor->field_34 = 0;
        pJimActor->field_20 = 0;
        array_800B9358[0].dword_800B9358 = 0;

        return &jimCtrlActor_800B82F0.field_0_base;
    }
}
