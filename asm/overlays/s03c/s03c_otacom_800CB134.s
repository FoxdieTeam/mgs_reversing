	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03c_otacom_800CB134
s03c_otacom_800CB134:
	dw 0x3C02800C ; 800CB134
	dw 0xAC4433D0 ; 800CB138
	dw 0x3C02800C ; 800CB13C
	dw 0x03E00008 ; 800CB140
	dw 0xAC4533D4 ; 800CB144
