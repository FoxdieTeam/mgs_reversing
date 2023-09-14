#include "linker.h"
#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

extern const char aNoMemoryForObj[]; // = "NO MEMORY FOR OBJ\n";

void init_file_mode_helper2_8004A800()
{
    int i;

    stru_800ABB7C = (RadioFileModeStru_800ABB7C *)GV_AllocMemory_80015EB8(0, sizeof(RadioFileModeStru_800ABB7C));
    if (stru_800ABB7C == NULL)
    {
        printf(aNoMemoryForObj);
    }

    for (i = 0; i < 12; i++)
    {
        stru_800ABB7C->field_0_array[i].field_0 = 0;
    }
}