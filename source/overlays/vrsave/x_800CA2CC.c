// vrsave: VR revision copy of menu/radiomes.c
// (menu_radio_update_helper6_80047D40), no exact twin; adapted from the asm
#include "libgv/libgv.h"
#include "menu/menuman.h"

void vrsave_800CA2CC( MenuWork *work )
{
    GV_FreeMemory( GV_NORMAL_MEMORY, work->field_214_font );
    work->field_214_font = NULL;
}
