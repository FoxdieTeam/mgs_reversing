	opt	c+, at+, e+, n-
	section .text

	xdef padChkVsync_8009AA08
padChkVsync_8009AA08:
	dw 0x3C02800B ; 0x8009AA08
	dw 0x8C42B294 ; 0x8009AA0C
	dw 0x3C01800B ; 0x8009AA10
	dw 0x03E00008 ; 0x8009AA14
	dw 0xAC20B294 ; 0x8009AA18
