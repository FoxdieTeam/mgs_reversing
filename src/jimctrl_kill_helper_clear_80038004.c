#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern void MENU_JimakuClear_80049518(void);

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

void jimctrl_kill_helper_clear_80038004(Actor_JimCtrl *pJimCtrl)
{
    array_800B933C_child *pIter;
    int i;

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
