	opt	c+, at+, e+, n-
	section .text

	xdef CdSyncCallback
CdSyncCallback:
	dw 0x3C02800A ; 0x8008C8DC
	dw 0x8C423E68 ; 0x8008C8E0
	dw 0x3C01800A ; 0x8008C8E4
	dw 0x03E00008 ; 0x8008C8E8
	dw 0xAC243E68 ; 0x8008C8EC
