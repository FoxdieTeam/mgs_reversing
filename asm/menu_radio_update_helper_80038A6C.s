	opt	c+, at+, e+, n-
	section .text

	xdef menu_radio_update_helper_80038A6C
menu_radio_update_helper_80038A6C:
	dw 0x3C03800C ; 0x80038A6C
	dw 0x24020001 ; 0x80038A70
	dw 0x03E00008 ; 0x80038A74
	dw 0xA062D538 ; 0x80038A78
