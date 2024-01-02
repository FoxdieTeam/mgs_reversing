	opt	c+, at+, e+, n-
	section overlay.text

	xdef s15c_800E1210
s15c_800E1210:
	dw 0xAC800028 ; 800E1210
	dw 0x03E00008 ; 800E1214
	dw 0x00001021 ; 800E1218
