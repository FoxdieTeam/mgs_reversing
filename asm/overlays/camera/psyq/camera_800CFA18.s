	opt	c+, at+, e+, n-
	section camera.text

	xdef camera_800CFA18
camera_800CFA18:
	dw 0x3C02800C ; 800CFA18
	dw 0x8C423A70 ; 800CFA1C
	dw 0x00000000 ; 800CFA20
	dw 0x8C420000 ; 800CFA24
	dw 0x03E00008 ; 800CFA28
	dw 0x00000000 ; 800CFA2C
