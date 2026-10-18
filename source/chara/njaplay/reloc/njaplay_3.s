	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5D4C
njp_800C5D4C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	njp_800C5A70
	addu	$16,$4,$0
	jal	njp_800C5B18
	addu	$4,$16,$0
	beq	$2,$0,$Lnjp_800C5D4C_1
	nop
	lhu	$2,2452($16)
	nop
	addiu	$2,$2,1
	sh	$2,2452($16)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C5D4C_0
	addu	$4,$16,$0
	sh	$0,2452($16)
$Lnjp_800C5D4C_0:
	addu	$6,$0,$0
	lh	$5,2452($16)
	addiu	$7,$0,1022
	jal	njp_sna_8004E260
	addiu	$5,$5,16
	addu	$4,$16,$0
	jal	njp_sna_8004F034
	addiu	$5,$0,1022
$Lnjp_800C5D4C_1:
	lh	$2,184($16)
	nop
	beq	$2,$0,$Lnjp_800C5D4C_2
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	addiu	$2,$0,-1
	sh	$2,2452($16)
$Lnjp_800C5D4C_2:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5D4C_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_800C54EC)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_800C54EC)
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$5,0x4
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,2048
	j	$Lnjp_800C5D4C_4
	nop
$Lnjp_800C5D4C_3:
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$5,$Lnjp_800C5D4C_5
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_800C4A38)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_800C4A38)
$Lnjp_800C5D4C_4:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	njp_FreeTargets
	addu	$4,$16,$0
	j	$Lnjp_800C5D4C_6
	nop
$Lnjp_800C5D4C_5:
	jal	njp_sub_8004E4C0
	addu	$4,$16,$0
	sh	$2,110($16)
	addu	$4,$16,$0
	jal	njp_sub_8004EA50
	addu	$5,$2,$0
$Lnjp_800C5D4C_6:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
