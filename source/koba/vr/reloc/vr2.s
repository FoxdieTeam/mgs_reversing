	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2KillMissiles
Vr2KillMissiles:
	addiu	$29,$29,-56
	lui	$4,%hi(vr2_str_nikita)
	addiu	$4,$4,%lo(vr2_str_nikita)
	sw	$31,48($29)
	sw	$17,44($29)
	jal	GV_StrCode
	sw	$16,40($29)
	lui	$16,%hi(vr2_str_kill)
	addiu	$16,$16,%lo(vr2_str_kill)
	addu	$4,$16,$0
	jal	GV_StrCode
	sh	$2,16($29)
	addiu	$4,$29,16
	addiu	$17,$0,1
	sh	$2,20($29)
	jal	GV_SendMessage
	sh	$17,34($29)
	lui	$4,%hi(vr2_str_stinger)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vr2_str_stinger)
	addu	$4,$16,$0
	jal	GV_StrCode
	sh	$2,16($29)
	addiu	$4,$29,16
	sh	$2,20($29)
	jal	GV_SendMessage
	sh	$17,34($29)
	lw	$31,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	jr	$31
	addiu	$29,$29,56
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2SetSnakeMotion
Vr2SetSnakeMotion:
	addiu	$29,$29,-48
	lui	$4,%hi(vr2_str_snake)
	sw	$31,40($29)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vr2_str_snake)
	sh	$2,16($29)
	ori	$2,$0,0xbe0a
	sh	$2,20($29)
	lui	$2,%hi(linkvarbuf+32)
	lh	$3,%lo(linkvarbuf+32)($2)
	addiu	$2,$0,2
	bne	$3,$2,$LVr2SetSnakeMotion_0
	addiu	$2,$0,3
	addiu	$2,$0,4
$LVr2SetSnakeMotion_0:
	sh	$2,22($29)
	addiu	$4,$29,16
	ori	$2,$0,0xffff
	sh	$2,24($29)
	sh	$2,26($29)
	sh	$2,28($29)
	addiu	$2,$0,5
	jal	GV_SendMessage
	sh	$2,34($29)
	lw	$31,40($29)
	nop
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2ResetEquip
Vr2ResetEquip:
	addiu	$29,$29,-32
	lui	$2,%hi(linkvarbuf)
	sw	$17,20($29)
	addiu	$17,$2,%lo(linkvarbuf)
	sw	$31,24($29)
	sw	$16,16($29)
	lh	$2,28($17)
	addiu	$16,$0,-1
	bne	$2,$16,$LVr2ResetEquip_0
	lui	$2,%hi(Work+513)
	jal	MENU_ResetWeaponPos
	sb	$16,%lo(Work+513)($2)
$LVr2ResetEquip_0:
	lh	$3,30($17)
	nop
	bne	$3,$16,$LVr2ResetEquip_1
	lui	$2,%hi(Work+493)
	jal	MENU_ResetItemPos
	sb	$3,%lo(Work+493)($2)
$LVr2ResetEquip_1:
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
	.globl	Vr2Itoa2
Vr2Itoa2:
	lui	$3,0x6666
	ori	$3,$3,0x6667
	mult	$4,$3
	sra	$2,$4,31
	mfhi	$7
	sra	$6,$7,2
	subu	$6,$6,$2
	mult	$6,$3
	sb	$0,2($5)
	sll	$2,$6,2
	addu	$2,$2,$6
	sll	$2,$2,1
	subu	$4,$4,$2
	addiu	$4,$4,48
	sra	$2,$6,31
	sb	$4,1($5)
	mfhi	$7
	sra	$3,$7,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$6,$6,$2
	addiu	$6,$6,48
	jr	$31
	sb	$6,0($5)
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2DrawTime
Vr2DrawTime:
	addiu	$29,$29,-64
	sw	$20,56($29)
	addu	$20,$5,$0
	lui	$5,0x8888
	ori	$5,$5,0x8889
	mult	$4,$5
	sw	$18,48($29)
	addu	$18,$6,$0
	sra	$2,$4,31
	mfhi	$3
	addu	$6,$3,$4
	sra	$6,$6,4
	subu	$6,$6,$2
	mult	$6,$5
	sw	$19,52($29)
	addu	$19,$7,$0
	sw	$31,60($29)
	sw	$17,44($29)
	sll	$2,$6,4
	subu	$2,$2,$6
	sll	$2,$2,1
	subu	$4,$4,$2
	sll	$3,$4,1
	addu	$3,$3,$4
	sll	$3,$3,3
	mfhi	$7
	addu	$3,$3,$4
	sll	$3,$3,2
	mult	$3,$5
	sw	$16,40($29)
	sra	$4,$6,31
	addiu	$5,$29,16
	addu	$2,$7,$6
	sra	$2,$2,5
	subu	$17,$2,$4
	addu	$16,$17,$0
	sll	$2,$16,4
	subu	$2,$2,$16
	sll	$2,$2,2
	subu	$17,$6,$2
	mfhi	$9
	addu	$4,$9,$3
	sra	$4,$4,4
	sra	$3,$3,31
	jal	Vr2Itoa2
	subu	$4,$4,$3
	addu	$4,$17,$0
	addiu	$17,$29,24
	jal	Vr2Itoa2
	addu	$5,$17,$0
	addu	$4,$16,$0
	addiu	$16,$29,32
	jal	Vr2Itoa2
	addu	$5,$16,$0
	addu	$4,$18,$0
	addu	$5,$19,$0
	jal	MENU_Locate
	addu	$6,$0,$0
	lui	$4,%hi(vr2_str_s)
	addiu	$4,$4,%lo(vr2_str_s)
	jal	MENU_Printf
	addu	$5,$20,$0
	addu	$4,$18,$0
	addiu	$5,$19,6
	jal	MENU_Locate
	addu	$6,$0,$0
	lui	$4,%hi(vr2_str_time_fmt)
	addiu	$4,$4,%lo(vr2_str_time_fmt)
	addu	$5,$16,$0
	addu	$6,$17,$0
	jal	MENU_Printf
	addiu	$7,$29,16
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
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2DrawScore
Vr2DrawScore:
	addiu	$29,$29,-40
	sw	$18,32($29)
	lw	$18,56($29)
	lui	$5,0x6666
	sw	$31,36($29)
	sw	$17,28($29)
	sw	$16,24($29)
	sb	$0,19($29)
	lw	$4,240($18)
	ori	$5,$5,0x6667
	mult	$4,$5
	sra	$2,$4,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	addiu	$4,$4,48
	sb	$4,18($29)
	lw	$2,240($18)
	nop
	mult	$2,$5
	sra	$2,$2,31
	mfhi	$8
	sra	$4,$8,2
	subu	$4,$4,$2
	mult	$4,$5
	addu	$16,$6,$0
	lui	$6,0x51eb
	sra	$2,$4,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	addiu	$4,$4,48
	sb	$4,17($29)
	lw	$2,240($18)
	ori	$6,$6,0x851f
	mult	$2,$6
	addu	$17,$7,$0
	sra	$2,$2,31
	mfhi	$8
	sra	$7,$8,5
	subu	$7,$7,$2
	mult	$7,$5
	addu	$4,$16,$0
	addu	$6,$0,$0
	addu	$5,$17,$0
	sra	$2,$7,31
	mfhi	$8
	sra	$3,$8,2
	subu	$3,$3,$2
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,1
	subu	$7,$7,$2
	addiu	$7,$7,48
	jal	MENU_Locate
	sb	$7,16($29)
	lui	$4,%hi(vr2_str_score)
	jal	MENU_Printf
	addiu	$4,$4,%lo(vr2_str_score)
	addiu	$4,$16,44
	addiu	$5,$17,6
	jal	MENU_Locate
	addiu	$6,$0,1
	lh	$2,246($18)
	lw	$3,240($18)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$LVr2DrawScore_0
	addiu	$4,$0,255
	addu	$5,$4,$0
	jal	MENU_Color
	addu	$6,$0,$0
	addiu	$4,$0,64
	addiu	$5,$0,80
	jal	GM_SeSet2
	addiu	$6,$0,180
$LVr2DrawScore_0:
	lui	$4,%hi(vr2_str_s)
	addiu	$4,$4,%lo(vr2_str_s)
	jal	MENU_Printf
	addiu	$5,$29,16
	addiu	$4,$0,148
	addu	$5,$4,$0
	lhu	$2,240($18)
	addu	$6,$4,$0
	jal	MENU_Color
	sh	$2,246($18)
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
	.globl	Vr2CheckEnd
Vr2CheckEnd:
	addiu	$29,$29,-32
	lui	$3,%hi(vr_end_timer)
	sw	$16,16($29)
	lw	$16,%lo(vr_end_timer)($3)
	sw	$17,20($29)
	addu	$17,$4,$0
	beq	$16,$0,$LVr2CheckEnd_5
	sw	$31,24($29)
	blez	$16,$LVr2CheckEnd_5
	addiu	$2,$0,1
	bne	$16,$2,$LVr2CheckEnd_4
	addiu	$2,$16,-1
	jal	GM_StreamStatus
	nop
	addiu	$3,$0,-1
	bne	$2,$3,$LVr2CheckEnd_3
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	nop
	andi	$2,$2,0x20
	beq	$2,$0,$LVr2CheckEnd_0
	addu	$4,$0,$0
	lh	$3,36($17)
	lh	$2,38($17)
	nop
	beq	$3,$2,$LVr2CheckEnd_0
	addiu	$4,$0,1
	lw	$5,232($17)
	j	$LVr2CheckEnd_1
	addu	$4,$0,$0
$LVr2CheckEnd_0:
	addu	$5,$0,$0
$LVr2CheckEnd_1:
	jal	NewVrOver
	nop
	beq	$2,$0,$LVr2CheckEnd_2
	lui	$3,%hi(vr_end_timer)
	j	$LVr2CheckEnd_4
	addiu	$2,$0,-1
$LVr2CheckEnd_2:
	jal	GV_DestroyActorSystem
	addiu	$4,$0,4
	j	$LVr2CheckEnd_5
	nop
$LVr2CheckEnd_3:
	jal	GM_StreamStatus
	nop
	bne	$2,$16,$LVr2CheckEnd_5
	nop
	jal	GM_StreamPlayStop
	nop
	j	$LVr2CheckEnd_5
	nop
$LVr2CheckEnd_4:
	sw	$2,%lo(vr_end_timer)($3)
$LVr2CheckEnd_5:
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
	.globl	Vr2Finish
Vr2Finish:
	addiu	$29,$29,-24
	sw	$16,16($29)
	lui	$16,%hi(vr_end_timer)
	lw	$2,%lo(vr_end_timer)($16)
	addu	$5,$4,$0
	bne	$2,$0,$LVr2Finish_1
	sw	$31,20($29)
	lui	$4,%hi(VR_Status)
	lui	$2,%hi(VR_Flags)
	lw	$2,%lo(VR_Flags)($2)
	addiu	$3,$0,5
	andi	$2,$2,0x20
	beq	$2,$0,$LVr2Finish_0
	sw	$3,%lo(VR_Status)($4)
	lw	$4,232($5)
	lh	$5,36($5)
	jal	GCL_SetVar
	nop
$LVr2Finish_0:
	addu	$4,$0,$0
	addu	$5,$4,$0
	addiu	$2,$0,4
	jal	GM_CallSystemCallbackProc
	sw	$2,%lo(vr_end_timer)($16)
	lui	$4,0x8
	lui	$3,%hi(GM_GameStatus)
	lw	$2,%lo(GM_GameStatus)($3)
	ori	$4,$4,0x6000
	or	$2,$2,$4
	sw	$2,%lo(GM_GameStatus)($3)
$LVr2Finish_1:
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
	.globl	Vr2GameOver
Vr2GameOver:
	addiu	$29,$29,-24
	lui	$5,%hi(VR_Status)
	lw	$2,%lo(VR_Status)($5)
	addiu	$3,$0,5
	beq	$2,$3,$LVr2GameOver_0
	sw	$31,16($29)
	lui	$2,%hi(bikkuri_flag)
	sw	$0,%lo(bikkuri_flag)($2)
	lui	$2,%hi(GM_GameOverTimer)
	sw	$3,%lo(VR_Status)($5)
	jal	Vr2Finish
	sw	$0,%lo(GM_GameOverTimer)($2)
$LVr2GameOver_0:
	lw	$31,16($29)
	nop
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2CalcResult
Vr2CalcResult:
	addiu	$29,$29,-48
	lui	$2,%hi(GM_PlayerControl)
	lw	$3,%lo(GM_PlayerControl)($2)
	addu	$8,$4,$0
	sw	$31,40($29)
	lhu	$2,228($8)
	nop
	sh	$2,78($3)
	lui	$2,%hi(VR_Records+8)
	lw	$2,%lo(VR_Records+8)($2)
	lw	$3,240($8)
	bgez	$2,$LVr2CalcResult_0
	nop
	subu	$2,$0,$2
$LVr2CalcResult_0:
	slt	$2,$2,$3
	bne	$2,$0,$LVr2CalcResult_1
	addiu	$7,$0,2
	j	$LVr2CalcResult_3
	addiu	$7,$0,3
$LVr2CalcResult_1:
	beq	$7,$0,$LVr2CalcResult_3
	sll	$5,$7,2
	addiu	$2,$7,-1
	addu	$7,$2,$0
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	sll	$3,$7,2
	addu	$3,$3,$2
	lw	$4,0($3)
	addu	$5,$5,$2
	sw	$4,0($5)
	lw	$2,0($3)
	lw	$3,240($8)
	bgez	$2,$LVr2CalcResult_2
	nop
	subu	$2,$0,$2
$LVr2CalcResult_2:
	slt	$2,$2,$3
	bne	$2,$0,$LVr2CalcResult_1
	nop
	addiu	$7,$7,1
$LVr2CalcResult_3:
	sltiu	$2,$7,3
	beq	$2,$0,$LVr2CalcResult_4
	lui	$2,%hi(VR_Records)
	addiu	$2,$2,%lo(VR_Records)
	sll	$3,$7,2
	lw	$4,240($8)
	addu	$3,$3,$2
	sw	$4,0($3)
$LVr2CalcResult_4:
	addiu	$2,$0,4
	sh	$2,16($29)
	addiu	$2,$29,24
	sw	$2,20($29)
	lui	$2,%hi(VR_Records)
	addiu	$6,$2,%lo(VR_Records)
	lw	$5,8($6)
	lw	$3,240($8)
	lw	$2,%lo(VR_Records)($2)
	lw	$4,4($6)
	sw	$5,36($29)
	lui	$5,%hi(VR_Flags)
	sw	$2,28($29)
	lw	$2,%lo(VR_Flags)($5)
	sw	$3,24($29)
	sw	$4,32($29)
	lw	$4,240($8)
	sll	$3,$7,1
	sw	$4,12($6)
	lw	$4,40($8)
	or	$2,$2,$3
	sw	$2,%lo(VR_Flags)($5)
	jal	GCL_ExecProc
	addiu	$5,$29,16
	lw	$31,40($29)
	nop
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2CheckMessages
Vr2CheckMessages:
	addiu	$29,$29,-48
	sw	$31,44($29)
	sw	$20,40($29)
	sw	$19,36($29)
	sw	$18,32($29)
	sw	$17,28($29)
	sw	$16,24($29)
	lw	$4,32($4)
	jal	GV_ReceiveMessage
	addiu	$5,$29,16
	addu	$17,$2,$0
	blez	$17,$LVr2CheckMessages_5
	lui	$18,%hi(VR_Status)
	addiu	$20,$0,1
	lui	$19,%hi(VR_TargetCount)
$LVr2CheckMessages_0:
	lw	$5,16($29)
	nop
	lhu	$3,4($5)
	ori	$2,$0,0xb247
	bne	$3,$2,$LVr2CheckMessages_1
	ori	$2,$0,0xec10
	sw	$20,%lo(VR_Status)($18)
	lhu	$3,4($5)
$LVr2CheckMessages_1:
	nop
	bne	$3,$2,$LVr2CheckMessages_2
	lui	$4,%hi(vr2_str_plus)
	addiu	$2,$0,3
	sw	$2,%lo(VR_Status)($18)
$LVr2CheckMessages_2:
	lhu	$16,4($5)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vr2_str_plus)
	bne	$16,$2,$LVr2CheckMessages_3
	lui	$4,%hi(vr2_str_itemset)
	lw	$2,%lo(VR_Status)($18)
	nop
	bne	$2,$20,$LVr2CheckMessages_3
	nop
	lw	$2,%lo(VR_TargetCount)($19)
	nop
	addiu	$2,$2,1
	sw	$2,%lo(VR_TargetCount)($19)
$LVr2CheckMessages_3:
	lw	$2,16($29)
	nop
	lhu	$16,4($2)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vr2_str_itemset)
	bne	$16,$2,$LVr2CheckMessages_4
	nop
	jal	Vr2ResetEquip
	nop
$LVr2CheckMessages_4:
	lw	$2,16($29)
	addiu	$17,$17,-1
	addiu	$2,$2,20
	bgtz	$17,$LVr2CheckMessages_0
	sw	$2,16($29)
$LVr2CheckMessages_5:
	lw	$31,44($29)
	lw	$20,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2Act
Vr2Act:
	addiu	$29,$29,-48
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$31,40($29)
	sw	$19,36($29)
	sw	$18,32($29)
	jal	Vr2CheckMessages
	sw	$17,28($29)
	lui	$17,%hi(VR_Status)
	lw	$2,%lo(VR_Status)($17)
	addiu	$18,$0,1
	bne	$2,$18,$LVr2Act_0
	lui	$2,%hi(VR_TargetCount)
	lw	$2,%lo(VR_TargetCount)($2)
	nop
	sw	$2,240($16)
$LVr2Act_0:
	lh	$2,38($16)
	nop
	beq	$2,$0,$LVr2Act_6
	nop
	lw	$3,%lo(VR_Status)($17)
	nop
	addiu	$2,$3,-1
	sltiu	$2,$2,2
	bne	$2,$0,$LVr2Act_1
	addiu	$4,$0,148
	addiu	$2,$0,5
	bne	$3,$2,$LVr2Act_6
	nop
$LVr2Act_1:
	addu	$5,$4,$0
	jal	MENU_Color
	addu	$6,$4,$0
	lui	$5,%hi(vr2_str_score)
	addiu	$5,$5,%lo(vr2_str_score)
	addiu	$6,$0,138
	sw	$16,16($29)
	sw	$0,20($29)
	lw	$4,240($16)
	jal	Vr2DrawScore
	addiu	$7,$0,188
	lui	$2,0x8888
	lhu	$3,36($16)
	ori	$2,$2,0x8889
	sll	$3,$3,16
	sra	$4,$3,16
	mult	$4,$2
	sra	$3,$3,31
	mfhi	$24
	addu	$2,$24,$4
	sra	$2,$2,4
	subu	$3,$2,$3
	sll	$2,$3,16
	sra	$2,$2,16
	slti	$2,$2,10
	beq	$2,$0,$LVr2Act_3
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	subu	$2,$4,$2
	sll	$2,$2,16
	sra	$2,$2,16
	addiu	$3,$0,29
	bne	$2,$3,$LVr2Act_2
	lui	$3,0x8888
	lw	$2,%lo(VR_Status)($17)
	nop
	bne	$2,$18,$LVr2Act_2
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,185
	lui	$3,0x8888
$LVr2Act_2:
	lhu	$2,36($16)
	ori	$3,$3,0x8889
	sll	$2,$2,16
	sra	$4,$2,16
	mult	$4,$3
	sra	$2,$2,31
	mfhi	$24
	addu	$3,$24,$4
	sra	$3,$3,4
	subu	$3,$3,$2
	sll	$2,$3,4
	subu	$2,$2,$3
	sll	$2,$2,1
	subu	$4,$4,$2
	sll	$4,$4,16
	sra	$4,$4,16
	slti	$4,$4,15
	bne	$4,$0,$LVr2Act_4
	lui	$5,%hi(vr2_str_time)
	addiu	$4,$0,148
	addiu	$5,$0,48
	jal	MENU_Color
	addu	$6,$5,$0
$LVr2Act_3:
	lui	$5,%hi(vr2_str_time)
$LVr2Act_4:
	addiu	$5,$5,%lo(vr2_str_time)
	addiu	$6,$0,138
	addiu	$7,$0,200
	lh	$4,36($16)
	addiu	$2,$0,1
	sw	$16,16($29)
	jal	Vr2DrawTime
	sw	$2,20($29)
	lui	$7,0xff
	ori	$7,$7,0xffff
	addu	$14,$0,$0
	lui	$13,0xff
	ori	$13,$13,0xffff
	lui	$15,0xff00
	addiu	$12,$0,80
	addu	$11,$16,$0
	lui	$2,%hi(DG_Chanls+492)
	addiu	$2,$2,%lo(DG_Chanls+492)
	lui	$3,%hi(GV_Clock)
	addiu	$2,$2,492
	lw	$5,%lo(GV_Clock)($3)
	addu	$8,$15,$0
	sll	$4,$5,2
	addu	$4,$4,$2
	sll	$5,$5,4
	addu	$6,$5,$16
	addu	$10,$4,$0
	addu	$9,$5,$0
	lw	$2,0($4)
	lw	$3,48($6)
	lw	$2,0($2)
	and	$3,$3,$8
	and	$2,$2,$7
	or	$3,$3,$2
	addiu	$2,$9,48
	sw	$3,48($6)
	lw	$6,0($4)
	addu	$2,$16,$2
	lw	$3,0($6)
	and	$2,$2,$7
	and	$3,$3,$8
	or	$3,$3,$2
	sw	$3,0($6)
$LVr2Act_5:
	addu	$4,$16,$12
	addiu	$12,$12,32
	addu	$5,$9,$11
	addiu	$14,$14,1
	lw	$2,0($10)
	lw	$3,80($5)
	lw	$2,0($2)
	and	$3,$3,$15
	and	$2,$2,$13
	or	$3,$3,$2
	sw	$3,80($5)
	lw	$3,0($10)
	addu	$4,$4,$9
	lw	$2,0($3)
	and	$4,$4,$13
	and	$2,$2,$15
	or	$2,$2,$4
	sw	$2,0($3)
	slti	$2,$14,4
	bne	$2,$0,$LVr2Act_5
	addiu	$11,$11,32
	lui	$7,0xff
	ori	$7,$7,0xffff
	lui	$2,%hi(DG_Chanls+492)
	addiu	$2,$2,%lo(DG_Chanls+492)
	lui	$3,%hi(GV_Clock)
	addiu	$2,$2,492
	lw	$4,%lo(GV_Clock)($3)
	lui	$8,0xff00
	sll	$5,$4,2
	addu	$5,$5,$2
	sll	$4,$4,3
	addu	$6,$4,$16
	addiu	$4,$4,208
	lw	$2,0($5)
	lw	$3,208($6)
	lw	$2,0($2)
	and	$3,$3,$8
	and	$2,$2,$7
	or	$3,$3,$2
	sw	$3,208($6)
	lw	$3,0($5)
	addu	$4,$16,$4
	lw	$2,0($3)
	and	$4,$4,$7
	and	$2,$2,$8
	or	$2,$2,$4
	sw	$2,0($3)
$LVr2Act_6:
	lhu	$2,250($16)
	nop
	beq	$2,$0,$LVr2Act_7
	lui	$19,%hi(VR_Status)
	jal	Vr2SetSnakeMotion
	nop
	jal	Vr2SetSnakeMotion
	nop
	jal	Vr2SetSnakeMotion
	nop
	sh	$0,250($16)
$LVr2Act_7:
	lw	$18,%lo(VR_Status)($19)
	addiu	$2,$0,1
	bne	$18,$2,$LVr2Act_11
	lui	$2,%hi(linkvarbuf+22)
	lh	$2,38($16)
	nop
	beq	$2,$0,$LVr2Act_11
	lui	$2,%hi(linkvarbuf+22)
	lh	$3,36($16)
	lhu	$2,36($16)
	blez	$3,$LVr2Act_8
	addiu	$2,$2,-1
	sh	$2,36($16)
	sll	$2,$2,16
	sra	$2,$2,16
	addiu	$3,$0,2
	bne	$2,$3,$LVr2Act_11
	lui	$2,%hi(linkvarbuf+22)
	lh	$2,%lo(linkvarbuf+22)($2)
	nop
	blez	$2,$LVr2Act_12
	lui	$2,%hi(GM_GameStatus)
	lw	$3,%lo(GM_GameStatus)($2)
	lui	$4,0x1000
	or	$3,$3,$4
	jal	Vr2SetSnakeMotion
	sw	$3,%lo(GM_GameStatus)($2)
	jal	Vr2KillMissiles
	nop
	j	$LVr2Act_11
	lui	$2,%hi(linkvarbuf+22)
$LVr2Act_8:
	bne	$3,$0,$LVr2Act_11
	lui	$2,%hi(linkvarbuf+22)
	lui	$2,%hi(linkvarbuf)
	addiu	$17,$2,%lo(linkvarbuf)
	lh	$2,22($17)
	nop
	blez	$2,$LVr2Act_12
	lui	$2,%hi(VR_TargetCount)
	lbu	$3,236($16)
	lw	$2,%lo(VR_TargetCount)($2)
	nop
	slt	$2,$2,$3
	bne	$2,$0,$LVr2Act_9
	addu	$4,$16,$0
	jal	Vr2CalcResult
	addu	$4,$16,$0
	lh	$3,32($17)
	addiu	$2,$0,2
	beq	$3,$2,$LVr2Act_10
	sw	$2,%lo(VR_Status)($19)
	jal	Vr2SetSnakeMotion
	nop
	jal	Vr2SetSnakeMotion
	nop
	jal	Vr2SetSnakeMotion
	nop
	j	$LVr2Act_10
	sh	$18,250($16)
$LVr2Act_9:
	lw	$3,224($16)
	lui	$2,%hi(GM_VrGameOverVox)
	jal	Vr2GameOver
	sw	$3,%lo(GM_VrGameOverVox)($2)
$LVr2Act_10:
	lui	$2,%hi(linkvarbuf+22)
$LVr2Act_11:
	lh	$2,%lo(linkvarbuf+22)($2)
	nop
	bgtz	$2,$LVr2Act_15
	nop
$LVr2Act_12:
	lhu	$2,248($16)
	nop
	bne	$2,$0,$LVr2Act_13
	addu	$4,$0,$0
	addiu	$5,$0,63
	jal	GM_SeSet2
	addiu	$6,$0,26
$LVr2Act_13:
	lhu	$3,248($16)
	nop
	sltiu	$2,$3,90
	beq	$2,$0,$LVr2Act_14
	addiu	$2,$3,1
	sh	$2,248($16)
$LVr2Act_14:
	lui	$2,%hi(GM_GameOverTimer)
	lui	$3,%hi(VR_Status)
	sw	$0,%lo(GM_GameOverTimer)($2)
	addiu	$2,$0,5
	lui	$4,%hi(GM_GameStatus)
	sw	$2,%lo(VR_Status)($3)
	lw	$2,%lo(GM_GameStatus)($4)
	lui	$3,0x1000
	or	$2,$2,$3
	lhu	$3,248($16)
	sw	$2,%lo(GM_GameStatus)($4)
	addiu	$2,$0,90
	bne	$3,$2,$LVr2Act_15
	lui	$2,%hi(bikkuri_flag)
	sw	$0,%lo(bikkuri_flag)($2)
	jal	Vr2Finish
	addu	$4,$16,$0
$LVr2Act_15:
	jal	Vr2CheckEnd
	addu	$4,$16,$0
	lw	$31,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2Die
Vr2Die:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2_800DE2C8
Vr2_800DE2C8:
	addiu	$2,$0,3
	sb	$2,3($4)
	addiu	$2,$0,96
	sb	$2,7($4)
	addiu	$2,$0,32
	sb	$2,5($4)
	sb	$2,6($4)
	addiu	$2,$0,135
	sh	$2,8($4)
	addiu	$2,$0,185
	sh	$2,10($4)
	addiu	$2,$0,50
	sh	$2,12($4)
	lbu	$2,7($4)
	addiu	$3,$0,29
	sb	$0,4($4)
	sh	$3,14($4)
	ori	$2,$2,0x2
	jr	$31
	sb	$2,7($4)
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2_800DE318
Vr2_800DE318:
	addu	$8,$0,$0
	addiu	$11,$0,3
	addiu	$10,$0,96
	addu	$9,$4,$0
$LVr2_800DE318_0:
	addu	$7,$0,$0
	addu	$6,$9,$0
$LVr2_800DE318_1:
	addiu	$2,$6,80
	sb	$10,7($2)
	addu	$3,$10,$0
	addiu	$7,$7,1
	andi	$3,$3,0xfd
	sb	$11,3($2)
	sb	$0,4($2)
	sb	$0,5($2)
	sb	$0,6($2)
	sb	$3,7($2)
	slti	$2,$7,2
	bne	$2,$0,$LVr2_800DE318_1
	addiu	$6,$6,16
	addiu	$8,$8,1
	slti	$2,$8,4
	bne	$2,$0,$LVr2_800DE318_0
	addiu	$9,$9,32
	addu	$8,$0,$0
	addiu	$10,$0,134
	addiu	$9,$0,184
	addiu	$12,$0,52
	addiu	$7,$0,1
	addiu	$14,$0,185
	addiu	$11,$0,31
	addiu	$13,$0,214
	addu	$6,$4,$0
$LVr2_800DE318_2:
	addiu	$2,$6,80
	addiu	$3,$6,112
	addiu	$4,$6,144
	addiu	$5,$6,176
	addiu	$6,$6,16
	addiu	$8,$8,1
	sh	$10,8($2)
	sh	$9,10($2)
	sh	$12,12($2)
	sh	$7,14($2)
	slti	$2,$8,2
	sh	$14,8($3)
	sh	$9,10($3)
	sh	$7,12($3)
	sh	$11,14($3)
	sh	$10,8($4)
	sh	$9,10($4)
	sh	$7,12($4)
	sh	$11,14($4)
	sh	$10,8($5)
	sh	$13,10($5)
	sh	$12,12($5)
	bne	$2,$0,$LVr2_800DE318_2
	sh	$7,14($5)
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vr2_800DE400
Vr2_800DE400:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	addiu	$4,$16,48
	lui	$2,%hi(GM_CurrentMap)
	lui	$3,%hi(GM_VrGameOverVox)
	sw	$5,%lo(GM_CurrentMap)($2)
	addiu	$2,$0,-1
	sw	$31,20($29)
	jal	Vr2_800DE2C8
	sw	$2,%lo(GM_VrGameOverVox)($3)
	jal	Vr2_800DE2C8
	addiu	$4,$16,64
	jal	Vr2_800DE318
	addu	$4,$16,$0
	lui	$3,0xe100
	ori	$3,$3,0x400
	addiu	$2,$0,1
	sb	$2,211($16)
	sb	$2,219($16)
	lui	$2,%hi(linkvarbuf)
	addiu	$2,$2,%lo(linkvarbuf)
	sw	$3,212($16)
	sw	$3,220($16)
	lhu	$3,24($2)
	sh	$0,146($2)
	lw	$31,20($29)
	lw	$16,16($29)
	lui	$2,%hi(Work+522)
	sh	$3,%lo(Work+522)($2)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,24
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NewVr2
NewVr2:
	addiu	$29,$29,-48
	sw	$19,36($29)
	addu	$19,$4,$0
	sw	$18,32($29)
	addu	$18,$5,$0
	addiu	$4,$0,5
	addiu	$5,$0,252
	sw	$31,40($29)
	sw	$17,28($29)
	jal	GV_NewActor
	sw	$16,24($29)
	lui	$3,%hi(vr_end_timer)
	addu	$17,$2,$0
	beq	$17,$0,$LNewVr2_14
	sw	$0,%lo(vr_end_timer)($3)
	addu	$4,$17,$0
	lui	$5,%hi(Vr2Act)
	addiu	$5,$5,%lo(Vr2Act)
	lui	$6,%hi(Vr2Die)
	addiu	$6,$6,%lo(Vr2Die)
	lui	$7,%hi(vr2_str_file)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(vr2_str_file)
	lui	$16,%hi(VR_Flags)
	sw	$0,%lo(VR_Flags)($16)
	jal	GCL_GetOption
	addiu	$4,$0,100
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_0
	nop
	jal	GCL_StrToInt
	nop
	sh	$2,228($17)
$LNewVr2_0:
	jal	GCL_GetOption
	addiu	$4,$0,115
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_1
	nop
	lw	$2,%lo(VR_Flags)($16)
	nop
	ori	$2,$2,0x10
	jal	GCL_StrToInt
	sw	$2,%lo(VR_Flags)($16)
	lw	$3,%lo(VR_Flags)($16)
	sll	$2,$2,8
	or	$3,$3,$2
	jal	GCL_NextStr
	sw	$3,%lo(VR_Flags)($16)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LNewVr2_2
	sw	$2,44($17)
$LNewVr2_1:
	sw	$0,44($17)
$LNewVr2_2:
	jal	GCL_GetOption
	addiu	$4,$0,101
	addu	$4,$2,$0
	bne	$4,$0,$LNewVr2_3
	nop
	lui	$4,%hi(vr2_str_endproc)
	jal	printf
	addiu	$4,$4,%lo(vr2_str_endproc)
	j	$LNewVr2_12
	nop
$LNewVr2_3:
	jal	GCL_StrToInt
	nop
	sw	$2,40($17)
	jal	GCL_GetOption
	addiu	$4,$0,97
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_4
	nop
	jal	GCL_StrToInt
	nop
	sh	$2,38($17)
	sh	$2,36($17)
	j	$LNewVr2_5
	lui	$2,%hi(VR_Status)
$LNewVr2_4:
	addiu	$2,$0,1800
	sh	$2,36($17)
	lui	$2,%hi(VR_Status)
	sh	$0,38($17)
$LNewVr2_5:
	sw	$0,%lo(VR_Status)($2)
	jal	GCL_GetOption
	addiu	$4,$0,114
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_6
	nop
	jal	GCL_StrToInt
	lui	$16,%hi(VR_Records)
	sw	$2,%lo(VR_Records)($16)
	jal	GCL_NextStr
	addiu	$16,$16,%lo(VR_Records)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	jal	GCL_NextStr
	sw	$2,4($16)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	lui	$4,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($4)
	sw	$2,8($16)
	ori	$3,$3,0x8
	sw	$3,%lo(VR_Flags)($4)
$LNewVr2_6:
	lh	$2,38($17)
	nop
	bne	$2,$0,$LNewVr2_7
	lui	$2,%hi(VR_Flags)
	lw	$3,%lo(VR_Flags)($2)
	addiu	$4,$0,-9
	and	$3,$3,$4
	sw	$3,%lo(VR_Flags)($2)
$LNewVr2_7:
	jal	GCL_GetOption
	addiu	$4,$0,111
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_8
	addiu	$2,$0,-1
	jal	GCL_StrToInt
	nop
	j	$LNewVr2_9
	sw	$2,224($17)
$LNewVr2_8:
	sw	$2,224($17)
$LNewVr2_9:
	jal	GCL_GetOption
	addiu	$4,$0,98
	addu	$4,$2,$0
	beq	$4,$0,$LNewVr2_10
	nop
	jal	GCL_StrToInt
	nop
	j	$LNewVr2_11
	sb	$2,236($17)
$LNewVr2_10:
	sb	$0,236($17)
$LNewVr2_11:
	addu	$4,$17,$0
	addu	$5,$18,$0
	jal	Vr2_800DE400
	addiu	$6,$29,16
	bgez	$2,$LNewVr2_13
	lui	$2,%hi(bikkuri_flag)
$LNewVr2_12:
	jal	GV_DestroyActor
	addu	$4,$17,$0
	j	$LNewVr2_15
	addu	$2,$0,$0
$LNewVr2_13:
	sw	$0,%lo(bikkuri_flag)($2)
	lui	$2,%hi(VR_TargetCount)
	sw	$19,32($17)
	sw	$0,%lo(VR_TargetCount)($2)
	sh	$0,248($17)
	sh	$0,244($17)
	sh	$0,246($17)
	sh	$0,250($17)
$LNewVr2_14:
	addu	$2,$17,$0
$LNewVr2_15:
	lw	$31,40($29)
	lw	$19,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.rdata
	.align	2
vr2_str_nikita:
	.ascii	"nikita"
	.byte	0
	.align	2
vr2_str_kill:
	.ascii	"kill"
	.byte	0
	.align	2
vr2_str_stinger:
	.ascii	"stinger"
	.byte	0
	.align	2
vr2_str_snake:
	.ascii	"\245\271\245\315\241\274\245\257"
	.byte	0
	.align	2
vr2_str_s:
	.ascii	"%s"
	.byte	0
	.align	2
vr2_str_time_fmt:
	.ascii	"%s:%s:%s"
	.byte	0
	.align	2
vr2_str_score:
	.ascii	"score"
	.byte	0
	.align	2
vr2_str_plus:
	.ascii	"plus"
	.byte	0
	.align	2
vr2_str_itemset:
	.ascii	"itemset"
	.byte	0
	.align	2
vr2_str_time:
	.ascii	"time"
	.byte	0
	.align	2
vr2_str_file:
	.ascii	"vr2.c"
	.byte	0
	.align	2
vr2_str_endproc:
	.ascii	"Please Set ENDPROC!\n"
	.byte	0
	.text
