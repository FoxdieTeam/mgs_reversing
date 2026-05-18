#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _HindBulWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    char    pad_a0[0xF8 - 0x20 - sizeof(CONTROL)];
    DG_PRIM *field_F8;
} HindBulWork;

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CB794.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CB888.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CB938.s")
void s11d_hind_bul_800CBA14(HindBulWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    prim = work->field_F8;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBA5C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBBA8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBE4C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBFD8.s")
