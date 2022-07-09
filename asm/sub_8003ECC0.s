	opt	c+, at+, e+, n-
	section .text

	xdef sub_8003ECC0
sub_8003ECC0:
	dw 0xAF800804 ; 0x8003ECC0
	dw 0x03E00008 ; 0x8003ECC4
	dw 0x00000000 ; 0x8003ECC8
