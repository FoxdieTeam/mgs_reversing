	opt	c+, at+, e+, n-
	section overlay.text

	xdef d00a_800D09DC
d00a_800D09DC:
	dw 0xA4850000 ; 800D09DC
	dw 0xA4860002 ; 800D09E0
	dw 0x03E00008 ; 800D09E4
	dw 0xA4870004 ; 800D09E8
