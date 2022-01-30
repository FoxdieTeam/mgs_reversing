	opt	c+, at+, e+, n-
	section .text

	xdef bu_init_80098FEC
bu_init_80098FEC:
	dw 0x240A00A0 ; 0x80098FEC
	dw 0x01400008 ; 0x80098FF0
	dw 0x24090070 ; 0x80098FF4
	dw 0x00000000 ; 0x80098FF8
