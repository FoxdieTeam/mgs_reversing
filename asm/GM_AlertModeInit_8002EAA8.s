	opt	c+, at+, e+, n-
	section .text

	xdef GM_AlertModeInit_8002EAA8
GM_AlertModeInit_8002EAA8:
	dw 0x2402FFFF ; 0x8002EAA8
	dw 0xA782079C ; 0x8002EAAC
	dw 0x03E00008 ; 0x8002EAB0
	dw 0x00000000 ; 0x8002EAB4
