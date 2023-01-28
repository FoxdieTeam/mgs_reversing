#include "linker.h"

extern short GM_RadarMode_800ABA80;
short SECTION(".sbss") GM_RadarMode_800ABA80;

void GM_AlertModeInit_8002EAA8(void)
{
    GM_RadarMode_800ABA80 = -1;
}
