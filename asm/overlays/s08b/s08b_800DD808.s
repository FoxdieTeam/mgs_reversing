	opt	c+, at+, e+, n-
	section overlay.text

	xdef s08b_800DD808
s08b_800DD808:
	dw 0x3C02800E ; 800DD808
	dw 0x8C4243A0 ; 800DD80C
	dw 0x03E00008 ; 800DD810
	dw 0x00000000 ; 800DD814
