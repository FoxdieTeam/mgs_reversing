	opt	c+, at+, e+, n-
	section overlay.text

	xdef d00a_800CEC50
d00a_800CEC50:
	dw 0x24020086 ; 800CEC50
	dw 0x03E00008 ; 800CEC54
	dw 0xAC820000 ; 800CEC58
