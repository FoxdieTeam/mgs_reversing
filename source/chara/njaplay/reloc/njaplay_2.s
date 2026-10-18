	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5150
njp_800C5150:
	addiu	$29,$29,-168
	sw	$20,160($29)
	addu	$20,$4,$0
	sw	$17,148($29)
	addu	$17,$5,$0
	sw	$31,164($29)
	sw	$19,156($29)
	sw	$18,152($29)
	bne	$17,$0,$Lnjp_800C5150_0
	sw	$16,144($29)
	addiu	$5,$0,27
	addiu	$6,$0,4
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($20)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($20)
	addu	$4,$20,$0
	jal	njp_sna_set_invuln_8004F2A0
	addu	$5,$0,$0
	addu	$4,$20,$0
	addiu	$5,$0,4096
	lbu	$2,117($20)
	lhu	$3,152($20)
	ori	$2,$2,0x8
	sh	$3,2452($20)
	jal	njp_sna_set_flags1_8004E2F4
	sb	$2,117($20)
	addiu	$4,$20,32
	addiu	$5,$0,209
	addiu	$6,$0,1
	jal	GM_SeSetMode
	sh	$0,2442($20)
$Lnjp_800C5150_0:
	slti	$2,$17,12
	beq	$2,$0,$Lnjp_800C5150_2
	sw	$0,1944($20)
	addu	$4,$20,$0
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_sna_800C35BC
	addiu	$6,$0,96
	addiu	$16,$20,32
	addu	$4,$16,$0
	addiu	$5,$20,2120
	lh	$3,2452($20)
	lh	$6,152($20)
	lhu	$2,180($20)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($20)
	addu	$2,$2,$6
	sh	$2,34($20)
	sll	$2,$2,16
	lw	$3,156($20)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	lw	$2,76($20)
	addu	$5,$16,$0
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,24
	lhu	$2,24($29)
	nop
	sh	$2,152($20)
	lhu	$2,28($29)
	nop
	sh	$2,154($20)
	addiu	$2,$0,11
	bne	$17,$2,$Lnjp_800C5150_5
	nop
	lw	$4,156($20)
	jal	njp_DG_ObjsMinY_800C5104
	nop
	lh	$3,34($20)
	nop
	subu	$3,$3,$2
	slti	$2,$3,97
	beq	$2,$0,$Lnjp_800C5150_1
	nop
	addiu	$3,$0,97
$Lnjp_800C5150_1:
	lw	$2,2200($20)
	sh	$3,82($20)
	j	$Lnjp_800C5150_5
	sh	$3,18($2)
$Lnjp_800C5150_2:
	lw	$4,156($20)
	jal	njp_DG_ObjsMinY_800C5104
	nop
	lh	$3,34($20)
	nop
	subu	$3,$3,$2
	slti	$2,$3,97
	beq	$2,$0,$Lnjp_800C5150_3
	addu	$4,$20,$0
	addiu	$3,$0,97
$Lnjp_800C5150_3:
	lw	$2,2200($20)
	addiu	$5,$0,4096
	sh	$3,82($20)
	jal	njp_sna_check_flags1_8004E31C
	sh	$3,18($2)
	beq	$2,$0,$Lnjp_800C5150_5
	nop
	lb	$2,119($20)
	nop
	beq	$2,$0,$Lnjp_800C5150_4
	addu	$4,$20,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4096
	addiu	$4,$29,32
	lui	$2,%hi(DG_ZeroMatrix)
	addiu	$11,$2,%lo(DG_ZeroMatrix)
	lw	$8,0($11)
	lw	$9,4($11)
	lw	$10,8($11)
	sw	$8,32($29)
	sw	$9,36($29)
	sw	$10,40($29)
	lw	$8,12($11)
	lw	$9,16($11)
	lw	$10,20($11)
	sw	$8,44($29)
	sw	$9,48($29)
	sw	$10,52($29)
	lw	$8,24($11)
	lw	$9,28($11)
	sw	$8,56($29)
	sw	$9,60($29)
	lh	$2,32($20)
	addiu	$5,$0,200
	sw	$2,52($29)
	lh	$2,152($20)
	addiu	$6,$0,100
	addiu	$2,$2,20
	sw	$2,56($29)
	lh	$2,36($20)
	addiu	$7,$0,300
	sw	$2,60($29)
	addiu	$2,$0,10
	jal	NewWindcrcl_800CF784
	sw	$2,16($29)
	addiu	$16,$29,64
	addu	$4,$16,$0
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,136
	addiu	$2,$0,350
	addiu	$19,$0,150
	sh	$2,76($16)
	sh	$2,72($16)
	jal	GM_SetTarget
	sh	$19,74($16)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,2
	addiu	$7,$0,256
	lui	$17,%hi(DG_ZeroVector)
	addiu	$17,$17,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$17,20($29)
	addu	$4,$16,$0
	addiu	$18,$20,32
	jal	GM_MoveTarget
	addu	$5,$18,$0
	jal	GM_PowerTarget
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,136
	addiu	$2,$0,500
	sh	$2,76($16)
	sh	$2,72($16)
	jal	GM_SetTarget
	sh	$19,74($16)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,2
	addu	$7,$5,$0
	addiu	$2,$0,5
	sw	$2,16($29)
	jal	GM_SetPowerTarget
	sw	$17,20($29)
	addu	$4,$16,$0
	addu	$5,$18,$0
	addiu	$2,$0,4
	jal	GM_MoveTarget
	sw	$2,68($16)
	jal	GM_PowerTarget
	addu	$4,$16,$0
	lui	$4,%hi(njp_dword_8009EED4)
	addiu	$4,$4,%lo(njp_dword_8009EED4)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EED8)
	addiu	$4,$4,%lo(njp_dword_8009EED8)
	jal	NewPadVibration
	addiu	$5,$0,2
	addu	$4,$18,$0
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
	j	$Lnjp_800C5150_5
	nop
$Lnjp_800C5150_4:
	lhu	$2,2442($20)
	nop
	addiu	$2,$2,-96
	sh	$2,2442($20)
$Lnjp_800C5150_5:
	lh	$2,182($20)
	nop
	beq	$2,$0,$Lnjp_800C5150_6
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	addu	$4,$20,$0
	lbu	$2,117($20)
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	andi	$2,$2,0xf7
	jal	njp_sna_start_anim_8004E1F4
	sb	$2,117($20)
	addu	$4,$20,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4100
	jal	njp_sna_clear_invuln_8004F2EC
	addu	$4,$20,$0
$Lnjp_800C5150_6:
	lw	$31,164($29)
	lw	$20,160($29)
	lw	$19,156($29)
	lw	$18,152($29)
	lw	$17,148($29)
	lw	$16,144($29)
	jr	$31
	addiu	$29,$29,168
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C54EC
njp_800C54EC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C54EC_0
	sw	$31,20($29)
	addiu	$5,$0,5
	addiu	$6,$0,4
	lui	$2,%hi(njp_800C60E4)
	addiu	$2,$2,%lo(njp_800C60E4)
	sw	$2,2340($16)
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,26
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addiu	$7,$0,1022
	addiu	$2,$0,1
	sh	$2,2452($16)
$Lnjp_800C54EC_0:
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
	lui	$2,%hi(njp_800C6A60)
	addiu	$2,$2,%lo(njp_800C6A60)
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
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_800C4E38)
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
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C5634_2
	addiu	$5,$5,%lo(njp_800C4E38)
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
	lui	$2,%hi(njp_800C6A60)
	addiu	$2,$2,%lo(njp_800C6A60)
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
	lui	$5,%hi(njp_800C4E38)
	j	$Lnjp_800C573C_2
	addiu	$5,$5,%lo(njp_800C4E38)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5A70
njp_800C5A70:
	addiu	$29,$29,-96
	sw	$19,84($29)
	addu	$19,$4,$0
	addiu	$4,$29,40
	sw	$31,88($29)
	sw	$18,80($29)
	sw	$17,76($29)
	jal	ReadRotMatrix
	sw	$16,72($29)
	addiu	$4,$19,32
	jal	DG_SetPos2
	addiu	$5,$19,40
	lui	$4,%hi(njp_front_probe)
	addiu	$4,$4,%lo(njp_front_probe)
	addiu	$5,$29,16
	jal	DG_PutVector
	addiu	$6,$0,3
	lw	$2,2524($19)
	nop
	blez	$2,$Lnjp_800C5A70_1
	addu	$16,$0,$0
	addiu	$18,$29,16
	addu	$17,$19,$0
	addu	$5,$18,$0
$Lnjp_800C5A70_0:
	addiu	$18,$18,8
	lw	$4,2512($17)
	jal	GM_MoveTarget
	addiu	$17,$17,4
	lw	$2,2524($19)
	addiu	$16,$16,1
	slt	$2,$16,$2
	bne	$2,$0,$Lnjp_800C5A70_0
	addu	$5,$18,$0
$Lnjp_800C5A70_1:
	jal	SetRotMatrix
	addiu	$4,$29,40
	lw	$31,88($29)
	lw	$19,84($29)
	lw	$18,80($29)
	lw	$17,76($29)
	lw	$16,72($29)
	jr	$31
	addiu	$29,$29,96
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5B18
njp_800C5B18:
	addiu	$29,$29,-72
	sw	$20,64($29)
	addu	$20,$4,$0
	sw	$19,60($29)
	addu	$19,$0,$0
	lui	$4,0x80
	sw	$31,68($29)
	sw	$18,56($29)
	sw	$17,52($29)
	jal	njp_GM_CheckPlayerStatusFlag
	sw	$16,48($29)
	bne	$2,$0,$Lnjp_800C5B18_3
	addu	$2,$19,$0
	lw	$2,2524($20)
	nop
	slt	$2,$19,$2
	beq	$2,$0,$Lnjp_800C5B18_2
	addu	$18,$0,$0
	addu	$17,$20,$0
$Lnjp_800C5B18_0:
	lw	$16,2512($17)
	nop
	lhu	$5,6($16)
	nop
	andi	$2,$5,0x4
	beq	$2,$0,$Lnjp_800C5B18_1
	addiu	$2,$0,1
	lh	$3,62($16)
	nop
	bne	$3,$2,$Lnjp_800C5B18_1
	addiu	$4,$29,16
	andi	$2,$5,0xfffb
	sh	$2,6($16)
	addiu	$2,$0,1024
	sh	$0,62($16)
	jal	ReadRotMatrix
	sh	$2,38($16)
	addiu	$19,$19,1
	lh	$2,8($16)
	addiu	$4,$20,32
	sw	$2,36($29)
	lh	$2,10($16)
	addiu	$5,$0,211
	sw	$2,40($29)
	lh	$2,12($16)
	addiu	$6,$0,1
	jal	GM_SeSetMode
	sw	$2,44($29)
	addiu	$4,$29,16
	jal	NewSpark
	addiu	$5,$0,1
$Lnjp_800C5B18_1:
	lw	$2,2524($20)
	addiu	$18,$18,1
	slt	$2,$18,$2
	bne	$2,$0,$Lnjp_800C5B18_0
	addiu	$17,$17,4
$Lnjp_800C5B18_2:
	addu	$2,$19,$0
$Lnjp_800C5B18_3:
	lw	$31,68($29)
	lw	$20,64($29)
	lw	$19,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5C18
njp_800C5C18:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$0,2
	sw	$31,20($29)
	jal	njp_800C5A70
	sw	$2,2532($16)
	jal	njp_800C5B18
	addu	$4,$16,$0
	beq	$2,$0,$Lnjp_800C5C18_1
	nop
	lhu	$2,2452($16)
	nop
	addiu	$2,$2,1
	sh	$2,2452($16)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C5C18_0
	addu	$4,$16,$0
	sh	$0,2452($16)
$Lnjp_800C5C18_0:
	lh	$5,2452($16)
	addu	$6,$0,$0
	jal	njp_SetAction_8004E22C
	addiu	$5,$5,16
$Lnjp_800C5C18_1:
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5C18_2
	addu	$4,$16,$0
	addiu	$5,$0,3
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
	addiu	$2,$0,-1
	sh	$2,2452($16)
$Lnjp_800C5C18_2:
	lw	$2,2320($16)
	nop
	lhu	$2,0($2)
	nop
	andi	$2,$2,0x20
	bne	$2,$0,$Lnjp_800C5C18_3
	lui	$3,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_800C4AF0)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_800C4AF0)
	addu	$4,$16,$0
	lui	$5,0x2000
	jal	njp_sna_clear_flags1_8004E308
	ori	$5,$5,0x4
	j	$Lnjp_800C5C18_4
	addiu	$4,$0,2048
$Lnjp_800C5C18_3:
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($3)
	nop
	bltz	$2,$Lnjp_800C5C18_5
	nop
	lhu	$2,%lo(njp_gSnaMoveDir_800ABBA4)($3)
	lhu	$3,2454($16)
	sh	$2,110($16)
	addiu	$2,$3,1
	sll	$3,$3,16
	sra	$3,$3,16
	slti	$3,$3,2
	bne	$3,$0,$Lnjp_800C5C18_5
	sh	$2,2454($16)
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_800C4A90)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_800C4A90)
	addiu	$4,$0,16
$Lnjp_800C5C18_4:
	jal	njp_GM_SetPlayerStatusFlag
	nop
	jal	njp_FreeTargets
	addu	$4,$16,$0
$Lnjp_800C5C18_5:
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
	lui	$5,%hi(njp_800C54EC)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C54EC)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C5E9C
njp_800C5E9C:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$2,$0,2
	sw	$31,20($29)
	sw	$2,2532($16)
	slti	$2,$5,3
	bne	$2,$0,$Lnjp_800C5E9C_1
	addiu	$2,$0,16
	bne	$5,$2,$Lnjp_800C5E9C_0
	nop
	jal	njp_sna_clear_invuln_8004F2EC
	nop
$Lnjp_800C5E9C_0:
	addu	$4,$16,$0
	lui	$5,%hi(njp_stru_8009EFD4)
	jal	njp_sna_800C3898
	addiu	$5,$5,%lo(njp_stru_8009EFD4)
	jal	njp_sna_800C399C
	addu	$4,$16,$0
	lh	$2,182($16)
	nop
	beq	$2,$0,$Lnjp_800C5E9C_1
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C5E9C_1:
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
	.globl	njp_800C5F20
njp_800C5F20:
	addiu	$29,$29,-40
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addu	$17,$5,$0
	addiu	$2,$17,-5
	sltiu	$2,$2,11
	sw	$31,32($29)
	sw	$19,28($29)
	beq	$2,$0,$Lnjp_800C5F20_0
	sw	$18,24($29)
	addiu	$2,$0,2
	sw	$2,2532($16)
$Lnjp_800C5F20_0:
	bne	$17,$0,$Lnjp_800C5F20_1
	slti	$19,$17,10
	addu	$4,$16,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4096
	sh	$0,2442($16)
	slti	$19,$17,10
$Lnjp_800C5F20_1:
	beq	$19,$0,$Lnjp_800C5F20_2
	addu	$4,$16,$0
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	njp_sna_800C35BC
	addiu	$6,$0,96
	lbu	$2,117($16)
	sw	$0,1944($16)
	ori	$2,$2,0x8
	sb	$2,117($16)
$Lnjp_800C5F20_2:
	addiu	$18,$0,10
	bne	$17,$18,$Lnjp_800C5F20_3
	slti	$2,$17,3
	addu	$4,$16,$0
	lbu	$2,117($16)
	addiu	$5,$0,4096
	andi	$2,$2,0xf7
	jal	njp_sna_clear_flags1_8004E308
	sb	$2,117($16)
	slti	$2,$17,3
$Lnjp_800C5F20_3:
	bne	$2,$0,$Lnjp_800C5F20_9
	nop
	bne	$17,$18,$Lnjp_800C5F20_4
	nop
	jal	njp_sna_clear_invuln_8004F2EC
	addu	$4,$16,$0
$Lnjp_800C5F20_4:
	bne	$19,$0,$Lnjp_800C5F20_5
	nop
	lh	$2,2454($16)
	nop
	bne	$2,$0,$Lnjp_800C5F20_5
	nop
	lbu	$2,119($16)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$Lnjp_800C5F20_5
	nop
	addiu	$4,$16,32
	addiu	$5,$0,210
	jal	GM_SeSetMode
	addiu	$6,$0,1
	addiu	$2,$0,1
	sh	$2,2454($16)
$Lnjp_800C5F20_5:
	addu	$4,$16,$0
	lui	$5,%hi(njp_stru_8009EFD4+16)
	jal	njp_sna_800C3898
	addiu	$5,$5,%lo(njp_stru_8009EFD4+16)
	jal	njp_sna_800C399C
	addu	$4,$16,$0
	lh	$2,182($16)
	nop
	bne	$2,$0,$Lnjp_800C5F20_6
	addiu	$2,$0,13
	lh	$3,170($16)
	nop
	bne	$3,$2,$Lnjp_800C5F20_9
	nop
	lh	$2,390($16)
	nop
	slti	$2,$2,16
	bne	$2,$0,$Lnjp_800C5F20_9
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C5F20_9
	nop
$Lnjp_800C5F20_6:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,2048
	addu	$4,$16,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C5F20_7
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_run_begin_80053B88)
	j	$Lnjp_800C5F20_8
	addiu	$5,$5,%lo(njp_sna_anim_run_begin_80053B88)
$Lnjp_800C5F20_7:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
$Lnjp_800C5F20_8:
	jal	njp_sna_start_anim_8004E1F4
	nop
$Lnjp_800C5F20_9:
	lw	$31,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
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
