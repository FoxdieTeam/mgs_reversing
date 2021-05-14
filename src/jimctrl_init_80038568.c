#include "jimctrl.h"
#include "Script_tbl_map_8002BB44.h"
#include "linker.h"

extern int FS_Seek_800240E0(DWORD);
extern void sub_800241B4(int);
extern int sub_80024060(void);
extern DWORD gotohell_800B9358;
extern GameState_800B4D98 gGameState_800B4D98;
extern const char aJimctrlC[];
extern dword_800B9358_struct array_800B9358[2];

Actor_JimCtrl SECTION(".gJimCtrlActor_800B82F0") jimCtrlActor_800B82F0;

Actor *jimctrl_init_80038568(DWORD flags)
{
    int seekResult;
    DWORD toSeek = 4;
    Actor_JimCtrl *pJimActor = &jimCtrlActor_800B82F0;
    if (flags & 0x80)
    {
        toSeek = 7;
    }
    seekResult = FS_Seek_800240E0(toSeek);

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
        GV_ActorPushBack_800150a8(1, &pJimActor->field_0_base, 0);

        GV_ActorInit_8001514c(
            &pJimActor->field_0_base,
            (TActorFunction)jimctrl_act_80038070,
            (TActorFunction)jimctrl_kill_8003853C,
            aJimctrlC
        );

        pJimActor->field_24 = flags;

        sub_80024060();

        pJimActor->field_30 = -1;
        pJimActor->field_2C = 0;
        pJimActor->field_34 = 0;
        pJimActor->field_20 = 0;
        array_800B9358[0].dword_800B9358 = 0;

        return &jimCtrlActor_800B82F0.field_0_base;
    }

}
