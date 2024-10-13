#include "common.h"
#include "mts/mts.h"

#include "game.h"
#include "charadef.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

// force gp usage
extern void *gOverlayBase_800AB9C8;
void *SECTION(".sbss") gOverlayBase_800AB9C8;

extern GCL_Vars gGcl_vars_800B3CC8;
extern CHARA MainCharacterEntries[]; /* in main.c */

void GM_InitChara(void)
{
#ifdef DEV_EXE
    extern CHARA _StageCharacterEntries[];
    gOverlayBase_800AB9C8 = &_StageCharacterEntries[0];
#else
    extern void *mts_get_bss_tail(void);
    gOverlayBase_800AB9C8 = mts_get_bss_tail();
#endif
}

void GM_ResetChara(void)
{
    int *chara;

#ifdef DEV_EXE
    return; // the overlay is embedded in the executable in dev variant
#endif

    chara = (int *)gOverlayBase_800AB9C8;
    chara[1] = 0;   // chara->func
    chara[0] = 0;   // chara->class_id
}

NEWCHARA GM_GetChara(unsigned char *script)
{
    return GM_GetCharaID(GCL_StrToInt(script));
}

NEWCHARA GM_GetCharaID(int chara_id)
{
    CHARA *chara_table;
    int    i = 0;

    do {
        // First search the fixed set of commands
        chara_table = &MainCharacterEntries[0];
        if (i != 0)
        {
            // Then look at the dynamically loaded commands
            chara_table = (CHARA *)gOverlayBase_800AB9C8;
        }

        if (chara_table->func)
        {
            do {
                if (chara_table->class_id == chara_id)
                {
                    return chara_table->func;
                }
                chara_table++;
            } while (chara_table->func);
        }
        i++;
    } while (i < 2);

    return NULL;
}
