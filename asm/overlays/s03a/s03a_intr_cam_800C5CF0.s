	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03a_intr_cam_800C5CF0
s03a_intr_cam_800C5CF0:
	dw 0x03E00008 ; 800C5CF0
	dw 0x00000000 ; 800C5CF4
