	opt	c+, at+, e+, n-
	section .text

	xdef GM_ConfigControlHazard_8002622C
GM_ConfigControlHazard_8002622C:
	dw 0xA4850032 ; 0x8002622C
	dw 0xA4860036 ; 0x80026230
	dw 0x03E00008 ; 0x80026234
	dw 0xA4870038 ; 0x80026238
