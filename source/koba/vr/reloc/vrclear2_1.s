	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2_800DF6F4
Vrclear2_800DF6F4:
	addiu	$29,$29,-40
	sw	$18,32($29)
	addu	$18,$4,$0
	sw	$31,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$3,976($18)
	nop
	slti	$2,$3,111
	bne	$2,$0,$LVrclear2_800DF6F4_0
	addiu	$2,$3,12
	addiu	$2,$0,111
$LVrclear2_800DF6F4_0:
	sw	$2,976($18)
	lw	$3,980($18)
	nop
	slti	$2,$3,160
	bne	$2,$0,$LVrclear2_800DF6F4_1
	addiu	$2,$3,12
	addiu	$2,$0,160
$LVrclear2_800DF6F4_1:
	sw	$2,980($18)
	lhu	$2,980($18)
	addiu	$4,$18,112
	sh	$2,16($29)
	lhu	$2,976($18)
	addiu	$17,$0,320
	sh	$2,18($29)
	lw	$2,980($18)
	addiu	$5,$29,16
	sll	$2,$2,1
	subu	$2,$17,$2
	sh	$2,20($29)
	lw	$2,976($18)
	addiu	$16,$0,224
	sll	$2,$2,1
	subu	$2,$16,$2
	jal	SetDrawArea
	sh	$2,22($29)
	lhu	$2,980($18)
	nop
	addu	$2,$2,$17
	sh	$2,16($29)
	lhu	$2,976($18)
	nop
	sh	$2,18($29)
	lw	$2,980($18)
	addiu	$4,$18,124
	sll	$2,$2,1
	subu	$17,$17,$2
	sh	$17,20($29)
	lw	$2,976($18)
	addiu	$5,$29,16
	sll	$2,$2,1
	subu	$16,$16,$2
	jal	SetDrawArea
	sh	$16,22($29)
	lw	$2,60($18)
	nop
	sll	$2,$2,6
	slti	$2,$2,321
	bne	$2,$0,$LVrclear2_800DF6F4_3
	lui	$2,%hi(GV_Clock)
	lw	$3,%lo(GV_Clock)($2)
	nop
	sll	$3,$3,6
	addu	$2,$3,$18
	addiu	$4,$2,136
	lui	$2,%hi(DG_Chanls+492)
	addiu	$2,$2,%lo(DG_Chanls+492)
	addu	$3,$3,$2
	addiu	$2,$3,108
	addiu	$3,$3,172
$LVrclear2_800DF6F4_2:
	lw	$10,0($2)
	lw	$11,4($2)
	lw	$12,8($2)
	lw	$13,12($2)
	sw	$10,0($4)
	sw	$11,4($4)
	sw	$12,8($4)
	sw	$13,12($4)
	addiu	$2,$2,16
	bne	$2,$3,$LVrclear2_800DF6F4_2
	addiu	$4,$4,16
	lui	$9,0xff
	ori	$9,$9,0xffff
	lui	$3,%hi(DG_Chanls+492)
	lui	$2,%hi(GV_Clock)
	addiu	$3,$3,%lo(DG_Chanls+492)
	lw	$5,%lo(GV_Clock)($2)
	lui	$8,0xff00
	sll	$6,$5,2
	addu	$6,$6,$3
	sll	$4,$5,1
	addu	$4,$4,$5
	sll	$4,$4,2
	addu	$7,$4,$18
	addiu	$4,$4,112
	addu	$4,$18,$4
	lw	$2,0($6)
	lw	$3,112($7)
	lw	$2,784($2)
	and	$3,$3,$8
	and	$2,$2,$9
	or	$3,$3,$2
	sw	$3,112($7)
	lw	$3,0($6)
	and	$4,$4,$9
	lw	$2,784($3)
	sll	$5,$5,6
	and	$2,$2,$8
	or	$2,$2,$4
	addu	$4,$5,$18
	addiu	$5,$5,136
	sw	$2,784($3)
	lw	$2,0($6)
	lw	$3,136($4)
	lw	$2,0($2)
	and	$3,$3,$8
	and	$2,$2,$9
	or	$3,$3,$2
	sw	$3,136($4)
	lw	$3,0($6)
	addu	$5,$18,$5
	lw	$2,0($3)
	and	$5,$5,$9
	and	$2,$2,$8
	or	$2,$2,$5
	sw	$2,0($3)
$LVrclear2_800DF6F4_3:
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2Draw
Vrclear2Draw:
	addiu	$29,$29,-48
	sw	$18,24($29)
	addu	$18,$4,$0
	sw	$31,40($29)
	sw	$21,36($29)
	sw	$20,32($29)
	sw	$19,28($29)
	sw	$17,20($29)
	jal	Vrclear2_800DF134
	sw	$16,16($29)
	lh	$3,38($18)
	nop
	sltiu	$2,$3,7
	beq	$2,$0,$LVrclear2Draw_19
	lui	$2,%hi(Vrclear2Draw_jtbl_800E183C)
	addiu	$2,$2,%lo(Vrclear2Draw_jtbl_800E183C)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$LVrclear2Draw_0:
	lui	$2,%hi(vrclear2_buttons)
	lbu	$17,954($18)
	lhu	$3,36($18)
	addiu	$16,$2,%lo(vrclear2_buttons)
	beq	$17,$0,$LVrclear2Draw_2
	sh	$3,34($18)
$LVrclear2Draw_1:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2Draw_1
	addiu	$16,$16,120
$LVrclear2Draw_2:
	lw	$2,60($18)
	addu	$5,$18,$0
	addu	$4,$2,$0
	addiu	$2,$2,1
	jal	Vrclear2_800DED20
	sw	$2,60($18)
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x10
	bne	$2,$0,$LVrclear2Draw_3
	nop
	jal	MoveCursor
	addu	$4,$18,$0
	j	$LVrclear2Draw_16
	addiu	$4,$18,268
$LVrclear2Draw_3:
	jal	CheckPad
	addu	$4,$18,$0
	beq	$2,$0,$LVrclear2Draw_19
	lui	$3,%hi(linkvarbuf)
	lbu	$2,952($18)
	addiu	$3,$3,%lo(linkvarbuf)
	addiu	$2,$2,16
	sll	$2,$2,1
	addu	$2,$2,$3
	lh	$2,0($2)
	lw	$4,60($18)
	sll	$2,$2,1
	addiu	$3,$2,30
	slt	$2,$3,$4
	beq	$2,$0,$LVrclear2Draw_4
	nop
	addu	$3,$4,$0
$LVrclear2Draw_4:
	j	$LVrclear2Draw_19
	sw	$3,60($18)
$LVrclear2Draw_5:
	lhu	$2,32($18)
	addu	$4,$18,$0
	addiu	$2,$2,1
	jal	CheckMessage
	sh	$2,32($18)
	jal	OpenButtons
	addu	$4,$2,$0
	beq	$2,$0,$LVrclear2Draw_19
	nop
	lw	$2,44($18)
	sh	$0,38($18)
	sh	$0,32($18)
	beq	$2,$0,$LVrclear2Draw_6
	sw	$0,60($18)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2Draw_7
	lui	$2,%hi(GV_PadData+32)
	jal	GM_StreamPlayStart
	nop
$LVrclear2Draw_6:
	lui	$2,%hi(GV_PadData+32)
$LVrclear2Draw_7:
	lhu	$2,%lo(GV_PadData+32)($2)
	j	$LVrclear2Draw_19
	sw	$2,264($18)
$LVrclear2Draw_8:
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lw	$2,60($18)
	nop
	addiu	$2,$2,1
	j	$LVrclear2Draw_19
	sw	$2,60($18)
$LVrclear2Draw_9:
	addu	$19,$0,$0
	lbu	$17,954($18)
	lui	$2,%hi(vrclear2_buttons)
	beq	$17,$0,$LVrclear2Draw_13
	addiu	$16,$2,%lo(vrclear2_buttons)
	addu	$21,$16,$0
	addiu	$20,$0,5
$LVrclear2Draw_10:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	lh	$3,34($18)
	nop
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$2,$21
	beq	$16,$2,$LVrclear2Draw_12
	nop
	lbu	$3,34($16)
	nop
	beq	$3,$20,$LVrclear2Draw_11
	addu	$2,$0,$0
	sltu	$2,$2,$3
$LVrclear2Draw_11:
	or	$19,$19,$2
$LVrclear2Draw_12:
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2Draw_10
	addiu	$16,$16,120
$LVrclear2Draw_13:
	lw	$2,60($18)
	addu	$5,$18,$0
	addu	$4,$2,$0
	addiu	$2,$2,1
	jal	Vrclear2_800DED20
	sw	$2,60($18)
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	bne	$19,$0,$LVrclear2Draw_15
	addiu	$2,$0,3
	lh	$3,38($18)
	nop
	bne	$3,$2,$LVrclear2Draw_15
	addiu	$2,$0,2
	lh	$3,34($18)
	nop
	bne	$3,$2,$LVrclear2Draw_14
	lui	$16,%hi(vrclear2_buttons)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2Draw_14
	nop
	lw	$4,964($18)
	jal	GCL_SetVar
	addiu	$5,$0,-1
	lui	$16,%hi(vrclear2_buttons)
$LVrclear2Draw_14:
	lh	$2,34($18)
	addiu	$16,$16,%lo(vrclear2_buttons)
	sll	$4,$2,4
	subu	$4,$4,$2
	sll	$4,$4,3
	jal	VrMenu_ExecItem
	addu	$4,$4,$16
	lh	$2,34($18)
	addiu	$17,$0,5
	sh	$17,38($18)
	sll	$4,$2,4
	subu	$4,$4,$2
	sll	$4,$4,3
	jal	VrMenu_ExecItem
	addu	$4,$4,$16
	sh	$17,38($18)
$LVrclear2Draw_15:
	addiu	$4,$18,268
$LVrclear2Draw_16:
	lui	$5,%hi(vrclear2_buttons+24)
	lh	$2,36($18)
	addiu	$5,$5,%lo(vrclear2_buttons+24)
	sll	$3,$2,4
	subu	$3,$3,$2
	sll	$3,$3,3
	lui	$2,%hi(GV_Clock)
	lw	$7,%lo(GV_Clock)($2)
	addu	$5,$3,$5
	sll	$6,$7,2
	addu	$6,$6,$7
	sll	$6,$6,6
	addiu	$6,$6,276
	addu	$6,$18,$6
	sll	$7,$7,4
	addiu	$7,$7,916
	jal	VrMenu_UpdateFrame
	addu	$7,$18,$7
	j	$LVrclear2Draw_19
	nop
$LVrclear2Draw_17:
	jal	Vrclear2_800DF6F4
	addu	$4,$18,$0
	lbu	$17,954($18)
	lui	$2,%hi(vrclear2_buttons)
	beq	$17,$0,$LVrclear2Draw_19
	addiu	$16,$2,%lo(vrclear2_buttons)
$LVrclear2Draw_18:
	jal	VrMenu_DrawItem
	addu	$4,$16,$0
	addiu	$17,$17,-1
	bne	$17,$0,$LVrclear2Draw_18
	addiu	$16,$16,120
$LVrclear2Draw_19:
	lw	$31,40($29)
	lw	$21,36($29)
	lw	$20,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2Init
Vrclear2Init:
	addiu	$29,$29,-56
	sw	$18,48($29)
	addu	$18,$4,$0
	lui	$2,%hi(linkvarbuf)
	addiu	$5,$2,%lo(linkvarbuf)
	sw	$31,52($29)
	sw	$17,44($29)
	sw	$16,40($29)
	lh	$3,34($5)
	lui	$2,%hi(vrclear2_weights)
	addiu	$11,$2,%lo(vrclear2_weights)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	lb	$10,8($11)
	swl	$8,19($29)
	swr	$8,16($29)
	swl	$9,23($29)
	swr	$9,20($29)
	sb	$10,24($29)
	lb	$8,9($11)
	nop
	sb	$8,25($29)
	bgez	$3,$LVrclear2Init_1
	addu	$4,$0,$0
	addiu	$3,$0,34
$LVrclear2Init_0:
	slti	$2,$4,11
	beq	$2,$0,$LVrclear2Init_2
	addiu	$2,$0,10
	addiu	$3,$3,2
	addu	$2,$3,$5
	lh	$2,0($2)
	nop
	bltz	$2,$LVrclear2Init_0
	addiu	$4,$4,1
$LVrclear2Init_1:
	addiu	$2,$0,10
$LVrclear2Init_2:
	bne	$4,$2,$LVrclear2Init_3
	addiu	$2,$4,1
	addiu	$2,$0,1
	sb	$2,952($18)
	lui	$2,%hi(linkvarbuf+34)
	sb	$0,953($18)
	j	$LVrclear2Init_4
	sh	$0,%lo(linkvarbuf+34)($2)
$LVrclear2Init_3:
	sb	$2,952($18)
	andi	$2,$4,0xff
	sltiu	$2,$2,10
	beq	$2,$0,$LVrclear2Init_4
	nop
	lbu	$2,952($18)
	nop
	addu	$2,$2,$29
	lbu	$2,15($2)
	nop
	sb	$2,953($18)
$LVrclear2Init_4:
	lw	$2,1008($18)
	nop
	bne	$2,$0,$LVrclear2Init_5
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$4,$0,-17
	and	$3,$3,$4
	sw	$3,%lo(VR_Flags)($2)
$LVrclear2Init_5:
	lw	$3,1008($18)
	addiu	$2,$0,16
	bne	$3,$2,$LVrclear2Init_6
	lui	$2,%hi(VR_Flags)
	sw	$0,%lo(VR_Flags)($2)
$LVrclear2Init_6:
	lw	$4,988($18)
	nop
	beq	$4,$0,$LVrclear2Init_7
	lui	$2,%hi(VR_Flags)
	lw	$2,1012($18)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$LVrclear2Init_7
	lui	$2,%hi(VR_Flags)
	lw	$5,984($18)
	jal	SetClearFlag
	nop
	lui	$2,%hi(VR_Flags)
$LVrclear2Init_7:
	lw	$3,%lo(VR_Flags)($2)
	lw	$4,1012($18)
	andi	$2,$3,0x6
	srl	$5,$2,1
	addiu	$2,$0,-5
	and	$4,$4,$2
	sw	$4,1012($18)
	addiu	$2,$0,3
	lui	$3,%hi(vrclear2_buttons+128)
	sb	$2,954($18)
	addiu	$2,$0,-1
	sh	$2,%lo(vrclear2_buttons+128)($3)
	slti	$2,$5,3
	bne	$2,$0,$LVrclear2Init_8
	lui	$2,%hi(VR_Flags)
	addiu	$5,$0,-1
$LVrclear2Init_8:
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2Init_9
	addiu	$2,$0,-1
	beq	$5,$2,$LVrclear2Init_9
	sll	$2,$5,2
	addu	$2,$18,$2
	lw	$4,44($2)
	j	$LVrclear2Init_10
	nop
$LVrclear2Init_9:
	lw	$4,56($18)
$LVrclear2Init_10:
	jal	GM_VoxStream
	lui	$5,0x4000
	addiu	$4,$18,112
	addiu	$16,$29,32
	addu	$5,$16,$0
	sh	$0,32($29)
	sh	$0,34($29)
	sh	$0,36($29)
	jal	SetDrawArea
	sh	$0,38($29)
	addiu	$4,$18,124
	jal	SetDrawArea
	addu	$5,$16,$0
	lui	$2,%hi(vrclear2_buttons)
	addiu	$5,$2,%lo(vrclear2_buttons)
	lw	$3,140($5)
	lw	$2,260($5)
	nop
	bne	$3,$2,$LVrclear2Init_13
	addiu	$2,$0,1
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	addiu	$3,$0,2
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2Init_11
	sh	$3,36($18)
	lw	$2,1012($18)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2Init_11
	addiu	$3,$0,3
	lhu	$2,122($5)
	lhu	$4,146($5)
	sh	$3,8($5)
	sh	$0,372($5)
	sh	$2,362($5)
	j	$LVrclear2Init_12
	sh	$4,386($5)
$LVrclear2Init_11:
	lui	$2,%hi(vrclear2_buttons)
	addiu	$2,$2,%lo(vrclear2_buttons)
	addiu	$3,$0,-1
	sh	$3,8($2)
	addiu	$3,$0,1
	sh	$3,372($2)
$LVrclear2Init_12:
	lui	$2,%hi(vrclear2_buttons)
	addiu	$2,$2,%lo(vrclear2_buttons)
	sh	$0,124($2)
	sh	$0,126($2)
	j	$LVrclear2Init_14
	sh	$0,120($2)
$LVrclear2Init_13:
	sh	$2,36($18)
$LVrclear2Init_14:
	lui	$3,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($3)
	nop
	andi	$2,$2,0x20
	beq	$2,$0,$LVrclear2Init_15
	nop
	sh	$0,36($18)
$LVrclear2Init_15:
	lw	$2,%lo(VR_Flags)($3)
	nop
	andi	$2,$2,0x8
	beq	$2,$0,$LVrclear2Init_16
	nop
	lw	$2,1012($18)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrclear2Init_16
	addiu	$2,$0,3
	sh	$2,36($18)
$LVrclear2Init_16:
	lw	$2,1012($18)
	nop
	andi	$3,$2,0x1
	addiu	$2,$0,1
	bne	$3,$2,$LVrclear2Init_17
	addiu	$4,$0,4
	lui	$4,%hi(vrclear2_str_replay)
	addiu	$4,$4,%lo(vrclear2_str_replay)
	addiu	$2,$0,2
	lui	$17,%hi(vrclear2_buttons)
	addiu	$16,$17,%lo(vrclear2_buttons)
	sh	$2,36($18)
	addiu	$2,$0,-1
	sh	$2,8($16)
	addiu	$2,$0,3
	sh	$3,372($16)
	sh	$0,124($16)
	sh	$0,126($16)
	sh	$0,120($16)
	jal	GV_StrCode
	sb	$2,954($18)
	addu	$4,$2,$0
	jal	DG_GetTexture
	sw	$4,16($16)
	addiu	$3,$16,40
	sw	$2,36($16)
	lbu	$6,8($2)
	lbu	$5,10($2)
	lbu	$4,9($2)
	lbu	$7,11($2)
	addu	$5,$6,$5
	sb	$4,13($3)
	sb	$4,21($3)
	addu	$4,$4,$7
	sb	$6,12($3)
	sb	$5,20($3)
	sb	$6,28($3)
	sb	$4,29($3)
	sb	$5,36($3)
	sb	$4,37($3)
	lhu	$4,4($2)
	nop
	sh	$4,22($3)
	lhu	$4,6($2)
	nop
	sh	$4,14($3)
	addiu	$3,$16,80
	lbu	$6,8($2)
	lbu	$5,10($2)
	lbu	$4,9($2)
	lbu	$7,11($2)
	addu	$5,$6,$5
	sb	$4,13($3)
	sb	$4,21($3)
	addu	$4,$4,$7
	sb	$6,12($3)
	sb	$5,20($3)
	sb	$6,28($3)
	sb	$4,29($3)
	sb	$5,36($3)
	sb	$4,37($3)
	lhu	$4,4($2)
	nop
	sh	$4,22($3)
	lhu	$2,6($2)
	nop
	sh	$2,14($3)
	addiu	$2,$0,56
	sh	$2,4($16)
	addiu	$2,$0,8
	sh	$2,6($16)
	addiu	$2,$0,132
	sh	$2,%lo(vrclear2_buttons)($17)
	addiu	$2,$0,76
	sh	$2,28($16)
	addiu	$2,$0,14
	sh	$2,30($16)
	addiu	$2,$0,121
	sh	$2,24($16)
	addiu	$4,$0,4
$LVrclear2Init_17:
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$2,$0,2
	sh	$2,38($18)
	addiu	$2,$0,32
	sh	$4,34($18)
	sh	$0,32($18)
	sw	$0,976($18)
	andi	$3,$3,0x28
	bne	$3,$2,$LVrclear2Init_18
	sw	$0,980($18)
	sh	$4,38($18)
$LVrclear2Init_18:
	jal	VrMenu_LoadFrameTexture
	nop
	addiu	$4,$18,276
	addiu	$5,$18,916
	jal	VrMenu_InitFrame
	addu	$6,$2,$0
	addiu	$2,$0,160
	sh	$2,268($18)
	addiu	$2,$0,112
	sh	$2,270($18)
	sh	$0,272($18)
	sh	$0,274($18)
	lw	$31,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.rdata
	.align	2
Vrclear2Draw_jtbl_800E183C:
	.word	$LVrclear2Draw_0
	.word	$LVrclear2Draw_19
	.word	$LVrclear2Draw_5
	.word	$LVrclear2Draw_9
	.word	$LVrclear2Draw_8
	.word	$LVrclear2Draw_9
	.word	$LVrclear2Draw_17
	.align	2
vrclear2_weights:
	.word	0x0A0A010A
	.word	0x0A0A1E0A
	.word	0x00000A0A
	.align	2
vrclear2_str_replay:
	.ascii	"replay"
	.byte	0
	.text
