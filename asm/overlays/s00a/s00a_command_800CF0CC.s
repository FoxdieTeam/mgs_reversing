	opt	c+, at+, e+, n-
	section overlay.text

	xdef s00a_command_800CF0CC
s00a_command_800CF0CC:
	dw 0x24020085 ; 800CF0CC
	dw 0x03E00008 ; 800CF0D0
	dw 0xAC820000 ; 800CF0D4
