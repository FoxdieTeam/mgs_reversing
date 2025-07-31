#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

extern void (*pfn_800BDFB0)();
extern unsigned short (*pfn_800BDFB4)(unsigned short);

extern u_long DG_PaletteBuffer_800B3818[256];

/*---------------------------------------------------------------------------*/

STATIC int dword_8009F728 = 0;

STATIC RECT takabe_palette1 = { 768, 226, 256, 2 };
STATIC RECT takabe_palette2 = { 768, 196, 256, 2 };

void DG_StorePalette2(void)
{
    StoreImage(&takabe_palette2, DG_PaletteBuffer_800B3818);
}

void DG_StorePaletteEffect(void)
{
    RECT rect1 = takabe_palette1;
    RECT rect2 = takabe_palette2;
    int i;

    for (i = 15; i > 0; i--)
    {
        DrawSync(0);
        StoreImage2(&rect2, DG_PaletteBuffer_800B3818);
        DrawSync(0);
        LoadImage2(&rect1, DG_PaletteBuffer_800B3818);
        rect2.y += 2;
        rect1.y += 2;
    }
}

void DG_ResetPaletteEffect(void)
{
    dword_8009F728 = 0;
}

static inline u_short modify_data(u_short data, u_short param_2)
{
    u_short high = data & 0x8000;

    if ((data & 0x7fff) != 0)
    {
        return high | param_2;
    }
    else
    {
        return high;
    }
}

void sub_80079004(u_short param_1)
{
    RECT    rect = takabe_palette1;
    int     i, j;
    u_short *ptr;

    for (i = 15; i > 0; i--)
    {
        DrawSync(0);
        StoreImage2(&rect, DG_PaletteBuffer_800B3818);
        DrawSync(0);

        ptr = (u_short *)DG_PaletteBuffer_800B3818;

        for (j = 512; j > 0; j--)
        {
            *ptr++ = modify_data(*ptr, param_1);
        }

        LoadImage2(&rect, DG_PaletteBuffer_800B3818);
        rect.y += 2;
    }
}

void sub_800790E8(void)
{
    unsigned short uVar2 = 0x7fff;

    dword_8009F728 |= 1;

    if ((dword_8009F728 & 2) != 0)
    {
        uVar2 = (*pfn_800BDFB4)(0x7fff);
    }

    sub_80079004(uVar2);
}

void sub_8007913C(void)
{
    dword_8009F728 &= ~0x1;

    if ((dword_8009F728 & 2) != 0)
    {
        (*pfn_800BDFB0)();
    }
    else
    {
        DG_StorePaletteEffect();
    }
}

void DG_SetExtPaletteMakeFunc(void (*param_1)(void), u_short (*param_2)(u_short))
{
    pfn_800BDFB0 = param_1;
    pfn_800BDFB4 = param_2;

    dword_8009F728 |= 2;

    if ((dword_8009F728 & 1) == 0)
    {
        param_1();
    }
}

void DG_ResetExtPaletteMakeFunc(void)
{
    dword_8009F728 &= ~2;

    if ((dword_8009F728 & 1) == 0)
    {
        DG_StorePaletteEffect();
    }
}

void DG_MakeEffectPalette(unsigned short *param_1, int param_2)
{
    if ((dword_8009F728 & 2) == 0)
    {
        return;
    }

    if (param_2 <= 0)
    {
        return;
    }

    for (; param_2 > 0; param_2--)
    {
        *param_1 = pfn_800BDFB4(*param_1);
    }
}
