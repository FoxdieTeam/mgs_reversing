	opt	c+, at+, e+, n-
	section .text

	xdef font_get_buffer_ptr_80044FE8
font_get_buffer_ptr_80044FE8:
	dw 0x8C820028 ; 0x80044FE8
	dw 0x03E00008 ; 0x80044FEC
	dw 0x00000000 ; 0x80044FF0
