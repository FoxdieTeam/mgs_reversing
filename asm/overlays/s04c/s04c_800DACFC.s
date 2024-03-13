	opt	c+, at+, e+, n-
	section overlay.text

	xdef s04c_800DACFC
s04c_800DACFC:
	dw 0x8FBF0018 ; 800DACFC
	dw 0x27BD0020 ; 800DAD00
	dw 0x03E00008 ; 800DAD04
	dw 0x00000000 ; 800DAD08
