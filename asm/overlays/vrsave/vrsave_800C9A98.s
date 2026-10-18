	opt	c+, at+, e+, n-
	section .text

	xdef vrsave_800C9A98
vrsave_800C9A98:
	dw 0x8C820004 ; 800C9A98
	dw 0x03E00008 ; 800C9A9C
	dw 0x00000000 ; 800C9AA0
