#include "game.h"
#include "linker.h"

extern char byte_8009D698[];

extern short word_800ABA80;
short SECTION(".sbss") word_800ABA80;

void GM_AlertModeSet_8002EA68(int a1)
{
    if (a1 > word_800ABA80)
    {
        word_800ABA80 = a1;
        GM_CallSystemCallbackProc_8002B570(2, byte_8009D698[a1]);
    }
}
