	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxInitPack
VrBoxInitPack:
	addiu	$2,$0,9
	sb	$2,3($4)
	addiu	$2,$0,46
	sb	$2,7($4)
	lbu	$6,8($5)
	lbu	$3,10($5)
	lbu	$2,9($5)
	lbu	$7,11($5)
	addu	$3,$6,$3
	sb	$2,13($4)
	sb	$2,21($4)
	addu	$2,$2,$7
	sb	$6,12($4)
	sb	$3,20($4)
	sb	$6,28($4)
	sb	$2,29($4)
	sb	$3,36($4)
	sb	$2,37($4)
	lhu	$2,4($5)
	nop
	sh	$2,22($4)
	lhu	$2,6($5)
	jr	$31
	sh	$2,14($4)
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxMakePrim
VrBoxMakePrim:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	addiu	$6,$17,832
	addiu	$4,$17,816
	addiu	$7,$17,808
	sw	$31,32($29)
	sw	$16,24($29)
	sh	$0,2($6)
	sh	$0,826($17)
	sh	$0,2($4)
	sh	$0,2($7)
	lhu	$2,36($17)
	addiu	$3,$17,36
	addiu	$2,$2,256
	sh	$2,824($17)
	sh	$2,808($17)
	lhu	$2,4($3)
	nop
	addiu	$2,$2,256
	sh	$2,4($4)
	sh	$2,4($7)
	lhu	$2,36($17)
	addiu	$5,$0,1
	addiu	$2,$2,-256
	sh	$2,832($17)
	sh	$2,8($7)
	lhu	$2,4($3)
	addiu	$4,$0,4114
	addiu	$2,$2,-256
	sh	$2,4($6)
	addu	$6,$0,$0
	sh	$2,20($7)
	jal	DG_MakePrim
	sw	$0,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LVrBoxMakePrim_0
	nop
	jal	DG_QueuePrim
	addu	$4,$16,$0
	lui	$2,%hi(GM_CurrentMap)
	lw	$2,%lo(GM_CurrentMap)($2)
	nop
	sh	$2,40($16)
$LVrBoxMakePrim_0:
	sw	$16,804($17)
	beq	$16,$0,$LVrBoxMakePrim_1
	addiu	$2,$0,-1
	addiu	$2,$0,500
	sh	$2,46($16)
	lui	$4,%hi(vrbox_str_shadow)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox_str_shadow)
	jal	DG_GetTexture
	addu	$4,$2,$0
	addu	$17,$2,$0
	beq	$17,$0,$LVrBoxMakePrim_1
	addiu	$2,$0,-1
	lw	$4,64($16)
	jal	VrBoxInitPack
	addu	$5,$17,$0
	lw	$4,68($16)
	jal	VrBoxInitPack
	addu	$5,$17,$0
	lw	$2,64($16)
	addiu	$3,$0,80
	sb	$3,4($2)
	lw	$2,64($16)
	nop
	sb	$3,5($2)
	lw	$2,64($16)
	nop
	sb	$3,6($2)
	lw	$2,68($16)
	nop
	sb	$3,4($2)
	lw	$2,68($16)
	nop
	sb	$3,5($2)
	lw	$4,68($16)
	addu	$2,$0,$0
	sb	$3,6($4)
$LVrBoxMakePrim_1:
	lw	$31,32($29)
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
	.globl	VrBoxUpdateFlags
VrBoxUpdateFlags:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,28($29)
	sw	$18,24($29)
	sw	$17,20($29)
	lh	$4,722($16)
	nop
	andi	$3,$4,0xe0
	sra	$3,$3,5
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	andi	$17,$4,0x1f
	andi	$4,$4,0x1c00
	lw	$3,776($16)
	sh	$2,784($16)
	andi	$2,$3,0x1
	beq	$2,$0,$LVrBoxUpdateFlags_3
	sra	$18,$4,10
	srl	$2,$3,26
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxUpdateFlags_2
	srl	$2,$3,3
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxUpdateFlags_0
	nop
	bne	$17,$0,$LVrBoxUpdateFlags_2
	addiu	$4,$16,36
	j	$LVrBoxUpdateFlags_1
	addiu	$5,$0,178
$LVrBoxUpdateFlags_0:
	beq	$17,$0,$LVrBoxUpdateFlags_2
	addiu	$4,$16,36
	addiu	$5,$0,176
$LVrBoxUpdateFlags_1:
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBoxUpdateFlags_2:
	lw	$2,776($16)
	addiu	$3,$0,-9
	and	$2,$2,$3
	andi	$3,$17,0x1
	sll	$3,$3,3
	or	$2,$2,$3
	sw	$2,776($16)
$LVrBoxUpdateFlags_3:
	lw	$2,776($16)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBoxUpdateFlags_4
	sll	$2,$18,2
	addu	$2,$2,$18
	sll	$2,$2,2
	sw	$2,780($16)
$LVrBoxUpdateFlags_4:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	addiu	$2,$0,1
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxCopyPath
VrBoxCopyPath:
	lw	$2,80($4)
	nop
	lw	$2,8($2)
	nop
	lw	$3,0($2)
	lb	$2,786($4)
	lw	$3,24($3)
	sll	$2,$2,3
	addu	$3,$3,$2
	lh	$2,0($3)
	nop
	bgtz	$2,$LVrBoxCopyPath_0
	sw	$2,452($4)
	jr	$31
	addiu	$2,$0,-1
$LVrBoxCopyPath_0:
	lw	$7,4($3)
	blez	$2,$LVrBoxCopyPath_2
	addu	$6,$0,$0
	addu	$3,$4,$0
	addiu	$5,$7,6
$LVrBoxCopyPath_1:
	lhu	$2,0($7)
	nop
	sh	$2,456($3)
	lhu	$2,-2($5)
	addiu	$7,$7,8
	sh	$2,458($3)
	lhu	$2,-4($5)
	addiu	$6,$6,1
	sh	$2,460($3)
	lhu	$2,0($5)
	addiu	$5,$5,8
	sh	$2,462($3)
	lw	$2,452($4)
	nop
	slt	$2,$6,$2
	bne	$2,$0,$LVrBoxCopyPath_1
	addiu	$3,$3,8
$LVrBoxCopyPath_2:
	jr	$31
	addu	$2,$0,$0
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxNextPathPoint
VrBoxNextPathPoint:
	lw	$3,712($4)
	lw	$2,452($4)
	addiu	$3,$3,1
	slt	$2,$3,$2
	bne	$2,$0,$LVrBoxNextPathPoint_0
	sll	$2,$3,3
	addu	$3,$0,$0
	sll	$2,$3,3
$LVrBoxNextPathPoint_0:
	addu	$2,$4,$2
	sw	$3,712($4)
	lwl	$5,459($2)
	lwr	$5,456($2)
	lwl	$6,463($2)
	lwr	$6,460($2)
	swl	$5,719($4)
	swr	$5,716($4)
	swl	$6,723($4)
	swr	$6,720($4)
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxMoveToTarget
VrBoxMoveToTarget:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	sw	$16,24($29)
	addu	$16,$5,$0
	addiu	$4,$17,716
	addiu	$5,$17,36
	sw	$31,32($29)
	jal	GV_SubVec3
	addiu	$6,$29,16
	jal	GV_VecLen3
	addiu	$4,$29,16
	slt	$2,$2,$16
	bne	$2,$0,$LVrBoxMoveToTarget_0
	nop
	jal	GV_VecLen3
	addiu	$4,$29,16
	addiu	$4,$29,16
	addiu	$5,$17,104
	lw	$7,780($17)
	jal	GV_LenVec3
	addu	$6,$2,$0
	j	$LVrBoxMoveToTarget_1
	addu	$2,$0,$0
$LVrBoxMoveToTarget_0:
	addiu	$2,$0,1
$LVrBoxMoveToTarget_1:
	lw	$31,32($29)
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
	.globl	VrBoxUpdateHeight
VrBoxUpdateHeight:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	sw	$18,32($29)
	addiu	$18,$17,36
	sw	$16,24($29)
	addiu	$16,$17,808
	sw	$31,36($29)
	lw	$2,44($18)
	addu	$5,$18,$0
	lw	$4,8($2)
	jal	HZD_LevelHazardCheck
	addiu	$6,$0,3
	jal	HZD_GetLevelHeight
	addiu	$4,$29,16
	lhu	$2,16($29)
	nop
	sh	$2,834($17)
	sh	$2,826($17)
	sh	$2,818($17)
	sh	$2,2($16)
	lw	$3,16($29)
	addiu	$2,$0,-30000
	beq	$3,$2,$LVrBoxUpdateHeight_0
	addiu	$3,$0,7
	lw	$2,776($17)
	nop
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxUpdateHeight_1
	nop
$LVrBoxUpdateHeight_0:
	j	$LVrBoxUpdateHeight_2
	addu	$3,$0,$0
$LVrBoxUpdateHeight_1:
	lw	$2,844($17)
	nop
	sll	$2,$2,5
	addiu	$3,$2,128
$LVrBoxUpdateHeight_2:
	lhu	$2,0($18)
	nop
	addu	$2,$2,$3
	sh	$2,16($16)
	sh	$2,0($16)
	lhu	$2,4($18)
	nop
	addu	$2,$2,$3
	sh	$2,12($16)
	sh	$2,4($16)
	lhu	$2,0($18)
	nop
	subu	$2,$2,$3
	sh	$2,24($16)
	sh	$2,8($16)
	lhu	$2,4($18)
	nop
	subu	$2,$2,$3
	sh	$2,28($16)
	sh	$2,20($16)
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
	.globl	VrBoxStart
VrBoxStart:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	sw	$31,24($29)
	sw	$17,20($29)
	lw	$3,732($16)
	addiu	$2,$0,28
	sh	$2,0($3)
	sh	$0,6($3)
	lhu	$2,792($16)
	nop
	sh	$2,38($3)
	lw	$2,776($16)
	nop
	ori	$2,$2,0x8
	sw	$2,776($16)
	lbu	$2,776($16)
	addiu	$17,$16,36
	sw	$0,772($16)
	sw	$0,840($16)
	srl	$2,$2,7
	bne	$2,$0,$LVrBoxStart_0
	sw	$0,844($16)
	lwl	$7,459($16)
	lwr	$7,456($16)
	lwl	$8,463($16)
	lwr	$8,460($16)
	swl	$7,39($16)
	swr	$7,36($16)
	swl	$8,43($16)
	swr	$8,40($16)
	sw	$0,712($16)
	lwl	$7,459($16)
	lwr	$7,456($16)
	lwl	$8,463($16)
	lwr	$8,460($16)
	swl	$7,719($16)
	swr	$7,716($16)
	swl	$8,723($16)
	swr	$8,720($16)
$LVrBoxStart_0:
	lw	$2,776($16)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxStart_1
	addiu	$2,$0,1
	lw	$3,768($16)
	nop
	sw	$2,12($3)
$LVrBoxStart_1:
	lw	$2,160($16)
	addu	$4,$17,$0
	lw	$7,0($2)
	lw	$8,4($2)
	lw	$9,8($2)
	lw	$10,12($2)
	sw	$7,736($16)
	sw	$8,740($16)
	sw	$9,744($16)
	sw	$10,748($16)
	lw	$7,16($2)
	lw	$8,20($2)
	lw	$9,24($2)
	lw	$10,28($2)
	sw	$7,752($16)
	sw	$8,756($16)
	sw	$9,760($16)
	sw	$10,764($16)
	lw	$2,760($16)
	addiu	$5,$0,1
	addiu	$2,$2,200
	jal	GM_ConfigControlAttribute
	sw	$2,760($16)
	lw	$4,160($16)
	nop
	lw	$2,40($4)
	addiu	$3,$0,-129
	and	$2,$2,$3
	sw	$2,40($4)
	lw	$4,804($16)
	nop
	lw	$2,36($4)
	addiu	$3,$0,-257
	and	$2,$2,$3
	sw	$2,36($4)
	lw	$2,160($16)
	nop
	lw	$3,52($2)
	addiu	$2,$0,127
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	lw	$2,776($16)
	nop
	srl	$2,$2,26
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxStart_2
	addu	$4,$17,$0
	addiu	$5,$0,176
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBoxStart_2:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxStop
VrBoxStop:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$3,$0,-9
	sw	$31,20($29)
	lw	$2,776($16)
	lhu	$4,790($16)
	and	$2,$2,$3
	lw	$3,732($16)
	sw	$0,772($16)
	sw	$2,776($16)
	addiu	$2,$0,513
	sh	$4,788($16)
	sh	$2,0($3)
	sh	$0,6($3)
	lw	$2,776($16)
	addiu	$4,$16,36
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxStop_0
	sw	$0,840($16)
	lw	$2,768($16)
	nop
	sw	$0,12($2)
$LVrBoxStop_0:
	jal	GM_ConfigControlAttribute
	addu	$5,$0,$0
	lw	$3,160($16)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	sw	$2,40($3)
	lw	$3,804($16)
	nop
	lw	$2,36($3)
	nop
	ori	$2,$2,0x100
	sw	$2,36($3)
	lw	$31,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxAct
VrBoxAct:
	addiu	$29,$29,-112
	sw	$17,92($29)
	addu	$17,$4,$0
	lui	$2,%hi(VR_Status)
	lw	$3,%lo(VR_Status)($2)
	addiu	$2,$0,2
	sw	$31,104($29)
	sw	$19,100($29)
	sw	$18,96($29)
	bne	$3,$2,$LVrBoxAct_0
	sw	$16,88($29)
	jal	GV_DestroyActor
	nop
$LVrBoxAct_0:
	addiu	$5,$17,128
	addiu	$19,$17,36
	lhu	$4,48($19)
	lw	$3,32($17)
	lw	$18,732($17)
	lui	$2,%hi(GM_CurrentMap)
	jal	GV_ReceiveMessage
	sw	$3,%lo(GM_CurrentMap)($2)
	sb	$2,86($19)
	sll	$2,$2,24
	beq	$2,$0,$LVrBoxAct_6
	nop
	lw	$2,92($19)
	nop
	lhu	$3,4($2)
	addiu	$2,$0,17405
	beq	$3,$2,$LVrBoxAct_4
	slti	$2,$3,17406
	beq	$2,$0,$LVrBoxAct_1
	addiu	$2,$0,12835
	beq	$3,$2,$LVrBoxAct_2
	nop
	j	$LVrBoxAct_6
	nop
$LVrBoxAct_1:
	ori	$2,$0,0xc39b
	beq	$3,$2,$LVrBoxAct_3
	nop
	j	$LVrBoxAct_6
	nop
$LVrBoxAct_2:
	jal	GV_DestroyActor
	addu	$4,$17,$0
	j	$LVrBoxAct_6
	nop
$LVrBoxAct_3:
	lbu	$2,787($17)
	j	$LVrBoxAct_5
	sh	$0,790($17)
$LVrBoxAct_4:
	lbu	$2,787($17)
$LVrBoxAct_5:
	nop
	sw	$2,772($17)
$LVrBoxAct_6:
	lw	$4,776($17)
	nop
	srl	$2,$4,1
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBoxAct_8
	srl	$2,$4,8
	lb	$2,86($19)
	nop
	beq	$2,$0,$LVrBoxAct_7
	addu	$3,$0,$0
	lw	$2,92($19)
	nop
	lhu	$2,4($2)
	nop
	xori	$2,$2,0x9a1f
	sltiu	$3,$2,1
$LVrBoxAct_7:
	addiu	$2,$0,-3
	and	$2,$4,$2
	sll	$3,$3,1
	or	$2,$2,$3
	sw	$2,776($17)
	jal	GM_ActControl
	addu	$4,$19,$0
	jal	GM_ActObject2
	addiu	$4,$17,160
	addu	$4,$18,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PushTarget
	addu	$4,$18,$0
	jal	VrBoxUpdateHeight
	addu	$4,$17,$0
	j	$LVrBoxAct_40
	nop
$LVrBoxAct_8:
	andi	$2,$2,0x7
	addiu	$3,$0,7
	bne	$2,$3,$LVrBoxAct_9
	nop
	lhu	$2,78($19)
	nop
	addiu	$2,$2,128
	sh	$2,78($19)
	lw	$2,772($17)
	nop
	beq	$2,$0,$LVrBoxAct_10
	nop
	lhu	$2,76($19)
	nop
	addiu	$2,$2,8
	j	$LVrBoxAct_10
	sh	$2,76($19)
$LVrBoxAct_9:
	lhu	$2,78($19)
	nop
	addiu	$2,$2,64
	sh	$2,78($19)
$LVrBoxAct_10:
	lhu	$2,78($19)
	nop
	andi	$2,$2,0xfff
	sh	$2,78($19)
	lhu	$2,784($17)
	nop
	bne	$2,$0,$LVrBoxAct_12
	addiu	$2,$2,-1
	lw	$5,780($17)
	addu	$4,$17,$0
	jal	VrBoxMoveToTarget
	addiu	$5,$5,25
	beq	$2,$0,$LVrBoxAct_13
	nop
	jal	VrBoxUpdateFlags
	addu	$4,$17,$0
	jal	VrBoxNextPathPoint
	addu	$4,$17,$0
	lhu	$2,784($17)
	nop
	bne	$2,$0,$LVrBoxAct_11
	addiu	$2,$2,-1
	addiu	$4,$17,716
	addiu	$5,$17,36
	addiu	$16,$29,80
	jal	GV_SubVec3
	addu	$6,$16,$0
	jal	GV_VecLen3
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$17,104
	lw	$7,780($17)
	jal	GV_LenVec3
	addu	$6,$2,$0
	j	$LVrBoxAct_13
	nop
$LVrBoxAct_11:
	sh	$2,784($17)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,107($17)
	swr	$8,104($17)
	swl	$9,111($17)
	swr	$9,108($17)
	j	$LVrBoxAct_13
	nop
$LVrBoxAct_12:
	sh	$2,784($17)
$LVrBoxAct_13:
	lh	$2,790($17)
	nop
	beq	$2,$0,$LVrBoxAct_15
	nop
	lh	$4,788($17)
	lhu	$3,788($17)
	slti	$2,$4,2
	bne	$2,$0,$LVrBoxAct_14
	addiu	$2,$0,1
	addiu	$2,$3,-1
	j	$LVrBoxAct_15
	sh	$2,788($17)
$LVrBoxAct_14:
	bne	$4,$2,$LVrBoxAct_15
	nop
	jal	VrBoxStart
	addu	$4,$17,$0
	sh	$0,788($17)
$LVrBoxAct_15:
	jal	GM_ActControl
	addu	$4,$19,$0
	lhu	$2,2($19)
	lhu	$3,70($19)
	addu	$4,$17,$0
	addu	$2,$2,$3
	jal	VrBoxUpdateHeight
	sh	$2,2($19)
	addu	$4,$18,$0
	jal	GM_MoveTarget
	addu	$5,$19,$0
	jal	GM_PushTarget
	addu	$4,$18,$0
	jal	GM_ActObject2
	addiu	$4,$17,160
	lw	$2,160($17)
	nop
	lw	$8,0($2)
	lw	$9,4($2)
	lw	$10,8($2)
	lw	$11,12($2)
	sw	$8,736($17)
	sw	$9,740($17)
	sw	$10,744($17)
	sw	$11,748($17)
	lw	$8,16($2)
	lw	$9,20($2)
	lw	$10,24($2)
	lw	$11,28($2)
	sw	$8,752($17)
	sw	$9,756($17)
	sw	$10,760($17)
	sw	$11,764($17)
	lw	$2,760($17)
	lh	$3,788($17)
	addiu	$2,$2,200
	bne	$3,$0,$LVrBoxAct_21
	sw	$2,760($17)
	lw	$2,772($17)
	nop
	bne	$2,$0,$LVrBoxAct_21
	nop
	lw	$2,776($17)
	nop
	srl	$2,$2,3
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxAct_17
	nop
	lw	$3,844($17)
	nop
	slti	$2,$3,8
	beq	$2,$0,$LVrBoxAct_16
	addiu	$2,$3,1
	sw	$2,844($17)
	sll	$2,$2,9
	sw	$2,32($29)
	sw	$2,28($29)
	sw	$2,24($29)
	lw	$4,160($17)
	jal	ScaleMatrix
	addiu	$5,$29,24
$LVrBoxAct_16:
	lw	$3,732($17)
	addiu	$2,$0,28
	sh	$2,0($3)
	lw	$2,776($17)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxAct_19
	addiu	$2,$0,1
	lw	$3,768($17)
	j	$LVrBoxAct_19
	sw	$2,12($3)
$LVrBoxAct_17:
	lw	$3,844($17)
	nop
	blez	$3,$LVrBoxAct_19
	nop
	lw	$2,840($17)
	nop
	bne	$2,$0,$LVrBoxAct_18
	addiu	$2,$3,-1
	sw	$2,844($17)
	sll	$2,$2,9
	sw	$2,32($29)
	sw	$2,28($29)
	sw	$2,24($29)
	lw	$4,160($17)
	jal	ScaleMatrix
	addiu	$5,$29,24
$LVrBoxAct_18:
	lw	$2,844($17)
	nop
	bne	$2,$0,$LVrBoxAct_20
	addiu	$2,$0,513
	lw	$3,732($17)
	nop
	sh	$2,0($3)
	lw	$2,776($17)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxAct_19
	nop
	lw	$2,768($17)
	nop
	sw	$0,12($2)
$LVrBoxAct_19:
	lw	$2,844($17)
	nop
	bne	$2,$0,$LVrBoxAct_20
	nop
	lw	$3,160($17)
	nop
	lw	$2,40($3)
	nop
	ori	$2,$2,0x80
	j	$LVrBoxAct_21
	sw	$2,40($3)
$LVrBoxAct_20:
	lw	$2,160($17)
	nop
	lw	$3,40($2)
	addiu	$4,$0,-129
	and	$3,$3,$4
	sw	$3,40($2)
$LVrBoxAct_21:
	lw	$2,840($17)
	nop
	beq	$2,$0,$LVrBoxAct_22
	lui	$2,%hi(GV_Clock)
	lw	$4,%lo(GV_Clock)($2)
	lw	$3,160($17)
	sll	$2,$4,8
	lw	$3,52($3)
	subu	$2,$2,$4
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	lw	$2,840($17)
	nop
	addiu	$2,$2,1
	andi	$2,$2,0xf
	bne	$2,$0,$LVrBoxAct_22
	sw	$2,840($17)
	lw	$2,160($17)
	nop
	lw	$3,52($2)
	addiu	$2,$0,127
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
$LVrBoxAct_22:
	lhu	$3,6($18)
	nop
	andi	$2,$3,0x4
	beq	$2,$0,$LVrBoxAct_30
	andi	$2,$3,0xfffb
	lhu	$4,62($18)
	sh	$2,6($18)
	addiu	$2,$4,-3
	sltiu	$2,$2,2
	beq	$2,$0,$LVrBoxAct_23
	addiu	$3,$0,6
	lw	$2,776($17)
	nop
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxAct_27
	nop
	lhu	$2,38($18)
	nop
	addiu	$2,$2,-2
	sh	$2,38($18)
	sll	$2,$2,16
	bltz	$2,$LVrBoxAct_25
	addu	$4,$19,$0
	j	$LVrBoxAct_24
	addiu	$5,$0,52
$LVrBoxAct_23:
	sll	$2,$4,16
	sra	$2,$2,16
	addiu	$3,$0,2
	beq	$2,$3,$LVrBoxAct_26
	addiu	$2,$0,1
	lh	$2,38($18)
	nop
	bltz	$2,$LVrBoxAct_25
	addu	$4,$19,$0
	addiu	$5,$0,215
$LVrBoxAct_24:
	jal	GM_SeSetMode
	addiu	$6,$0,1
$LVrBoxAct_25:
	addiu	$2,$0,1
$LVrBoxAct_26:
	sw	$2,840($17)
$LVrBoxAct_27:
	lw	$2,772($17)
	nop
	bne	$2,$0,$LVrBoxAct_31
	nop
	lh	$2,38($18)
	nop
	bltz	$2,$LVrBoxAct_28
	addiu	$2,$0,2
	lh	$3,62($18)
	nop
	bne	$3,$2,$LVrBoxAct_30
	nop
	lw	$2,776($17)
	nop
	srl	$2,$2,6
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBoxAct_30
	nop
$LVrBoxAct_28:
	lh	$2,788($17)
	nop
	bne	$2,$0,$LVrBoxAct_30
	nop
	lw	$2,776($17)
	nop
	srl	$2,$2,4
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBoxAct_29
	addiu	$2,$0,1
	lbu	$2,787($17)
$LVrBoxAct_29:
	nop
	sw	$2,772($17)
	addiu	$2,$0,255
	sh	$2,38($18)
	addiu	$2,$0,513
	sh	$2,0($18)
$LVrBoxAct_30:
	lw	$2,772($17)
	nop
	beq	$2,$0,$LVrBoxAct_40
	nop
$LVrBoxAct_31:
	lbu	$2,787($17)
	lw	$3,772($17)
	nop
	beq	$3,$2,$LVrBoxAct_32
	addiu	$2,$3,1
	j	$LVrBoxAct_40
	sw	$2,772($17)
$LVrBoxAct_32:
	lw	$2,776($17)
	nop
	srl	$2,$2,4
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxAct_33
	lui	$5,%hi(blast_data_8009F4B8)
	lw	$4,160($17)
	addiu	$5,$5,%lo(blast_data_8009F4B8)
	jal	NewBlast
	addiu	$18,$0,32
	j	$LVrBoxAct_34
	nop
$LVrBoxAct_33:
	addiu	$18,$0,64
$LVrBoxAct_34:
	lw	$2,776($17)
	addiu	$3,$0,7
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxAct_35
	nop
	addiu	$18,$0,128
$LVrBoxAct_35:
	addu	$4,$19,$0
	addiu	$5,$29,72
	lui	$6,%hi(VR_TargetCount)
	lw	$2,%lo(VR_TargetCount)($6)
	lui	$3,%hi(DG_ZeroVector)
	addiu	$11,$3,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,75($29)
	swr	$8,72($29)
	swl	$9,79($29)
	swr	$9,76($29)
	addiu	$2,$2,1
	jal	DG_SetPos2
	sw	$2,%lo(VR_TargetCount)($6)
	addiu	$16,$29,40
	jal	ReadRotMatrix
	addu	$4,$16,$0
	addu	$4,$16,$0
	addiu	$5,$17,724
	lhu	$2,848($17)
	addu	$6,$18,$0
	sw	$2,16($29)
	lw	$2,852($17)
	addu	$7,$0,$0
	jal	NewSplashVr
	sw	$2,20($29)
	lw	$2,776($17)
	addiu	$3,$0,4
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxAct_36
	addu	$4,$19,$0
	j	$LVrBoxAct_37
	addiu	$5,$0,201
$LVrBoxAct_36:
	addiu	$5,$0,63
$LVrBoxAct_37:
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lh	$2,790($17)
	nop
	bne	$2,$0,$LVrBoxAct_38
	nop
	jal	GV_DestroyActor
	addu	$4,$17,$0
	j	$LVrBoxAct_39
	nop
$LVrBoxAct_38:
	jal	VrBoxStop
	addu	$4,$17,$0
$LVrBoxAct_39:
	lw	$4,800($17)
	nop
	blez	$4,$LVrBoxAct_40
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
$LVrBoxAct_40:
	lw	$31,104($29)
	lw	$19,100($29)
	lw	$18,96($29)
	lw	$17,92($29)
	lw	$16,88($29)
	jr	$31
	addiu	$29,$29,112
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxDie
VrBoxDie:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	addiu	$4,$17,36
	sw	$31,24($29)
	jal	GM_FreeControl
	sw	$16,16($29)
	jal	GM_FreeObject
	addiu	$4,$17,160
	lw	$4,732($17)
	jal	GM_FreeTarget
	nop
	lw	$16,804($17)
	nop
	beq	$16,$0,$LVrBoxDie_0
	nop
	jal	DG_DequeuePrim
	addu	$4,$16,$0
	jal	DG_FreePrim
	addu	$4,$16,$0
$LVrBoxDie_0:
	lw	$4,768($17)
	nop
	beq	$4,$0,$LVrBoxDie_1
	nop
	jal	GM_ResetHomingTarget
	nop
$LVrBoxDie_1:
	lw	$31,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBoxLoadModel
VrBoxLoadModel:
	addiu	$29,$29,-40
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,32($29)
	jal	GM_AllocTarget
	sw	$17,28($29)
	lw	$3,776($16)
	addu	$17,$2,$0
	srl	$2,$3,8
	andi	$2,$2,0x7
	bne	$2,$0,$LVrBoxLoadModel_1
	sw	$17,732($16)
	srl	$2,$3,4
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxLoadModel_0
	addiu	$3,$0,500
	j	$LVrBoxLoadModel_7
	addiu	$2,$0,400
$LVrBoxLoadModel_0:
	addiu	$2,$0,400
	sh	$2,724($16)
	sh	$2,726($16)
	sh	$2,728($16)
	j	$LVrBoxLoadModel_8
	addiu	$2,$0,64
$LVrBoxLoadModel_1:
	addiu	$3,$2,-1
	sltiu	$2,$3,6
	beq	$2,$0,$LVrBoxLoadModel_9
	lui	$2,%hi(VrBoxLoadModel_jtbl_800E2988)
	addiu	$2,$2,%lo(VrBoxLoadModel_jtbl_800E2988)
	sll	$3,$3,2
	addu	$3,$3,$2
	lw	$2,0($3)
	nop
	jr	$2
	nop
$LVrBoxLoadModel_2:
	addiu	$2,$0,400
	sh	$2,724($16)
	sh	$2,726($16)
	sh	$2,728($16)
	j	$LVrBoxLoadModel_8
	addiu	$2,$0,64
$LVrBoxLoadModel_3:
	addiu	$2,$0,510
	sh	$2,724($16)
	sh	$2,726($16)
	sh	$2,728($16)
	j	$LVrBoxLoadModel_8
	addiu	$2,$0,64
$LVrBoxLoadModel_4:
	addiu	$2,$0,400
	j	$LVrBoxLoadModel_7
	addiu	$3,$0,500
$LVrBoxLoadModel_5:
	addiu	$2,$0,1250
	sh	$2,724($16)
	sh	$2,726($16)
	addiu	$2,$0,1000
	sh	$2,728($16)
	j	$LVrBoxLoadModel_8
	addiu	$2,$0,256
$LVrBoxLoadModel_6:
	addiu	$2,$0,250
	addiu	$3,$0,800
$LVrBoxLoadModel_7:
	sh	$2,724($16)
	sh	$2,728($16)
	addiu	$2,$0,64
	sh	$3,726($16)
$LVrBoxLoadModel_8:
	sw	$2,852($16)
$LVrBoxLoadModel_9:
	addu	$4,$17,$0
	addiu	$5,$0,28
	addiu	$6,$0,2
	jal	GM_SetTarget
	addiu	$7,$16,724
	addu	$4,$17,$0
	lhu	$2,60($4)
	addiu	$5,$0,1
	ori	$2,$2,0x2
	sh	$2,60($4)
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	sw	$2,20($29)
	lw	$7,792($16)
	jal	GM_SetPowerTarget
	addiu	$6,$0,-1
	lw	$31,32($29)
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
	.globl	VrBoxGetResources
VrBoxGetResources:
	addiu	$29,$29,-104
	sw	$19,92($29)
	addu	$19,$4,$0
	sw	$18,88($29)
	addu	$18,$5,$0
	sw	$20,96($29)
	addu	$20,$6,$0
	lui	$4,%hi(vrbox_str_id_n)
	addiu	$4,$4,%lo(vrbox_str_id_n)
	sw	$31,100($29)
	sw	$17,84($29)
	jal	GV_StrCode
	sw	$16,80($29)
	lui	$16,%hi(vrbox_str_id_b)
	addiu	$16,$16,%lo(vrbox_str_id_b)
	addu	$4,$16,$0
	jal	GV_StrCode
	sw	$2,16($29)
	addu	$4,$16,$0
	jal	GV_StrCode
	sw	$2,20($29)
	lui	$4,%hi(vrbox_str_ufo)
	addiu	$4,$4,%lo(vrbox_str_ufo)
	jal	GV_StrCode
	sw	$2,24($29)
	lui	$4,%hi(vrbox_str_kokesi_c)
	addiu	$4,$4,%lo(vrbox_str_kokesi_c)
	jal	GV_StrCode
	sw	$2,28($29)
	lui	$4,%hi(vrbox_str_kokesi_s)
	addiu	$4,$4,%lo(vrbox_str_kokesi_s)
	jal	GV_StrCode
	sw	$2,32($29)
	lui	$17,%hi(vrbox_str_ufo2)
	addiu	$17,$17,%lo(vrbox_str_ufo2)
	addu	$4,$17,$0
	jal	GV_StrCode
	sw	$2,36($29)
	lui	$4,%hi(vrbox_str_mato_04add)
	addiu	$4,$4,%lo(vrbox_str_mato_04add)
	jal	GV_StrCode
	sw	$2,40($29)
	lui	$16,%hi(vrbox_str_mato_06add)
	addiu	$16,$16,%lo(vrbox_str_mato_06add)
	addu	$4,$16,$0
	jal	GV_StrCode
	sw	$2,48($29)
	addu	$4,$16,$0
	jal	GV_StrCode
	sw	$2,52($29)
	lui	$4,%hi(vrbox_str_mato_08add)
	addiu	$4,$4,%lo(vrbox_str_mato_08add)
	jal	GV_StrCode
	sw	$2,56($29)
	lui	$4,%hi(vrbox_str_mato_09add)
	addiu	$4,$4,%lo(vrbox_str_mato_09add)
	jal	GV_StrCode
	sw	$2,60($29)
	lui	$4,%hi(vrbox_str_mato_14add)
	addiu	$4,$4,%lo(vrbox_str_mato_14add)
	jal	GV_StrCode
	sw	$2,64($29)
	addu	$4,$17,$0
	jal	GV_StrCode
	sw	$2,68($29)
	addiu	$17,$19,36
	addu	$4,$17,$0
	addu	$5,$18,$0
	addu	$6,$20,$0
	jal	GM_InitControl
	sw	$2,72($29)
	bgez	$2,$LVrBoxGetResources_0
	addu	$4,$17,$0
	j	$LVrBoxGetResources_24
	addiu	$2,$0,-1
$LVrBoxGetResources_0:
	addiu	$5,$0,-1
	addiu	$6,$0,-2
	addu	$7,$5,$0
	lui	$2,%hi(GM_CurrentMap)
	sw	$20,%lo(GM_CurrentMap)($2)
	jal	GM_ConfigControlHazard
	sw	$20,32($19)
	addiu	$4,$0,114
	lw	$2,776($19)
	addiu	$3,$0,-33
	sh	$0,788($19)
	ori	$2,$2,0x8
	and	$2,$2,$3
	addiu	$3,$0,-65
	and	$2,$2,$3
	jal	GCL_GetOption
	sw	$2,776($19)
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_1
	nop
	jal	GCL_StrToInt
	nop
	sb	$2,786($19)
$LVrBoxGetResources_1:
	jal	GCL_GetOption
	addiu	$4,$0,100
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_2
	addiu	$2,$0,4
	jal	GCL_StrToInt
	nop
	j	$LVrBoxGetResources_3
	sb	$2,787($19)
$LVrBoxGetResources_2:
	sb	$2,787($19)
$LVrBoxGetResources_3:
	jal	GCL_GetOption
	addiu	$4,$0,118
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_4
	lui	$3,0x400
	jal	GCL_StrToInt
	nop
	lui	$4,0xfbff
	ori	$4,$4,0xffff
	andi	$2,$2,0x1
	lw	$3,776($19)
	sll	$2,$2,26
	and	$3,$3,$4
	or	$3,$3,$2
	j	$LVrBoxGetResources_5
	sw	$3,776($19)
$LVrBoxGetResources_4:
	lw	$2,776($19)
	nop
	or	$2,$2,$3
	sw	$2,776($19)
$LVrBoxGetResources_5:
	jal	GCL_GetOption
	addiu	$4,$0,104
	addiu	$4,$0,109
	addiu	$5,$0,-33
	sltu	$2,$0,$2
	lw	$3,776($19)
	sll	$2,$2,5
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GCL_GetOption
	sw	$3,776($19)
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_6
	addiu	$3,$0,-1793
	jal	GCL_StrToInt
	nop
	addiu	$4,$0,-1793
	andi	$2,$2,0x7
	lw	$3,776($19)
	sll	$2,$2,8
	and	$3,$3,$4
	or	$3,$3,$2
	j	$LVrBoxGetResources_7
	sw	$3,776($19)
$LVrBoxGetResources_6:
	lw	$2,776($19)
	nop
	and	$2,$2,$3
	sw	$2,776($19)
$LVrBoxGetResources_7:
	lw	$4,776($19)
	addiu	$3,$0,6
	srl	$2,$4,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxGetResources_8
	ori	$2,$4,0x20
	sw	$2,776($19)
$LVrBoxGetResources_8:
	lw	$2,776($19)
	nop
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxGetResources_9
	addiu	$4,$19,736
	jal	GM_SetHomingTarget
	addiu	$5,$19,36
	addiu	$3,$0,1
	sw	$2,768($19)
	sw	$3,8($2)
$LVrBoxGetResources_9:
	jal	GCL_GetOption
	addiu	$4,$0,98
	addiu	$4,$0,115
	addiu	$5,$0,-17
	sltu	$2,$0,$2
	lw	$3,776($19)
	sll	$2,$2,4
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GCL_GetOption
	sw	$3,776($19)
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_10
	nop
	lw	$2,776($19)
	nop
	ori	$2,$2,0x4
	jal	GCL_StrToInt
	sw	$2,776($19)
	sw	$2,780($19)
$LVrBoxGetResources_10:
	jal	GCL_GetOption
	addiu	$4,$0,105
	addiu	$4,$0,97
	addiu	$5,$0,-3
	sltu	$2,$0,$2
	lw	$3,776($19)
	sll	$2,$2,1
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GCL_GetOption
	sw	$3,776($19)
	addiu	$4,$0,101
	addiu	$5,$0,-2
	lw	$3,776($19)
	sltu	$2,$0,$2
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GCL_GetOption
	sw	$3,776($19)
	beq	$2,$0,$LVrBoxGetResources_11
	addiu	$2,$0,-1
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrBoxGetResources_12
	sw	$2,800($19)
$LVrBoxGetResources_11:
	sw	$2,800($19)
$LVrBoxGetResources_12:
	jal	GCL_GetOption
	addiu	$4,$0,108
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_13
	addiu	$2,$0,150
	lw	$2,776($19)
	nop
	ori	$2,$2,0x40
	jal	GCL_StrToInt
	sw	$2,776($19)
	j	$LVrBoxGetResources_14
	sw	$2,792($19)
$LVrBoxGetResources_13:
	sw	$2,792($19)
$LVrBoxGetResources_14:
	jal	GCL_GetOption
	addiu	$4,$0,116
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_15
	nop
	jal	GCL_StrToInt
	nop
	sh	$2,790($19)
	sll	$2,$2,16
	sra	$2,$2,16
	slti	$2,$2,31
	beq	$2,$0,$LVrBoxGetResources_16
	addiu	$2,$0,30
	j	$LVrBoxGetResources_16
	sh	$2,790($19)
$LVrBoxGetResources_15:
	sh	$0,790($19)
$LVrBoxGetResources_16:
	jal	GCL_GetOption
	addiu	$4,$0,117
	addu	$4,$2,$0
	beq	$4,$0,$LVrBoxGetResources_17
	nop
	jal	GCL_StrToInt
	nop
	sll	$3,$2,4
	subu	$3,$3,$2
	sll	$2,$3,1
	sll	$3,$3,17
	sra	$3,$3,16
	slti	$3,$3,31
	beq	$3,$0,$LVrBoxGetResources_17
	sh	$2,790($19)
	addiu	$2,$0,30
	sh	$2,790($19)
$LVrBoxGetResources_17:
	jal	GCL_GetOption
	addiu	$4,$0,110
	addiu	$3,$0,-129
	sltu	$2,$0,$2
	sll	$2,$2,7
	lw	$4,776($19)
	addiu	$16,$19,160
	and	$4,$4,$3
	or	$4,$4,$2
	srl	$2,$4,8
	andi	$2,$2,0x7
	bne	$2,$0,$LVrBoxGetResources_20
	sw	$4,776($19)
	srl	$2,$4,4
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBoxGetResources_18
	nop
	lui	$4,%hi(vrbox_str_id_b)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox_str_id_b)
	addu	$4,$16,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox_str_mato_06add)
	j	$LVrBoxGetResources_19
	addiu	$4,$4,%lo(vrbox_str_mato_06add)
$LVrBoxGetResources_18:
	lui	$4,%hi(vrbox_str_id_n)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox_str_id_n)
	addu	$4,$16,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox_str_mato_04add)
	addiu	$4,$4,%lo(vrbox_str_mato_04add)
$LVrBoxGetResources_19:
	jal	GV_StrCode
	nop
	j	$LVrBoxGetResources_22
	sw	$2,848($19)
$LVrBoxGetResources_20:
	addu	$4,$16,$0
	addiu	$6,$0,349
	addiu	$2,$2,-1
	sll	$2,$2,2
	addu	$2,$29,$2
	lw	$5,16($2)
	jal	GM_InitObject
	addu	$7,$0,$0
	lw	$2,776($19)
	lw	$3,776($19)
	srl	$2,$2,8
	andi	$2,$2,0x7
	addiu	$2,$2,-1
	sll	$2,$2,2
	addu	$2,$29,$2
	lw	$2,48($2)
	nop
	sw	$2,848($19)
	srl	$2,$3,8
	andi	$2,$2,0x7
	addiu	$2,$2,-2
	sltiu	$2,$2,3
	beq	$2,$0,$LVrBoxGetResources_21
	ori	$2,$3,0x10
	sw	$2,776($19)
$LVrBoxGetResources_21:
	lw	$2,776($19)
	addiu	$3,$0,7
	srl	$2,$2,8
	andi	$2,$2,0x7
	bne	$2,$3,$LVrBoxGetResources_22
	addiu	$2,$0,255
	sb	$2,787($19)
$LVrBoxGetResources_22:
	jal	VrBoxLoadModel
	addu	$4,$19,$0
	addu	$4,$16,$0
	jal	GM_ConfigObjectLight
	addiu	$5,$19,388
	jal	VrBoxCopyPath
	addu	$4,$19,$0
	bgez	$2,$LVrBoxGetResources_23
	lui	$7,0xfffe
	lui	$4,%hi(vrbox_str_root_not_found)
	jal	printf
	addiu	$4,$4,%lo(vrbox_str_root_not_found)
	lui	$7,0xfffe
$LVrBoxGetResources_23:
	ori	$7,$7,0x7fff
	lui	$6,0xfffd
	ori	$6,$6,0xffff
	lui	$5,0xfc03
	ori	$5,$5,0xffff
	addu	$4,$19,$0
	addiu	$2,$0,8
	addiu	$3,$0,-30721
	sh	$0,784($19)
	sw	$0,772($19)
	lwl	$8,459($19)
	lwr	$8,456($19)
	lwl	$9,463($19)
	lwr	$9,460($19)
	swl	$8,39($19)
	swr	$8,36($19)
	swl	$9,43($19)
	swr	$9,40($19)
	sw	$0,712($19)
	lwl	$8,459($19)
	lwr	$8,456($19)
	lwl	$9,463($19)
	lwr	$9,460($19)
	swl	$8,719($19)
	swr	$8,716($19)
	swl	$9,723($19)
	swr	$9,720($19)
	sw	$2,844($19)
	lw	$2,776($19)
	addiu	$16,$19,36
	sw	$0,840($19)
	and	$2,$2,$3
	and	$2,$2,$7
	and	$2,$2,$6
	and	$2,$2,$5
	jal	VrBoxMakePrim
	sw	$2,776($19)
	addu	$4,$16,$0
	jal	GM_ConfigControlAttribute
	addiu	$5,$0,1
	jal	GM_ActControl
	addu	$4,$17,$0
	jal	GM_ActObject2
	addiu	$4,$19,160
	jal	GM_ConfigControlTrapCheck
	addu	$4,$17,$0
	lw	$3,160($19)
	addu	$2,$0,$0
	lw	$4,52($3)
	addiu	$3,$0,127
	sw	$3,28($4)
	sw	$3,24($4)
	sw	$3,20($4)
$LVrBoxGetResources_24:
	lw	$31,100($29)
	lw	$20,96($29)
	lw	$19,92($29)
	lw	$18,88($29)
	lw	$17,84($29)
	lw	$16,80($29)
	jr	$31
	addiu	$29,$29,104
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NewVrBox
NewVrBox:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	addiu	$4,$0,5
	addiu	$5,$0,856
	sw	$31,28($29)
	jal	GV_NewActor
	sw	$16,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LNewVrBox_0
	addu	$4,$16,$0
	lui	$5,%hi(VrBoxAct)
	addiu	$5,$5,%lo(VrBoxAct)
	lui	$6,%hi(VrBoxDie)
	addiu	$6,$6,%lo(VrBoxDie)
	lui	$7,%hi(vrbox_str_file)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(vrbox_str_file)
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	VrBoxGetResources
	addu	$6,$18,$0
	bgez	$2,$LNewVrBox_1
	addu	$2,$16,$0
	jal	GV_DestroyActor
	addu	$4,$16,$0
	j	$LNewVrBox_1
	addu	$2,$0,$0
$LNewVrBox_0:
	addu	$2,$16,$0
$LNewVrBox_1:
	lw	$31,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,32
	.set	macro
	.set	reorder
	.rdata
	.align	2
vrbox_str_shadow:
	.ascii	"shadow"
	.byte	0
	.align	2
VrBoxLoadModel_jtbl_800E2988:
	.word	$LVrBoxLoadModel_2
	.word	$LVrBoxLoadModel_3
	.word	$LVrBoxLoadModel_4
	.word	$LVrBoxLoadModel_5
	.word	$LVrBoxLoadModel_6
	.word	$LVrBoxLoadModel_6
	.align	2
vrbox_str_id_n:
	.ascii	"id_n"
	.byte	0
	.align	2
vrbox_str_id_b:
	.ascii	"id_b"
	.byte	0
	.align	2
vrbox_str_ufo:
	.ascii	"ufo"
	.byte	0
	.align	2
vrbox_str_kokesi_c:
	.ascii	"kokesi_c"
	.byte	0
	.align	2
vrbox_str_kokesi_s:
	.ascii	"kokesi_s"
	.byte	0
	.align	2
vrbox_str_ufo2:
	.ascii	"ufo2"
	.byte	0
	.align	2
vrbox_str_mato_04add:
	.ascii	"mato_04add"
	.byte	0
	.align	2
vrbox_str_mato_06add:
	.ascii	"mato_06add"
	.byte	0
	.align	2
vrbox_str_mato_08add:
	.ascii	"mato_08add"
	.byte	0
	.align	2
vrbox_str_mato_09add:
	.ascii	"mato_09add"
	.byte	0
	.align	2
vrbox_str_mato_14add:
	.ascii	"mato_14add"
	.byte	0
	.align	2
vrbox_str_root_not_found:
	.ascii	"root not found\n"
	.byte	0
	.align	2
vrbox_str_file:
	.ascii	"vrbox.c"
	.byte	0
	.text
