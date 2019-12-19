	opt	c+, at+, e+, n-
	section .text

	xdef mts_8008C598
mts_8008C598:
	dw 0x3C02800C ; 0x8008C598
	dw 0x24423208 ; 0x8008C59C
	dw 0x03E00008 ; 0x8008C5A0
	dw 0x00000000 ; 0x8008C5A4
