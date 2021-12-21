	opt	c+, at+, e+, n-
	section .text

	xdef erase_800995FC
erase_800995FC:
	dw 0x240A00B0 ; 0x800995FC
	dw 0x01400008 ; 0x80099600
	dw 0x24090045 ; 0x80099604
	dw 0x00000000 ; 0x80099608
