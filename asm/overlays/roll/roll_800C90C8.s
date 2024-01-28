	opt	c+, at+, e+, n-
	section overlay.text

	xdef roll_800C90C8
roll_800C90C8:
	dw 0x94820000 ; 800C90C8
	dw 0x03E00008 ; 800C90CC
	dw 0x00000000 ; 800C90D0
