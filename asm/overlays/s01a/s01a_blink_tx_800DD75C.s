	opt	c+, at+, e+, n-
	section overlay.text

	xdef s01a_blink_tx_800DD75C
s01a_blink_tx_800DD75C:
	dw 0x03E00008 ; 800DD75C
	dw 0x00000000 ; 800DD760
