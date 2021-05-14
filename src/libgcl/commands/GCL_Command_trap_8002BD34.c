#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "mts_new.h"

extern int gBinds_800ABA60;
extern int gBindsCount_800ABA64;
int SECTION(".sbss") gBinds_800ABA60;
int SECTION(".sbss") gBindsCount_800ABA64;

STATIC_ASSERT_SIZE(BindStruct, 0x18);

void GM_SetBinds_80029A5C(int, BindStruct *, int);

BindStruct SECTION(".gBindsArray_800b58e0") gBindsArray_800b58e0[128];

extern const char aBindsOver[];

int GCL_Command_trap_8002BD34(unsigned char *pScript)
{
    int iVar1;
    int sVar2;
    BindStruct *pBVar4;
    int code;
    int value;
    int tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        mts_printf_8008BBA0(aBindsOver);
    }

    iVar1 = gBindsCount_800ABA64;
    pBVar4 = gBindsArray_800b58e0 + gBindsCount_800ABA64;

    sVar2 = GCL_GetNextParamValue_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    gBindsArray_800b58e0[iVar1].field_4 = sVar2;

    sVar2 = GCL_GetNextParamValue_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    pBVar4->field_0 = sVar2;

    sVar2 = GCL_GetNextParamValue_80020AD4();
    if (sVar2 == 0x14c9)
    {
        sVar2 = 0;
    }
    gBindsArray_800b58e0[iVar1].field_2_param_m = sVar2;

    gBindsArray_800b58e0[iVar1].field_B_param_e = 0;
    gBindsArray_800b58e0[iVar1].field_8_param_i_c_flags = 0;

    GCL_Execute_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
    gBindsArray_800b58e0[iVar1].field_14_proc_and_block = value;
    gBindsCount_800ABA64++; // 780 gp

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[iVar1].field_6 = (short)tmp; // 0x77c gp
    GM_SetBinds_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}
