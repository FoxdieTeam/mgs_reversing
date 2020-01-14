	opt	c+, at+, e+, n-
	section .text

	xdef SD_MDX_F4_80087754
SD_MDX_F4_80087754:
	dw 0x03E00008 ; 0x80087754
	dw 0x00000000 ; 0x80087758
