	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C65D4
njp_800C65D4:
	addiu	$29,$29,-48
	sw	$20,40($29)
	addu	$20,$4,$0
	sw	$31,44($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$2,2320($20)
	lw	$3,2320($20)
	lhu	$2,0($2)
	nop
	sh	$2,16($29)
	lbu	$2,15($3)
	addiu	$4,$29,16
	jal	GM_CheckShukanReverse
	sb	$2,18($29)
	jal	GM_CheckShukanReverseAnalog
	addiu	$4,$29,18
	addiu	$17,$20,2348
	lh	$19,8($17)
	lh	$2,6($17)
	lh	$3,2348($20)
	subu	$18,$0,$2
	beq	$3,$0,$Lnjp_800C65D4_0
	addu	$16,$0,$0
	lh	$16,108($20)
$Lnjp_800C65D4_0:
	lui	$2,%hi(njp_dword_800ABBDC)
	lh	$3,%lo(njp_dword_800ABBDC)($2)
	nop
	slt	$2,$18,$3
	beq	$2,$0,$Lnjp_800C65D4_1
	lui	$2,%hi(njp_dword_800ABBD4)
	addu	$18,$3,$0
$Lnjp_800C65D4_1:
	lh	$3,%lo(njp_dword_800ABBD4)($2)
	nop
	slt	$2,$3,$19
	beq	$2,$0,$Lnjp_800C65D4_2
	nop
	addu	$19,$3,$0
$Lnjp_800C65D4_2:
	addu	$4,$20,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,16384
	addiu	$6,$0,1
	lhu	$3,16($29)
	addu	$5,$2,$0
	andi	$2,$3,0x1000
	beq	$2,$0,$Lnjp_800C65D4_6
	addu	$4,$6,$0
	andi	$2,$5,0xff
	beq	$2,$0,$Lnjp_800C65D4_3
	addiu	$2,$0,64
	addiu	$6,$0,64
	lbu	$3,18($29)
	nop
	subu	$4,$2,$3
$Lnjp_800C65D4_3:
	lh	$3,10($17)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$6
	bne	$6,$0,$Lnjp_800C65D4_4
	nop
	.word	0x0007000D
$Lnjp_800C65D4_4:
	addiu	$1,$0,-1
	bne	$6,$1,$Lnjp_800C65D4_5
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C65D4_5
	nop
	.word	0x0006000D
$Lnjp_800C65D4_5:
	mflo	$2
	j	$Lnjp_800C65D4_10
	subu	$16,$16,$2
$Lnjp_800C65D4_6:
	andi	$2,$3,0x4000
	beq	$2,$0,$Lnjp_800C65D4_10
	andi	$2,$5,0xff
	beq	$2,$0,$Lnjp_800C65D4_7
	nop
	lbu	$2,18($29)
	addiu	$6,$0,63
	addiu	$4,$2,64
$Lnjp_800C65D4_7:
	lh	$3,12($17)
	andi	$2,$4,0xff
	mult	$3,$2
	mflo	$3
	nop
	nop
	div	$3,$6
	bne	$6,$0,$Lnjp_800C65D4_8
	nop
	.word	0x0007000D
$Lnjp_800C65D4_8:
	addiu	$1,$0,-1
	bne	$6,$1,$Lnjp_800C65D4_9
	lui	$1,0x8000
	bne	$3,$1,$Lnjp_800C65D4_9
	nop
	.word	0x0006000D
$Lnjp_800C65D4_9:
	mflo	$2
	nop
	addu	$16,$16,$2
$Lnjp_800C65D4_10:
	slt	$2,$16,$18
	beq	$2,$0,$Lnjp_800C65D4_11
	slt	$2,$19,$16
	addu	$16,$18,$0
	slt	$2,$19,$16
$Lnjp_800C65D4_11:
	beq	$2,$0,$Lnjp_800C65D4_12
	nop
	addu	$16,$19,$0
$Lnjp_800C65D4_12:
	sh	$16,108($20)
	lw	$31,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	at
	.text
