	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	Vrclear2GetResources
Vrclear2GetResources:
	addiu	$29,$29,-64
	sw	$19,52($29)
	addu	$19,$4,$0
	addiu	$4,$0,99
	lui	$2,%hi(GM_CurrentMap)
	sw	$5,%lo(GM_CurrentMap)($2)
	addiu	$2,$0,320
	sw	$31,56($29)
	sw	$18,48($29)
	sw	$17,44($29)
	sw	$16,40($29)
	jal	GCL_GetOption
	sw	$2,972($19)
	beq	$2,$0,$LVrclear2GetResources_0
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrclear2GetResources_1
	sw	$2,1008($19)
$LVrclear2GetResources_0:
	addiu	$2,$0,1
	sw	$2,1008($19)
$LVrclear2GetResources_1:
	jal	GCL_GetOption
	addiu	$4,$0,112
	beq	$2,$0,$LVrclear2GetResources_5
	nop
	jal	GCL_StrToInt
	addu	$4,$2,$0
	addu	$16,$2,$0
	addiu	$2,$0,4
	bne	$16,$2,$LVrclear2GetResources_2
	addiu	$2,$0,1
	sh	$2,948($19)
	j	$LVrclear2GetResources_3
	addiu	$16,$0,3
$LVrclear2GetResources_2:
	sh	$0,948($19)
$LVrclear2GetResources_3:
	beq	$16,$0,$LVrclear2GetResources_5
	addiu	$17,$29,16
$LVrclear2GetResources_4:
	jal	GCL_NextStr
	addiu	$16,$16,-1
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,0($17)
	bne	$16,$0,$LVrclear2GetResources_4
	addiu	$17,$17,4
$LVrclear2GetResources_5:
	jal	GCL_GetOption
	addiu	$4,$0,115
	beq	$2,$0,$LVrclear2GetResources_6
	sw	$2,964($19)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	jal	GCL_NextStr
	sw	$2,984($19)
	jal	GCL_StrToInt
	addu	$4,$2,$0
	j	$LVrclear2GetResources_7
	sw	$2,988($19)
$LVrclear2GetResources_6:
	sw	$0,984($19)
	sw	$0,988($19)
$LVrclear2GetResources_7:
	jal	Vrclear2_800DEF84
	addu	$4,$19,$0
	addiu	$4,$0,122
	lui	$2,%hi(vrclear2_pad186c)
	addiu	$2,$2,%lo(vrclear2_pad186c)
	sw	$2,960($19)
	sw	$2,956($19)
	lw	$2,1012($19)
	addiu	$3,$0,-9
	and	$2,$2,$3
	jal	GCL_GetOption
	sw	$2,1012($19)
	beq	$2,$0,$LVrclear2GetResources_9
	addu	$16,$0,$0
	lw	$2,1012($19)
	addu	$17,$19,$0
	ori	$2,$2,0x8
	sw	$2,1012($19)
$LVrclear2GetResources_8:
	jal	GCL_NextStr
	nop
	jal	GCL_GetString
	addu	$4,$2,$0
	beq	$2,$0,$LVrclear2GetResources_9
	sw	$2,956($17)
	addiu	$16,$16,1
	slti	$2,$16,2
	bne	$2,$0,$LVrclear2GetResources_8
	addiu	$17,$17,4
$LVrclear2GetResources_9:
	jal	GCL_GetOption
	addiu	$4,$0,116
	beq	$2,$0,$LVrclear2GetResources_11
	addu	$16,$0,$0
	addu	$17,$19,$0
$LVrclear2GetResources_10:
	jal	GCL_NextStr
	addiu	$16,$16,1
	jal	GCL_StrToInt
	addu	$4,$2,$0
	sw	$2,44($17)
	slti	$2,$16,4
	bne	$2,$0,$LVrclear2GetResources_10
	addiu	$17,$17,4
	j	$LVrclear2GetResources_13
	addu	$16,$0,$0
$LVrclear2GetResources_11:
	addiu	$16,$0,3
	addiu	$2,$19,12
$LVrclear2GetResources_12:
	sw	$0,44($2)
	addiu	$16,$16,-1
	bgez	$16,$LVrclear2GetResources_12
	addiu	$2,$2,-4
	addu	$16,$0,$0
$LVrclear2GetResources_13:
	lui	$2,%hi(vrclear2_buttons)
	addiu	$18,$2,%lo(vrclear2_buttons)
	addiu	$17,$29,16
$LVrclear2GetResources_14:
	addu	$4,$18,$0
	lw	$5,0($17)
	jal	VrMenu_InitItem
	addiu	$6,$0,1
	beq	$2,$0,$LVrclear2GetResources_15
	nop
	addiu	$17,$17,4
$LVrclear2GetResources_15:
	addiu	$16,$16,1
	slti	$2,$16,5
	bne	$2,$0,$LVrclear2GetResources_14
	addiu	$18,$18,120
	lui	$4,%hi(vrclear2_str_go_vrsave)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrclear2_str_go_vrsave)
	lui	$3,%hi(vrclear2_buttons+380)
	sw	$2,%lo(vrclear2_buttons+380)($3)
	lw	$3,1012($19)
	addiu	$4,$0,-497
	and	$3,$3,$4
	sw	$3,1012($19)
	lw	$31,56($29)
	lw	$19,52($29)
	lw	$18,48($29)
	lw	$17,44($29)
	lw	$16,40($29)
	addu	$2,$0,$0
	jr	$31
	addiu	$29,$29,64
	.set	macro
	.set	reorder
	.rdata
	.align	2
vrclear2_pad186c:
	.word	0x00000000
	.align	2
vrclear2_str_go_vrsave:
	.ascii	"GO_VRSAVE"
	.byte	0
	.text
