	opt	c+, at+, e+, n-
	section overlay.text

	xdef s16c_command_800CEA40
s16c_command_800CEA40:
	dw 0x2402008A ; 800CEA40
	dw 0x03E00008 ; 800CEA44
	dw 0xAC820000 ; 800CEA48
