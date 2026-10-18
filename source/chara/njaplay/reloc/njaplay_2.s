	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5550
njp_800C5550:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C5550_0
	sw	$31,20($29)
	jal	njp_sna_8004EC00
	nop
	jal	njp_sub_8004F454
	addu	$4,$16,$0
	addu	$4,$16,$0
	addu	$5,$0,$0
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($16)
	jal	njp_sna_set_invuln_8004F2A0
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,28
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
$Lnjp_800C5550_0:
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C5550_1
	nop
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5550_1
	addiu	$2,$0,15
	sw	$2,448($16)
	addiu	$2,$0,1
	sh	$0,408($16)
	sh	$2,2452($16)
$Lnjp_800C5550_1:
	lbu	$2,119($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lnjp_800C5550_2
	nop
	jal	njp_sna_clear_invuln_8004F2EC
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	addiu	$4,$16,32
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C5550_2:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5634
njp_800C5634:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C5634_0
	sw	$31,20($29)
	addu	$5,$0,$0
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_sna_fp_update_800C6A60)
	addiu	$2,$2,%lo(njp_sna_fp_update_800C6A60)
	jal	njp_sna_set_invuln_8004F2A0
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,9
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$4,$16,32
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C5634_0
	lui	$3,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($3)
	nop
	bne	$2,$0,$Lnjp_800C5634_0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($3)
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_spin_end_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_sna_anim_spin_end_800C4E38)
$Lnjp_800C5634_0:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5634_3
	nop
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C5634_1
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_spin_end_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_sna_anim_spin_end_800C4E38)
$Lnjp_800C5634_1:
	jal	njp_sna_set_invuln_8004F2A0
	addiu	$5,$0,32
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x100
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C5634_2:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C5634_3:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C573C
njp_800C573C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C573C_0
	sw	$31,20($29)
	addu	$5,$0,$0
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_sna_fp_update_800C6A60)
	addiu	$2,$2,%lo(njp_sna_fp_update_800C6A60)
	sh	$0,2434($16)
	jal	njp_sna_set_invuln_8004F2A0
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,10
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$4,$16,32
	addiu	$5,$0,197
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C573C_0
	lui	$3,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($3)
	nop
	bne	$2,$0,$Lnjp_800C573C_0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($3)
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
$Lnjp_800C573C_0:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C573C_3
	nop
	lw	$2,2200($16)
	nop
	lh	$2,38($2)
	nop
	bgtz	$2,$Lnjp_800C573C_1
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_spin_end_800C4E38)
	j	$Lnjp_800C573C_2
	addiu	$5,$5,%lo(njp_sna_anim_spin_end_800C4E38)
$Lnjp_800C573C_1:
	jal	njp_sna_set_invuln_8004F2A0
	addiu	$5,$0,32
	lui	$4,0x40
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x100
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C573C_2:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C573C_3:
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5838
njp_800C5838:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$18,32($29)
	addiu	$18,$16,2368
	sw	$31,36($29)
	bne	$5,$0,$Lnjp_800C5838_3
	sw	$17,28($29)
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($16)
	jal	njp_sub_8004F338
	sw	$2,2344($16)
	lui	$4,0x2000
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x8000
	lhu	$3,8($18)
	nop
	andi	$2,$3,0x400
	bne	$2,$0,$Lnjp_800C5838_1
	addu	$4,$16,$0
	andi	$2,$3,0x4000
	bne	$2,$0,$Lnjp_800C5838_0
	addiu	$2,$0,-2
	addiu	$2,$0,-1
$Lnjp_800C5838_0:
	sh	$2,88($16)
	sh	$2,86($16)
	sh	$2,2436($16)
	addu	$4,$16,$0
$Lnjp_800C5838_1:
	jal	njp_sna_set_invuln_8004F2A0
	addu	$5,$0,$0
	addu	$4,$16,$0
	addiu	$17,$0,-1
	sh	$17,170($16)
	lhu	$5,0($18)
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	lh	$2,2($18)
	nop
	bltz	$2,$Lnjp_800C5838_2
	nop
	sh	$2,110($16)
	sh	$2,42($16)
$Lnjp_800C5838_2:
	sh	$17,2452($16)
	sh	$17,2454($16)
$Lnjp_800C5838_3:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,64
	sh	$0,108($16)
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x2
	bne	$2,$0,$Lnjp_800C5838_4
	lui	$2,%hi(DG_ZeroVector)
	addiu	$10,$2,%lo(DG_ZeroVector)
	lwl	$7,3($10)
	lwr	$7,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$7,2443($16)
	swr	$7,2440($16)
	swl	$8,2447($16)
	swr	$8,2444($16)
$Lnjp_800C5838_4:
	lhu	$3,8($18)
	nop
	andi	$2,$3,0x4000
	bne	$2,$0,$Lnjp_800C5838_5
	addiu	$5,$16,32
	andi	$2,$3,0x2
	bne	$2,$0,$Lnjp_800C5838_6
	addiu	$4,$16,32
	addiu	$5,$16,2120
	lh	$3,10($18)
	lh	$6,152($16)
	lhu	$2,180($16)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($16)
	addu	$2,$2,$6
	sh	$2,34($16)
	sll	$2,$2,16
	lw	$3,156($16)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	j	$Lnjp_800C5838_6
	nop
$Lnjp_800C5838_5:
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,16
	lhu	$2,16($29)
	nop
	sh	$2,152($16)
	lhu	$2,20($29)
	nop
	sh	$2,154($16)
$Lnjp_800C5838_6:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5838_9
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x20
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5838_7
	nop
	lbu	$2,117($16)
	nop
	andi	$2,$2,0xfd
	sb	$2,117($16)
$Lnjp_800C5838_7:
	lhu	$2,8($18)
	nop
	andi	$2,$2,0x100
	beq	$2,$0,$Lnjp_800C5838_8
	addiu	$2,$0,15
	sw	$2,448($16)
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sh	$0,408($16)
	sw	$2,2324($16)
	sw	$0,2328($16)
	sh	$0,2454($16)
	j	$Lnjp_800C5838_9
	sh	$0,2452($16)
$Lnjp_800C5838_8:
	lui	$4,0x2000
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x8040
	jal	njp_sna_clear_invuln_8004F2EC
	addu	$4,$16,$0
	sh	$0,2434($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C5838_9:
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
