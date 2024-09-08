#include "linker.h"
#include "mts/mts_new.h"

#include "game.h"
#include "charadef.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

// force gp usage
extern unsigned char *gOverlayBase_800AB9C8;
unsigned char        *SECTION(".sbss") gOverlayBase_800AB9C8;

extern GCL_Vars           gGcl_vars_800B3CC8;
extern CHARA MainCharacterEntries_8009D2DC[];

void GM_InitChara(void)
{
    gOverlayBase_800AB9C8 = mts_get_bss_tail();
}

void GM_ResetChara(void)
{
    int *puVar1;

#ifdef DEV_EXE
    return; // the overlay is embedded in the executable in dev variant
#endif

    puVar1 = (int *)gOverlayBase_800AB9C8;
    puVar1[1] = 0;
    puVar1[0] = 0;
}

NEWCHARA GM_GetChara(unsigned char *pScript)
{
    return GM_GetCharaID(GCL_StrToInt(pScript));
}

NEWCHARA GM_GetCharaID(int chara_id)
{
    CHARA *chara_table;
    int    i = 0;

    do {
        // First search the fixed set of commands
        chara_table = &MainCharacterEntries_8009D2DC[0];
        if (i != 0)
        {
            // Then look at the dynamically loaded commands
            chara_table = (CHARA *)gOverlayBase_800AB9C8; // TODO: Fix type
        }

        if (chara_table->function)
        {
            do
            {
                if (chara_table->class_id == chara_id)
                {
                    return chara_table->function;
                }
                chara_table++;
            } while (chara_table->function);
        }
        i++;
    } while (i < 2);

    return 0;
}

void GM_ClearWeaponAndItem(void)
{
    GM_CurrentWeaponId = WEAPON_NONE;
    GM_CurrentItemId = WEAPON_NONE;
}
