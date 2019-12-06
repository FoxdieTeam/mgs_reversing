	opt	c+, at+, e+, n-
	section .text

	xdef sgtrect3_kill_80070EC0
sgtrect3_kill_80070EC0:
	dw 0x3C02800A ; 0x80070EC0
	dw 0x03E00008 ; 0x80070EC4
	dw 0xA040F5F8 ; 0x80070EC8
