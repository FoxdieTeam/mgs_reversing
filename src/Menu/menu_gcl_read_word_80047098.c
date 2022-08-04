#include "linker.h"
#include "menuMan.h"

unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript)
{
    *pOut = (pScript[1] ) | ( pScript[0] << 8);
    return pScript + sizeof(short);
}
