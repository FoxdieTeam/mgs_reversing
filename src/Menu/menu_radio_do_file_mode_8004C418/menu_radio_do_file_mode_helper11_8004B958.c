#include "libgv/libgv.h"

extern const char aNoMemoryForInf[];
extern const char aAllocInfoX[];

// a1 is &dword_800ABB74
void menu_radio_do_file_mode_helper11_8004B958(void **a1, int num)
{
    if (!*a1)
    {
        *a1 = GV_AllocMemory_80015EB8(0, (0x24 * num) + 0x24);

        if (!*a1)
        {
            mts_printf_8008BBA0(aNoMemoryForInf); // "NO MEMORY FOR INFO\n"
        }

        mts_printf_8008BBA0(aAllocInfoX, *a1); // "alloc info %X\n"
    }
}
