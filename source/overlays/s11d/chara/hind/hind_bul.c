#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _HindBulWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    char    pad_a0[0xE8 - 0x20 - sizeof(CONTROL)];
    int     field_E8;
    char    pad_ec[0xF8 - 0xE8 - sizeof(int)];
    DG_PRIM *prim;
    char    pad_fc[0x17C - 0xF8 - sizeof(DG_PRIM *)];
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

    RotMatrixYXZ(&svec_a, &work->prim->world);

    work->prim->world.t[0] = work->control.mov.vx;
    work->prim->world.t[1] = work->control.mov.vy;
    work->prim->world.t[2] = work->control.mov.vz;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CB938.s")
void s11d_hind_bul_800CBA14(HindBulWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreePrim(work->prim);
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBA5C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBBA8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_bul_800CBE4C.s")
extern int  s11d_dword_800D1F88;
extern void s11d_hind_bul_800CB938(HindBulWork *work);
extern int  s11d_hind_bul_800CBE4C(HindBulWork *work, int arg0, int arg1);
extern const char s11d_dword_800D1E58[];

HindBulWork *s11d_hind_bul_800CBFD8(int arg0, int arg1, int arg2, int arg3)
{
    HindBulWork *work;

    work = GV_NewActor(5, sizeof(HindBulWork));
    if (work == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(work, s11d_hind_bul_800CB938, s11d_hind_bul_800CBA14, s11d_dword_800D1E58);
    if (s11d_hind_bul_800CBE4C(work, arg0, arg1) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }
    s11d_dword_800D1F88 = arg3;
    work->field_E8 = arg2;
    return work;
}
