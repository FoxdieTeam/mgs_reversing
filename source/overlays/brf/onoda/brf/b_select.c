#include "game/game.h"

typedef struct _Work
{
    GV_ACT actor;             /* 0x000, size 0x20 */
    char   pad_20[0x10];      /* 0x020 */
    char   field_30;          /* 0x030 */
    char   field_31;          /* 0x031 */
    char   field_32;          /* 0x032 */
    char   field_33;          /* 0x033 */
    char   field_34;          /* 0x034 */
    char   field_35;          /* 0x035 */
    char   field_36;          /* 0x036 */
    char   field_37;          /* 0x037 */
    char   field_38;          /* 0x038 */
    char   field_39;          /* 0x039 */
    char   field_3A;          /* 0x03A */
    char   field_3B;          /* 0x03B */
    char   field_3C;          /* 0x03C */
    char   field_3D;          /* 0x03D */
    char   field_3E;          /* 0x03E */
    char   field_3F;          /* 0x03F */
    char   field_40;          /* 0x040 */
    char   field_41;          /* 0x041 */
    char   field_42;          /* 0x042 */
    char   field_43;          /* 0x043 */
    char   field_44;          /* 0x044 */
    char   field_45;          /* 0x045 */
    char   field_46;          /* 0x046 */
    char   field_47;          /* 0x047 */
    char   field_48;          /* 0x048 */
    char   field_49;          /* 0x049 */
    char   field_4A;          /* 0x04A */
    char   field_4B;          /* 0x04B */
    char   field_4C;          /* 0x04C */
    char   field_4D;          /* 0x04D */
    char   field_4E;          /* 0x04E */
    char   field_4F;          /* 0x04F */
    char   field_50;          /* 0x050 */
    char   field_51;          /* 0x051 */
    char   field_52;          /* 0x052 */
    char   field_53;          /* 0x053 */
    char   field_54;          /* 0x054 */
    char   field_55;          /* 0x055 */
    char   field_56;          /* 0x056 */
    char   pad_57[0x19];      /* 0x057 */
    int    field_70;          /* 0x070 */
    int    field_74;          /* 0x074 */
    char   pad_78[0x8];       /* 0x078 */
    int    field_80;          /* 0x080 */
    char   pad_84[0x4];       /* 0x084 */
    int    field_88;          /* 0x088 */
    char   pad_8C[0x4];       /* 0x08C */
    int    field_90;          /* 0x090 */
    char   pad_94[0x10];      /* 0x094 */
    int    field_A4;          /* 0x0A4 */
    char   pad_A8[0x8];       /* 0x0A8 */
    int    field_B0;          /* 0x0B0 */
    char   pad_B4[0x4];       /* 0x0B4 */
    int    field_B8;          /* 0x0B8 */
    char   pad_BC[0x10];      /* 0x0BC */
    int    field_CC;          /* 0x0CC */
    int    field_D0;          /* 0x0D0 */
    char   pad_D4[0x354];     /* 0x0D4 */
    int    field_428[64];     /* 0x428 */
    int    field_528;         /* 0x528 */
    char   pad_52C[0x100];    /* 0x52C */
    int    field_62C[64];     /* 0x62C */
    int    field_72C;         /* 0x72C */
    int      field_730[20];   /* 0x730 */
    POLY_FT4 field_780[9];    /* 0x780 */
    char     pad_8E8[0x6EC];  /* 0x8E8 */
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

void brf_800C5FB4(Work *work, int arg)
{
    brf_800C5350(work);
    brf_800C5DE4(work);
}

void brf_800C53E4(Work *work);
void brf_800C5EAC(Work *work);

void brf_800C5FE0(Work *work, int arg)
{
    brf_800C53E4(work);
    brf_800C5EAC(work);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C600C.s")
void brf_800C609C(Work *work, int sel, int arg)
{
    if (sel == 0)
    {
        brf_800C5FB4(work, arg);
    }
    else if (sel == 1)
    {
        brf_800C5FB4(work, arg);
        brf_800C5FE0(work, arg);
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C60FC.s")
void brf_800C60FC(Work *work);

void brf_800C6228(Work *work, int a1, int a2)
{
    GM_SeSet2(0, 0x3F, 0xB7);
    brf_800C60FC(work);
    GM_VoxStream(work->field_730[a1], 0x40000000);
    work->field_74 = work->field_70;
    work->field_70 = a2;
    work->field_D0 = 0;
    work->field_CC = a1;
    GM_SetSound(0x01FFFF0B, 0);
}
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
void brf_800C6930(Work *work, int idx1, int idx2, int base_y)
{
    POLY_FT4 *p = work->field_780;
    int x0, x3;

    x0 = p[idx1].x0;
    x3 = p[idx1].x3;
    p[idx1].y0 = base_y + 0xA;
    p[idx1].y1 = base_y + 0xA;
    p[idx1].y2 = base_y + 0xB;
    p[idx1].y3 = base_y + 0xB;
    p[idx1].x0 = x0;
    p[idx1].x1 = x3;
    p[idx1].x2 = x0;
    p[idx1].x3 = x3;

    x0 = p[idx2].x0;
    x3 = p[idx2].x3;
    p[idx2].y0 = base_y - 4;
    p[idx2].y1 = base_y - 4;
    p[idx2].y2 = base_y + 0xA;
    p[idx2].y3 = base_y + 0xA;
    p[idx2].x0 = x0;
    p[idx2].x1 = x3;
    p[idx2].x2 = x0;
    p[idx2].x3 = x3;
}
int brf_800C69B4(Work *work, int idx, int y, int h)
{
    POLY_FT4 *p = work->field_780;
    int x0 = p[idx].x0;
    int x3 = p[idx].x3;

    p[idx].y0 = y;
    p[idx].y1 = y;
    p[idx].y2 = y + 0xD;
    p[idx].y3 = y + 0xD;
    p[idx].x0 = x0;
    p[idx].x1 = x3;
    p[idx].x2 = x0;
    p[idx].x3 = x3;
    return y + h;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C69FC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C6AD0.s")
void brf_800C6B54(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    q = -12 - (d - a1) * 83 / 3;
    p[2].x0 = -142;
    p[2].y0 = q;
    p[2].x1 = -2;
    p[2].y1 = q;
    p[2].x2 = -142;
    p[2].y2 = q + 12;
    p[2].x3 = -2;
    p[2].y3 = q + 12;
    p[3].x0 = -142;
    p[3].y0 = q;
    p[3].x1 = -2;
    p[3].y1 = q;
    p[3].x2 = -142;
    p[3].y2 = q + 12;
    p[3].x3 = -2;
    p[3].y3 = q + 12;
}
void brf_800C6C00(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int diff;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_30 = 1;
    diff = d - a1;
    p[4].x0 = -142;
    p[4].y0 = diff * 13 - 95;
    p[4].x1 = -22;
    p[4].y1 = diff * 13 - 95;
    p[4].x2 = -142;
    p[4].y2 = diff * 13 - 78;
    p[4].x3 = -22;
    p[4].y3 = diff * 13 - 78;
}
void brf_800C6C74(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_31 = 1;
    q = (d - a1) * 46 / 3;
    p[5].x0 = -142;
    p[5].y0 = q - 95;
    p[5].x1 = -46;
    p[5].y1 = q - 95;
    p[5].x2 = -142;
    p[5].y2 = q - 78;
    p[5].x3 = -46;
    p[5].y3 = q - 78;
}
void brf_800C6D04(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_32 = 1;
    q = (d - a1) * 66 / 4;
    p[6].x0 = -142;
    p[6].y0 = q - 95;
    p[6].x1 = -22;
    p[6].y1 = q - 95;
    p[6].x2 = -142;
    p[6].y2 = q - 78;
    p[6].x3 = -22;
    p[6].y3 = q - 78;
}
void brf_800C6D7C(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_33 = 1;
    q = (d - a1) * 86 / 5;
    p[7].x0 = -142;
    p[7].y0 = q - 95;
    p[7].x1 = -46;
    p[7].y1 = q - 95;
    p[7].x2 = -142;
    p[7].y2 = q - 78;
    p[7].x3 = -46;
    p[7].y3 = q - 78;
}
void brf_800C6E14(Work *work, int a1, int a2)
{
    POLY_FT4 *p = work->field_780;
    int d = work->field_D0;
    int q;

    if (d < a1)
    {
        return;
    }
    if (a2 < d)
    {
        return;
    }
    work->field_34 = 1;
    q = (d - a1) * 23;
    p[8].x0 = -142;
    p[8].y0 = q - 95;
    p[8].x1 = -86;
    p[8].y1 = q - 95;
    p[8].x2 = -142;
    p[8].y2 = q - 83;
    p[8].x3 = -86;
    p[8].y3 = q - 83;
}
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
void brf_800C7F3C(Work *work)
{
    work->field_35 = 1;
    if (work->field_80 == 1)
    {
        work->field_36 = 1;
        work->field_47 = 1;
        work->field_48 = 1;
    }
    work->field_45 = 1;
    work->field_46 = 1;
}
void brf_800C7F6C(Work *work)
{
    work->field_37 = 0;
    work->field_38 = 0;
    work->field_39 = 0;
    work->field_3A = 0;
    work->field_3B = 0;
    work->field_49 = 0;
    work->field_4A = 0;
    work->field_4B = 0;
    work->field_4C = 0;
    work->field_53 = 0;
    work->field_54 = 0;
}
void brf_800C7F9C(Work *work)
{
    work->field_37 = 1;
    work->field_39 = 1;
    work->field_3B = 1;
    if (work->field_88 == 1)
    {
        work->field_38 = 1;
        work->field_49 = 1;
        work->field_4A = 1;
    }
    if (work->field_90 == 1)
    {
        work->field_3A = 1;
        work->field_4B = 1;
        work->field_4C = 1;
    }
    work->field_53 = 1;
    work->field_54 = 1;
}
void brf_800C7FF0(Work *work)
{
    work->field_3C = 0;
    work->field_3D = 0;
    work->field_3E = 0;
    work->field_3F = 0;
    work->field_40 = 0;
    work->field_41 = 0;
    work->field_42 = 0;
    work->field_43 = 0;
    work->field_44 = 0;
    work->field_4D = 0;
    work->field_4E = 0;
    work->field_4F = 0;
    work->field_50 = 0;
    work->field_51 = 0;
    work->field_52 = 0;
    work->field_55 = 0;
    work->field_56 = 0;
}
void brf_800C8038(Work *work)
{
    work->field_3C = 1;
    work->field_3D = 1;
    work->field_3E = 1;
    if (work->field_A4 == 1)
    {
        work->field_3F = 1;
        work->field_4D = 1;
        work->field_4E = 1;
    }
    work->field_40 = 1;
    work->field_41 = 1;
    if (work->field_B0 == 1)
    {
        work->field_42 = 1;
        work->field_4F = 1;
        work->field_50 = 1;
    }
    work->field_43 = 1;
    if (work->field_B8 == 1)
    {
        work->field_44 = 1;
        work->field_51 = 1;
        work->field_52 = 1;
    }
    work->field_55 = 1;
    work->field_56 = 1;
}
void brf_800C80A8(Work *work)
{
    brf_800C7F20(work);
}
void brf_800C80C8(Work *work)
{
    brf_800C7F3C(work);
}
void brf_800C80E8(Work *work)
{
    brf_800C7FF0(work);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8108.s")
void brf_800C8128(Work *work)
{
    brf_800C7F20(work);
    brf_800C7F9C(work);
}
void brf_800C8154(Work *work)
{
    brf_800C7F6C(work);
    brf_800C7F3C(work);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800C8180.s")
void brf_800C81AC(Work *work)
{
    brf_800C7FF0(work);
    brf_800C7F9C(work);
}
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
