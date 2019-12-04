	opt	c+, at+, e+, n-
	section .text

	xdef SysDeqIntRP_8009A0EC
SysDeqIntRP_8009A0EC:
	dw 0x240A00C0 ; 0x8009A0EC
	dw 0x01400008 ; 0x8009A0F0
	dw 0x24090003 ; 0x8009A0F4
	dw 0x00000000 ; 0x8009A0F8
