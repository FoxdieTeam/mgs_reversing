#include "linker.h"
#include "gcl.h"

extern GCL_ActorTableEntry StaticResInitFunc_8009D2DC[];

unsigned char *SECTION(".sbss") gOverlayBase_800AB9C8; // resident memory base ?

TGCL_ActorCreateFn GM_LookupActorFunc_8002A8EC(int hashedName);

TGCL_ActorCreateFn GM_GCL_LookupActorFunc_8002A8C4(unsigned char *pScript)
{
    return GM_LookupActorFunc_8002A8EC(GCL_GetNextValue_800209E8(pScript));
}

TGCL_ActorCreateFn GM_LookupActorFunc_8002A8EC(int hashedName)
{
    GCL_ActorTableEntry *pSrcTable;
    int i = 0;
    do
    {
        // First search the fixed set of commands
        pSrcTable = &StaticResInitFunc_8009D2DC[0];
        if (i != 0)
        {
            // Then look at the dynamically loaded commands
            pSrcTable = (GCL_ActorTableEntry *)gOverlayBase_800AB9C8; // TODO: Fix type
        }

        if (pSrcTable->function)
        {
            do
            {
                if (pSrcTable->hashCode == hashedName)
                {
                    return pSrcTable->function;
                }
                pSrcTable++;
            } while (pSrcTable->function);
        }
        i++;
    } while (i < 2);

    return 0;
}
