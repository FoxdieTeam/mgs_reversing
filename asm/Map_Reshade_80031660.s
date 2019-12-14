	opt	c+, at+, e+, n-, m-
	section .text

	INCLUDE utils.s

	xref aReshadeNullMap
	xref mg_printf_8008BBA0
	xref Map_FromId_800314C0
	xref sub_80031F04

	xdef Map_Reshade_80031660
Map_Reshade_80031660:
	addiu   sp, sp, -0x20
	sw      s1, 0x14(sp)
	addu    s1, a0, zero
	sw      ra, 0x18(sp)
	sw      s0, 0x10(sp)
	lhu     a0, 0x2C(s1)
	jal     Map_FromId_800314C0
	nop
	addu    s0, v0, zero
	bne     s0, zero, loc_80031694
	luih     a0, aReshadeNullMap
	jal     mg_printf_8008BBA0
	adduih   a0, aReshadeNullMap

	loc_80031694:
	lw      v0, 0xC(s0)
	nop
	beq     v0, zero, loc_800316B0
	addu    a0, s1, zero

	lw      a2, 0(v0)
	jal     sub_80031F04
	addiu   a1, v0, 4

	loc_800316B0:
	lw      ra, 0x18(sp)
	lw      s1, 0x14(sp)
	lw      s0, 0x10(sp)
	jr      ra
	addiu   sp, sp, 0x20
