	opt	c+, at+, e+, n-
	section .text

	xdef rfsight_kill_80069850
rfsight_kill_80069850:
	dw 0xA78008FC ; 0x80069850
	dw 0x03E00008 ; 0x80069854
	dw 0xAC800024 ; 0x80069858
