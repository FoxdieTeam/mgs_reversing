	opt	c+, at+, e+, n-
	section .text

	xdef vrsave_800C9B80
vrsave_800C9B80:
	dw 0x8C820028 ; 800C9B80
	dw 0x03E00008 ; 800C9B84
	dw 0x00000000 ; 800C9B88
