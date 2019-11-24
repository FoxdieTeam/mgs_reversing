	opt	c+, at+, e+, n-
	section .text

	xdef mg_printf_8008BBA0
mg_printf_8008BBA0:
	dw 0x03E00008 ; 0x8008BBA0
	dw 0x00000000 ; 0x8008BBA4
