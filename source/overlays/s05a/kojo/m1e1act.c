#include "game/game.h"
#include "kojo/m1e1.h"

typedef struct
{
    HZD_VEC pOut[8];
    HZD_VEC pOut2[12];
} HzdBlock; /* 0xA0 */

typedef struct _Work
{
    char     pad_000[0x20];
    SVECTOR  field_20;      /* 0x020 */
    char     pad_28[0x6C - 0x28];
    SVECTOR  field_6C;      /* 0x06C */
    char     pad_74[0xDC - 0x74];
    OBJECT   body;          /* 0x0DC */
    OBJECT   bodies_a[3];   /* 0x1C0 */
    OBJECT   bodies_b[3];   /* 0x46C */
    void    *field_718[10]; /* 0x718 */
    char     pad_740[0xA84 - 0x740];
    struct { char _pad[0x48]; } field_A84[10]; /* 0xA84 */
    char     pad_D54[0xE9C - 0xD54];
    u_short  field_E9C;     /* 0xE9C */
    char     pad_E9E[0xEA0 - 0xE9E];
    u_short  field_EA0;     /* 0xEA0 */
    char     pad_EA2[0xF58 - 0xEA2];
    int      field_F58;     /* 0xF58 */
    char     pad_F5C[0xF8C - 0xF5C];
    SVECTOR  bbox[10];      /* 0xF8C */
    char     pad_FDC[0xFEC - 0xFDC];
    HzdBlock hzd[5];        /* 0xFEC */
    HZD_FLR  copy0;         /* 0x130C */
    HZD_FLR  copy1;         /* 0x133C */
    HZD_FLR  copy2;         /* 0x136C */
} Work;

extern void sub_8007E1C0(HZD_VEC *pOut, HZD_VEC *pOut2, MATRIX *pTransform,
                         SVECTOR *pMin, SVECTOR *pMax);
extern void AN_Smoke_800CE08C(SVECTOR *pos);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4A74.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D5E30.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D627C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D797C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D863C.s")
void s05a_800D9754(Work *work)
{
    SVECTOR vec;
    int     s0;

    if (work->field_F58 <= 0) return;
    if (work->field_F58 >= 0xF)
    {
        DG_SetPos2(&work->field_20, &work->field_6C);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&work->bbox[1].vy; vec.vz = (short)*(u_short *)&work->bbox[0].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&work->bbox[1].vy; vec.vz = (short)*(u_short *)&work->bbox[1].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8);
        vec.vx = *(u_short *)((char *)work->body.objs->objs[1].model + 0x20);
        vec.vy = *(u_short *)((char *)work->body.objs->objs[1].model + 0x24) + (*(u_short *)&work->bbox[9].vy - *(u_short *)&work->bbox[8].vy);
        vec.vz = *(u_short *)((char *)work->body.objs->objs[1].model + 0x28);
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
    }
    s0 = work->field_F58 - 0xA;
    {
        int d;
        if (s0 >= 0) { d = 5; s0 = 5 - s0; } else { d = 0xA; s0 = work->field_F58; }
        s0 = s0 * 34 / d;
    }
    memset(&vec, 0, 8); vec.vx = s0; DG_SetPos2(&DG_ZeroVector, &vec);
    DG_RotatePos(&work->body.rots[3]);
    {
        int dist, r;
        short pv[3];
        memset(&vec, 0, 8); vec.vz = 0x64; DG_PutVector(&vec, &vec, 1);
        dist = SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz); r = ratan2(vec.vy, dist);
        pv[0] = r;
        r = (short)r; if (r < 0) r = -r; pv[2] = s0 - r;
        s0 = work->body.rots[3].vy;
        while (s0 < 0) s0 += 0x1000;
        while (s0 >= 0x1001) s0 -= 0x1000;
        if (s0 >= 0x801) pv[2] = -pv[2];
        work->field_E9C += pv[0];
        work->field_EA0 += pv[2];
    }
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D9A14.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA02C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA62C.s")
#define WMDL(off) (*(u_short *)((char *)work->body.objs->objs[0].model + (off)))

void s05a_800DA940(Work *work)
{
    SVECTOR vec;
    SVECTOR verts[10];
    int     i;
    int     s0, s1;

    if (*(int *)((char *)work + 0xD54) == 6)
    {
        return;
    }

    DG_SetPos2(&work->field_20, &work->field_6C);
    M1E1GetCaterpillerVertex(&work->bodies_a[0], &work->bodies_b[0], verts, 1);
    for (i = 0; i < 10; i++) verts[i].vy += 0x258;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget((TARGET *)work->field_718[i], &verts[i]);
        GM_PushTarget((TARGET *)work->field_718[i]);
    }

    M1E1GetCaterpillerVertex(&work->bodies_a[0], &work->bodies_b[0], verts, 0);
    for (i = 0; i < 10; i++) verts[i].vy += 0x12C;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget((TARGET *)&work->field_A84[i], &verts[i]);
    }

    s0 = (*(int *)((char *)work + 0x8C8) * 3) >> 2;
    s1 = (*(int *)((char *)work + 0x95C) * 3) >> 2;

    vec.vx = 0; vec.vz = WMDL(0x1C) - s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x8CC), &vec);
    vec.vx = 0; vec.vz = WMDL(0x10) + s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x914), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x960), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x9A8), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x9F0), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0xA38), &vec);
}

void s05a_800DACF0(Work *work)
{
    work->copy0 = *(HZD_FLR *)((char *)work + 0x105C);
    work->copy1 = *(HZD_FLR *)((char *)work + 0x10FC);
    work->copy2 = *(HZD_FLR *)((char *)work + 0x12DC);

    sub_8007E1C0(work->hzd[0].pOut, work->hzd[0].pOut2,
                 (MATRIX *)((char *)work->body.objs + 0xA4), &work->bbox[0], &work->bbox[1]);
    sub_8007E1C0(work->hzd[1].pOut, work->hzd[1].pOut2,
                 (MATRIX *)((char *)work->body.objs + 0x100), &work->bbox[2], &work->bbox[3]);
    sub_8007E1C0(work->hzd[2].pOut, work->hzd[2].pOut2,
                 (MATRIX *)((char *)work->bodies_a[0].objs + 0x48), &work->bbox[4], &work->bbox[5]);
    sub_8007E1C0(work->hzd[3].pOut, work->hzd[3].pOut2,
                 (MATRIX *)((char *)work->bodies_b[0].objs + 0x48), &work->bbox[6], &work->bbox[7]);
    sub_8007E1C0(work->hzd[4].pOut, work->hzd[4].pOut2,
                 (MATRIX *)((char *)work->body.objs + 0x15C), &work->bbox[8], &work->bbox[9]);
}
