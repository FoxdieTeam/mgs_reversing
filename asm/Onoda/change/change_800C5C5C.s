	opt	c+, at+, e+, n-
	section .text

	xdef change_800C5C5C
change_800C5C5C:
	dw 0x240A00B0 ; 800C5C5C
	dw 0x01400008 ; 800C5C60
	dw 0x24090051 ; 800C5C64
