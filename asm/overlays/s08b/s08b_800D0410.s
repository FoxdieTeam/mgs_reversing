	opt	c+, at+, e+, n-
	section overlay.text

	xdef s08b_800D0410
s08b_800D0410:
	dw 0x3C02800B ; 800D0410
	dw 0x8C42B3CC ; 800D0414
	dw 0x00000000 ; 800D0418
	dw 0x30420001 ; 800D041C
	dw 0x10400008 ; 800D0420
	dw 0x00802821 ; 800D0424
	dw 0x00001021 ; 800D0428
	dw 0x8CA319D0 ; 800D042C
	dw 0x2404001B ; 800D0430
	dw 0xACA419B0 ; 800D0434
	dw 0x24630001 ; 800D0438
	dw 0x03E00008 ; 800D043C
	dw 0xACA319D0 ; 800D0440
	dw 0x03E00008 ; 800D0444
	dw 0x24020001 ; 800D0448
