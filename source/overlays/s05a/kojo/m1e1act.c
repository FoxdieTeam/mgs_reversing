#include "game/game.h"

typedef struct
{
    int a, b, c, d;
} Quad;

typedef struct
{
    HZD_VEC pOut[8];
    HZD_VEC pOut2[12];
} HzdBlock; /* 0xA0 */

typedef struct _Work
{
    char     pad_000[0xDC];
    OBJECT   body;          /* 0x0DC */
    OBJECT   bodies_a[3];   /* 0x1C0 */
    OBJECT   bodies_b[3];   /* 0x46C */
    char     pad_718[0xF8C - 0x718];
    SVECTOR  bbox[10];      /* 0xF8C */
    char     pad_FDC[0xFEC - 0xFDC];
    HzdBlock hzd[5];        /* 0xFEC */
    char     copy0[0x30];   /* 0x130C */
    char     copy1[0x30];   /* 0x133C */
    char     copy2[0x30];   /* 0x136C */
} Work;

extern void sub_8007E1C0(HZD_VEC *pOut, HZD_VEC *pOut2, MATRIX *pTransform,
                         SVECTOR *pMin, SVECTOR *pMax);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4A74.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D5E30.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D627C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D797C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D863C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D9754.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D9A14.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA02C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA62C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA940.s")

void s05a_800DACF0(Work *work)
{
    Quad *src, *dst, *end;

    dst = (Quad *)((char *)work + 0x130C);
    src = (Quad *)((char *)work + 0x105C);
    end = (Quad *)((char *)work + 0x108C);
    do
    {
        *dst++ = *src++;
    } while (src != end);

    dst = (Quad *)((char *)work + 0x133C);
    src = (Quad *)((char *)work + 0x10FC);
    end = (Quad *)((char *)work + 0x112C);
    do
    {
        *dst++ = *src++;
    } while (src != end);

    dst = (Quad *)((char *)work + 0x136C);
    src = (Quad *)((char *)work + 0x12DC);
    end = (Quad *)((char *)work + 0x130C);
    do
    {
        *dst++ = *src++;
    } while (src != end);

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
