	opt	c+, at+, e+, n-
	section .text

	xdef null_printf_8008BBA8
null_printf_8008BBA8:
	dw 0x03E00008 ; 0x8008BBA8
	dw 0x00000000 ; 0x8008BBAC
