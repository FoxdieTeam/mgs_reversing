	opt	c+, at+, e+, n-
	section overlay.text

	xdef s00a_command_800CF050
s00a_command_800CF050:
	dw 0x24020087 ; 800D1BB0
	dw 0x03E00008 ; 800D1BB4
	dw 0xAC820000 ; 800D1BB8
