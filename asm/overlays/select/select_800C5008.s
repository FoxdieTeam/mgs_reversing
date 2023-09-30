	opt	c+, at+, e+, n-
	section overlay.text

	xdef select_800C5008
select_800C5008:
	dw 0x0000418D ; 800C5008
	dw 0x10400002 ; 800C500C
	dw 0x00601021 ; 800C5010
	dw 0x2402FFFF ; 800C5014
	dw 0x03E00008 ; 800C5018
	dw 0x00000000 ; 800C501C
