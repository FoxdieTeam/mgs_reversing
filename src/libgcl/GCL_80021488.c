#include "Script_tbl_map_8002BB44.h"
#include "linker.h"

extern GameState_800B4D98   gGameState_800B4D98;
extern GameState_800B4D98   gGcl_gameStateVars_800B44C8;

extern GCL_Vars             gGcl_vars_800B3CC8;
extern GCL_Vars             gGcl_memVars_800b4588;

extern char                 gStageName_800B4D88[16];

extern char*                GM_StageName_8002A880(char*);
extern char*                strcpy_8008E768(char *, char *);
extern int                  GV_StrCode_80016CCC(const char* string );
extern int                  GM_PushAreaHistory_8002A7D8(int stageNameHash, char *pStageName);

void *memcpy_8008E648(void *destination, const void *source, int num);

void GCL_80021488(void)
{
    // The use of the following struct makes no sense, suspecting a bug here
    typedef struct  { short f[0x9C / sizeof(short)]; } GmState;

    *(GmState*)&gGameState_800B4D98 = *(GmState*)&gGcl_gameStateVars_800B44C8;
    gGcl_vars_800B3CC8 = gGcl_memVars_800b4588;

    GM_PushAreaHistory_8002A7D8(GV_StrCode_80016CCC(gStageName_800B4D88), gStageName_800B4D88);
}
