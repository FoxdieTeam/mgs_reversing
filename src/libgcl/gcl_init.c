#include "libgcl.h"

int SECTION(".sbss") gGcl_scriptNameHash_800AB990;
int SECTION(".sbss") dword_800AB994;

int GCL_InitFunc_8001FC88(unsigned char *pFileData, int hashedName)
{
    if (hashedName == gGcl_scriptNameHash_800AB990)
    {
        GCL_LoadScript_80020064(pFileData);
    }
    return 1;
}

void GCL_ChangeSenerioCode_8001FCB0(int isDemoScript)
{
    // 0x6 means hashed string
    // 0xA242 = "demo"
    // 0xEA54 = "scenerio"
    gGcl_scriptNameHash_800AB990 = (isDemoScript == 1) ? 0x6A242 : 0x6EA54;
}

void GCL_StartDaemon_8001FCDC(void)
{
    GCL_ParseInit_80020B68();
    GCL_InitVar_80021264();
    GCL_InitBasicCommands_8002040C();
    GV_SetLoader_80015418('g', GCL_InitFunc_8001FC88);
    GCL_ChangeSenerioCode_8001FCB0(0);
}

void GCL_ResetSystem_8001FD24(void)
{
}