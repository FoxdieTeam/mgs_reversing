	opt	c+, at+, e+, n-
	section .text

	xdef menu_number_kill_80042980
menu_number_kill_80042980:
	dw 0x03E00008 ; 0x80042980
	dw 0x00000000 ; 0x80042984
