#include "gcl.h"
#include "menuMan.h"
#include "mts_new.h"

extern const char   aWrongCodeForRa[];

extern int          game_state_flags_800AB3CC;

extern char*        GCL_Read_String_80020A70(char *pScript);
extern void         MENU_ClearRadioTable_8004967C(void);
extern void         MENU_RadioCall_80042730(int param_1, int param_2, int param_3);
extern void         MENU_ResetCall_80042814(void);
extern void         MENU_SetRadioCallbackProc_8004283C(int param_1);
extern void         sub_80049764(int param_1, int param_2);
extern void         sub_80049794(int param_1, int param_2);

int Script_tbl_radio_8002C4A8(void)
{
    int hash;
    int code1;
    int code2;

    if (GCL_GetParam_80020968('b'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            sub_80049764(GCL_Get_Param_80020AD4(), GCL_Get_Param_80020AD4());
        }
    }
    if (GCL_GetParam_80020968('o'))
    {
        hash = GCL_Get_Param_80020AD4();
        if (hash == 0xDD2) // 入る "enter"
        {
            hash = 0;
        }
        else if (hash == 0xD5CC) // 出る "leave"
        {
            hash = 1;
        }
        else
        {
            mts_printf_8008BBA0(aWrongCodeForRa);
        }
        while (GCL_Get_Param_Result_80020AA4())
        {
            code1 = GCL_Get_Param_80020AD4();
            code2 = GCL_Get_Param_80020AD4();
            if (hash)
            {
                code2 = -1;
            }
            sub_80049794(code1, code2);
        }
    }
    if (GCL_GetParam_80020968('c')) // call
    {
        MENU_RadioCall_80042730(GCL_Get_Param_80020AD4(),
                                GCL_Get_Param_80020AD4(),
                                GCL_Get_Param_80020AD4());
    }
    if (GCL_GetParam_80020968('p')) // proc
    {
        MENU_SetRadioCallbackProc_8004283C(GCL_Get_Param_80020AD4());
    }
    if (GCL_GetParam_80020968('r')) // reset
    {
        MENU_ResetCall_80042814();
    }
    if (GCL_GetParam_80020968('m'))
    {
        menu_radio_clear_or_set_var_8004E110(
                    GCL_Get_Param_80020AD4(),
                    GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4()));
    }
    if (GCL_GetParam_80020968('d'))
    {
        game_state_flags_800AB3CC |= 0x2000;
    }
    if (GCL_GetParam_80020968('e'))
    {
        game_state_flags_800AB3CC &= ~0x2000;
    }
    if (GCL_GetParam_80020968('a'))
    {
        MENU_ClearRadioTable_8004967C();
    }
    return 0;
}
