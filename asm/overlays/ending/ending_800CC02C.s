	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800CC02C
ending_800CC02C:
	dw 0x8FBF0010 ; 800CC02C
	dw 0x27BD0018 ; 800CC030
	dw 0x03E00008 ; 800CC034
	dw 0x00000000 ; 800CC038
