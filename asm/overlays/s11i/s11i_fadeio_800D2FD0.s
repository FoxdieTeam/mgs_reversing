	opt	c+, at+, e+, n-
	section overlay.text

	xdef s11i_fadeio_800D2FD0
s11i_fadeio_800D2FD0:
	dw 0x27BDFFE0 ; 800D2FD0
	dw 0xAFB00010 ; 800D2FD4
	dw 0x00808021 ; 800D2FD8
	dw 0xAFB10014 ; 800D2FDC
	dw 0x00A08821 ; 800D2FE0
	dw 0x3C04800A ; 800D2FE4
	dw 0xAFBF0018 ; 800D2FE8
	dw 0x0C006F11 ; 800D2FEC
	dw 0x2484D430 ; 800D2FF0
	dw 0x02002021 ; 800D2FF4
	dw 0x0C034BEC ; 800D2FF8
	dw 0x02202821 ; 800D2FFC
	dw 0x8FBF0018 ; 800D3000
	dw 0x8FB10014 ; 800D3004
	dw 0x8FB00010 ; 800D3008
	dw 0x03E00008 ; 800D300C
	dw 0x27BD0020 ; 800D3010