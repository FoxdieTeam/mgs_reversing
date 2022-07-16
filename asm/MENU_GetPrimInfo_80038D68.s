	opt	c+, at+, e+, n-
	section .text

	xdef MENU_GetPrimInfo_80038D68
MENU_GetPrimInfo_80038D68:
	dw 0x3C02800A ; 0x80038D68
	dw 0x03E00008 ; 0x80038D6C
	dw 0x2442E2D0 ; 0x80038D70
