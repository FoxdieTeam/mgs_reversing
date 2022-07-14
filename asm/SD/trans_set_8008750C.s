	opt	c+, at+, e+, n-
	section .text

	xdef trans_set_8008750C
trans_set_8008750C:
	dw 0x3C03800C ; 0x8008750C
	dw 0x8C63057C ; 0x80087510
	dw 0x3C02800C ; 0x80087514
	dw 0x8042F0D4 ; 0x80087518
	dw 0x03E00008 ; 0x8008751C
	dw 0xAC6200A8 ; 0x80087520
