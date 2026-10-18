// vrsave: savemngr actor die function and the layout change of the menu for the extra record slots.
#include "mgstype.h"
#include "overlays/vrsave/vrsave.h"

extern VR_SAVEMNGR_ITEM vrsave_dword_800C12CC[];

void vrsave_800CB9D4(void)
{
}

void vrsave_800CB9DC(void)
{
    VR_SAVEMNGR_ITEM *items;

    items = vrsave_dword_800C12CC;
    items[0].link[2] = 2;
    items[0].rect.y = 0x97;
    items[0].frame_rect.y = 0x94;
    items[1].state = 8;
    items[1].flags |= 0x20000000;
    items[2].link[0] = 0;
}
