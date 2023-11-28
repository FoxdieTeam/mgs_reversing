	opt	c+, at+, e+, n-
	section overlay.text

	xdef s03a_red_alrt_800CE44C
s03a_red_alrt_800CE44C:
	dw 0x3C02800C ; 800CE44C
	dw 0xAC50356C ; 800CE450
	dw 0x8FB00028 ; 800CE454
	dw 0x03E00008 ; 800CE458
	dw 0x27BD0030 ; 800CE45C
