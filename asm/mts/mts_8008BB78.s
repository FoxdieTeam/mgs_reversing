
	opt	c+, at+, e+, n-
	section .text

	xdef mts_8008BB78
mts_8008BB78:
	dw 0x3C01800A ; 0x8008BB78
	dw 0xAC203DB4 ; 0x8008BB7C
	dw 0x03E00008 ; 0x8008BB80
	dw 0x00000000 ; 0x8008BB84
