	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C495C
njp_800C495C:
	addiu	$29,$29,-56
	sw	$19,44($29)
	addu	$19,$4,$0
	addiu	$2,$0,160
	sh	$2,28($29)
	sh	$2,24($29)
	addiu	$2,$0,650
	sw	$31,52($29)
	sw	$20,48($29)
	sw	$18,40($29)
	sw	$17,36($29)
	sw	$16,32($29)
	sh	$2,26($29)
	lw	$2,2524($19)
	nop
	beq	$2,$0,$Lnjp_800C495C_0
	addu	$18,$0,$0
	jal	njp_FreeTargets
	nop
$Lnjp_800C495C_0:
	lui	$2,%hi(DG_ZeroVector)
	addiu	$20,$2,%lo(DG_ZeroVector)
	addu	$17,$19,$0
$Lnjp_800C495C_1:
	jal	GM_AllocTarget
	nop
	addu	$16,$2,$0
	beq	$16,$0,$Lnjp_800C495C_2
	sw	$16,2512($17)
	addu	$4,$16,$0
	addiu	$5,$0,21
	addiu	$6,$0,1
	addiu	$7,$29,24
	addiu	$17,$17,4
	lw	$2,2524($19)
	addu	$18,$18,$6
	addu	$2,$2,$6
	jal	GM_SetTarget
	sw	$2,2524($19)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,-1
	addiu	$7,$0,1024
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$20,20($29)
	slti	$2,$18,3
	bne	$2,$0,$Lnjp_800C495C_1
	nop
$Lnjp_800C495C_2:
	lw	$31,52($29)
	lw	$20,48($29)
	lw	$19,44($29)
	lw	$18,40($29)
	lw	$17,36($29)
	lw	$16,32($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	at
	.text
