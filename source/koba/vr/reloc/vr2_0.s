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
	lui	$5,%hi(Act)
	addiu	$5,$5,%lo(Act)
	lui	$6,%hi(Die)
	addiu	$6,$6,%lo(Die)
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
	jal	GetResources
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
vr2_str_file:
	.ascii	"vr2.c"
	.byte	0
	.align	2
vr2_str_endproc:
	.ascii	"Please Set ENDPROC!\n"
	.byte	0
	.text
