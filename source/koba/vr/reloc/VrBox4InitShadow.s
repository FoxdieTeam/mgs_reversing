	.set	noreorder
	.set	noat
	.set	nomacro
	.text
	.globl	VrBox4InitShadow
VrBox4InitShadow:
	addiu	$29,$29,-40
	sw	$17,28($29)
	addu	$17,$4,$0
	addiu	$6,$17,1124
	addiu	$4,$17,1108
	addiu	$7,$17,1100
	sw	$31,32($29)
	sw	$16,24($29)
	sh	$0,2($6)
	sh	$0,1118($17)
	sh	$0,2($4)
	sh	$0,2($7)
	lhu	$2,36($17)
	addiu	$3,$17,36
	addiu	$2,$2,256
	sh	$2,1116($17)
	sh	$2,1100($17)
	lhu	$2,4($3)
	nop
	addiu	$2,$2,256
	sh	$2,4($4)
	sh	$2,4($7)
	lhu	$2,36($17)
	addiu	$5,$0,1
	addiu	$2,$2,-256
	sh	$2,1124($17)
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
	beq	$16,$0,$LVrBox4InitShadow_0
	nop
	jal	DG_QueuePrim
	addu	$4,$16,$0
	lui	$2,%hi(GM_CurrentMap)
	lw	$2,%lo(GM_CurrentMap)($2)
	nop
	sh	$2,40($16)
$LVrBox4InitShadow_0:
	sw	$16,1096($17)
	beq	$16,$0,$LVrBox4InitShadow_1
	addiu	$2,$0,-1
	addiu	$2,$0,500
	sh	$2,46($16)
	lui	$4,%hi(vrbox4_str_shadow)
	jal	GV_StrCode
	addiu	$4,$4,%lo(vrbox4_str_shadow)
	jal	DG_GetTexture
	addu	$4,$2,$0
	addu	$17,$2,$0
	beq	$17,$0,$LVrBox4InitShadow_1
	addiu	$2,$0,-1
	lw	$4,64($16)
	jal	InitShadowPoly
	addu	$5,$17,$0
	lw	$4,68($16)
	jal	InitShadowPoly
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
$LVrBox4InitShadow_1:
	lw	$31,32($29)
	lw	$17,28($29)
	lw	$16,24($29)
	jr	$31
	addiu	$29,$29,40
	.set	macro
	.set	reorder
	.set	at
	.rdata
	.align	2
	.align	2
vrbox4_str_shadow:
	.ascii	"shadow"
	.byte	0
	.text
