	opt	c+, at+, e+, n-
	section overlay.text

	xdef s08b_800CDB10
s08b_800CDB10:
	dw 0x27BDFFE8 ; 800CDB10
	dw 0xAFB00010 ; 800CDB14
	dw 0xAFBF0014 ; 800CDB18
	dw 0x0C033690 ; 800CDB1C
	dw 0x00808021 ; 800CDB20
	dw 0x0C03367C ; 800CDB24
	dw 0x02002021 ; 800CDB28
	dw 0x0C0353B4 ; 800CDB2C
	dw 0x02002021 ; 800CDB30
	dw 0x0C033400 ; 800CDB34
	dw 0x02002021 ; 800CDB38
	dw 0x0C033664 ; 800CDB3C
	dw 0x02002021 ; 800CDB40
	dw 0x8FBF0014 ; 800CDB44
	dw 0x8FB00010 ; 800CDB48
	dw 0x03E00008 ; 800CDB4C
	dw 0x27BD0018 ; 800CDB50
