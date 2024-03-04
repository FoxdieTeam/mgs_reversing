	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03c_otacom_800CB320
s03c_otacom_800CB320:
	dw 0x3C02800C ; 800CB320
	dw 0x8C4233BC ; 800CB324
	dw 0x03E00008 ; 800CB328
	dw 0x00000000 ; 800CB32C
