	opt	c+, at+, e+, n-
	section .text

	xdef vrsave_800CB6E0
vrsave_800CB6E0:
	dw 0x3C02800B ; 800CB6E0
	dw 0x9442E240 ; 800CB6E4
	dw 0x03E00008 ; 800CB6E8
	dw 0x3042F0F0 ; 800CB6EC
