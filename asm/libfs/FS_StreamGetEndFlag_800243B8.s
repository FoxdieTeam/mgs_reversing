	opt	c+, at+, e+, n-
	section .text

	xdef FS_StreamGetEndFlag_800243B8
FS_StreamGetEndFlag_800243B8:
	dw 0x3C02800A ; 0x800243B8
	dw 0x8C42D51C ; 0x800243BC
	dw 0x03E00008 ; 0x800243C0
	dw 0x00000000 ; 0x800243C4
