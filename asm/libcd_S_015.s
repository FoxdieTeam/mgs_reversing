	opt	c+, at+, e+, n-
	section .text

	xdef CdReadyCallback
CdReadyCallback:
	dw 0x3C02800A ; 0x8008C8F0
	dw 0x8C423E6C ; 0x8008C8F4
	dw 0x3C01800A ; 0x8008C8F8
	dw 0x03E00008 ; 0x8008C8FC
	dw 0xAC243E6C ; 0x8008C900
