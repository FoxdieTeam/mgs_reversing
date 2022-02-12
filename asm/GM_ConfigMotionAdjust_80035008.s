	opt	c+, at+, e+, n-
	section .text

	xdef GM_ConfigMotionAdjust_80035008
GM_ConfigMotionAdjust_80035008:
	dw 0x8C820000 ; 0x80035008
	dw 0x00000000 ; 0x8003500C
	dw 0xAC45003C ; 0x80035010
	dw 0x03E00008 ; 0x80035014
	dw 0x00001021 ; 0x80035018
