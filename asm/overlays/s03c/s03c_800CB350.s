	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03c_800CB350
s03c_800CB350:
	dw 0x3C02800C ; 800CB350
	dw 0x8C4233C8 ; 800CB354
	dw 0x03E00008 ; 800CB358
	dw 0x0002102A ; 800CB35C
