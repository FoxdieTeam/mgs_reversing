	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3898
njp_800C3898:
	addiu	$29,$29,-168
	sw	$18,160($29)
	addu	$18,$4,$0
	sw	$16,152($29)
	addu	$16,$5,$0
	sw	$17,156($29)
	addiu	$17,$29,120
	sw	$31,164($29)
	jal	ReadRotMatrix
	addu	$4,$17,$0
	lw	$4,156($18)
	jal	DG_SetPos
	addiu	$4,$4,440
	addu	$4,$16,$0
	addiu	$16,$29,96
	addu	$5,$16,$0
	jal	DG_PutVector
	addiu	$6,$0,2
	jal	SetRotMatrix
	addu	$4,$17,$0
	addu	$4,$16,$0
	addiu	$16,$29,104
	addu	$5,$16,$0
	lw	$3,76($18)
	addiu	$2,$0,1
	sw	$2,16($29)
	lw	$6,0($3)
	jal	GM_OnlineTargetCheck
	addu	$7,$16,$0
	beq	$2,$0,$Lnjp_800C3898_0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	addiu	$7,$29,112
	addiu	$2,$0,100
	sh	$2,116($29)
	sh	$2,114($29)
	jal	GM_SetTarget
	sh	$2,112($29)
	addiu	$4,$29,24
	addiu	$5,$0,1
	addu	$6,$5,$0
	addiu	$7,$0,256
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addu	$5,$16,$0
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lh	$2,104($29)
	lh	$3,106($29)
	lh	$4,108($29)
	sw	$2,140($29)
	sw	$3,144($29)
	sw	$4,148($29)
$Lnjp_800C3898_0:
	lw	$31,164($29)
	lw	$18,160($29)
	lw	$17,156($29)
	lw	$16,152($29)
	jr	$31
	addiu	$29,$29,168
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C399C
njp_800C399C:
	addiu	$29,$29,-112
	sw	$16,104($29)
	addu	$16,$4,$0
	addiu	$4,$29,24
	addiu	$5,$0,4
	addiu	$6,$0,1
	sw	$31,108($29)
	lw	$2,2200($16)
	nop
	lwl	$3,19($2)
	lwr	$3,16($2)
	lwl	$8,23($2)
	lwr	$8,20($2)
	swl	$3,99($29)
	swr	$3,96($29)
	swl	$8,103($29)
	swr	$8,100($29)
	jal	GM_SetTarget
	addiu	$7,$29,96
	addiu	$4,$29,24
	addiu	$5,$0,1
	addu	$6,$5,$0
	addiu	$7,$0,256
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addiu	$4,$29,24
	jal	GM_MoveTarget
	addiu	$5,$16,32
	jal	GM_PowerTarget
	addiu	$4,$29,24
	lw	$31,108($29)
	lw	$16,104($29)
	jr	$31
	addiu	$29,$29,112
	.set	macro
	.set	reorder
	.set	at
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
	lui	$5,%hi(njp_800C6AC0)
	j	$Lnjp_800C3A30_6
	addiu	$5,$5,%lo(njp_800C6AC0)
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3B98
njp_800C3B98:
	lui	$2,%hi(njp_bss_44)
	lw	$2,%lo(njp_bss_44)($2)
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$2,$0,$Lnjp_800C3B98_0
	sw	$31,20($29)
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C3B98_0
	addiu	$2,$0,450
	sh	$2,2436($16)
	lui	$4,0x3
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x10
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	addu	$4,$16,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	GM_ExitBehindCamera
	nop
	j	$Lnjp_800C3B98_1
	addiu	$2,$0,1
$Lnjp_800C3B98_0:
	addu	$2,$0,$0
$Lnjp_800C3B98_1:
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
	.globl	njp_800C3C1C
njp_800C3C1C:
	addiu	$29,$29,-48
	sw	$18,32($29)
	addu	$18,$4,$0
	lui	$5,0x8
	sw	$31,40($29)
	sw	$19,36($29)
	sw	$17,28($29)
	jal	njp_sna_check_flags1_8004E31C
	sw	$16,24($29)
	bne	$2,$0,$Lnjp_800C3C1C_3
	nop
	lhu	$4,80($18)
	jal	GV_ReceiveMessage
	addiu	$5,$29,16
	beq	$2,$0,$Lnjp_800C3C1C_3
	addu	$16,$2,$0
	lw	$3,1952($18)
	nop
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,2
	addiu	$2,$2,1956
	addu	$17,$18,$2
	sll	$2,$16,2
	addu	$2,$2,$16
	lw	$3,16($29)
	sll	$2,$2,2
	addu	$3,$3,$2
	addiu	$3,$3,-20
	blez	$16,$Lnjp_800C3C1C_3
	sw	$3,16($29)
	addiu	$19,$0,8
$Lnjp_800C3C1C_0:
	lw	$2,1952($18)
	nop
	beq	$2,$19,$Lnjp_800C3C1C_3
	nop
	lw	$2,16($29)
	nop
	lhu	$3,4($2)
	ori	$2,$0,0x937a
	beq	$3,$2,$Lnjp_800C3C1C_1
	addiu	$2,$0,28923
	beq	$3,$2,$Lnjp_800C3C1C_1
	ori	$2,$0,0xbe0a
	bne	$3,$2,$Lnjp_800C3C1C_2
	nop
$Lnjp_800C3C1C_1:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4
	bne	$2,$0,$Lnjp_800C3C1C_2
	nop
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,4
$Lnjp_800C3C1C_2:
	lw	$2,16($29)
	addiu	$16,$16,-1
	lwl	$6,3($2)
	lwr	$6,0($2)
	lwl	$7,7($2)
	lwr	$7,4($2)
	lwl	$8,11($2)
	lwr	$8,8($2)
	lwl	$9,15($2)
	lwr	$9,12($2)
	swl	$6,3($17)
	swr	$6,0($17)
	swl	$7,7($17)
	swr	$7,4($17)
	swl	$8,11($17)
	swr	$8,8($17)
	swl	$9,15($17)
	swr	$9,12($17)
	lwl	$6,19($2)
	lwr	$6,16($2)
	nop
	swl	$6,19($17)
	swr	$6,16($17)
	addiu	$17,$17,20
	lw	$2,16($29)
	lw	$3,1952($18)
	addiu	$2,$2,-20
	addiu	$3,$3,1
	sw	$2,16($29)
	bgtz	$16,$Lnjp_800C3C1C_0
	sw	$3,1952($18)
$Lnjp_800C3C1C_3:
	lw	$31,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C3D84
njp_800C3D84:
	addiu	$29,$29,-88
	sw	$18,56($29)
	addu	$18,$4,$0
	sw	$31,84($29)
	sw	$30,80($29)
	sw	$23,76($29)
	sw	$22,72($29)
	sw	$21,68($29)
	sw	$20,64($29)
	sw	$19,60($29)
	sw	$17,52($29)
	sw	$16,48($29)
	lw	$2,1952($18)
	nop
	beq	$2,$0,$Lnjp_800C3D84_24
	nop
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x2
	bne	$2,$0,$Lnjp_800C3D84_24
	addiu	$23,$18,1956
	sw	$0,40($29)
	lw	$22,1952($18)
	nop
	blez	$22,$Lnjp_800C3D84_23
	addu	$30,$23,$0
	addiu	$17,$18,1974
$Lnjp_800C3D84_0:
	lhu	$3,-14($17)
	addiu	$2,$0,25270
	beq	$3,$2,$Lnjp_800C3D84_20
	slti	$2,$3,25271
	beq	$2,$0,$Lnjp_800C3D84_2
	addiu	$2,$0,12835
	beq	$3,$2,$Lnjp_800C3D84_17
	slti	$2,$3,12836
	beq	$2,$0,$Lnjp_800C3D84_1
	addiu	$2,$0,9600
	beq	$3,$2,$Lnjp_800C3D84_18
	nop
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_1:
	addiu	$2,$0,24203
	beq	$3,$2,$Lnjp_800C3D84_15
	addu	$4,$18,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_2:
	ori	$2,$0,0x9a1f
	beq	$3,$2,$Lnjp_800C3D84_16
	slt	$2,$2,$3
	bne	$2,$0,$Lnjp_800C3D84_3
	ori	$2,$0,0xaf6a
	ori	$2,$0,0x937a
	beq	$3,$2,$Lnjp_800C3D84_4
	addu	$20,$0,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_3:
	beq	$3,$2,$Lnjp_800C3D84_19
	ori	$2,$0,0xbe0a
	beq	$3,$2,$Lnjp_800C3D84_4
	addiu	$20,$0,1
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_4:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C3D84_21
	addu	$21,$0,$0
	lhu	$19,0($17)
	lhu	$2,-12($17)
	addiu	$16,$18,2368
	sh	$0,0($17)
	sh	$2,2368($18)
	addiu	$2,$0,-1
	sh	$2,2($16)
	sh	$2,4($16)
	sh	$2,6($16)
	slti	$2,$19,3
	bne	$2,$0,$Lnjp_800C3D84_5
	sh	$0,8($16)
	lhu	$2,-10($17)
	nop
	sh	$2,2($16)
$Lnjp_800C3D84_5:
	slti	$2,$19,4
	bne	$2,$0,$Lnjp_800C3D84_6
	slti	$2,$19,5
	lhu	$2,-8($17)
	nop
	sh	$2,4($16)
	slti	$2,$19,5
$Lnjp_800C3D84_6:
	bne	$2,$0,$Lnjp_800C3D84_7
	slti	$2,$19,6
	lhu	$2,-6($17)
	nop
	sh	$2,6($16)
	slti	$2,$19,6
$Lnjp_800C3D84_7:
	bne	$2,$0,$Lnjp_800C3D84_8
	nop
	lhu	$3,-4($17)
	nop
	sll	$2,$3,16
	sra	$21,$2,16
	sh	$3,8($16)
$Lnjp_800C3D84_8:
	jal	njp_sna_act_unk_helper4_8004FA3C
	nop
	beq	$2,$0,$Lnjp_800C3D84_9
	nop
	bne	$20,$0,$Lnjp_800C3D84_9
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,4
	sh	$0,0($17)
	lui	$4,%hi(njp_str_47F4)
	jal	printf
	addiu	$4,$4,%lo(njp_str_47F4)
	j	$Lnjp_800C3D84_21
	nop
$Lnjp_800C3D84_9:
	beq	$20,$0,$Lnjp_800C3D84_10
	sh	$0,14($16)
	addiu	$2,$0,1
	sh	$2,14($16)
$Lnjp_800C3D84_10:
	andi	$2,$21,0x80
	bne	$2,$0,$Lnjp_800C3D84_11
	andi	$2,$21,0x4
	lhu	$2,2486($18)
	nop
	beq	$2,$0,$Lnjp_800C3D84_21
	addiu	$4,$18,156
	addiu	$5,$18,384
	addu	$6,$2,$0
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,32
	sw	$2,20($29)
	addiu	$2,$18,1688
	addiu	$7,$18,464
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	andi	$2,$21,0x4
$Lnjp_800C3D84_11:
	beq	$2,$0,$Lnjp_800C3D84_12
	slti	$2,$19,7
	bne	$2,$0,$Lnjp_800C3D84_21
	nop
	lhu	$2,34($18)
	lhu	$3,-2($17)
	j	$Lnjp_800C3D84_13
	subu	$2,$2,$3
$Lnjp_800C3D84_12:
	lhu	$2,152($18)
$Lnjp_800C3D84_13:
	nop
	sh	$2,10($16)
	andi	$2,$21,0x10
	beq	$2,$0,$Lnjp_800C3D84_14
	addiu	$2,$0,1
	lbu	$2,117($18)
	nop
	ori	$2,$2,0x2
	sb	$2,117($18)
	addiu	$2,$0,1
$Lnjp_800C3D84_14:
	sh	$2,12($16)
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C5838)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C5838)
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,4
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x800
	j	$Lnjp_800C3D84_21
	nop
$Lnjp_800C3D84_15:
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x4
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_16:
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x4
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_17:
	jal	GV_DestroyActor
	addu	$4,$18,$0
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_18:
	jal	njp_GM_ClearPlayerStatusFlag
	lui	$4,0x2000
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_19:
	jal	njp_GM_SetPlayerStatusFlag
	lui	$4,0x2000
	j	$Lnjp_800C3D84_21
	sh	$0,0($17)
$Lnjp_800C3D84_20:
	lhu	$2,-12($17)
	nop
	sh	$2,32($18)
	lhu	$2,-10($17)
	nop
	sh	$2,34($18)
	lhu	$2,-8($17)
	nop
	sh	$2,36($18)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,103($18)
	swr	$8,100($18)
	swl	$9,107($18)
	swr	$9,104($18)
	lw	$2,76($18)
	addiu	$5,$18,32
	lw	$4,8($2)
	jal	njp_sub_8004E588
	addiu	$6,$29,32
	lhu	$2,32($29)
	nop
	sh	$2,152($18)
	lhu	$2,36($29)
	nop
	sh	$2,154($18)
	sh	$0,0($17)
$Lnjp_800C3D84_21:
	lhu	$2,0($17)
	nop
	beq	$2,$0,$Lnjp_800C3D84_22
	nop
	lwl	$8,3($23)
	lwr	$8,0($23)
	lwl	$9,7($23)
	lwr	$9,4($23)
	lwl	$10,11($23)
	lwr	$10,8($23)
	lwl	$11,15($23)
	lwr	$11,12($23)
	swl	$8,3($30)
	swr	$8,0($30)
	swl	$9,7($30)
	swr	$9,4($30)
	swl	$10,11($30)
	swr	$10,8($30)
	swl	$11,15($30)
	swr	$11,12($30)
	lwl	$8,19($23)
	lwr	$8,16($23)
	nop
	swl	$8,19($30)
	swr	$8,16($30)
	lw	$8,40($29)
	addiu	$30,$30,20
	addiu	$8,$8,1
	sw	$8,40($29)
$Lnjp_800C3D84_22:
	addiu	$22,$22,-1
	addiu	$17,$17,20
	bgtz	$22,$Lnjp_800C3D84_0
	addiu	$23,$23,20
$Lnjp_800C3D84_23:
	lw	$9,40($29)
	nop
	sw	$9,1952($18)
$Lnjp_800C3D84_24:
	lw	$31,84($29)
	lw	$30,80($29)
	lw	$23,76($29)
	lw	$22,72($29)
	lw	$21,68($29)
	lw	$20,64($29)
	lw	$19,60($29)
	lw	$18,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,88
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C41B4
njp_800C41B4:
	lhu	$2,6($4)
	sh	$0,40($4)
	sh	$0,42($4)
	andi	$2,$2,0xff7b
	sh	$2,6($4)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$7,$2,%lo(DG_ZeroVector)
	lwl	$3,3($7)
	lwr	$3,0($7)
	lwl	$5,7($7)
	lwr	$5,4($7)
	swl	$3,47($4)
	swr	$3,44($4)
	swl	$5,51($4)
	swr	$5,48($4)
	addiu	$2,$0,-1
	sw	$2,68($4)
	jr	$31
	sh	$0,62($4)
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4200
njp_800C4200:
	addiu	$29,$29,-24
	bne	$5,$0,$Lnjp_800C4200_0
	sw	$31,16($29)
	lui	$2,%hi(njp_800C44CC)
	addiu	$2,$2,%lo(njp_800C44CC)
	sw	$2,2340($4)
	lui	$2,%hi(njp_800C6900)
	addiu	$2,$2,%lo(njp_800C6900)
	addiu	$5,$0,2
	addiu	$6,$0,4
	sh	$0,2434($4)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($4)
$Lnjp_800C4200_0:
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
	.globl	njp_800C4244
njp_800C4244:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C4244_0
	sw	$31,20($29)
	addiu	$4,$0,16
	lui	$2,%hi(njp_800C45CC)
	addiu	$2,$2,%lo(njp_800C45CC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6900)
	addiu	$2,$2,%lo(njp_800C6900)
	jal	njp_GM_SetPlayerStatusFlag
	sw	$2,2344($16)
	addu	$4,$16,$0
	addiu	$5,$0,5
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C4244_0:
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
	.globl	njp_800C4298
njp_800C4298:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	bne	$5,$0,$Lnjp_800C4298_2
	sw	$17,20($29)
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	bne	$2,$0,$Lnjp_800C4298_1
	addu	$4,$16,$0
	addiu	$17,$0,7
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x100
	beq	$2,$0,$Lnjp_800C4298_0
	addiu	$4,$16,32
	addiu	$17,$0,183
$Lnjp_800C4298_0:
	jal	GM_SeSet
	addu	$5,$17,$0
	lui	$2,%hi(njp_bss_56)
	lhu	$2,%lo(njp_bss_56)($2)
	lui	$4,0x1
	addiu	$2,$2,-2048
	jal	njp_GM_SetPlayerStatusFlag
	sh	$2,110($16)
	addu	$4,$16,$0
$Lnjp_800C4298_1:
	addiu	$5,$0,21
	addiu	$2,$0,300
	sh	$2,2436($16)
	lui	$2,%hi(njp_800C4750)
	addiu	$2,$2,%lo(njp_800C4750)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6994)
	addiu	$2,$2,%lo(njp_800C6994)
	addiu	$6,$0,4
	sh	$0,2434($16)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($16)
$Lnjp_800C4298_2:
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lh	$2,2454($16)
	nop
	slti	$2,$2,8
	beq	$2,$0,$Lnjp_800C4298_5
	lui	$2,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_52)($2)
	nop
	beq	$4,$0,$Lnjp_800C4298_5
	nop
	lh	$3,0($4)
	nop
	bgez	$3,$Lnjp_800C4298_3
	nop
	addiu	$3,$3,7
$Lnjp_800C4298_3:
	lhu	$2,100($16)
	sra	$3,$3,3
	addu	$2,$2,$3
	sh	$2,100($16)
	lh	$2,4($4)
	nop
	bgez	$2,$Lnjp_800C4298_4
	nop
	addiu	$2,$2,7
$Lnjp_800C4298_4:
	sra	$2,$2,3
	lhu	$3,104($16)
	lhu	$4,2454($16)
	addu	$3,$3,$2
	addiu	$4,$4,1
	sh	$3,104($16)
	sh	$4,2454($16)
$Lnjp_800C4298_5:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C43CC
njp_800C43CC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	bne	$5,$0,$Lnjp_800C43CC_1
	sw	$31,20($29)
	lui	$4,0x1
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x10
	lui	$2,%hi(njp_800C47EC)
	addiu	$2,$2,%lo(njp_800C47EC)
	sw	$2,2340($16)
	lui	$2,%hi(njp_800C6994)
	lh	$3,2480($16)
	addiu	$2,$2,%lo(njp_800C6994)
	sw	$2,2344($16)
	addiu	$2,$0,2
	bne	$3,$2,$Lnjp_800C43CC_0
	addiu	$5,$0,23
	addiu	$5,$0,22
$Lnjp_800C43CC_0:
	addu	$4,$16,$0
	addiu	$2,$0,300
	addiu	$6,$0,4
	sh	$2,2436($16)
	jal	njp_SetAction_8004E22C
	sh	$0,2480($16)
	lui	$2,%hi(njp_bss_56)
	lhu	$2,%lo(njp_bss_56)($2)
	nop
	addiu	$2,$2,-2048
	sh	$2,110($16)
$Lnjp_800C43CC_1:
	lh	$2,2454($16)
	nop
	slti	$2,$2,8
	beq	$2,$0,$Lnjp_800C43CC_4
	lui	$2,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_52)($2)
	nop
	beq	$4,$0,$Lnjp_800C43CC_4
	nop
	lh	$3,0($4)
	nop
	bgez	$3,$Lnjp_800C43CC_2
	nop
	addiu	$3,$3,7
$Lnjp_800C43CC_2:
	lhu	$2,100($16)
	sra	$3,$3,3
	addu	$2,$2,$3
	sh	$2,100($16)
	lh	$2,4($4)
	nop
	bgez	$2,$Lnjp_800C43CC_3
	nop
	addiu	$2,$2,7
$Lnjp_800C43CC_3:
	sra	$2,$2,3
	lhu	$3,104($16)
	lhu	$4,2454($16)
	addu	$3,$3,$2
	addiu	$4,$4,1
	sh	$3,104($16)
	sh	$4,2454($16)
$Lnjp_800C43CC_4:
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
	.globl	njp_800C44CC
njp_800C44CC:
	addiu	$29,$29,-24
	sw	$16,16($29)
	sw	$31,20($29)
	jal	njp_800C3A30
	addu	$16,$4,$0
	bne	$2,$0,$Lnjp_800C44CC_7
	nop
	lh	$2,2452($16)
	lhu	$3,2452($16)
	blez	$2,$Lnjp_800C44CC_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C44CC_0:
	lh	$2,2452($16)
	nop
	bne	$2,$0,$Lnjp_800C44CC_7
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$2,$Lnjp_800C44CC_7
	lui	$2,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	beq	$3,$2,$Lnjp_800C44CC_1
	addu	$4,$16,$0
	beq	$3,$0,$Lnjp_800C44CC_2
	addiu	$2,$0,2
	lw	$3,1948($16)
	nop
	bne	$3,$2,$Lnjp_800C44CC_3
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	addu	$4,$16,$0
$Lnjp_800C44CC_1:
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C44CC_7
	nop
$Lnjp_800C44CC_2:
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
$Lnjp_800C44CC_3:
	lh	$4,110($16)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	jal	GV_DiffDirAbs
	nop
	addu	$3,$2,$0
	slti	$2,$3,257
	bne	$2,$0,$Lnjp_800C44CC_5
	addu	$4,$16,$0
	addu	$2,$3,$0
	bgez	$2,$Lnjp_800C44CC_4
	nop
	addiu	$2,$2,1023
$Lnjp_800C44CC_4:
	sra	$2,$2,10
	addiu	$2,$2,1
	j	$Lnjp_800C44CC_6
	sh	$2,2452($16)
$Lnjp_800C44CC_5:
	lui	$5,%hi(njp_800C4244)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4244)
$Lnjp_800C44CC_6:
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lhu	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	sh	$2,110($16)
$Lnjp_800C44CC_7:
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
	.globl	njp_800C45CC
njp_800C45CC:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,24($29)
	jal	njp_800C3A30
	sw	$16,16($29)
	bne	$2,$0,$Lnjp_800C45CC_9
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$2,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$2,$Lnjp_800C45CC_0
	lui	$2,%hi(njp_bss_44)
	lhu	$2,2454($17)
	nop
	addiu	$2,$2,1
	sh	$2,2454($17)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,5
	bne	$2,$0,$Lnjp_800C45CC_1
	lui	$2,%hi(njp_bss_44)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	j	$Lnjp_800C45CC_9
	nop
$Lnjp_800C45CC_0:
	sh	$0,2454($17)
$Lnjp_800C45CC_1:
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	beq	$3,$2,$Lnjp_800C45CC_2
	nop
	beq	$3,$0,$Lnjp_800C45CC_3
	addiu	$2,$0,2
	lw	$3,1948($17)
	nop
	bne	$3,$2,$Lnjp_800C45CC_3
	nop
$Lnjp_800C45CC_2:
	lhu	$2,2452($17)
	nop
	addiu	$2,$2,1
	sh	$2,2452($17)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,3
	bne	$2,$0,$Lnjp_800C45CC_4
	nop
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C45CC_9
	nop
$Lnjp_800C45CC_3:
	sh	$0,2452($17)
$Lnjp_800C45CC_4:
	lh	$2,2452($17)
	nop
	bne	$2,$0,$Lnjp_800C45CC_5
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	lw	$5,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bltz	$5,$Lnjp_800C45CC_6
	nop
	jal	njp_sub_8004E4C0
	addu	$4,$17,$0
	j	$Lnjp_800C45CC_7
	addu	$16,$2,$0
$Lnjp_800C45CC_5:
	lw	$16,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	nop
	bgez	$16,$Lnjp_800C45CC_7
	nop
$Lnjp_800C45CC_6:
	lh	$16,110($17)
$Lnjp_800C45CC_7:
	lh	$4,110($17)
	jal	GV_DiffDirAbs
	addu	$5,$16,$0
	slti	$2,$2,1049
	bne	$2,$0,$Lnjp_800C45CC_8
	addu	$4,$17,$0
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$17,$0
	lui	$5,%hi(njp_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4200)
	j	$Lnjp_800C45CC_9
	sh	$16,110($17)
$Lnjp_800C45CC_8:
	sh	$16,110($17)
	jal	njp_sub_8004EA50
	addu	$5,$16,$0
$Lnjp_800C45CC_9:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C4750
njp_800C4750:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C4750_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C4750_0:
	jal	njp_800C3B98
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C4750_3
	lui	$4,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($4)
	addiu	$2,$0,2
	beq	$3,$2,$Lnjp_800C4750_1
	addiu	$2,$0,4
	bne	$3,$2,$Lnjp_800C4750_2
	nop
$Lnjp_800C4750_1:
	lhu	$2,%lo(njp_bss_44)($4)
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C43CC)
	addiu	$5,$5,%lo(njp_800C43CC)
	jal	njp_sna_start_anim_8004E1F4
	sh	$2,2480($16)
$Lnjp_800C4750_2:
	lui	$4,%hi(njp_bss_56)
	lw	$2,%lo(njp_bss_56)($4)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	beq	$2,$3,$Lnjp_800C4750_3
	nop
	lhu	$2,%lo(njp_bss_56)($4)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
$Lnjp_800C4750_3:
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
	.globl	njp_800C47EC
njp_800C47EC:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lh	$2,2452($16)
	lhu	$3,2452($16)
	beq	$2,$0,$Lnjp_800C47EC_0
	addiu	$2,$3,-1
	sh	$2,2452($16)
$Lnjp_800C47EC_0:
	jal	njp_800C3B98
	addu	$4,$16,$0
	bne	$2,$0,$Lnjp_800C47EC_5
	nop
	lw	$2,76($16)
	nop
	lw	$4,8($2)
	jal	GM_CheckBehindCamera
	addiu	$5,$16,32
	lui	$2,%hi(njp_bss_44)
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C47EC_1
	lui	$5,%hi(njp_bss_56)
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	lui	$5,%hi(njp_800C4298)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C4298)
	j	$Lnjp_800C47EC_5
	nop
$Lnjp_800C47EC_1:
	lw	$2,%lo(njp_bss_56)($5)
	lh	$3,42($16)
	addiu	$2,$2,-2048
	bne	$2,$3,$Lnjp_800C47EC_2
	lui	$2,%hi(njp_bss_48)
	lui	$3,%hi(njp_bss_52)
	lw	$4,%lo(njp_bss_48)($2)
	lw	$2,%lo(njp_bss_52)($3)
	nop
	beq	$4,$2,$Lnjp_800C47EC_3
	lui	$2,%hi(njp_bss_44)
$Lnjp_800C47EC_2:
	lhu	$2,%lo(njp_bss_56)($5)
	sh	$0,2454($16)
	addiu	$2,$2,-2048
	sh	$2,110($16)
	lui	$2,%hi(njp_bss_44)
$Lnjp_800C47EC_3:
	lw	$3,%lo(njp_bss_44)($2)
	addiu	$2,$0,2
	bne	$3,$2,$Lnjp_800C47EC_4
	addiu	$17,$0,23
	addiu	$17,$0,22
$Lnjp_800C47EC_4:
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	njp_SetAction_8004E22C
	addiu	$6,$0,4
$Lnjp_800C47EC_5:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
njp_str_47F4:
	.ascii	"force act cancel\n"
	.byte	0
	.align	2
njp_str_4808:
	.ascii	"pos %d %d %d\n"
	.byte	0
	.align	2
njp_str_4818:
	.ascii	"turn %d %d %d\n"
	.byte	0
	.align	2
njp_str_4828:
	.ascii	"ceil floor %d %d\n"
	.byte	0
	.align	2
njp_str_483C:
	.ascii	"status %4x\n"
	.byte	0
	.align	2
njp_str_4848:
	.ascii	"item %d\n"
	.byte	0
	.align	2
njp_str_4854:
	.ascii	"flag %4x\n"
	.byte	0
	.align	2
njp_str_4860:
	.ascii	"stance %d\n"
	.byte	0
	.align	2
njp_str_486C:
	.ascii	"pad %x\n"
	.byte	0
	.align	2
njp_str_4874:
	.ascii	"padto %d\n"
	.byte	0
	.align	2
njp_str_4880:
	.ascii	"trap check %d\n"
	.byte	0
	.align	2
njp_str_4890:
	.ascii	"kaze \n"
	.byte	0
	.text
