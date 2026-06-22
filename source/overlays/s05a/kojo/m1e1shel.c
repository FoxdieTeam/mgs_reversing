#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;   /* 0x000 */
    CONTROL control;  /* 0x020 */
    OBJECT  body;     /* 0x09C */
} Work;

typedef struct _Casing
{
    GV_ACT   actor;     /* 0x00 */
    int      field_20;  /* 0x20 */
    DG_PRIM *field_24;  /* 0x24 */
} Casing;

typedef struct _Smoke
{
    GV_ACT  actor;     /* 0x00 */
    int     field_20;  /* 0x20 */
    SVECTOR field_24;  /* 0x24 */
    SVECTOR field_2C;  /* 0x2C */
    int     field_34;  /* 0x34 */
} Smoke;

extern void *s05a_800DBF58(int arg0, SVECTOR *arg1, SVECTOR *arg2);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DAE58.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DB278.s")

void s05a_800DB654(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DB684.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBA94.s")

void s05a_800DBC44(Casing *work)
{
    DG_PRIM *prim = work->field_24;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBC80.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DBD14.s")

void s05a_800DBED0(Smoke *work)
{
    int n;

    GM_CurrentMap = work->field_20;
    n = work->field_34 + 1;
    work->field_34 = n;
    if (n == 1)
    {
        s05a_800DBF58(1, &work->field_24, &work->field_2C);
    }
    else if (n == 2)
    {
        sub_8007913C();
    }
    else if (n >= 30)
    {
        GV_DestroyActor(work);
    }
}

void s05a_800DBF50(void *work)
{
    /* do nothing */
}
