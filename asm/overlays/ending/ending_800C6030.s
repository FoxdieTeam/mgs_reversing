	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800C6030
ending_800C6030:
	dw 0xA4850000 ; 800C6030
	dw 0xA4860002 ; 800C6034
	dw 0x03E00008 ; 800C6038
	dw 0xA4870004 ; 800C603C
