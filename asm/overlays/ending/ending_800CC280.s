	opt	c+, at+, e+, n-
	section overlay.text

	xdef ending_800CC280
ending_800CC280:
	dw 0x3C02800C ; 800CC280
	dw 0x8C423638 ; 800CC284
	dw 0x00000000 ; 800CC288
	dw 0x8C420000 ; 800CC28C
	dw 0x03E00008 ; 800CC290
	dw 0x00000000 ; 800CC294
