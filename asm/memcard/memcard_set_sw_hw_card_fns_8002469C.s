	opt	c+, at+, e+, n-
	section .text

	xdef memcard_set_sw_hw_card_fns_8002469C
memcard_set_sw_hw_card_fns_8002469C:
	dw 0x3C03800B ; 0x8002469C
	dw 0x3C028002 ; 0x800246A0
	dw 0x244244DC ; 0x800246A4
	dw 0xAC6252E8 ; 0x800246A8
	dw 0x3C03800B ; 0x800246AC
	dw 0x3C028002 ; 0x800246B0
	dw 0x244244EC ; 0x800246B4
	dw 0x03E00008 ; 0x800246B8
	dw 0xAC6252EC ; 0x800246BC
