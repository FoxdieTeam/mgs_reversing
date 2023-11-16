	opt	c+, at+, e+, n-
	section overlay.text

	xdef d01a_command_800C7CC0
d01a_command_800C7CC0:
	dw 0x2402008A ; 800C7CC0
	dw 0x03E00008 ; 800C7CC4
	dw 0xAC820000 ; 800C7CC8
