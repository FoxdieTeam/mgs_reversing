	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800CBDE4
ending_800CBDE4:
	dw 0x94820000 ; 800CBDE4
	dw 0x03E00008 ; 800CBDE8
	dw 0x00000000 ; 800CBDEC
