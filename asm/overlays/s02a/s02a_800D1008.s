	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02a_800D1008
s02a_800D1008:
	dw 0x24020087 ; 800D1008
	dw 0x03E00008 ; 800D100C
	dw 0xAC820000 ; 800D1010
