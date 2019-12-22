	opt	c+, at+, e+, n-
	section .text

	xdef memcard_800244DC
memcard_800244DC:
	dw 0x3C02800B ; 0x800244DC
	dw 0xAC4452F4 ; 0x800244E0
	dw 0x03E00008 ; 0x800244E4
	dw 0x00000000 ; 0x800244E8
