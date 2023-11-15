	opt	c+, at+, e+, n-
	section overlay.text

	xdef s00a_command_800CB610
s00a_command_800CB610:
	dw 0x24020002 ; 800CE170
	dw 0xA4820B22 ; 800CE174
	dw 0x24020005 ; 800CE178
	dw 0xA4820B24 ; 800CE17C
	dw 0x03E00008 ; 800CE180
	dw 0xAC800B28 ; 800CE184
