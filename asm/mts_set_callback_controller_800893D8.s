	opt	c+, at+, e+, n-
	section .text

	xdef mts_set_callback_controller_800893D8
mts_set_callback_controller_800893D8:
	dw 0x3C01800A ; 0x800893D8
	dw 0xAC243D74 ; 0x800893DC
	dw 0x03E00008 ; 0x800893E0
	dw 0x00000000 ; 0x800893E4
