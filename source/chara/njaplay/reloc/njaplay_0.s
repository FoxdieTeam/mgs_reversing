	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3A30
njp_800C3A30:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lw	$2,2320($16)
	nop
	lhu	$5,0($2)
	lhu	$4,2($2)
	andi	$3,$5,0x20
	beq	$3,$0,$Lnjp_800C3A30_1
	andi	$2,$4,0x40
	lb	$2,119($16)
	nop
	beq	$2,$0,$Lnjp_800C3A30_1
	andi	$2,$4,0x40
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_set_flags1_8004E2F4
	ori	$5,$5,0x4
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C3A30_0
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A90)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4A90)
$Lnjp_800C3A30_0:
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4A38)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4A38)
$Lnjp_800C3A30_1:
	beq	$2,$0,$Lnjp_800C3A30_2
	andi	$2,$4,0x80
	lb	$2,119($16)
	nop
	beq	$2,$0,$Lnjp_800C3A30_2
	andi	$2,$4,0x80
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C5150)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C5150)
$Lnjp_800C3A30_2:
	beq	$2,$0,$Lnjp_800C3A30_4
	andi	$2,$5,0xf000
	beq	$2,$0,$Lnjp_800C3A30_3
	nop
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4B44)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C4B44)
$Lnjp_800C3A30_3:
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_chokethrow_begin2_80058C80)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_sna_anim_chokethrow_begin2_80058C80)
$Lnjp_800C3A30_4:
	andi	$2,$4,0x8
	bne	$2,$0,$Lnjp_800C3A30_5
	addu	$4,$16,$0
	j	$Lnjp_800C3A30_7
	addu	$2,$0,$0
$Lnjp_800C3A30_5:
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4BA4)
	addiu	$5,$5,%lo(njp_800C4BA4)
$Lnjp_800C3A30_6:
	jal	njp_sna_start_anim_8004E1F4
	nop
	addiu	$2,$0,1
$Lnjp_800C3A30_7:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.text
