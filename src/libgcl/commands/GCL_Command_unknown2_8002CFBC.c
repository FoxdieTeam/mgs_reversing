#include "gcl.h"
#include "mts_new.h"
#include "linker.h"

extern int          gBinds_800ABA60;
int SECTION(".sdata") gBinds_800ABA60;
extern int          dword_800AB414;
int SECTION(".sdata") dword_800AB414;

extern const char   aErrorDemoThrea[];

extern int          GM_CurrentMap_800AB9B0;

extern char*        GCL_Read_String_80020A70(char *pScript);
extern int          demothrd_init_80079460(int param_1, int param_2);
extern int          demothrd_init_800794E4(int param_1, int param_2);

int GCL_Command_unknown2_8002CFBC(void)
{
    int tmp, demo, flags, ivar;
    char *str;

    ivar = 0;
    str = (char*)0;
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
        dword_800AB414 = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        dword_800AB414 = -1;
    }
    tmp = GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;
    if (str)
    {
        demo = demothrd_init_800794E4(flags, (int)str);
    }
    else 
    {
        demo = demothrd_init_80079460(flags, ivar);
    }
    GM_CurrentMap_800AB9B0 = tmp;
    if (!demo)
    {
        mts_printf_8008BBA0(aErrorDemoThrea);
    }
    return 0;
}
