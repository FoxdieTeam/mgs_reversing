	opt	c+, at+, e+, n-
	section .text

	xdef FS_StreamIsForceStop_800243C8
FS_StreamIsForceStop_800243C8:
	dw 0x3C02800A ; 0x800243C8
	dw 0x8C42D518 ; 0x800243CC
	dw 0x03E00008 ; 0x800243D0
	dw 0x00000000 ; 0x800243D4
