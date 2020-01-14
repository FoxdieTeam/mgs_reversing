	opt	c+, at+, e+, n-
	section .text

	xdef SD_80086F00
SD_80086F00:
	dw 0x3C03800C ; 0x80086F00
	dw 0x8C63057C ; 0x80086F04
