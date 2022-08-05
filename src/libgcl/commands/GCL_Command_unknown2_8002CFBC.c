#include "libgcl/gcl.h"
#include "mts/mts_new.h"
#include "linker.h"

extern int gBinds_800ABA60;
int        SECTION(".sdata") gBinds_800ABA60;
extern int demodebug_finish_proc_800AB414;
int        SECTION(".sdata") demodebug_finish_proc_800AB414;

extern const char aErrorDemoThrea[];

extern int GM_CurrentMap_800AB9B0;

int   DM_ThreadStream_80079460(int param_1, int param_2);
int   DM_ThreadFile_800794E4(int param_1, int param_2);

int GCL_Command_unknown2_8002CFBC(int argc, char **argv)
{
    int   tmp, demo, flags, ivar;
    char *str;

    ivar = 0;
    str = (char *)0;
    flags = GCL_GetParam_80020968('e') != 0;
    if (GCL_GetParam_80020968('a'))
    {
        flags |= 4;
    }
    if (GCL_GetParam_80020968('v'))
    {
        flags |= 2;
    }
    if (GCL_GetParam_80020968('s'))
    {
        ivar = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    if (GCL_GetParam_80020968('f'))
    {
        str = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    }
    if (GCL_GetParam_80020968('p'))
    {
        demodebug_finish_proc_800AB414 = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        demodebug_finish_proc_800AB414 = -1;
    }
    tmp = GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;
    if (str)
    {
        demo = DM_ThreadFile_800794E4(flags, (int)str);
    }
    else
    {
        demo = DM_ThreadStream_80079460(flags, ivar);
    }
    GM_CurrentMap_800AB9B0 = tmp;
    if (!demo)
    {
        mts_printf_8008BBA0(aErrorDemoThrea);
    }
    return 0;
}
