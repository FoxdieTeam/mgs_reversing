	opt	c+, at+, e+, n-
	section overlay.text

	xdef s15c_800E15AC
s15c_800E15AC:
	dw 0x8C83003C ; 800E15AC
	dw 0x24020001 ; 800E15B0
	dw 0x03E00008 ; 800E15B4
	dw 0xAC620000 ; 800E15B8
