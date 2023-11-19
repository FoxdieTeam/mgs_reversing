	opt	c+, at+, e+, n-
	section overlay.text

	xdef s16c_800DBB44
s16c_800DBB44:
	dw 0xAC800028 ; 800DBB44
	dw 0x03E00008 ; 800DBB48
	dw 0x00001021 ; 800DBB4C
