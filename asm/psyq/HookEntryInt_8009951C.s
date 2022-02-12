	opt	c+, at+, e+, n-
	section .text

	xdef HookEntryInt_8009951C
HookEntryInt_8009951C:
	dw 0x240A00B0 ; 0x8009951C
	dw 0x01400008 ; 0x80099520
	dw 0x24090019 ; 0x80099524
	dw 0x00000000 ; 0x80099528
