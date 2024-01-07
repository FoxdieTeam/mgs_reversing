	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800CC1DC
ending_800CC1DC:
	dw 0x8FBF0018 ; 800CC1DC
	dw 0x27BD0020 ; 800CC1E0
	dw 0x03E00008 ; 800CC1E4
	dw 0x00000000 ; 800CC1E8
