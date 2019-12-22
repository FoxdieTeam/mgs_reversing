	opt	c+, at+, e+, n-
	section .text

	xdef menu_radio_init_nullsub_80042190
menu_radio_init_nullsub_80042190:
	dw 0x03E00008 ; 0x80042190
	dw 0x00000000 ; 0x80042194
