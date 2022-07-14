	opt	c+, at+, e+, n-
	section .text

	xdef FS_StreamGetSize_80024188
FS_StreamGetSize_80024188:
	dw 0x8C82FFFC ; 0x80024188
	dw 0x03E00008 ; 0x8002418C
	dw 0x00021203 ; 0x80024190
