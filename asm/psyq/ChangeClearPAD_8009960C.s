	opt	c+, at+, e+, n-
	section .text

	xdef ChangeClearPAD_8009960C
ChangeClearPAD_8009960C:
	dw 0x240A00B0 ; 0x8009960C
	dw 0x01400008 ; 0x80099610
	dw 0x2409005B ; 0x80099614
	dw 0x00000000 ; 0x80099618
