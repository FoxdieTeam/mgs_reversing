	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_800D1014
s02c_800D1014:
	dw 0x2402008A ; 800D1014
	dw 0x03E00008 ; 800D1018
	dw 0xAC820000 ; 800D101C
