	opt	c+, at+, e+, n-
	section .text

	xdef write_800995BC
write_800995BC:
	dw 0x240A00B0 ; 0x800995BC
	dw 0x01400008 ; 0x800995C0
	dw 0x24090035 ; 0x800995C4
	dw 0x00000000 ; 0x800995C8
