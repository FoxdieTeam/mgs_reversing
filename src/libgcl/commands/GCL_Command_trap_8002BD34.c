#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"
#include "libgcl/hash.h"

extern int gBinds_800ABA60;
extern int gBindsCount_800ABA64;
int        SECTION(".sbss") gBinds_800ABA60;
int        SECTION(".sbss") gBindsCount_800ABA64;

STATIC_ASSERT_SIZE(BindStruct, 0x18);

void HZD_SetBind_80029A5C(int, BindStruct *, int);

BindStruct SECTION(".gBindsArray_800b58e0") gBindsArray_800b58e0[128];

extern const char aBindsOver[];

int GCL_Command_trap_8002BD34(int argc, char **argv)
{
    BindStruct *pBind;
    int         i, arg, code, value;
    int         tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        mts_printf_8008BBA0(aBindsOver);
    }

    i = gBindsCount_800ABA64;
    pBind = gBindsArray_800b58e0 + i;

    // Trap id
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_4 = arg;

    // Entity id
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;

    // Event condition
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    gBindsArray_800b58e0[i].field_2_param_m = arg; // mask

    gBindsArray_800b58e0[i].field_B_param_e = 0; // exec
    gBindsArray_800b58e0[i].field_8_param_i_c_flags = 0;

    GCL_GetNextValue_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
    gBindsArray_800b58e0[i].field_14_proc_and_block = value;
    gBindsCount_800ABA64++;

    tmp = gBinds_800ABA60;
    gBindsArray_800b58e0[i].field_6 = (short)tmp;
    HZD_SetBind_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);

    return 0;
}
