	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800CC020
ending_800CC020:
	dw 0x3C04800D ; 800CC020
	dw 0x0C022EE8 ; 800CC024
	dw 0x2484CD4C ; 800CC028
