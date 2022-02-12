	opt	c+, at+, e+, n-
	section .text

	xdef InitHeap_800993DC
InitHeap_800993DC:
	dw 0x240A00A0 ; 0x800993DC
	dw 0x01400008 ; 0x800993E0
	dw 0x24090039 ; 0x800993E4
	dw 0x00000000 ; 0x800993E8
