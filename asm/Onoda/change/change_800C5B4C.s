	opt	c+, at+, e+, n-
	section .text

	xdef change_800C5B4C
change_800C5B4C:
	dw 0x240A00B0 ; 800C5B4C
	dw 0x01400008 ; 800C5B50
	dw 0x24090038 ; 800C5B54
