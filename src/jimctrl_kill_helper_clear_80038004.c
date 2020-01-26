#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern void MENU_JimakuClear_80049518(void);

extern array_800B9340_child array_800B9340[array_800B9340_SIZE];

void jimctrl_kill_helper_clear_80038004(Actor_sub_80038004 *someActor)
{
    array_800B9340_child *pIter;
    int i;

    if (someActor->field_44 != 0)
    {
        MENU_JimakuClear_80049518();
    }

    if (someActor->field_38 != 0)
    {
        i = 0;
        pIter = &array_800B9340[0];
        for (; i < array_800B9340_SIZE; pIter++, i++)
        {
            pIter->field_2 = 0;
            pIter->field_3 = 0;
        }
    }
}
