	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C60E4
njp_800C60E4:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$18,32($29)
	addu	$18,$5,$0
	addiu	$2,$18,-5
	sltiu	$2,$2,15
	sw	$31,36($29)
	beq	$2,$0,$Lnjp_800C60E4_0
	sw	$17,28($29)
	addiu	$2,$0,2
	sw	$2,2532($16)
$Lnjp_800C60E4_0:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$17,$2,0xf000
	lh	$2,2452($16)
	sltu	$17,$0,$17
	beq	$17,$2,$Lnjp_800C60E4_2
	nop
	beq	$17,$0,$Lnjp_800C60E4_1
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$2,$0,1022
	sw	$2,16($29)
	addiu	$4,$16,156
	addiu	$5,$0,26
	addu	$6,$18,$0
	jal	GM_ConfigObjectOverride
	addiu	$7,$0,4
	j	$Lnjp_800C60E4_2
	nop
$Lnjp_800C60E4_1:
	addiu	$4,$16,156
	addiu	$5,$0,14
	addu	$6,$18,$0
	jal	GM_ConfigObjectAction
	addiu	$7,$0,4
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
$Lnjp_800C60E4_2:
	beq	$17,$0,$Lnjp_800C60E4_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_sub_8004E4C0
	addu	$4,$16,$0
	sh	$2,110($16)
$Lnjp_800C60E4_3:
	addu	$4,$16,$0
	lui	$5,%hi(njp_stru_8009EFD4+32)
	jal	njp_sna_800C3898
	addiu	$5,$5,%lo(njp_stru_8009EFD4+32)
	jal	njp_sna_800C399C
	addu	$4,$16,$0
	addiu	$2,$0,23
	bne	$18,$2,$Lnjp_800C60E4_6
	sh	$17,2452($16)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	beq	$17,$0,$Lnjp_800C60E4_4
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_run_begin_80053B88)
	j	$Lnjp_800C60E4_5
	addiu	$5,$5,%lo(njp_sna_anim_run_begin_80053B88)
$Lnjp_800C60E4_4:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C60E4_5:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C60E4_6:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.text
