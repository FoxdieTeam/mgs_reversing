	opt	c+, at+, e+, n-
	section overlay.text

	xdef s11g_800CFD50
s11g_800CFD50:
	dw 0xAC800028 ; 800CFD50
	dw 0x03E00008 ; 800CFD54
	dw 0x00001021 ; 800CFD58
