	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_800E0DB0
s02c_800E0DB0:
	dw 0xAC800028 ; 800E0DB0
	dw 0x03E00008 ; 800E0DB4
	dw 0x00001021 ; 800E0DB8
