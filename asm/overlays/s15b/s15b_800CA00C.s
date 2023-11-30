	opt	c+, at+, e+, n-
	section overlay.text

	xdef s15b_800CA00C
s15b_800CA00C:
	dw 0x3C02800D ; 800CA00C
	dw 0x8C42C8E0 ; 800CA010
	dw 0x03E00008 ; 800CA014
	dw 0x00000000 ; 800CA018
