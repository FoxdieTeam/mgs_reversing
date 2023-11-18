	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_command_800CD5BC
s02c_command_800CD5BC:
	dw 0x24020002 ; 800CD5BC
	dw 0xA4820B22 ; 800CD5C0
	dw 0x24020005 ; 800CD5C4
	dw 0xA4820B24 ; 800CD5C8
	dw 0x03E00008 ; 800CD5CC
	dw 0xAC800B28 ; 800CD5D0
