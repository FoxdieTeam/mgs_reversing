	opt	c+, at+, e+, n-
	section overlay.text

	xdef s01a_breath_800C4C50
s01a_breath_800C4C50:
	dw 0xAE020028 ; 800C4C50
	dw 0xAE020028 ; 800C4C54
	dw 0x0C0312B4 ; 800C4C58
	dw 0x02002021 ; 800C4C5C
	dw 0x3C04FF00 ; 800C4C60
