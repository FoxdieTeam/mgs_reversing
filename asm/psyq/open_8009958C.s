	opt	c+, at+, e+, n-
	section .text

	xdef open_8009958C
open_8009958C:
	dw 0x240A00B0 ; 0x8009958C
	dw 0x01400008 ; 0x80099590
	dw 0x24090032 ; 0x80099594
	dw 0x00000000 ; 0x80099598
