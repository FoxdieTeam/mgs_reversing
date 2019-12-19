	opt	c+, at+, e+, n-
	section .text

	xdef EnterCriticalSection_8009952C
EnterCriticalSection_8009952C:
	dw 0x24040001 ; 0x8009952C
	dw 0x0000000C ; 0x80099530
	dw 0x03E00008 ; 0x80099534
	dw 0x00000000 ; 0x80099538
