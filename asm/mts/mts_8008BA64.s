
	opt	c+, at+, e+, n-
	section .text

	xdef mts_8008BA64
mts_8008BA64:
	dw 0x3C01800A ; 0x8008BA64
	dw 0xAC203DB0 ; 0x8008BA68
	dw 0x03E00008 ; 0x8008BA6C
	dw 0x00000000 ; 0x8008BA70
