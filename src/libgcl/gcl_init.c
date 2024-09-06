#include "hash.h"
#include "libgcl.h"

// #define STATIC static
#define STATIC

int SECTION(".sbss") scenerio_code;
int SECTION(".sbss") dword_800AB994;

/**
 *  @brief      GCX bytecode initialization handler
 *
 *  If @p id is the same as @c scenerio_code the script will be loaded
 *  and set for execution, otherwise it will be skipped.
 *
 *  @param[in]  buf     pointer to cached GCX script
 *  @param[in]  id      strcode of the script's basename
 *
 *  @retval     1       on success
 *  @retval     <= 0    on failure (but this can't happen)
 */
STATIC int GCL_InitFunc(unsigned char *top, int id)
{
    if (id == scenerio_code)
    {
        GCL_LoadScript(top);
    }
    return 1;
}

void GCL_ChangeSenerioCode(int demo_flag)
{
    scenerio_code = (demo_flag == 1)
        ? GCL_StrHash(HASH_demo)        // 0x006a242
        : GCL_StrHash(HASH_scenerio);   // 0x006ea54
}

void GCL_StartDaemon(void)
{
    GCL_ParseInit();
    GCL_InitVar();
    GCL_InitBasicCommands();
    GV_SetLoader('g', GCL_InitFunc);
    GCL_ChangeSenerioCode(0);
}

void GCL_ResetSystem(void)
{
    /* do nothing */
}
