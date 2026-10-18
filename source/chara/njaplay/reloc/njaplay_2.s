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
	lui	$2,%hi(njp_pVec_800ABBC8)
	sw	$0,%lo(njp_bss_20)($30)
	sw	$0,%lo(njp_pVec_800ABBCC)($22)
	sw	$4,%lo(njp_pVec_800ABBC8)($2)
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
	lui	$5,%hi(njp_sna_anim_800C5634)
	jal	njp_sna_start_anim_8004E1F4
	addiu	$5,$5,%lo(njp_sna_anim_800C5634)
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
	lui	$5,%hi(njp_sna_anim_800C573C)
	addiu	$5,$5,%lo(njp_sna_anim_800C573C)
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
	.text
