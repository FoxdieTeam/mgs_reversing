	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02a_800DC10C
s02a_800DC10C:
	dw 0x3C02800E ; 800DC10C
	dw 0x8C423700 ; 800DC110
	dw 0x03E00008 ; 800DC114
	dw 0x00000000 ; 800DC118
