	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox2GetBounds
VrBox2GetBounds:
	addiu	$11,$0,-32000
	addu	$10,$11,$0
	addiu	$9,$0,32000
	blez	$5,$LVrBox2GetBounds_5
	addu	$8,$9,$0
$LVrBox2GetBounds_0:
	lh	$3,0($4)
	nop
	slt	$2,$10,$3
	beq	$2,$0,$LVrBox2GetBounds_1
	slt	$2,$3,$8
	addu	$10,$3,$0
$LVrBox2GetBounds_1:
	beq	$2,$0,$LVrBox2GetBounds_2
	nop
	addu	$8,$3,$0
$LVrBox2GetBounds_2:
	lh	$3,4($4)
	nop
	slt	$2,$11,$3
	beq	$2,$0,$LVrBox2GetBounds_3
	slt	$2,$3,$9
	addu	$11,$3,$0
$LVrBox2GetBounds_3:
	beq	$2,$0,$LVrBox2GetBounds_4
	nop
	addu	$9,$3,$0
$LVrBox2GetBounds_4:
	addiu	$5,$5,-1
	bgtz	$5,$LVrBox2GetBounds_0
	addiu	$4,$4,8
$LVrBox2GetBounds_5:
	sh	$8,0($6)
	sh	$9,4($6)
	sh	$10,0($7)
	jr	$31
	sh	$11,4($7)
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox2Func_800DF140
VrBox2Func_800DF140:
	addiu	$29,$29,-32
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$4,0x1f80
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$31,24($29)
	lwl	$8,3($5)
	lwr	$8,0($5)
	lwl	$9,7($5)
	lwr	$9,4($5)
	swl	$8,3($17)
	swr	$8,0($17)
	swl	$9,7($17)
	swr	$9,4($17)
	addu	$5,$4,$0
	lw	$2,48($29)
	ori	$5,$5,0x20
	lui	$11,0x1f80
	ori	$11,$11,0x8
	lwl	$8,3($6)
	lwr	$8,0($6)
	lwl	$9,7($6)
	lwr	$9,4($6)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lui	$11,0x1f80
	ori	$11,$11,0x10
	lwl	$8,3($7)
	lwr	$8,0($7)
	lwl	$9,7($7)
	lwr	$9,4($7)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	lui	$11,0x1f80
	ori	$11,$11,0x18
	lwl	$8,3($2)
	lwr	$8,0($2)
	lwl	$9,7($2)
	lwr	$9,4($2)
	swl	$8,3($11)
	swr	$8,0($11)
	swl	$9,7($11)
	swr	$9,4($11)
	jal	DG_PutVector
	addiu	$6,$0,4
	lhu	$2,32($17)
	nop
	sh	$2,16($16)
	lhu	$2,34($17)
	nop
	sh	$2,20($16)
	lhu	$2,36($17)
	nop
	sh	$2,18($16)
	lhu	$2,40($17)
	nop
	sh	$2,24($16)
	lhu	$2,34($17)
	lui	$4,0x1f80
	sh	$2,28($16)
	lhu	$2,44($17)
	ori	$4,$4,0x20
	sh	$2,26($16)
	lhu	$2,48($17)
	addiu	$5,$0,4
	sh	$2,32($16)
	lhu	$2,34($17)
	lui	$6,0x1f80
	sh	$2,36($16)
	lhu	$2,52($17)
	ori	$6,$6,0x40
	sh	$2,34($16)
	lhu	$2,56($17)
	lui	$7,0x1f80
	sh	$2,40($16)
	lhu	$2,34($17)
	ori	$7,$7,0x48
	sh	$2,44($16)
	lhu	$3,60($17)
	addiu	$2,$0,255
	sh	$0,22($16)
	sh	$0,30($16)
	sh	$2,38($16)
	jal	VrBox2GetBounds
	sh	$3,42($16)
	lhu	$2,20($16)
	lhu	$3,64($17)
	addiu	$2,$2,-1
	sh	$3,0($16)
	sh	$2,4($16)
	lhu	$2,68($17)
	nop
	sh	$2,2($16)
	lhu	$2,20($16)
	lhu	$3,72($17)
	addiu	$2,$2,1
	sh	$2,12($16)
	sh	$3,8($16)
	lhu	$2,76($17)
	sh	$0,6($16)
	sh	$2,10($16)
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
	.globl	VrBox2Func_800DF2FC
VrBox2Func_800DF2FC:
	addiu	$29,$29,-80
	sw	$17,68($29)
	addu	$17,$4,$0
	addiu	$6,$0,12835
	sw	$31,72($29)
	sw	$16,64($29)
	lw	$5,36($17)
	lw	$3,32($17)
	lui	$2,%hi(GM_CurrentMap)
	jal	GM_CheckMessage
	sw	$3,%lo(GM_CurrentMap)($2)
	bne	$2,$0,$LVrBox2Func_800DF2FC_11
	lui	$2,%hi(VR_Status)
	addiu	$3,$0,2
	lw	$2,%lo(VR_Status)($2)
	lw	$16,340($17)
	bne	$2,$3,$LVrBox2Func_800DF2FC_0
	addu	$4,$16,$0
	addiu	$2,$0,-1
	sw	$2,384($17)
	jal	GV_DestroyActor
	addu	$4,$17,$0
	addu	$4,$16,$0
$LVrBox2Func_800DF2FC_0:
	jal	GM_MoveTarget
	addiu	$5,$17,684
	lbu	$2,696($17)
	nop
	beq	$2,$0,$LVrBox2Func_800DF2FC_1
	lui	$2,%hi(GV_Clock)
	lw	$4,%lo(GV_Clock)($2)
	lw	$3,40($17)
	sll	$2,$4,8
	lw	$3,52($3)
	subu	$2,$2,$4
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	lbu	$2,696($17)
	nop
	addiu	$2,$2,1
	andi	$2,$2,0xf
	bne	$2,$0,$LVrBox2Func_800DF2FC_1
	sb	$2,696($17)
	lw	$2,40($17)
	nop
	lw	$3,52($2)
	addiu	$2,$0,127
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
$LVrBox2Func_800DF2FC_1:
	lhu	$3,6($16)
	nop
	andi	$2,$3,0x4
	beq	$2,$0,$LVrBox2Func_800DF2FC_6
	nop
	lhu	$2,62($16)
	nop
	addiu	$2,$2,-1
	sltiu	$2,$2,2
	beq	$2,$0,$LVrBox2Func_800DF2FC_2
	addiu	$4,$17,684
	addiu	$5,$0,215
	addiu	$6,$0,1
	andi	$2,$3,0xfffb
	sh	$2,6($16)
	addu	$2,$6,$0
	jal	GM_SeSetMode
	sb	$2,696($17)
$LVrBox2Func_800DF2FC_2:
	lw	$2,380($17)
	nop
	bne	$2,$0,$LVrBox2Func_800DF2FC_7
	nop
	lh	$2,38($16)
	nop
	bltz	$2,$LVrBox2Func_800DF2FC_3
	addiu	$2,$0,2
	lh	$3,62($16)
	nop
	bne	$3,$2,$LVrBox2Func_800DF2FC_6
	nop
	lw	$2,692($17)
	nop
	srl	$2,$2,4
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF2FC_6
	nop
$LVrBox2Func_800DF2FC_3:
	lw	$2,692($17)
	nop
	srl	$2,$2,3
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF2FC_4
	addiu	$2,$0,1
	lbu	$2,698($17)
	j	$LVrBox2Func_800DF2FC_5
	sw	$2,380($17)
$LVrBox2Func_800DF2FC_4:
	sw	$2,380($17)
$LVrBox2Func_800DF2FC_5:
	addiu	$2,$0,1
	sh	$2,0($16)
$LVrBox2Func_800DF2FC_6:
	lw	$2,380($17)
	nop
	beq	$2,$0,$LVrBox2Func_800DF2FC_12
	nop
$LVrBox2Func_800DF2FC_7:
	lbu	$2,698($17)
	lw	$3,380($17)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$LVrBox2Func_800DF2FC_8
	addiu	$2,$3,1
	j	$LVrBox2Func_800DF2FC_12
	sw	$2,380($17)
$LVrBox2Func_800DF2FC_8:
	addiu	$16,$17,684
	addu	$4,$16,$0
	addiu	$5,$29,56
	addiu	$2,$0,3072
	sh	$2,56($29)
	addiu	$2,$0,1024
	lui	$6,%hi(VR_TargetCount)
	sh	$2,58($29)
	lw	$2,%lo(VR_TargetCount)($6)
	lui	$3,%hi(DG_ZeroVector)
	sh	$0,60($29)
	addiu	$11,$3,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,59($29)
	swr	$8,56($29)
	swl	$9,63($29)
	swr	$9,60($29)
	addiu	$2,$2,1
	jal	DG_SetPos2
	sw	$2,%lo(VR_TargetCount)($6)
	jal	ReadRotMatrix
	addiu	$4,$29,24
	addu	$4,$16,$0
	addiu	$5,$0,201
	jal	GM_SeSetMode
	addiu	$6,$0,1
	lw	$3,692($17)
	nop
	srl	$2,$3,3
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF2FC_10
	srl	$2,$3,8
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF2FC_9
	addiu	$4,$29,24
	addiu	$5,$17,332
	lhu	$2,700($17)
	addiu	$6,$0,32
	sw	$2,16($29)
	lbu	$2,697($17)
	addu	$7,$0,$0
	jal	NewSplashVr
	sw	$2,20($29)
	addiu	$4,$29,24
$LVrBox2Func_800DF2FC_9:
	lui	$5,%hi(blast_data_8009F4B8)
	jal	NewBlast
	addiu	$5,$5,%lo(blast_data_8009F4B8)
	j	$LVrBox2Func_800DF2FC_11
	nop
$LVrBox2Func_800DF2FC_10:
	addiu	$4,$29,24
	addiu	$5,$17,332
	lhu	$2,700($17)
	addiu	$6,$0,64
	sw	$2,16($29)
	lbu	$2,697($17)
	addu	$7,$0,$0
	jal	NewSplashVr
	sw	$2,20($29)
$LVrBox2Func_800DF2FC_11:
	jal	GV_DestroyActor
	addu	$4,$17,$0
$LVrBox2Func_800DF2FC_12:
	lw	$31,72($29)
	lw	$17,68($29)
	lw	$16,64($29)
	jr	$31
	addiu	$29,$29,80
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox2Func_800DF5C4
VrBox2Func_800DF5C4:
	addiu	$29,$29,-40
	sw	$19,28($29)
	addu	$19,$4,$0
	sw	$31,32($29)
	sw	$18,24($29)
	sw	$17,20($29)
	sw	$16,16($29)
	lw	$2,692($19)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF5C4_3
	addiu	$17,$19,396
	addiu	$18,$19,464
	addu	$5,$17,$0
	lw	$4,388($19)
	lw	$6,460($19)
	jal	THING_Hzd_800C4874
	addu	$7,$18,$0
	lw	$16,388($19)
	nop
	blez	$16,$LVrBox2Func_800DF5C4_1
	addu	$5,$17,$0
$LVrBox2Func_800DF5C4_0:
	addiu	$17,$17,16
	lw	$4,392($19)
	jal	HZD_DequeueDynamicSegment
	addiu	$16,$16,-1
	bgtz	$16,$LVrBox2Func_800DF5C4_0
	addu	$5,$17,$0
$LVrBox2Func_800DF5C4_1:
	lw	$16,460($19)
	nop
	blez	$16,$LVrBox2Func_800DF5C4_3
	addu	$5,$18,$0
$LVrBox2Func_800DF5C4_2:
	addiu	$18,$18,48
	lw	$4,392($19)
	jal	HZD_DequeueDynamicFloor
	addiu	$16,$16,-1
	bgtz	$16,$LVrBox2Func_800DF5C4_2
	addu	$5,$18,$0
$LVrBox2Func_800DF5C4_3:
	lw	$4,344($19)
	jal	GM_ResetHomingTarget
	nop
	jal	GM_FreeObject
	addiu	$4,$19,40
	lw	$4,340($19)
	jal	GM_FreeTarget
	nop
	lw	$4,384($19)
	nop
	blez	$4,$LVrBox2Func_800DF5C4_4
	nop
	jal	GCL_ExecProc
	addu	$5,$0,$0
$LVrBox2Func_800DF5C4_4:
	lw	$31,32($29)
	lw	$19,28($29)
	lw	$18,24($29)
	lw	$17,20($29)
	lw	$16,16($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox2Func_800DF6B0
VrBox2Func_800DF6B0:
	addiu	$29,$29,-48
	sw	$16,24($29)
	addu	$16,$4,$0
	sw	$18,32($29)
	addu	$18,$5,$0
	sw	$19,36($29)
	addu	$19,$6,$0
	sw	$31,40($29)
	jal	GM_AllocTarget
	sw	$17,28($29)
	addu	$17,$2,$0
	addu	$4,$17,$0
	addiu	$5,$0,28
	addiu	$6,$0,2
	addiu	$7,$16,332
	sw	$17,340($16)
	lwl	$8,3($18)
	lwr	$8,0($18)
	lwl	$9,7($18)
	lwr	$9,4($18)
	swl	$8,335($16)
	swr	$8,332($16)
	swl	$9,339($16)
	swr	$9,336($16)
	lhu	$2,332($16)
	lhu	$3,336($16)
	addiu	$2,$2,50
	addiu	$3,$3,50
	sh	$2,332($16)
	jal	GM_SetTarget
	sh	$3,336($16)
	addu	$4,$17,$0
	addiu	$5,$0,1
	addiu	$6,$0,-1
	addu	$7,$19,$0
	lui	$2,%hi(DG_ZeroVector)
	addiu	$2,$2,%lo(DG_ZeroVector)
	sw	$0,16($29)
	jal	GM_SetPowerTarget
	sw	$2,20($29)
	addu	$4,$17,$0
	jal	GM_MoveTarget
	addiu	$5,$16,684
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
	.globl	VrBox2Func_800DF778
VrBox2Func_800DF778:
	addiu	$29,$29,-136
	sw	$20,120($29)
	addu	$20,$4,$0
	addiu	$4,$0,112
	sw	$21,124($29)
	addu	$21,$6,$0
	lui	$2,%hi(GM_CurrentMap)
	sw	$31,132($29)
	sw	$22,128($29)
	sw	$19,116($29)
	sw	$18,112($29)
	sw	$17,108($29)
	sw	$16,104($29)
	sw	$21,%lo(GM_CurrentMap)($2)
	sw	$21,32($20)
	jal	GCL_GetOption
	sw	$5,36($20)
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_0
	addu	$4,$18,$0
	jal	GCL_StrToSV
	addiu	$5,$29,56
	lwl	$8,59($29)
	lwr	$8,56($29)
	lwl	$9,63($29)
	lwr	$9,60($29)
	swl	$8,687($20)
	swr	$8,684($20)
	swl	$9,691($20)
	swr	$9,688($20)
	j	$LVrBox2Func_800DF778_1
	lui	$2,%hi(DG_ZeroVector)
$LVrBox2Func_800DF778_0:
	lui	$2,%hi(DG_ZeroVector)
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,687($20)
	swr	$8,684($20)
	swl	$9,691($20)
	swr	$9,688($20)
	lui	$2,%hi(DG_ZeroVector)
$LVrBox2Func_800DF778_1:
	addiu	$11,$2,%lo(DG_ZeroVector)
	lwl	$8,3($11)
	lwr	$8,0($11)
	lwl	$9,7($11)
	lwr	$9,4($11)
	swl	$8,59($29)
	swr	$8,56($29)
	swl	$9,63($29)
	swr	$9,60($29)
	jal	GCL_GetOption
	addiu	$4,$0,98
	addiu	$4,$0,104
	addiu	$5,$0,-9
	sltu	$2,$0,$2
	lw	$3,692($20)
	sll	$2,$2,3
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GCL_GetOption
	sw	$3,692($20)
	beq	$2,$0,$LVrBox2Func_800DF778_3
	nop
	jal	GM_GetMap
	addu	$4,$21,$0
	bne	$2,$0,$LVrBox2Func_800DF778_2
	sw	$2,604($20)
	lui	$4,%hi(vrbox2_str_no_map)
	addiu	$4,$4,%lo(vrbox2_str_no_map)
	jal	printf
	addu	$5,$21,$0
$LVrBox2Func_800DF778_2:
	addiu	$4,$20,348
	jal	GM_SetHomingTarget
	addiu	$5,$20,560
	addiu	$3,$0,1
	sw	$2,344($20)
	j	$LVrBox2Func_800DF778_4
	sw	$3,8($2)
$LVrBox2Func_800DF778_3:
	sw	$0,344($20)
$LVrBox2Func_800DF778_4:
	jal	GCL_GetOption
	addiu	$4,$0,97
	beq	$2,$0,$LVrBox2Func_800DF778_5
	addiu	$3,$0,-257
	lw	$2,692($20)
	j	$LVrBox2Func_800DF778_6
	ori	$2,$2,0x100
$LVrBox2Func_800DF778_5:
	lw	$2,692($20)
	nop
	and	$2,$2,$3
$LVrBox2Func_800DF778_6:
	sw	$2,692($20)
	jal	GCL_GetOption
	addiu	$4,$0,108
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_7
	addu	$4,$18,$0
	lw	$2,692($20)
	nop
	ori	$2,$2,0x10
	jal	GCL_StrToInt
	sw	$2,692($20)
	j	$LVrBox2Func_800DF778_8
	addu	$22,$2,$0
$LVrBox2Func_800DF778_7:
	addiu	$22,$0,150
	lw	$2,692($20)
	addiu	$3,$0,-17
	and	$2,$2,$3
	sw	$2,692($20)
$LVrBox2Func_800DF778_8:
	jal	GCL_GetOption
	addiu	$4,$0,101
	beq	$2,$0,$LVrBox2Func_800DF778_9
	addiu	$2,$0,-1
	jal	GCL_NextStr
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrBox2Func_800DF778_10
	sw	$2,384($20)
$LVrBox2Func_800DF778_9:
	sw	$2,384($20)
$LVrBox2Func_800DF778_10:
	jal	GCL_GetOption
	addiu	$4,$0,119
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_11
	nop
	jal	GCL_StrToInt
	addu	$4,$18,$0
	addiu	$4,$0,-2
	lw	$3,692($20)
	andi	$2,$2,0x1
	and	$3,$3,$4
	or	$3,$3,$2
	j	$LVrBox2Func_800DF778_12
	sw	$3,692($20)
$LVrBox2Func_800DF778_11:
	lw	$2,692($20)
	nop
	ori	$2,$2,0x1
	sw	$2,692($20)
$LVrBox2Func_800DF778_12:
	jal	GCL_GetOption
	addiu	$4,$0,109
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_13
	addiu	$3,$0,-225
	jal	GCL_StrToInt
	addu	$4,$18,$0
	addiu	$4,$0,-225
	andi	$2,$2,0x7
	lw	$3,692($20)
	sll	$2,$2,5
	and	$3,$3,$4
	or	$3,$3,$2
	j	$LVrBox2Func_800DF778_14
	sw	$3,692($20)
$LVrBox2Func_800DF778_13:
	lw	$2,692($20)
	nop
	and	$2,$2,$3
	sw	$2,692($20)
$LVrBox2Func_800DF778_14:
	jal	GCL_GetOption
	addiu	$4,$0,100
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_15
	addiu	$2,$0,4
	jal	GCL_StrToInt
	addu	$4,$18,$0
	j	$LVrBox2Func_800DF778_16
	sb	$2,698($20)
$LVrBox2Func_800DF778_15:
	sb	$2,698($20)
$LVrBox2Func_800DF778_16:
	lw	$3,692($20)
	nop
	srl	$2,$3,5
	andi	$2,$2,0x7
	bne	$2,$0,$LVrBox2Func_800DF778_24
	addiu	$19,$20,40
	jal	GCL_GetOption
	addiu	$4,$0,107
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_19
	addu	$4,$18,$0
	lw	$2,692($20)
	nop
	ori	$2,$2,0x2
	jal	GCL_StrToInt
	sw	$2,692($20)
	addu	$5,$2,$0
	slti	$2,$5,2
	beq	$2,$0,$LVrBox2Func_800DF778_17
	lui	$4,%hi(vrbox2_str_kabe_n)
	addiu	$4,$4,%lo(vrbox2_str_kabe_n)
	lw	$3,692($20)
	addiu	$2,$0,-5
	and	$3,$3,$2
	andi	$2,$5,0x1
	sll	$2,$2,2
	or	$3,$3,$2
	j	$LVrBox2Func_800DF778_18
	sw	$3,692($20)
$LVrBox2Func_800DF778_17:
	lui	$4,%hi(vrbox2_str_kabe_y)
	addiu	$4,$4,%lo(vrbox2_str_kabe_y)
	lw	$2,692($20)
	addiu	$3,$0,-5
	and	$2,$2,$3
	sw	$2,692($20)
$LVrBox2Func_800DF778_18:
	jal	GV_StrCode
	nop
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	jal	GCL_StrToInt
	addu	$4,$18,$0
	lui	$4,%hi(vrbox2_str_kabe_01add)
	addiu	$4,$4,%lo(vrbox2_str_kabe_01add)
	addiu	$5,$0,-5
	andi	$2,$2,0x1
	lw	$3,692($20)
	sll	$2,$2,2
	and	$3,$3,$5
	or	$3,$3,$2
	jal	GV_StrCode
	sw	$3,692($20)
	sw	$2,700($20)
	addiu	$2,$0,64
	j	$LVrBox2Func_800DF778_22
	sb	$2,697($20)
$LVrBox2Func_800DF778_19:
	lw	$2,692($20)
	nop
	srl	$2,$2,3
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF778_20
	nop
	lui	$4,%hi(vrbox2_str_kt_n)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_kt_n)
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox2_str_mato_00add)
	j	$LVrBox2Func_800DF778_21
	addiu	$4,$4,%lo(vrbox2_str_mato_00add)
$LVrBox2Func_800DF778_20:
	lui	$4,%hi(vrbox2_str_kt_b)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_kt_b)
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox2_str_mato_02add)
	addiu	$4,$4,%lo(vrbox2_str_mato_02add)
$LVrBox2Func_800DF778_21:
	jal	GV_StrCode
	nop
	sw	$2,700($20)
	addiu	$2,$0,64
	sb	$2,697($20)
	lw	$2,692($20)
	addiu	$3,$0,-3
	and	$2,$2,$3
	addiu	$3,$0,-5
	and	$2,$2,$3
	sw	$2,692($20)
$LVrBox2Func_800DF778_22:
	lw	$2,692($20)
	nop
	srl	$2,$2,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF778_23
	nop
	lw	$5,0($19)
	jal	RotMatrixY
	addiu	$4,$0,1024
$LVrBox2Func_800DF778_23:
	lw	$2,692($20)
	nop
	srl	$2,$2,1
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF778_29
	nop
	lhu	$2,686($20)
	nop
	addiu	$2,$2,1000
	sh	$2,686($20)
	lw	$3,0($19)
	lh	$2,684($20)
	nop
	sw	$2,20($3)
	lw	$3,0($19)
	lh	$2,686($20)
	nop
	sw	$2,24($3)
	lw	$3,0($19)
	lh	$2,688($20)
	nop
	sw	$2,28($3)
	lw	$2,40($20)
	nop
	lw	$8,0($2)
	lw	$9,4($2)
	lw	$10,8($2)
	lw	$11,12($2)
	sw	$8,348($20)
	sw	$9,352($20)
	sw	$10,356($20)
	sw	$11,360($20)
	lw	$8,16($2)
	lw	$9,20($2)
	lw	$10,24($2)
	lw	$11,28($2)
	sw	$8,364($20)
	sw	$9,368($20)
	sw	$10,372($20)
	sw	$11,376($20)
	lw	$2,372($20)
	j	$LVrBox2Func_800DF778_30
	addiu	$2,$2,200
$LVrBox2Func_800DF778_24:
	addiu	$2,$0,-3
	and	$2,$3,$2
	sw	$2,692($20)
	lbu	$3,692($20)
	addiu	$2,$0,64
	sb	$2,697($20)
	addiu	$2,$0,2
	srl	$3,$3,5
	beq	$3,$2,$LVrBox2Func_800DF778_27
	slti	$2,$3,3
	beq	$2,$0,$LVrBox2Func_800DF778_25
	addiu	$2,$0,1
	beq	$3,$2,$LVrBox2Func_800DF778_26
	lui	$4,%hi(vrbox2_str_kt_n)
	j	$LVrBox2Func_800DF778_29
	nop
$LVrBox2Func_800DF778_25:
	addiu	$2,$0,3
	beq	$3,$2,$LVrBox2Func_800DF778_28
	lui	$4,%hi(vrbox2_str_ice)
	j	$LVrBox2Func_800DF778_29
	nop
$LVrBox2Func_800DF778_26:
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_kt_n)
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox2_str_mato_00add)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_mato_00add)
	j	$LVrBox2Func_800DF778_29
	sw	$2,700($20)
$LVrBox2Func_800DF778_27:
	lui	$4,%hi(vrbox2_str_kt_b)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_kt_b)
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
	lui	$4,%hi(vrbox2_str_mato_02add)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_mato_02add)
	lw	$3,692($20)
	sw	$2,700($20)
	ori	$3,$3,0x8
	j	$LVrBox2Func_800DF778_29
	sw	$3,692($20)
$LVrBox2Func_800DF778_28:
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox2_str_ice)
	addu	$4,$19,$0
	addu	$5,$2,$0
	addiu	$6,$0,349
	jal	GM_InitObject
	addu	$7,$0,$0
$LVrBox2Func_800DF778_29:
	lhu	$2,686($20)
	nop
	addiu	$2,$2,500
	sh	$2,686($20)
	lw	$3,0($19)
	lh	$2,684($20)
	nop
	sw	$2,20($3)
	lh	$2,686($20)
	lw	$3,0($19)
	addiu	$2,$2,-500
	sw	$2,24($3)
	lw	$3,0($19)
	lh	$2,688($20)
	nop
	sw	$2,28($3)
	lw	$2,40($20)
	nop
	lw	$8,0($2)
	lw	$9,4($2)
	lw	$10,8($2)
	lw	$11,12($2)
	sw	$8,348($20)
	sw	$9,352($20)
	sw	$10,356($20)
	sw	$11,360($20)
	lw	$8,16($2)
	lw	$9,20($2)
	lw	$10,24($2)
	lw	$11,28($2)
	sw	$8,364($20)
	sw	$9,368($20)
	sw	$10,372($20)
	sw	$11,376($20)
	lw	$2,372($20)
	nop
	addiu	$2,$2,700
$LVrBox2Func_800DF778_30:
	sw	$2,372($20)
	jal	GCL_GetOption
	addiu	$4,$0,121
	addu	$18,$2,$0
	beq	$18,$0,$LVrBox2Func_800DF778_32
	addu	$4,$19,$0
	lw	$3,0($19)
	nop
	lh	$2,46($3)
	nop
	blez	$2,$LVrBox2Func_800DF778_32
	addu	$17,$0,$0
	addiu	$16,$3,152
$LVrBox2Func_800DF778_31:
	jal	GCL_StrToInt
	addu	$4,$18,$0
	lhu	$3,0($16)
	nop
	addu	$3,$3,$2
	sh	$3,0($16)
	lw	$2,0($19)
	addiu	$17,$17,1
	lh	$2,46($2)
	nop
	slt	$2,$17,$2
	bne	$2,$0,$LVrBox2Func_800DF778_31
	addiu	$16,$16,92
	addu	$4,$19,$0
$LVrBox2Func_800DF778_32:
	jal	GM_ConfigObjectLight
	addiu	$5,$20,268
	lw	$2,40($20)
	nop
	lw	$3,52($2)
	addiu	$2,$0,127
	sw	$2,28($3)
	sw	$2,24($3)
	sw	$2,20($3)
	lw	$3,692($20)
	sw	$0,380($20)
	srl	$2,$3,1
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF778_34
	sb	$0,696($20)
	srl	$2,$3,2
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF778_33
	addiu	$2,$0,1000
	sh	$0,64($29)
	sh	$2,66($29)
	j	$LVrBox2Func_800DF778_35
	sh	$2,68($29)
$LVrBox2Func_800DF778_33:
	sh	$2,64($29)
	sh	$2,66($29)
	j	$LVrBox2Func_800DF778_35
	sh	$0,68($29)
$LVrBox2Func_800DF778_34:
	addiu	$3,$0,525
	addiu	$2,$0,500
	sh	$3,64($29)
	sh	$2,66($29)
	sh	$3,68($29)
$LVrBox2Func_800DF778_35:
	addu	$4,$20,$0
	addiu	$5,$29,64
	jal	VrBox2Func_800DF6B0
	addu	$6,$22,$0
	lhu	$2,64($29)
	lhu	$3,66($29)
	lhu	$5,68($29)
	subu	$7,$0,$2
	subu	$4,$0,$5
	subu	$6,$0,$3
	sh	$7,72($29)
	sh	$3,74($29)
	sh	$4,76($29)
	sh	$2,80($29)
	sh	$6,82($29)
	sh	$4,84($29)
	sh	$2,88($29)
	sh	$3,90($29)
	sh	$5,92($29)
	sh	$7,96($29)
	sh	$6,98($29)
	sh	$5,100($29)
	lw	$2,692($20)
	nop
	andi	$2,$2,0x1
	beq	$2,$0,$LVrBox2Func_800DF778_39
	addiu	$16,$20,396
	jal	GM_GetMap
	addu	$4,$21,$0
	addiu	$4,$20,684
	lw	$2,8($2)
	addiu	$5,$29,56
	jal	DG_SetPos2
	sw	$2,392($20)
	jal	ReadRotMatrix
	addiu	$4,$29,24
	lw	$2,692($20)
	nop
	srl	$2,$2,1
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF778_37
	addu	$4,$16,$0
	addiu	$2,$0,4
	sw	$2,388($20)
	addu	$17,$0,$0
	addiu	$18,$29,72
$LVrBox2Func_800DF778_36:
	addu	$4,$16,$0
	addiu	$5,$29,24
	sll	$6,$17,3
	addu	$6,$18,$6
	addiu	$3,$17,1
	andi	$7,$3,0x3
	sll	$7,$7,3
	lhu	$2,66($29)
	addu	$7,$18,$7
	subu	$2,$0,$2
	addiu	$2,$2,-250
	sh	$2,2($6)
	lhu	$2,66($29)
	addu	$17,$3,$0
	jal	THING_Hzd_800C45C4
	sh	$2,2($7)
	addu	$5,$16,$0
	lw	$4,392($20)
	jal	HZD_QueueDynamicSegment2
	addu	$6,$0,$0
	lw	$3,388($20)
	addiu	$16,$16,16
	addu	$3,$3,$2
	slti	$2,$17,4
	bne	$2,$0,$LVrBox2Func_800DF778_36
	sw	$3,388($20)
	j	$LVrBox2Func_800DF778_38
	nop
$LVrBox2Func_800DF778_37:
	addiu	$2,$0,1
	lw	$3,692($20)
	addiu	$7,$29,72
	sw	$2,388($20)
	srl	$17,$3,2
	and	$17,$17,$2
	sll	$6,$17,3
	lhu	$2,66($29)
	addu	$6,$7,$6
	subu	$2,$0,$2
	sh	$2,2($6)
	addiu	$2,$17,1
	sll	$2,$2,3
	addu	$7,$7,$2
	lhu	$2,66($29)
	addiu	$5,$29,24
	jal	THING_Hzd_800C45C4
	sh	$2,2($7)
	addu	$5,$16,$0
	lw	$4,392($20)
	jal	HZD_QueueDynamicSegment2
	addu	$6,$0,$0
	lw	$3,388($20)
	nop
	addu	$3,$3,$2
	sw	$3,388($20)
$LVrBox2Func_800DF778_38:
	lw	$2,692($20)
	nop
	srl	$2,$2,1
	andi	$2,$2,0x1
	bne	$2,$0,$LVrBox2Func_800DF778_39
	addiu	$21,$20,464
	addu	$4,$21,$0
	addiu	$16,$29,72
	addu	$5,$16,$0
	addiu	$17,$29,80
	addu	$6,$17,$0
	addiu	$2,$0,2
	addiu	$18,$29,88
	addu	$7,$18,$0
	sw	$2,460($20)
	lhu	$2,66($29)
	addiu	$19,$29,96
	sh	$2,98($29)
	sh	$2,90($29)
	sh	$2,82($29)
	sh	$2,74($29)
	jal	VrBox2Func_800DF140
	sw	$19,16($29)
	addu	$5,$21,$0
	lw	$4,392($20)
	jal	HZD_QueueDynamicFloor
	addiu	$21,$20,512
	addu	$4,$21,$0
	addu	$5,$16,$0
	lw	$3,460($20)
	addu	$6,$17,$0
	addu	$3,$3,$2
	sw	$3,460($20)
	lhu	$2,66($29)
	addu	$7,$18,$0
	subu	$2,$0,$2
	addiu	$2,$2,-250
	sh	$2,98($29)
	sh	$2,90($29)
	sh	$2,82($29)
	sh	$2,74($29)
	jal	VrBox2Func_800DF140
	sw	$19,16($29)
	lw	$4,392($20)
	jal	HZD_QueueDynamicFloor
	addu	$5,$21,$0
	lw	$3,460($20)
	nop
	addu	$3,$3,$2
	sw	$3,460($20)
$LVrBox2Func_800DF778_39:
	lw	$31,132($29)
	lw	$22,128($29)
	lw	$21,124($29)
	lw	$20,120($29)
	lw	$19,116($29)
	lw	$18,112($29)
	lw	$17,108($29)
	lw	$16,104($29)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,136
	.set	macro
	.set	reorder
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NewVrBox2
NewVrBox2:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	addiu	$4,$0,5
	addiu	$5,$0,704
	sw	$31,28($29)
	jal	GV_NewActor
	sw	$16,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LNewVrBox2_0
	addu	$4,$16,$0
	lui	$5,%hi(VrBox2Func_800DF2FC)
	addiu	$5,$5,%lo(VrBox2Func_800DF2FC)
	lui	$6,%hi(VrBox2Func_800DF5C4)
	addiu	$6,$6,%lo(VrBox2Func_800DF5C4)
	lui	$7,%hi(vrbox2_str_file)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(vrbox2_str_file)
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	VrBox2Func_800DF778
	addu	$6,$18,$0
	bgez	$2,$LNewVrBox2_1
	addu	$2,$16,$0
	jal	GV_DestroyActor
	addu	$4,$16,$0
	j	$LNewVrBox2_1
	addu	$2,$0,$0
$LNewVrBox2_0:
	addu	$2,$16,$0
$LNewVrBox2_1:
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
vrbox2_str_no_map:
	.ascii	"InitControl : no map %X\n"
	.byte	0
	.align	2
vrbox2_str_kabe_n:
	.ascii	"kabe_n"
	.byte	0
	.align	2
vrbox2_str_kabe_y:
	.ascii	"kabe_y"
	.byte	0
	.align	2
vrbox2_str_kabe_01add:
	.ascii	"kabe_01add"
	.byte	0
	.align	2
vrbox2_str_kt_n:
	.ascii	"kt_n"
	.byte	0
	.align	2
vrbox2_str_mato_00add:
	.ascii	"mato_00add"
	.byte	0
	.align	2
vrbox2_str_kt_b:
	.ascii	"kt_b"
	.byte	0
	.align	2
vrbox2_str_mato_02add:
	.ascii	"mato_02add"
	.byte	0
	.align	2
vrbox2_str_ice:
	.ascii	"ice"
	.byte	0
	.align	2
vrbox2_str_file:
	.ascii	"vrbox2.c"
	.byte	0
	.text
