#include "psyq.h"

extern void (*pfn_800BDFB0)();
extern unsigned short (*pfn_800BDFB4)(unsigned short);

extern u_long image_data_800B3818[256];

int dword_8009F728 = 0;
RECT rect_8009F72C = {768, 226, 256, 2};
RECT rect_8009F734 = {768, 196, 256, 2};

void sub_80078F04()
{
    StoreImage(&rect_8009F734, image_data_800B3818);
}

void DG_StorePaletteEffect_80078F30()
{
    RECT rect1 = rect_8009F72C;
    RECT rect2 = rect_8009F734;
    int count;

    for (count = 15; count > 0; count--)
    {
        DrawSync(0);
        StoreImage2(&rect2, image_data_800B3818);
        DrawSync(0);
        LoadImage2(&rect1, image_data_800B3818);
        rect2.y += 2;
        rect1.y += 2;
    }
}

void DG_ResetPaletteEffect_80078FF8()
{
    dword_8009F728 = 0;
}

static inline ushort modify_data(ushort data, ushort param_2)
{
    ushort high = data & 0x8000;

    if ((data & 0x7fff) != 0)
    {
        return high | param_2;
    }
    else
    {
        return high;
    }
}

void sub_80079004(ushort param_1)
{
    RECT    rect = rect_8009F72C;
    int     count, count2;
    ushort *ptr;

    count = 15;

    for (; count > 0; count--)
    {
        DrawSync(0);
        StoreImage2(&rect, image_data_800B3818);
        DrawSync(0);

        ptr = (ushort *)image_data_800B3818;
        count2 = 512;

        for (; count2 > 0; count2--)
        {
            *ptr++ = modify_data(*ptr, param_1);
        }

        LoadImage2(&rect, image_data_800B3818);
        rect.y += 2;
    }
}

void sub_800790E8()
{
    unsigned short uVar2 = 0x7fff;

    dword_8009F728 |= 1;

    if ((dword_8009F728 & 2) != 0)
    {
        uVar2 = (*pfn_800BDFB4)(0x7fff);
    }

    sub_80079004(uVar2);
}

void sub_8007913C()
{
    dword_8009F728 &= ~0x1;

    if ((dword_8009F728 & 2) != 0)
    {
        (*pfn_800BDFB0)();
    }
    else
    {
        DG_StorePaletteEffect_80078F30();
    }
}

void set_pal_effect_fns_80079194(void (*param_1)(), void (*param_2)())
{
    pfn_800BDFB0 = param_1;
    pfn_800BDFB4 = (void *)param_2;

    dword_8009F728 |= 2;

    if ((dword_8009F728 & 1) == 0)
    {
        param_1();
    }
}

void DG_ResetExtPaletteMakeFunc_800791E4()
{
    dword_8009F728 &= ~2;

    if ((dword_8009F728 & 1) == 0)
    {
        DG_StorePaletteEffect_80078F30();
    }
}

void DG_MakeEffectPalette_80079220(unsigned short *param_1, int param_2)
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
