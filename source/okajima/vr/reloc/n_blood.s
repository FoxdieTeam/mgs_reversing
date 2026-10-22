	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodInitVerts
NBloodInitVerts:
	addiu	$29,$29,-96
	sw	$16,56($29)
	lw	$16,112($29)
	sw	$23,84($29)
	addu	$23,$5,$0
	sw	$30,88($29)
	addu	$30,$6,$0
	sw	$22,80($29)
	addu	$22,$7,$0
	sw	$31,92($29)
	sw	$21,76($29)
	sw	$20,72($29)
	sw	$19,68($29)
	sw	$18,64($29)
	sw	$17,60($29)
	jal	DG_SetPos
	sw	$22,48($29)
	lui	$4,%hi(nblood_data)
	jal	DG_RotatePos
	addiu	$4,$4,%lo(nblood_data)
	addiu	$22,$22,-1
	bltz	$22,$LNBloodInitVerts_9
	addiu	$21,$23,4
$LNBloodInitVerts_0:
	jal	GV_RandU
	addiu	$4,$0,4096
	addu	$16,$2,$0
	jal	rcos
	addu	$4,$16,$0
	addu	$4,$16,$0
	jal	rsin
	sra	$17,$2,4
	addiu	$4,$0,128
	jal	GV_RandU
	sra	$18,$2,4
	addiu	$16,$2,32
	div	$17,$16
	bne	$16,$0,$LNBloodInitVerts_1
	nop
	.word	0x0007000D
$LNBloodInitVerts_1:
	addiu	$1,$0,-1
	bne	$16,$1,$LNBloodInitVerts_2
	lui	$1,0x8000
	bne	$17,$1,$LNBloodInitVerts_2
	nop
	.word	0x0006000D
$LNBloodInitVerts_2:
	mflo	$17
	nop
	nop
	div	$18,$16
	bne	$16,$0,$LNBloodInitVerts_3
	nop
	.word	0x0007000D
$LNBloodInitVerts_3:
	addiu	$1,$0,-1
	bne	$16,$1,$LNBloodInitVerts_4
	lui	$1,0x8000
	bne	$18,$1,$LNBloodInitVerts_4
	nop
	.word	0x0006000D
$LNBloodInitVerts_4:
	mflo	$18
	addiu	$4,$0,64
	sll	$2,$16,3
	sh	$16,18($29)
	sh	$2,42($29)
	sll	$2,$17,3
	sh	$2,40($29)
	sll	$2,$18,3
	sh	$17,16($29)
	sh	$18,20($29)
	jal	GV_RandS
	sh	$2,44($29)
	addiu	$4,$0,64
	jal	GV_RandS
	addu	$20,$2,$0
	addiu	$4,$0,64
	jal	GV_RandS
	addu	$19,$2,$0
	addiu	$4,$29,16
	addu	$5,$23,$0
	addiu	$6,$0,1
	addu	$3,$17,$20
	addu	$16,$16,$19
	sh	$3,24($29)
	addu	$3,$18,$2
	subu	$17,$17,$20
	subu	$18,$18,$2
	sh	$16,26($29)
	sh	$3,28($29)
	sh	$17,32($29)
	sh	$16,34($29)
	jal	DG_RotVector
	sh	$18,36($29)
	addiu	$4,$29,16
	addu	$5,$30,$0
	jal	DG_PutVector
	addiu	$6,$0,4
	lw	$8,48($29)
	nop
	addiu	$2,$8,-1
	slt	$2,$22,$2
	bne	$2,$0,$LNBloodInitVerts_8
	nop
	lh	$2,0($23)
	nop
	bgez	$2,$LNBloodInitVerts_5
	nop
	addiu	$2,$2,3
$LNBloodInitVerts_5:
	sra	$2,$2,2
	sh	$2,0($23)
	lh	$2,-2($21)
	nop
	bgez	$2,$LNBloodInitVerts_6
	nop
	addiu	$2,$2,3
$LNBloodInitVerts_6:
	lh	$3,0($21)
	sra	$2,$2,2
	bgez	$3,$LNBloodInitVerts_7
	sh	$2,-2($21)
	addiu	$3,$3,3
$LNBloodInitVerts_7:
	sra	$2,$3,2
	sh	$2,0($21)
$LNBloodInitVerts_8:
	addiu	$21,$21,8
	addiu	$23,$23,8
	addiu	$22,$22,-1
	bgez	$22,$LNBloodInitVerts_0
	addiu	$30,$30,32
$LNBloodInitVerts_9:
	lw	$31,92($29)
	lw	$30,88($29)
	lw	$23,84($29)
	lw	$22,80($29)
	lw	$21,76($29)
	lw	$20,72($29)
	lw	$19,68($29)
	lw	$18,64($29)
	lw	$17,60($29)
	lw	$16,56($29)
	jr	$31
	addiu	$29,$29,96
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodUpdateVerts
NBloodUpdateVerts:
	addu	$10,$4,$0
	addiu	$9,$6,-1
	bltz	$9,$LNBloodUpdateVerts_1
	addu	$11,$5,$0
	addiu	$8,$4,4
	addiu	$7,$5,20
$LNBloodUpdateVerts_0:
	addiu	$9,$9,-1
	lh	$5,0($10)
	lh	$4,-2($8)
	lhu	$2,0($11)
	lh	$6,0($8)
	addu	$2,$2,$5
	sh	$2,0($11)
	addiu	$11,$11,32
	lhu	$2,-18($7)
	lhu	$3,4($7)
	addu	$2,$2,$4
	sh	$2,-18($7)
	lhu	$2,-16($7)
	addu	$3,$3,$5
	sh	$3,4($7)
	lhu	$3,8($7)
	addu	$2,$2,$6
	sh	$2,-16($7)
	lhu	$2,6($7)
	addu	$3,$3,$6
	sh	$3,8($7)
	lhu	$3,-10($7)
	addu	$2,$2,$4
	sh	$2,6($7)
	lhu	$2,-12($7)
	addu	$3,$3,$4
	sh	$3,-10($7)
	lhu	$3,-4($7)
	addu	$2,$2,$5
	sh	$2,-12($7)
	lhu	$2,-8($7)
	addu	$3,$3,$5
	sh	$3,-4($7)
	lhu	$3,0($7)
	addu	$2,$2,$6
	sh	$2,-8($7)
	lhu	$2,-2($7)
	addu	$3,$3,$6
	sh	$3,0($7)
	addu	$2,$2,$4
	sh	$2,-2($7)
	addiu	$7,$7,32
	addiu	$4,$4,-11
	sh	$5,0($10)
	sh	$4,-2($8)
	sh	$6,0($8)
	addiu	$8,$8,8
	bgez	$9,$LNBloodUpdateVerts_0
	addiu	$10,$10,8
$LNBloodUpdateVerts_1:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodInitPacks
NBloodInitPacks:
	addiu	$9,$5,-1
	bltz	$9,$LNBloodInitPacks_1
	addiu	$12,$0,9
	addiu	$11,$0,46
	addiu	$10,$0,2
	addiu	$8,$4,22
$LNBloodInitPacks_0:
	sb	$12,-19($8)
	sb	$11,-15($8)
	lbu	$4,8($6)
	lbu	$3,10($6)
	lbu	$2,9($6)
	lbu	$5,11($6)
	addu	$3,$4,$3
	sb	$2,-9($8)
	sb	$2,-1($8)
	addu	$2,$2,$5
	sb	$4,-10($8)
	sb	$3,-2($8)
	sb	$4,6($8)
	sb	$2,7($8)
	sb	$3,14($8)
	sb	$2,15($8)
	lhu	$2,4($6)
	nop
	sh	$2,0($8)
	lhu	$2,6($6)
	nop
	sh	$2,-8($8)
	lhu	$2,0($8)
	nop
	ori	$2,$2,0x20
	sh	$2,0($8)
	addiu	$9,$9,-1
	bgez	$9,$LNBloodInitPacks_0
	addiu	$8,$8,40
$LNBloodInitPacks_1:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodShadePacks
NBloodShadePacks:
	addiu	$5,$5,-1
	bltz	$5,$LNBloodShadePacks_1
	addiu	$4,$4,6
$LNBloodShadePacks_0:
	sb	$6,-2($4)
	sb	$6,-1($4)
	sb	$6,0($4)
	addiu	$5,$5,-1
	bgez	$5,$LNBloodShadePacks_0
	addiu	$4,$4,40
$LNBloodShadePacks_1:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodAct
NBloodAct:
	addiu	$29,$29,-32
	sw	$18,24($29)
	addu	$18,$4,$0
	lui	$3,%hi(GM_CurrentMap)
	sw	$31,28($29)
	sw	$17,20($29)
	sw	$16,16($29)
	lw	$4,680($18)
	lw	$2,32($18)
	addiu	$16,$4,-1
	sw	$2,%lo(GM_CurrentMap)($3)
	bgtz	$16,$LNBloodAct_0
	sw	$16,680($18)
	jal	GV_DestroyActor
	addu	$4,$18,$0
	j	$LNBloodAct_1
	nop
$LNBloodAct_0:
	addiu	$4,$18,40
	lw	$6,684($18)
	jal	NBloodUpdateVerts
	addiu	$5,$18,168
	sll	$16,$16,3
	lw	$17,36($18)
	lw	$5,684($18)
	lw	$4,64($17)
	jal	NBloodShadePacks
	addu	$6,$16,$0
	lw	$4,68($17)
	lw	$5,684($18)
	jal	NBloodShadePacks
	addu	$6,$16,$0
$LNBloodAct_1:
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
	.globl	NBloodDie
NBloodDie:
	addiu	$29,$29,-24
	sw	$31,20($29)
	sw	$16,16($29)
	lw	$16,36($4)
	nop
	beq	$16,$0,$LNBloodDie_0
	nop
	jal	DG_DequeuePrim
	addu	$4,$16,$0
	jal	DG_FreePrim
	addu	$4,$16,$0
$LNBloodDie_0:
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
	.globl	NBloodGetResources
NBloodGetResources:
	addiu	$29,$29,-48
	sw	$18,32($29)
	addu	$18,$4,$0
	addu	$4,$5,$0
	sw	$19,36($29)
	addu	$19,$6,$0
	slti	$2,$19,11
	sw	$31,40($29)
	sw	$17,28($29)
	sw	$16,24($29)
	beq	$2,$0,$LNBloodGetResources_0
	sw	$7,32($18)
	j	$LNBloodGetResources_1
	addiu	$2,$0,16
$LNBloodGetResources_0:
	addiu	$2,$19,-10
$LNBloodGetResources_1:
	sw	$2,684($18)
	addiu	$5,$18,40
	addiu	$16,$18,168
	sw	$19,16($29)
	lw	$7,684($18)
	jal	NBloodInitVerts
	addu	$6,$16,$0
	addiu	$4,$0,18
	addu	$6,$0,$0
	addu	$7,$16,$0
	lui	$2,%hi(nblood_data+8)
	lw	$5,684($18)
	addiu	$2,$2,%lo(nblood_data+8)
	jal	DG_MakePrim
	sw	$2,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LNBloodGetResources_2
	nop
	jal	DG_QueuePrim
	addu	$4,$16,$0
	lui	$2,%hi(GM_CurrentMap)
	lw	$2,%lo(GM_CurrentMap)($2)
	nop
	sh	$2,40($16)
$LNBloodGetResources_2:
	beq	$16,$0,$LNBloodGetResources_3
	sw	$16,36($18)
	lui	$4,%hi(nblood_str_blood_1)
	jal	GV_StrCode
	addiu	$4,$4,%lo(nblood_str_blood_1)
	jal	DG_GetTexture
	addu	$4,$2,$0
	addu	$17,$2,$0
	beq	$17,$0,$LNBloodGetResources_3
	addu	$6,$17,$0
	lw	$4,64($16)
	lw	$5,684($18)
	jal	NBloodInitPacks
	addu	$7,$19,$0
	addu	$6,$17,$0
	lw	$4,68($16)
	lw	$5,684($18)
	jal	NBloodInitPacks
	addu	$7,$19,$0
	addu	$2,$0,$0
	addiu	$3,$0,8
	j	$LNBloodGetResources_4
	sw	$3,680($18)
$LNBloodGetResources_3:
	addiu	$2,$0,-1
$LNBloodGetResources_4:
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
	.globl	NewNBloods
NewNBloods:
	addiu	$29,$29,-40
	sw	$19,28($29)
	addu	$19,$4,$0
	sw	$18,24($29)
	addu	$18,$5,$0
	sw	$20,32($29)
	addu	$20,$6,$0
	sw	$17,20($29)
	addu	$17,$0,$0
	sw	$16,16($29)
	addu	$16,$17,$0
	blez	$18,$LNewNBloods_3
	sw	$31,36($29)
	addiu	$4,$0,5
$LNewNBloods_0:
	jal	GV_NewActor
	addiu	$5,$0,688
	addu	$16,$2,$0
	beq	$16,$0,$LNewNBloods_1
	addu	$4,$16,$0
	lui	$5,%hi(NBloodAct)
	addiu	$5,$5,%lo(NBloodAct)
	lui	$6,%hi(NBloodDie)
	addiu	$6,$6,%lo(NBloodDie)
	lui	$7,%hi(nblood_str_file)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(nblood_str_file)
	addu	$4,$16,$0
	addu	$5,$19,$0
	addu	$6,$18,$0
	jal	NBloodGetResources
	addu	$7,$20,$0
	bgez	$2,$LNewNBloods_2
	addiu	$17,$17,1
	jal	GV_DestroyActor
	addu	$4,$16,$0
	j	$LNewNBloods_4
	addu	$2,$0,$0
$LNewNBloods_1:
	addiu	$17,$17,1
$LNewNBloods_2:
	slt	$2,$17,$18
	bne	$2,$0,$LNewNBloods_0
	addiu	$4,$0,5
$LNewNBloods_3:
	addu	$2,$16,$0
$LNewNBloods_4:
	lw	$31,36($29)
	lw	$20,32($29)
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
	.globl	NBloodMistInit
NBloodMistInit:
	addiu	$29,$29,-64
	sw	$17,52($29)
	addu	$17,$5,$0
	sw	$31,56($29)
	jal	DG_SetPos
	sw	$16,48($29)
	jal	GV_RandU
	addiu	$4,$0,4096
	addu	$16,$2,$0
	jal	rcos
	addu	$4,$16,$0
	bgez	$2,$LNBloodMistInit_0
	nop
	addiu	$2,$2,3
$LNBloodMistInit_0:
	sra	$2,$2,2
	sh	$2,16($29)
	jal	rsin
	addu	$4,$16,$0
	bgez	$2,$LNBloodMistInit_1
	nop
	addiu	$2,$2,3
$LNBloodMistInit_1:
	addiu	$4,$0,128
	sra	$2,$2,2
	jal	GV_RandU
	sh	$2,20($29)
	addiu	$2,$2,32
	sll	$3,$2,16
	lh	$6,16($29)
	sra	$3,$3,16
	div	$6,$3
	bne	$3,$0,$LNBloodMistInit_2
	nop
	.word	0x0007000D
$LNBloodMistInit_2:
	addiu	$1,$0,-1
	bne	$3,$1,$LNBloodMistInit_3
	lui	$1,0x8000
	bne	$6,$1,$LNBloodMistInit_3
	nop
	.word	0x0006000D
$LNBloodMistInit_3:
	mflo	$6
	lh	$5,20($29)
	nop
	div	$5,$3
	bne	$3,$0,$LNBloodMistInit_4
	nop
	.word	0x0007000D
$LNBloodMistInit_4:
	addiu	$1,$0,-1
	bne	$3,$1,$LNBloodMistInit_5
	lui	$1,0x8000
	bne	$5,$1,$LNBloodMistInit_5
	nop
	.word	0x0006000D
$LNBloodMistInit_5:
	mflo	$5
	sh	$2,18($29)
	lui	$2,%hi(DG_ZeroVector)
	sh	$6,16($29)
	sh	$5,20($29)
	addiu	$10,$2,%lo(DG_ZeroVector)
	lwl	$7,3($10)
	lwr	$7,0($10)
	lwl	$8,7($10)
	lwr	$8,4($10)
	swl	$7,43($29)
	swr	$7,40($29)
	swl	$8,47($29)
	swr	$8,44($29)
	jal	GV_RandS
	addiu	$4,$0,32
	addiu	$4,$0,32
	addu	$2,$17,$2
	jal	GV_RandS
	sh	$2,44($29)
	addiu	$4,$29,40
	addiu	$17,$29,24
	addu	$5,$17,$0
	addiu	$6,$0,1
	jal	DG_RotVector
	sh	$2,40($29)
	addiu	$4,$29,16
	addiu	$16,$29,32
	addu	$5,$16,$0
	jal	DG_PutVector
	addiu	$6,$0,1
	addu	$4,$16,$0
	jal	NBloodMist
	addu	$5,$17,$0
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
	.globl	NBloodMistAct
NBloodMistAct:
	addiu	$29,$29,-24
	sw	$16,16($29)
	addu	$16,$4,$0
	lui	$2,0x5555
	sw	$31,20($29)
	lw	$4,48($16)
	ori	$2,$2,0x5556
	mult	$4,$2
	lw	$3,32($16)
	lui	$2,%hi(GM_CurrentMap)
	sw	$3,%lo(GM_CurrentMap)($2)
	sra	$3,$4,31
	mfhi	$7
	subu	$3,$7,$3
	sll	$2,$3,1
	addu	$2,$2,$3
	bne	$4,$2,$LNBloodMistAct_0
	nop
	lw	$4,36($16)
	lw	$5,40($16)
	lw	$6,32($16)
	jal	NewNBloods
	nop
$LNBloodMistAct_0:
	lw	$3,48($16)
	nop
	slti	$2,$3,20
	beq	$2,$0,$LNBloodMistAct_1
	nop
	lw	$2,52($16)
	j	$LNBloodMistAct_6
	addiu	$2,$2,-9
$LNBloodMistAct_1:
	addiu	$2,$0,20
	bne	$3,$2,$LNBloodMistAct_2
	slti	$2,$3,40
	j	$LNBloodMistAct_6
	addiu	$2,$0,200
$LNBloodMistAct_2:
	beq	$2,$0,$LNBloodMistAct_3
	nop
	lw	$2,52($16)
	j	$LNBloodMistAct_6
	addiu	$2,$2,-8
$LNBloodMistAct_3:
	addiu	$2,$0,40
	bne	$3,$2,$LNBloodMistAct_4
	slti	$2,$3,50
	j	$LNBloodMistAct_6
	addiu	$2,$0,150
$LNBloodMistAct_4:
	bne	$2,$0,$LNBloodMistAct_5
	addiu	$2,$0,50
	beq	$3,$2,$LNBloodMistAct_6
	addiu	$2,$0,150
$LNBloodMistAct_5:
	lw	$2,52($16)
	nop
	addiu	$2,$2,-12
$LNBloodMistAct_6:
	sw	$2,52($16)
	lw	$3,48($16)
	nop
	slti	$2,$3,50
	beq	$2,$0,$LNBloodMistAct_7
	nop
	lw	$4,36($16)
	lw	$5,52($16)
	jal	NBloodMistInit
	nop
	lw	$2,48($16)
	j	$LNBloodMistAct_8
	slti	$2,$2,30
$LNBloodMistAct_7:
	andi	$2,$3,0x1
$LNBloodMistAct_8:
	beq	$2,$0,$LNBloodMistAct_9
	nop
	lw	$4,36($16)
	lw	$5,52($16)
	jal	NBloodMistInit
	nop
$LNBloodMistAct_9:
	lw	$2,48($16)
	nop
	addu	$3,$2,$0
	addiu	$2,$2,1
	slti	$3,$3,61
	bne	$3,$0,$LNBloodMistAct_10
	sw	$2,48($16)
	jal	GV_DestroyActor
	addu	$4,$16,$0
$LNBloodMistAct_10:
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
	.globl	NBloodMistDie
NBloodMistDie:
	jr	$31
	nop
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NBloodMistGetResources
NBloodMistGetResources:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	sw	$16,24($29)
	addu	$16,$5,$0
	sw	$18,32($29)
	addu	$18,$6,$0
	sw	$31,36($29)
	lhu	$2,20($16)
	addiu	$4,$29,16
	sh	$2,16($29)
	lhu	$2,24($16)
	addiu	$5,$0,214
	sh	$2,18($29)
	lhu	$2,28($16)
	addiu	$6,$0,1
	jal	GM_SeSetMode
	sh	$2,20($29)
	lui	$2,%hi(GM_CurrentMap)
	lw	$3,%lo(GM_CurrentMap)($2)
	addiu	$2,$0,200
	sw	$16,36($17)
	sw	$18,40($17)
	sw	$2,52($17)
	sw	$0,44($17)
	sw	$0,48($17)
	sw	$3,32($17)
	lw	$31,36($29)
	lw	$18,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	NewNBlood
NewNBlood:
	addiu	$29,$29,-32
	sw	$17,20($29)
	addu	$17,$4,$0
	addiu	$4,$0,5
	addiu	$5,$0,56
	sw	$31,24($29)
	jal	GV_NewActor
	sw	$16,16($29)
	addu	$16,$2,$0
	beq	$16,$0,$LNewNBlood_0
	addu	$4,$16,$0
	lui	$5,%hi(NBloodMistAct)
	addiu	$5,$5,%lo(NBloodMistAct)
	lui	$6,%hi(NBloodMistDie)
	addiu	$6,$6,%lo(NBloodMistDie)
	lui	$7,%hi(nblood_str_file)
	jal	GV_SetNamedActor
	addiu	$7,$7,%lo(nblood_str_file)
	addu	$4,$16,$0
	addu	$5,$17,$0
	jal	NBloodMistGetResources
	addiu	$6,$0,1
	bgez	$2,$LNewNBlood_1
	addu	$2,$16,$0
	jal	GV_DestroyActor
	addu	$4,$16,$0
	j	$LNewNBlood_1
	addu	$2,$0,$0
$LNewNBlood_0:
	addu	$2,$16,$0
$LNewNBlood_1:
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
	.globl	NBloodMist
NBloodMist:
	addiu	$29,$29,-48
	sw	$31,40($29)
	lhu	$2,0($4)
	nop
	sh	$2,16($29)
	lhu	$2,2($4)
	addiu	$3,$29,24
	sh	$2,18($29)
	lhu	$2,4($4)
	lui	$6,%hi(nblood_data+16)
	sh	$2,20($29)
	lhu	$2,0($5)
	addiu	$6,$6,%lo(nblood_data+16)
	sh	$2,24($29)
	lhu	$2,2($5)
	addu	$4,$0,$0
	sh	$2,2($3)
	lhu	$2,4($5)
	addu	$5,$4,$0
	sh	$2,4($3)
	addiu	$2,$29,16
	sh	$0,32($29)
	sh	$0,34($29)
	sw	$2,20($6)
	jal	NewAnime
	sh	$0,32($29)
	lw	$31,40($29)
	nop
	jr	$31
	addiu	$29,$29,48
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
nblood_str_blood_1:
	.ascii	"blood_1"
	.byte	0
	.align	2
nblood_str_file:
	.ascii	"n_blood.c"
	.byte	0
	.data
	.align	2
nblood_data:
	.word	0x00000400
	.word	0x00000000
	.word	0x00320032
	.word	0x00640064
	.word	0x00011660
	.word	0x00010001
	.word	0x01F40001
	.word	0x00A00001
	.word	0x00FF00A0
	.word	0x00000000
	.text
