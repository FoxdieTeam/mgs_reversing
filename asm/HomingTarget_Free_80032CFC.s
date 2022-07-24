	opt	c+, at+, e+, n-
	section .text

	xdef HomingTarget_Free_80032CFC
HomingTarget_Free_80032CFC:
	dw 0x10800002 ; 0x80032CFC
	dw 0x00000000 ; 0x80032D00
	dw 0xAC80000C ; 0x80032D04
	dw 0x03E00008 ; 0x80032D08
	dw 0x00000000 ; 0x80032D0C
