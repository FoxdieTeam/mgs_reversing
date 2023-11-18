	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_asiato_800D2DAC
s02c_asiato_800D2DAC:
	dw 0xA4850000 ; 800D2DAC
	dw 0xA4860002 ; 800D2DB0
	dw 0x03E00008 ; 800D2DB4
	dw 0xA4870004 ; 800D2DB8
