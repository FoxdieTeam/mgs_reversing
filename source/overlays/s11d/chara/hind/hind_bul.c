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
extern SVECTOR DG_ZeroVector;

void s11d_hind_bul_800CB888(HindBulWork *work)
{
    SVECTOR svec_a;
    SVECTOR svec_b;

    svec_a = DG_ZeroVector;
    svec_a.vy = GV_VecDir2(&work->control.step);
    svec_b.vx = work->control.step.vy;
    svec_b.vz = work->control.step.vz;
    svec_a.vx = GV_VecDir2(&svec_b);

    RotMatrixYXZ(&svec_a, (MATRIX *)work->field_F8);

    work->field_F8->world.t[0] = work->control.mov.vx;
    work->field_F8->world.t[1] = work->control.mov.vy;
    work->field_F8->world.t[2] = work->control.mov.vz;
}
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
