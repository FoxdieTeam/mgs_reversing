	opt	c+, at+, e+, n-
	section overlay.text

	xdef roll_800C9310
roll_800C9310:
	dw 0x8FBF0010 ; 800C9310
	dw 0x27BD0018 ; 800C9314
	dw 0x03E00008 ; 800C9318
	dw 0x00000000 ; 800C931C
