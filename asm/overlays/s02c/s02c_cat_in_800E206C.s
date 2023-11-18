	opt	c+, at+, e+, n-
	section overlay.text

	xdef s02c_cat_in_800E206C
s02c_cat_in_800E206C:
	dw 0x8C83003C ; 800E206C
	dw 0x24020001 ; 800E2070
	dw 0x03E00008 ; 800E2074
	dw 0xAC620000 ; 800E2078
