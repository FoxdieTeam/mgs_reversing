	opt	c+, at+, e+, n-
	section .text

	xdef sub_80072074
sub_80072074:
	dw 0x3C02800A ; 0x80072074
	dw 0x03E00008 ; 0x80072078
	dw 0xA440F5FC ; 0x8007207C
