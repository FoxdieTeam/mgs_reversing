// vrtitle: VR revision copy of menu/weapon.c
// (menu_weapon_unknown_8003DEB0), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"
#include "memcard/memcard.h"

extern int vrtitle_dword_800C1BB8;

void vrtitle_800D0124( DATA_INFO *info, int arg1 );

void vrtitle_800D0160( void )
{
    vrtitle_800D0124( (DATA_INFO *)&vrtitle_dword_800C1BB8, 1 );
}
