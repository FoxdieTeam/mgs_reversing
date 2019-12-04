	opt	c+, at+, e+, n-
	section .text

	xdef SetMem_8009944C
SetMem_8009944C:
	dw 0x240A00A0 ; 0x8009944C
	dw 0x01400008 ; 0x80099450
	dw 0x2409009F ; 0x80099454
	dw 0x00000000 ; 0x80099458
