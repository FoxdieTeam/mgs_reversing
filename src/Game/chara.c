#include "linker.h"
#include "mts/mts_new.h"

#include "game.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

// force gp usage
extern unsigned char *gOverlayBase_800AB9C8;
unsigned char        *SECTION(".sbss") gOverlayBase_800AB9C8;

extern GCL_Vars           gGcl_vars_800B3CC8;
extern GCL_ActorTableEntry MainCharacterEntries_8009D2DC[];

void GM_InitChara_8002A890()
{
    gOverlayBase_800AB9C8 = mts_get_bss_tail_8008C598();
}

void GM_ResetChara_8002A8B0()
{
    int *puVar1;

    puVar1 = (int *)gOverlayBase_800AB9C8;
    puVar1[1] = 0;
    puVar1[0] = 0;
    return;
}

TGCL_ActorCreateFn GM_GetChara_8002A8C4(unsigned char *pScript)
{
    return GM_GetCharaID_8002A8EC(GCL_StrToInt_800209E8(pScript));
}

TGCL_ActorCreateFn GM_GetCharaID_8002A8EC(int chara_id)
{
    GCL_ActorTableEntry *pSrcTable;
    int                  i = 0;
    do
    {
        // First search the fixed set of commands
        pSrcTable = &MainCharacterEntries_8009D2DC[0];
        if (i != 0)
        {
            // Then look at the dynamically loaded commands
            pSrcTable = (GCL_ActorTableEntry *)gOverlayBase_800AB9C8; // TODO: Fix type
        }

        if (pSrcTable->function)
        {
            do
            {
                if (pSrcTable->hashCode == chara_id)
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

void GM_ClearWeaponAndItem_8002A960()
{
    GM_CurrentWeaponId = WEAPON_NONE;
    GM_CurrentItemId = WEAPON_NONE;
}