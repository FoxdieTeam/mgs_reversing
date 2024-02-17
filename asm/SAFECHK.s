    opt	c+, at+, e+, n-

    ; asmpsx has a conflicting macro named strlen
    disable strlen

    xdef	SafetyCheck
    xdef	SafetyCheck1
    xdef	SafetyCheck2
    xdef	SafetyCheck3
    xdef	SafetyCheck4
    xdef	SafetyCheck5

    xdef	safety_check_commands
    xdef	safety_check_cdregs
    xdef	safety_check_params
    xdef	safety_check_results
    xdef	safety_check_coords
    xdef 	safety_check_message
    xdef	safety_check_offset

    xref	VSync
    xref 	ResetGraph
    xref 	StopCallback
    xref 	SetDefDrawEnv
    xref 	SetDefDispEnv
    xref 	SetDrawEnv
    xref 	DrawPrim
    xref 	PutDispEnv
    xref 	SetDispMask
    xref 	exit
    xref 	strlen
    xref 	Krom2RawAdd

    section overlay.data

    ; random unused data
    dw		$001C7350
    dw		$03100000

safety_check_commands:
    dw		$03010001
    dw		$05010007
    dw		$03010302
    dw		$05010016
    dw		$0301010E
    dw		$03040119
    dw		$0301000B
    dw		$03010003
    dw		$03020119
    dw		$05010009

safety_check_cdregs:
    dw		$1F801800
    dw		$1F801801
    dw		$1F801802
    dw		$1F801803

safety_check_params:
    db		0, 0, 0, 0, 0, 0, 0, 0

safety_check_results:
    db		0, 0, 0, 0, 0, 0, 0, 0

safety_check_coords:
    db		0, 0
    db		6, 5
    db		12, 10
    db		18, 15
    db		24, 20
    db		30, 25
    db		35, 30
    db		40, 34
    db		45, 38
    db		49, 41
    db		53, 44
    db		56, 47
    db		59, 49
    db		61, 51
    db		62, 52
    db		63, 53
    db		64, 54
    db		0, 0
    db		0, 0
    db		0, 0
    db		0, 0
    db		0, 0
    db		0, 0
    db		0, 0

    section overlay.rdata

; 強制終了しました。 本体が改造されている おそれがあります。
safety_check_message:
    db		$8B
    db		$AD
    db		$90
    db		$A7
    db		$8F
    db		$49
    db		$97
    db		$B9
    db		$82
    db		$B5
    db		$82
    db		$DC
    db		$82
    db		$B5
    db		$82
    db		$BD
    db		$81
    db		$42
    db		$0A
    db		$96
    db		$7B
    db		$91
    db		$CC
    db		$82
    db		$AA
    db		$89
    db		$FC
    db		$91
    db		$A2
    db		$82
    db		$B3
    db		$82
    db		$EA
    db		$82
    db		$C4
    db		$82
    db		$A2
    db		$82
    db		$E9
    db		$0A
    db		$82
    db		$A8
    db		$82
    db		$BB
    db		$82
    db		$EA
    db		$82
    db		$AA
    db		$82
    db		$A0
    db		$82
    db		$E8
    db		$82
    db		$DC
    db		$82
    db		$B7
    db		$81
    db		$42
    db		$00
    db		$00

safety_check_offset:
    dh 		257, 511
    dh 		-255, -1
    dh 		0, 0
    dh 		0, 0
    dh 		0, 0

    section overlay.text

SafetyCheck:
    addiu	sp, sp, -0x30
    sw		s2, 0x20(sp)
    move	s2, a0
    sw		s3, 0x24(sp)
    move 	s3, a1
    sw 		s4, 0x28(sp)
    move 	s4, a2
    sw 		s0, 0x18(sp)
    move 	s0, zero
    addiu 	v0, zero, 0x20
    sw 		ra, 0x2c(sp)
    sw 		s1, 0x1c(sp)
    sb 		v0, safety_check_params
    jal 	SafetyCheck1
    addiu 	a0, zero, 5
    bltz 	v0, @lab_164
    nop
    jal 	SafetyCheck1
    move 	a0, zero
    bltz 	v0, @lab_164
    nop
    lbu 	v1, safety_check_results
    nop
    andi 	v0, v1, 0xf0
    bnez 	v0, @lab_164
    andi 	v0, v1, 2
    bnez 	v0, @lab_88
    addiu 	a0, zero, 2
    jal 	SafetyCheck1
    addiu 	a0, zero, 1
    bltz 	v0, @lab_164
    addiu 	a0, zero, 2

@lab_88:
    la 		s1, safety_check_params
    sb 		s2, 0(s1)
    sb 		s3, 1(s1)
    jal 	SafetyCheck1
    sb 		s4, 2(s1)
    bltz 	v0, @lab_164
    addiu 	v0, zero, 1
    sb 		v0, 0(s1)
    jal 	SafetyCheck1
    addiu 	a0, zero, 4
    bltz 	v0, @lab_164
    nop
    jal 	VSync
    addiu 	a0, zero, 3
    jal 	SafetyCheck1
    addiu 	a0, zero, 3
    bltz 	v0, @lab_164
    nop
    jal 	SafetyCheck1
    addiu 	a0, zero, 6
    bltz	v0, @lab_164
    nop
    jal		SafetyCheck1
    addiu	a0, zero, 7
    bltz	v0, @lab_164
    addiu	v0, zero, 4
    sb		v0, 0(s1)
    jal		SafetyCheck1
    addiu	a0, zero, 8
    bltz	v0, @lab_164
    nop
    jal		VSync
    addiu	a0, zero, 0xc8
    addiu	v0, zero, 5
    sb		v0, 0(s1)
    jal 	SafetyCheck1
    addiu 	a0, zero, 8
    bltz 	v0, @lab_164
    nop
    la		s1, (safety_check_results+1)
    lbu		v0, 0(s1)
    nop
    beqz 	v0, @lab_174
    nop
    jal 	SafetyCheck1
    move	a0, zero
    bltz	v0, @lab_164
    nop
    lbu 	v0, -1(s1)
    nop
    andi 	v0, v0, 0x10
    beqz 	v0, @lab_16c
    nop

@lab_164:
    j 		@lab_174
    addiu	s0, zero, -1

@lab_16c:
    jal		SafetyCheck2
    nop

@lab_174:
    jal 	SafetyCheck1
    addiu	a0, zero, 9
    bgez	v0, @lab_18c
    move	v0, s0
    addiu	s0, zero, -1
    move	v0, s0

@lab_18c:
    lw		ra, 0x2c(sp)
    lw		s4, 0x28(sp)
    lw		s3, 0x24(sp)
    lw		s2, 0x20(sp)
    lw		s1, 0x1c(sp)
    lw		s0, 0x18(sp)
    jr		ra
    addiu	sp, sp, 0x30

SafetyCheck1:
    move	t0, a0
    move	a0, zero
    move	a1, zero
    lw		v1, safety_check_cdregs
    addiu	v0, zero, 1
    sb		v0, 0(v1)
    lw		v1, safety_check_cdregs+12
    addiu	v0, zero, 7
    sb		v0, 0(v1)

@lab_2c:
    sw		a0, 0(a1)
    addiu	a0, a0, 1
    slti	v0, a0, 4
    bnez	v0, @lab_2c
    addiu	v0, zero, 1
    lw		v1, safety_check_cdregs
    nop
    sb		v0, 0(v1)
    lw		v1, safety_check_cdregs+8
    addiu	v0, zero, 0x18
    sb		v0, 0(v1)
    lw		v0, safety_check_cdregs
    sll		a0, t0, 2
    sb		zero, 0(v0)
    opt m-
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, (safety_check_commands&0xffff)+1(v0)
    opt m+
    nop
    beqz	v0, @lab_c0
    move	a1, zero

@lab_88:
    lw		v0, safety_check_cdregs+8
    opt m-
    lui		v1, safety_check_params>>16
    addu    v1, v1, a1
    lbu		v1, safety_check_params&0xffff(v1)
    nop
    sb		v1, 0(v0)
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, (safety_check_commands&0xffff)+1(v0)
    opt m+
    addiu	a1, a1, 1
    slt		v0, a1, v0
    bnez	v0, @lab_88
    nop

@lab_c0:
    lw		v0, safety_check_cdregs
    sll		a0, t0, 2
    sb		zero, 0(v0)
    lw		v1, safety_check_cdregs+4
    opt m-
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, safety_check_commands&0xffff(v0)
    move	a1, zero
    sb		v0, 0(v1)
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, (safety_check_commands&0xffff)+3(v0)
    opt m+
    nop
    beqz	v0, @lab_194
    move	a2, zero
    addiu	a3, zero, 1
    addiu	t2, zero, 7
    move	t1, v0

@lab_110:
    lw		v0, safety_check_cdregs
    nop
    sb		a3, 0(v0)
    lw		a0, safety_check_cdregs+12
    nop

@lab_12c:
    lbu		v1, 0(a0)
    lbu		v0, 0(a0)
    andi	v1, v1, 7
    andi	v0, v0, 7
    bne		v1, v0, @lab_12c
    move	a1, v1
    andi	v0, a1, 0xff
    beqz	v0, @lab_188
    nop
    addu	a2, a2, v0
    lw		v0, safety_check_cdregs
    move	v1, zero
    sb		a3, 0(v0)
    lw		v0, safety_check_cdregs+12
    move	a0, zero
    sb		t2, 0(v0)

@lab_174:
    sw		v1, 0(a0)
    addiu	v1, v1, 1
    slti	v0, v1, 4
    bnez	v0, @lab_174
    nop

@lab_188:
    slt		v0, a2, t1
    bnez	v0, @lab_110
    nop

@lab_194:
    addiu	v0, zero, 5
    bne		a1, v0, @lab_1a4
    move	v1, zero
    addiu	v1, zero, -1

@lab_1a4:
    bgez 	v1, @lab_1b4
    sll 	a0, t0, 2
    j 		@lab_208
    addiu 	v0, zero, -1

@lab_1b4:
    opt m-
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, (safety_check_commands&0xffff)+2(v0)
    opt m+
    nop
    beqz	v0, @lab_204
    move	a1, zero

@lab_1cc:
    lw 		v0, safety_check_cdregs+4
    nop
    lbu		v0, 0(v0)
    sb		v0, safety_check_results(a1)
    opt	m-
    lui		v0, safety_check_commands>>16
    addu    v0, v0, a0
    lbu		v0, (safety_check_commands&0xffff)+2(v0)
    opt	m+
    addiu	a1, a1, 1
    slt		v0, a1, v0
    bnez	v0, @lab_1cc
    nop

@lab_204:
    move	v0, zero

@lab_208:
    lw		a0, safety_check_cdregs
    addiu	v1, zero, 1
    sb		v1, 0(a0)
    lw		a0, safety_check_cdregs+8
    addiu	v1, zero, 0x1f
    jr		ra
    sb		v1, 0(a0)

SafetyCheck2:
    addiu 	sp, sp, -0xf8
    addiu 	a0, zero, 1
    sw 		ra, 0xf0(sp)
    sw 		s1, 0xec(sp)
    jal 	ResetGraph
    sw 		s0, 0xe8(sp)
    jal 	StopCallback
    addiu 	s0, zero, 0xf0
    jal 	ResetGraph
    addiu 	a0, zero, 5
    addiu 	a0, sp, 0x18
    move 	a1, zero
    move 	a2, zero
    addiu 	a3, zero, 0x140
    jal 	SetDefDrawEnv
    sw 		s0, 0x10(sp)
    addiu 	s1, sp, 0x78
    move 	a0, s1
    move 	a1, zero
    move 	a2, zero
    addiu 	a3, zero, 0x140
    jal 	SetDefDispEnv
    sw 		s0, 0x10(sp)
    addiu 	s0, sp, 0x90
    move 	a0, s0
    addiu 	a1, sp, 0x18
    addiu 	v0, zero, 1
    jal 	SetDrawEnv
    sb 		v0, 0x30(sp)
    jal 	DrawPrim
    move 	a0, s0
    jal 	PutDispEnv
    move 	a0, s1
    lui 	v1, 0xe600
    ori 	v1, v1, 2
    addiu 	a0, sp, 0xd0
    lui 	v0, 0x200
    sw 		v0, 0xd0(sp)
    sw 		v1, 0xd4(sp)
    jal 	DrawPrim
    sw 		zero, 0xd8(sp)
    ori 	a2, zero, 0xffff
    move 	s0, zero
    addiu 	v0, zero, 0x10
    sh		v0, 0xe4(sp)
    addiu	v0, zero, 1
    sh		v0, 0xe6(sp)

@lab_bc:
    la		a0, safety_check_message
    addiu	a1, sp, 0xe0
    addiu	v0, s0, 0x50
    sh		v0, 0xe0(sp)
    addiu	v0, s0, 0x5c
    jal		SafetyCheck3
    sh		v0, 0xe2(sp)
    addiu	s0, s0, 1
    slti	v0, s0, 2
    bnez	v0, @lab_bc
    ori		a2, zero, 0x8000
    jal		SafetyCheck5
    nop
    jal		SetDispMask
    addiu	a0, zero, 1
    jal 	exit
    nop
    lw		ra, 0xf0(sp)
    lw		s1, 0xec(sp)
    lw		s0, 0xe8(sp)
    jr		ra
    addiu	sp, sp, 0xf8

SafetyCheck3:
    addiu	sp, sp, -0x30
    sw		s0, 0x10(sp)
    move	s0, a0
    sw		s1, 0x14(sp)
    move	s1, a1
    sw		s4, 0x20(sp)
    move	s4, a2
    sw		ra, 0x28(sp)
    sw		s5, 0x24(sp)
    sw		s3, 0x1c(sp)
    jal		strlen
    sw		s2, 0x18(sp)
    addu	v1, s0, v0
    sltu	v0, s0, v1
    lh		s3, 0(s1)
    beqz	v0, @lab_b4
    addiu	s5, zero, 0xa
    move	s2, v1

@lab_48:
    lbu		v0, 0(s0)
    nop
    bne		v0, s5, @lab_6c
    nop
    lhu 	v0, 2(s1)
    sh		s3, 0(s1)
    addiu	v0, v0, 0x12
    j		@lab_a4
    sh		v0, 2(s1)

@lab_6c:
    lbu		a0, 0(s0)
    addiu	s0, s0, 1
    lbu		v0, 0(s0)
    sll		a0, a0, 8
    jal		Krom2RawAdd
    or		a0, v0, a0
    move	a0, s1
    move	a1, v0
    jal		SafetyCheck4
    move	a2, s4
    lhu		v0, 0(s1)
    nop
    addiu	v0, v0, 0x11
    sh		v0, 0(s1)

@lab_a4:
    addiu	s0, s0, 1
    sltu	v0, s0, s2
    bnez	v0, @lab_48
    nop

@lab_b4:
    lw		ra, 0x28(sp)
    lw		s5, 0x24(sp)
    lw		s4, 0x20(sp)
    lw		s3, 0x1c(sp)
    lw		s2, 0x18(sp)
    lw		s1, 0x14(sp)
    lw		s0, 0x10(sp)
    jr 		ra
    addiu	sp, sp, 0x30

SafetyCheck4:
    addiu	sp, sp, -0x60
    sw		s1, 0x44(sp)
    move 	s1, a0
    sw 		s2, 0x48(sp)
    move 	s2, a1
    sw 		s4, 0x50(sp)
    move 	s4, a2
    sw 		ra, 0x5c(sp)
    sw 		s6, 0x58(sp)
    sw 		s5, 0x54(sp)
    sw 		s3, 0x4c(sp)
    sw 		s0, 0x40(sp)
    lh 		s5, 0(s1)
    lh 		s6, 2(s1)
    lui 	v0, 0xb00
    sw 		v0, 0x10(sp)
    lui 	v0, 0xa000
    sw 		v0, 0x14(sp)
    lw 		v0, 4(s1)
    move 	s3, zero
    sw 		v0, 0x1c(sp)
    addiu 	a2, sp, 0x20

@lab_58:
    move 	s0, zero

@lab_5c:
    addiu 	v1, zero, 7

@lab_60:
    move 	a1, a2
    addiu 	a2, a1, 2
    lbu 	v0, 0(s2)
    nop
    srav 	v0, v0, v1
    andi 	v0, v0, 1
    beqz 	v0, @lab_84
    move 	a0, zero
    move 	a0, s4

@lab_84:
    addiu 	v1, v1, -1
    bgez 	v1, @lab_60
    sh 		a0, 0(a1)
    addiu 	s0, s0, 1
    slti 	v0, s0, 2
    bnez 	v0, @lab_5c
    addiu 	s2, s2, 1
    move 	s0, zero

@lab_a4:
    lw 		v0, 0(s1)
    addiu 	a0, sp, 0x10
    jal 	DrawPrim
    sw 		v0, 0x18(sp)
    lhu 	v0, 0(s1)
    addiu 	s0, s0, 1
    addiu 	v0, v0, 1
    sh 		v0, 0(s1)
    slti 	v0, s0, 2
    bnez 	v0, @lab_a4
    nop
    lhu 	v0, 2(s1)
    addiu 	s3, s3, 1
    sh 		s5, 0(s1)
    addiu 	v0, v0, 1
    sh 		v0, 2(s1)
    slti 	v0, s3, 0xf
    bnez 	v0, @lab_58
    addiu 	a2, sp, 0x20
    sh 		s6, 2(s1)
    lw 		ra, 0x5c(sp)
    lw 		s6, 0x58(sp)
    lw 		s5, 0x54(sp)
    lw 		s4, 0x50(sp)
    lw 		s3, 0x4c(sp)
    lw 		s2, 0x48(sp)
    lw 		s1, 0x44(sp)
    lw 		s0, 0x40(sp)
    jr 		ra
    addiu 	sp, sp, 0x60

SafetyCheck5:
    addiu	sp, sp, -0x50
    lui		v1, 0x2800
    ori		v1, v1, 0xff
    sw		s2, 0x38(sp)
    move	s2, zero
    sw		s4, 0x40(sp)
    addiu	s4, sp, 0x10
    sw		s6, 0x48(sp)
    addiu	s6, sp, 0x28
    sw		s5, 0x44(sp)
    addiu 	s5, zero, 0x10
    sw 		s3, 0x3c(sp)
    la 		s3, safety_check_coords
    lui 	v0, 0x500
    sw		ra, 0x4c(sp)
    sw		s1, 0x34(sp)
    sw		s0, 0x30(sp)
    sw		v0, 0x10(sp)
    sw		v1, 0x14(sp)

@lab_50:
    move	s1, zero
    move	s0, s6

@lab_58:
    la 		a1, safety_check_offset
    lwl 	v0, 3(a1)
    lwr 	v0, 0(a1)
    lwl 	v1, 7(a1)
    lwr 	v1, 4(a1)
    swl 	v0, 0x2b(sp)
    swr 	v0, 0x28(sp)
    swl 	v1, 0x2f(sp)
    swr 	v1, 0x2c(sp)
    move 	a2, zero
    move 	t1, s0
    move 	t0, s4

@lab_8c:
    addiu	a1, a2, 2
    sra 	a1, a1, 2
    andi 	v1, a2, 1
    addu 	v1, s2, v1
    subu 	v0, s5, v1
    sll 	v0, v0, 1
    addu 	v0, v0, s3
    addu 	v0, v0, a1
    lb 		a0, 1(t1)
    lbu 	v0, 0(v0)
    nop
    mult 	a0, v0
    sll 	v1, v1, 1
    addu 	v1, v1, s3
    addu 	v1, v1, a1
    lb 		a0, 0(t1)
    mflo 	a3
    lbu 	v0, 0(v1)
    nop
    mult 	a0, v0
    addiu 	a2, a2, 1
    addiu 	v0, a3, 0x78
    sll 	v0, v0, 0x10
    mflo 	v1
    addiu 	v1, v1, 0xa0
    or 		v0, v0, v1
    sw 		v0, 8(t0)
    slti 	v0, a2, 4
    bnez 	v0, @lab_8c
    addiu 	t0, t0, 4
    jal 	DrawPrim
    addiu 	a0, sp, 0x10
    addiu 	s1, s1, 1
    slti 	v0, s1, 4
    bnez 	v0, @lab_58
    addiu 	s0, s0, 2
    addiu 	s2, s2, 1
    slti 	v0, s2, 0x10
    bnez 	v0, @lab_50
    lui 	a2, 0x50
    ori 	a2, a2, 0x70
    lui 	a1, 0x48
    ori 	a1, a1, 0x78
    lui 	v1, 0xa8
    ori 	v1, v1, 0xc8
    lui 	v0, 0xa0
    ori 	v0, v0, 0xd0
    addiu 	a0, sp, 0x10
    sw 		a2, 0x18(sp)
    sw 		a1, 0x1c(sp)
    sw 		v1, 0x20(sp)
    jal 	DrawPrim
    sw 		v0, 0x24(sp)
    lw 		ra, 0x4c(sp)
    lw 		s6, 0x48(sp)
    lw 		s5, 0x44(sp)
    lw 		s4, 0x40(sp)
    lw 		s3, 0x3c(sp)
    lw 		s2, 0x38(sp)
    lw 		s1, 0x34(sp)
    lw 		s0, 0x30(sp)
    jr 		ra
    addiu 	sp, sp, 0x50
    nop
