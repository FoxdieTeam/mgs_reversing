	opt	c+, at+, e+, n-
	section overlay.text

	xdef s06a_800DCD08
s06a_800DCD08:
	dw 0x27BDFFE8 ; 800DCD08
	dw 0x308400FF ; 800DCD0C
	dw 0xAFBF0010 ; 800DCD10
	dw 0x0C037332 ; 800DCD14
	dw 0x00002821 ; 800DCD18
	dw 0x8FBF0010 ; 800DCD1C
	dw 0x00000000 ; 800DCD20
	dw 0x03E00008 ; 800DCD24
	dw 0x27BD0018 ; 800DCD28
