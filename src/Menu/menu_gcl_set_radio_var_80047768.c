#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"
#include "gcl.h"

extern const char aSetDS[];

void menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript)
{
    int varId;
    pScript = menu_gcl_read_word_80047098(&varId, pScript);
    mts_printf_8008BBA0(aSetDS, varId, pScript);
    menu_radio_clear_or_set_var_8004E110(varId, pScript);
}

void sub_800477B0(menu_chara_struct *unknown, unsigned char *pScript)
{
    int iVar1 = GCL_800209E8(pScript);
    unknown->field_0_state = 3;
    unknown->field_C_pScript = GCL_Get_Param_Result_80020AA4();
    unknown->field_1A = iVar1;
    mts_8008A400();
    unknown->field_18 &= ~0x100;
}
