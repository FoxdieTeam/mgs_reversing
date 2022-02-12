#include "linker.h"
#include "menuMan.h"

void menu_radio_compact_free_vars_8004D3D8(void);

RadioMemory SECTION(".gRadioMemory_800BDB38") gRadioMemory_800BDB38[RADIO_MEMORY_COUNT] = {};

void MENU_InitRadioMemory_8004E0EC(void)
{
    RadioMemory *pIter = &gRadioMemory_800BDB38[0];
    int i = RADIO_MEMORY_COUNT - 1;
    while (i >= 0)
    {
        pIter->field_0_id = 0;
        pIter++;
        i--;
    }
}

char *strcpy_8008E768(char *, const char *);
int strcmp_8008E6F8(const char *str1, const char *str2);

extern const char aClear[];

int dword_800AB770 = 0; //sdata

void MENU_SetRadioMemory_8004E110(int varId, const char *pVarName)
{
    RadioMemory *pVar;

    // Get existing var
    pVar = menu_radio_table_find_8004D380(varId);
    if (!pVar)
    {
        // Isn't one so get next free var
        pVar = menu_radio_table_next_free_8004D3B8();
    }

    if (strcmp_8008E6F8(pVarName, aClear) == 0)
    {
        // Clear the var
        dword_800AB770 = 0;
        pVar->field_0_id = 0;
    }
    else
    {
        // Set the var
        pVar->field_0_id = varId;
        strcpy_8008E768(pVar->field_2_name, pVarName);
    }

    menu_radio_compact_free_vars_8004D3D8();
}
