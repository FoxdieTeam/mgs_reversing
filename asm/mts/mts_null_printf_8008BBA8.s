	opt	c+, at+, e+, n-
	section .text

	xdef mts_null_printf_8008BBA8
mts_null_printf_8008BBA8:
	dw 0x03E00008 ; 0x8008BBA8
	dw 0x00000000 ; 0x8008BBAC
