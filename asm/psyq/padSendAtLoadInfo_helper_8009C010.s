	opt	c+, at+, e+, n-
	section .text

	xdef padSendAtLoadInfo_helper_8009C010
padSendAtLoadInfo_helper_8009C010:
	dw 0x24020045 ; 0x8009C010
	dw 0xA0820037 ; 0x8009C014
	dw 0xAC80002C ; 0x8009C018
	dw 0x03E00008 ; 0x8009C01C
	dw 0xA0800036 ; 0x8009C020
