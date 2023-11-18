	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_fadeio_800E0180
s02c_fadeio_800E0180:
	dw 0x03E00008 ; 800E0180
	dw 0x00000000 ; 800E0184
