	opt	c+, at+, e+, n-
	section .text

	xdef change_800C5988
change_800C5988:
	dw 0x3C03800A ; 800C5988
	dw 0x24020002 ; 800C598C
	dw 0x03E00008 ; 800C5990
	dw 0xAC62D45C ; 800C5994
