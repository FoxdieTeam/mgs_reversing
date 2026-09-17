#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800D1380(void)
{
    MenuPrim *prim = &rank_dword_800E1978;

    prim->ot = DG_ChanlOTag(1);
    prim->next = prim->buf[GV_Clock];
}
