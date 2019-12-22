#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"

extern const char aSetDS[];

void menu_gcl_set_radio_var_80047768(void* unknown, unsigned char *pScript)
{
    unsigned char* pScriptNext;
    int varId;

    pScriptNext = menu_gcl_read_word_80047098(&varId, pScript);
    mts_printf_8008BBA0(aSetDS, varId, pScriptNext);
    menu_radio_clear_or_set_var_8004E110(varId, pScriptNext);
}
