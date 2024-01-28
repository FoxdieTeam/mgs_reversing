	opt	c+, at+, e+, n-
	section overlay.text

	xdef roll_800C5900
roll_800C5900:
	dw 0x3C02800D ; 800C5900
	dw 0x8C429EB8 ; 800C5904
	dw 0x03E00008 ; 800C5908
	dw 0x00000000 ; 800C590C
