	opt	c+, at+, e+, n-
	section overlay.text

	xdef s11i_asiato_800CC2FC
s11i_asiato_800CC2FC:
	dw 0xA600006C ; 800CC2FC
	dw 0x8FBF0018 ; 800CC300
	dw 0x8FB10014 ; 800CC304
	dw 0x8FB00010 ; 800CC308
	dw 0x03E00008 ; 800CC30C
	dw 0x27BD0020 ; 800CC310
