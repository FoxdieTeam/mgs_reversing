	opt	c+, at+, e+, n-
	section .text

	xdef MENU_SetRadarFunc_80038F30
MENU_SetRadarFunc_80038F30:
	dw 0xAF8401A8 ; 0x80038F30
	dw 0x03E00008 ; 0x80038F34
	dw 0x00000000 ; 0x80038F38
