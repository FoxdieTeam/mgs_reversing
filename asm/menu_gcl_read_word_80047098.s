	opt	c+, at+, e+, n-
	section .text

	xdef menu_gcl_read_word_80047098
menu_gcl_read_word_80047098:
	dw 0x90A20000 ; 0x80047098
	dw 0x90A30001 ; 0x8004709C
	dw 0x00021200 ; 0x800470A0
	dw 0x00621825 ; 0x800470A4
	dw 0x24A20002 ; 0x800470A8
	dw 0x03E00008 ; 0x800470AC
	dw 0xAC830000 ; 0x800470B0
