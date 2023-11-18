	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_command_800D0FFC
s02c_command_800D0FFC:
	dw 0x24020087 ; 800D0FFC
	dw 0x03E00008 ; 800D1000
	dw 0xAC820000 ; 800D1004
