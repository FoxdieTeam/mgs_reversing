	opt	c+, at+, e+, n-
	section .text

	xdef ReturnFromException_800994FC
ReturnFromException_800994FC:
	dw 0x240A00B0 ; 0x800994FC
	dw 0x01400008 ; 0x80099500
	dw 0x24090017 ; 0x80099504
	dw 0x00000000 ; 0x80099508
