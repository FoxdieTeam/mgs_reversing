#include <util/idaTypes.h>
#include "linker.h"

extern void memcard_getfiles_helper_80024960(int);

typedef struct mem_card_struct
{
    BYTE field_1;
    BYTE field_2;
} mem_card_struct;

mem_card_struct* SECTION(".gMemoryCardFiles_800B52F8") gMemCardItems_800B52F8[100]; //todo size unknown

mem_card_struct* memcard_get_files_80025350(int idx)
{
    mem_card_struct* pLolItem = &gMemCardItems_800B52F8[0];

    mem_card_struct* pItem = pLolItem + idx * 0xD4;
    if ((pItem->field_2 == 1) ||
        (pItem->field_2 == 4))
    {
        memcard_getfiles_helper_80024960(idx);
        pItem->field_2 = 1;
        return pItem;
    }
    return 0;
}
