#include "game/game.h"
#include "kojo/m1e1.h"
#include "libgcl/libgcl.h"

extern int s05a_dword_800C362C;

typedef struct
{
    HZD_SEG seg[4];
    HZD_FLR flr[2];
} HzdBlock; /* 0xA0 */

typedef struct _Work
{
    char     pad_000[0x20];
    CONTROL  control;       /* 0x020 (mov@0x20, map@0x4C, turn@0x6C) */
    char     pad_9C[0xDC - 0x9C];
    OBJECT   body;          /* 0x0DC */
    OBJECT   bodies_a[3];   /* 0x1C0 */
    OBJECT   bodies_b[3];   /* 0x46C */
    void    *field_718[10]; /* 0x718 */
    char     pad_740[0xA84 - 0x740];
    struct { char _pad[0x48]; } field_A84[10]; /* 0xA84 */
    int      field_D54;     /* 0xD54 */
    char     pad_D58[0xD64 - 0xD58];
    int      field_D64;     /* 0xD64 */
    int      field_D68;     /* 0xD68 */
    char     pad_D6C[0xE08 - 0xD6C];
    int      field_E08;     /* 0xE08 */
    int      field_E0C;     /* 0xE0C */
    int      field_E10;     /* 0xE10 */
    char     pad_E14[0xE1C - 0xE14];
    int      field_E1C;     /* 0xE1C */
    int      field_E20;     /* 0xE20 */
    char     pad_E24[0xE9C - 0xE24];
    u_short  field_E9C;     /* 0xE9C */
    char     pad_E9E[0xEA0 - 0xE9E];
    u_short  field_EA0;     /* 0xEA0 */
    char     pad_EA2[0xEB0 - 0xEA2];
    void    *field_EB0;     /* 0xEB0 */
    char     pad_EB4[0xEDC - 0xEB4];
    void    *field_EDC;     /* 0xEDC */
    char     pad_EE0[0xF58 - 0xEE0];
    int      field_F58;     /* 0xF58 */
    char     pad_F5C[0xF8C - 0xF5C];
    SVECTOR  bbox[10];      /* 0xF8C */
    char     pad_FDC[0xFEC - 0xFDC];
    HzdBlock hzd[5];        /* 0xFEC */
    HZD_FLR  copy0;         /* 0x130C */
    HZD_FLR  copy1;         /* 0x133C */
    HZD_FLR  copy2;         /* 0x136C */
} Work;

extern void sub_8007E1C0(HZD_SEG *seg, HZD_FLR *flr, MATRIX *pTransform,
                         SVECTOR *pMin, SVECTOR *pMax);
extern void AN_Smoke_800CE08C(SVECTOR *pos);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4A74.s")
void s05a_800D5E30(Work *work)
{
    int i;

    GM_uTenageMotion = -1;
    if (work->field_EDC) GV_DestroyActor(work->field_EDC);
    GM_lpfnPlayerActControl = 0;
    GM_lpfnPlayerActObject2 = 0;
    GM_lpfnBombHoming = 0;
    GM_lpfnBombBound = 0;
    GM_lpfnBombExplosion = 0;
    if (work->field_EB0) GV_DestroyActor(work->field_EB0);

    if (work->field_E1C >= 0)
    {
        long     argv[5];
        GCL_ARGS args;
        argv[0] = work->field_D64 / 10 * 30 / 100 * 60 / 1000 * 60;
        argv[1] = work->field_D68 * 30;
        argv[2] = work->field_E08;
        argv[3] = work->field_E0C;
        argv[4] = work->field_E10;
        args.argv = argv;
        args.argc = 5;
        GCL_ForceExecProc(work->field_E1C, &args);
    }

    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[0].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[0].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[1].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[1].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[2].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[2].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[3].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[3].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[4].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[4].flr[1]);

    GM_FreeObject(&work->body);
    for (i = 0; i < 3; i++)
    {
        GM_FreeObject(&work->bodies_a[i]);
        GM_FreeObject(&work->bodies_b[i]);
    }
    for (i = 0; i < 8; i++) GM_FreeTarget(work->field_718[i]);
    GM_FreeControl(&work->control);
    s05a_dword_800C362C = 0;
    if (work->field_D54 == 5 && work->field_E20 >= 0) GCL_ExecProc(work->field_E20, 0);
}
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
        DG_SetPos2(&work->control.mov, &work->control.turn);
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

    if (work->field_D54 == 6)
    {
        return;
    }

    DG_SetPos2(&work->control.mov, &work->control.turn);
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
    work->copy0 = work->hzd[0].flr[1];
    work->copy1 = work->hzd[1].flr[1];
    work->copy2 = work->hzd[4].flr[1];

    sub_8007E1C0(work->hzd[0].seg, work->hzd[0].flr,
                 (MATRIX *)((char *)work->body.objs + 0xA4), &work->bbox[0], &work->bbox[1]);
    sub_8007E1C0(work->hzd[1].seg, work->hzd[1].flr,
                 (MATRIX *)((char *)work->body.objs + 0x100), &work->bbox[2], &work->bbox[3]);
    sub_8007E1C0(work->hzd[2].seg, work->hzd[2].flr,
                 (MATRIX *)((char *)work->bodies_a[0].objs + 0x48), &work->bbox[4], &work->bbox[5]);
    sub_8007E1C0(work->hzd[3].seg, work->hzd[3].flr,
                 (MATRIX *)((char *)work->bodies_b[0].objs + 0x48), &work->bbox[6], &work->bbox[7]);
    sub_8007E1C0(work->hzd[4].seg, work->hzd[4].flr,
                 (MATRIX *)((char *)work->body.objs + 0x15C), &work->bbox[8], &work->bbox[9]);
}
