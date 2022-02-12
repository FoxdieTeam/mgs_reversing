	opt	c+, at+, e+, n-
	section .text

	xdef card_write_8009906C
card_write_8009906C:
	dw 0x240A00B0 ; 0x8009906C
	dw 0x01400008 ; 0x80099070
	dw 0x2409004E ; 0x80099074
	dw 0x00000000 ; 0x80099078
