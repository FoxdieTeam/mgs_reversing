	opt	c+, at+, e+, n-
	section overlay.text

	xdef s19b_800DBEDC
s19b_800DBEDC:
	dw 0x3C03800E ; 800DBEDC
	dw 0x24020002 ; 800DBEE0
	dw 0x03E00008 ; 800DBEE4
	dw 0xAC62E7EC ; 800DBEE8
