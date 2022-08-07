#include "linker.h"
#include "libgcl/gcl.h"

extern int gBinds_800ABA60;
int        SECTION(".sbss") gBinds_800ABA60;

int GCL_Command_chara_8002C1B0(int argc, char **argv)
{
    int                ret;
    int                charaHash;
    TGCL_ActorCreateFn pCreateActorFn;

    pCreateActorFn = GM_GetChara_8002A8C4(GCL_Get_Param_Result_80020AA4());
    if (pCreateActorFn)
    {
        charaHash = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
        (*pCreateActorFn)(charaHash, gBinds_800ABA60, argc, argv);
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}
