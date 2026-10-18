	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C35BC
njp_800C35BC:
	addiu	$29,$29,-72
	sw	$18,64($29)
	addu	$18,$4,$0
	addu	$2,$5,$0
	sw	$17,60($29)
	addu	$17,$6,$0
	sw	$31,68($29)
	bltz	$2,$Lnjp_800C35BC_0
	sw	$16,56($29)
	addiu	$16,$29,48
	addu	$4,$16,$0
	addiu	$5,$29,16
	sh	$0,52($29)
	sh	$0,48($29)
	jal	RotMatrixYXZ
	sh	$2,50($29)
	addiu	$4,$29,16
	addu	$5,$16,$0
	addu	$6,$16,$0
	sh	$0,50($29)
	sh	$0,48($29)
	jal	ApplyMatrixSV
	sh	$17,52($29)
	addiu	$4,$18,100
	addu	$5,$16,$0
	jal	GV_AddVec3
	addu	$6,$4,$0
$Lnjp_800C35BC_0:
	lw	$31,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3640
njp_800C3640:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,13
	beq	$5,$2,$Lnjp_800C3640_3
	addu	$3,$0,$0
	slti	$2,$5,14
	beq	$2,$0,$Lnjp_800C3640_0
	addiu	$2,$0,5
	beq	$5,$2,$Lnjp_800C3640_1
	nop
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_0:
	addiu	$2,$0,14
	beq	$5,$2,$Lnjp_800C3640_4
	addiu	$2,$0,3
	j	$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_1:
	bne	$6,$0,$Lnjp_800C3640_2
	addiu	$2,$0,10
	j	$Lnjp_800C3640_6
	addiu	$3,$0,168
$Lnjp_800C3640_2:
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,169
$Lnjp_800C3640_3:
	addiu	$2,$0,3
	bne	$6,$2,$Lnjp_800C3640_6
	nop
	j	$Lnjp_800C3640_6
	addiu	$3,$0,205
$Lnjp_800C3640_4:
	beq	$6,$2,$Lnjp_800C3640_5
	nop
	bne	$6,$5,$Lnjp_800C3640_6
	nop
$Lnjp_800C3640_5:
	addiu	$3,$0,205
$Lnjp_800C3640_6:
	beq	$3,$0,$Lnjp_800C3640_7
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C3640_7:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C36EC
njp_800C36EC:
	addiu	$29,$29,-24
	sw	$31,16($29)
	addiu	$2,$0,26
	bne	$5,$2,$Lnjp_800C36EC_1
	addu	$3,$0,$0
	addiu	$2,$0,3
	beq	$6,$2,$Lnjp_800C36EC_0
	addiu	$2,$0,14
	bne	$6,$2,$Lnjp_800C36EC_1
	nop
$Lnjp_800C36EC_0:
	addiu	$3,$0,205
$Lnjp_800C36EC_1:
	beq	$3,$0,$Lnjp_800C36EC_2
	addu	$5,$3,$0
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C36EC_2:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
