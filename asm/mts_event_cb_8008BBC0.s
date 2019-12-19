	opt	c+, at+, e+, n-
	section .text

	xdef mts_event_cb_8008BBC0
mts_event_cb_8008BBC0:
	dw 0x08022EF0 ; 0x8008BBC0
	dw 0x00000000 ; 0x8008BBC4
