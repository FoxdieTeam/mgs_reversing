	opt	c+, at+, e+, n-
	section .text

	xdef snake_vr_sna_init_80052AC0
snake_vr_sna_init_80052AC0:
	dw 0x03E00008 ; 80052AC0
	dw 0x00000000 ; 80052AC4
