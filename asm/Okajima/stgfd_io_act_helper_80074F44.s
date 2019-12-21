	opt	c+, at+, e+, n-
	section .text

	xdef stgfd_io_act_helper_80074F44
stgfd_io_act_helper_80074F44:
	dw 0x8FA20010 ; 0x80074F44
	dw 0xAC850024 ; 0x80074F48
	dw 0xA4860034 ; 0x80074F4C
	dw 0xA4870036 ; 0x80074F50
	dw 0x03E00008 ; 0x80074F54
	dw 0xA4820038 ; 0x80074F58
