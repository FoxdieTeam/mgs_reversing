	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03e_intr_cam_800C56F0
s03e_intr_cam_800C56F0:
	dw 0x03E00008 ; 800C56F0
	dw 0x00000000 ; 800C56F4
