	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_command_800D1020
s02c_command_800D1020:
	dw 0x24020086 ; 800D1020
	dw 0x03E00008 ; 800D1024
	dw 0xAC820000 ; 800D1028
