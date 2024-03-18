	opt	c+, at+, e+, n-
	section overlay.text

	xdef s13a_800DC400
s13a_800DC400:
	dw 0x03E00008 ; 800DC400
	dw 0x00001021 ; 800DC404
