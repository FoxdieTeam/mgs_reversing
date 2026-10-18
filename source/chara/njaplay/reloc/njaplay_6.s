	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6CA4
njp_800C6CA4:
	addiu	$29,$29,-64
	sw	$17,52($29)
	addu	$17,$4,$0
	addiu	$2,$5,-19
	sltiu	$2,$2,3
	sw	$31,56($29)
	beq	$2,$0,$Lnjp_800C6CA4_0
	sw	$16,48($29)
	addiu	$2,$0,2
	sw	$2,2532($17)
$Lnjp_800C6CA4_0:
	lw	$16,2276($17)
	bne	$5,$0,$Lnjp_800C6CA4_1
	lui	$2,%hi(dword_800AB9D4)
	addu	$4,$17,$0
	addiu	$5,$0,25
	addiu	$6,$0,4
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	sw	$2,2340($17)
	jal	njp_SetAction_8004E22C
	sw	$2,2344($17)
	addiu	$2,$0,25
	sh	$2,62($16)
	sh	$0,2480($17)
	lui	$2,%hi(dword_800AB9D4)
$Lnjp_800C6CA4_1:
	lw	$3,%lo(dword_800AB9D4)($2)
	addiu	$2,$0,22
	bne	$3,$2,$Lnjp_800C6CA4_2
	addiu	$4,$16,8
	addiu	$5,$17,40
	lhu	$2,42($16)
	addiu	$3,$0,5
	sh	$3,40($16)
	addiu	$2,$2,-1
	jal	DG_SetPos2
	sh	$2,42($16)
	jal	ReadRotMatrix
	addiu	$4,$29,16
	addiu	$4,$29,16
	jal	NewBlood
	addiu	$5,$0,2
	lui	$4,%hi(njp_dword_8009EF24)
	addiu	$4,$4,%lo(njp_dword_8009EF24)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EF2C)
	addiu	$4,$4,%lo(njp_dword_8009EF2C)
	jal	NewPadVibration
	addiu	$5,$0,2
	addiu	$4,$17,32
	addiu	$5,$0,212
	jal	GM_SeSetMode
	addiu	$6,$0,1
$Lnjp_800C6CA4_2:
	lh	$2,182($17)
	nop
	beq	$2,$0,$Lnjp_800C6CA4_3
	addu	$4,$17,$0
	jal	njp_sna_sub_8004E41C
	addiu	$5,$0,2
	addu	$4,$17,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,4
$Lnjp_800C6CA4_3:
	lw	$31,56($29)
	lw	$17,52($29)
	lw	$16,48($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C6DC0
njp_800C6DC0:
	addiu	$29,$29,-104
	sw	$18,72($29)
	addu	$18,$4,$0
	sw	$31,100($29)
	sw	$30,96($29)
	sw	$23,92($29)
	sw	$22,88($29)
	sw	$21,84($29)
	sw	$20,80($29)
	sw	$19,76($29)
	sw	$17,68($29)
	sw	$16,64($29)
	lh	$3,180($18)
	lh	$2,82($18)
	sw	$0,2532($18)
	sw	$2,1944($18)
	slti	$2,$3,500
	beq	$2,$0,$Lnjp_800C6DC0_0
	sh	$3,82($18)
	addiu	$3,$0,500
$Lnjp_800C6DC0_0:
	slti	$2,$3,701
	bne	$2,$0,$Lnjp_800C6DC0_1
	addu	$4,$18,$0
	addiu	$3,$0,700
$Lnjp_800C6DC0_1:
	lw	$2,2200($18)
	addiu	$5,$0,4096
	jal	njp_sna_check_flags1_8004E31C
	sh	$3,18($2)
	bne	$2,$0,$Lnjp_800C6DC0_3
	nop
	lh	$2,2442($18)
	nop
	bgez	$2,$Lnjp_800C6DC0_2
	nop
	lb	$2,119($18)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_2
	nop
	sh	$0,2442($18)
$Lnjp_800C6DC0_2:
	lhu	$2,2442($18)
	nop
	addiu	$2,$2,-32
	sh	$2,2442($18)
$Lnjp_800C6DC0_3:
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,128
	bne	$2,$0,$Lnjp_800C6DC0_73
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x2000
	beq	$2,$0,$Lnjp_800C6DC0_4
	lui	$2,%hi(njp_GV_PadData_8009F0C4)
	addiu	$2,$2,%lo(njp_GV_PadData_8009F0C4)
	sw	$2,2320($18)
$Lnjp_800C6DC0_4:
	addu	$4,$18,$0
	addiu	$5,$0,16384
	jal	njp_sna_clear_flags1_8004E308
	sh	$0,112($18)
	lw	$3,2320($18)
	nop
	lh	$2,10($3)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_7
	lui	$4,0x1
	lhu	$2,0($3)
	nop
	andi	$2,$2,0xf000
	beq	$2,$0,$Lnjp_800C6DC0_6
	addiu	$4,$3,14
	addu	$3,$0,$0
$Lnjp_800C6DC0_5:
	lbu	$2,0($4)
	nop
	addiu	$2,$2,-64
	andi	$2,$2,0xff
	sltiu	$2,$2,129
	beq	$2,$0,$Lnjp_800C6DC0_8
	addiu	$3,$3,1
	slti	$2,$3,2
	bne	$2,$0,$Lnjp_800C6DC0_5
	addiu	$4,$4,1
$Lnjp_800C6DC0_6:
	lui	$4,0x1
$Lnjp_800C6DC0_7:
	lui	$2,%hi(njp_bss_16)
	lui	$3,%hi(njp_dword_800ABBA8)
	sw	$0,%lo(njp_bss_16)($2)
	addiu	$2,$0,-1
	sw	$2,%lo(njp_dword_800ABBA8)($3)
	lui	$2,%hi(njp_dword_800ABBC4)
	sw	$0,%lo(njp_dword_800ABBC4)($2)
	lui	$2,%hi(njp_bss_60)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$16,$2,%lo(njp_bss_60)
	beq	$2,$0,$Lnjp_800C6DC0_9
	lui	$2,%hi(njp_bss_20)
	lw	$2,%lo(njp_bss_20)($2)
	j	$Lnjp_800C6DC0_10
	lui	$22,%hi(njp_pVec_800ABBCC)
$Lnjp_800C6DC0_8:
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,16384
	j	$Lnjp_800C6DC0_7
	lui	$4,0x1
$Lnjp_800C6DC0_9:
	addu	$2,$0,$0
	lui	$22,%hi(njp_pVec_800ABBCC)
$Lnjp_800C6DC0_10:
	lui	$30,%hi(njp_bss_20)
	sw	$2,0($16)
	addiu	$2,$0,-1
	lw	$4,%lo(njp_pVec_800ABBCC)($22)
	lw	$3,2320($18)
	lui	$15,%hi(njp_dword_800ABBD0)
	sw	$2,%lo(njp_dword_800ABBD0)($15)
	lh	$3,8($3)
	lui	$2,%hi(njp_bss_48)
	sw	$0,%lo(njp_bss_20)($30)
	sw	$0,%lo(njp_pVec_800ABBCC)($22)
	sw	$4,%lo(njp_bss_48)($2)
	lui	$2,%hi(njp_gSnaMoveDir_800ABBA4)
	sw	$3,%lo(njp_gSnaMoveDir_800ABBA4)($2)
	lb	$16,120($18)
	sw	$0,1948($18)
	blez	$16,$Lnjp_800C6DC0_31
	sw	$3,56($29)
	addiu	$4,$18,128
	lui	$21,%hi(njp_bss_16)
	lui	$19,%hi(njp_dword_800ABBB4)
	addiu	$2,$18,122
	sw	$4,%lo(njp_bss_16)($21)
	jal	GV_VecDir2
	sw	$2,%lo(njp_dword_800ABBB4)($19)
	addu	$4,$2,$0
	lw	$2,%lo(njp_dword_800ABBB4)($19)
	lui	$20,%hi(njp_dword_800ABBA8)
	sw	$4,%lo(njp_dword_800ABBA8)($20)
	lbu	$2,0($2)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_11
	nop
	lw	$2,%lo(njp_bss_16)($21)
	lw	$3,144($18)
	lui	$23,%hi(njp_dword_800ABBD0)
	sw	$4,%lo(njp_dword_800ABBD0)($23)
	sw	$2,%lo(njp_pVec_800ABBCC)($22)
	sw	$3,%lo(njp_bss_20)($30)
$Lnjp_800C6DC0_11:
	lw	$24,56($29)
	nop
	bltz	$24,$Lnjp_800C6DC0_31
	addiu	$2,$0,1
	beq	$16,$2,$Lnjp_800C6DC0_12
	addiu	$17,$18,136
	jal	GV_VecDir2
	addu	$4,$17,$0
	lw	$4,56($29)
	lw	$5,%lo(njp_dword_800ABBA8)($20)
	jal	GV_DiffDirAbs
	addu	$16,$2,$0
	addu	$5,$16,$0
	lw	$4,56($29)
	jal	GV_DiffDirAbs
	addu	$16,$2,$0
	slt	$2,$2,$16
	beq	$2,$0,$Lnjp_800C6DC0_12
	addu	$4,$17,$0
	addiu	$2,$18,123
	sw	$4,%lo(njp_bss_16)($21)
	jal	GV_VecDir2
	sw	$2,%lo(njp_dword_800ABBB4)($19)
	lw	$3,%lo(njp_dword_800ABBB4)($19)
	addu	$4,$2,$0
	sw	$4,%lo(njp_dword_800ABBA8)($20)
	lbu	$2,0($3)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_13
	addiu	$10,$0,-1
	lw	$2,%lo(njp_bss_16)($21)
	lw	$3,148($18)
	lui	$25,%hi(njp_dword_800ABBD0)
	sw	$4,%lo(njp_dword_800ABBD0)($25)
	sw	$2,%lo(njp_pVec_800ABBCC)($22)
	sw	$3,%lo(njp_bss_20)($30)
$Lnjp_800C6DC0_12:
	addiu	$10,$0,-1
$Lnjp_800C6DC0_13:
	addiu	$17,$18,32
	lb	$3,88($17)
	addiu	$2,$0,1
	bne	$3,$2,$Lnjp_800C6DC0_17
	addu	$16,$17,$0
	lbu	$2,90($17)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_26
	nop
	lw	$6,112($17)
	lhu	$3,32($18)
	lhu	$2,0($6)
	nop
	subu	$3,$3,$2
	sh	$3,48($29)
	lhu	$4,4($17)
	lhu	$2,2($6)
	sll	$3,$3,16
	subu	$4,$4,$2
	sh	$4,50($29)
	lhu	$5,8($6)
	lhu	$2,0($6)
	sra	$3,$3,16
	subu	$5,$5,$2
	sll	$2,$5,16
	sra	$7,$2,16
	mult	$7,$3
	sll	$4,$4,16
	sh	$5,40($29)
	lhu	$3,10($6)
	lhu	$2,2($6)
	sra	$4,$4,16
	subu	$3,$3,$2
	mflo	$8
	sll	$2,$3,16
	sra	$5,$2,16
	mult	$5,$4
	sh	$3,42($29)
	mflo	$9
	addu	$2,$8,$9
	bgez	$2,$Lnjp_800C6DC0_14
	addu	$3,$2,$0
	j	$Lnjp_800C6DC0_15
	addiu	$2,$0,1
$Lnjp_800C6DC0_14:
	mult	$7,$7
	mflo	$2
	nop
	nop
	mult	$5,$5
	mflo	$8
	addu	$2,$2,$8
	slt	$2,$2,$3
$Lnjp_800C6DC0_15:
	bne	$2,$0,$Lnjp_800C6DC0_27
	addu	$16,$10,$0
	addu	$10,$0,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_16:
	j	$Lnjp_800C6DC0_26
	sw	$2,1948($18)
$Lnjp_800C6DC0_17:
	addiu	$13,$18,122
	addu	$14,$0,$0
	addu	$9,$14,$0
	addiu	$12,$29,32
	addu	$11,$17,$0
$Lnjp_800C6DC0_18:
	lw	$6,112($11)
	nop
	sw	$6,0($12)
	lbu	$2,0($13)
	nop
	andi	$2,$2,0x40
	bne	$2,$0,$Lnjp_800C6DC0_21
	nop
	lhu	$3,0($16)
	lhu	$2,0($6)
	nop
	subu	$3,$3,$2
	sh	$3,48($29)
	lhu	$5,4($16)
	lhu	$2,2($6)
	sll	$3,$3,16
	subu	$5,$5,$2
	sh	$5,50($29)
	lhu	$4,8($6)
	lhu	$2,0($6)
	sra	$3,$3,16
	subu	$4,$4,$2
	sll	$2,$4,16
	sra	$7,$2,16
	mult	$7,$3
	sll	$5,$5,16
	sh	$4,40($29)
	lhu	$3,10($6)
	lhu	$2,2($6)
	sra	$5,$5,16
	subu	$3,$3,$2
	mflo	$8
	sll	$2,$3,16
	sra	$4,$2,16
	mult	$4,$5
	sh	$3,42($29)
	mflo	$19
	addu	$2,$8,$19
	bgez	$2,$Lnjp_800C6DC0_19
	addu	$3,$2,$0
	j	$Lnjp_800C6DC0_20
	addiu	$2,$0,1
$Lnjp_800C6DC0_19:
	mult	$7,$7
	mflo	$2
	nop
	nop
	mult	$4,$4
	mflo	$8
	addu	$2,$2,$8
	slt	$2,$2,$3
$Lnjp_800C6DC0_20:
	bne	$2,$0,$Lnjp_800C6DC0_21
	addiu	$2,$0,1
	addu	$10,$9,$0
	addiu	$14,$14,1
	sw	$2,1948($18)
$Lnjp_800C6DC0_21:
	addiu	$12,$12,4
	addiu	$11,$11,4
	addiu	$9,$9,1
	slti	$2,$9,2
	bne	$2,$0,$Lnjp_800C6DC0_18
	addiu	$13,$13,1
	slti	$2,$14,2
	bne	$2,$0,$Lnjp_800C6DC0_26
	addiu	$16,$17,96
	jal	GV_VecLen3
	addu	$4,$16,$0
	addiu	$17,$17,104
	addu	$4,$17,$0
	jal	GV_VecLen3
	addu	$20,$2,$0
	addu	$4,$16,$0
	jal	GV_VecDir2
	addu	$19,$2,$0
	addu	$4,$17,$0
	jal	GV_VecDir2
	addu	$16,$2,$0
	addu	$4,$16,$0
	jal	GV_DiffDirAbs
	addu	$5,$2,$0
	slti	$2,$2,512
	beq	$2,$0,$Lnjp_800C6DC0_22
	addiu	$2,$0,1
	sw	$2,1948($18)
	slt	$2,$20,$19
	j	$Lnjp_800C6DC0_27
	xori	$16,$2,0x1
$Lnjp_800C6DC0_22:
	lui	$2,%hi(njp_bss_60)
	lw	$3,%lo(njp_bss_60)($2)
	lw	$2,32($29)
	nop
	bne	$3,$2,$Lnjp_800C6DC0_23
	addiu	$10,$0,2
	j	$Lnjp_800C6DC0_24
	addu	$10,$0,$0
$Lnjp_800C6DC0_23:
	lw	$2,36($29)
	nop
	bne	$3,$2,$Lnjp_800C6DC0_25
	addiu	$2,$0,2
	addiu	$10,$0,1
$Lnjp_800C6DC0_24:
	addiu	$2,$0,2
$Lnjp_800C6DC0_25:
	bne	$10,$2,$Lnjp_800C6DC0_16
	addiu	$2,$0,1
	sw	$10,1948($18)
$Lnjp_800C6DC0_26:
	addu	$16,$10,$0
$Lnjp_800C6DC0_27:
	addiu	$2,$0,-1
	bne	$16,$2,$Lnjp_800C6DC0_28
	addiu	$17,$0,2
	lui	$2,%hi(njp_pVec_800ABBCC)
	sw	$0,%lo(njp_pVec_800ABBCC)($2)
	lui	$2,%hi(njp_dword_800ABBD0)
	j	$Lnjp_800C6DC0_31
	sw	$16,%lo(njp_dword_800ABBD0)($2)
$Lnjp_800C6DC0_28:
	beq	$16,$17,$Lnjp_800C6DC0_29
	sll	$4,$16,3
	addiu	$4,$4,128
	addu	$4,$18,$4
	lui	$2,%hi(njp_pVec_800ABBCC)
	jal	GV_VecDir2
	sw	$4,%lo(njp_pVec_800ABBCC)($2)
	lui	$3,%hi(njp_dword_800ABBD0)
	sw	$2,%lo(njp_dword_800ABBD0)($3)
	sllv	$2,$16,$17
	addu	$2,$18,$2
	lw	$3,144($2)
	lui	$2,%hi(njp_bss_20)
	sw	$3,%lo(njp_bss_20)($2)
$Lnjp_800C6DC0_29:
	lui	$2,%hi(njp_dword_800ABBD0)
	lw	$5,%lo(njp_dword_800ABBD0)($2)
	lw	$4,56($29)
	jal	GV_DiffDirS
	nop
	addu	$3,$2,$0
	addiu	$2,$3,896
	sltiu	$2,$2,1793
	beq	$2,$0,$Lnjp_800C6DC0_31
	lui	$4,%hi(njp_dword_800ABBC4)
	addiu	$2,$0,1
	bltz	$3,$Lnjp_800C6DC0_30
	sw	$2,%lo(njp_dword_800ABBC4)($4)
	slti	$2,$3,257
	bne	$2,$0,$Lnjp_800C6DC0_31
	addiu	$2,$0,4
	j	$Lnjp_800C6DC0_31
	sw	$2,%lo(njp_dword_800ABBC4)($4)
$Lnjp_800C6DC0_30:
	slti	$2,$3,-256
	beq	$2,$0,$Lnjp_800C6DC0_31
	nop
	sw	$17,%lo(njp_dword_800ABBC4)($4)
$Lnjp_800C6DC0_31:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x20
	beq	$2,$0,$Lnjp_800C6DC0_42
	nop
	lh	$2,2380($18)
	lh	$17,2376($18)
	beq	$2,$0,$Lnjp_800C6DC0_38
	addiu	$2,$0,450
	sh	$2,88($18)
	sh	$2,86($18)
	sh	$2,2436($18)
	andi	$2,$17,0x4002
	bne	$2,$0,$Lnjp_800C6DC0_32
	andi	$2,$17,0x100
	addiu	$4,$18,32
	addiu	$5,$18,2120
	lh	$3,2378($18)
	lh	$6,152($18)
	lhu	$2,180($18)
	subu	$3,$6,$3
	subu	$2,$2,$3
	sh	$2,82($18)
	addu	$2,$2,$6
	sh	$2,34($18)
	sll	$2,$2,16
	lw	$3,156($18)
	sra	$2,$2,16
	jal	DG_GetLightMatrix2
	sw	$2,24($3)
	j	$Lnjp_800C6DC0_33
	nop
$Lnjp_800C6DC0_32:
	bne	$2,$0,$Lnjp_800C6DC0_33
	addiu	$2,$0,1100
	sh	$2,82($18)
$Lnjp_800C6DC0_33:
	lhu	$2,82($18)
	lh	$16,2372($18)
	nop
	bltz	$16,$Lnjp_800C6DC0_35
	sh	$2,180($18)
	lh	$5,42($18)
	jal	GV_DiffDirAbs
	addu	$4,$16,$0
	slti	$2,$2,1537
	bne	$2,$0,$Lnjp_800C6DC0_34
	nop
	sh	$16,42($18)
$Lnjp_800C6DC0_34:
	sh	$16,110($18)
$Lnjp_800C6DC0_35:
	andi	$2,$17,0x80
	bne	$2,$0,$Lnjp_800C6DC0_36
	andi	$2,$17,0x800
	addiu	$4,$18,156
	addiu	$5,$18,384
	addiu	$6,$0,5887
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,32
	sw	$2,20($29)
	addiu	$2,$18,1688
	addiu	$7,$18,464
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	addiu	$2,$0,-1
	sh	$2,170($18)
	andi	$2,$17,0x800
$Lnjp_800C6DC0_36:
	beq	$2,$0,$Lnjp_800C6DC0_37
	nop
	lh	$5,2434($18)
	jal	njp_sub_8004E5E8
	addu	$4,$18,$0
	addu	$4,$18,$0
	addu	$5,$2,$0
	jal	njp_SetAction_8004E22C
	addu	$6,$0,$0
$Lnjp_800C6DC0_37:
	sh	$0,2380($18)
$Lnjp_800C6DC0_38:
	lw	$3,1952($18)
	nop
	blez	$3,$Lnjp_800C6DC0_40
	addiu	$4,$18,1956
	ori	$7,$0,0x937a
	addiu	$6,$0,28923
	ori	$5,$0,0xbe0a
$Lnjp_800C6DC0_39:
	lhu	$2,4($4)
	nop
	beq	$2,$7,$Lnjp_800C6DC0_41
	nop
	beq	$2,$6,$Lnjp_800C6DC0_41
	nop
	beq	$2,$5,$Lnjp_800C6DC0_41
	addiu	$3,$3,-1
	bgtz	$3,$Lnjp_800C6DC0_39
	addiu	$4,$4,20
$Lnjp_800C6DC0_40:
	jal	njp_GM_ClearPlayerStatusFlag
	addiu	$4,$0,4
$Lnjp_800C6DC0_41:
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x820
$Lnjp_800C6DC0_42:
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x80
	beq	$2,$0,$Lnjp_800C6DC0_51
	nop
	lbu	$16,2432($18)
	nop
	beq	$16,$0,$Lnjp_800C6DC0_48
	addiu	$16,$16,-1
	blez	$16,$Lnjp_800C6DC0_46
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_43
	addu	$2,$0,$0
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_43
	addu	$2,$0,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_43:
	beq	$2,$0,$Lnjp_800C6DC0_45
	andi	$2,$16,0x3
	beq	$2,$0,$Lnjp_800C6DC0_44
	addiu	$4,$0,-129
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	j	$Lnjp_800C6DC0_45
	sw	$3,40($2)
$Lnjp_800C6DC0_44:
	lw	$3,156($18)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	sw	$2,40($3)
$Lnjp_800C6DC0_45:
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_47
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2
	beq	$2,$0,$Lnjp_800C6DC0_47
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,1
	bne	$2,$0,$Lnjp_800C6DC0_47
	nop
	jal	GV_RandS
	addiu	$4,$0,16
	mult	$2,$16
	lui	$3,%hi(GM_SnakeCamera)
	addiu	$3,$3,%lo(GM_SnakeCamera)
	lhu	$2,2($3)
	mflo	$15
	addu	$2,$2,$15
	j	$Lnjp_800C6DC0_47
	sh	$2,2($3)
$Lnjp_800C6DC0_46:
	jal	njp_sna_clear_invuln_8004F2EC
	addu	$4,$18,$0
$Lnjp_800C6DC0_47:
	j	$Lnjp_800C6DC0_64
	sb	$16,2432($18)
$Lnjp_800C6DC0_48:
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x400
	beq	$2,$0,$Lnjp_800C6DC0_49
	addiu	$4,$0,-129
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	sw	$3,40($2)
$Lnjp_800C6DC0_49:
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_50
	addiu	$4,$0,-129
	lw	$3,156($18)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	j	$Lnjp_800C6DC0_64
	sw	$2,40($3)
$Lnjp_800C6DC0_50:
	lw	$2,156($18)
	nop
	lw	$3,40($2)
	nop
	and	$3,$3,$4
	j	$Lnjp_800C6DC0_64
	sw	$3,40($2)
$Lnjp_800C6DC0_51:
	lw	$16,2200($18)
	nop
	lhu	$3,6($16)
	nop
	andi	$2,$3,0x6
	beq	$2,$0,$Lnjp_800C6DC0_63
	addiu	$2,$0,1
	lh	$17,62($16)
	nop
	beq	$17,$2,$Lnjp_800C6DC0_52
	addiu	$2,$0,3
	beq	$17,$2,$Lnjp_800C6DC0_52
	addiu	$2,$0,8
	bne	$17,$2,$Lnjp_800C6DC0_53
	addiu	$19,$0,1
$Lnjp_800C6DC0_52:
	addu	$19,$0,$0
$Lnjp_800C6DC0_53:
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2
	bne	$2,$0,$Lnjp_800C6DC0_57
	lui	$4,0x21
	lbu	$2,117($18)
	ori	$4,$4,0x20
	andi	$2,$2,0xfd
	jal	njp_GM_ClearPlayerStatusFlag
	sb	$2,117($18)
	addu	$4,$18,$0
	jal	njp_sna_clear_flags1_8004E308
	addiu	$5,$0,48
	addu	$4,$18,$0
	addiu	$2,$0,450
	jal	njp_sub_8004F454
	sh	$2,2436($18)
	lui	$4,0x40
	jal	njp_GM_SetPlayerStatusFlag
	ori	$4,$4,0x100
	bne	$19,$0,$Lnjp_800C6DC0_54
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C5634)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_800C5634)
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,24
	lui	$4,%hi(njp_dword_8009EED4)
	addiu	$4,$4,%lo(njp_dword_8009EED4)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EED8)
	addiu	$4,$4,%lo(njp_dword_8009EED8)
	jal	NewPadVibration
	addiu	$5,$0,2
	j	$Lnjp_800C6DC0_56
	addu	$4,$18,$0
$Lnjp_800C6DC0_54:
	lwl	$23,47($16)
	lwr	$23,44($16)
	lwl	$24,51($16)
	lwr	$24,48($16)
	swl	$23,2443($18)
	swr	$23,2440($18)
	swl	$24,2447($18)
	swr	$24,2444($18)
	lhu	$3,2440($18)
	lh	$6,2442($18)
	sll	$3,$3,16
	sra	$2,$3,16
	srl	$3,$3,31
	addu	$2,$2,$3
	sra	$2,$2,1
	bgez	$6,$Lnjp_800C6DC0_55
	sh	$2,2440($18)
	addiu	$6,$6,3
$Lnjp_800C6DC0_55:
	addu	$4,$18,$0
	lui	$5,%hi(njp_800C573C)
	addiu	$5,$5,%lo(njp_800C573C)
	lhu	$3,2444($18)
	sra	$2,$6,2
	sh	$2,2442($18)
	sll	$3,$3,16
	sra	$2,$3,16
	srl	$3,$3,31
	addu	$2,$2,$3
	sra	$2,$2,1
	jal	njp_sna_start_anim_8004E1F4
	sh	$2,2444($18)
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,25
	lui	$4,%hi(njp_dword_8009EEE0)
	addiu	$4,$4,%lo(njp_dword_8009EEE0)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EEE4)
	addiu	$4,$4,%lo(njp_dword_8009EEE4)
	jal	NewPadVibration
	addiu	$5,$0,2
	jal	njp_sna_8004EC00
	addu	$4,$18,$0
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	addiu	$5,$0,4
	addu	$4,$18,$0
$Lnjp_800C6DC0_56:
	jal	njp_sna_act_helper2_helper4_8004F090
	addu	$5,$17,$0
	j	$Lnjp_800C6DC0_62
	nop
$Lnjp_800C6DC0_57:
	addu	$4,$18,$0
	jal	njp_sna_set_invuln_8004F2A0
	addiu	$5,$0,32
	lh	$2,40($16)
	nop
	blez	$2,$Lnjp_800C6DC0_58
	addiu	$2,$0,1
	lh	$5,62($16)
	jal	njp_sna_act_helper2_helper4_8004F090
	addu	$4,$18,$0
	addiu	$2,$0,1
$Lnjp_800C6DC0_58:
	beq	$17,$2,$Lnjp_800C6DC0_59
	addiu	$2,$0,3
	bne	$17,$2,$Lnjp_800C6DC0_60
	addiu	$5,$0,63
$Lnjp_800C6DC0_59:
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,24
	lui	$4,%hi(njp_dword_8009EED4)
	addiu	$4,$4,%lo(njp_dword_8009EED4)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EED8)
	j	$Lnjp_800C6DC0_61
	addiu	$4,$4,%lo(njp_dword_8009EED8)
$Lnjp_800C6DC0_60:
	addu	$4,$0,$0
	jal	GM_SeSet2
	addiu	$6,$0,25
	lui	$4,%hi(njp_dword_8009EEE0)
	addiu	$4,$4,%lo(njp_dword_8009EEE0)
	jal	NewPadVibration
	addiu	$5,$0,1
	lui	$4,%hi(njp_dword_8009EEE4)
	addiu	$4,$4,%lo(njp_dword_8009EEE4)
$Lnjp_800C6DC0_61:
	jal	NewPadVibration
	addiu	$5,$0,2
	lh	$2,38($16)
	nop
	bgtz	$2,$Lnjp_800C6DC0_62
	lui	$2,%hi(GM_GameOverTimer)
	lw	$2,%lo(GM_GameOverTimer)($2)
	nop
	addiu	$2,$2,1
	sltiu	$2,$2,2
	beq	$2,$0,$Lnjp_800C6DC0_62
	addu	$4,$0,$0
	addiu	$5,$0,63
	addiu	$6,$0,26
	sh	$0,40($18)
	jal	GM_SeSet2
	sh	$0,108($18)
	addu	$4,$18,$0
	jal	njp_sna_8004F8E4
	addiu	$5,$0,12
$Lnjp_800C6DC0_62:
	jal	njp_sna_clear_target_800C41B4
	addu	$4,$16,$0
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C6DC0_64
	nop
	jal	GV_RandS
	addiu	$4,$0,512
	lhu	$3,110($18)
	nop
	addu	$3,$3,$2
	j	$Lnjp_800C6DC0_64
	sh	$3,110($18)
$Lnjp_800C6DC0_63:
	andi	$2,$3,0x80
	beq	$2,$0,$Lnjp_800C6DC0_64
	nop
	jal	njp_sna_clear_target_800C41B4
	addu	$4,$16,$0
$Lnjp_800C6DC0_64:
	jal	njp_800C3D84
	addu	$4,$18,$0
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x4000
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,8192
	beq	$2,$0,$Lnjp_800C6DC0_65
	nop
	lw	$2,1952($18)
	nop
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,4
	bne	$2,$0,$Lnjp_800C6DC0_66
	nop
	jal	GM_StreamStatus
	nop
	addiu	$3,$0,2
	beq	$2,$3,$Lnjp_800C6DC0_66
	nop
	jal	GM_StreamPlayStop
	nop
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x4000
	lui	$3,%hi(GM_GameOverTimer)
	addiu	$2,$0,1
	j	$Lnjp_800C6DC0_66
	sw	$2,%lo(GM_GameOverTimer)($3)
$Lnjp_800C6DC0_65:
	lui	$16,%hi(GM_GameOverTimer)
	lw	$5,%lo(GM_GameOverTimer)($16)
	nop
	blez	$5,$Lnjp_800C6DC0_66
	lui	$3,0x1000
	lui	$4,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($4)
	nop
	or	$2,$2,$3
	sw	$2,%lo(GM_GameStatus)($4)
	addiu	$2,$0,2
	bne	$5,$2,$Lnjp_800C6DC0_66
	nop
	addu	$4,$18,$0
	jal	njp_sna_set_flags1_8004E2F4
	lui	$5,0x8
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,8192
	addu	$4,$18,$0
	jal	njp_sna_set_invuln_8004F2A0
	addu	$5,$0,$0
	addiu	$2,$0,-1
	sw	$2,%lo(GM_GameOverTimer)($16)
$Lnjp_800C6DC0_66:
	jal	njp_sna_act_helper2_helper3_8004ED6C
	addu	$4,$18,$0
	addu	$4,$18,$0
	lw	$16,2328($18)
	lw	$3,2324($18)
	addu	$5,$16,$0
	addiu	$2,$16,1
	jalr	$31,$3
	sw	$2,2328($18)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,1
	beq	$2,$0,$Lnjp_800C6DC0_67
	addu	$4,$18,$0
	lw	$2,2344($18)
	j	$Lnjp_800C6DC0_68
	nop
$Lnjp_800C6DC0_67:
	lw	$2,2340($18)
$Lnjp_800C6DC0_68:
	nop
	jalr	$31,$2
	addu	$5,$16,$0
	lh	$4,86($18)
	lh	$5,2436($18)
	jal	GV_NearExp4
	nop
	lhu	$3,2442($18)
	lw	$4,2320($18)
	sh	$2,86($18)
	sh	$3,102($18)
	lhu	$2,2($4)
	nop
	andi	$2,$2,0x10
	beq	$2,$0,$Lnjp_800C6DC0_70
	addu	$4,$18,$0
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,4
	bne	$2,$0,$Lnjp_800C6DC0_69
	addu	$2,$0,$0
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,2049
	bne	$2,$0,$Lnjp_800C6DC0_69
	addu	$2,$0,$0
	lw	$3,2344($18)
	lui	$2,%hi(njp_nop_800C48EC)
	addiu	$2,$2,%lo(njp_nop_800C48EC)
	bne	$3,$2,$Lnjp_800C6DC0_69
	addiu	$2,$0,1
	addu	$2,$0,$0
$Lnjp_800C6DC0_69:
	beq	$2,$0,$Lnjp_800C6DC0_70
	nop
	jal	njp_sub_8004EB74
	addu	$4,$18,$0
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,8
$Lnjp_800C6DC0_70:
	jal	njp_sna_stealth_800C33C8
	addu	$4,$18,$0
	lh	$2,170($18)
	lh	$4,390($18)
	lhu	$3,2434($18)
	lui	$5,%hi(GM_PlayerAction)
	sw	$2,%lo(GM_PlayerAction)($5)
	lui	$2,%hi(dword_800AB9D4)
	sw	$4,%lo(dword_800AB9D4)($2)
	lui	$2,%hi(linkvarbuf+32)
	sh	$3,%lo(linkvarbuf+32)($2)
	lh	$3,170($18)
	addiu	$2,$0,25
	bne	$3,$2,$Lnjp_800C6DC0_72
	addiu	$16,$18,32
	slti	$2,$4,16
	bne	$2,$0,$Lnjp_800C6DC0_71
	addiu	$2,$0,7
	addiu	$2,$0,39
$Lnjp_800C6DC0_71:
	sw	$2,%lo(GM_PlayerAction)($5)
	addiu	$16,$18,32
$Lnjp_800C6DC0_72:
	lh	$5,170($18)
	lh	$6,390($18)
	jal	njp_sna_se_800C3640
	addu	$4,$16,$0
	lh	$5,172($18)
	lh	$6,414($18)
	jal	njp_sna_se_800C36EC
	addu	$4,$16,$0
$Lnjp_800C6DC0_73:
	lw	$31,100($29)
	lw	$30,96($29)
	lw	$23,92($29)
	lw	$22,88($29)
	lw	$21,84($29)
	lw	$20,80($29)
	lw	$19,76($29)
	lw	$18,72($29)
	lw	$17,68($29)
	lw	$16,64($29)
	jr	$31
	addiu	$29,$29,104
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C7C04
njp_800C7C04:
	addiu	$29,$29,-64
	sw	$17,44($29)
	addu	$17,$4,$0
	lui	$5,0x4
	sw	$31,60($29)
	sw	$20,56($29)
	sw	$19,52($29)
	sw	$18,48($29)
	jal	njp_sna_check_flags1_8004E31C
	sw	$16,40($29)
	beq	$2,$0,$Lnjp_800C7C04_1
	addu	$2,$0,$0
	jal	njp_CheckMessage0_80050878
	addu	$4,$17,$0
	jal	njp_800C3D84
	addu	$4,$17,$0
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x4
	beq	$2,$0,$Lnjp_800C7C04_0
	addiu	$4,$17,32
	addiu	$5,$17,40
	lui	$2,%hi(dword_800AB9D4)
	jal	DG_SetPos2
	sw	$0,%lo(dword_800AB9D4)($2)
	lw	$4,156($17)
	jal	DG_PutObjs
	nop
	j	$Lnjp_800C7C04_1
	addiu	$2,$0,1
$Lnjp_800C7C04_0:
	addu	$2,$0,$0
$Lnjp_800C7C04_1:
	bne	$2,$0,$Lnjp_800C7C04_17
	nop
	lw	$16,2200($17)
	nop
	lhu	$2,6($16)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$Lnjp_800C7C04_2
	addiu	$4,$16,52
	addiu	$5,$17,100
	jal	GV_AddVec3
	addu	$6,$5,$0
	lhu	$2,6($16)
	nop
	andi	$2,$2,0xfff7
	sh	$2,6($16)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,55($16)
	swr	$8,52($16)
	swl	$9,59($16)
	swr	$9,56($16)
$Lnjp_800C7C04_2:
	lh	$20,180($17)
	jal	GM_ActMotion
	addiu	$4,$17,156
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x80
	beq	$2,$0,$Lnjp_800C7C04_4
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C7C04_4
	addiu	$4,$29,32
	lwl	$8,2503($17)
	lwr	$8,2500($17)
	lwl	$9,2507($17)
	lwr	$9,2504($17)
	swl	$8,35($29)
	swr	$8,32($29)
	swl	$9,39($29)
	swr	$9,36($29)
	lui	$5,%hi(DG_ZeroVector)
	addiu	$5,$5,%lo(DG_ZeroVector)
	jal	GV_NearExp8V
	addiu	$6,$0,3
	jal	GV_VecLen3
	addiu	$4,$29,32
	slti	$2,$2,9
	bne	$2,$0,$Lnjp_800C7C04_3
	nop
	lwl	$8,35($29)
	lwr	$8,32($29)
	lwl	$9,39($29)
	lwr	$9,36($29)
	swl	$8,2503($17)
	swr	$8,2500($17)
	swl	$9,2507($17)
	swr	$9,2504($17)
$Lnjp_800C7C04_3:
	lhu	$2,2500($17)
	lbu	$3,119($17)
	lhu	$4,2504($17)
	andi	$3,$3,0x1
	sh	$2,100($17)
	beq	$3,$0,$Lnjp_800C7C04_4
	sh	$4,104($17)
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x80
$Lnjp_800C7C04_4:
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x200
	beq	$2,$0,$Lnjp_800C7C04_5
	nop
	sh	$0,104($17)
	sh	$0,100($17)
$Lnjp_800C7C04_5:
	lh	$18,152($17)
	lbu	$2,117($17)
	addiu	$3,$18,750
	andi	$2,$2,0x8
	beq	$2,$0,$Lnjp_800C7C04_6
	sh	$3,84($17)
	lw	$2,1944($17)
	nop
	slti	$2,$2,750
	beq	$2,$0,$Lnjp_800C7C04_6
	nop
	lhu	$2,34($17)
	nop
	sh	$2,84($17)
$Lnjp_800C7C04_6:
	lh	$2,2434($17)
	nop
	beq	$2,$0,$Lnjp_800C7C04_7
	slti	$2,$20,500
	bne	$2,$0,$Lnjp_800C7C04_7
	addiu	$2,$0,496
	sh	$2,82($17)
$Lnjp_800C7C04_7:
	jal	njp_UpdateLife_8004F6E8
	addu	$4,$17,$0
	jal	njp_CheckSnakeDead_8004E384
	addu	$4,$17,$0
	jal	njp_CheckMessage0_80050878
	addu	$4,$17,$0
	jal	GM_ActControl
	addiu	$4,$17,32
	lui	$19,%hi(njp_bss_40)
	lui	$16,%hi(njp_bss_32)
	addiu	$4,$16,%lo(njp_bss_32)
	sw	$0,4($4)
	sw	$0,%lo(njp_bss_32)($16)
	lh	$3,86($17)
	addiu	$2,$0,-2
	beq	$3,$2,$Lnjp_800C7C04_8
	sw	$0,%lo(njp_bss_40)($19)
	jal	HZD_GetLevelHazard
	nop
	lw	$2,%lo(njp_bss_32)($16)
	nop
	beq	$2,$0,$Lnjp_800C7C04_8
	nop
	lh	$2,46($2)
	nop
	sw	$2,%lo(njp_bss_40)($19)
$Lnjp_800C7C04_8:
	lh	$2,152($17)
	nop
	subu	$2,$18,$2
	slti	$2,$2,250
	bne	$2,$0,$Lnjp_800C7C04_11
	addu	$4,$17,$0
	jal	njp_sna_check_flags1_8004E31C
	lui	$5,0x800
	bne	$2,$0,$Lnjp_800C7C04_11
	lui	$2,%hi(njp_bss_32)
	lw	$2,%lo(njp_bss_32)($2)
	nop
	beq	$2,$0,$Lnjp_800C7C04_9
	addu	$4,$17,$0
	lhu	$2,6($2)
	nop
	andi	$2,$2,0x2
	beq	$2,$0,$Lnjp_800C7C04_11
	nop
$Lnjp_800C7C04_9:
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,4096
	bne	$2,$0,$Lnjp_800C7C04_11
	addu	$4,$17,$0
	lui	$5,0x80
	lwl	$8,103($17)
	lwr	$8,100($17)
	lwl	$9,107($17)
	lwr	$9,104($17)
	swl	$8,2503($17)
	swr	$8,2500($17)
	swl	$9,2507($17)
	swr	$9,2504($17)
	jal	njp_sna_set_flags1_8004E2F4
	sh	$0,2502($17)
	lui	$2,%hi(njp_800C5550)
	lw	$3,2324($17)
	addiu	$16,$2,%lo(njp_800C5550)
	beq	$3,$16,$Lnjp_800C7C04_11
	nop
	jal	njp_GM_CheckPlayerStatusFlag
	lui	$4,0x1
	beq	$2,$0,$Lnjp_800C7C04_10
	addiu	$2,$0,450
	sh	$2,2436($17)
	lui	$4,0x3
	jal	njp_GM_ClearPlayerStatusFlag
	ori	$4,$4,0x10
	addu	$4,$17,$0
	addu	$5,$0,$0
	addiu	$6,$0,4
	jal	njp_sna_8004E260
	addu	$7,$5,$0
	jal	GM_ExitBehindCamera
	nop
$Lnjp_800C7C04_10:
	addu	$4,$17,$0
	jal	njp_sna_start_anim_8004E1F4
	addu	$5,$16,$0
$Lnjp_800C7C04_11:
	lh	$3,86($17)
	addiu	$2,$0,-2
	bne	$3,$2,$Lnjp_800C7C04_12
	addiu	$4,$17,32
	addiu	$5,$17,40
	lhu	$2,180($17)
	lhu	$3,34($17)
	subu	$2,$2,$20
	addu	$3,$3,$2
	jal	DG_SetPos2
	sh	$3,34($17)
$Lnjp_800C7C04_12:
	jal	GM_ActObject
	addiu	$4,$17,156
	addu	$4,$17,$0
	jal	njp_sna_clear_flags1_8004E308
	lui	$5,0x100
	addiu	$16,$17,32
	addu	$4,$16,$0
	jal	DG_GetLightMatrix2
	addiu	$5,$17,2120
	lui	$2,%hi(dword_800ABA1C)
	lw	$2,%lo(dword_800ABA1C)($2)
	lw	$3,2188($17)
	sltiu	$2,$2,1
	sw	$2,0($3)
	lw	$4,2200($17)
	jal	GM_MoveTarget
	addu	$5,$16,$0
	addu	$4,$17,$0
	lwl	$8,35($17)
	lwr	$8,32($17)
	lwl	$9,39($17)
	lwr	$9,36($17)
	swl	$8,27($29)
	swr	$8,24($29)
	swl	$9,31($29)
	swr	$9,28($29)
	jal	njp_sna_check_flags1_8004E31C
	addiu	$5,$0,2048
	bne	$2,$0,$Lnjp_800C7C04_13
	lui	$19,%hi(GM_SnakeCamera)
	lw	$2,156($17)
	nop
	lhu	$2,648($2)
	nop
	sh	$2,26($29)
$Lnjp_800C7C04_13:
	addiu	$16,$19,%lo(GM_SnakeCamera)
	addu	$4,$17,$0
	lwl	$8,27($29)
	lwr	$8,24($29)
	lwl	$9,31($29)
	lwr	$9,28($29)
	swl	$8,2495($17)
	swr	$8,2492($17)
	swl	$9,2499($17)
	swr	$9,2496($17)
	lwl	$8,43($17)
	lwr	$8,40($17)
	lwl	$9,47($17)
	lwr	$9,44($17)
	swl	$8,43($16)
	swr	$8,40($16)
	swl	$9,47($16)
	swr	$9,44($16)
	lhu	$2,42($16)
	addiu	$18,$17,2492
	andi	$2,$2,0xfff
	jal	njp_800C6DC0
	sh	$2,42($16)
	lw	$4,2200($17)
	lwl	$8,103($17)
	lwr	$8,100($17)
	lwl	$9,107($17)
	lwr	$9,104($17)
	swl	$8,47($4)
	swr	$8,44($4)
	swl	$9,51($4)
	swr	$9,48($4)
	jal	GM_PushTarget
	nop
	lui	$2,%hi(GM_Camera+34)
	lh	$2,%lo(GM_Camera+34)($2)
	nop
	beq	$2,$0,$Lnjp_800C7C04_14
	addu	$4,$16,$0
	addu	$5,$18,$0
	jal	GV_NearExp4V
	addiu	$6,$0,3
	j	$Lnjp_800C7C04_15
	addu	$4,$17,$0
$Lnjp_800C7C04_14:
	addiu	$11,$19,%lo(GM_SnakeCamera)
	lwl	$8,27($29)
	lwr	$8,24($29)
	lwl	$9,31($29)
	lwr	$9,28($29)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	addu	$4,$17,$0
$Lnjp_800C7C04_15:
	ori	$5,$0,0x8000
	lui	$16,%hi(GM_PlayerPosition)
	lwl	$8,35($17)
	lwr	$8,32($17)
	lwl	$9,39($17)
	lwr	$9,36($17)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	addiu	$11,$16,%lo(GM_PlayerPosition)
	lwl	$8,19($29)
	lwr	$8,16($29)
	lwl	$9,23($29)
	lwr	$9,20($29)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	jal	njp_sna_check_flags1_8004E31C
	addiu	$19,$29,16
	beq	$2,$0,$Lnjp_800C7C04_16
	nop
	addiu	$11,$16,%lo(GM_PlayerPosition)
	lwl	$8,2495($17)
	lwr	$8,2492($17)
	lwl	$9,2499($17)
	lwr	$9,2496($17)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lw	$4,2200($17)
	jal	GM_MoveTarget
	addiu	$5,$17,2492
$Lnjp_800C7C04_16:
	lh	$18,152($17)
	nop
	sh	$18,18($29)
	lw	$2,76($17)
	lw	$6,2116($17)
	lw	$4,8($2)
	jal	HZD_GetAddress
	addu	$5,$19,$0
	addiu	$4,$0,16384
	lui	$3,%hi(GM_PlayerAddress)
	sw	$2,2116($17)
	jal	njp_GM_ClearPlayerStatusFlag
	sw	$2,%lo(GM_PlayerAddress)($3)
	jal	njp_GM_CheckPlayerStatusFlag
	addiu	$4,$0,3
	beq	$2,$0,$Lnjp_800C7C04_17
	nop
	jal	njp_GM_SetPlayerStatusFlag
	addiu	$4,$0,16384
$Lnjp_800C7C04_17:
	lw	$31,60($29)
	lw	$20,56($29)
	lw	$19,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	njp_800C81E8
njp_800C81E8:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$17,20($29)
	addiu	$17,$16,32
	addu	$4,$17,$0
	sw	$31,28($29)
	jal	GM_FreeControl
	sw	$18,24($29)
	addiu	$18,$16,156
	jal	GM_FreeObject
	addu	$4,$18,$0
	lw	$4,2200($16)
	jal	GM_FreeTarget
	nop
	jal	njp_FreeTargets
	addu	$4,$16,$0
	lw	$4,2184($16)
	nop
	beq	$4,$0,$Lnjp_800C81E8_0
	nop
	jal	GV_DestroyOtherActor
	nop
$Lnjp_800C81E8_0:
	lw	$4,2308($16)
	nop
	beq	$4,$0,$Lnjp_800C81E8_1
	lui	$3,%hi(GM_PlayerControl)
	jal	GV_DestroyOtherActor
	nop
	lui	$3,%hi(GM_PlayerControl)
$Lnjp_800C81E8_1:
	lw	$2,%lo(GM_PlayerControl)($3)
	nop
	bne	$2,$17,$Lnjp_800C81E8_2
	nop
	sw	$0,%lo(GM_PlayerControl)($3)
$Lnjp_800C81E8_2:
	lui	$3,%hi(GM_PlayerBody)
	lw	$2,%lo(GM_PlayerBody)($3)
	nop
	bne	$2,$18,$Lnjp_800C81E8_3
	nop
	sw	$0,%lo(GM_PlayerBody)($3)
$Lnjp_800C81E8_3:
	lw	$31,28($29)
	lw	$18,24($29)
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
	.globl	njp_800C82A4
njp_800C82A4:
	addiu	$29,$29,-88
	sw	$16,56($29)
	addu	$16,$4,$0
	sw	$17,60($29)
	addu	$17,$5,$0
	addiu	$4,$0,5
	addiu	$5,$0,2536
	sw	$31,84($29)
	sw	$22,80($29)
	sw	$21,76($29)
	sw	$20,72($29)
	sw	$19,68($29)
	jal	GV_NewActor
	sw	$18,64($29)
	addu	$18,$2,$0
	beq	$18,$0,$Lnjp_800C82A4_8
	lui	$5,%hi(njp_800C7C04)
	addu	$4,$18,$0
	addiu	$5,$5,%lo(njp_800C7C04)
	lui	$6,%hi(njp_800C81E8)
	addiu	$6,$6,%lo(njp_800C81E8)
	lui	$7,%hi(njp_str_4898)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(njp_str_4898)
	addiu	$19,$18,32
	addu	$4,$19,$0
	addu	$5,$16,$0
	jal	GM_InitControl
	addu	$6,$17,$0
	bltz	$2,$Lnjp_800C82A4_6
	addiu	$2,$0,-1
	jal	GCL_GetOption
	addiu	$4,$0,112
	addiu	$4,$0,100
	jal	GCL_GetOption
	addu	$16,$2,$0
	addu	$4,$19,$0
	addu	$5,$16,$0
	jal	GM_ConfigControlString
	addu	$6,$2,$0
	addu	$4,$19,$0
	addu	$5,$0,$0
	addiu	$6,$0,450
	jal	GM_ConfigControlHazard
	addu	$7,$6,$0
	addiu	$2,$0,1
	sb	$2,89($19)
	addu	$4,$19,$0
	jal	GM_ConfigControlAttribute
	addu	$5,$2,$0
	jal	GM_ConfigControlTrapCheck
	addu	$4,$19,$0
	ori	$16,$0,0x92f1
	addiu	$4,$0,109
	jal	GCL_GetOption
	addiu	$20,$18,156
	beq	$2,$0,$Lnjp_800C82A4_0
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	addu	$16,$2,$0
$Lnjp_800C82A4_0:
	addu	$4,$20,$0
	addu	$5,$16,$0
	addiu	$6,$0,813
	jal	GM_InitObject
	ori	$7,$0,0x92f1
	jal	GM_ConfigObjectJoint
	addu	$4,$20,$0
	addu	$4,$20,$0
	addiu	$5,$18,384
	addiu	$6,$0,5887
	addiu	$7,$18,464
	addiu	$2,$18,1076
	sw	$2,16($29)
	addiu	$2,$18,1688
	sw	$19,20($29)
	jal	GM_ConfigMotionControl
	sw	$2,24($29)
	addu	$4,$20,$0
	jal	GM_ConfigObjectLight
	addiu	$5,$18,2120
	addu	$4,$18,$0
	lui	$2,%hi(GM_PlayerControl)
	sw	$19,%lo(GM_PlayerControl)($2)
	lui	$2,%hi(GM_PlayerPosition)
	addiu	$11,$2,%lo(GM_PlayerPosition)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lui	$2,%hi(GM_PlayerBody)
	jal	njp_sna_8004EB14
	sw	$20,%lo(GM_PlayerBody)($2)
	lui	$2,%hi(linkvarbuf)
	addiu	$22,$2,%lo(linkvarbuf)
	addiu	$21,$0,-1
	lhu	$3,32($22)
	addiu	$2,$0,450
	sh	$2,2436($18)
	lui	$2,%hi(GM_SnakeCamera)
	sw	$21,2116($18)
	sw	$21,2312($18)
	sh	$3,2434($18)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,2467($18)
	swr	$8,2464($18)
	swl	$9,2471($18)
	swr	$9,2468($18)
	lwl	$8,35($18)
	lwr	$8,32($18)
	lwl	$9,39($18)
	lwr	$9,36($18)
	swl	$8,2495($18)
	swr	$8,2492($18)
	swl	$9,2499($18)
	swr	$9,2496($18)
	addiu	$11,$2,%lo(GM_SnakeCamera)
	lwl	$8,2495($18)
	lwr	$8,2492($18)
	lwl	$9,2499($18)
	lwr	$9,2496($18)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	jal	GCL_GetOption
	addiu	$4,$0,111
	beq	$2,$0,$Lnjp_800C82A4_1
	addiu	$2,$0,6000
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2486($18)
	addiu	$2,$0,6000
$Lnjp_800C82A4_1:
	sh	$2,2192($18)
	jal	GCL_GetOption
	addiu	$4,$0,108
	beq	$2,$0,$Lnjp_800C82A4_2
	addiu	$2,$0,512
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2192($18)
	addiu	$2,$0,512
$Lnjp_800C82A4_2:
	sh	$2,2194($18)
	jal	GCL_GetOption
	addiu	$4,$0,114
	beq	$2,$0,$Lnjp_800C82A4_3
	addiu	$4,$0,116
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,2194($18)
	addiu	$4,$0,116
$Lnjp_800C82A4_3:
	lui	$16,%hi(njp_dword_800ABBDC)
	addiu	$2,$0,-1023
	lui	$17,%hi(njp_dword_800ABBD4)
	sh	$2,%lo(njp_dword_800ABBDC)($16)
	addiu	$2,$0,1023
	jal	GCL_GetOption
	sh	$2,%lo(njp_dword_800ABBD4)($17)
	beq	$2,$0,$Lnjp_800C82A4_4
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	jal	GCL_NextStr
	sh	$2,%lo(njp_dword_800ABBDC)($16)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sh	$2,%lo(njp_dword_800ABBD4)($17)
$Lnjp_800C82A4_4:
	sw	$21,2508($18)
	jal	GCL_GetOption
	addiu	$4,$0,101
	beq	$2,$0,$Lnjp_800C82A4_5
	nop
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,2508($18)
$Lnjp_800C82A4_5:
	addu	$4,$18,$0
	lui	$5,%hi(njp_sna_anim_idle_800C4200)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_idle_800C4200)
	addu	$4,$20,$0
	addu	$5,$0,$0
	addu	$6,$5,$0
	jal	GM_ConfigObjectAction
	addu	$7,$5,$0
	jal	GM_ActMotion
	addu	$4,$20,$0
	lui	$2,%hi(GV_PadData)
	addiu	$2,$2,%lo(GV_PadData)
	lh	$3,180($18)
	addiu	$17,$29,40
	sw	$2,2320($18)
	addiu	$2,$0,650
	sw	$3,1944($18)
	sh	$3,82($18)
	addiu	$3,$0,300
	sh	$3,40($29)
	sh	$2,2($17)
	jal	GM_AllocTarget
	sh	$3,4($17)
	addu	$16,$2,$0
	addu	$4,$16,$0
	addiu	$5,$0,159
	addiu	$6,$0,1
	addu	$7,$17,$0
	jal	GM_SetTarget
	sw	$16,2200($18)
	addu	$4,$16,$0
	addiu	$5,$0,1
	addiu	$6,$0,-1
	lui	$2,%hi(DG_ZeroVector)
	sw	$0,16($29)
	lh	$7,22($22)
	addiu	$2,$2,%lo(DG_ZeroVector)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addu	$4,$16,$0
	addu	$5,$0,$0
	addu	$6,$5,$0
	addiu	$7,$18,2288
	addiu	$2,$18,2296
	jal	GM_SetCaptureTarget
	sw	$2,16($29)
	addu	$4,$16,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	addu	$4,$19,$0
	lhu	$2,22($22)
	addu	$5,$20,$0
	sh	$2,2430($18)
	addiu	$2,$0,6
	sh	$2,34($29)
	addiu	$2,$0,12
	sh	$2,36($29)
	addiu	$2,$0,15
	sh	$2,38($29)
	addiu	$2,$18,2188
	sh	$0,32($29)
	sw	$2,16($29)
	lhu	$6,34($29)
	lhu	$2,32($29)
	lhu	$7,38($29)
	sll	$6,$6,16
	or	$6,$2,$6
	lhu	$2,36($29)
	sll	$7,$7,16
	jal	NewShadow2
	or	$7,$2,$7
	addu	$5,$17,$0
	addiu	$6,$29,48
	addiu	$7,$18,2532
	sw	$2,2184($18)
	lui	$2,%hi(dword_800ABA1C)
	sw	$0,%lo(dword_800ABA1C)($2)
	lui	$2,%hi(njp_pVec_800ABBCC)
	addiu	$3,$0,-65
	sw	$0,%lo(njp_pVec_800ABBCC)($2)
	addiu	$2,$0,-883
	sh	$21,30($22)
	sh	$2,44($29)
	addiu	$2,$0,-45
	sh	$0,40($29)
	sh	$3,42($29)
	sh	$0,48($29)
	sh	$3,50($29)
	sh	$2,52($29)
	lw	$4,156($18)
	lui	$2,%hi(snainit_item_800A9420)
	sw	$21,%lo(snainit_item_800A9420)($2)
	jal	NewKatana
	addiu	$4,$4,440
	addu	$2,$0,$0
$Lnjp_800C82A4_6:
	bltz	$2,$Lnjp_800C82A4_7
	lui	$2,%hi(njp_snainit_actor)
	sw	$18,%lo(njp_snainit_actor)($2)
	j	$Lnjp_800C82A4_9
	addu	$2,$18,$0
$Lnjp_800C82A4_7:
	jal	GV_DestroyActor
	addu	$4,$18,$0
$Lnjp_800C82A4_8:
	addu	$2,$0,$0
$Lnjp_800C82A4_9:
	lw	$31,84($29)
	lw	$22,80($29)
	lw	$21,76($29)
	lw	$20,72($29)
	lw	$19,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,88
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
njp_str_4898:
	.ascii	"njaplay.c"
	.byte	0
	.text
