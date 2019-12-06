	opt	c+, at+, e+, n-
	section .text

	xdef srand_8008E6E8
srand_8008E6E8:
	dw 0x3C01800C ; 0x8008E6E8
	dw 0x03E00008 ; 0x8008E6EC
	dw 0xAC241530 ; 0x8008E6F0
	dw 0x00000000 ; 0x8008E6F4
