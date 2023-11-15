	opt	c+, at+, e+, n-
	section overlay.text

	xdef CommandDie_800D02EC
CommandDie_800D02EC:
	dw 0x03E00008 ; 800D2E4C
	dw 0x00000000 ; 800D2E50
