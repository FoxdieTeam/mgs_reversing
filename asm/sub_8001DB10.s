	opt	c+, at+, e+, n-
	section .text

	xdef sub_8001DB10
sub_8001DB10:
	dw 0xAF8006A4 ; 0x8001DB10
	dw 0xAF8006A8 ; 0x8001DB14
	dw 0x03E00008 ; 0x8001DB18
	dw 0x00000000 ; 0x8001DB1C
