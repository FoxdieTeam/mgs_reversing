	opt	c+, at+, e+, n-
	section overlay.text

	xdef opening_optxtscn_800CCDCC
opening_optxtscn_800CCDCC:
	dw 0x308200FF ; 800CCDCC
	dw 0x2C42001C ; 800CCDD0
	dw 0x14400002 ; 800CCDD4
	dw 0x00000000 ; 800CCDD8
	dw 0x00002021 ; 800CCDDC
	dw 0x03E00008 ; 800CCDE0
	dw 0x308200FF ; 800CCDE4
