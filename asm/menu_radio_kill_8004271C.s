	opt	c+, at+, e+, n-
	section .text

	xdef menu_radio_kill_8004271C
menu_radio_kill_8004271C:
	dw 0x90820028 ; 0x8004271C
	dw 0x00000000 ; 0x80042720
	dw 0x304200EF ; 0x80042724
	dw 0x03E00008 ; 0x80042728
	dw 0xA0820028 ; 0x8004272C
