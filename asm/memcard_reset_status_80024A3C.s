	opt	c+, at+, e+, n-
	section .text

	xdef memcard_reset_status_80024A3C
memcard_reset_status_80024A3C:
	dw 0x3C02800B ; 0x80024A3C
	dw 0x244252F8 ; 0x80024A40
	dw 0x24030002 ; 0x80024A44
	dw 0xA0430001 ; 0x80024A48
	dw 0x03E00008 ; 0x80024A4C
	dw 0xA04301A9 ; 0x80024A50
