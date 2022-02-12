	opt	c+, at+, e+, n-
	section .text

	xdef read_800995AC
read_800995AC:
	dw 0x240A00B0 ; 0x800995AC
	dw 0x01400008 ; 0x800995B0
	dw 0x24090034 ; 0x800995B4
	dw 0x00000000 ; 0x800995B8
