#include "menuMan.h"
#include "linker.h"

extern void menu_init_rpk_item_8003DDCC(MenuMan_Inventory_14h_Unk *pUnk, int imgIdx, int palIdx);

MenuMan_Inventory_14h_Unk SECTION(".gMenuMan_800BD5A0") dword_800BD5A0;

void menu_sub_8003B568(void)
{
    int imgIdx;
    DWORD palIdx;
    int i;
    
    for (i = 0; i < 0x15; i++)
    {
        imgIdx = 0xc + i;
        palIdx = 0x2e;
        if (imgIdx != 0x16)
        {
            palIdx = 0;
            if (imgIdx == 0x1b)
            {
                palIdx = 0x2f;
            }
        }
        menu_init_rpk_item_8003DDCC(&dword_800BD5A0 + i, imgIdx, palIdx);
    }
}
