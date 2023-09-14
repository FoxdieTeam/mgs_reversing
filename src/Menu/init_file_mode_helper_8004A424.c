#include "linker.h"
#include "menuman.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"

extern void *dword_800ABB50;
void *SECTION(".sbss") dword_800ABB50;

extern int dword_800ABB48;
int SECTION(".sbss") dword_800ABB48;

extern const char aNoMemoryForSta_0[];

void init_file_mode_helper_8004A424(int param_1)
{
    int size = 0x800;

    dword_800ABB50 = GV_AllocMemory_80015EB8(0, size);

    if (!dword_800ABB50)
    {
        printf(aNoMemoryForSta_0); // "NO MEMORY FOR STACK\n"
    }

    dword_800ABB48 = param_1;
    mts_set_stack_check_8008B648(7, (unsigned int *)(dword_800ABB50 + size), size);
    mts_sta_tsk_8008B47C(7, init_file_mode_helper_helper_80049EDC, (void *)(dword_800ABB50 + size));
}
