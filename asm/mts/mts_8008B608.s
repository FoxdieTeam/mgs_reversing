	opt	c+, at+, e+, n-
	section .text

	xdef mts_8008B608
mts_8008B608:
	dw 0x3C02800C ; 0x8008B608
	dw 0x8C420DB0 ; 0x8008B60C
	dw 0x03E00008 ; 0x8008B610
	dw 0x00000000 ; 0x8008B614