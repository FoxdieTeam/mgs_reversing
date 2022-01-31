	opt	c+, at+, e+, n-
	section .text

	xdef close_800995CC
close_800995CC:
	dw 0x240A00B0 ; 0x800995CC
	dw 0x01400008 ; 0x800995D0
	dw 0x24090036 ; 0x800995D4
	dw 0x00000000 ; 0x800995D8
