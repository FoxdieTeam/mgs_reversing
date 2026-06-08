#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"
#include "okajima/spark.h"

typedef struct _HindBulWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    TARGET  target;      // 0x9C
    int     field_E4;
    int     field_E8;
    int     field_EC;
    SVECTOR field_F0;
    DG_PRIM *prim;
    char    pad_fc[0x17C - 0xF8 - sizeof(DG_PRIM *)];
} HindBulWork;

int s11d_hind_bul_800CB794(HindBulWork *work)
{
    SVECTOR pos;
    SVECTOR out;
    SVECTOR diff;
    int     hit;

    if (work->field_E8 == 0)
    {
        return 0;
    }

    pos = work->control.mov;
    GV_SubVec3(&work->field_F0, &pos, &diff);
    GV_LenVec3(&diff, &out, GV_VecLen3(&diff), 2000);
    GV_AddVec3(&pos, &out, &out);

    hit = GM_Target_8002E1B8(&pos, &out, work->field_EC, &out, ENEMY_SIDE);
    if (hit)
    {
        GM_MoveTarget(&work->target, &out);
        GM_PowerTarget(&work->target);
    }

    return hit;
}

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
void s11d_hind_bul_800CB938(HindBulWork *work)
{
    MATRIX  mat;
    SVECTOR rot;
    VECTOR  scale;

    GM_ActControl(&work->control);

    work->field_E4 -= 2000;
    work->control.mov.vy = (unsigned short)work->control.mov.vy + (unsigned short)work->control.step.vy;

    s11d_hind_bul_800CB888(work);

    if (s11d_hind_bul_800CB794(work) != 0)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->field_E4 <= 0)
    {
        rot.vx = -1024;
        rot.vz = 0;
        rot.vy = 0;
        RotMatrixYXZ(&rot, &mat);

        mat.t[0] = work->field_F0.vx;
        mat.t[1] = work->field_F0.vy;
        mat.t[2] = work->field_F0.vz;

        GM_SeSet(&work->field_F0, 0xB5);

        scale.vz = 0x2000;
        scale.vy = 0x2000;
        scale.vx = 0x2000;
        ScaleMatrix(&mat, &scale);
        NewSpark(&mat, 1);

        GV_DestroyActor(work);
    }
}

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
