	opt	c+, at+, e+, n-
	section .text

	xdef memcard_get_status_800257B0
memcard_get_status_800257B0:
	dw 0x3C02800B ; 0x800257B0
	dw 0x8C425648 ; 0x800257B4
	dw 0x03E00008 ; 0x800257B8
	dw 0x00000000 ; 0x800257BC
