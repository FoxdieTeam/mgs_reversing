	opt	c+, at+, e+, n-
	section .text

	xdef menu_viewer_kill_80044A90
menu_viewer_kill_80044A90:
	dw 0xA380083C ; 0x80044A90
	dw 0x03E00008 ; 0x80044A94
	dw 0x00000000 ; 0x80044A98
