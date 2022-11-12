#include "linker.h"

extern short word_800ABA80;
short SECTION(".sbss") word_800ABA80;

void GM_AlertModeInit_8002EAA8(void)
{
    word_800ABA80 = -1;
}
