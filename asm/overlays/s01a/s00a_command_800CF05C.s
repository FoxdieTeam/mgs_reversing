	opt	c+, at+, e+, n-
	section overlay.text

	xdef s00a_command_800CF05C
s00a_command_800CF05C:
	dw 0x2402008B ; 800D1BBC
	dw 0x03E00008 ; 800D1BC0
	dw 0xAC820000 ; 800D1BC4
