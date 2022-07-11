	opt	c+, at+, e+, n-
	section .text

	xdef GM_StartDaemon_helper_8002A960
GM_StartDaemon_helper_8002A960:
	dw 0x3C02800B ; 0x8002A960
	dw 0x24424D98 ; 0x8002A964
	dw 0x2403FFFF ; 0x8002A968
	dw 0xA443001C ; 0x8002A96C
	dw 0x03E00008 ; 0x8002A970
	dw 0xA443001E ; 0x8002A974
