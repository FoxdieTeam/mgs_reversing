extern int dword_8009F728;

void DG_StorePaletteEffect_80078F30(void);

void DG_ResetExtPaletteMakeFunc_800791E4(void)
{
    unsigned int uVar1;

    uVar1 = dword_8009F728 & 1;
    dword_8009F728 &= 0xfffffffd;

    if (uVar1 == 0) {
        DG_StorePaletteEffect_80078F30();
    }
}
