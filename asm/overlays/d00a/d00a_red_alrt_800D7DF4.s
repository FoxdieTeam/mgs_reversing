	opt	c+, at+, e+, n-
	section overlay.text

	xdef d00a_red_alrt_800D7DF4
d00a_red_alrt_800D7DF4:
	dw 0x3C02800C ; 800D7DF4
	dw 0xAC503634 ; 800D7DF8
	dw 0x8FB00028 ; 800D7DFC
	dw 0x03E00008 ; 800D7E00
	dw 0x27BD0030 ; 800D7E04
