	opt	c+, at+, e+, n-
	section .text

	xdef card_read_8009901C
card_read_8009901C:
	dw 0x240A00B0 ; 0x8009901C
	dw 0x01400008 ; 0x80099020
	dw 0x2409004F ; 0x80099024
	dw 0x00000000 ; 0x80099028
