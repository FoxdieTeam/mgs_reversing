	opt	c+, at+, e+, n-, m-

	section .text

luih	macro reg, value
	lui     \reg, ((\value>>16)&0xFFFF)
	endm

adduih	macro reg, value
	addiu   \reg, \reg, (\value&0xFFFF)
	endm
