	opt	c+, at+, e+, n-
	section overlay.text

	xdef EnemyResetThink_800CB224
EnemyResetThink_800CB224:
	dw 0xA4800B20 ; 800CDD84
	dw 0xA4800B22 ; 800CDD88
	dw 0xA4800B24 ; 800CDD8C
	dw 0xAC800B28 ; 800CDD90
	dw 0xA4800B4C ; 800CDD94
	dw 0x03E00008 ; 800CDD98
	dw 0xAC800B3C ; 800CDD9C
