#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    char            pad_180[0x7DC - 0x180];
    OBJECT          field_7DC;      /* 0x7DC */
    char            pad_8C0[0x8CC - 0x8C0];
    TARGET         *target;      /* 0x8CC */
    char            pad_8D0[0x9B0 - 0x8D0];
    void           *field_9B0;      /* 0x9B0 */
    void           *field_9B4;      /* 0x9B4 */
} Work;

extern int s03d_dword_800C3960;
extern int s03d_dword_800C3968;

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB4B4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB530.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB640.s")
void Meryl3_800CB834(Work *work)
{
    TARGET *t = work->target;

    GM_SetTarget(t, 0x14, 1, (SVECTOR *)&s03d_dword_800C3960);
    GM_SetPowerTarget(t, 1, -1, 0xEA60, 0xEA60, (SVECTOR *)&s03d_dword_800C3968);
}

void Meryl3_800CB894(Work *work)
{
    GV_DestroyActor(work->field_9B0);
    GV_DestroyActor(work->field_9B4);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_9C);
    GM_FreeObject(&work->field_7DC);
    GM_FreeTarget(work->target);
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CB8F0.s")
