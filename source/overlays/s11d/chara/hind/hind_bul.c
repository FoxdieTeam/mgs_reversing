#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"
#include "okajima/spark.h"

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
    GV_SubVec3((SVECTOR *)((char *)work + 0xF0), &pos, &diff);
    GV_LenVec3(&diff, &out, GV_VecLen3(&diff), 2000);
    GV_AddVec3(&pos, &out, &out);

    hit = GM_Target_8002E1B8(&pos, &out, *(int *)((char *)work + 0xEC), &out, ENEMY_SIDE);
    if (hit)
    {
        GM_MoveTarget((TARGET *)((char *)work + 0x9C), &out);
        GM_PowerTarget((TARGET *)((char *)work + 0x9C));
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
    int     temp;

    GM_ActControl(&work->control);

    *(int *)((char *)work + 0xE4) -= 2000;
    temp = *(unsigned short *)((char *)work + 0x22) + *(unsigned short *)((char *)work + 0x66);
    *(short *)((char *)work + 0x22) = temp;

    s11d_hind_bul_800CB888(work);

    if (s11d_hind_bul_800CB794(work) != 0)
    {
        GV_DestroyActor(work);
        return;
    }

    if (*(int *)((char *)work + 0xE4) <= 0)
    {
        rot.vx = -1024;
        rot.vz = 0;
        rot.vy = 0;
        RotMatrixYXZ(&rot, &mat);

        mat.t[0] = *(short *)((char *)work + 0xF0);
        mat.t[1] = *(short *)((char *)work + 0xF2);
        mat.t[2] = *(short *)((char *)work + 0xF4);

        GM_SeSet((SVECTOR *)((char *)work + 0xF0), 0xB5);

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
