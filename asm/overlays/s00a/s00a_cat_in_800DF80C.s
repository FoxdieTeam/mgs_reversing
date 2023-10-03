	opt	c+, at+, e+, n-
	section overlay.text

	xdef s00a_cat_in_800DF80C
s00a_cat_in_800DF80C:
	dw 0x8C83003C ; 800DF80C
	dw 0x24020001 ; 800DF810
	dw 0x03E00008 ; 800DF814
	dw 0xAC620000 ; 800DF818
