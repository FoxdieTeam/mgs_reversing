	opt	c+, at+, e+, n-
	section overlay.text

	xdef s11e_800CC7FC
s11e_800CC7FC:
	dw 0x03E00008 ; 800CC7FC
	dw 0x00001021 ; 800CC800
	dw 0x03E00008 ; 800CC804
	dw 0x24020001 ; 800CC808
