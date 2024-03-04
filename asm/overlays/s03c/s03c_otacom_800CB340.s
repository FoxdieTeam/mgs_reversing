	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03c_otacom_800CB340
s03c_otacom_800CB340:
	dw 0x3C02800C ; 800CB340
	dw 0x904233C5 ; 800CB344
	dw 0x03E00008 ; 800CB348
	dw 0x00000000 ; 800CB34C
