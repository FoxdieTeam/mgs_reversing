	opt	c+, at+, e+, n-
	section overlay.text

	xdef s11i_fadeio_800D30FC
s11i_fadeio_800D30FC:
	dw 0x03E00008 ; 800D30FC
	dw 0x00000000 ; 800D3100
