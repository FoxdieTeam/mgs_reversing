	opt	c+, at+, e+, n-
	section .text

	xdef gglsight_kill_800783F8
gglsight_kill_800783F8:
	dw 0x3C02800A ; 0x800783F8
	dw 0x03E00008 ; 0x800783FC
	dw 0xA440F714 ; 0x80078400
