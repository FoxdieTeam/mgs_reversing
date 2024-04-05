	opt	c+, at+, e+, n-
	section overlay.text

	xdef s19b_800DBEEC
s19b_800DBEEC:
	dw 0x3C02800E ; 800DBEEC
	dw 0x03E00008 ; 800DBEF0
	dw 0xAC44E7C8 ; 800DBEF4
