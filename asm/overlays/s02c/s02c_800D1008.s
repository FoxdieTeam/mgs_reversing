	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_800D1008
s02c_800D1008:
	dw 0x2402008B ; 800D1008
	dw 0x03E00008 ; 800D100C
	dw 0xAC820000 ; 800D1010
