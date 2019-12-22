	opt	c+, at+, e+, n-
	section .text

	xdef gmsight_kill_80063644
gmsight_kill_80063644:
	dw 0x3C02800C ; 0x80063644
	dw 0x03E00008 ; 0x80063648
	dw 0xA440DCC0 ; 0x8006364C
