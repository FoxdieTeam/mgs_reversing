	opt	c+, at+, e+, n-
	section .text

	xdef lseek_8009959C
lseek_8009959C:
	dw 0x240A00B0 ; 0x8009959C
	dw 0x01400008 ; 0x800995A0
	dw 0x24090033 ; 0x800995A4
	dw 0x00000000 ; 0x800995A8
