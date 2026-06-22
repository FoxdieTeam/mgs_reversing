#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;   /* 0x000 */
    CONTROL control;  /* 0x020 */
    OBJECT  body;     /* 0x09C */
} Work;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DAE58.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DB278.s")

void s05a_800DB654(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DB684.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBA94.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBC44.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBC80.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBD14.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBED0.s")

void s05a_800DBF50(void *work)
{
    /* do nothing */
}
