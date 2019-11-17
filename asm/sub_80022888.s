	opt	c+, at+, e+, n-
	section .text

	xdef sub_80022888
sub_80022888:
	dw 0x3C02800B ; 0x80022888
	dw 0x8C424E58 ; 0x8002288C
	dw 0x03E00008 ; 0x80022890
	dw 0x00000000 ; 0x80022894
