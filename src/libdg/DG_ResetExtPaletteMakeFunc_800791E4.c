extern int dword_8009F728;

void DG_StorePaletteEffect_80078F30(void);

void DG_ResetExtPaletteMakeFunc_800791E4(void)
{
    dword_8009F728 &= ~2;

    if ((dword_8009F728 & 1) == 0) {
        DG_StorePaletteEffect_80078F30();
    }
}
