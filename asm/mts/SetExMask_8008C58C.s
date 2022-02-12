
	opt	c+, at+, e+, n-
	section .text

	xdef SetExMask_8008C58C
SetExMask_8008C58C:
	dw 0x0001018D ; 0x8008C58C
	dw 0x03E00008 ; 0x8008C590
	dw 0x00000000 ; 0x8008C594
