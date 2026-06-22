#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;     /* 0x00 */
    int     field_20;  /* 0x20 */
    int     field_24;  /* 0x24 */
    SVECTOR field_28;  /* 0x28 */
    SVECTOR field_30;  /* 0x30 */
    int     field_38;  /* 0x38 */
    int     field_3C;  /* 0x3C */
} Work;

extern const char s05a_dword_800E34E8[]; /* = "m1e1smke.c" */

void s05a_800DC058(Work *work);
void s05a_800DC224(void *work);

void *s05a_800DBF58(int arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    work->field_24 = arg0;
    work->field_20 = GM_CurrentMap;
    work->field_28 = *arg1;
    work->field_30 = *arg2;
    work->field_3C = 0;
    switch (work->field_24)
    {
    case 0:
        work->field_38 = 0x3C;
        break;
    case 1:
        work->field_38 = 0xA;
        break;
    }
    GV_SetNamedActor(work, s05a_800DC058, s05a_800DC224, s05a_dword_800E34E8);

    return work;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DC058.s")

void s05a_800DC224(void *work)
{
    /* do nothing */
}
