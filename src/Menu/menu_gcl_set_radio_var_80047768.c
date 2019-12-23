#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"
#include "gcl.h"

extern const char aSetDS[];

unsigned char* sub_800217F0(unsigned char*);

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

void sub_8004780C(menu_chara_struct *unknown, unsigned char *pScript)
{
    unknown->field_0_state = 4;
    unknown->field_C_pScript = pScript;
    unknown->field_1A = 0;
    mts_8008A400();
}

void sub_80047838(menu_chara_struct *unknown, unsigned char *pScript)
{
    while (*pScript)
    {
        pScript = sub_800217F0(pScript);
    }
}
