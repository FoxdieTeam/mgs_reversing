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
vrclear2_weights:
	.word	0x0A0A010A
	.word	0x0A0A1E0A
	.word	0x00000A0A
	.align	2
vrclear2_str_replay:
	.ascii	"replay"
	.byte	0
	.text
