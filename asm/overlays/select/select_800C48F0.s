	opt	c+, at+, e+, n-
	section overlay.text

	xdef select_800C48F0
select_800C48F0:
	dw 0x27BDFFE8 ; 800C48F0
	dw 0x308400FF ; 800C48F4
	dw 0xAFBF0010 ; 800C48F8
	dw 0x0C03122B ; 800C48FC
	dw 0x00002821 ; 800C4900
	dw 0x8FBF0010 ; 800C4904
	dw 0x3042FFFF ; 800C4908
	dw 0x03E00008 ; 800C490C
	dw 0x27BD0018 ; 800C4910
