#include "common.h"
#include "mts/mts.h"

#include "game.h"
#include "charadef.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

extern GCL_Vars gGcl_vars_800B3CC8;

extern CHARA MainCharacterEntries[];    /* in main.c */
extern CHARA _StageCharacterEntries[];  /* only visible when built-in */

// force gp usage
void *SECTION(".sbss") StageCharacterEntries;

void GM_InitChara(void)
{
#ifdef DEV_EXE
    StageCharacterEntries = &_StageCharacterEntries[0];
#else
    extern void *mts_get_bss_tail(void);
    StageCharacterEntries = mts_get_bss_tail();
#endif
}

void GM_ResetChara(void)
{
    CHARA *chara;

#ifndef DEV_EXE
    chara = (CHARA *)StageCharacterEntries;
    // overwrite the first entry with the end-of-table marker
    *((int *)&chara->func) = 0;
    *((int *)&chara->class_id) = 0;
#endif
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
            chara_table = (CHARA *)StageCharacterEntries;
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
