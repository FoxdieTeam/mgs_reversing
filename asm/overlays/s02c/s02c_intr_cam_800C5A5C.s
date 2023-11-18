	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_intr_cam_800C5A5C
s02c_intr_cam_800C5A5C:
	dw 0x03E00008 ; 800C5A5C
	dw 0x00000000 ; 800C5A60
