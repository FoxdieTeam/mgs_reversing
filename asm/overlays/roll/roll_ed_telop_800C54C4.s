	opt	c+, at+, e+, n-
	section overlay.text

	xdef roll_ed_telop_800C54C4
roll_ed_telop_800C54C4:
	dw 0x8FB10014 ; 800C54C4
	dw 0x8FB00010 ; 800C54C8
	dw 0x03E00008 ; 800C54CC
	dw 0x27BD0020 ; 800C54D0
