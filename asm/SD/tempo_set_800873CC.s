	opt	c+, at+, e+, n-
	section .text

	xdef tempo_set_800873CC
tempo_set_800873CC:
	dw 0x3C03800C ; 0x800873CC
	dw 0x8C63057C ; 0x800873D0
	dw 0x3C02800C ; 0x800873D4
	dw 0x8C42F0D4 ; 0x800873D8
	dw 0x03E00008 ; 0x800873DC
	dw 0xA06200B8 ; 0x800873E0
