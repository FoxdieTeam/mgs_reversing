	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBg3GetResources
VrBg3GetResources:
	addiu	$29,$29,-72
	sw	$21,60($29)
	addu	$21,$4,$0
	lui	$2,%hi(GM_CurrentMap)
	addiu	$4,$0,116
	sw	$31,68($29)
	sw	$22,64($29)
	sw	$20,56($29)
	sw	$19,52($29)
	sw	$18,48($29)
	sw	$17,44($29)
	sw	$16,40($29)
	jal	GCL_GetOption
	sw	$5,%lo(GM_CurrentMap)($2)
	beq	$2,$0,$LVrBg3GetResources_0
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrBg3GetResources_1
	sw	$2,212($21)
$LVrBg3GetResources_0:
	sw	$0,212($21)
$LVrBg3GetResources_1:
	lw	$2,212($21)
	nop
	slti	$2,$2,14
	bne	$2,$0,$LVrBg3GetResources_2
	addiu	$2,$0,13
	sw	$2,212($21)
$LVrBg3GetResources_2:
	jal	GCL_GetOption
	addiu	$4,$0,97
	beq	$2,$0,$LVrBg3GetResources_3
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrBg3GetResources_4
	sh	$2,234($21)
$LVrBg3GetResources_3:
	sh	$0,234($21)
$LVrBg3GetResources_4:
	sw	$0,16($29)
	addiu	$4,$0,2066
	addiu	$5,$0,4
	addu	$6,$0,$0
	jal	DG_MakePrim
	addu	$7,$6,$0
	addu	$22,$2,$0
	beq	$22,$0,$LVrBg3GetResources_5
	addiu	$16,$21,36
	jal	DG_QueuePrim
	addu	$4,$22,$0
	lui	$2,%hi(GM_CurrentMap)
	lw	$2,%lo(GM_CurrentMap)($2)
	nop
	sh	$2,40($22)
	addiu	$16,$21,36
$LVrBg3GetResources_5:
	lui	$4,%hi(bg3_op_back_l)
	addiu	$4,$4,%lo(bg3_op_back_l)
	jal	GV_StrCode
	sw	$22,32($21)
	jal	DG_GetTexture
	addu	$4,$2,$0
	lui	$4,%hi(bg3_op_back_r)
	addiu	$4,$4,%lo(bg3_op_back_r)
	jal	GV_StrCode
	sw	$2,196($21)
	jal	DG_GetTexture
	addu	$4,$2,$0
	addu	$4,$21,$0
	addu	$6,$16,$0
	addiu	$17,$0,159
	addiu	$16,$0,111
	addiu	$18,$0,-160
	addiu	$20,$0,-112
	sw	$2,200($21)
	sw	$0,16($29)
	sw	$17,20($29)
	sw	$16,24($29)
	sw	$18,28($29)
	sw	$20,32($29)
	lw	$5,196($21)
	jal	VrBg3InitPoly
	addu	$7,$0,$0
	addu	$4,$21,$0
	addiu	$6,$21,76
	addiu	$19,$0,112
	sw	$19,16($29)
	sw	$17,20($29)
	sw	$16,24($29)
	sw	$18,28($29)
	sw	$0,32($29)
	lw	$5,196($21)
	jal	VrBg3InitPoly
	addu	$7,$0,$0
	addu	$4,$21,$0
	addiu	$6,$21,116
	sw	$0,16($29)
	sw	$17,20($29)
	sw	$16,24($29)
	sw	$0,28($29)
	sw	$20,32($29)
	lw	$5,200($21)
	jal	VrBg3InitPoly
	addu	$7,$0,$0
	addu	$4,$21,$0
	addiu	$6,$21,156
	sw	$19,16($29)
	sw	$17,20($29)
	sw	$16,24($29)
	sw	$0,28($29)
	sw	$0,32($29)
	lw	$5,200($21)
	jal	VrBg3InitPoly
	addu	$7,$0,$0
	addiu	$16,$21,36
	addu	$7,$0,$0
	addu	$2,$22,$0
	addiu	$5,$2,36
	lui	$2,%hi(GV_Clock)
	lw	$2,%lo(GV_Clock)($2)
	lw	$3,32($21)
	ori	$8,$0,0xe7ff
	sw	$0,204($21)
	sll	$2,$2,2
	addu	$3,$3,$2
	lw	$6,64($3)
$LVrBg3GetResources_6:
	nop
	addu	$3,$6,$0
	addu	$2,$16,$0
	addiu	$4,$16,32
$LVrBg3GetResources_7:
	lw	$9,0($2)
	lw	$10,4($2)
	lw	$11,8($2)
	lw	$12,12($2)
	sw	$9,0($3)
	sw	$10,4($3)
	sw	$11,8($3)
	sw	$12,12($3)
	addiu	$2,$2,16
	bne	$2,$4,$LVrBg3GetResources_7
	addiu	$3,$3,16
	lw	$9,0($2)
	lw	$10,4($2)
	sw	$9,0($3)
	sw	$10,4($3)
	sh	$8,0($6)
	lhu	$2,10($5)
	nop
	addiu	$2,$2,-1000
	sh	$2,10($5)
	lh	$2,234($21)
	nop
	beq	$2,$0,$LVrBg3GetResources_8
	nop
	lw	$2,0($5)
	nop
	ori	$2,$2,0x100
	sw	$2,0($5)
$LVrBg3GetResources_8:
	addiu	$5,$5,84
	addiu	$6,$6,40
	addiu	$7,$7,1
	slti	$2,$7,4
	bne	$2,$0,$LVrBg3GetResources_6
	addiu	$16,$16,40
	lw	$31,68($29)
	lw	$22,64($29)
	lw	$21,60($29)
	lw	$20,56($29)
	lw	$19,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,72
	.set	macro
	.set	reorder
	.rdata
	.align	2
	.align	2
bg3_op_back_l:
	.ascii	"op_back_l"
	.byte	0
	.align	2
bg3_op_back_r:
	.ascii	"op_back_r"
	.byte	0
	.text
