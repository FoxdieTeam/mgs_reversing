	opt	c+, at+, e+, n-
	section .text

	xdef change_800C3B84
change_800C3B84:
	dw 0x8C820028 ; 800C3B84
	dw 0x03E00008 ; 800C3B88
	dw 0x00000000 ; 800C3B8C
