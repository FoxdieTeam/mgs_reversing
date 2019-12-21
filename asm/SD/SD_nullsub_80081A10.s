	opt	c+, at+, e+, n-
	section .text

	xdef SD_nullsub_80081A10
SD_nullsub_80081A10:
	dw 0x03E00008 ; 0x80081A10
	dw 0x00000000 ; 0x80081A14
