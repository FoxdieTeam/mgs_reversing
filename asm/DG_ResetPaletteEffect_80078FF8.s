	opt	c+, at+, e+, n-
	section .text

	xdef DG_ResetPaletteEffect_80078FF8
DG_ResetPaletteEffect_80078FF8:
	dw 0x3C02800A ; 0x80078FF8
	dw 0x03E00008 ; 0x80078FFC
	dw 0xAC40F728 ; 0x80079000
