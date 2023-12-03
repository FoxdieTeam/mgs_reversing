	opt	c+, at+, e+, n-
	section overlay.text

	xdef s08c_800CFB64
s08c_800CFB64:
	dw 0xAC800028 ; 800CFB64
	dw 0x03E00008 ; 800CFB68
	dw 0x00001021 ; 800CFB6C
