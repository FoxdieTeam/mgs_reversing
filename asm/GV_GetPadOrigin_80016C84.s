	opt	c+, at+, e+, n-
	section .text

	xdef GV_GetPadOrigin_80016C84
GV_GetPadOrigin_80016C84:
	dw 0x8F820094 ; 0x80016C84
	dw 0x03E00008 ; 0x80016C88
	dw 0x00000000 ; 0x80016C8C
