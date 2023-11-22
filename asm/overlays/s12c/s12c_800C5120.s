	opt	c+, at+, e+, n-
	section overlay.text

	xdef s12c_800C5120
s12c_800C5120:
	dw 0xA4850000 ; 800C5120
	dw 0xA4860002 ; 800C5124
	dw 0x03E00008 ; 800C5128
	dw 0xA4870004 ; 800C512C
