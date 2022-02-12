
	opt	c+, at+, e+, n-
	section .text

	xdef mts_get_task_res1_8008B630
mts_get_task_res1_8008B630:
	dw 0x00042140 ; 0x8008B630
	dw 0x3C01800C ; 0x8008B634
	dw 0x00240821 ; 0x8008B638
	dw 0x80220C3F ; 0x8008B63C
	dw 0x03E00008 ; 0x8008B640
	dw 0x00000000 ; 0x8008B644
