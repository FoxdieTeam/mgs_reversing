	opt	c+, at+, e+, n-
	section .text

	xdef font_set_font_addr_80044BC0
font_set_font_addr_80044BC0:
	dw 0x3C02800A ; 0x80044BC0
	dw 0x2442E75C ; 0x80044BC4
	dw 0x00042080 ; 0x80044BC8
	dw 0x00822021 ; 0x80044BCC
	dw 0x03E00008 ; 0x80044BD0
	dw 0xAC850000 ; 0x80044BD4
