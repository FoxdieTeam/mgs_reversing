	opt	c+, at+, e+, n-
	section .text

	xdef gmsight_loader_80063650
gmsight_loader_80063650:
	dw 0x3C03800C ; 0x80063650
	dw 0x24020001 ; 0x80063654
	dw 0xA462DCC0 ; 0x80063658
	dw 0x00001021 ; 0x8006365C
	dw 0x03E00008 ; 0x80063660
	dw 0xAC800020 ; 0x80063664
