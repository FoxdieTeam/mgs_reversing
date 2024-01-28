	opt	c+, at+, e+, n-
	section overlay.text

	xdef roll_800C919C
roll_800C919C:
	dw 0x8FBF0010 ; 800C919C
	dw 0x27BD0018 ; 800C91A0
	dw 0x03E00008 ; 800C91A4
	dw 0x00000000 ; 800C91A8
