#include "linker.h"

extern int gFn_radar_800AB48C;
int SECTION(".sdata") gFn_radar_800AB48C;

void MENU_SetRadarFunc_80038F30(int param_1)
{
    gFn_radar_800AB48C = param_1;
    return;
}
