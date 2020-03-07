	opt	c+, at+, e+, n-
	section .text

	xdef GCL_SetStackPointer_800208F0
GCL_SetStackPointer_800208F0:
	dw 0x10800002 ; 0x800208F0
	dw 0x00000000 ; 0x800208F4
	dw 0xAF8406B4 ; 0x800208F8
	dw 0x03E00008 ; 0x800208FC
	dw 0x00000000 ; 0x80020900
