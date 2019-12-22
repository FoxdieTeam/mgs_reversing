	opt	c+, at+, e+, n-
	section .text

	xdef SD_80086EF8
SD_80086EF8:
	dw 0x03E00008 ; 0x80086EF8
	dw 0x00000000 ; 0x80086EFC
