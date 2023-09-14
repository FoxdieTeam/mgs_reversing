#include "linker.h"
#include "libgcl/libgcl.h"
#include "mts/mts_new.h"
#include "libgcl/hash.h"
#include "libhzd/libhzd.h"

extern int gBinds_800ABA60;
extern int gBindsCount_800ABA64;
int        SECTION(".sbss") gBinds_800ABA60;
int        SECTION(".sbss") gBindsCount_800ABA64;

STATIC_ASSERT_SIZE(BindStruct, 0x18);

extern BindStruct gBindsArray_800b58e0[128];

int GCL_Command_trap_8002BD34(unsigned char *pScript)
{
    BindStruct *pBind;
    int         i, arg, code, value;
    int         tmp;

    if (0x7f < gBindsCount_800ABA64)
    {
        printf("binds over\n");
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

int GCL_Command_ntrap_8002BE20(unsigned char *pScript)
{
    // int bindIdx;
    BindStruct *pBind;
    int         flags;
    int         arg;
    int         tmp;

    if (gBindsCount_800ABA64 > 127) // 780 gp
    {
        printf("binds over\n");
    }
    // bindIdx = gBindsCount_800ABA64; // 780 gp
    pBind = gBindsArray_800b58e0 + gBindsCount_800ABA64;
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_4 = arg;
    arg = GCL_GetNextParamValue_80020AD4();
    if (arg == HASH_TRAP_ALL)
    {
        arg = 0;
    }
    pBind->field_0 = arg;
    pBind->field_8_param_i_c_flags = 0; // v0
    flags = 0;                          // still s1
    if (GCL_GetParam_80020968('m'))     // mask
    {
        arg = GCL_GetNextParamValue_80020AD4();
        if (arg == HASH_TRAP_ALL)
        {
            arg = 0;
        }
        pBind->field_2_param_m = arg;
    }
    else
    {
        pBind->field_2_param_m = 0;
    }
    if (GCL_GetParam_80020968('d')) // dir
    {
        flags |= 1;
        pBind->field_C_param_d = GCL_GetNextParamValue_80020AD4();

        if (GCL_Get_Param_Result_80020AA4())
        {
            pBind->field_E_param_d_or_512 = GCL_GetNextParamValue_80020AD4();
        }
        else
        {
            pBind->field_E_param_d_or_512 = 0x200;
        }
    }
    if (GCL_GetParam_80020968('b')) // button
    {
        flags |= 4;
        pBind->field_A_param_b = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('s')) // stance
    {
        flags |= 2;
        pBind->field_9_param_s = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('r')) // repeat
    {
        flags |= 0x40;
    }
    if (GCL_GetParam_80020968('i'))
    {
        pBind->field_8_param_i_c_flags |= 1;
    }
    if (GCL_GetParam_80020968('c'))
    {
        pBind->field_8_param_i_c_flags |= 2;
    }
    if (GCL_GetParam_80020968('t')) // time
    {
        if ((flags & 0x40) != 0)
        {
            printf("ntrap:can't set every\n");
        }
        pBind->field_10_every = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('p')) // proc
    {
        flags |= 0x80;
        pBind->field_14_proc_and_block = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetParam_80020968('e')) // exec
    {
        int code;
        int value;
        if ((flags & 0x80) != 0)
        {
            printf("ntrap:can't set proc and block\n");
        }
        GCL_GetNextValue_8002069C(GCL_Get_Param_Result_80020AA4(), &code, &value);
        pBind->field_14_proc_and_block = value;
    }
    pBind->field_B_param_e = flags;
    gBindsCount_800ABA64++;
    tmp = gBinds_800ABA60;
    pBind->field_6 = (short)tmp;
    printf("BIND %08X\n", tmp);
    HZD_SetBind_80029A5C(0, gBindsArray_800b58e0, gBindsCount_800ABA64);
    return 0;
}
