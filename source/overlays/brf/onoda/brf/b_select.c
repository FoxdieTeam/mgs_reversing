#include "game/game.h"

typedef struct _Work
{
    GV_ACT actor;             /* 0x000, size 0x20 */
    char   pad_20[0x15];      /* 0x020 */
    char   field_35;          /* 0x035 */
    char   field_36;          /* 0x036 */
    char   pad_37[0xE];       /* 0x037 */
    char   field_45;          /* 0x045 */
    char   field_46;          /* 0x046 */
    char   field_47;          /* 0x047 */
    char   field_48;          /* 0x048 */
    char   pad_49[0x27];      /* 0x049 */
    int    field_70;          /* 0x070 */
    char   pad_74[0x5C];      /* 0x074 */
    int    field_D0;          /* 0x0D0 */
    char   pad_D4[0x354];     /* 0x0D4 */
    int    field_428[64];     /* 0x428 */
    int    field_528;         /* 0x528 */
    char   pad_52C[0x100];    /* 0x52C */
    int    field_62C[64];     /* 0x62C */
    int    field_72C;         /* 0x72C */
    char   pad_730[0x8A4];    /* 0x730 */
    int    field_FD4;         /* 0xFD4 */
    int    field_FD8;         /* 0xFD8 */
    int    field_FDC;         /* 0xFDC */
    int    field_FE0;         /* 0xFE0 */
    char   pad_FE4[0x4];      /* 0xFE4 */
} Work;

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5230.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5350.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C53E4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5478.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5584.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C56C0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5A68.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5DE4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C5EAC.s")
void brf_800C5F74(Work *work)
{
    int i;

    work->field_528 = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->field_428[i] = 0;
    }

    work->field_72C = 0;
    for (i = 0x3F; i >= 0; i--)
    {
        work->field_62C[i] = 0;
    }
}
void brf_800C5350(Work *work);
void brf_800C5DE4(Work *work);

void brf_800C5FB4(Work *work)
{
    brf_800C5350(work);
    brf_800C5DE4(work);
}

void brf_800C53E4(Work *work);
void brf_800C5EAC(Work *work);

void brf_800C5FE0(Work *work)
{
    brf_800C53E4(work);
    brf_800C5EAC(work);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C600C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C609C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C60FC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6228.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C62B0.s")
void brf_800C65C8(Work *work)
{
    int i = 8;
    char *p = (char *)work + i;

    for (; i >= 0; i--, p--)
    {
        p[0x58] = 0;
    }
}
void brf_800C65E8(Work *work)
{
    int i = 0x2B;
    char *p = (char *)work + i;

    for (; i >= 0; i--, p--)
    {
        p[0x2C] = 0;
    }
    brf_800C65C8(work);
}
void brf_800C6620(Work *work)
{
    work->field_FD4 = 0;
    work->field_FD8 = 0;
    work->field_FDC = 0;
    work->field_FE0 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6634.s")
void brf_800C68EC(Work *work, int a1, int a2, int a3)
{
    work->field_FD8 = work->field_70;
    work->field_FD4 = a1;
    work->field_FDC = a2;
    work->field_70 = a2;
    work->field_D0 = 0;
    work->field_FE0 = a3;
    GM_SeSet2(0, 0x3F, 0x1F);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6930.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C69B4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C69FC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6AD0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6B54.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6C00.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6C74.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6D04.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6D7C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6E14.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6E88.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C731C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7488.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C75F0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7B28.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7B94.s")
void brf_800C7F20(Work *work)
{
    work->field_35 = 0;
    work->field_36 = 0;
    work->field_45 = 0;
    work->field_46 = 0;
    work->field_47 = 0;
    work->field_48 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7F3C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7F6C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7F9C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C7FF0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8038.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C80A8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C80C8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C80E8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8108.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8128.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8154.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8180.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C81AC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C81D8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C829C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C95B4.s")

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C96DC.s")
void brf_800C96DC(Work *work); // Act

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C972C.s")
void brf_800C972C(Work *work); // Die

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C97CC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C983C.s")

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C99C0.s")
int brf_800C99C0(Work *work, int where); // GetResources

void *NewBriefingSelect(int name, int where)
{
    Work *work;

    GM_GameStatus |= (STATE_MENU_OFF | STATE_LIFEBAR_OFF | STATE_PAUSE_OFF | STATE_RADIO_OFF);

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, brf_800C96DC, brf_800C972C, "b_select.c");
        if (brf_800C99C0(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
