	opt	c+, at+, e+, n-
	section .text

	xdef SD_80087A80
SD_80087A80:
	dw 0x03E00008 ; 0x80087A80
	dw 0x00000000 ; 0x80087A84
