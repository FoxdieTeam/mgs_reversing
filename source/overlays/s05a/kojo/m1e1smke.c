#include "game/game.h"

typedef struct
{
    GV_ACT  actor;      /* 0x00 */
    int     field_20;   /* 0x20 */
    int     field_24;   /* 0x24 */
    SVECTOR field_28;   /* 0x28 */
    SVECTOR field_30;   /* 0x30 */
    int     field_38;   /* 0x38 */
    int     field_3c;   /* 0x3C */
} Work;

extern const char s05a_dword_800E34E8[];

void s05a_800DC058(GV_ACT *actor);
void s05a_800DC224(void *work);

Work *s05a_800DBF58(int type, SVECTOR *a1, SVECTOR *a2)
{
    Work *work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));

    if (work == NULL)
    {
        return NULL;
    }

    work->field_24 = type;
    work->field_20 = GM_CurrentMap;
    work->field_28 = *a1;
    work->field_30 = *a2;
    work->field_3c = 0;
    switch (work->field_24)
    {
    case 0:
        work->field_38 = 60;
        break;
    case 1:
        work->field_38 = 10;
        break;
    }
    GV_SetNamedActor(&work->actor, s05a_800DC058, s05a_800DC224, s05a_dword_800E34E8);
    return work;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DC058.s")

void s05a_800DC224(void *work)
{
    /* do nothing */
}
