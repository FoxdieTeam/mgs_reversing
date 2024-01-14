	opt	c+, at+, e+, n-
	section overlay.text

	xdef opening_800CC0C8
opening_800CC0C8:
	dw 0xAC800028 ; 800CC0C8
	dw 0x03E00008 ; 800CC0CC
	dw 0x00001021 ; 800CC0D0
