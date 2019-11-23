	opt	c+, at+, e+, n-
	section .text

	xdef DG_ChangeReso_80017154
DG_ChangeReso_80017154:
	dw 0x03E00008 ; 0x80017154
	dw 0x00000000 ; 0x80017158
