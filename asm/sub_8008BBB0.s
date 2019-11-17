	opt	c+, at+, e+, n-
	section .text

	xdef sub_8008BBB0
sub_8008BBB0:
	dw 0x3C02800A ; 0x8008BBB0
	dw 0x8C423D78 ; 0x8008BBB4
	dw 0x03E00008 ; 0x8008BBB8
	dw 0x00000000 ; 0x8008BBBC
