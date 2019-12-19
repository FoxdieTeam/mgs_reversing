	opt	c+, at+, e+, n-
	section .text

	xdef mts_8008BB88
mts_8008BB88:
	dw 0x3C01800A ; 0x8008BB88
	dw 0xAC243DB8 ; 0x8008BB8C
	dw 0x03E00008 ; 0x8008BB90
	dw 0x00000000 ; 0x8008BB94
