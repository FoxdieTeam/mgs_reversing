	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_fadeio_800E0188
s02c_fadeio_800E0188:
	dw 0x03E00008 ; 800E0188
	dw 0x00001021 ; 800E018C
