	opt	c+, at+, e+, n-
	section overlay.text

	xdef s19b_800DBECC
s19b_800DBECC:
	dw 0x3C03800E ; 800DBECC
	dw 0x24020001 ; 800DBED0
	dw 0x03E00008 ; 800DBED4
	dw 0xAC62E7EC ; 800DBED8
