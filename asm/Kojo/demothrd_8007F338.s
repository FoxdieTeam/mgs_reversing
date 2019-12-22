	opt	c+, at+, e+, n-
	section .text

	xdef demothrd_8007F338
demothrd_8007F338:
	dw 0x10800003 ; 0x8007F338
	dw 0x00000000 ; 0x8007F33C
	dw 0xAC840000 ; 0x8007F340
	dw 0xAC840004 ; 0x8007F344
	dw 0x03E00008 ; 0x8007F348
	dw 0x00000000 ; 0x8007F34C
