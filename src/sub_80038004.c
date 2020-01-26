#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern void MENU_JimakuClear_80049518(void);

extern array_800B9340_child array_800B9340[array_800B9340_SIZE];

void jimctrl_zero_memory_80038004(Actor_sub_80038004 *someActor)
{
    array_800B9340_child *puVar1;
    int iterator;

    if (someActor->field_44 != 0)
    {
        MENU_JimakuClear_80049518();
    }

    if (someActor->field_38 != 0)
    {
        puVar1 = &array_800B9340[0];
        for (iterator = 0; iterator < array_800B9340_SIZE; iterator++)
        {
            puVar1->b = 0;
            puVar1->c = 0;
            puVar1++;
        }
    }
}
